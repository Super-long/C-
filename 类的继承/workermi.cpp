#include"workermi.h"
#include"workermi.hpp"
#include<iostream>
#include<cstring>
const int size=5;

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    //using std::strchr;

    worker * lolas[size];
    int ct;
    for(ct=0;ct<size;ct++)
    {
        char choice;
        cout << "Enter the employee category:"
        << "w: waiter\ns: singer\nt: singing waiter"
        << "\nq to quit";
        cin >> choice;
        while(strchr("wstq",choice)==NULL)
        {
            while(cin.get()!='\n')
                continue;
            cout <<"please enter w,s,t,q:\n";
            cin >> choice;
        }
        if(choice=='q') break;
        switch(choice)
        {
            case'w':
                lolas[ct]=new waiter;
                break;
            case's':
                lolas[ct]=new singer;
                break;
            case't':
                lolas[ct]=new singingwaiter;
                break;
        }
        cin.get();
        lolas[ct]->set();
        //使用虚基类的好处 
    }

    cout <<"here's your staff:\n";
    for(int i=0;i<ct;i++)
    {
        cout << endl;
        lolas[i]->show();
    }
    for(int i=0;i<ct;i++)
    {
        delete lolas[i];
    }
    cout << "Bye.\n";
    return 0;
}