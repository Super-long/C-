#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<dirent.h>
#include<signal.h>

int count=1;

int main()
{
    if(fork()==0)
    {
        count--;
        exit(1);
    }else
    {
        wait(NULL);
        printf("%d\n",++count);
    }
    exit(1);
}