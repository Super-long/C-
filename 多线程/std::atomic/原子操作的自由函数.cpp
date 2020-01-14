#include<bits/stdc++.h>
using namespace std;

std::shared_ptr<int> ptr;

//非成员函数版本使得 不是原子类型也可以使用原子类型的操作
//后缀加上explicit可以增加一个指定内存序的参数
void process_data(){
    std::shared_ptr<int> local = std::atomic_load(&ptr);
    cout << *local << endl;
}

void update_data(){
    std::shared_ptr<int> local(new int(10));
    std::atomic_store(&ptr, local);
}

void foo(int lhs, int rhs){
    cout << lhs << " " << rhs << endl;
}

int get_num(){
    static int i = 0;
    return ++i;
}

int main(){
    foo(get_num(), get_num());
    return 0;
}