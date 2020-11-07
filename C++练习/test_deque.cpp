#include<bits/stdc++.h>
using namespace std;

void func1(){
    size_t v1 = 42;
    auto f = [v1] () mutable {return v1++;};

}



int main(){
    deque<int> que;
    for (int i = 0; i < 10; i++){
        que.push_back(i);
    }
    cout << que[5] << endl;
    vector<int> vec;
 
}