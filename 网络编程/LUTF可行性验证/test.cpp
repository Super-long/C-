#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// 仅仅是测试demo，分配4096字节的stack足够了。
#define STACK_SIZE		4096
/* 
 * 为什么是72？
 * 因为我们在信号处理中增加了一个局部变量，这样pretcode的偏移就是32字节了。
 * 于是32+40=72！
 */
#define CONTEXT_OFFSET	72
// rip寄存器相对于局部变量a的偏移。注意rip在sigcontext中的偏移是16
#define PC_OFFSET		200

int wait_start()
{
	for (;;) {
		sleep(1000);
	}
}

// 线程1的处理函数
void thread1()
{
	int a = 1, ret = 0;
	char buf[64];
	int fd = open("./file", O_RDWR);
	for (;;) {
		// 线程1持续往一个文件里写内容。
		snprintf(buf, 32, "user thread 1 stack: %p  value:%d\n", &a, a++);
		ret = write(fd, buf, 32);
		printf("write buffer to file:%s  size=%d\n", buf, ret);
		sleep(1);
	}
}

// 线程2的处理函数
void thread2()
{
	int a = 2;
	for (;;) {
		// 线程2随便打印些自己栈上的什么东西。
		printf("tcp user cong 2 stack: %p  value:%d\n", &a, a++);
		sleep(1);
	}
}

unsigned char *buf;
int start = 0;
struct sigcontext context[2];
struct sigcontext *curr_con;
unsigned long pc[2];
int idx = 0;
unsigned char *stack1, *stack2;

// SIGINT用来启动所有线程，每次信号启动一个。
void sig_start(int dunno)
{
	unsigned long a = 0, *p;
	if (start == 0) {  // 启动第一个线程
		// 首先定位到sigcontext的rip，启动线程仅仅修改rip即可，目标是跳入到thread1线程处理函数
		p = (unsigned long*)((unsigned char *)&a + PC_OFFSET);
		*p = pc[0];
		// 定位到sigcontext
		p = (unsigned long *)((unsigned char *)&a + CONTEXT_OFFSET);
		curr_con = (struct sigcontext *)p;
		// 初始化其堆栈寄存器为为该线程分配的独立堆栈空间。
		curr_con->rsp = curr_con->rbp = (unsigned long)((unsigned char *)stack1 + STACK_SIZE);
		start++;
	} else if (start == 1) { // 启动第二个线程
		// 定位线程1的sigcontext，保存其上下文，因为马上就要schedule线程2了。
		p = (unsigned long *)((unsigned char *)&a + CONTEXT_OFFSET);
		curr_con = (struct sigcontext *)p;
		memcpy((void *)&context[0], (const void *)curr_con, sizeof(struct sigcontext));

		// 保存第一个线程的上下文后再定位到sigcontext的rip并修改之，同线程1
		p = (unsigned long *)((char*)&a + PC_OFFSET);
		idx = 1;
		*p = pc[1];
		p = (unsigned long *)((unsigned char *)&a + CONTEXT_OFFSET);
		curr_con = (struct sigcontext *)p;
		// 初始化其堆栈寄存器为为该线程分配的独立堆栈空间。
		curr_con->rsp = curr_con->rbp = (unsigned long)((unsigned char *)stack2 + STACK_SIZE);
		start++;
		// 两个线程均启动完毕，开启时间片轮转调度吧。
		alarm(2);
		signal(SIGINT, NULL);
	}

	return;
}

void sig_schedule(int unused)
{
	unsigned long a = 0;
	unsigned char *p;
	
	// 保存当前线程的上下文
	p = (unsigned char *)((unsigned char *)&a + CONTEXT_OFFSET);
	curr_con = (struct sigcontext *)p;
	memcpy((void *)&context[idx%2], curr_con, sizeof(struct sigcontext));
	
	// 轮转调度下一个线程，恢复其上下文。
	idx++;
	memcpy(curr_con, (void *)&context[idx%2], sizeof(struct sigcontext));

	// 2秒后再调度
	alarm(2);

	return;
}

int main()
{
	printf("process id is %d  %p %p\n",getpid(), thread1, thread2);
	
	// 为两个线程分配stack空间。
	// 注意，线程的stack空间一定要独立，不然函数调用会冲突的。
	stack1 = (unsigned char *)calloc(1, 4096);
	stack2 = (unsigned char *)calloc(1, 4096);
	signal(SIGINT, sig_start);
	signal(SIGALRM, sig_schedule);
	pc[0] = (unsigned long)thread1;
	pc[1] = (unsigned long)thread2;

	wait_start();
}
