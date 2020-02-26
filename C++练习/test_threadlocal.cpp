#include<bits/stdc++.h>
using namespace std;
#include <unistd.h>

thread_local int* ptr;

class test{
public:
    int* TT;

    void exchange(){
        TT = ptr;
    }
};

void excute(int i, test& T){
    int a = i;
    ptr = &a;
    cout << "threadlocal : "<<*ptr << endl;
    T.exchange();
}

int main(){
    int number = 20;
    ptr = &number;
    test a;
    auto Thread = std::thread(&excute, 10, std::ref(a));
    sleep(1);
    cout << *a.TT << endl;
    Thread.join();
    return 0;
}