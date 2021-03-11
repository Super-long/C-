#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(){
    pid_t pid;
    pid = fork();
    char* pathname = "test.txt"; 
    char ChildProcess[13] = "aaaaaaaaaaa\n";
    char FatherProcess[7] = "bbbbb\n";

    switch (pid)
    {
        case 0:
            {
                printf("in the child\n");
                FILE* fl = fopen(pathname, "a+");
                for(int i=0;i<100000;++i){
                    fwrite(ChildProcess, 12,1,fl);
                }
                fclose(fl);
                break;
            }
        case -1:
            perror("error message\n");
            break;
        default:
            {
                printf("in the father\n");
                FILE* fl = fopen(pathname, "a+");
                for(int i=0;i<100000;++i){
                    fwrite(FatherProcess, 6,1,fl);
                }
                fclose(fl);
                break;
            }
    }
    return 0;
}
