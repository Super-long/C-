#include<thread>
#include<iostream>
#include<mutex>
using namespace std;

/* int main(){
    std::thread t1([]{cout << "hello\n";});
   // t1.join();
   // cout << "main thread\n";
   // return 0;
}*/

/* int main(){
    thread t1([](int a){cout << a << endl;},5);//
    t1.join();
    cout << "main\n";
    return 0;
} */

std::mutex mt;
int Data;

void add(int a){
    mt.lock();
    Data += a;
    std::cout << "add Data = " << Data << endl;
    mt.unlock();
}

void mul(int a){
    mt.lock();
    Data *= a;
    std::cout << "mul Data = " << Data << endl;
    mt.unlock();
}

/* void test(){
    unique_lock<mutex> h(mt,std::defer_lock);
    mt.lock();
    Data -= 5;
    cout << "test Data = " << Data << endl;
} */

void test(){
    mt.lock();
    unique_lock<mutex> h(mt,std::adopt_lock);
    //h.lock();
    Data -= 5;
    cout << "test Data = " << Data << endl;
} 

int main(){
    thread t1(add, 2);
    t1.detach();
    thread t3(test);
    t3.detach();
    thread t2(mul,10);
    t2.detach();

    getchar();
    return 0;
}

//锁管理器 提供自动加锁解锁过程 异常安全 
//unique_lock 效率上差一点 内存占用多一点 但更加灵活
//lock_guard 效率高 不灵活