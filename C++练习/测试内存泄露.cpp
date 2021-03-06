#include <thread>
#include <iostream>
#include <unistd.h>
int a = 10;
int b = 20;

int main(){
    int c = 30;
    printf("%d %p %p %p\n", getpid(), &a, &b, &c);
    while(true) {
        sleep(10);
    }
}
