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

int main(){
    int FileName = 0;
    vector<int> arr;
    arr.reserve(500);

    constexpr int len = 1024*1024*1024;

    // 机器

    for (size_t i = 0; i < 10; i++){
        int fd = open(std::to_string(i).c_str(), O_RDWR | O_CREAT | O_DIRECT, 0755);
        arr.push_back(fd);
        char *buf;
        size_t buf_size = len;
        posix_memalign((void **)&buf, getpagesize(), buf_size);
        int ret = write(fd, buf, len);
        if(ret != len){
            std::cerr << "Partially written！\n";
        }
    }

    for(auto x : arr){
        close(x);
    }
    return  0;
}