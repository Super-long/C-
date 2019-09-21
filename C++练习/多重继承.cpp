#include<memory>
#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

namespace Test_MI{
    class base1{
        public:
            virtual void print(){cout << "hello world in base1\n";}
            virtual ~base1(){cout << "destruct in base1\n";}
    };
    class base2{
        public:
            virtual void print(){cout << "hello world in base2\n";}
            virtual ~base2(){cout << "dextruct in base2\n";}
    };
    class D1 : public base1{
        public:
            void show() const {cout << "show in D1\n";}
            virtual void print() override {cout << "hello world in D1\n";}
            virtual ~D1() override {cout << "destruct in D1\n";}
    };
    class D2 : public base2{
        public:
            void show(int) const {cout << "show in D2\n";}
            virtual void print() override {cout << "hello world in D2\n";}
            virtual ~D2() override {cout << "destruct in D2\n";}
    };
    class MI_Test final: public D1,public D2{
        public:
            void print() override final {cout << "hello world in MI_Test\n";}
            virtual ~MI_Test() override final {cout << "destruct in MI_Test\n";}
    };
}
int hh = 5;
namespace{
    int aa = 5;
}
using namespace Test_MI;
int main(){
    MI_Test test;
    test.D1::show(); //不指明作用域就会出现二义性
    //test.show(); //在两个基类中的函数名虽然相同　但是参数不同　这样仍会造成二义性(名称查询优先于类型查询)
    //为了避免二义性　我们可以在派生类中重新编写一个同名函数　隐藏基类同名函数
    int hh = 10;
    int aa = 10;
    cout << ::aa << endl;
    cout << ::hh << endl;
    base1 *pb1 = new MI_Test;
    pb1->print();
    base2 *pb2 = new MI_Test;
    pb2->print();
    D1 *b1 = new MI_Test;
    b1->print();
    D2 *b2 = new MI_Test;
    b2->print();

    delete pb1;
    cout << "------\n";
    delete pb2;
    cout << "------\n";
    delete b1;
    cout << "------\n";
    delete b2;
    return 0;
}