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
int compare(const T &a,const T &b){
    cout << "one\n";
    if(a<b) return -1;
    if(b<a) return -1;
    return 0;
}

/* template<unsigned m,unsigned n> //指向数组的引用
int compare(const char (&p1)[m],const char (&p2)[n])
{
    cout << "two\n";
    return m+n;
} */

template<unsigned m,unsigned n>
int compare(const char (&p1)[m],const char (&p2)[n])
{
    return m;
}

template<unsigned m> constexpr  //常量模板 返回值及形参必须是常量
unsigned my_size(const char(&p1)[m])
{
    return m;
}
//问娄神
int main()
{
    string a("asd");
    string b("omomo");
    constexpr char aa[20]={"asdasd"};
    constexpr char bb[20]={"mkmkm"};
    char str[20]={"4545"};
    cout << my_size(str) << endl;
    cout << compare("hello","lololo") << endl;
    compare(aa,bb);
    return 0;
}