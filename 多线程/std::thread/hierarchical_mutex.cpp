#include<bits/stdc++.h>
using namespace std;

//其实层次锁就是一种强制的定义锁定顺序 无非是提供了一种方法检查运行时是否遵循约定 以此来避免死锁
//层次锁不是标准的一部分 
//像个链表一样
class hierarchical_mutex{
    private:
        std::mutex internal_mutex;
        uint64_t const hierarchical_value;
        uint64_t previous_value;
        static thread_local uint64_t this_thread_hierarchical_value;
        //这个限定符非常精髓

        void check_for_hierarchy() noexcept(false) {
            //等于号 : 锁定后在lock自己当然也是错的
            if(this_thread_hierarchical_value <= hierarchical_value){
                throw logic_error("mutex hierarchical violated.");
            }
        }

        void update_hierarchy_value(){
            previous_value = this_thread_hierarchical_value;
            this_thread_hierarchical_value = hierarchical_value;
        }
    
    public:
        constexpr explicit hierarchical_mutex(uint64_t value) : 
            hierarchical_value(value), previous_value(0) {}

        void lock() noexcept(false) {
            check_for_hierarchy();
            internal_mutex.lock();
            update_hierarchy_value();
        }

        void unlock(){
            this_thread_hierarchical_value = previous_value;
            internal_mutex.unlock();
        } 

        bool try_lock() noexcept(false) {
            check_for_hierarchy();
            if(!internal_mutex.try_lock()) return false;
            update_hierarchy_value();
            return true;
        }
};

thread_local uint64_t //容易忘记初始化
    hierarchical_mutex::this_thread_hierarchical_value = ULONG_MAX;

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

void high_level_fun(){
    std::lock_guard<hierarchical_mutex> guard1(high_level_mutex);
    std::lock_guard<hierarchical_mutex> guard2(low_level_mutex);
    std::unique_lock<hierarchical_mutex> a;
    hierarchical_mutex other(6000);
    //std::lock_guard<hierarchical_mutex> guard3(other);
    //加上以后就会抛错
}

int main(){
    auto T = std::thread(high_level_fun);
    T.join();
    return 0;
}