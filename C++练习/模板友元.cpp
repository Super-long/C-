#include<iostream>
#include<string>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

template <typename T>
class Pal
{
    friend T;  //这个东西有意思 假如T为自定义模板 没有将不能用T来使用类的保护和私有函数
    public:
        static size_t st;
        Pal() = default ;
        Pal(T &a):tmp(a) {}
        void show(){
            cout << tmp << endl;
        }
    private:
        T tmp;
};

class c
{
    friend class Pal<c>;//这个版本的实例化为c的友元
    template<typename T> friend class Pal; //所有实例化版本都是这个普通类的友元
};

template<typename T,typename U> using pr = pair<T,U>;

template<typename T> //模板静态成员的正确初始化方法
size_t Pal<T>::st = 10;

int main()
{
    Pal<int> t;
    cout << t.st << endl;
    pr<string,int> tmp;
    tmp = make_pair("hello",20);
    cout << tmp.second << endl;
    return 0;
}