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

int main(void)
{
    int sem_id = semget(500000,1,IPC_CREAT); //想要正确使用在拿到已设置好的信号量后就不要再设置了
    //设置后出现问题的原因在于那边跑到input时semval是0 这边设置成1导致两边交互加减1 然后信号量就没有什么作用了
    printf("%d\n",sem_id);
    int shmid;
    char *shmptr;
    // 创建或打开内存共享区域
    if((shmid=shmget(MYKEY,BUF_SIZE,IPC_CREAT))==-1){
        printf("shmget error!\n");
        exit(1);
    }
    if((shmptr=shmat(shmid,NULL,0))==(void*)-1){
        fprintf(stderr,"shmat error!\n");
        exit(1);
    }
    while(1){
        // 每隔 3 秒从共享内存中取一次数据并打印到控制台
        pv(sem_id,-1);
        printf("string:%s\n",shmptr);
        sleep(3);
        pv(sem_id,1);
    }
    exit(0);
}