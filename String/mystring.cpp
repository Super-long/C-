//#include"stringfwd.h"
#include"Base_string.h"
#include"Char_traits.h"
#include"Base_string.cc"
#include<iostream>

using namespace String;

int main(){
    using std::cout;
    using std::endl;
    const char book[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    String::Basic_string<char,Char_traits<char>,std::allocator<char>> S({'a','b','a','b','a','b','a','b','a','b'});
    //String::Basic_string<char,Char_traits<char>,std::allocator<char>> T(S);
    
    //String::string S;
    std::cout << S.length() << endl;
    std::cout << S.capacity() << endl;
    S.reserve(20);
    std::cout << S.length() << endl;
    std::cout << S.capacity() << endl;

    cout << "数据" << S[0] << S[1] << S[2]<< endl;

    return 0;
}