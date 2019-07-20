#include"Wine.h"
#include<iostream>

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

    Wine holding(lab,yrs);
    holding.Getbottles();
    holding.show();

    const int YRS=3;
    int y[YRS]={1993,1995,1998};
    int b[YRS]={48,60,72};
    Wine more("Gushing Grape Red",YRS,y,b);
    more.show();
    cout <<"Total bottles for "<< more.Label()
    <<": " << more.sum() << endl;
    cout << "Bye!\n";
    return 0;
}