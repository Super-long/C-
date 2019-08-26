#include<memory>
#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

class Foo
{
    public:
        Foo sorted() &&;
        Foo sorted() const &;
    private:
        vector<int>vec={4,6,2,3,1,9,7};
};
/* 
Foo Foo::sorted() const &
{
    return Foo(*this).sorted();//默认构造函数自动生成
} */ 
//其实两种方法均有两次拷贝　注释掉的方法还多了一次函数调用　但看起来确实很巧妙

Foo Foo::sorted() const &//因为是一个左值　所以不能在原址上操作　需要拷贝一个对象
{
    Foo ret(*this);
    sort(ret.vec.begin(),ret.vec.end());
    return ret;
}

Foo Foo::sorted() &&
{
    cout << "yidong\n";
    sort(vec.begin(),vec.end());
    return *this;
}

int main()
{
    Foo tmp;
    Foo temp = tmp.sorted();
}