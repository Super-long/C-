//旨在测试next_permutations函数的随机排列功能
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int main()
{
    string tmp;
    cout << "enter a string (quit to quit)\n";
    while(cin >> tmp && tmp!="quit")
    {
        cout << "init permutation\n";
        sort(tmp.begin(),tmp.end());
        cout << tmp << endl;
        while(next_permutation(tmp.begin(),tmp.end()))
        {
            cout << tmp << endl;//自动提供唯一的全排列组合
        }
    }
    cout << "Done!";
    return 0;
}