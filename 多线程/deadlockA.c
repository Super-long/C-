#include <unistd.h> 
#include <pthread.h> 
#include <string.h> 
 
pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexC = PTHREAD_MUTEX_INITIALIZER; 

 
static int counterA = 0; 
static int counterB = 0; 
 
int func1() 
{ 
	pthread_mutex_lock(&mutexA); 
	++counterA; 
	sleep(1); 
	pthread_mutex_lock(&mutexB); 
	++counterB; 
	pthread_mutex_unlock(&mutexB); 
	pthread_mutex_unlock(&mutexA); 

	return counterA; 
} 

int func2() 
{ 
	pthread_mutex_lock(&mutexB); 
	++counterB; 
	sleep(1); 
	pthread_mutex_lock(&mutexA); 
	++counterA; 
	pthread_mutex_unlock(&mutexA); 
	pthread_mutex_unlock(&mutexB); 

	return counterB; 
} 
 
void* start_routine1(void* arg) 
{ 
	while (1) 
	{ 
		int iRetValue = func1(); 

		if (iRetValue == 100000) 
		{ 
			pthread_exit(NULL); 
		} 
	} 
} 

void* start_routine2(void* arg) 
{ 
	while (1) 
	{ 
		int iRetValue = func2(); 

		if (iRetValue == 100000) 
		{ 
			pthread_exit(NULL); 
		} 
	} 
} 

void* start_routine(void* arg) 
{ 
	while (1) 
	{ 
		sleep(1); 
		char szBuf[128]; 
		memset(szBuf, 0, sizeof(szBuf)); 
		strcpy(szBuf, (char*)arg); 
	} 
}

int main() 
{ 
	pthread_t tid[4]; 
	if (pthread_create(&tid[0], NULL, &start_routine1, NULL) != 0) 
	{ 
		_exit(1); 
	} 
	if (pthread_create(&tid[1], NULL, &start_routine2, NULL) != 0) 
	{ 
		_exit(1); 
	} 
	if (pthread_create(&tid[2], NULL, &start_routine, "thread3") != 0) 
	{ 
		_exit(1); 
	} 
	if (pthread_create(&tid[3], NULL, &start_routine, "thread3") != 0) 
	{ 
		_exit(1); 
	} 

	sleep(5); 
	//pthread_cancel(tid[0]); 

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 
	pthread_join(tid[2], NULL); 
	pthread_join(tid[3], NULL); 

	pthread_mutex_destroy(&mutexA); 
	pthread_mutex_destroy(&mutexB); 
	pthread_mutex_destroy(&mutexC); 


	return 0; 
}