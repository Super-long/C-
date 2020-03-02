#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 
void *thread_proc(void *data)
{
    printf("a new thread creaded\n");
    while (1)
    {
        sleep(10);
    }
 
    return (void *)0;
}
 
int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_proc, NULL);
    pthread_join(tid, NULL);
    return 0;
}
