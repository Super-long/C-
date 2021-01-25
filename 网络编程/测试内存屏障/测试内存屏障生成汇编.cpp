#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <atomic>

#if __GNUC__ < 4 

static inline void barrier(void) {__asm__ volatile("":::"memory");}

#else

static inline void barrier(void) {__sync_synchronize();}

#endif

std::atomic<int> count;
int flag;

int test_w_1(){
    count.store(10, std::memory_order_seq_cst);

    return flag;
}

void test_r_1(){
    flag = count.load(std::memory_order_seq_cst);
}

int main(){
    int a = 5;
    __asm__ volatile("mfence":::"memory");
    return 0;
}