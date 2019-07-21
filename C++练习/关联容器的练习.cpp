#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

typedef struct{
    int ans;
    char ch;
}node;

bool compare(node a,node b)
{
    return a.ans < b.ans;
}

map <node,int,decltype(compare)*> mp(compare);

int main()
{
    node book[5];
    for(auto x : book){
        cin >> x.ans >> x.ch;
        mp[x]++;
    }
    for(const auto &x : mp)
    {
        cout << x.first.ch << ": " << x.second << endl;
    }
    return 0;
}