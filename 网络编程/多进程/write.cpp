#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<chrono>
#include<time.h>
using namespace std;
using namespace chrono;

int main(){
    pid_t pid;
    pid = fork();
    char* pathname = "test.txt"; 
    char* ChildProcess = "aaaaa\n";
    char* FatherProcess = "bbbbb\n";

    switch (pid)
    {
        case 0://child process
            {
                printf("in the child\n");
                int fd = open(pathname, O_RDWR | O_APPEND);
                auto start = system_clock::now();
                for(int i=0;i<100000;++i){
                    write(fd, ChildProcess,6);
                }
                auto end = system_clock::now();
                printf("child : %d\n",end - start);
                close(fd);
                break;
            }
        case -1:
            perror("error message\n");
            break;
        default:
            {
                printf("in the father\n");
                int fd = open(pathname, O_RDWR | O_APPEND);
                auto start = system_clock::now();
                for(int i=0;i<100000;++i){
                    write(fd, FatherProcess, 6);
                }
                auto end = system_clock::now();
                printf("father : %d\n", end- start);
                close(fd);
                break;
            }
    }
    return 0;
}