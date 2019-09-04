//可变模板参数　相比于　初始化列表　的好处就是其中的元素可以不是一个类型
//这就很强大了

#include<memory>
#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

template<typename ... Args>
void g(Args ... args){
    cout << sizeof...(Args) << endl;
    return;
}

template<typename T> //非可变参数版本　防止循环递归
ostream& print(ostream &os,T& t){
    os << t << endl;
}

template<typename T,typename ... Args> //这样的参数就可以接收右值且不需要拷贝
ostream& print(ostream & os ,T &t,const Args& ... args){
    os << t << endl;
    return print(os,args...);
}

int main()
{
    int a = 5;
    g(1);
    g(1,2);
    g(1,2,3);
    print(cout,a,4,5,6,7,8);
    return 0;
}