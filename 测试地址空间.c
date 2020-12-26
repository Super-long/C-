#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = 0;

    while (malloc(1*1024*1024*1024) != NULL) {
        count++;
    }
    printf("count is %f G\n", count / 1024.0f);

    //sleep(10000);

    return EXIT_SUCCESS;
}