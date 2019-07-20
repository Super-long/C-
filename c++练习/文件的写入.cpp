#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

const char *file = "test.cpp";
int main()
{
    using namespace std;
    char ch;
    ifstream fin(file);
    if(fin.is_open())
    {
        cout << "Here are the current contents of thr "<<file <<":\n";
        while(fin.get(ch))
        cout << ch;
        fin.close();
    }

    ofstream fout(file,ios_base::out|ios_base::app);
    if(!fout.is_open())
    {
        cout << "Can't open the "<<file << endl;
        exit(EXIT_FAILURE);
    }
    cout << "\nPlease enter the new names:\n";
    string name;
    while(getline(cin,name) && name.size()>0)
    {
        fout << name << endl;
    }
    fout.close();

    fin.open(file);
    if(fin.is_open())
    {
        cout << "Here are the new contents of the "<<file<<endl;
        while(fin.get(ch))
        {
            cout<<ch;
        }
        cout << endl;
        fin.close();
    }
    cout << "Done\n";
    return 0;
}