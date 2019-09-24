#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

namespace Test_typeid{
    class Base{
        public:
            virtual void show(){cout << "show in base\n";} 
    };
    class Der : public Base{
        public:
            void show() override {cout << "show in Der\n";}
    };

    class Base1{
        public:
            void show(){cout << "show in base\n";} 
    };
    class Der1 : public Base1{
        public:
            void show(){cout << "show in Der\n";}
    };
}

int main(){
    using namespace Test_typeid;
    Der *dp = new Der;
    Base *bp = dp;

    if(typeid(*bp) == typeid(*dp)){
        cout << "ok\n";
    }
    if(typeid(*bp) == typeid(Der)){
        cout << "hello\n";
    }

    Der1 *ddp = new Der1; //无虚函数　指示对象的静态对象
    Base1 *bdp = ddp;

    if(typeid(*bdp) == typeid(*ddp)){
        cout << "ok\n";
    }
    if(typeid(*bdp) == typeid(Der1)){
        cout << "hello\n";
    }
    
    Der1 tmpa;
    Base1 &tmpb = dynamic_cast<Base1&>(tmpa);
    return 0;
}

/*输出为
ok
hello
*/