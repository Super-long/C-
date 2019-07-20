#ifndef QUEUETP_H_
#define QUEUETP_H_

#include<iostream>
#include<string>

template<typename T>
class QueueTp
{
    private:
        const int LEN=10;
        T *data;
        int top;
    public:
        QueueTp(){top=0,data=new T[LEN];}
        QueueTp(int t){top=0,data=new T[t];}
        ~QueueTp() {delete []data;}
        bool is_empty()const {return top==0;}
        bool is_full() const {return top==LEN;}
        int size(){return top;}
        bool push(T item);
        bool pop();
        T& front()const;
        T& rear()const;
};

#endif

template<typename T>
bool QueueTp<T>::push(T item)
{
    if(is_full())
    {
        std::cout <<"Stack has full!\n";
        return false;
    }else
    {
        for(int i=top;i>0;i--)
        {
            data[i]=data[i-1];
        }
        top++;
        data[0]=item;
        return true;
    }
}

template<typename T>
bool QueueTp<T>::pop()
{
    if(is_empty())
    {
        std::cout << "Stack has empty!\n";
    }else
    {
        top--;
        return true;
    }
}


template <typename T>
T &QueueTp<T>::front() const
{
	return data[top - 1];
}
 
template <typename T>
T &QueueTp<T>::rear() const
{
	return data[0];
}
