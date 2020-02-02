#include<bits/stdc++.h>
using namespace std;

std::shared_ptr<int> ptr(new int);

int main(){
    auto T = ptr;
    T.reset(new int(10));
    cout << *T << endl;
    cout << *ptr << endl;
    return 0;
}