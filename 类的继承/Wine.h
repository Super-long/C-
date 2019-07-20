//公有继承 十四章练习题
//pair类的创建
#ifndef WINE_H_
#define WINE_H_ 
#include<string>
#include<iostream>
#include<valarray>
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::endl;

class Wine
{
    private:  
        typedef std::valarray<int> Arrayint;
        typedef pair<Arrayint,Arrayint> pairArray; 
        string name;
        pairArray data;  //包含
        int number;

    public:
        Wine(const char * s,int n,const int yr[],const int bot[]);
        Wine(const char *s,int n);
        void Getbottles();
        string & Label() {return name;}
        int sum() const;
        void show() const;
};

Wine::Wine(const char *s,int n,const int yr[],const int bot[])
{
    name = s;
    number = n;
    Arrayint a(n);
    Arrayint b(n);
    for(int i=0;i<n;i++)
    {
        a[i]=yr[i];
        b[i]=bot[i];
    }
    data=std::make_pair(a,b);
}

Wine::Wine(const char *s,int n)
{
    name = s;
    number = n;
    Arrayint a(n);
    Arrayint b(n);
    data = std::make_pair(a,b);
}

void Wine::Getbottles()
{
    cout << "enter " << name << "data for " << number << "year(s)\n";
    int i;
    for(i=0;i<number;i++)
    {
        cout << "Enter year:";
        cin >> data.first[i];
        cout << "Enter bottles for that year:";
        cin >> data.second[i];
    }
}

void Wine::show() const 
{
    cout << "Wine::" << name << endl;
    cout << "   year    bottles\n";
    for(int i=0;i<number;i++)
    {
        cout << "   "<<data.first[i]<<"   "<<data.second[i]<<endl;
    }
}

int Wine::sum() const
{
    int sum2=0;
    for(int i=0;i<number;i++)
    {
        sum2+=data.second[i];
    }
    return sum2;
}

#endif