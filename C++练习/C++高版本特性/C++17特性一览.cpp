#include<bits/stdc++.h>
#include<tuple>
using namespace std;

#define one     (1)         // 构造函数模板推导
#define two     (1<<2)      // 结构化绑定
#define three   (1<<3)      // if-switch语句初始化
#define four    (1<<4)      // 内联变量-->很有意思
#define five    (1<<5)      // 折叠表达式，constexpr lambda表达式，namespace嵌套
#define six     (1<<6)      // 
#define seven   (1<<7)      // 
#define eight   (1<<8)      // 
#define nine    (1<<9)      // 
#define ten     (1<<10)     // 

int Switch = five;

//----------------------- 结构化绑定
std::tuple<int, double> func_two() {
    return std::tuple(1, 2.2);
}

//----------------------- 折叠表达式
// TODO 下去再看看模板的可变参(...)
template <typename ... Ts> 
constexpr auto func_five(Ts... ts) {
    return (ts + ...);
}

//----------------------- namespace嵌套
/* namespace A {
    namespace B {
        namespace C {
            void func();
        }
    }
}

// c++17，更方便更舒适
namespace A::B::C {
    void func();
} */


int main() {
    if (Switch&one){
      // 叫模板自动推导好一点
      vector items = {1,2,3};
      // pair pa(4, "string"); 不直接匹配字符串
      pair pa(4, string("hihi"));
      cout << pa.second << " " << items[2] << endl;

    } else if (Switch&two){
      // 可以绑定pair，tuple，数组，结构体
      // 结构化绑定以后也可以修改原值
      // 也可以自定义类的结构化绑定，但是要修改std，感觉没什么必要
      auto[i, d] = func_two();
      cout << i << " " << d << endl;

      map<int, string> mp = {
        {0, "a"},
        {1, "b"},
      };

      for(const auto& [x, y] : mp){
        cout << x << " " << y << endl;
      }

      pair pa(4, string("hihi"));
      auto&[x, y] = pa;
      cout << x << " " << y << endl;

/*       vector vec = {1,2,3};
      auto&[xx, yy, zz] = vec;
      cout << xx << endl; */

    } else if (Switch&three){
      // if (init; condition) 可以让我们在括号内初始化条件 省个变量名称
      if (int a = 29; a < 101) {
          cout << a;
      }
      // cout << a << endl; 处于作用域之外了
    } else if (Switch&four){
      /*多个翻译单元的定义最终只保留一个，保证是相同的*/
      /*所以用inline修饰以后，许多以前不能在头文件定义的东西，可以写在头文件里了*/
      // TODO 下去需要仔细琢磨
    } else if (Switch&five){

      constexpr int item = func_five(1,2,3,4,5);
      string a = "hello ";
      string b = "world";
      cout << item << " " << func_five(a, b) << endl;

      // constexpr lambda 表达式
      constexpr auto lamb = [](auto b) {
          int ret = 0;  // C++14中放宽了lambda的标准
          for (size_t i = 0; i < b; i++){
              ret += i;
          }
          return ret;
      };
      cout << lamb(5) << endl;

      // constexpr有以下限制
      /*
        函数体不能包含汇编语句、goto语句、label、try块、
        静态变量、线程局部存储、没有初始化的普通变量，不能
        动态分配内存，不能有new delete等，不能虚函数
      */

    } else if (Switch&six){

    } else if (Switch&seven){

    } else if (Switch&eight){

    } else if (Switch&ten){

    }
}

// g++ -std=c++17  C++17特性一览.cpp; ./a.out