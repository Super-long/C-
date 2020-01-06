#include<bits/stdc++.h>
using namespace std;

template<typename Iterator, typename T>
struct accumulate_block{
    void operator()(Iterator lhs, Iterator rhs, T& res){
        res = std::accumulate(lhs, rhs, res);
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

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = lhs;
    for(unsigned long i = 0; i < num_threads - 1; ++i){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, rhs, results[num_threads - 1]);
    for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

int main(){
    std::vector<int> vec;

    default_random_engine generator(time(NULL));//engine 引擎
    uniform_int_distribution<unsigned> distribution(0, 2000); //均匀分布

    for(int i=0;i<100000;++i){
        vec.emplace_back(distribution(generator));
    }

    cout << parallel_accumulate(vec.begin(), vec.end(), 0) << endl;
}