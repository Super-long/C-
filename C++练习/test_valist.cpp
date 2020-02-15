#include <bits/stdc++.h>
using namespace std;
#include<cstdarg>
#include<sys/socket.h>

char book[1000];

int SWrite(const char* format, va_list para){
    return vsnprintf(book, 1000, format, para);
}

int swrite(const char* format, ...){
    va_list va;
    va_start(va, format);
    int ret = SWrite(format, va);
    va_end(va);
    return ret;
}

int main(){
    swrite("book%s\n", "ok\n");
    cout << book << endl;
    return 0;
}