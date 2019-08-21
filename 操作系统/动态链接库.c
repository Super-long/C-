#include<stdio.h>
//gcc -shared -fpic -o test_dy.so  动态链接库.c 
//csapp　４８６页
//.so为动态链接库的后缀
void foo(int * a)
{
    printf("这是动态链接库\n");
    return 0;
}