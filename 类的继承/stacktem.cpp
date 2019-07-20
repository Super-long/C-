#include<iostream>
#include<string>
#include"stacktp.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    stack<string> st;
    char ch;
    string po;
    cout << "请输入A或者a来添加一个元素，Q或者q退出！\n";
    while(cin >> ch && std::toupper(ch)!='Q')
    {
        while(cin.get()!='\n')
            continue;
        if(!std::isalpha(ch))
        {
            cout << "请重新输入！";
            cout << '\a';
        }
        switch (ch)
        {
            case 'A':
            case 'a':
                cout << "请输入一个字符串!\n";
                //cin >> po;
                getline(cin,po);
    //使用getline更优 cin会丢失数据            
                if(st.isfull())
                {
                    cout << "栈已满!\n";
                }else
                {
                    st.push(po);
                }
                break;
            case 'p':
            case 'P':
                if(st.isempty())
                    cout << "栈已空!\n";
                else
                {
                    st.pop(po);
                    cout << po << " :popped!\n";
                }
        }
    cout << "请输入A或者a来添加一个元素，Q或者q退出！\n";
    }
    cout << "bye!\n";
    return 0;
}