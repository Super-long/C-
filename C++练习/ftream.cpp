#include<fstream>
#include<iostream>
#include<string>
//输入一个字符串 创建一个以输入为名称的文件 
int main()
{
    using namespace std;
    string filename;
    cin >> filename;

    ofstream fout(filename.c_str());//const char *c_str()

    fout << "hello world!\n";
    cout << "Enter you favorite number:\n";
    float input;
    cin >> input;
    fout << "Your favorite number is "<< input << endl;
    fout.close();

    ifstream fin(filename.c_str());
    char ch;
    while(fin.get(ch))
    {
        cout << ch;
    }
    cout << "Done!\n";
    fin.close();
    return 0;
}