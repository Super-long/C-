#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
//这也算个简易的智能指针了吧
class Hasptr
{
    public:
        Hasptr(const string &a = string()):
        use(new size_t(1)),i(0),ps(new string(a)){}

        Hasptr(const Hasptr &p):
        ps(p.ps),i(p.i),use(p.use){++*use;}

        void show(){cout << *use << endl;}

        Hasptr & operator=(const Hasptr &a){
            ++*a.use;//防止自赋值
            if(--*use==0){
                delete ps;
                delete use;
            }
            i=a.i;
            ps=a.ps;
            use=a.use;
            return *this;
        }
        ~Hasptr(){
            if(--*use==0)//递减很重要
            {
                delete use;
                delete ps;
            }
        }
    private:
        size_t *use;
        int i;
        string *ps;
};

int main()
{
    Hasptr tmpa;
    tmpa.show();
    Hasptr tmpb;
    tmpb.show();
    Hasptr tmpc("hello");
    tmpc.show();
    tmpc=tmpb;
    tmpc.show();
    return 0;
}