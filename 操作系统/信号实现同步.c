//在这个程序中其实看到了信号与锁一样都是实现同步的几种方法之一　

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<errno.h>
#include<signal.h>

volatile sig_atomic_t pid; //保证信号处理函数中对全局变量的读写是有效的
//volatile　保证每次从都从内存中读取
//sig_atomic_t 保证读写操作均为原子操作　也就是说不需要暂时屏蔽触发信号处理函数的信号　防止数据同时间被多次修改

void chld_handler(int signo)
{
    int old = errno; //在信号处理函数中有可能会修改全局变量errno　从而影响外面的函数 
    pid=waitpid(-1,NULL,0);
    errno = old;
} //防止子进程成为僵尸进程

void int_handler(int signo)
{
    //在简单shell的实现中　这个函数中需要进行输出
    //注意只能使用异步安全的函数　printf strlen都不是
    //参考另外一篇博客　
}

int main(int argc ,char **argv)
{
    sigset_t mask,prev; //型号集

    signal(SIGCHLD,chld_handler);
    signal(SIGINT,int_handler);

    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);//将信号加入屏蔽集

    sigprocmask(SIG_BLOCK,&mask,&prev); //把当前屏蔽集设置为参数一二的并集
    //防止在fock之后　信号处理函数之前信号到达　那样程序就会永远阻塞
    while(1){
        if(fock()==0)
        {
            printf("子进程处理shell请求\n");
            exit(1);
        }
        pid=0;
        while(!pid)
            sigsuspend(&prev);

        sigprocmask(SIG_SETMASK,&prev,NULL);//恢复信号屏蔽字
    }
    return 0;
}