//
// Created by lizhaolong on 2020/1/6.
//

#include <bits/stdc++.h>
using namespace std;

class backgound_task{
private:
    void do_something() const{
        cout << "do something\n";
    }

    void do_something_else()const{
        cout << "do something else\n";
    }
public:
    void operator()() const{
        do_something();
        do_something_else();
    }
};


void update_data(int a, std::pair<int,int>& pa){
    pa.first = 1;
    pa.second = 2;
}

void oops_again(int a){
    std::pair<int, int> pa;
    int d = 5;
    //确实是一个没注意到的问题 书上说不会修改 但我的机子上跑的是类型不匹配 这个ref太六了
    //std::ref 在模板传参的时候传入引用 用于bind thread等
    std::thread t(update_data, d, std::ref(pa));
    t.join();
    cout << pa.first << " " << pa.second << endl;
}

void some_function(){
        cout << "some function\n";
}

void some_other_function(){
    while (1){
        cout << "some_other_function\n";
}
}

void test(){
    std::thread t1(some_function);
    cout << "one\n";
    std::thread t2 = std::move(t1);
    cout << "one\n";
    t1 = std::thread(some_other_function);
    cout << "one\n";
    std::thread t3;
    cout << "one\n";
    t3 = std::move(t2);
    //t1 = std::move(t3); //尝试给一个有绑定了函数的线程再绑定一个函数 会引发错误
    t3.join();
    t1.join(); //主线程挂了以后所有线程死亡 也就是注释了
    //t1.detach();相当于在后台跑
    //TODO detach主线程挂了以后还会一直跑吗? 答 :主线程可以提前结束
}

int main(){
    backgound_task f;
    //下面写法的意思是接收单个参数并返回一个thread对象 因为C++会把下述式子解释成一个函数声明.
    std::thread my_thread((backgound_task()));//p15
    my_thread.join();
    oops_again(5);
    test();
    return 0;
}