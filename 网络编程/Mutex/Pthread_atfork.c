#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
//这个代码的作用是fork之后调节锁的资源 防止出现死锁
pthread_mutex_t mutex;

void *anther(void *arg){
    printf("in child pthread\n");
    pthread_mutex_lock(&mutex);
    sleep(5);
    pthread_mutex_unlock(&mutex);
}

void prepare(){
    pthread_mutex_lock(&mutex);
}

void infork(){
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_atfork(prepare,infork,infork); 
    //其实就是三个回调函数 在创建新线程之前锁住 fork以后再解开 使得子进程中锁资源可控
    //其实就是为了使得我们清楚锁的状态
    pthread_mutex_init(&mutex,NULL);
    pthread_t pid;
    pthread_create(&pid,NULL,anther,NULL);
    sleep(1); //保证线程可拿到mutex
    int id = fork();
    if(id < 0){
        pthread_mutex_destroy(&mutex);
        pthread_join(pid,NULL);
        return 0;
    }else if(id == 0){
        printf("in the child\n");
        pthread_mutex_lock(&mutex);//子进程会拷贝父进程锁的状态 且只拥有一个执行线程
        printf("running\n");
        pthread_mutex_unlock(&mutex);
        exit(0);
    }else{
        wait(NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_join(pid,NULL);
    return 0;
}