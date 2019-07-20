#include"emp.h"
#include<string>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;

void abstr_emp::showAll()const
{
    cout <<"fname: "<< fname<<endl;
    cout <<"lname: "<< lname<<endl;
    cout <<"job:   "<< job  <<endl;
}

void abstr_emp::setAll()
{
    cout <<"please enter fname:";
    cin >> fname;
    cout <<"please enter lname:";
    cin >> lname;
    cout <<"please enter job:";
    cin >> job;
}

ostream &operator<<(ostream & os,const abstr_emp &ab)
{
    os << "fname:" << ab.fname<<endl;
    os << "lname:" << ab.lname<<endl;
    os << "job:  " << ab.job  <<endl;
}

abstr_emp::~abstr_emp(){}

manager::manager(const manager & man):abstr_emp((const abstr_emp &)man)
{
    inchargeof=man.inchargeof;
}
void manager::showAll()const
{
    abstr_emp::showAll();
    cout <<"Inchargerof"<<InChargeof()<<endl;
}

void manager::setAll()
{
    abstr_emp::setAll();
    cout <<"please enter inchargeof:";
    cin >> InChargeof();
}

fink::fink(const fink & f):abstr_emp((const abstr_emp &)f)
{
    reportsto=f.reportsto;
}
void fink::showAll()const
{
    abstr_emp::showAll();
    cout<<"ReportsTo"<<ReportsTo()<<endl;
}

void fink::setAll()
{
    abstr_emp::setAll();
    cout << "please enter reportsto:";
    cin >> ReportsTo();
}

void highfink::showAll() const
{
    abstr_emp::showAll();
    cout << ReportsTo();
    cout << InChargeof();
}

void highfink::setAll()
{
    abstr_emp::setAll();
    cout <<"please enter inchargeof:";
    cin >> InChargeof();
    cout << "please enter reportsto:";
    cin >> ReportsTo();
}

highfink::highfink(const manager & m,const string &s)
    :abstr_emp((const abstr_emp &)m),manager(m),fink((const abstr_emp &)m,s){}


highfink::highfink(const fink & f,const int in)
    :abstr_emp((const abstr_emp &)f),manager((const abstr_emp &)f,in),fink(f){}

highfink::highfink(const highfink & high):abstr_emp((const abstr_emp&)high),manager((const manager&)high),fink((const fink&)high){}