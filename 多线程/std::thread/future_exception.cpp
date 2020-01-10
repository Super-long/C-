#include<bits/stdc++.h>
using namespace std;

double sqrt_Temp(double T){
    if(T < 0) 
        throw std::out_of_range("T < 0");
    return sqrt(T);
}

void test(std::promise<int>& T){
    try{
        T.set_value(sqrt_Temp(-1));
    }catch(...){
        cout << "catch in test\n";
        T.set_exception(std::current_exception());
    } 
    //T.set_exception(std::logic_error("test"));
    //上面操作失败的原因是参数是一个异常的指针 
    //T.set_exception(std::copy_exception(std::logic_error("test")));
}

string test_two(int t){
    throw std::logic_error("joker.");
    return string(t,'a');
}

void test_three(packaged_task<decltype(test_two)>& pa){
    pa(10);
}

int main(){
    //线程间转移异常
    std::future<double> f = std::async(sqrt_Temp, -1);
    try{
        double y = f.get();
    }catch(...){
        cout << "catch a exception.\n";
    }

    std::promise<int> p;
    auto th = std::thread(test, std::ref(p));
    th.detach();
    try{
        auto Temp = p.get_future();
        cout << Temp.get() << endl;
    }catch(...){
        cout << "catch a exception.\n";
    }

    std::packaged_task<decltype(test_two)> pa(test_two);
    auto EE = std::thread(test_three, std::ref(pa));
    EE.detach();
    try{
        auto E = pa.get_future();
        cout << E.get() << endl;
    }catch(...){
        cout << "three\n";
    }
    return 0;
}