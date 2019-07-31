//实现引用计数
#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

class Hasptr{
    friend void swap(Hasptr &,Hasptr &);
    public:
        Hasptr(string &s):
        ps(new string(s)),i(0),use(new int(1)){}
        Hasptr(const Hasptr &ptr);
        Hasptr& operator=(const Hasptr &);
        bool operator<(Hasptr &);
        void swap(Hasptr &,Hasptr &);
        ~Hasptr();
    private:
        string *ps;
        int i;
        int *use;
};

bool Hasptr::operator<(Hasptr &a)
{
    cout << "asdasd\n";
    return *ps<*(a.ps);
}

void swap(Hasptr & a,Hasptr & b)
{
    using std::swap;
    cout << "进行swap\n";
    swap(a.ps,b.ps);
    swap(a.use,b.use);
    swap(a.i,b.i);
}

Hasptr::~Hasptr()
{
    if(--(*use)==0)
    {
        delete ps;
        delete use;
    }
}

Hasptr::Hasptr(const Hasptr &ptr)
{
    ps=ptr.ps;
    i=ptr.i;
    use=ptr.use;
    *use=++(*ptr.use);
}

Hasptr & Hasptr::operator=(const Hasptr &ptr)
{
    (*ptr.use)++;  //为了引用计数　复制运算符前面减　后面加
    if(--(*use)==0)
    {
        delete use;
        delete ps;
    }
    ps = ptr.ps;
    i = ptr.i;
    use=ptr.use;
    return *this;
}

int main()
{
    string a("bbb");
    string b("aaa");
    string c("asddasdasd");
    Hasptr hp1(a);
    Hasptr hp2(b);
    Hasptr hp3(c);
    vector<Hasptr>vec;
    vec.push_back(hp1);
    vec.push_back(hp2);
    vec.push_back(hp3);
    sort(vec.begin(),vec.end());
}