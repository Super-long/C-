#include<functional>
#include<iostream>
using namespace std;
using namespace std::placeholders;
int check_size(int x,int y){
    cout << x << " " << y << endl;
    return 2;
}

int main(){
    int y = 1;
    auto T = bind(check_size,y,_1);
    T(3);
}