#include <iostream>
class A {
public:
    virtual void func_a();
    int a = 10;
};

class D: public A {
public:
    virtual void func_a();
    int d = 40;
};

void A::func_a() {std::cout << "A::func_a()" << std::endl;}
void D::func_a() {std::cout << "D::func_a()" << std::endl;}

int main() {
    std::cout << "sizeof(A): " << sizeof(A) << std::endl;
    std::cout << "sizeof(D): " << sizeof(D) << std::endl;
    D* d = new D();
    A* aa = new A();
    std::cout << d << std::endl;
    A* a = d;
    std::cout << a << std::endl;
    d->func_a();
    a->func_a();
    return 0;
}