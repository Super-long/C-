#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<cstdlib>
using namespace std;
string str1;
vector<string> vec;
int ans;
void input(ifstream &);
int main()
{
    ifstream fina("testa.cpp");
    input(fina);
    ifstream finb("testb.cpp");  //这两个文件中名字不要打多余的空格 两个字符串是不一样的
    input(finb);
    sort(vec.begin(),vec.end());
    int flag=unique(vec.begin(),vec.begin()+ans)-vec.begin();
    ofstream fout("testc.cpp");
    for(int i=0;i<flag;i++){
        fout << vec[i] << endl;
    }
    return 0;
}
void input(ifstream & fin)
{
    if(!fin.is_open())
    {
        cerr << "fina Error in open!\n";
        exit(EXIT_FAILURE);
    }
    while(!fin.eof())
    {
        getline(fin,str1);
        ans++;
        vec.push_back(str1);
    }
}