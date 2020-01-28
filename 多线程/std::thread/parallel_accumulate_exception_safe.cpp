#include<bits/stdc++.h>
using namespace std;

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

template<typename Iterator, typename T>
struct accumulate_block{
    T operator()(Iterator lhs, Iterator rhs){
        return std::accumulate(lhs, rhs, T());
    }
};

//一个并行计算的例子 基本原理是把一个vector分块 分别计算 最后累加
template<typename Iterator, typename T>
T parallel_accumulate(Iterator lhs, Iterator rhs, T init){
    const unsigned long length = std::distance(lhs, rhs);

    if(!length) return init;

    const unsigned long min_per_threads = 25; //每个线程处理的数字

    const unsigned long max_threads 
        = (length + min_per_threads - 1) / min_per_threads;

    const unsigned long hardware_threads
        = std::thread::hardware_concurrency();
    
    const unsigned long num_threads
        = std::min(hardware_threads!=0 ? hardware_threads : 2, max_threads);

    const unsigned long block_size = length / num_threads;

    std::vector<std::future<T>> results(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = lhs;
    join_threads joiner(threads);

    for(size_t i = 0; i < num_threads - 1; ++i){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        std::packaged_task<T(Iterator,Iterator)> task{
            accumulate_block<Iterator, T>()
        };
        results[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);
        block_start = block_end;
    }
    T result = init;
    for(size_t i = 0; i < (num_threads - 1); i++){
        result += results[i].get(); //可能抛出异常 但是异常安全,不会使得线程调用terminate
    }
    auto last_result = accumulate_block<Iterator, T>()(block_start, rhs);
    return result + last_result;
}

/**
 * @ 使用async 由库保证异常安全 不会出现空悬线程
 * @ 相对与packaged_task相比由库管理线程 能更好的利用get()的时间 效率更高
*/
template<typename Iterator, typename T> 
T _parallel_accumulate(Iterator lhs, Iterator rhs, T init){
    const unsigned long length = std::distance(lhs, rhs);
    constexpr const unsigned long max_size = 64/sizeof(T);//cache line
    if(length <= max_size){
        return std::accumulate(lhs, rhs, init);
    }else{
        Iterator mid_point = lhs;
        std::advance(mid_point, length/2);
        auto first_half = 
            std::async(_parallel_accumulate<Iterator, T>, lhs, mid_point, init);
        auto second_result = _parallel_accumulate(mid_point, rhs, init);
        return first_half.get() + second_result;
    }
}

int main(){
    std::vector<int> vec;

    default_random_engine generator(time(NULL));//engine 引擎
    uniform_int_distribution<unsigned> distribution(0, 2000); //均匀分布

    for(int i=0;i<100000;++i){
        vec.emplace_back(distribution(generator));
    }
    cout << _parallel_accumulate(vec.begin(), vec.end(), 0) << endl;
}