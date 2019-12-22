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
    cout << S.find_last_not_of(T,20) << endl;
    cout << S.find_last_not_of('m', 20) << endl;
    cout << S.find_last_not_of("ijk", 20, 3) << endl;
    //cout << TT.find('c', 10) << endl;

    return 0;
}