#include<memory>
#include<iostream>

using namespace std;

bool del(int *p)
{
    delete [] p;
}

shared_ptr<int> shared(new int[100],del);//使用函数

shared_ptr<int> ptr(new int[100],
[](int *p){delete [] p;});//使用lambda表达式

unique_ptr<int[]>unique(new int[100]);

int main()
{
    auto x = ptr.get();
    delete [] x;
    cout << unique[10]<<endl;
}