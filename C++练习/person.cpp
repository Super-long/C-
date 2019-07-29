#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
#include<fstream>
using namespace std;

class person
{
    private:
        string name;
        string address;
    public:
        static int back;
        person() =default;
        person(string &a,string &b):name(a),address(b){}
        person(istream &is){write(is,*this);}
        person(string &a):name(a),address(" "){}
        string get_name(){return name;}
        string get_address(){return address;}
        istream &write(istream & is,person &data1);     //这两个函数当然也可以写成友元
        ostream &read(ostream & os,person &data2) const;
};
ostream &person::read(ostream & os,person &data2) const
{
    os << data2.name << endl;    
    os << data2.address << endl;
    return os;
}

istream &person::write(istream &is,person &data1)
{
    is >> data1.name;
    is >> data1.address;
    return is;
}
int person::back=5;
int main()
{
    string aa="asdasdasd";
    person dd=aa;
    person a(aa);
    a.back++;
    a.back++;
    cout << person::back << endl;
}