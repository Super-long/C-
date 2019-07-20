#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
    string temp;
    string tempa;
    string tempb;
    ofstream fina("testb.cpp");
    if(!fina.is_open())
    {
        cerr << "Error in open!\n";
        exit(EXIT_FAILURE);
    }else{
        while(!fina.eof())
        {
            getline(cin,temp);
            fina << temp << endl;
        }
    }
    ofstream finb("testc.cpp");
    if(!finb.is_open())
    {
        cerr << "Error in open!\n";
        exit(EXIT_FAILURE);
    }else{
        while(!finb.eof())
        {
            getline(cin,temp);
            finb << temp << endl;
        }
    }
    fina.close();
    finb.close();
    ifstream finaa;
    ifstream finbb;
    finaa.open("testb.cpp");
    finbb.open("testc.cpp");
    ofstream fout("testd.cpp");
    if(!fout.is_open())
    {
        cerr << "Error in open!\n";
        exit(EXIT_FAILURE);
    }else{
        if(!fina.is_open() && !finb.is_open())
        {
            cerr << "Error in open!\n";
            exit(EXIT_FAILURE);
        }else{
            while(finaa.eof() || finbb.eof())
            {
                getline(finaa,tempa);
                getline(finbb,tempb);
                fout << tempa << " " << tempb << endl;
            }
        }
        if(finaa.eof())
        {
            while(getline(finaa,tempa))
            fout << tempa << endl;
        }
        if(finbb.eof())
        {
            while(getline(finbb,tempb))
            fout << tempb << endl;
        }
    }
    finbb.close();
    finaa.close();
    fout.close();
    return 0;
}