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
            //run_penging_task();
        }
    }

    

public:
    thread_pool() : done(false), joiner(threads) {
        unsigned const Count = std::thread::hardware_concurrency();
        try{
            for(size_t i = 0; i < Count; i++){
                queues.emplace_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue));
                threads.emplace_back(std::thread(&thread_pool::work_thread, this, i));
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

    }
};

#endif //THREAD_POOL_H