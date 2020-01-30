#include <bits/stdc++.h>
using namespace std;
#include "interrupt_thread.h"

void test(){
    cout << "hello\n";
}

int main(){
    interrupt_thread run(test);
    run.join();
    getchar();
    return 0;
}