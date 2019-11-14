#include"Implaa.h"
#include<memory>
using namespace std;

class Sum{
    public:
        Sum(const A& a,const B& b,const C& c):Pimpl(new Person(a,b,c)){}
        void show_A(){
            Pimpl->show_A();
        }
        void show_B(){
            Pimpl->show_B();
        }
        void show_C(){
            Pimpl->show_C();
        }
    private:
        shared_ptr<Person> Pimpl;
};

class Num{
    public:
        virtual ~Num(){} //宛如一个智障 没加这个调了半天
        virtual void show_A() const = 0;
        virtual void show_B() const = 0;
        virtual void show_C() const = 0;
        static shared_ptr<Num> Create(const A& a,const B& b,const C& c);
};

class RealNum : public Num{
    public:
        RealNum(const A& aa,const B& bb,const C& cc):a(aa),b(bb),c(cc){}
        virtual ~RealNum(){}
        void show_A()const{
            a.show_A();
            cout << "A\n";
        }
        void show_B()const{
            b.show_B();
            cout << "B\n";
        }
        void show_C()const{
            c.show_C();
            cout << "C\n";
        }
    private:
        A a;
        B b;
        C c;
};

shared_ptr<Num> Num::Create(const A& a,const B& b,const C& c)
{
    return shared_ptr<Num>(new RealNum(a,b,c));
}

int main(){
    A a(5);
    B b(10);
    C c(15);
    auto T = Num::Create(a,b,c);
    T->show_A();

    Sum TT(a,b,c);
    TT.show_A();
    return 0;
}