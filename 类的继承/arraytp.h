//利用模板参数来提供数组长度 可以不使用动态数组

#ifndef ARRAYTP_H_
#define ARRAYTP_H_

#include<iostream>
#include<cstdlib>

template<class T,int n>
class Arraytp
{
    private:
        T ar[n];
    public:
        Arraytp() {};
        explicit Arraytp(const T &);
        virtual T & operator[](int i);
        virtual T operator[](int i)const;
};

template<class T,int n>
Arraytp<T,n>::Arraytp(const T & v)
{
    for(int i=0;i<n;i++)
    ar[i]=v;
}

template<class T,int n>
T & Arraytp<T,n>::operator[](int i)
{
    if(i<0 || i>n)
    {
    std::cout << "超过数组范围!\n";
    std::exit(EXIT_FAILURE);
    }else
    {
        return ar[i];
    }
}

template<class T,int n>
T Arraytp<T,n>::operator[](int i) const
{
    if(i<0 || i>n)
    {
    std::cout << "超过数组范围!\n";
    std::exit(EXIT_FAILURE);
    }else
    {
        return ar[i];
    }
}

#endif