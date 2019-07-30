#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
int main()
{
    int tt;
    try{
        cin >> tt ;
        throw runtime_error("sdf");
    }catch(runtime_error)
    {
        cout << "继续\n";
    }
    cout << "asd\n";
    getchar();
    cin.clear();
    char ch;
    while(cin.get()!='\n'){
        continue;
        
    }
    vector<int>vec;
    string str;
    getline(cin,str);
    istringstream recod(str);
    int word;
    while(recod >> word)
    vec.emplace_back(word);
    cout << vec.size() << endl;
/*     int temp;
    //while(cin >> temp);
    auto old_state=cin.rdstate();
    cin.clear();
    cin.failbit;
    cout << "asd";
    cin >> temp;
    cout << "asdasd\n";
    cin.setstate(old_state);
    cout << "asdasd" << flush;
    cin >> temp; */
}