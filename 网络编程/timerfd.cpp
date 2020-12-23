#include <stdio.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <time.h>
#include <sys/timerfd.h>
#include <unistd.h>
 
static void epollAddEvent(int epollFd, int addFd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = addFd;
	epoll_ctl(epollFd, EPOLL_CTL_ADD, addFd, &ev);
	return;
}
 
static int calcProcessTime(int *pStartMs)
{
	struct timespec endTime;
	clock_gettime(CLOCK_REALTIME, &endTime);
	if(pStartMs){
		return endTime.tv_sec * 1000 + endTime.tv_nsec / 1000000 - *pStartMs;
	}
	return endTime.tv_sec * 1000 + endTime.tv_nsec / 1000000;
}
 

            int SetTimer(int timeFd, long intervalNanoseconds = 1000000000l, long firstNanoseconds = 2000000000l){
                struct itimerspec its;

                constexpr int base = 1000000000;

                its.it_interval.tv_sec = intervalNanoseconds / base;     // 后面触发的间隔时间
                its.it_interval.tv_nsec = intervalNanoseconds % base;
                its.it_value.tv_sec = firstNanoseconds / base;// 首次超时时间
                its.it_value.tv_nsec = firstNanoseconds % base;
                // https://linux.die.net/man/2/timerfd_settime
                if (::timerfd_settime(timeFd, 0, &its, nullptr) < 0)
                    return -1;
                return 0;   // timerfd_settime成功时返回0，等于-1的时候失败；
            }

int  FD = 0;
void* thread_work(void* user)
{
	int epollFd = *(int*)user;
	struct epoll_event events[1] = {0};
	int cnt = 0;
    SetTimer(FD);
	while(1)
	{
		int ms = 0;
		ms = calcProcessTime(NULL);
		int fireEvents = epoll_wait(epollFd, events, 1, -1);
		ms = calcProcessTime(&ms);
		if(fireEvents > 0){
			printf("time out: %d ms\n", ms);
			uint64_t exp;
			ssize_t size = read(events[0].data.fd, &exp, sizeof(uint64_t));
			if(size != sizeof(uint64_t)) {
				printf("read error!\n");
			}
            //timer_update(events[0].data.fd, 3000);
		}
		else{
			printf("fireEvents = %d", fireEvents);
		}
	}
}
 
int main()
{
	/* create epoll */
	int epollFd = -1;
	epollFd = epoll_create(1);
 
	/* create timer */
	int timeFd = -1;
	timeFd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	
	/* add timer fd to epoll monitor event */
	epollAddEvent(epollFd, timeFd, EPOLLIN);
    FD = timeFd;
 
	/* create thread to monitor */
	pthread_t threadId = -1;
	pthread_create(&threadId, NULL, &thread_work, (void*)&epollFd);
	while(1){
		usleep(1000000);
	}
 
	return 0;
}