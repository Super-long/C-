#include <atomic> //atomic
#include <mutex> //mutex lock_guard
#include <thread> //thread
#include <condition_variable> // condition_variable

class interrupt_flag{
private:
    std::atomic<bool> flag;
    std::condition_variable* thread_cond;
    std::mutex set_clear_mutex;

public:
    interrupt_flag() : flag(false), thread_cond(nullptr) {}

    void set(){
        flag.store(true, std::memory_order_relaxed);
        std::lock_guard<std::mutex> guard(set_clear_mutex);
        if(static_cast<bool>(thread_cond)){ //用于主线程
            thread_cond->notify_all();
        }
    }

    bool is_set() const{
        return flag.load(std::memory_order_relaxed);
    }

    void set_condition_variable(std::condition_variable& cv){
        std::lock_guard<std::mutex> guard(set_clear_mutex);
        thread_cond = &cv;
    }

    void set_condition_clear(){
        std::lock_guard<std::mutex> guard(set_clear_mutex);
        thread_cond = nullptr;
    }

    struct RAII_cv{
        ~RAII_cv();
    };
};

thread_local interrupt_flag this_thread_interrupt_flag;

interrupt_flag::RAII_cv::~RAII_cv(){
    this_thread_interrupt_flag.set_condition_clear();
}
