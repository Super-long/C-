#include <iostream>
#include <iomanip>
#include <vector>
#include <unistd.h>
#include <thread>

#include <memory>

#include <coroutine>

// 要支持协程函数，首先要准备一个包装的类型，里面包含 promise_type ，然后提供基本的创建、维护handle的函数。
struct test_rpc_generator {
    test_rpc_generator(const test_rpc_generator&) = delete;
    test_rpc_generator(test_rpc_generator&& other): coro(other.coro) {
        other.coro = nullptr;
    };
    ~test_rpc_generator() {
        if (coro) {
            coro.destroy();
        }
    }

    struct promise_type;
    using handle = std::coroutine_handle<promise_type>;

    struct promise_type {
        int* current_value;
        static auto get_return_object_on_allocation_failure() {
            return test_rpc_generator{nullptr};
        }

        auto get_return_object() {
            return test_rpc_generator{handle::from_promise(*this)};
        }

        auto initial_suspend() {
            current_value = nullptr;
            return std::suspend_never{};
        }

        auto final_suspend() {
            return std::suspend_always{};
        }

        void unhandled_exception() {
            std::terminate();
        }

        void return_void() {
        }

        // 注意这是指针赋值
        auto yield_value(int* value) {
            std::cout << "yield_value.\n";
            current_value = value;
            return std::suspend_always{};
        }
    };


    int* value() const {
        if (coro) {
            return coro.promise().current_value;
        }

        return 0;
    }

    bool move_next(int rpc_result) {
        std::cout << "move_next.\n";
        if (coro && coro.promise().current_value) {
            *coro.promise().current_value = rpc_result;
        }

        return coro ? (coro.resume(), !coro.done()) : false; 
    }

    bool await_ready() const {
        return !coro || coro.done();
    }

private:
    test_rpc_generator(handle h) : coro(h) {}
    handle coro;
};

test_rpc_generator f() {
    int rpc_res1, rpc_res2;
    co_yield &rpc_res1; // 比较像一次异步的调用
    std::cout << "Coroutine thread: " << std::this_thread::get_id() << '\n';
    // _alloca(rpc_res1);
    std::cout<< "resumed got rpc_res1: "<< rpc_res1<< "(@"<< &rpc_res1<< ")" << ", rpc_res2: "<< rpc_res2 <<"(@"<< &rpc_res2<< ")"<< std::endl;

    co_yield &rpc_res2;
    std::cout << "Coroutine thread: " << std::this_thread::get_id() << '\n';
    // _alloca(rpc_res2);
    std::cout<< "resumed got rpc_res1: "<< rpc_res1<< "(@"<< &rpc_res1<< ")" << ", rpc_res2: "<< rpc_res2 <<"(@"<< &rpc_res2<< ")"<< std::endl;
}

int main(int argc, char * argv[]) {
#ifdef __cpp_coroutines
    std::cout<< "__cpp_coroutines: "<< __cpp_coroutines<< std::endl;
#endif

    int rpc_fake_data = 1;
    auto g1 = f();
    auto g2 = f();
    void* detect_addr = malloc(4000);
    std::cout << "detect_addr:" << detect_addr << std::endl;
    free(detect_addr);

    for (bool is_continue = true; is_continue; is_continue = (!g1.await_ready() || !g2.await_ready())) {
        if (!g1.await_ready()) {
            g1.move_next(++ rpc_fake_data); // 调用一个闭包中的函数就会返回协程执行
            sleep(2);
            std::cout << "g1 value:" << g1.value() << std::endl;
        }

        if (!g2.await_ready()) {
            g2.move_next(++ rpc_fake_data);
            std::cout << "g2 value:" << g2.value() << std::endl;
        }

    }
    return 0;
}