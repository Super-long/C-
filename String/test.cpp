#include<bits/stdc++.h>
using namespace std;

int main(){
    auto ch = char();
    string str1 = "hello";
    string str2;
    
    cout << str2.capacity() << endl;
    cout << str2.size() << endl;
    str2.reserve(80);
    cout << str2.capacity() << endl;
    cout << str2.size() << endl;
 /*    cout << str1.capacity() << endl;
    cout << str1.size() << endl;
    str1.shrink_to_fit();
    cout << str1.capacity() << endl;
    cout << str1.size() << endl;
    //string(str1).swap(str1);
    str1.reserve(16);
    cout << str1.capacity() << endl;
    cout << str1.size() << endl; */
}