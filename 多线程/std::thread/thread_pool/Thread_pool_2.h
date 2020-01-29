#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "Threadsafe_Queue.h" //Threadsafe_Queue
#include "function_wrapper.h" //function_wrapper
#include "join_threads.h" //join_threads
#include "steal_queue.h" //work_stealing_queue
#include <thread> //thread
#include <atomic> //atomic_bool
#include <future> //future packaged_task

class thread_pool{
private:
    using task_type = function_wrapper;

    std::atomic<bool> done;
    Threadsafe_Queue<task_type> pool_work_queue;
    std::vector<std::unique_ptr<work_stealing_queue>> queues;
    std::vector<std::thread> threads;
    join_threads joiner;

    static thread_local work_stealing_queue* local_queue;
    static thread_local unsigned index;

    void work_thread(unsigned index_){
        index = index_;
        local_queue = queues[index].get();
        while(!done){
            run_penging_task();
        }
    }

    bool pop_from_local_queue(task_type& task){
        cout << "loacl : " << local_queue->size() << endl;
        return static_cast<bool>(local_queue) && local_queue->try_pop(task); 
    }

    bool pop_from_pool_queue(task_type& task){
        return pool_work_queue.try_pop(task);
    }

    bool pop_from_other_local_queue(task_type& task){
        for(size_t i = 0; i < queues.size(); i++){
            const unsigned this_index = (index + i + 1)%queues.size();
            if(queues[this_index]->try_steal(task))
                return true;
        }
        return false;
    }

public:
    thread_pool() : done(false),threads(std::thread::hardware_concurrency()), joiner(threads) {
        try{
            for(size_t i = 0; i < threads.size(); i++){
                auto x = new work_stealing_queue;
                queues.emplace_back(std::unique_ptr<work_stealing_queue>(x));
                threads[i] = std::thread(&thread_pool::work_thread, this, i);
                //TODO 这里出现莫名奇妙的段错误 找不到错.
            }
        }catch(...){
            done = true;
            throw;
        }
    }

    ~thread_pool(){
        done = true;
    }

    void run_penging_task(){
        task_type Task;
        if(pop_from_local_queue(Task) || pop_from_pool_queue(Task)
            || pop_from_other_local_queue(Task)){
                Task();
        }else{
            std::this_thread::yield();
        }
    }

    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
    submit(FunctionType fun){
        using result_type = typename std::result_of<FunctionType()>::type;
        std::packaged_task<result_type()> Task(std::move(fun));
        std::future<result_type> res(Task.get_future());
        if(local_queue){
            local_queue->push(std::move(Task));
        }else{
            pool_work_queue.push(std::move(Task));
        }
        return res;
    }
};

thread_local work_stealing_queue* //容易忘记初始化
    thread_pool::local_queue = nullptr;
thread_local unsigned
    thread_pool::index = 0;

#endif //THREAD_POOL_H