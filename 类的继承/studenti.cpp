#include<iostream>
#include"studenti.h"
#include"studenti.hpp"

using std::cin;
using std::cout;
using std::endl;

void set(student & sa,int n);

const int pupils = 3;
const int quizzes = 5;

int main()
{
    student ad[pupils]=
    {student(quizzes),student(quizzes),student(quizzes)};
    for(int i=0;i<pupils;i++)
    {
        set(ad[i],quizzes);
    }
    for(int i=0;i<pupils;i++)
    {
        cout << ad[i].Name() << endl;
    }
    for(int i=0;i<pupils;i++)
    {
        cout << ad[i] << endl;
        cout << ad[i].avarage() << endl;
    }
    return 0;
}
void set(student & sa,int n)
{
    cout << "please enter your name\n";
    getline(cin,sa);
    cout << "please enter" << n << "scores\n";
    for(int i=0 ;i<n; i++)
    {
        cin >> sa[i];
    }
    while(cin.get()!='\n')
        continue;
}