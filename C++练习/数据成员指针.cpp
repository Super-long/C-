//类成员指针
#include<iostream>
using namespace std;

class Hank{
    public:
        static const int Hank::*data(){
            //因为要使用的数据一般来说都是私有的　所以要使用一个静态公有函数返回成员指针
            return &Hank::tmpb;
        }
        void show(int a,int b)const{cout << "two\n"<<tmpa << endl;;}
        void show(int a)const{cout << "one\n";}
        void play(){cout << "three\n";}
    private:
        int tmpa = 0;
        int tmpb;
};

int main(){
    const int Hank::*pdata = Hank::data();//对于私有成员　使用一个静态函数来返回一个成员指证
    auto x = Hank::data(); //两种方法都可以　这时只是一个指针　还未指向一个实体
    cout << x << endl;//把p不看成一个指针而是看做一个“偏移量” 其值并不会指向一个地址
    Hank hello,*world = &hello;
    cout << world->*pdata << endl;
    cout << hello.*pdata << endl;

    using Action = void (Hank::*)(int)const;//类型名称较长的时候使用一个using创建一个别名
    void (Hank::*tmp)(int,int)const;
    tmp = &Hank::show;
    Action temp = &Hank::show;

    auto x = &Hank::play; //函数重载时不可以

    (hello.*temp)(0);
    (hello.*tmp)(0,0);//调用函数 
    //加括号的原因是因为　()运算符的优先级高于指针指向成员运算符

    //调用函数的时候参数还是隐式的传入了一个this指针　因为函数中还是可以使用私有成员
    return 0;
}