//一个简单的pair类 可以去修改其中的两个元素
//代码中的例子也说明使用多个类型参数的模板也可以成为数组 初始化需要注意！！
#include<iostream>
#include<string>
template<class T1,class T2>
class pair
{
    private:    
        T1 a;
        T2 b;
    public:
        T1 & first(); //用于修改a和b的值
        T2 & second();
        T1 first() const {return a;}
        T2 second() const {return b;}
        pair(const T1 & aval,const T2 & bval) :a(aval),b(bval) {}
        pair() {}
};

template<class T1,class T2>
T1 & pair<T1,T2>::first()
{
    return a;
}

template<class T1,class T2>
T2 & pair<T1,T2>::second()
{
    return b;
}

int main()
{
    using std::cout;
    using std::string;
    using std::endl;
    pair<string,int> rate[4]{
        pair<string,int>("li",5),
        pair<string,int>("zhao",5),
        pair<string,int>("long",5),
        pair<string,int>("a",5),//仅仅是为了调用构造函数
    };

    pair<int,int> tmp(10,10);//test

    for(int i=0;i<4;i++)
    {
        cout << rate[i].first() << endl;
        cout << rate[i].second() << endl;
    }

    rate[3].first()="hello world";
    rate[3].second()=5;
    cout << rate[3].first() << endl;
    cout << rate[3].second() << endl;
    return 0;
}