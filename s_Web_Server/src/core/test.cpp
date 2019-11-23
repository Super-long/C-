#include<unordered_map>
#include<iostream>
#include<memory>
using namespace std;

class tmp{
    public:
        tmp(int a, char c) : hell(a),ch(c){}
        char show(){
            cout << hell << endl;
            return ch;
        }
    private:
        int hell;
        char ch;
};

int main(){
    tmp T(5,'g');
    unordered_map<int,unique_ptr<tmp>> mp;
    mp[1] = make_unique<tmp>(5,'j');

    auto& x = mp[1];
    cout << x->show() << endl;
}