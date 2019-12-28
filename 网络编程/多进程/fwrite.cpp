#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>
#include<chrono>
#include<stdlib.h>
using namespace std;
using namespace chrono;

std::time_t getTimeStamp()
{
    auto start = system_clock::now();
    //do something
    auto end = system_clock::now();
    auto duration = std::chrono::duration_cast<microseconds>(end - start);
    return double(duration.count()) * microseconds::period::num / microseconds::period::den;
}

int main(){
    pid_t pid;
    pid = fork();
    char* pathname = "test.txt"; 
    char ChildProcess[7] = "aaaaa\n";
    char FatherProcess[7] = "bbbbb\n";

    switch (pid)
    {
        case 0:
            {
                printf("in the child\n");
                FILE* fl = fopen(pathname, "rt+");
                auto start = system_clock::now();
                for(int i=0;i<100000;++i){
                    auto now = system_clock::now();
                    fwrite(ChildProcess, 6,1,fl);
                }
                auto end = system_clock::now();
                fclose(fl);
                printf("child : %d\n", end - start);
                break;
            }
        case -1:
            perror("error message\n");
            break;
        default:
            {
                printf("in the father\n");
                FILE* fl = fopen(pathname, "rt+");
                auto start = system_clock::now();
                for(int i=0;i<100000;++i){
                    int a = fwrite(FatherProcess, 6,1,fl);
                }
                auto end = system_clock::now();
                printf("parent : %d\n",end - start);
                fclose(fl);
                break;
            }
    }
    return 0;
}