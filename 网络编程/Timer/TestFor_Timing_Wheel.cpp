#include"Timing_Wheel.h"
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<errno.h> 
#include<fcntl.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<signal.h>
using namespace std;

TimerWheel TW;
int a[10] = {1,2,3,4,5,6,7,8,9};

void sig(int sig){
    printf("hello world\n");
    TW.TW_Tick();
    alarm(2);
}

int main(){
    signal(SIGALRM, sig);
    alarm(2);
    for(int i=0;i<10;++i){
        cout << a[i] << " have send\n";
        TW.TW_Add(a[i]);
        sleep(2);
    }
    return 0;
}
