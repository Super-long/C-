#include<vector>
#include<tuple>
#include<iostream>
#include<variant>

#include<bits/stdc++.h>

using namespace std;

pair<int, string> get_record(){
    return pair(0,"asdasd");
}

auto get_record2(){
    return std::tuple(1, 2, 3);
}//自动推导函数返回值类型 C++14

/**
 * @ 非类型模板参数的自动推导 C++17
*/  
template<auto value>
void foo(){
    cout << value << endl;
}

struct nodef{
    nodef() = delete;
};

int main(){
    //vector x = {1,2,3}; //模板类型推导 C++17
    //auto x = get_record2();

    auto[id1, id2, id3] = get_record2();//结构化绑定 C++17
    map<int, string> Table = {{1 , "one"},
                            {2, "two"},
                            {3, "three"},
                            {4, "four"}};
    for(const auto& [one, two] : Table){//结构化绑定 C++17
        cout << one << " " << two << endl;
    }

    cout << id1 << " " << id2 << " " << id3 << endl;
    //auto T = get<0>(x);
    //auto TT = get<1>(x);
    //cout << T << " " << TT << endl;

    /**
     * @ 选择语句中的初始化器 C++17
     * @ 下面两种写法是一样的
    */
    int i = 0;
    if(i ==0){
        cout << "hello\n";
    }
    cout << i << endl;

    if(int i = 0; i == 0){
        cout << "hello\n";
    }
    cout << i << endl;

   foo<10>();

    /**
     * @ std::variant<> C++17
     * @ 可代替union
     * @ https://blog.csdn.net/janeqi1987/article/details/100568096
    */
    std::variant<string, int, short> var{"hi"}; //如果其中类型没有默认构造函数则会出错
    std::cout << var.index() << endl; //查明当前设置了哪一个选项
    var = 20;
    cout << var.index() << endl; 
    cout << get<short>(var) << endl;//当像这样取不匹配的值的时候会抛错
    //get_if<>() 会返回指针 错误会返回nullptr

/*     std::variant<nodef, int> vl = 1;
    //monostate避免的情况就是variant中元素均无法默认初始化 是一个helper类
    std::variant<monostate, nodef> vll;

    if (std::holds_alternative<std::monostate>(vll)) 
    {//可检查是否存在monostate
        std::cout << "has monostate\n";
    }
    cout << vl.index() << endl; */

    return 0;
}

//编译用这个 g++ -std=c++17 xxx