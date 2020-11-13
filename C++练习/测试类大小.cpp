#include <bits/stdc++.h>
using namespace std;

class X{
    public:
        void show() ;
};

class Y : public virtual X{
    protected:
    void showY(){
        cout << this << endl;
    }
};
class Z : public virtual X{
    protected:
    void showZ(){
        cout << this << endl;
    }
};
class A : public Y, public Z {
    public:
    void show(){ 
        cout << this << endl;
        this->showZ();
        this->showY();
    }
};

int main(){
    cout << sizeof(X) << endl;
    cout << sizeof(Y) << endl;
    cout << sizeof(Z) << endl;
    cout << sizeof(A) << endl;
    A test;
    test.show();
}