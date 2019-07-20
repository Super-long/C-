#include<iostream>
#include<cstring>
#include"QueueTp.h"
#include"workermi.h"
#include"workermi.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;

const int len=10;
QueueTp<worker *> que(len);

int main()
{
    char ch;
    for(int i=0;i<len;i++)
    {
        cout <<"w:waiter s:singer t:ingingwaiter\n"
            <<"q to quit."<<endl;
        cin >> ch;
        while(std::strchr("wstq",ch)==NULL)
        cout <<"please enter w s t q!\n";
        if(ch=='q') break;
        switch (ch)
        {
            case 'w':
                que.push(new waiter);
                break;
            case 's':
                que.push(new singer);
                break;
            case 't':
                que.push(new singingwaiter);
                break;
        }
        while(cin.get()!='\n')
        cin.get();
        que.rear()->set();  //传入的是指针
    }
    for(int i=0;i<que.size();i++)
    {
        que.front()->show();
        que.push(que.front());
        que.pop();
        cout << endl;
    }
    for(int i=0;i<len;i++)
    {
        delete que.front();
        que.pop();
    }
    return 0;
}