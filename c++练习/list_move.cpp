//测试remove函数和remove成员
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
const int len=10;
void show(int i)
{
    cout << i << " ";
}

int main()
{
    int ar[len]={4,2,5,6,4,9,8,7,1,2};
    list<int> la(ar,ar+10);
    list<int> lb(la);
    cout << "Original list contents:\n";
    for_each(la.begin(),la.end(),show);
    cout << endl;
    cout << "after la remove(4)\n";
    la.remove(4);
    for_each(la.begin(),la.end(),show);
    cout << "after lb remove(4)\n";
    list<int>::iterator last;
    last=remove(lb.begin(),lb.end(),4);
    for_each(lb.begin(),lb.end(),show);
    cout << "after lb erase \n";
    lb.erase(last,lb.end());
    for_each(lb.begin(),lb.end(),show);
    return 0;
}