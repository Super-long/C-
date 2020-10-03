#include <iostream>
#include <memory>       // unique_ptr
#include <shared_mutex> // shared_timed_mutex
#include <vector>       // vector
using namespace std;

#define one     (1)         // 函数返回值类型推导
#define two     (1<<2)      // lambda参数auto
#define three   (1<<3)      // 变量模板与别名模板
#define four    (1<<4)      // 更为宽松的constexper
#define five    (1<<5)      // [[deprecated]]标记
#define six     (1<<6)      // 二进制字面量与整形字面量分隔符
#define seven   (1<<7)      // std::make_unique
#define eight   (1<<8)      // std::shared_timed_mutex与std::shared_lock
#define nine    (1<<9)      // integer_sequence : 目前发现的用处就是把一个容器的每一项在编译期当做一个函数的参数
#define ten     (1<<10)     // exchange 

// 每个测试样例函数命名规则为func_测试编号

int Switch = ten;

//----------------------- 返回值类型推导
auto func_one(int i) {
    return i;
}

template<typename T> auto func_one(T t){    // 模板中也可以这样玩
    return t;
}
/*
auto func(bool flag) {
    if (flag) return 1;
    else return 2.3; // 在出现多个类型分支的时候没办法推导
}

auto func() {
    return {1, 2, 3}; // 初始化列表也没办法被推导
}
*/

//-----------------------lambda参数auto

auto func_two = [] (auto a) { return a;};

//-----------------------变量模板与别名模板

template<class T>   // 变量模板 最典型的用法就是pi，在以前只能用一个没有参数的模板函数来返回
constexpr T pi = T(3.1415926535897932385L);

template<typename T, typename U>
struct str_three{
    T t;
    U u;
};

// C++11引入类型别名的原因是因为无法在typedef语句的基础上直接构建别名模板
// 别名模板可以使声明一个只带一个模板参数T的类模板，使其等价于模板参数T为int类型的str_three模板
template<typename U>
using var_three = str_three<int, U>;

//----------------------- 更宽松的constexpr限制
/**
 * C++11: 1. 函数的返回类型以及所有形参的类型都得是字面值类型
 *        2. 函数体中只能由一个return语句
 * C++14: 1. 可以使用局部变量和循环
 *        2. 可以使用多个return
 * C++17: 1. 待下一个文件
*/

constexpr int factorial_four(int n) { // C++14 和 C++11均可
    return n <= 1 ? 1 : (n * factorial_four(n - 1));
}

// 多返回值与局部变量
constexpr int factorial(int n) { // C++11中不可，C++14中可以
    if(n < 0) return 0;
    int ret = 0;
    // int items[20]; 这样定义是不对的
    for (int i = 0; i < n; ++i) {
        ret += i;
    }
    return ret;
}

//----------------------- [[deprecated]]标记 
// 编译时被产生警告，用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用
// 可以修饰类、变、函数等
/* struct [[deprecated]] var_five {
    int item;
};

[[deprecated]] constexpr int func_five(){
    return 200;
} */

//----------------------- std::shared_timed_mutex 
// GCC的C++14支持shared_timed_mutex不支持shared_mutex我也是服了
// timed_mutex是C++11的

class cls_eight{
private:
    mutable std::shared_timed_mutex mutex_;
    int value;
public:
    cls_eight() :value(0) {}

    int get() const{
        std::shared_lock<std::shared_timed_mutex> guard(mutex_);
        return value;
    }

    void increase() {
        std::unique_lock<std::shared_timed_mutex> guard(mutex_);
        value += 1;
    }
};

//----------------------- exchange
/*
new_value的值给了obj，而没有对new_value赋值
template<class T, class U = T>
constexpr T exchange(T& obj, U&& new_value) {
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}
*/

int main() {
    if (Switch&one){

        cout << func_one(2) << " " << func_one<double>(5.5) << endl;

    } else if (Switch&two){

        cout << func_two("hello world!") << " " << func_two("1024") << endl;

    } else if (Switch&three){

        cout << pi<int> << " " << pi<double> << endl;
        var_three<int> temp_three;
        temp_three.t = 10;
        temp_three.u = 20;
        cout << temp_three.t << " " << temp_three.u << endl;

    } else if (Switch&four){

        cout << factorial(5) << endl;
        cout << factorial_four(5) << endl;

    } else if (Switch&five){
        //var_five item;
        //cout << func_five() << endl;
    } else if (Switch&six){

        int a = 0b0001'0011'1010;
        double b = 3.14'1234'1234'1234;
        // 别忘了C++11的原生字符串

    } else if (Switch&seven){

        std::unique_ptr<int> ptr = std::make_unique<int>(5);
        cout << *ptr << endl;

    } else if (Switch&eight){

        cls_eight value_eight;
        value_eight.increase();
        cout << value_eight.get() << endl;

    } else if (Switch&ten){
        std::vector<int> items;
        std::vector<int> vec = {12,3,4,5};
        std::exchange(items, vec);
        for (int x : items) {
            cout << x << " ";
        }
        putchar('\n');
    }
    return  0;
}

// g++ -std=c++14  C++14语法糖.cpp; ./a.out