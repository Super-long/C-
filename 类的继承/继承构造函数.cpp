#include<memory>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;


struct A{
    int a=5;
    int b=6;
/*     A() {
        a=5;
        b=6;
    } */
    A() = default;
    A(const A&) = default;
};

struct B : A{
    using A::A;
/*     B(int x,int y) //参数相同会覆盖基类
    {
        this->a=x;
        this->b=y;
    }*/
    int show(){
        cout << this->a << endl;
        cout << "C: " << c << endl;
    }
    int c=52;
};

int main()
{
/*     B tmp(7,8);
    tmp.show();
    B tep(tmp);
    tep.show(); */
    B tmp;
    B tep(tmp);
    tep.show(); //只有继承的构造函数 也会合成一个默认的构造函数
}