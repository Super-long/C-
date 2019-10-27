//注意sudo执行　这是一个很重要的细节 
//ps:这两个代码嫌麻烦都没释放资源，，，
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<errno.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<unistd.h>

#define BUF_SIZE 1024
#define MYKEY 25
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short* array;
    struct seminfo* __buf;
};

void pv(int sem_id,int op){
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_flg = SEM_UNDO;
    sem_b.sem_op = op;
    semop(sem_id,&sem_b,1);
}
//共享内存最大的问题是在不同进程间会遇到竞态条件　需要信号量来加锁　
int main(void)
{
    int sem_id = semget(500000,1,IPC_CREAT);
    printf("%d %d\n",sem_id,errno);
    union semun sem_un;
    sem_un.val = 1;
    semctl(sem_id,0,SETVAL,sem_un);
    int shmid;
    char *shmptr;
    if((shmid=shmget(MYKEY,BUF_SIZE,IPC_CREAT))==-1){
        printf("shmget error!\n");
        exit(1);
    }
    if((shmptr=shmat(shmid,NULL,0))==(void*)-1){
        printf("shmat error!\n");//sudo执行　会有权限问题
        printf("%d\n",errno);//13
        exit(1);
    }
    while(1){
        pv(sem_id,-1);
        // 把用户的输入存到共享内存区域中
        printf("input:");
        scanf("%s",shmptr);
        pv(sem_id,1);
    }
    exit(0);
}