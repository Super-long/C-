#include"Wine2.h"
#include<iostream>
//其实这部分与第一道题相同 因为接口相同
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    cout << "enter name of wine:";
    char lab[50];
    cin.getline(lab,50);
    cout << "enter number of year:";
    int yrs;
    cin >> yrs;          //输入阶段

    Wine2 holding(lab,yrs);
    holding.Getbottles();
    holding.show();

    const int YRS=3;
    int y[YRS]={1993,1995,1998};
    int b[YRS]={48,60,72};
    Wine2 more("Gushing Grape Red",YRS,y,b);
    more.show();
    cout <<"Total bottles for "<< more.Label()
    <<": " << more.sum() << endl;
    cout << "Bye!\n";
    return 0;
}