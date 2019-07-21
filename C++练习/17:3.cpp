//把一个文件拷贝到另一个文件
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int main(int argc,char *argv[])
{
    ofstream fout("test.cpp");
    if(!fout.is_open()){
        cerr << "Error in fout!\n";
        exit(EXIT_FAILURE);
    }
    ifstream fin("testa.cpp");
    if(!fout.is_open())
    {
        cerr << "Error in fout!\n";
        exit(EXIT_FAILURE);
    }
    char ch;
    while(fin.get(ch)){
        fout << ch;
    }
    ifstream fink("test.cpp");
    if(fink.is_open()){
        while(fink.get(ch)){
            cout << ch;
        }
    }else{
        cerr << "Error in the read!\n";
        exit(EXIT_FAILURE);
    }
    fin.close();
    fout.close();
    fink.close();
    return 0;
}