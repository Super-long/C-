#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>
using namespace std;

template<class T>
class tobig
{
    private:
        T cutoff;
    public:
        tobig(const T &t):cutoff(t){}
        bool operator()(const T &v) {return v>cutoff;}
};     //可以 但没必要 为了满足remove_if 其实写一个函数就够了

//bool judge(int n){return n>100;} 
//可以满足与类相同的条件 但类更通用 想改变边界条件两个对象就可以 但函数必须得写两个

void outint(int n) {cout << n << " ";}

int main()
{
    tobig<int> limit(100);
    int val[10]={102,52,13,46,782,156,520,206,198};
    list<int> ya(val,val+10);
    list<int> et(val,val+10);
    cout << "original val:\n";
    for_each(ya.begin(),ya.end(),outint);
    cout << endl;

    for(auto tmp : ya) cout << tmp << " ";
    cout << endl;

    ya.remove_if(limit);
    for_each(ya.begin(),ya.end(),outint);
    cout << endl;

    et.remove_if(tobig<int>(200));
    for(auto tmp: et) cout << tmp <<" ";
    cout << endl;
    return 0;
}