#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<sstream>
#include<fstream>
using namespace std;

template<typename U,typename T>
U my_find(const U& a,const U& b,const T&&c)
//这里的参数存在一个完美转发的问题 使用引用右值是不可以匹配的
{
    auto tmp=a;
    for(tmp;tmp!=b;tmp++)
    {
        if(*tmp==c)
        {
            return tmp;
        }
    }
}

int main()
{
    vector<int> vec={1,2,3,4,5,6};
    auto x = my_find(vec.begin(),vec.end(),3);
    cout << *x << endl;
}