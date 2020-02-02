#include <bits/stdc++.h>
using namespace std;

class CountDownLatch{
private:
    std::condition_variable cv;
    std::mutex mutex_;
    std::atomic<unsigned> count;

public:
    explicit CountDownLatch(unsigned num) : count(num) {} 

    void wait(){
        std::unique_lock<std::mutex> guard(mutex_);
        while(count > 0){
            cv.wait(guard);
        }
    }

    void countdown(){
        --count;
        std::unique_lock<std::mutex> guard(mutex_);
        if(count == 0){
            cout << "in loop\n";
            cv.notify_all();
        }
    }
};

CountDownLatch Store(5);

void test(){
    Store.countdown();
    cout << "running.\n";
}

int main(){
    vector<std::thread> vec(5);
    for(size_t i = 0; i < 5; i++){
        vec[i] = std::thread(test);
    }
    Store.wait();
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    return 0;
}