#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<sstream>
#include<fstream>
using namespace std;

class Debugclass {
    public:
        Debugclass(ostream &s = cerr):os(s){}
        template<typename T>
        void operator()(T*p) const{
            os << "deleing unique_ptr\n";
            delete p;
        }
    private:
        ostream &os;
};

int main()
{
    double *p = new double;
    Debugclass deb;
    deb(p); //调用成员模板函数
    int *ip = new int;
    Debugclass()(ip); //这个调用方式有点神奇 但可惜没什么卵用
    //在一个临时对象上调用函数运算符
    unique_ptr<int ,Debugclass> q(new int(666),Debugclass());
    //只是这样可以 但感觉没什么必要(现阶段来看)
    cout << *q << endl;
}