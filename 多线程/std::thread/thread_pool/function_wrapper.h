#ifndef FUNCTION_WRAPPER_H_
#define FUNCTION_WRAPPER_H_

#include <memory> //unique_ptr

class function_wrapper{
    struct base_type{
        virtual void call() = 0;
        virtual ~base_type() {}
    };
    std::unique_ptr<base_type> ptr;
    template<typename T>
    struct wrapper_type : base_type{
        T fun;
        wrapper_type(T&& f) : fun(std::move(f)){}
        void call() override {fun();}
    };

    public:
        template<typename T>
        function_wrapper(T&& f) :
            ptr(new wrapper_type<T>(std::move(f))){}
        
        function_wrapper() = default;
        function_wrapper(function_wrapper&& f) : ptr(std::move(f.ptr)){}
        void operator()() {ptr->call();}
        function_wrapper& operator=(function_wrapper&& f){
            ptr = std::move(f.ptr);
            return *this;
        }

        function_wrapper(const function_wrapper&) = delete;
        function_wrapper(function_wrapper&) = delete;
        function_wrapper& operator=(const function_wrapper&) = delete;
};


#endif //FUNCTION_WRAPPER_H_