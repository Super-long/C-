#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

struct node{
    string name;
    vector<string>vec;
};

int main()
{
/*     ofstream co;
    ifstream io; */
/*     fstream co;
    co.open("aaaaaaaaaa.cpp",ios::app | ofstream::out | ofstream::in);
    ifstream io("aaaaaaaaaa.cpp");
    co << "hello\n";
    string str;
    io >> str;
    cout << str << endl;
    co.close(); */

    string line,word;
    vector<node>vec;
    auto old_state = cin.rdstate();
    while(getline(cin,line)){
        node temp;
        istringstream rec_ord(line);
        rec_ord >> temp.name;
        while(rec_ord >> word){
            temp.vec.emplace_back(word);
        }
        vec.emplace_back(std::move(temp));
    }
    if(!vec.empty())
    cout << vec[0].vec[0] << endl;
    cout << vec.size() << endl;
    cin.clear();
    //cin.setstate(old_state); //流出现错误后这种设置方法也可以　就是没有清空缓冲区内的东西
    string str;
    cin >> str;
    cout << str << endl;

    cout << "******分隔\n";

    //ostringstream os;
    ostringstream os("hello");
    cout << os.str() << endl; //下面的输出流会刷新流中的数据
    os << " " << "hello world\n";
    os << " " << "ni hao world\n";
    if(!os.str().empty()){
        cout << os.str();
    } 
    return 0;
}