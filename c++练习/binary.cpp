#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

inline void eatline(){while(cin.get()!='\n') continue;}

struct plant
{
    char name[20];
    double population;
    double g;
};

const char *file="plant.dat";

int main()
{   
    plant pl;
    cout << fixed << right;
    ifstream fin;
    fin.open(file,ios_base::in|ios_base::binary);
    if(fin.is_open())
    {
        cout <<"Here are the contents of the "<<file<<endl;
        while(fin.read((char *)&pl,sizeof(pl)));
        cout << setw(20) << pl.name << ": "
            << setprecision(0)<<setw(12)<<pl.population
            << setprecision(2)<<setw(6)<<pl.population;
        fin.close();
    }

    ofstream fout;
    fout.open(file,ios_base::out|ios_base::app|ios_base::binary);
    if(!fout.is_open())
    {
        cerr << "Can't open "<<file<<" file to open\n";
        exit(EXIT_FAILURE);
    }
    cout << "Enter plant's name (black to quit):\n";
    cin.get(pl.name,20);
    //while(pl.name[0] != '\0')
    while(pl.name[0] != '1')
    {
        eatline();
        cout << "Enter plant polulation:\n";
        cin >> pl.population;
        cout << " Enter plant g:\n";
        cin >> pl.g;
        eatline();
        fout.write((char *)&pl,sizeof(pl));
        cout << "Enter plant's name (black to quit):\n";
        cin >> pl.name;
    }
    fout.close();

    fin.open(file,ios_base::in|ios_base::binary);
    if(fin.is_open())
    {
        cout <<"Here are the new contents for "<<file<<endl;
        while(fin.read((char*)&pl,sizeof(pl)))
        cout << setw(20) << pl.name << ": "
        << setprecision(0)<<setw(12)<<pl.population
        << setprecision(2)<<setw(6)<<pl.population;
    }
    fin.close();
    cout << "\nDone!\n";
    return 0;
}