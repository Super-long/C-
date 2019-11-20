#include<iostream>
#include<sys/epoll.h>
#include<memory>
using namespace std;

int main(){
    unique_ptr<epoll_event[]> store_(new epoll_event[20]);
    store_[1].data.fd = 1;
    auto ptr = reinterpret_cast<epoll_event*>(store_.get());
    auto p = store_.get();
    cout << p[1].data.fd << endl;
    //当获取原指针以后直接用不行吗
    cout << ptr[1].data.fd << endl;
}