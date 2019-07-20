#include<iostream>
#include"arraytp.h"

using std::cout;
using std::cin;
using std::endl;
int main()
{
    Arraytp<int,10> sums;
    Arraytp<double,10> aves;
    Arraytp<Arraytp<int,5>,10> twodee;
    for(int i=1;i<=10;i++)
    {
        sums[i]=0;
        for(int j=1;j<=5;j++)
        {
            twodee[i][j]=i*j;
            sums[i]+=twodee[i][j];
        }
        aves[i]=(double)sums[i]/10;
    }
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=5;j++)
        {
            cout.width(2);
            cout << twodee[i][j] << " ";
        }
        cout << ":sum=";
        cout.width(2);
        cout << sums[i] << ": average=" << aves[i] << endl;
    }
    cout << "dones!\n";
    return 0;
}