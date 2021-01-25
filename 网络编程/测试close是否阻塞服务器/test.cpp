#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>
#include <string.h>
#include <unistd.h>   
#include <stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<bits/stdc++.h>
using namespace std;
// aof.c 1676行描述到close/rename时可能出现阻塞；但就实验结果来看貌似并没有
// 可以使用lsof查看进程打开的文件

int main(){
    //int oldfd = open("test.cpp",O_WRONLY|O_APPEND);
    auto start = std::chrono::high_resolution_clock::now(); 

    for (size_t i = 0; i < 100000; i++){
        int newfd = open("test.cpp",O_WRONLY|O_APPEND);
    //sleep(1);
        close(newfd);
    }
    
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::ratio<1,1000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,1000>>>(end - start);

    //close(oldfd);
    std::cout << time_span.count() << std::endl;
}