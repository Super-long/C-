#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

//信号量等于1不就是互斥锁吗　本质上是一个计数器
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short* array;
    struct seminfo* __buf;
};

void pv(int sem_id,int op){
    struct sembuf sem_b;
    sem_b.sem_num = 0; //所以我为什么不直接设置为1
    sem_b.sem_flg = SEM_UNDO;
    sem_b.sem_op = op;
    semop(sem_id,&sem_b,1);
}

int main(int argc,char **argv){
    int sem_id = semget(IPC_PRIVATE,1,0666);
    union semun sem_un;
    sem_un.val = 1;
    //第二个参数为信号量在信号集中的编号　0表示第一个
    semctl(sem_id,0,SETVAL,sem_un);//原子操作

    pid_t id = fork();
    if(id < 0){
        return 1;
    }else if(id == 0){
        printf("child process is running\n");
        pv(sem_id,-1);//p操作
        printf("child\n");
        sleep(5);
        pv(sem_id,1);//v操作
        exit(0);
    }else{
        printf("parent process is running\n");
        pv(sem_id,-1);//p操作
        printf("parent\n");
        sleep(5);
        pv(sem_id,1);//v操作
    }
    waitpid(id,nullptr,0);
    semctl(sem_id,0,IPC_RMID,sem_un);
    //这时会唤醒等待队列上的所有进程　并设置errno为EIDRM 且semop会返回错误
    return 0;
}