#include<bits/stdc++.h>
using namespace std;

//http://man7.org

int main(){
    auto ch = char();
    string str1 = "hello";
    string str2 = "sda";
    str2.append(str1);
    cout << str2 << endl;
    allocator<int>a;
    auto ptr = a.allocate(20);
    ptr[0] = 'c';
    cout << ptr[0] << endl;
    a.deallocate(ptr,20);
/*     cout << a.max_size() << endl; */
    cout << static_cast<int>(str2.front()) << endl;
/*     cout << str2.capacity() << endl;
    cout << str2.size() << endl;
    str2.reserve(80);
    cout << str2.capacity() << endl;
    cout << str2.size() << endl; */
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