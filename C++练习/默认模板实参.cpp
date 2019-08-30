#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

template<typename T,typename F = less<T>>
int compare(T &a,T &b,F f=F()) //F是函数指针 F() 是函数
{
    if(f(a,b)) return -1; //a小于b
    if(f(b,a)) return 1;
    return 0;
}

class pla
{
    public:
        int a;
        pla() = default;
        pla(int tmp):a(tmp){}
};

bool tmp(const pla&a,const pla&b)
{
    return a.a<b.a;
}

template<class a>
void mm(a &&tmp)
{
    cout << tmp << endl;
}

template<typename T>
void judge(T &a) //只适用于顺序容器
{
    typedef typename T::size_type size_type;
    for(size_type i=0;i<a.size();i++)
    {
        cout << a[i]<< endl;
    }
}

int main()
{
    int tmpa=10;
    int tmpb=20;
    cout << compare(tmpa,tmpb) << endl;
    pla b(5);
    pla a(10);
    cout << compare(a,b,tmp) << endl;
    mm(5);
    vector<int>vec={1,2,3,4,5};
    judge(vec);
    return 0;
}