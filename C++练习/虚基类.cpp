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
    class tmpa{
        public:
        int tmpaa = 0;
    };
    class tmpb : public tmpa{
        public:
        int tmpbb = 1;
    };
}
namespace hello = VMI;//hello是VMI的命名空间别名 
int main(){
    //未命名的命名空间中
    //需要加限定符　foo cval
    //不需要限定符　bar ival
    using VMI::tmpa;
    using VMI::tmpb;
    try{
        throw VMI::tmpb();
    }catch(tmpa &err){//就算是引用也只能使用静态绑定的类型
        cout << err.tmpaa << endl;
    }
}