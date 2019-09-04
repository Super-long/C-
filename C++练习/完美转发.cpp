#include<memory>
#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

/*完美转发问题是因为右值传入模板后　模板参数被解释为左值　那么就无法使用一个参数为右值引用的函数　
因此我们需要使用　std::forward　来还原函数本来的类型*/
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