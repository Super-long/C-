#include"studenti.h"
using std::ostream;
using std::istream;
using std::string;
using std::endl;

double student::avarage()const
{
    if(ArrayDb::size()>0)
        return ArrayDb::sum()/ArrayDb::size();
    else
        return 0;
}
//这个函数需要注意 对于对象方法的引用

double & student::operator[](int n)
{
    //return ArrayDb[n];
    //这样会陷入无限递归
    return ArrayDb::operator[](n);
}

double student::operator[](int n) const
{
    return ArrayDb::operator[](n);
}

const string & student::Name()const
{
    return (const string &)*this;
    //这种方法要记住
}

istream & getline(istream & is,student & stu)
{
    getline(is,(string &)stu);
    return is;
}

istream & operator>>(istream &is,student & stu)
{
    is >> (string &)stu;
    return is;
}

ostream & student::arr_out(ostream &os)const
{
    int len=ArrayDb::size();
    if(len>0)
    {
        for(int i=0;i<len;i++)
        {
            os << ArrayDb::operator[](i) <<"";
            if(i%5!=4)
            os << endl;
        }
    }
    else
        os<<"empty array!\n";
    return os;
}

ostream & operator<<(ostream &os,student & stu)
{

    os << "scores :" << (string &)stu << endl;
    stu.arr_out(os);
    return os;
}