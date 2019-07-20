//成员模板类
//有什么作用？？？
#include<iostream>
using std::cout;
using std::cin;
using std::endl;

template<typename T>
class beta
{
    private:
        template<typename V>
            class hold
            {
                private:
                    V val;
                public:
                    hold(V v=0):val(v) {}    //初始化列表一般用括号来赋值
                    void show() const {cout << val << endl;}
                    V value() const {return val;}
            };
        hold<T> q;
        hold<int> n;
    public:
        beta(T t,int i):q(t),n(i){}
        template<typename U>
            U blab(U u,T t) {return (q.value()+n.value())*u/t;} //这个函数还是比较巧妙
        void show() const {q.show();n.show();}
};

int main()
{
    beta<double> guy(3.5,3);
    guy.show();
    guy.blab(10,2.3);
    guy.blab(10.0,2.3);     //返回值为参数中的第一个
    return 0;
}