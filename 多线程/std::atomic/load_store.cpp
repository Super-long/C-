#include<atomic>
#include<iostream>
using namespace std;

enum class Player{
    one,
    two,
    three
};

int main(){
    atomic<Player> factory;
    //atomic<T>模板类，生成一个T类型的原子对象，并提供了系列原子操作函数
    //不要在保护数据中通过用户自定义类型T通过参数指针或引用使得共享数据超出保护的作用域
    
}