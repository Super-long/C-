#ifndef JOIN_THREADS_H_
#define JOIN_THREADS_H_

#include <vector> //vector
#include <thread> //thread

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

#endif //JOIN_THREADS_H_