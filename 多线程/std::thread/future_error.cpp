#include<bits/stdc++.h>
using namespace std;

void test(std::promise<int>& para){
    para.set_value(10);
    //para.set_value(20);
    return;
}

int main(){
    std::promise<int> pro;
    std::future<int> T = pro.get_future();
    std::thread fun(test, std::ref(pro));
    fun.join();
    cout << T.get() << endl;
    auto TT = pro.get_future();
    return 0;
}