#include<bits/stdc++.h>
#include<tuple>
#include<variant>
using namespace std;

// md 现在仍旧不支持
int main(){
    int a = 5;
    int b = 6;
    if(a <=> b){
        std::cout << "-1\n"; 
    } else {
        std::cout << "0\n";
    }
    return 0;
}