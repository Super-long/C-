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

int main(){
    thread t1([](int a){cout << a << endl;},5);
    t1.join();
    cout << "main\n";
    return 0;
}