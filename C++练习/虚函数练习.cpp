#include<iostream>
using namespace std;

class one{
    public:
        virtual void show(){
            cout << "one\n";
        }
};

class three{
    public:
        virtual void show(){
            cout << "three\n";
        }
};

class two :public one,public three{
    public:
        void show() override{
            cout << "two\n";
        }
};

void jugde(one &t){
    t.show();
}

void ssc(three&t){
    t.show();
}

int main(){
    two tmpa;
    one tmpb;
    three tmpc;
    double a = 1/3;
/*     jugde(tmpa);
    ssc(tmpc); */
    double b = 10.5;
    const double& t = b;//把常量引用的类型改成double或者int有不同的输出
    cout << t << endl;
    b = 5;
    cout << t << endl;//神奇　因为绑定的实际上是一个临时变量
    cout << a << endl;
    return 0;
}