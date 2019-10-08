#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include"locker.h"
#include<list>
#include<cstdio>
#include<exception>
#include<pthread.h>
#include<iostream>

template<typename T>
void solve(const T &){
    //std::cout << T << std::endl;
    std::cout << "线程接收到消息\n" << std::endl;
    return;
}

template<typename T>
class threadpool{
    public:
        explicit threadpool(int thread_number = 10,int max_requests = 10000);
        ~threadpool();
        bool append(T* request);//向任务队列中添加任务
    private:
        static void* worker(void *arg);
        void run();
    private:
        int m_thread_number;//最大线程数
        int m_max_requests;//最大请求数
        pthread_t* m_threads; //描述线程的数组
        std::list<T*> m_workqueue;//任务队列
        locker m_queuelocker;//锁
        cond m_QueueState; //条件变量 类内初始化　
        bool m_stop;
        //直接类内默认初始化失败
};

template<typename T>
threadpool<T>::threadpool(int thread_number,int max_requests):
m_thread_number(thread_number),m_max_requests(max_requests),m_stop(false),m_threads(NULL),
m_queuelocker(),m_QueueState(){
    using std::cout;
    if(thread_number<=0 || max_requests<=0){
        throw std::exception();
    }
    m_threads = new pthread_t[m_thread_number];
    if(!m_threads){
        cout << "okokoko\n";
        throw std::bad_alloc();
    }
    typedef void* (*Temp)(void*);
    Temp enp = (Temp)&threadpool::run;

    for(int i=0;i<m_thread_number;++i){
        if(pthread_create(&(m_threads[i]),nullptr,enp,this) != 0){
            //if(pthread_create(&(m_threads[i]),nullptr,worker,this) != 0){
            delete []m_threads;
            throw std::exception(); //一会自定义一个错误类型　查错时更方便
        }
        std::cout << "创建一个线程　pid : " << m_threads[i] << std::endl;
        if(int ret = pthread_detach(m_threads[i])){
            delete []m_threads;
            throw std::exception();
        }
    }
}

template<typename T>
threadpool<T>::~threadpool(){
    delete []m_threads;
    m_stop = true;
}

//工作队列被所有线程共享　需要加锁保护
template<typename T>
bool threadpool<T>::append(T* requests){
    m_queuelocker.lock();
    if(m_workqueue.size() >= m_max_requests){
        m_queuelocker.unlock();
        //throw std::__throw_out_of_range();
        return false;
    }
    m_workqueue.emplace_back(requests);
    m_QueueState.signal(); //任务队列准备就绪
    m_queuelocker.unlock();
    return true;
}

//这个函数的写法值得考虑
template<typename T>
void* threadpool<T>::worker(void *arg){
    threadpool *pool = (threadpool*)arg;
    pool->run();
    return pool;  
}

template<typename T>
void threadpool<T>::run(){
    while(!m_stop){ //这里也很巧妙　可以等下试试不这样会发生什么
        m_QueueState.lock();
        while(m_workqueue.empty()){ //改了一句好了 好好分析
            m_QueueState.wait();
        }
        T* request = m_workqueue.front();
        m_workqueue.pop_front();
        m_QueueState.unlock();
        if(!request) continue;
        //这里就是线程得到这个参数后如何执行
        solve(*request);
    }
}

#endif