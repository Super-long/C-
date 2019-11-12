#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include"locker.h"
#include<list>
#include<cstdio>
#include<exception>
#include<pthread.h>
#include<iostream>

template<typename T>
void solve(const T &t){
    std::cout << "线程接收到消息: " << t << std::endl;
    return;
}

template<typename T>
class threadpool{
    enum{Max_Thread = 10,Max_Requests = 10000};
    public:
        explicit threadpool(int thread_number = Max_Thread,int max_requests = Max_Requests);
        ~threadpool();
        bool append(T* request);//向任务队列中添加任务
    private:
        static void* worker(void *arg);
        void run();
    private:
        int m_thread_number;//最大线程数
        int m_max_requests;//最大请求数
        pthread_t* m_threads; //描述线程的数组
        //unique_ptr<pthread_t[]>m_threads; //如果确定数组大小　就可以用unique_ptr管理内存
        std::list<T*> m_workqueue;//任务队列
        cond m_QueueState; //条件变量 类内初始化　
        bool m_stop;
        //直接类内默认初始化失败
};

template<typename T>
threadpool<T>::threadpool(int thread_number,int max_requests):
m_thread_number(thread_number),m_max_requests(max_requests),m_stop(false),m_threads(NULL),
m_QueueState(){//默认初始化
    if(thread_number<=0 || max_requests<=0){
        throw std::out_of_range("error in initialize");
    }
    m_threads = new pthread_t[m_thread_number];
    if(!m_threads){
        throw std::bad_alloc();
    }
    //typedef void* (*Temp)(void*);
    using Temp = void* (*)(void*);
    Temp enp = (Temp)&threadpool::run; 

    for(int i=0;i<m_thread_number;++i){
        if(pthread_create(&(m_threads[i]),nullptr,enp,this) != 0){
            //if(pthread_create(&(m_threads[i]),nullptr,worker,this) != 0){ //两种都可以
            delete []m_threads;
            throw std::exception();
        }
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

template<typename T>
bool threadpool<T>::append(T* requests){
    m_QueueState.lock();
    if(m_workqueue.size() >= m_max_requests){
        m_QueueState.unlock();
        return false;
    }
    m_workqueue.emplace_back(requests);
    m_QueueState.signal();
    m_QueueState.unlock();
    return true;
}

template<typename T> //这个函数本来为pthread_create的参数准备的　但有更好的解决方案 及强制类型转换
void* threadpool<T>::worker(void *arg){
    threadpool *pool = (threadpool*)arg;
    pool->run();
    return pool;  
}

template<typename T>
void threadpool<T>::run(){
    while(!m_stop){
        m_QueueState.lock();
        while(m_workqueue.empty()){
            m_QueueState.wait();
        }
        T* request = m_workqueue.front();
        m_workqueue.pop_front();
        m_QueueState.unlock();
        //这里就是线程得到这个参数后如何执行
        std::cout << pthread_self() << std::endl;
        solve(*request);//执行函数 
    }
}

#endif