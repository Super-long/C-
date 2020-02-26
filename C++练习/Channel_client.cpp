#include <functional>
#include <queue>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <sys/eventfd.h>

std::queue<std::function<void()>> Event;
int Eventfd = eventfd(0,EFD_CLOEXEC);

void test(){
    uint64_t Temp = 0;
    ::read(Eventfd, &Temp, sizeof(Temp));
    while(Temp--){
        std::function<void()> fun = std::move(Event.front());
        Event.pop();
        fun();
    }
}

void show1(){
    std::cout << "hello world.\n";
}

void show2(int padding){
    std::cout << "padding = " << padding << std::endl;
}

int main(){
    uint64_t padding = 1;
    auto son = std::thread(test);
    Event.push(show1);
    int ParaInShow2 = 1024;
    Event.push(std::bind(show2, ParaInShow2)); //closure;

    ::write(Eventfd, &padding , sizeof padding);
    ::write(Eventfd, &padding , sizeof padding);

    son.join();
    return 0;
}