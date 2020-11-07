#include<bits/stdc++.h>
using namespace std;

std::condition_variable cv;
std::mutex m;
bool done;

void write_loop(){
    auto const timeout = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    std::unique_lock<std::mutex> lk(m);
    while(true){
        while(!done){
            //if(cv.wait_until(lk, timeout) == std::cv_status::timeout)
            if(cv.wait_for(lk, std::chrono::seconds(5)) == std::cv_status::timeout)
            {
                cout << "timeout\n";
                break;
            }
        }
        done = false;
    }
}

int main(){
    auto T = std::thread(write_loop);
    T.detach();
    while(1){
        getchar();
        done = true;
        cv.notify_one();
    }
    auto start = std::chrono::high_resolution_clock::now(); 
    size_t lnum = 0;
    for(size_t i = 0; i < 100000000; i++){
        ++lnum; 
    }
    auto end = std::chrono::high_resolution_clock::now();
                                            //ratio参数a,b a秒为b个周期
    std::chrono::duration<double, std::ratio<1,100000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,100000>>>(end - start);
   
/*     std::chrono::duration<std::chrono::microseconds> tie_span 
    = std::chrono::duration_cast<std::chrono::microseconds>(end - start); */
//时间点可以转换为时间段 一般的类型都是时间段 我们需要duration_cast

    cout << time_span.count() << endl;
    //std::chrono::duration<double, std::chrono::seconds>(end - start).count()
    return 0;    
}