#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>
using namespace std;
class Quote
{
    public:
        Quote() = default;
        Quote(const Quote&){
            cout << "ok\n";
        }
        Quote(Quote &&) = default;//定义移动操作时 拷贝与赋值被定义为删除的
        virtual ~Quote() = default;//当定义虚析构时 移动只是没有合成 但可以合成
        virtual void show(){
            cout << str << endl;
        }
    private:
        const int str = 5;
};

struct tmp : Quote {
    public:
        using Quote::show;
        tmp() = default;
        tmp(const tmp&a) : Quote(a){cout << "gouzao\n";}
        tmp(tmp &&) = default;
/*         void show() override{
            cout << "hello\n";
        }; */
        void show(int a){
            cout << "show a :" << a << endl;
        }
};
vector<tmp>vec;
int main()
{
    tmp temp;
    tmp aa(temp);
    vec.push_back(std::move(temp));//当注销掉移动构造函数时 push_back使用拷贝构造函数
    temp.show();
    temp.show(5);
    temp.Quote::show(); //这样可以强制使用某个版本的虚函数 因为基类子对象也是派生类的一部分
    return 0;
} 