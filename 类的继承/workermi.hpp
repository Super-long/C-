#include"workermi.h"
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
worker::~worker(){}

void worker::data()const
{
    cout << "name:" << fullname << endl;
    cout << "id:" << id << endl;
}

void worker::get()
{
    getline(cin,fullname);
    cout <<"please enter id:\n";
    cin >> id;
}

void waiter::get()
{
    cout <<"enter panache:\n";
    cin >> panache;
    while(cin.get() != '\n')
    continue;
}

void waiter::data()const
{
    cout << "panache :\n" << panache <<endl;
}

void waiter::set()
{
    cout <<"please enter fullname:\n";
    worker::get();
    get();
}

void waiter::show() const
{
    cout <<"Category:waiter:\n";
    worker::data();
    data();
}

char * singer::pv[singer::Vtypes] =
{
    "other","alto","contralta","sprano",
    "bass","baritone","teror"
};

void singer::data()const
{
    cout << "voice:\n" << voice << endl;
}

void singer::get()
{
    cout << "enter the number of singer's range\n";
    for(int i=0;i<Vtypes;i++)
    {
        cout << i <<":"<< pv[i] << endl;
    }
    cin >> voice;
    while(cin.get()!='\n')
    continue;
}

void singer::set()
{
    cout << "please enter fullname:\n";
    worker::get();
    get();
}

void singer::show()const
{
    cout <<"category singer:\n";
    worker::data();
    data();
}

void singingwaiter::data()const
{
    singer::data();
    waiter::data();
}

void singingwaiter::get()
{
    singer::get();
    waiter::get();
}

void singingwaiter::set()
{
    cout << "enter fullname:\n";
    worker::get();
    get();
}

void singingwaiter::show()const
{
    cout << "category:singingwaiter:\n";
    worker::data();
    data();
}