#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *buffer = (char*)malloc(20);
    printf("-------------------------------------%p\n", &(buffer[20]));
    int a = 10;
    printf("-------------------------------------%p\n", &a);
    buffer[20] = ' ';


    return 0;
}