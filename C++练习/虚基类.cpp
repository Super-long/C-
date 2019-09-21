#include<memory>
#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

namespace{
    struct Base
    {
            void bar(int);
        protected:
            int ival;
    };

    struct Der1 : virtual public Base{
            void bar(char);
            void foo(char);
        protected:
            char cval;
    };

    struct Der2 : virtual public Base{
            void foo(int);
        protected:
            int ival;
            char cval;
    };

    class VMI_class : public Der1,public Der2{
    };
}

namespace VMI{

}

int main(){
    //未命名的命名空间中
    //需要加限定符　foo cval
    //不需要限定符　bar ival
}