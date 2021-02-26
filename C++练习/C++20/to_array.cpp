/* #include <bits/stdc++.h>
using namespace std;

template<typename T>
void f(T param){
    cout << "hello\n";
}

int main(){
    auto x = {1,3,5,7};
    //f({2,4,6,8});
} */

#include <type_traits>
#include <utility>
#include <array>
#include <memory>
 
int main()
{
    // 复制字符串字面量
    auto a1 = std::to_array("foo");
    static_assert(a1.size() == 4);
 
    // 推导元素类型和长度
    auto a2 = std::to_array({ 0, 2, 1, 3 });
    static_assert(std::is_same_v<decltype(a2), std::array<int, 4>>);
 
    // 推导长度而元素类型指定
    // 发生隐式转换
    auto a3 = std::to_array<long>({ 0, 1, 3 });
    static_assert(std::is_same_v<decltype(a3), std::array<long, 3>>);
 
    auto a4 = std::to_array<std::pair<int, float>>(
        { { 3, .0f }, { 4, .1f }, { 4, .1e23f } });
    static_assert(a4.size() == 3);
 
    // 创建不可复制的 std::array
    auto a5 = std::to_array({ std::make_unique<int>(3) });
    static_assert(a5.size() == 1);
 
    // 错误：不支持复制多维数组
    // char s[2][6] = { "nice", "thing" };
    // auto a6 = std::to_array(s);
}