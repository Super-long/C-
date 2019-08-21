#include"A.c"
#include<stdio.h>
void f(void);

int x;
//A B 为测试强弱符号
int main()
{
    f();
    printf("0x%x\n",x);
}