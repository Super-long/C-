#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<queue>
#include<vector>
#include<cstdlib>
#include<utility>
#include<cstring>
using namespace std;

//这东西好像是没什么用　除了返回值可以不需要用结构体去传多个参数
//两者的区别就是申请一个结构体可能需要占一个符号位　而元组就不需要

//优点: 使代码简洁高效　make_tuple　可以使得申请也更加简单
//或者在其中加一个范围的迭代器　全局变量虽然也可以　但是破坏了代码的耦合性(块间联系)

tuple<int,int,string> judge(){
    auto x = make_tuple(1,2,"string");
    return x;
}

int main()
{
    tuple<int,int,int> duo(1,2,3);
    auto x = make_tuple(1,2,3,4);
    cout << get<2>(x) << endl;
    auto temp = judge();
    cout << get<2>(temp) << endl;
    return 0;
}