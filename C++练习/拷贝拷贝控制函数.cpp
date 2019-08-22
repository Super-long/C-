#include<iostream>
using namespace std;
class tmp
{
    public:
        static int dd;
        tmp():tt(++dd){}
        int show()const {return tt;}
        tmp(const tmp &a){
            cout << ":" << a.tt << endl;
            this->tt=++dd;
        }
    private:
        int tt;
};
int tmp::dd=0;
void f(const tmp &a){cout << a.show() << endl;}
//void f(tmp a) {cout << a.show() << endl;} 这种写法会触发复制构造函数　函数中就成了副本　所以输出　４　５　６　
int main()
{
    tmp a,b=a,c=a;
    f(a);f(b);f(c); 
    return 0;
}