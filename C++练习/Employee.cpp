#include<iostream>
#include<string>
using namespace std;

class one
{
    public:
        static int number;
        one():t_number(++number),name("null"){}
        one(const string &tmp);
        one(const one &);
    private:
        int t_number;
        string name;
};
int one::number=0;
one::one(const string &tmp)
{
    t_number=(++number);
    name=tmp;
}

one::one(const one & tmp)
{
    t_number=(++number);
    name=tmp.name;
}

int main()
{
    one aa;
    one bb;
    cout << aa.number << endl;
    cout << bb.number << endl;
}