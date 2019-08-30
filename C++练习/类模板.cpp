#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

template<typename T>
class Blob{
    public:     //显示的告诉编译器作用域解析运算符解析的是类型名称(默认不是类型)
        typedef typename vector<T>::size_type size_type; //unsigned long
        Blob();
        Blob(initializer_list<T> il); //接收initializer_list参数
        size_type size() {return data->size();}

        template<typename U> //成员模板函数  //接收迭代器
        Blob(U a,U b):data(make_shared<vector<T>>(a,b)){}

        bool empty(){return data->empty();}
        void push_back(const T&t){data->push_back(t);}
        void push_back(T &&t) {data->push_back(std::move(t));} //移动版本
        void pop_back();
        T& back();
        T& operator[](size_type i);
    private:
        shared_ptr<vector<T>> data;
        void check(size_type i,const string &msg) const; //给定索引 检查是否越界
};

template<typename T>
void Blob<T>::check(size_type i,const string &msg)const
{
    if(i>=data->size())
    throw out_of_range(msg);//msg为抛出异常的的提示信息 使用what()成员函数返回
}

template<typename T>
T& Blob<T>::back()
{
    check(0,"back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(0,"out of range");
    return (*data)[i];  //傻了 智能指针解引用才是vecter对象
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0,"pop_back on empty range");
    return data->pop_back();
}

template<typename T>
Blob<T>::Blob():data(make_shared<vector<T>>()){} //默认构造函数

template<typename T>
Blob<T>::Blob(initializer_list<T> il):
data(make_shared<vector<T>>(std::move(il))){} //这样转成右值效率感觉会更高



template<typename T>
class Blobptr
{
    friend class Blobptr<T>;//一对一的友元关系
    public:
        Blobptr():curr(0){}
        Blobptr(Blob<T> bl,size_t sz = 0):
            wptr(bl.data),curr(sz){}
        T& operator*() const{
            auto p = check(curr,"error in *");
            return (*p)[curr];
        }
        Blobptr& operator++();
        Blobptr& operator--();  //类内不需要实例化

    private:
        shared_ptr<vector<T>> 
            check(size_t ,const string&) const;
        weak_ptr<vector<T>> wptr;
        size_t curr; //数组中当前位置
};

template<typename T>
Blobptr<T>& Blobptr<T>::operator++()
{
    Blobptr ret = *this;
    ++*this; //这个为什么可以跑， 没有重载呀，
    return ret;
}

template<typename T>
Blobptr<T>& Blobptr<T>::operator--()
{
    Blobptr ret = *this;
    --*this;
    return ret;
}

int main()
{
    vector<int> vec={1,2,3,4};
    Blob<int> bl(vec.begin(),vec.end());
    bl.push_back(10);
    cout << bl[2] << endl;
}