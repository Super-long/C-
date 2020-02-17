#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>

std::condition_variable cv;
std::mutex mutex_;

void test(){
    //sleep(5);
    std::unique_lock<std::mutex> guard(mutex_);
    cv.wait(guard);
    cout << "hello\n";
}

int main(){
    auto T = thread(test);
    {sleep(1);
     //   std::unique_lock<std::mutex> guard(mutex_);
        cv.notify_all();
    }
    getchar();
    T.join();
    return 0;
}