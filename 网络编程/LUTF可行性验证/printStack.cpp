#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int i, j, k = 0;
unsigned char *stack_buffer;
unsigned char *p;

void sig_start(int signo)
{
	unsigned long a = 0x1234567820000304;


	p = (unsigned char*)&a;
    printf("signo : %p; p : %p\n",&signo, &a);
	stack_buffer = (unsigned char *)&a;

	// 以下按照8字节为一组，打印堆栈的内容
	printf("----begin stack----\n");
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 8; j++) {
			printf(" %.2x", stack_buffer[k]);
			k++;
		}
		printf("\n");
	}
	printf("----end stack---- : %p\n");

	if (signo = SIGINT)
		signal(SIGINT, NULL);
	if (signo = SIGHUP)
		signal(SIGHUP, NULL);
	return;
}

int main()
{
	printf("process id is %d  %p %p\n",getpid(), main, sig_start);

	signal(SIGINT, sig_start);
	signal(SIGHUP, sig_start);
    unsigned long esp = 0x1234567820000304;
    printf("esp : %p\n", &esp);
    
	printf("esp : %p\n", &esp);
	for (;;);
}
