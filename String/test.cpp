#include<bits/stdc++.h>
using namespace std;

int main(){
    auto ch = char();
    string str1 = "hello";
    string str2(str1,2,3);
    allocator<char> chr;
    auto const o = chr.allocate(10);
    str2.push_back('2');
    string str3(chr);
    str3.push_back('2');
    cout << str3 << endl;
    cout << ch << endl;
}