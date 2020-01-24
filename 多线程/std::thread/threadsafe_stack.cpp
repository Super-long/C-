#include <exception> //exception
#include <memory> //shared_ptr
#include <mutex> //mutex lock_guard
#include <stack> //stack
#include <thread> //thread
#include <vector> //vector
#include <iostream> //for debugging
#include <algorithm> //for_each
#include <functional> //mem_fn

struct empty_stack : std::exception{
    const char* what() const throw(){ //Equivalent to noexcept
        exception::what();
    }
};

struct possible_lost_value : std::exception{
    const char* what() const throw(){
        exception::what();
    }
};

//

template<typename T>
class threadsafe_stack{
    private:
        std::stack<T> data;
        mutable std::mutex m; //这个mutable有点6 回去再看一下effctive C++
    public:
        threadsafe_stack(){}
        threadsafe_stack(const threadsafe_stack& other){
            std::lock_guard<std::mutex> lock(other.m);
            data = other.data; //copy
        }

        threadsafe_stack& operator=(const threadsafe_stack&) = delete;

        void push(T new_value){
            std::lock_guard<std::mutex> lock(m);
            data.emplace(std::move(new_value));
        }

        std::shared_ptr<T> pop(){ //缺点: 可能T是一个很小的对象 资源消耗大
            std::lock_guard<std::mutex> lock(m);

            if(data.empty()) throw empty_stack("return a pointer");
            std::shared_ptr<T> const res(std::make_shared<T>(data.top())); //一个顶层const 不允许改变值
            data.pop();
            return res;
        }

        //Requires stored objects to be copied.
        void pop(T& value){
            std::lock_guard<std::mutex> lock(m);
            if(data.empty()) throw empty_stack();
            value = data.top();
            data.pop();
        }

        //There is Optimal operation with movement construction.
        T pop_return_calue() noexcept(false) { //don't overload. 
            std::lock_guard<std::mutex> lock(m);
            if(std::is_nothrow_copy_constructible<T>::value 
                || std::is_nothrow_move_constructible<T>::value){ //ensure safety.
                    if(data.empty()) throw empty_stack("return value");
                    auto Temp = data.top();
                    data.pop();
                    return Temp;
            }
            //possible construction failture. Means the value may be lost.
            throw possible_lost_value();
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(m);
            return data.empty();
        }

        //size操作在此类中可能引起多线程之间的问题 比如以size为判断条件 就可能出现在空栈取元素的情况
        size_t size() const {
            std::lock_guard<std::mutex> lock(m); 
            return data.size();
        }
};

threadsafe_stack<int> sta;

void Push(){
    sta.push(10);
}

/* void Pop(){ 
    try{
        int Temp;
        sta.pop(Temp);
        std::cout << "pop : " << Temp << std::endl;
    }catch(empty_stack&){
        std::cout << "empty stack.\n";
    }
} */

template<typename Type>
void Pop(Type& Temp){
    try{
        sta.pop(Temp);
    }catch(empty_stack&){
        std::cout << "empty stack.\n";
    }
}

std::mutex mu;

int array_[10] = {0};

int main(){
    std::vector<std::thread> threads(10);
    for(int i = 0; i < 10; i++){
        int emp = 0;
        if(!(i&1))
            threads[i] = std::thread(Push);
        else{ 
            threads[i] = std::thread(Pop<int>, std::ref(array_[i]));
            //std::cout << emp << std::endl;
            /**
             * 上面的打印纯属sb行为 线程跑去执行别的函数了 主线程直接执行cout 当然打印的不对了
            */
        }
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   
    for(auto x : array_) std::cout << x << std::endl;
    return 0;
}