#include<iostream>
#include<stdexcept>
using namespace std;
int main()
{
    int m,n;
    while(cin >> m >> n)
    {
        try{
            if(m+n<100)
            throw runtime_error("Data must up to 100");
            else 
            {
                cout << m+n << endl;
                break;
            }
        }catch(runtime_error errc)
        {
            cout << errc.what() 
            << "\nTry again,Enter y or n\n";
            char c('0');
            cin >> c;
            if(!cin || c=='n')
            break;
        }
    }
    return 0;
}