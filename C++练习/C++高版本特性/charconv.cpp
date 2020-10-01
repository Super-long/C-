#include <charconv>
#include<bits/stdc++.h>
#include<tuple>
using namespace std;

// 感觉像是C语言原始函数的升级 字符串和数字之间的转换
int main()
{
    std::array<char, 3> str{"42"};
    int result;
    std::from_chars( str.data(), str.data()+str.size(),result );
    std::cout << result << std::endl;
 
    // p是填充到str以后的最后一个迭代器
    if(auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), 425);
       ec == std::errc()){
        if(p == str.end()){
            std::cout << "hello world\n";
        }
            std::cout << std::string_view(str.data(), p - str.data());
       }
    return 0;
}