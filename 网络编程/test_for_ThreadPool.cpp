#include"ThreadPool.h"
#include<iostream>
#include<unistd.h>
using namespace std;

int flag;
int main(){
    threadpool<int> Pool(50,20000);
    while(1){
        cout << "main_test : "<<flag << endl;
        Pool.append(&(++flag));
        sleep(2);
    }
    return 0;
}