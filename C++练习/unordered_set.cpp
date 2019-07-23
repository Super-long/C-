#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<unordered_set>
#include<list>
#include<vector>
#include<cstdlib>
#include<utility>
#include<cstring>
using namespace std;

typedef struct 
{
    int ans;
    string str;
}Node;

size_t hasher(const Node & sd)
{
    return hash<string>()(sd.str);
}

bool equalaa(const Node & a, const Node &b)  //equal不能做名称
{
    return a.str==b.str;
}

int main()
{
    unordered_multiset<Node,decltype(hasher)*,decltype(equalaa)*>mp(42,hasher,equalaa);
    string str; //不知道怎么实现 相同的确实存在了一起
    int ans;
    while(cin >> str >> ans)
    {
        mp.insert({ans,str});
    }
    Node ll={5,"hello"};
    for(auto x : mp) 
    cout << x.ans << " " << x.str << endl;
    auto a   = mp.find(ll);
    auto num = mp.count(ll); //都是ok的
    while(a!=mp.end())
    {
        cout << a->ans << " " << a->str << endl;
        a++;
    }
    return 0;
} 