#include<bits/stdc++.h>
#include<ostream>
using namespace std;

//http://man7.org

int main(){
    using std::cout;
    using std::endl;
    const char book[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    string S(book);
    string T;
 
     cout << S << endl;
    T.append(15, 'c');

    cout << S.size() << endl;
    cout << S.capacity() << endl;
    //S.assign(T, 2, 10);
    T.assign(book);
    cout << T << endl;
    cout << T.size() << endl;
    cout << T.capacity() << endl;

    cout << S << endl; 
}