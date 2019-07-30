//加强拷贝构造函数的理解

#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
using namespace std;

struct X
{
	X() { std::cout << "X()" << std::endl; }
	X(const X&) { std::cout << "X(const X&)" << std::endl; }
	X& operator=(const X &rh)
	{
		std::cout << "X& operator=(const X &rh)" << std::endl;
		return *this;
	}
	~X() { std::cout << "~x()" << std::endl; }
};

void fun1(X x)
{
    cout << "fun1 X x \n";
}

void fun2(X &x)
{
    cout << "fun2 X &x\n";
}

int main()
{
    X x1;
    fun1(x1);
    fun2(x1);
	X *x2 = new X();
	{	
		std::cout << "vector" << std::endl;
		std::vector<X> v;
		v.reserve(3);  //vector会进行扩充　
		v.push_back(x1);
		v.push_back(*x2);
        v.emplace_back(x1);
	}
    delete x2;
}

//巧妙的例子