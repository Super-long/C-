#include <bits/stdc++.h>
using namespace std;

struct a{

};

class b{

};

class c : public a{

};

class d : public a, private b{

};

int main(){
    cout << sizeof(struct a) << endl;
    cout << sizeof(struct b) << endl;
    cout << sizeof(struct c) << endl;
    cout << sizeof(struct d) << endl;
};