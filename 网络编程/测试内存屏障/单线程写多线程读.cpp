#include<bits/stdc++.h>
using namespace std;

vector<int> Data(200);

void func_write(){
    int count = 100000;
    while(count--){
        for(auto& x : Data){
            if(count&1){
                x = 1111111;
            } else {
                x = 2222222;
            }
        }
        std::this_thread::yield();
    }
}

void func_read(){
    int count = 100000;
    int prev = 0;
    while(count--){
        for(int i = 0; i < Data.size(); ++i){
            if(0 == i){
                prev = Data[i];
            } else {
                if(prev != Data[i]){
                    // 如果出现这种情况就证明出现了
                    cout << "error : " << prev << " -> " << Data[i] << endl;
                    exit(1);
                }
            }
        }
    }
}

int main(){
    
}