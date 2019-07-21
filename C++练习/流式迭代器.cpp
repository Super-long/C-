#include<iostream>
#include<string>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;
int main()
{
/*     ostream_iterator<int> out_iter(cout,"-");
    istream_iterator<int> in_iter(cin),eof; */
/*     vector<int>vec(in_iter,eof);  //基于一个范围建立vec 从流中获取
    for(auto x : vec)
    {
        *out_iter++ = x;  //相当于把值放入cout输出流中
    }
    cout << endl;

    copy(vec.begin(),vec.end(),out_iter); //两种写法相同
    cout << endl; */

    //-----------------------------------------------
/*     vector<int>tmp(in_iter,eof);
    sort(tmp.begin(),tmp.end());
    unique_copy(tmp.begin(),tmp.end(),out_iter);
    cout << endl; */

    string haha={"fitst,middle,last"};
    auto ha=find(haha.crbegin(),haha.crend(),',');
    cout << string(ha,haha.crend()) << endl;
    //打印最后一个零
    vector<int>vec={0,2,3,6,4,9,8,0,2,3,6,5,4,7,8,0,5};
    auto x = find(vec.crbegin(),vec.crend(),0);
    cout << vec.size()-(x-vec.crbegin()) << endl;

    
}