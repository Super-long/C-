/*这个文件存在的意义就是随便写 什么不清楚就敲什么*/




#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

template <typename T> class show;
template<typename T>
class Sort
{
    template <typename X> friend class show; //声明友元所需要的
    friend T;
    private:
        shared_ptr<vector<T>>vec;
    public:
        Sort() = default;
        Sort(initializer_list<T>il):vec(make_shared<vector<T>>(il)){}
        template<typename D>
        void operator()(D *p){
            delete p;
        }
        void ok(){
            sort(vec->begin(),vec->end());
        }
        static T sta;
};

template <typename T>
T Sort<T>::sta = 10; //静态变量要这样赋值

template<typename X>
class show{
    public:
        show() = default;
        void ok(Sort<X> &tmp){
            for(auto x: *(tmp.vec))
            cout << x << endl;
        }
};

template <typename T> using twin = Sort<T>; //模板别名

template<typename D, unsigned H>
int mp(D && x) //函数类型的非模板参数的调用方式比较奇怪 在main函数里面第一句
{
    return x+H;
}

char judge(char ch)
{
    if(ch>='A' && ch<='Z')
    return ch+32;
    return ch;
}

int main()
{
    cout << mp<int,5>(1) << endl;

    string first,second;
    first = "hello";
    second.resize(7);  //如果小于当前元素数量 元素会被截断
    vector<char> ddd(10);
    transform(first.begin(),first.end(),ddd.begin(),judge);
    cout << ddd[0] << endl; //这个也可以实现不同容器间的赋值

    vector<char>vecc;
    vecc.assign(second.begin(),second.end());
    cout << vecc[2] << endl; //实现不同容器间的拷贝

    Sort<char> tmpa({'s','d','d'});
    show<char> aa;
    tmpa.ok();
    aa.ok(tmpa);
    //自定义一个删除器
    unique_ptr<int,Sort<int>> tmpb(new int,Sort<int>({1,2,3}));
    //第二个参数是提供一个实例的对象 以前一直以为是函数， 
}