#include<bits/stdc++.h>
using namespace std;

struct test
{
    std::mutex m;
    char padding[65532];
    int a;
};

struct Test
{
    std::mutex m;
    int a;
    char padding[65532];
};

test T;

void Run(){
    int i=0;
    while(i++ <= 1000
    ){
            std::lock_guard<std::mutex> lk(T.m);
            T.a = 10;
    }
}

int main(){
    std::vector<std::thread> vec(3);
    auto start = std::chrono::high_resolution_clock::now(); 
    for(size_t i = 0; i < 3; i++)
    {
        vec[i] = std::thread(Run);
    }
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    auto end = std::chrono::high_resolution_clock::now();
                                            //ratio参数a,b a秒为b个周期
    std::chrono::duration<double, std::ratio<1,100000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,100000>>>(end - start);

    cout << time_span.count() << endl;
    return 0;
}
//填充: 1.24231e+06 1.2963e+06 1.15297e+06 1.22368e+06 1.34197e+06
//不填充: 1.28118e+06 1.20476e+06 1.18688e+06 1.24925e+06 1.21647e+06