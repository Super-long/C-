#include<iostream>
#include<string>
using namespace std;

template<typename T>
void swap(T tmpa,T tmpb){
    using std::swap;//去掉会冲突　不会造成无限递归
    cout << "hello woeld\n";
    swap(tmpa,tmpb);
}

namespace{//相当与全局静态变量　仅本文件可见
    string str;
    int bookone;
    int booktwo;
}

namespace NS{
    class Quote{
    };
    void display(const Quote&){cout << "linux\n";}
}

//私有继承与保护继承均不可以
class Bulk : public NS::Quote{
};

int main(){
    cin >> bookone;
    string s1 = "one";
    string s2 = "two";
    swap(s1,s2);//根据参数在std命名空间中先搜寻swap函数
    swap(1,2);//运行结果说明基础类型不在std命名空间中
    cout << s1 << endl;
    cout << "----------\n";
    NS::Quote *tmpa;
    Bulk book1;
    tmpa = &book1;
    display(book1);//私有继承和保护继承基类指针不能指向派生类
    cout << "-----------\n";
    cin >> str;
/*     operator>>(std::cin,booktwo);
    operator<<(cout,bookone); *///为什么不能这样写　好奇怪
    cout << bookone << endl;
    return 0;
}