#include<bits/stdc++.h>
using namespace std;

struct RGBA{
    uint8_t a,b,c,d;

    RGBA(uint8_t a, uint8_t e, uint8_t f, uint8_t g) :
        a(a), b(e), c(f), d(g){}
    
    void show(){
        cout << a << ": " << b << ": " << c << endl;
    }
};

RGBA operator"" _RGBA(const char* str, size_t size){
    cout << size << endl; //自动推断长度
    uint8_t a=97,b=2,c=3,d=4; //相当于unsigned char
    return RGBA(a,b,c,d);
}

int main(){
    string a = R"(\r"ow\\char\n)";//C++11 原生字符串 忽略转义字符
    string b = "\\r\"ow\\\\char\\n";
    cout << a << endl;
    cout << b << endl;

    //C++11 用户自定义字面量
    //C++11 目前规定的仅有以下是合法的
    /*
    char const *
    unsigned long long
    long double
    char const *, size_t
    wchar_t const *, size_t
    char16_t const *, size_t
    char32_t const *, size_t
    */

   RGBA Temp = "hello"_RGBA;
   Temp.show();
   //uint8_t默认输出类型为char
}