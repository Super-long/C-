/*返回一个动态分配int的vector 将此vector传递给另外一个函数
这个函数读取标准输入 读入的值保存在vector 再将vector传递给
另外一个函数 再打印出来 记得delete*/

/* #include<iostream>
#include<vector>
using namespace std;

vector<int>* judge()
{
    return new vector<int>;
}

vector<int>* rejudge(vector<int> * vec)
{
    int tmp=0;
    while(cin >> tmp && tmp)
    {
        vec->push_back(tmp);
    }
    return vec;
}

void show(vector<int>*vec)
{
    for(auto x : *vec)
    {
        cout << x << " "<< endl;
    }
    delete vec;
}

int main()
{
    show(rejudge(judge()));
    return 0;
} */

//智能指针版

#include<iostream>
#include<vector>
#include<memory>
using namespace std;

shared_ptr<vector<int>> judge()
{
    return make_shared<vector<int>>();
}

shared_ptr<vector<int>> rejudge(shared_ptr<vector<int>> ptr)
{
    int tmp(1);
    while(cin >> tmp && tmp)
    {
        ptr->push_back(tmp);
    }
    return  ptr;
}

void show(shared_ptr<vector<int>> ptr)
{
    for(auto x: *ptr)
    cout << x << " " << endl;
}

int main()
{
    show(rejudge(judge()));
}