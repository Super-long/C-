#include<iostream>
#include<vector>
using namespace std;
vector<double> tmp(5);
auto pd=tmp.begin();
double flag;
int main()
{
/*     for(int i=0;i<5;i++)
    cin >> tmp[i];
    for(pd=tmp.begin();pd!=tmp.end();pd++)
    cout << *pd << endl; */
    while(cin >> flag && flag>=0)
    {
        tmp.push_back(flag);
    }
    cout << "your entered" << tmp.size() <<" sorces!\n";
    return 0;
}