#ifndef LOCKER_H_
#define LOCKER_H_   
#include<exception>
#include<pthread.h>
#include<semaphore.h>//信号量

class locker{
    public:
        locker(){
            if(pthread_mutex_init(&m_mutex,nullptr)!=0){
                throw std::exception();
            }
        }
        ~locker(){
            pthread_mutex_destroy(&m_mutex);
        }
        bool lock(){
            return pthread_mutex_lock(&m_mutex) == 0;
        }
        bool unlock(){
            return pthread_mutex_unlock(&m_mutex) == 0;
        }
    private:
        pthread_mutex_t m_mutex;
};

class cond{
    public:
        cond(){
            if(pthread_mutex_init(&m_mutex,nullptr) != 0){
                throw std::exception();
            }
            if(pthread_cond_init(&m_cond,nullptr) != 0){
                pthread_mutex_destroy(&m_mutex);
                throw std::exception();
            }
        }
        ~cond(){
            pthread_mutex_destroy(&m_mutex);
            pthread_cond_destroy(&m_cond);
        }
        bool signal(){
            return pthread_cond_signal(&m_cond) == 0;
        }
        bool wait(){
            int ret = pthread_cond_wait(&m_cond, &m_mutex);
            return ret == 0;
        }
        bool lock(){
            return pthread_mutex_lock(&m_mutex) == 0;
        }
        bool unlock(){
            return pthread_mutex_unlock(&m_mutex) == 0;
        }
    private:
        pthread_mutex_t m_mutex;
        pthread_cond_t m_cond;
};

#endif 