#include<bits/stdc++.h>
#include<tuple>
#include<variant>
using namespace std;

#define one       (1)         // 构造函数模板推导
#define two       (1<<2)      // 结构化绑定
#define three     (1<<3)      // if-switch语句初始化
#define four      (1<<4)      // 内联变量-->很有意思
#define five      (1<<5)      // 折叠表达式，constexpr lambda表达式，namespace嵌套
#define six       (1<<6)      // from_chars函数和to_chars 见其他文件
#define seven     (1<<7)      // std::variant
#define eight     (1<<8)      // std::optional
#define nine      (1<<9)      // std::any
#define ten       (1<<10)     // std::apply
#define eleven    (1<<11)     // std::make_from_tuple
#define twelve    (1<<12)     // std::string_view
#define thirteen  (1<<13)     // std::file_system
#define foutteen  (1<<14)     // 并行算法库


int Switch = twelve;

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

//----------------------- std::variant

struct NoDefConstr_seven{
    NoDefConstr_seven(int i){
        std::cout << "NoDefConstr::NoDefConstr(int) called\n";
    }
};

//----------------------- std::apply
int add_ten(int first, int second) { return first + second; }

auto add_ten_lambda = [](auto first, auto second) { return first + second; };

//----------------------- 
struct Foo_eleven {
    Foo_eleven(int first, float second, int third) {
        std::cout << first << ", " << second << ", " << third << "\n";
    }
};

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

    } else if (Switch&seven){
      /**
       * @ std::variant<> C++17
       * @ 可代替union
       * @ https://blog.csdn.net/janeqi1987/article/details/100568096
      */
      // variant类似于union，第一个参数必须拥有默认构造函数

      std::variant<int, std::string> var{"hi"}; // initialized with string alternative
      std::cout << var.index() << std::endl; // prints 1
      var = 42; // now holds int alternative
      std::cout << var.index() << std::endl; // prints 0
      try {
        std::string s = std::get<std::string>(var); // access by type
        int i = std::get<0>(var); // access by index
      }
      catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
        std::cout << "hello\n";
      }

      // std::variant<NoDefConstr_seven, int> v1; 第一个参数没有构造函数　编译失败
      // std::monostate就是防止全部的参数都没有默认构造函数
      std::variant<std::monostate, NoDefConstr_seven, int> v2;

    } else if (Switch&eight){
      // C++干货系列——C++17新特性之std::optional : https://zhuanlan.zhihu.com/p/251306766
      // 其实就是为了杜绝以前在返回值无效的时候返回的magic值

    } else if (Switch&nine){
      // 一般顶多variant就足够用了，何必用Any呢 但在极端情况下，用any总比用void*强得多
      // 鼓励实现避免小对象的动态分配
      std::any a = 1;
      cout << a.type().name() << " " << std::any_cast<int>(a) << endl;
      a = 2.2f;
      cout << a.type().name() << " " << std::any_cast<float>(a) << endl;
      if (a.has_value()) {
          cout << a.type().name() << std::endl;
      }
      a.reset();
      // 可以这样判断类型
      // assert(a1.type() == typeid(int));
      if (a.has_value()) {
          cout << a.type().name() << std::endl;
      }
      a = std::string("a");
      // 这个string的类型名是真的恶心
      cout << a.type().name() << ": " << std::any_cast<std::string>(a) << endl;
    
    } else if(Switch&ten){
      
      std::cout << std::apply(add_ten, std::pair(1, 2)) << '\n';
      //std::cout << add(std::pair(1, 2)) << "\n"; // error
      std::cout << std::apply(add_ten_lambda, std::tuple(2.2f, 3.0f)) << '\n';
    
    } else if(Switch&eleven){

      auto tuple = std::make_tuple(42, 3.14f, 0);
      std::make_from_tuple<Foo_eleven>(std::move(tuple));

    } else if(Switch&twelve){
      // string_view的substr与构造时间复杂度为O(1),且不会产生拷贝
      // substr只是一个指针操作
      // C++17,使用 string_view 来避免复制 https://blog.csdn.net/tkokof1/article/details/82527370?utm_source=blogxgwz3
      // C++17 string_view的高效以及陷阱 https://www.jianshu.com/p/1a5a4b3b2615

    } else if(Switch&foutteen){
      // 不仅仅是新加的七个 以前的stl算法也可以使用
      // [译]C++17,标准库新引入的并行算法 https://blog.csdn.net/tkokof1/article/details/82713700
      // STL并行算法库 https://blog.csdn.net/davidhopper/article/details/98309966
    }
}

// g++ -std=c++17  C++17特性一览.cpp; ./a.out