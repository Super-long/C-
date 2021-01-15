#include<bits/stdc++.h>
using namespace std;

int sum_a __attribute__ ((aligned(64)));
//int sum_b __attribute__ ((aligned(64)));

void fun_a(){
    int count = 100000;  
    while(count--){
        sum_a+=1;
    }
    return;
}

int main(){
    auto tha = thread(fun_a);
    auto thb = thread(fun_a);
    
    tha.join();
    thb.join();
    
    std::cout << sum_a << endl;

    return 0;
}