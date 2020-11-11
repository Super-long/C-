#include <bits/stdc++.h>
using namespace std;

class test{
    friend test foo(double);
    public:
        test(){
            memset(array, 0, 100*sizeof(double));
        }

        test(const test& t){
            memcpy(this, &t, sizeof(test));
        }
    private:
        double array[100];
};

test foo(double val){
    test local;
    local.array[0] = val;
    local.array[99] = val;
    return local;
}

// 是否加上拷贝构造函数与NRV没什么关系

int main(){
    auto start = std::chrono::high_resolution_clock::now(); 

    for (size_t i = 0; i < 10000000; i++)
    {
        test t = foo(double(i));
    }
    

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::ratio<1,1000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,1000>>>(end - start);

    std::cout << time_span.count() << std::endl;
    return 0;
}
