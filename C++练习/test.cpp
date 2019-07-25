#include<iostream>
#include<memory>
using namespace std;
void process(shared_ptr<int> ptr)
{
    cout << *ptr << endl;
}

int main()
{
    //auto ptr=make_shared<int>(10);
 /*    shared_ptr<int> ptr(new int(10)); //接受指针参数的构造函数是explicit
    process(ptr);
    cout << *ptr << endl;
    int *x(new int(10));
    cout << "hwllo\n";
    cout << *x << endl;
    process(shared_ptr<int>(x));
    cout << *x << endl;
    cout << "asdas\n"; */
{    auto sp=make_shared<int>(10);
    auto p=sp.get();
    delete p;}
    cout << "hwllo \n";
}