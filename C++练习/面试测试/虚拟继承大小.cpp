#include <bits/stdc++.h>
using namespace std;
#pragma pack (4)

class c{
    public:
        int c;
};

class a : virtual public c{
    public:
        int a;
};

class b : virtual public c{
    public:
        int b;
};


class d : public a, public b{

};

class e {
    public:
        char c;
        int* ptr;
        
};

int main(){
    cout << sizeof(struct a) << endl;
    cout << sizeof(struct b) << endl;
    cout << sizeof(struct d) << endl;
    cout << sizeof(struct e) << endl;
};