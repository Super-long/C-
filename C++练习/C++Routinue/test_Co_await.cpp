#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <memory>

#include <coroutine>

struct wait_some_times {
    int left_times;
    std::coroutine_handle<> handle;
    wait_some_times(int t) : left_times(t), handle(nullptr) {}
};

struct suspend_some_times {
    wait_some_times& d;
    suspend_some_times(wait_some_times& _d) : d(_d) {}
    bool await_ready() noexcept {
        std::cout << "call await_ready: " << d.left_times << std::endl;
        return d.left_times <= 0;
    }

    void await_suspend(std::coroutine_handle <> h) noexcept {
        // 记下来handle以便后面resume用
        d.handle = h;

        std::cout << "call await_suspend: " << (--d.left_times) << std::endl;
    }

    void await_resume() noexcept {
        std::cout << "call await_resume: " << d.left_times << std::endl;
        d.handle = nullptr;
    }
};

struct coroutine_task {
    struct promise_type {
        coroutine_task get_return_object() {
            return coroutine_task{};
        }
        auto initial_suspend() {
            return std::suspend_never{};
        }
        auto final_suspend() {
            return std::suspend_never{};
        }

        void unhandled_exception() {}
        void return_void() {}
    };
};

auto operator co_await(wait_some_times& x) noexcept {
    return suspend_some_times{ x };
}

coroutine_task f(wait_some_times& waiter) {
    std::cout << "begin to co_await" << std::endl;
    std::cout << "Coroutine thread: " << std::this_thread::get_id() << '\n';
    co_await waiter; // 只有前三次会协程切出
    std::cout << "Coroutine thread: " << std::this_thread::get_id() << '\n';
    co_await waiter;
    std::cout << "Coroutine thread: " << std::this_thread::get_id() << '\n';
    co_await waiter;
    co_await waiter; // 这之后await_ready返回true了，不会再切出
    co_await waiter;
    std::cout << "end of corotine" << std::endl;
}

int main(int argc, char* argv[]) {
#ifdef __cpp_coroutines
    std::cout << "__cpp_coroutines: " << __cpp_coroutines << std::endl;
#endif
    wait_some_times waiter{ 3 };
    f(waiter);

    while (waiter.handle && !waiter.handle.done()) {
        std::cout << "about to resume: " << waiter.left_times << std::endl;
        // 这里用传出的handle来恢复切入协程
        waiter.handle.resume();
    }

    return 0;
}