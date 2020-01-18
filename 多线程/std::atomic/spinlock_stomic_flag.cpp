#include<bits/stdc++.h>
using namespace std;

class spinlock_mutex{
    private:
        std::atomic_flag flag;
    public:
        spinlock_mutex() : 
            flag(ATOMIC_FLAG_INIT){}
        void lock(){
            while(flag.test_and_set(std::memory_order_acquire));
        }//

        void unlock(){
            flag.clear(std::memory_order_release);
        }//与同一个线程之后的lock同步
};

int i;
spinlock_mutex m;

void work(){
    m.lock();
    ++i;
    m.unlock();
}

int main(){
    vector<std::thread> threads;
    for(int i=0;i<10;++i){
        threads.emplace_back(thread(work));
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    cout << i << endl;
    return 0;
}