#include<iostream>
#include<string>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

struct xyc{
    int x=0;
    int y=0;
    char c=' ';
};

template<unsigned N,unsigned M>
class Screen{
    unsigned cursor=0;
    unsigned width=N;
    unsigned height=M;
    string contest;
    public:
        Screen() = default;
        explicit Screen(char c):contest(N*M,c){} //防止隐性转换
        char get() {return contest[cursor];}
        Screen set(xyc &c) {
            cursor=--c.x*width + --c.y;
            contest[cursor]=c.c;
            return *this;
        }
        template<unsigned NN,unsigned MM>//编译器推导 切记模板参数不能重用
        friend ostream& operator<<(ostream &os,const Screen<NN,MM>&s);
        template<unsigned NN,unsigned MM>
        friend istream& operator>>(istream &is,const Screen<NN,MM>&s);
};

template<unsigned N,unsigned M>
ostream& operator<<(ostream &os,const Screen<N,M>&s)
{
    for(unsigned i=0;i<s.width;i++)
    {
        for(unsigned j=0;j<s.height;j++)
            putchar(s.contest[i*s.width+j]);
        putchar('\n');
    }
    return os;//流对象无法被拷贝
}

template<unsigned N,unsigned M>
istream& operator>>(istream &is,Screen<N,M>&s)//第一次输入重定向竟然写了const tcl
{
    xyc c;
    is >> c.x >> c.y >> c.c;
    s.set(c);
    return is;
}

int main()
{
    Screen<6,6> str('-');
    cout << str << endl;
    cin >> str;
    cout << str;
    return 0;
}