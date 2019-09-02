#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

/* template<unsigned m,unsigned n>
int compare(const char (&p1)[m],const char (&p2)[n])
{
    return m+n;
}
 */

struct node{
    int ll;
    int ff;
    bool operator<(node &tmp)
    {
        return ll < tmp.ll;
    }
};

template<class T>
int compare(const T &a,const T &b){ //保证值是一个常量 顶层const
    cout << "one\n";
    if(a<b) return -1;
    if(b<a) return -1;
    return 0;
}

int compare(node &a,node &b) //显示实例化优先级高于模板
{
    cout << "four\n";
    return 0;
}

template<unsigned m,unsigned n>
int compare(const char (&p1)[m],const char (&p2)[n])//指明是数组    
{
    cout << "two\n";
    return m+n;
}

/* int fun(char aa[],char bb[]) //指明是指针
{
    compare(aa,bb);
} */
//template//实例化声明
int compare(char *const aa,char *const bb)//加上const与初始模板产生二义性
{//底层const
    cout << "three\n";
}


template<unsigned m> constexpr  //常量模板 返回值及形参必须是常量
unsigned my_size(const char(&p1)[m])
{
    return m;
}

int main()
{
    string a("asd");
    string b("omomo");
    char str[20]={"4545"};
    cout << my_size(str) << endl;
    char aa[20]={"asdasd"};
    char bb[20]={"mkmkm"};
    cout << compare("hello","lololo") << endl;
    compare(aa,bb); //这样默认传入的是指针 会产生二义性
    //fun(aa,bb);

    node aaa,bbb;
    compare(aaa,bbb);

    vector<node> vec;
    vec.push_back(aaa);
    sort(vec.begin(),vec.end());
    return 0;
}