#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *buff)
{
    sleep(1);
    char *buffer = (char *)buff;
    buffer[22] = 'a';
    return NULL;
}

int main()
{
    char *buffer = (char* )malloc(20);

    pthread_t th;
    pthread_create(&th, NULL, thread_func, buffer);
    pthread_join(th, NULL);

    return 0;
}