#include<bits/stdc++.h>
using namespace std;

class hello{
    public:
        int n =0;
        void operator()(int &count){
            n++;
            cout << "n : " << n << " " << count << endl;
        }
        friend hello operator+(const int &a,const hello &b){
            cout << a << endl;
            return b;
        }
};

int main(){
    vector<int>vec = {1,2,3};
    int x = vec.back();
    int &d = vec.front();
    cout << x << endl;
    hello a;
    auto dd = 5+a;
    sort(vec.begin(),vec.end(),greater<int>());
    hello h;
    for_each(vec.begin(),vec.end(),h);
    return 0;
}