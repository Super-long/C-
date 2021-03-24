#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

int main(){ // direct IO
    vector<int> arr;
    arr.reserve(500);

    constexpr int len = 1024;

    for (size_t i = 0; i < 10; i++){
        int fd = open(std::to_string(i).c_str(), O_RDONLY | O_DIRECT, 0755);
        std::cout << fd << std::endl;
        arr.push_back(fd);
    }

    for (size_t i = 0; i < 1000; i++){
        int index = i%10;
        lseek(arr[index], 1024*1024*512, SEEK_SET); // 转移偏移量
        char* buf;
        posix_memalign((void**)&buf, getpagesize(), 1025);
        std::cout << arr[index] << std::endl;
        size_t buf_size = len;
        int ret = read(arr[index], buf, buf_size);
        if(ret != buf_size){
            free(buf);
            std::cout << errno << std::endl;
            std::cerr << "Partially written！\n";
            continue;
        }
        free(buf);
        //sync();
    }
    

    for(auto x : arr){
        close(x);
    }
    return  0;
}