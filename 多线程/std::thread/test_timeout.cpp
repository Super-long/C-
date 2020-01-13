#include<bits/stdc++.h>
using namespace std;

std::timed_mutex mt;

void test(){
    if((mt.try_lock_until(std::chrono::steady_clock::now() + std::chrono::microseconds(100))) == false){
        mt.unlock();
        cout << "unlcok.\n";
    }else{
        cout << "lock.\n";
        mt.unlock();
    }
}

int main(){
    mt.lock();
/*     auto T = std::thread(test);
    T.detach(); */
    if((mt.try_lock_until(std::chrono::steady_clock::now() + std::chrono::microseconds(100))) == false){
        mt.unlock();
        cout << "lcok.\n";
    }else{
        cout << "unlock.\n";
        mt.unlock();
    }
    //getchar();
    return 0;
}