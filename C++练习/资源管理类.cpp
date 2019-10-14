/*工厂模式相对来说比较好维护　把所有工厂可以产出的资源放到一个命名空间中　
加一个限定作用域的枚举类型 利用类型和参数来返回相关的资源管理类　通常智能指针就好
但有时候要自己手写一个资源管理类*/
#include<bits/stdc++.h>
using namespace std;

class FactoryForInvestment{//写成嵌套类不好　不如放到一个命名空间里
    private:
        class investment{
            public:
                void show(){
                    cout << "hello world\n";
                }
        };
    public:
        FactoryForInvestment() = default;
        shared_ptr<investment> GetInvestment(){
            return make_shared<investment>();//RVO优化
        }
};

int main(){
    FactoryForInvestment temp;
    auto T = temp.GetInvestment();//可以写成一个泛型函数　其中加一个完美转发
    T->show();
    return 0;
}