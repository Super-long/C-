//200 10 -50 123z 60 这道题的输入 
#include<iostream>
using namespace std;
int main()
{
    int sum=0;
    int input;
    while(cin >> input)
    {
        sum+=input;
    }
    cin.clear();
    cin >> input;
    cout << input << endl;
    cout << sum << endl;
    return 0;
}