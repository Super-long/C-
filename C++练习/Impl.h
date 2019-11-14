#include<iostream>
using namespace std;

class A{
    public:
        int a;
        explicit A(int aa):a(aa){}
        void show_A()const{
            cout << a << endl;
        }
};

class B{
    public:
        explicit B(double bb):b(bb){}
        double b;
        void show_B()const{
            cout << b << endl;
        }
};

class C{
    public:
        char ch;
        explicit C(char c):ch(c){}
        void show_C()const{
            cout << ch << endl;
        }
};

class Person{
    public:
        Person(const A& aa,const B& bb,const C& cc):a(aa),b(bb),c(cc){}
        void show_A()const{
            a.show_A();
        }
        void show_B()const{
            b.show_B();
        }
        void show_C()const{
            c.show_C();
        }
    private:
        A a;
        B b;
        C c;
};