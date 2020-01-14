#include<bits/stdc++.h>
using namespace std;

int main(){
    using pa = std::pair<int,int>;
    pa book[5];
    std::atomic<pa*> p(book); 
    pa* x = p.fetch_add(2);//相当于交换与添加
    assert(x == book); //fetch_add的返回的值是修改之前的
    assert(p.load() == &book[2]);

    x = (p -= 1);
    //assert(x == book);
    assert(x == &book[1]);
    assert(p.load() == &book[1]);
    cout << "okok\n";
    return 0;
}