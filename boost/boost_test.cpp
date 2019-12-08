#include<boost/utility.hpp>
#include<iostream>
using namespace std;

class myclass : public boost::noncopyable{
    public:
        myclass() {}
        explicit myclass(int para) {}
};

int main(){
    myclass c1();
    myclass c2(5);
    return 0;
}

//编译成功 boost库运行OK