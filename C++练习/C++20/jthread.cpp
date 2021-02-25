#include <thread>
#include <iostream>
 
using namespace std::literals::chrono_literals;
 
void f(std::stop_token stop_token, int value)
{
    while (!stop_token.stop_requested()) {
        std::cout << value++ << " -> jthread" << std::endl;
        std::this_thread::sleep_for(200ms);
    }
    std::cout << std::endl;
}

void ff(int value){
    while (true) {
        std::cout << value++ << " -> thread"<< std::endl;
        std::this_thread::sleep_for(200ms);
    }
}
 
int main(){
    std::jthread thread1(f, 5); // prints 5 6 7 8... for approximately 3 seconds
    std::thread thread2(ff, 5);
    std::this_thread::sleep_for(3s);
    // The destructor of jthread calls request_stop() and join().
}
