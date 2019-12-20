#include<sstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    string str;
    string Ddd;
    getline(cin, str);
    istringstream input(str);
    ostringstream ouput;
    vector<string> vec;
    string word;
    while(input >> word){
        vec.push_back(word);
    }
    for(const auto& T : vec){
        ouput << T << " ";
    }
    cout << ouput.str() << endl;
    return 0;
}