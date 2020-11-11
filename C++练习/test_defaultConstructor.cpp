#include <bits/stdc++.h>
using namespace std;

class Foo {
    public:
        Foo(){
            cout << "hello\n";
        }

        explicit Foo(const Foo & fo){
            cout << "koabei\n";
        }

};

class Bar{
    public:
        Bar(){
            //one = 1024;
        }
        void show(){
            cout << one << endl;
        }
    private:
        Foo two;
        int one;    // 默认构造函数不会初始化整数，指针，数组这些东西的，值完全是随机的
};

int main(){
    Bar one;
    one.show();
    Bar two(one);
    Bar three = Bar(one);
    return 0;
}