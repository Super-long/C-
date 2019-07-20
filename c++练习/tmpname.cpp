#include<cstdio>
#include<iostream>

int main()
{
    using namespace std;
    char name[TMP_MAX]={"temp-XXXXXX"};
    for(int i=0;i<10;i++)
    {
        mkstemp(name);
        //tmpnam(name);
        cout << name << endl;
    }
    return 0;
}