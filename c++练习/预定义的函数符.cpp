#include<iostream>
#include<algorithm>
//#include<functional>
using namespace std;
int val[10]={4,5,3,45,15,36,89,152,124,81};
int main()
{
    sort(val,val+10,greater<int>()); //预定义的函数符 可以用来替代函数
    for(auto pr : val) cout << pr << " ";
    return 0;
}