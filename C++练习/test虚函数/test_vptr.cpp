#include <bits/stdc++.h>
using namespace std;

class A1
{
public:
    A1(int _a1 = 1) : a1(_a1) { }
    virtual void f() { cout << "A1::f" << endl; }
    virtual void g() { cout << "A1::g" << endl; }
    virtual void h() { cout << "A1::h" << endl; }
    ~A1() {}
public:
    int a1;
};
class C : public A1
{
public:
    C(int _a1 = 1, int _c = 4) :A1(_a1), c(_c) { }
    virtual void f() { cout << "C::f" << endl; }
    virtual void g() { cout << "C::g" << endl; }
    //virtual void h() { cout << "C::h" << endl; }
public:
    int c;
};

class D : public C
{
public:
    friend void cross_product(const D& lhs, const D& rhs);
    D(int _a1 = 1, int _c = 4) : C(_a1),e(_c) { }
    virtual void f() { cout << "D::f" << endl; }
    virtual void g() { cout << "D::g" << endl; }
    //virtual void h() { cout << "C::h" << endl; }
    void cross_productA(const D& lhs){
        D temp;
        temp.a1 = lhs.e * this->e - lhs.a1 * this->a1;
        temp.c = lhs.c * this->c - lhs.a1 * this->a1;
        temp.e = lhs.a1 * this->a1 - lhs.c * this->e;
    }

    static void cross_productB(const D& lhs, const D& rhs){
        D temp;
        temp.a1 = lhs.e * rhs.e - lhs.a1 * rhs.a1;
        temp.c = lhs.c * rhs.c - lhs.a1 * rhs.a1;
        temp.e = lhs.a1 * rhs.a1 - lhs.c * rhs.e;
    }

    virtual void cross_productC(const D& lhs){
        D temp;
        temp.a1 = lhs.e * this->e - lhs.a1 * this->a1;
        temp.c = lhs.c * this->c - lhs.a1 * this->a1;
        temp.e = lhs.a1 * this->a1 - lhs.c * this->e;
    }
public:
    int e;
};
A1 a;
long long *pa = (long long *)(*(long long*)&a);

C c;
long long *p = (long long *)(*(long long*)&c);
typedef void(*FUNC)();        //重定义函数指针，指向函数的指针
 
void PrintVTable(long long* vTable)  //打印虚函数表
{
    if (vTable == NULL)
    {
        return;
    }
    cout << "vtbl:" << vTable << endl;
    int  i = 0;
    for (; vTable[i] != 0; ++i)
    {
        printf("function : %d :0X%x->", i, vTable[i]);
        FUNC f = (FUNC)vTable[i];
        f();         //访问虚函数
    }
    cout << endl;
}

inline void cross_product(const D& lhs, const D& rhs){
    D temp;
    temp.a1 = lhs.e * rhs.e - lhs.a1 * rhs.a1;
    temp.c = lhs.c * rhs.c - lhs.a1 * rhs.a1;
    temp.e = lhs.a1 * rhs.a1 - lhs.c * rhs.e;
}

int main(){
/*     PrintVTable(p);
    PrintVTable(pa); */

    D pA;
    D pB;

    unsigned long sum = 0;
    const size_t len = 10;

    for (size_t i = 0; i < len; i++){
        auto start = std::chrono::high_resolution_clock::now(); 

        for (size_t i = 0; i < 10000000; i++){
            cross_product(pA, pB);    // 278ms
            //pA.cross_productA(pB);    // 280ms
            //D::cross_productB(pA, pB);// 310ms
            //pA.cross_productC(pB);      // 280ms
        }    

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::ratio<1,1000>> time_span 
        = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,1000>>>(end - start);

        sum += time_span.count();
    }
    
    cout << sum/len << endl;

    return 0;
}