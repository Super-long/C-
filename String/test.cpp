#include<bits/stdc++.h>
#include<ostream>
using namespace std;

//http://man7.org

int main(){
    using std::cout;
    using std::endl;
    string str = "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    int x = str.find("fghidjk", 0 , 7);;
    string TT(str);
    char* bok = "def";
    cout << TT.find(bok, 0, 3) << endl;
}
