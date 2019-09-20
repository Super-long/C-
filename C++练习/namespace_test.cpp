#include<iostream>
#include<string>

/* namespace primer{
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}

int ivar = 0;
//using namespace primer;
void manip(){
    //using namespace primer;
    double dvar = 3.14159265;
    int lobj = limit + 1;
    ++ivar;
    ++::ivar;
}
 */
namespace primer{
    using std::cout;
    class C{
        public:
            friend void f2();//认为是最近的命名空间成员
            friend void f(const C&);
            C() = default;
            void ma() {cout << "hello world\n";}
    };
    void f2(){cout << "f2()\n";}
    void f(const C&){cout << "f()\n";}
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}

/* using primer::dvar;
using primer::ivar;
using primer::limit; */

int ivar = 0;
//using namespace primer;
void manip(){
    //using primer::dvar;
    using primer::ivar;
    using primer::limit;
    //using namespace primer;
    double dvar = 3.14159265;
    int lobj = limit + 1;
    ++ivar;
    ++::ivar;
}

int main(){
    std::string str;
    std::cin >> str;
    operator>>(std::cin,str);
    operator<<(std::cout,str);//operator不用加std::的原因是在参数中不仅会查找类作用域                       
                              //还会查找命名空间作用域
    primer::C tmp;
    primer::C tmpa;
    f(tmpa);
    primer::f2();//没有参数　无法根据参数来确定命名空间
    return 0;
}