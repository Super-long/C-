#include<stdio.h>

int main(){
    printf("hello world %d\n", getpid());
    sleep(15);
    printf("hello world\n");
    return 0;
}