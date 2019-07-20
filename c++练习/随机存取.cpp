#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
const int LEN=20;
using namespace std;
struct planet
{
    char name[LEN];
    double population;
    double g;
};

const char *file="plant.dat";
inline void eatline(){while(cin.get()!='\n') continue;}

int main()
{
    planet pl;
    fstream finout;
    finout.open(file,ios_base::in|ios_base::out|ios_base::binary);
    int ct=0;
    if(finout.is_open())
    {
        finout.seekg(0);
        cout << "Here are the current contents of you file:\n";
        while(finout.read((char *)&pl,sizeof(pl)))
        {
            cout << ++ct << ": " << setw(LEN) << pl.name <<": ";
            cout << setprecision(0) << setw(12)<<pl.population<<endl;
            cout << setprecision(2) << setw(6)<<pl.g<<endl;
        }
        if(finout.eof()){
            finout.clear();
        }
        else{
            cerr << "Error in reading!\n";
            exit(EXIT_FAILURE);
        }
    }else{
        cerr << file << "could not opend!\n";
        exit(EXIT_FAILURE);
    }
    cout << "Please enter a number you wish to change:\n";
    long rec;
    cin >> rec;
    //eatline();
    if(rec<0 || rec>=ct)
    {
        cout << "invild number!\n";
        exit(EXIT_FAILURE);
    }

    streampos place = (rec-1)*sizeof(pl);
    finout.seekg(place);
    if(finout.fail())
    {
        cerr << "Error in this operation.\n";
        exit(EXIT_FAILURE);
    }
    finout.read((char*)&pl,sizeof(pl));
    cout << ct << ": " << setw(LEN) << pl.name <<": ";
    cout << setprecision(0) << setw(12)<<pl.population<<endl;
    cout << setprecision(2) << setw(6)<<pl.g<<endl;
    if(finout.eof())
        finout.clear();
    cout << "please enter planet name\n";
    cin >> pl.name;
    cout << "please enter planet population:\n";
    cin >> pl.population;
    cout << "please enter planet g:\n";
    cin >> pl.g;
    place = (rec-1)*sizeof(pl);
    finout.seekp(place);//put
    finout.write((char*)&pl,sizeof(pl))<<flush; //第一遍没有写缓冲区
    if(finout.fail()){                          //缓冲区的作用在于在close之前把缓冲区清空
        cerr << "Error in the write:\n";
        exit(EXIT_FAILURE);
    }
    ct=0;
    finout.seekg(0);
    cout << "Here are the new contents of the "<<file<<endl;
    while(finout.read((char*)&pl,sizeof(pl)))
    {
        cout << ct++ << ": " << setw(LEN) << pl.name <<": ";
        cout << setprecision(0) << setw(12)<<pl.population<<endl;
        cout << setprecision(2) << setw(6)<<pl.g<<endl;
    }
    finout.close();
    cout << "Done!\n";
    return 0;
}