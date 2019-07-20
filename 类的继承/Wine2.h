//十四章练习题 私有继承
#ifndef WINE2_H_
#define WINE2_H_

#include<iostream>
#include<string>
#include<valarray>
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef std::valarray<int> Arrayint;
typedef pair<Arrayint,Arrayint> pairArray;

class Wine2 :private string,private pairArray
{
    private:
        int number;
    public:
        Wine2() {};
        Wine2(const char *,int,const int yr[],const int bot[]);
        Wine2(const char *,int);
        void Getbottles();
        string & Label();
        int sum() const;
        void show() const;
};

Wine2::Wine2(const char *s,int n,const int yr[],const int bot[])
:string(s),number(n),pairArray(Arrayint(yr,n),Arrayint(bot,n))
{}

Wine2::Wine2(const char *s,int n)
:string(s),number(n)
{}

void Wine2::Getbottles()
{
    Arrayint a(number);
    Arrayint b(number);
    cout << "enter " << (const string &)*this << "data for " << number << "year(s)\n";
    int i;
    for(i=0;i<number;i++)
    {
        cout << "Enter year:";
        cin >> a[i];
        cout << "Enter bottles for that year:";
        cin >> b[i];
    }
    (pairArray &)*this=std::make_pair(a,b);
    //这里刚开始没有加& 在82行出现段错误 这个bug找了很久，，
    //大家引以为戒 注意强制转换加&与不加是不一样的 加上是对本身做改变 
    //不加就是创建一个临时对象 对其做操作 
}

string & Wine2::Label()
{
    return (string &)*this;
}

int Wine2::sum() const
{
    int sum_all=0;
    for(int i=0;i<number;i++)
    {
        //sum_all+=(pairArray)*this.second[i];
        sum_all+=pairArray::second[i];
        //在这里pairArray相当于一个类 second相当于一个方法 
        //使用作用域解析运算符
    }
    return sum_all;
}

/* typedef std::valarray<int> Arrayint;
typedef pair<Arrayint,Arrayint> pairArray; */
void Wine2::show() const
{
    cout << "Wine::" << (string)*this << endl;
    cout << "   year    bottles\n";
    for(int i=0;i<number;i++)
    {
        cout << "   "<<pairArray::first[i]<<"  " << pairArray::second[i]<< endl;
    }
}                                                                                                                    

#endif

//需要注意的地方要使用某个对象要进行强制类型转换 例：string
//要调用函数需要进行作用域解析运算符 例：first