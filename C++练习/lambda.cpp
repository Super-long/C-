#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<stack>
#include<deque>
#include<list>
#include<numeric>
using namespace std;
bool tmp(int a)
{
    return a>5;
}
bool issshorter(string a,string b)
{
    return a.size() > b.size();
}
int main()
{
    vector<string>::size_type sz=4;
    vector<string>vec{"asd","hello","okop","oklsa","asdwqe","ddd","asd"};
    sort(vec.begin(),vec.end());
    auto x=unique(vec.begin(),vec.end());
    vec.erase(x,vec.end());
    for(auto x : vec) cout << x << " ";
    putchar('\n');
    stable_sort(vec.begin(),vec.end(),issshorter);
    for(auto x : vec) cout << x << " ";
    auto wc = find_if(vec.begin(),vec.end(),
    [sz](const string &a)
    {return a.size() < sz;});  //lambda表达式
    auto count=vec.end()-wc;
    for_each(wc,vec.end(),[](const string &a){cout << a << endl;});
}