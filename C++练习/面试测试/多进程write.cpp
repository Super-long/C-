#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>

int main(){
    pid_t pid;
    pid = fork();
    char* pathname = "test.txt"; 
    char* ChildProcess = "aaaaa\n";
    char* FatherProcess = "bbbbb\n";
    int fd = open(pathname, O_RDWR);
    switch (pid)
    {
        case 0:
            {
                printf("in the child\n");
                for(int i=0;i<1000000;++i){
                    write(fd, ChildProcess,6);
                }
                sleep(100);
                close(fd);
                break;
            }
        case -1:
            perror("error message\n");
            break;
        default:
            {
                printf("in the father\n");
                for(int i=0;i<1000000;++i){
                    write(fd, FatherProcess, 6);
                }
                close(fd);
                sleep(100);
                break;
            }
    }
    return 0;
}
