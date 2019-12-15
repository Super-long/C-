#include<bits/stdc++.h>
using namespace std;

//http://man7.org

int main(){
    using std::cout;
    using std::endl;
    const char book[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    string S(book);
    string T(S,3,10);
    cout << T[0] << T[1] << T[2] << endl;
    
    //String::string S;
    std::cout << T.length() << endl;
    std::cout << T.capacity() << endl;
    S.reserve(20);
    std::cout << T.length() << endl;
    std::cout << T.capacity() << endl;

    return 0;
}