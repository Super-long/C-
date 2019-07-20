#include<string>
#include<iostream>
#include<vector>
using namespace std;
vector<string> vec;
int main()
{
    cout << vec.size() << endl;
    string tmp="hello world";
    for(auto x : tmp)
    {
        cout << x;
    }
    cout << tmp << endl;
    return 0;
}