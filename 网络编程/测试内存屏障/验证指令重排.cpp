//#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <atomic>
 
sem_t beginSema1;
sem_t beginSema2;
sem_t endSema;
 
int X,Y;
int r1,r2;
 
void* thread1Func(void* param) {
	while (1) {
		sem_wait(&beginSema1);
		while ( (rand() / (double)RAND_MAX) > 0.2 ) ;
		X=1;
		__asm__ __volatile__("":::"memory");
        //std::atomic_thread_fence(std::memory_order_acq_rel);
		r1 = Y;
		sem_post(&endSema);
	}
	return NULL;
}
 
void* thread2Func(void* param) {
	while (1) {
		sem_wait(&beginSema2);
		while ( (rand() / (double)RAND_MAX) > 0.2 ) ;
		Y=1;
		__asm__ __volatile__("":::"memory");
        //std::atomic_thread_fence(std::memory_order_acq_rel);
		r2 = X;
		sem_post(&endSema);
	}
	return NULL;
}
 
 
int main() {
	sem_init(&beginSema1,0,0);
	sem_init(&beginSema2,0,0);
	sem_init(&endSema,0,0);
 
	pthread_t thread1,thread2;
 
	pthread_create(&thread1,NULL,thread1Func,NULL);
	pthread_create(&thread2,NULL,thread2Func,NULL);
 
	int detected = 0;
	int iterations = 0;
	for (iterations=1;;iterations++) {
		X=0;
		Y=0;
		sem_post(&beginSema1);
		sem_post(&beginSema2);
		sem_wait(&endSema);
		sem_wait(&endSema);
		if (r1 == 0 && r2 == 0) {
			detected++;
			printf("%d reorders detected after %d iterations\n", detected, iterations);
		}
	}
	return 0;
}