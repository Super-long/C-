#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<fstream>
#include<assert.h>
using namespace std;
struct node{
    int a,nl;
    node(int aa,int bb):a(aa),nl(bb){}
    ~node() = default;
};

void exercise(int *b,int *e){
    assert(b!=NULL);//调用abort()
    vector<int>vec(*b,*e);
    int *p = new int[vec.size()];
    ifstream in("hello");
    shared_ptr<int> tmp(new int[vec.size()],[](int *p){delete[] p;cout << "hello\n";});
    //传一个删除器进去就好了
    //throw runtime_error("delete p");
    throw node(1,2);
    try{

    }catch(node &err){
        cout << "hello\n";
    }catch(runtime_error &err){
        delete []p;
        cout << err.what() << endl;
    }
}

int main()
{
    int a = 5;
    int b = 6;
    int *p = &a;
    int *q = &b;
    exercise(p,q);
    try{

    }catch(node &err){
        cout << "ok\n";
    }
    return 0;
    //abort　没有刷新缓冲区呀，
}