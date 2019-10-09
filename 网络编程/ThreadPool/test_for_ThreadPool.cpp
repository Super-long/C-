#include"ThreadPool.h"
#include<iostream>
#include<unistd.h>
using namespace std;

int flag,tmp;
int main(){
    threadpool<int> Pool(5,20000);
    while(1){
        //有可能超过最大请求数
        tmp = ++flag;
        //Pool.append(&tmp);
        //加与不加while循环效率相差几十倍　可以测试下　奇怪
        while(!Pool.append(&tmp)){
            //cout << "重 11111111111111111111111111111111111111111复\n"; return 0;
        };//加while的原因是把超过最大请求的重新发送
        //sleep(2);
    }
    return 0;
}