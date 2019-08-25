#include<memory>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//这个程序可以看出如果move的对象有析构函数　在move之后对象就会被析构　
//int之类的基本数据类型不会被析构
int main()
{
    string a="hello";
    vector<int> aa={1,2,3};
    cout << &aa[2] << endl;
    vector<vector<int>>vec;
    vec.push_back(std::move(aa));
    cout << vec[0][2] << endl;
    cout << &vec[0][2] << endl;
    cout << aa.size() << endl;
}