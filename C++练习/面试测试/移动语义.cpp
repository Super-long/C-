#include <iostream>
#include<vector>
using namespace std;

class A {
public:
	A() {
		cout << " A construct" << endl;
	}
	A(const A&t){
		cout << "A copy construct" << endl;
		d = t.d;
	}
	A(const  A&&t) noexcept {
		d = t.d;
		cout << "A move construct" << endl;
	}
	A& operator=(const A&t) {
		d = t.d;
		cout << "A copy assignment " << endl;
		return *this;
	}

	A& operator=(const A&&t) noexcept {
		d = t.d;
		cout << "A move assignment" << endl;
		return *this;
	}
	int d;
};
class B{
public:
	A  a;
};
int main(int argc, char **argv) {
	B b1;
	vector<B> v2;
	unsigned addr;
	b1.a.d = 10086;

	{
		vector<B> v1;
		v1.push_back(b1);
		v1.push_back(b1);
		addr = (unsigned)&v1[0];
	}
	cout << ((B*)addr)->a.d <<" definitly udefinded" <<endl;//肯定未定义值


	{
		vector<B> v1;
		v1.push_back(b1);
		v1.push_back(b1);
		addr = (unsigned)&v1[0];
		cout << (unsigned int)&v1[0]<<" " << (unsigned int)&v1<< endl;

		v2 = std::move(v1);//比上一个括号多了这一句
		//v1.~vector();
	}
	cout <<  (unsigned)&v2[0]<< " " << (unsigned int)&v2 << endl; 
	cout << ((B*)addr)->a.d << " amazing" << endl;

	cout << v2[0].a.d << endl;;


	return 0;
}