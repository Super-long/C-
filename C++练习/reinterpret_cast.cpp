#include<iostream>

using namespace std;

class A {
public:
	virtual void func() {
		cout << "A::func" << endl;
	}
	virtual void funcA() {
		cout << "A::funcA" << endl;
	}
private:
	int a;
};
class B {
public:
	virtual void func() {
		cout << "B::func" << endl;
	}
	virtual void funcB() {
		cout << "B::funcB" << endl;
	}
private:
	int b;
};
class C :public A, public B {
public:
	virtual void func() {
		cout << "C::func" << endl;
	}
	virtual void funcC() {
		cout << "C::funcC" << endl;
	}
private:
	int c;
};

int main(){
	C c;
	A *pa = &c;
	B *pb = &c;
	C *pc = &c;
    
    pa = reinterpret_cast<A*>(pb);//逐字节拷贝 第一个多态 第二个从B的虚表中直接取
    pa->func();
    pa->funcA();
    pa = static_cast<A*>(pc);//static_cast只有派生先基类转化
    pa->func();
    pa->funcA();
    pa = dynamic_cast<A*>(pb);//dynamic_cast则会检查继承树
    pa->func();
    pa->funcA();
}
/* ouput
C::func
B::funcB
C::func
A::funcA
C::func
A::funcA
*/