#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p128, *p1k, *p10k, *p100k, *p200k, *p1mb;

    p128 = (int*)malloc(128);
    printf("Address of malloc(128) is %p\n", p128);

    p1k = (int*)malloc(1024);
    printf("Address of malloc(1024) is %p\n", p1k);

    p10k = (int*)malloc(10*1024);
    printf("Address of malloc(10*1024) is %p\n", p10k);

    p100k = (int*)malloc(100*1024);
    printf("Address of malloc(100*1024) is %p\n", p100k);

    p200k = (int*)malloc(200*1024);
    printf("Address of malloc(200*1024) is %p\n", p200k);

    p1mb = (int*)malloc(1000*1024);
    printf("Address of malloc(1000*1024) is %p\n", p1mb);

    free(p128);
    free(p1k);
    free(p10k);
    free(p100k);
    free(p200k);
    free(p1mb);

    return 0;
}