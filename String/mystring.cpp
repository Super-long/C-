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
    String::Basic_string<char,Char_traits<char>,std::allocator<char>> S(book);
    String::Basic_string<char,Char_traits<char>,std::allocator<char>> T("ghijk");
    String::Basic_string<char,Char_traits<char>,std::allocator<char>> TT;
    //T.append(10, 'a');
    TT.append(S);
    cout << TT.find('c', 10) << endl;

    return 0;
}