#include <thread>
#include <iostream>

int create();
int main(int argc, char **argv)
{

    std::thread workerB([]() {
       std::cout << "B start time: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
       int b  = create();       
       std::cout << "B: " << b << std::endl;
    });
    std::thread workerA([]() {
       std::cout << "A start time: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
       int a = create();
       std::cout << "A: " << a << std::endl;
    });
    workerA.join();
    workerB.join();

    return 0;
}


int create()
{
    static struct M {
      int value;
      M(): value(0) {
          std::cout << "Create M" << std::endl;
          std::this_thread::sleep_for(std::chrono::seconds(5));
      }
    } m;
    std::cout << "time: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
    return m.value++;
}

//----- 下面的代码在编译工具里面跑可以看到为static加的锁
// 深入理解函数内静态局部变量初始化 https://www.cnblogs.com/william-cheung/p/4831085.html
#include<thread>

struct M {
    int value;
    M(): value(0){
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
};

void foo() {
    static M bar;
}

int main(int argc, char **argv)
{

    std::thread workerB(foo);
    std::thread workerA(foo);
    workerA.join();
    workerB.join();

    return 0;
}