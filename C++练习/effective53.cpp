#include<bits/stdc++.h>
using namespace std;

class A{
    public:
        explicit A(int x) : a(x){}
        virtual void show() const{
            cout << a << endl;
        }
    private:
        int a;
};

class B : public A{
    public:
        B(int aa, int bb) : a(aa), A(bb){}
        virtual void show() const{ //不加const为什么不报警告呢  
        //但是确实掩盖了A中的函数 这种bug放到实际中得暴毙
            cout << a << endl;
        }
    private:
        int a,b;
};

int main(){
    B temp(1,2);
    temp.show();
    A& a = temp;
    a.show();
    return 0;
}