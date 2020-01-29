#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "Threadsafe_Queue.h" //Threadsafe_Queue
#include "function_wrapper.h" //function_wrapper
#include "join_threads.h" //join_threads
#include <thread> //thread
#include <atomic> //atomic_bool
#include <future> //future packaged_task

class thread_pool{
    private:
        std::atomic<bool> done; //顺序很重要 一会测试下
        Threadsafe_Queue<function_wrapper> work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        void work_thread(){
            while(!done){ //implenebt of spin-lock, and can be implemented as condition_variable.
                function_wrapper Task;
                if(work_queue.try_pop(Task)){
                    Task();
                }else{
                    std::this_thread::yield();
                }
            }
        }

    public:
        thread_pool() : done(false), joiner(threads) {
            try{
                unsigned int count = std::thread::hardware_concurrency();
                for(size_t i = 0; i < (count - 1); i++){
                    threads.emplace_back(std::thread(&thread_pool::work_thread,this));
                }
            }catch(...){
                done = true;
                throw;
            }
        }    

        ~thread_pool(){
            done = true;
        }
        template<typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type>
        submit(FunctionType fun){
            using result_type = typename std::result_of<FunctionType()>::type;
            std::packaged_task<result_type()> Task(std::move(fun));
            std::future<result_type> res(Task.get_future());
            work_queue.push(std::move(Task));
            return res;
        }

        void run_penging_task(){
            function_wrapper Task;
            if(work_queue.try_pop(Task)){
                Task();
            }else{
                std::this_thread::yield();
            }
        }
};

#endif //THREAD_POOL_H_