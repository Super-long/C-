#include<iostream>
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    char ch;
    while(cin.peek()!='#')
    {
        cin.get(ch);
        cout << ch;
    }if(!cin.eof())
    {
        cin.get(ch);
        cout<<endl<<ch<<" is next input\n";
    }else
    {
        cout<<"end of file reached.";
    }
    return 0;
}