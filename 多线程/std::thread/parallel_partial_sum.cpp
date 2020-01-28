#include <exception> //exception
#include <memory> //shared_ptr
#include <mutex> //mutex lock_guard
#include <thread> //thread
#include <vector> //vector
#include <future> //promise
#include <atomic> //atomic<bool>
#include <numeric> //partial_sum
#include <algorithm> //for_each

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

template<typename Iterator>
void parallel_partial_sum(Iterator lhs, Iterator rhs){
    using value_type = typename Iterator::value_type;

    struct process_chunk{
        void operator()(Iterator lhs, Iterator rhs,
            std::future<value_type>* previous_result, std::promise<value_type>* excepted){
                try{
                    Iterator end = rhs;
                    ++end;
                    std::partial_sum(lhs, end, lhs);
                    if(previous_result){
                        value_type result = previous_result->get();
                        *rhs += result;
                        if(excepted){
                            excepted->set_value(*rhs);
                        }
                        std::for_each(lhs, rhs, [&](value_type& para){
                            para += result;
                        });
                    }else if(excepted){
                        excepted->set_value(*rhs);
                    }
                }catch(...){
                    if(excepted)
                        excepted->set_exception(std::current_exception());
                    else 
                        throw;
                }
            }
    };
    
    unsigned long const length = std::distance(lhs, rhs);
    if(!length) 
        return;
    constexpr unsigned long const min_per_thread = (64 + sizeof(value_type) -1)/sizeof(value_type);
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const num_threads = std::min(max_threads, static_cast<unsigned long>(std::thread::hardware_concurrency()));

    unsigned long const block_size = length / num_threads;

    std::vector<std::thread> threads{num_threads - 1};
    std::vector<std::promise<value_type>> end_values{num_threads - 1};
    std::vector<std::future<value_type>> previous_values;
    previous_values.reserve(num_threads - 1);
    join_threads joiner(threads);

    Iterator block_start = lhs;
    for(size_t i = 0; i < (num_threads - 1); i++){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(process_chunk(), block_start, block_end,
            i!=0 ? &previous_values[i] : nullptr, &end_values[i]);
        block_start = block_end;
        ++block_start;
        previous_values.emplace_back(end_values[i].get_future());
    }
    Iterator finally = block_start;
    std::advance(finally, std::distance(block_start, rhs) - 1);
    process_chunk()(block_start, finally, 
    num_threads>1 ? &previous_values.back() : nullptr, nullptr);
}

#include<iostream>
using namespace std;
int main(){
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    parallel_partial_sum(vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(),[](int x){
        cout << x << " ";
    });
    return 0;
}