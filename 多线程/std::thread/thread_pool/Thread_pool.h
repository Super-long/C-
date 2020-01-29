#ifndef THREAD_POOL
#define THREAD_POOL

#include "Threadsafe_Queue.h" //Threadsafe_Queue
#include "function_wrapper.h" //function_wrapper
#include <thread> //thread
#include <atomic> //atomic_bool
#include <future> //future packaged_task

class join_threads{
    std::vector<std::thread>& threads;
    public: 
        explicit join_threads(std::vector<std::thread>& thread_) 
            : threads(thread_) {}
        join_threads() = delete;

        ~join_threads(){
            for(size_t i = 0; i < threads.size(); i++){
                if(threads[i].joinable())
                    threads[i].join();
            }
        }
};

class thread_pool{
    private:
        std::atomic<bool> done; //顺序很重要 一会测试下
        Threadsafe_Queue<function_wrapper> work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        void work_thread(){
            while(!done){ //implenebt of spin-lock, and can be implemented as condition_variable.
                function_wrapper Task;
                if(work_queue.try_pop(Task)){ //感觉可以wait
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
                for(size_t i = 0; i < count; i++){
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
};


#endif //THREAD_POOL