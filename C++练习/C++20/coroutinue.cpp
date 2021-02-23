#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <thread>
 
auto switch_to_new_thread(std::jthread& out) {
    //关键字 co_await 是一个操作符，所以我们只要实现这个操作符重载就可以实现协程等待任意类型。
    struct awaitable {
        std::jthread* p_out;
        bool await_ready() {
            std::cout << "ready\n";
            sleep(1);
            return true; 
        }

        // 返回值为void。将控制立即返回给当前协程的调用方
        // 因为协程在进入,await_suspend() 前已完全暂停，所以该函数可以自由地在线程间转移协程柄，而无需额外同步，其他持有句柄的线程可以调用resume
        // 转移句柄是非常有必要的，不调用resume无法返还控制权给调用方，这是裸协程，而不是用户态线程。
        void await_suspend(std::coroutine_handle<> h) {
            std::cout << "suspend\n";
            std::jthread& out = *p_out;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = std::jthread([h] { 
                sleep(2);
                h.resume(); 
            });
            // Potential undefined behavior: accessing potentially destroyed *this
            // std::cout << "New thread ID: " << p_out->get_id() << '\n';
            std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
        }
        void await_resume() {
            std::cout << "resume\n";
        }
    };
    return awaitable{&out};
}

// 要支持协程函数，首先要准备一个包装的类型，里面包含 promise_type ，然后提供基本的创建、维护handle的函数
struct task{
    struct promise_type {
        task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};
 
task resuming_on_new_thread(std::jthread& out) {
    std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
    co_await switch_to_new_thread(out);
    // awaiter destroyed here
    std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
}
 
int main() {
  std::jthread out;
  resuming_on_new_thread(out);
}
 