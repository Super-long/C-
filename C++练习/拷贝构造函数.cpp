#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

class Hasptr{
    public:
        Hasptr(string &s):
        ps(new string(s)),i(0){}
        Hasptr(const Hasptr &ptr):
        ps(new string(*ptr.ps)),i(ptr.i){}
        Hasptr & operator=(Hasptr &);
        ~Hasptr(){delete ps;}
    private:
        string *ps;
        int i;
};

Hasptr & Hasptr::operator=(Hasptr &ptr)
{
    ps = new string(*ptr.ps);
    i = ptr.i;
}