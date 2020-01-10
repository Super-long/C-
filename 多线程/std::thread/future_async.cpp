#include<bits/stdc++.h>
using namespace std;

struct x{
    void foo(int , string str){
        cout << "foo\n";
    }
    string bar(const string&){
        cout << "bar\n";
        return "bar";
    }
};

string test(const string& str){
    cout << str << endl;
    return str;
}

int main(){
    x X;                        //在这里参数设置为X,或者&X都可 无非是调用方法不一样罢了
    //参数若是右值 就会移动原来的参数构建副本来调用函数 
    //auto f1 = std::async(&x::foo, X, 40, "one"); 
    //auto f2 = std::async(&x::bar, X, "two"); //自动推断成future

    std::packaged_task<decltype(test)> T(test);
    T("hello");
    auto TT = T.get_future();
    cout << TT.get() << endl; //返回值会使得内部的值失效 因为get实现中对值调用了std::move

/*     cout << "running\n";
    cout << f2.get() << endl; */
}
