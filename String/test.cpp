#include<bits/stdc++.h>
using namespace std;

//http://man7.org

int main(){
    string str("asdasda");
    string one("aaa");
    str.pop_back();
    cout << str << endl;
    one.assign(str);
    str.assign(10,'a');
    cout << one << endl;
    cout << str << endl;
    return 0;
}