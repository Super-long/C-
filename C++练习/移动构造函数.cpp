#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

class Str{
    public:
        char *str;
        Str(char value[])
        {
            cout<<"普通构造函数..."<<endl;
            str = NULL;
            int len = strlen(value);
            str = (char *)malloc(len + 1);
            memset(str,0,len + 1);
            strcpy(str,value);
        }
        Str(const Str &s)
        {
            cout<<"拷贝构造函数..."<<endl;
            str = NULL;
            int len = strlen(s.str);
            str = (char *)malloc(len + 1);
            memset(str,0,len + 1);
            strcpy(str,s.str);
        }
        Str(Str &&s)
        {
            cout<<"移动构造函数..."<<endl;
            str = NULL;
            str = s.str;
            s.str = NULL;
        }
        ~Str()
        {
            cout<<"析构函数"<<endl;
            if(str != NULL)
            {
                free(str);
                str = NULL;
            }
        }
};
int main()
{
    char value[] = "I love zx";
    Str s(value);//对象仍旧存在　但是值已经在vector中
    vector<Str> vs;
    //vs.push_back(move(s));//左值转换成右值
    vs.push_back(s);
    cout<<vs[0].str<<endl;
    if(s.str != NULL)
        cout<<s.str<<endl;
    return 0;
} 