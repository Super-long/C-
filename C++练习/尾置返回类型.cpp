#include<iostream>
#include<vector>
#include<type_traits>
using namespace std;

template<typename T>
int compare(T a,T b)
{
    cout << "hello\n";
}

template<typename a,typename b,typename c>
a sum(b tmpb,c tmpc){
    cout << "hello\n";
    return tmpc+tmpb;
}

//type是一个类型成员　使用typename来声明作用域解析运算符使用的类型而不是值
template<typename T>
auto fcn(T beg ,T end) ->                
    typename remove_reference<decltype(*beg)>::type//尾置返回类型
    {
        return *beg;
    }

int a=5;
int *g=&a;
//返回一个右值
decltype(a)* ok() //decltype参数为右值返回为值　左值为引用
{               //可能decltype对加指针时有特殊处理
    return &a;
}

//模板重载
template<typename T>
void f(T&&){
    cout << "one\n";
}

template<typename T>
void f(const T&){
    cout << "two\n";
}

template<typename T>
void gd(T && val){ //当你下一次看时再仔细想一遍
    vector<typename remove_reference<decltype(val)>::type> vec;
    vec.push_back(val);   //此时T的类型被推断为int& 
}

int main()
{
    char c='a';
    compare(c,'a');
    sum<long long,int,int>(5,6);
    //int &b = okk(); //右值不能赋予引用　因为相当于亡值
    int *b=ok();
//    int *c=okk();
    cout << a << endl;  //10
    cout << "start\n";
    int aa=10;
    gd(10);
    f(5);
    f(aa);
    //这里其实比较玄学　书上说的是左值会执行one　但左值实际执行two
    return 0;
}