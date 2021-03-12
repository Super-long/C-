#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int* p = nullptr;

void thread_A(){
    int A = 10;
    printf("thread_A : %p.\n", &A);
    sleep(1);
    int* tempA = p;
    cout << *tempA << endl;
    sleep(100);
}

void thread_B(){
    int B = 100;
    p = &B;
    printf("thread_B : %p.\n", &B);
    sleep(100);
}

int main(){
    auto A = thread(thread_A);
    auto B = thread(thread_B);
    A.join();
    B.join();
    return 0;
}