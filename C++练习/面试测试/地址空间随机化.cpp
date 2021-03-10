#include <stdio.h>

void func();

int uninitialGlobalVar;
int globalVar = 1;

int main(void)
{
    int localVar = 1;

    printf("Address of func() is             %p, in text setment\n", func);
    printf("Address of uninitialGlobalVar is %p, in bss segment\n", &uninitialGlobalVar);
    printf("Address of globalVar is          %p, in data segment\n", &globalVar);
    printf("Address of localVar is           %p, in stack\n", &localVar);

    return 0;
}

void func()
{
    ;
}