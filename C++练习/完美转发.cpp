#include<memory>
#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

template<typename fun,typename a,typename b>
void exec(fun f,a &&tmpa,b &&tmpb){
	f(std::forward<a>(tmpa),std::forward<a>(tmpb));
}

int tmp(int &&a,int &&b){
    cout << a*b << endl;
}
vector<int>vec{1};
vector<int>aa;
int main()
{
    int a=5;
    int b=6;
    exec(tmp,std::move(a),std::move(b));
}