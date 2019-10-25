#include<list>
#include<iostream>
using namespace std;

int main(){
    list<int> li;
    li.push_back(5);
    auto x = li.end();
    cout << &x << endl;
    li.push_back(10);
    li.push_back(50);
    //li.erase(x);
    cout << *x << endl;
    cout << li.size() << endl;
    cout << &li.begin() << endl;
}