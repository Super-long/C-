#ifndef INTERRUPT_THREAD_H_
#define INTERRUPT_THREAD_H_

#include <thread> //thread
#include <future> //future promise
#include <exception> //exception
#include <condition_variable> // condition_variable
#include <chrono> //std::chrono
#include "interrupt_flag.h" //interrupt_flag

class thread_interrupted : public std::exception{
    const char* what() const throw(){ //Equivalent to noexcept
        exception::what();
    }
};

class interrupt_thread{
private:
    std::thread internal_thread;
    interrupt_flag* flag;

public:
    template<typename FunctionType>
    interrupt_thread(FunctionType fun){
        std::promise<interrupt_flag*> pro;
        internal_thread = std::thread([fun,&pro]{
            pro.set_value(&this_thread_interrupt_flag);
            try{
                fun();
            }catch(thread_interrupted& ti){
                //do something.
            }
        });
        flag = pro.get_future().get();
    }

    void join() {internal_thread.join();}
    bool joinable() const {internal_thread.joinable();}
    void detach() {internal_thread.detach();}

    void interrupt(){
        if(flag){ //If it exists, it proves to be a worker thread.
            flag->set();
        }
    }

    void interruption_point(){
        if(this_thread_interrupt_flag.is_set()){
            throw thread_interrupted();
        }
    }

    void interruptible_wait(std::condition_variable& cv,
            std::unique_lock<std::mutex>& lk){
        interruption_point();
        this_thread_interrupt_flag.set_condition_variable(cv);
        interrupt_flag::RAII_cv Temp_RAII;
        interruption_point();
        cv.wait_for(lk, std::chrono::milliseconds(1));
        interruption_point();                
    }

    template<typename Predicate>
    void 
    interruptible_wait(std::condition_variable& cv,
            std::unique_lock<std::mutex>& lk, Predicate pred){
        interruption_point();
        this_thread_interrupt_flag.set_condition_variable(cv);
        interrupt_flag::RAII_cv Temp_RAII;
        while(!this_thread_interrupt_flag.is_set() && !pred()){
            cv.wait_for(lk, std::chrono::milliseconds(1));
        }
        interruption_point();
    }

    template<typename Type> //using waitfor() before get();
    void interruptible_wait(std::future<Type>& fu){
        while(!this_thread_interrupt_flag.is_set()){
            if(fu.wait_for(std::chrono::milliseconds(1)) == 
                std::future_status::ready)
                break;
        }
        interruption_point();
    }

};

#endif //INTERRUPT_THREAD_H_