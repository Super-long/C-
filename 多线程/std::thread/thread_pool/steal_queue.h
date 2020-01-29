#ifndef STEAL_QUEUE_H_
#define STEAL_QUEUE_H_

#include <deque> //deque
#include <mutex> //mutex
#include "function_wrapper.h" //function_wrapper

class work_stealing_queue
{
private:
    using data_type = function_wrapper;
    std::deque<data_type> work_queue;
    mutable std::mutex mu;
public:
    work_stealing_queue(){}
    work_stealing_queue(const work_stealing_queue&) = delete;
    work_stealing_queue& operator=(const work_stealing_queue&) = delete;

    bool empty() const {
        std::lock_guard<std::mutex> lk(mu);
        return work_queue.empty();
    }

    void push(data_type data){
        std::lock_guard<std::mutex> lk(mu);
        work_queue.emplace_front(std::move(data));
    }

    bool try_pop(data_type& data){
        std::lock_guard<std::mutex> lk(mu);
        if(work_queue.empty()) return false;

        data = std::move(work_queue.front());
        work_queue.pop_front();
        return true;
    }

    bool try_steal(data_type& data){
        std::lock_guard<std::mutex> lk(mu);
        if(work_queue.empty()) return false;

        data = std::move(work_queue.back());
        work_queue.pop_back();
        return true;  
    }
};

#endif //STEAL_QUEUE_H_