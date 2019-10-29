#include<stdio.h>
int (*s[10]);
int a[10] = {1,2,3,4,4};

int main(){
    *s = 5;
    s[5] = 10;
    printf("%d", s[5]);
}