#include<bits/stdc++.h>
#include<ostream>
using namespace std;

//http://man7.org

int main(){
    using std::cout;
    using std::endl;
    const char book[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    string S(book);
    string T("ghijk");
    string TT;
    TT.begin();
    //T.append(10, 'a');
    cout << S.find_first_not_of(T,20) << endl;
    cout << S.find_first_not_of('m', 20) << endl;
    cout << S.find_first_not_of("ijk", 20, 3) << endl;
}
