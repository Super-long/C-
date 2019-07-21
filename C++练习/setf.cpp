#include<iostream>
using namespace std;
int main()
{
    int tmp=63;
    cout.setf(ios_base::showpos);
    cout << tmp << endl;

    cout << hex << tmp << endl;
    cout.setf(ios_base::uppercase);  //大写字母
    cout.setf(ios_base::showbase);  //十六进制前的0x
    cout << "or\n";
    cout << tmp << endl;
    bool he=true;
    cout.setf(ios_base::boolalpha);   //把布尔变量转化为true 或 false 
    cout << "how " << he << endl;
    cout << "how " << he << endl;
    return 0;
}