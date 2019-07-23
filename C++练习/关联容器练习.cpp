#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<list>
#include<vector>
#include<cstdlib>
#include<utility>
#include<cstring>
using namespace std;
/* map<vector<int>::iterator,int>mp;
//map<list<int>::iterator,int>mapp; //以vector的迭代器作为map的值
vector<int>vec={1,2,3,4,5,6};
list<int>ve={1,2,3,4,5,6};
int main()
{
    
    mp[vec.begin()]++;
    vec.
    //mp[ve.begin()]++;
    cout << mp[vec.begin()] << endl;
    cout << "hello word\n";
} */
/* int main()
{
    pair<string,int>pa;  //向关联容器拷贝元素
    map<string,int>mp;
    vector<pair<string,int>>vec;
    string s;
    int ss;
    while(cin >> s >> ss)
    {
        vec.push_back({s,ss});   //列表初始化
        //vec.push_back(make_pair(s,ss));
    }
    copy(vec.begin(),vec.end(),inserter(mp,mp.begin()));
    cout << mp.begin()->first << " " << mp.begin()->second << endl;
    for(auto x : vec)
    {
        cout << x.first << " " << x.second << endl;
    }
} */

/* int main()   //检测插入的返回值
{
    map<string,size_t>mp;
    string str;
    while(cin >> str)
    {
        //auto ret=mp.insert({str,str.size()});
        pair<map<string,size_t>::iterator,bool> ret=mp.insert(make_pair(str,str.size()));
        cout << ret.second << endl;
        if(!ret.second)
        ++ret.first->second;
    }
} */
/* 
int main()
{
    set<int>s;
    s.insert(1);
    s.insert(3);
    s.insert(6);
    multimap<int,int>mp={{1,1},{1,2},{3,1},{6,2},{4,3},{3,5}};


     for(auto beg=mp.lower_bound(1),
    end=mp.upper_bound(7);
    beg!=end;beg++) cout << beg->first << endl; 
    for(auto pos=mp.equal_range(1);
    pos.first!=pos.second;pos.first++) cout << pos.first->first <<  " " << pos.first->second << endl;
    
    
    auto x=mp.find(3);  //if 中好像不能定义变量
    size_t a=mp.count(3);
    if(x != mp.end())
    {
        for(;a>0;a--)
        {
            cout << x->first << " " << x->second << endl;
            ++x;
        }
    
    
    }
    auto x=mp.find(7);
    if(mp.find(7)==mp.end()) cout << " yes\n";
    cout << x->first << " " << x->second;   //这一步会向map中加入元素 所以一句判断就好
} */

/* int main()   //测试erase函数
{
    multimap<string,string>mp;
    mp.insert({"tony","hello"});
    mp.insert({"tony","nihao"});
    mp.insert({"pony","asdasd"});
    auto iter=mp.find("tony");
    auto num=mp.count("tony");
    while(num--){
        mp.erase(iter++);
    }
    cout << mp.size() << endl;
} */
