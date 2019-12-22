#include<bits/stdc++.h>
using namespace std;

//存在运行时期动态判断异常类型 可能会有性能上的损耗 且没写好程序还会直接挂机
//比较鸡肋的一个特性
//如果函数内抛出的异常不能够动态转换为声明的异常 那么会直接abort 
//如果可以街进行动态类型转换
void judge(int x) throw(std::bad_alloc) {
    if(x == 5) throw std::logic_error("hell world.");
}

template<typename T>
T See(T t){
    cout << t << endl;
    return T("asdasd");
}

int main(){
/*     try{
        while(true){
        int a = 5;
        cin >> a;
        judge(a);
        if(a == -1) break;
        }
    }catch(...){
        cout << "ok\n";
    } */
    string str = "sadasd";
    cout << See(str) << endl;
    auto x = make_shared<char*>(); //C++也可以像java一样进行类型推导
    cout << *x << endl;
}

/*
__THROW is meant to declare the function as capable of
throwing exceptions (a C++ feature). In C, the macro does nothing.
*/