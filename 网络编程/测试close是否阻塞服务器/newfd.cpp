#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#include<bits/stdc++.h>
using namespace std;
int main(){
    //int oldfd = open("test.cpp",O_WRONLY|O_APPEND);
    auto start = std::chrono::high_resolution_clock::now(); 

    int newfd = open("test.cpp",O_WRONLY|O_APPEND);
    for (size_t i = 0; i < 100000; i++){
        sleep(10);
    }
    
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::ratio<1,1000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,1000>>>(end - start);

    //close(oldfd);
    std::cout << time_span.count() << std::endl;
}