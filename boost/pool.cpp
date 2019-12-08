#include<boost/pool/pool.hpp>
#include<boost/pool/object_pool.hpp>
#include<iostream>
#include<memory>
using namespace std;

class myclass{
    public:
        myclass() = default;
        myclass(int a,int b) : aa(a), bb(b){} 
        ~myclass(){cout << "析构\n";}
        void show() {cout << aa << endl;}
    private:
        int aa,bb;
};

void test(){
    boost::object_pool<myclass> opl;
    myclass* p = opl.malloc();
    p->show();
    myclass* x = opl.construct(1,5); //自动执行析构函数
    x->show();
/*     opl.free(p);//一般来说不需要调用free 除非认为内存池空间不足
    opl.free(x); */
}

void test_T(){
    boost::object_pool<myclass> opl;
    myclass* T(opl.construct(10,15));//没必要用智能指针
    T->show();
}

int main(){
/*     boost::pool<> pl(sizeof(int));
    int *p = static_cast<int*>(pl.malloc());
    *p = 100;
    cout << *p << endl;
    pl.free(p); */
    test_T();
    int f;
    cin >> f;
    return 0;
}