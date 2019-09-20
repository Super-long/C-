#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<algorithm>
#include<fstream>
#include<assert.h>
using namespace std;
struct node{
    int a,nl;
    node(int aa,int bb):a(aa),nl(bb){}
    ~node() = default;
};

class isbn_error : std::logic_error{ //继承标准错误
    public:
        explicit isbn_error(const string &str) : std::logic_error(str){
            //cout << "isbn_error\n";
        }
};

void judge(){
    throw node(1,2);
}

void exercise(int *b,int *e){
    assert(b!=NULL);//调用abort()
    vector<int>vec(*b,*e);
    int *p = new int[vec.size()];
    ifstream in("hello");
    shared_ptr<int> tmp(new int[vec.size()],[](int *p){delete[] p;cout << "hello\n";});
    //传一个删除器进去就好了
    //throw runtime_error("delete p");
    try{
        judge();
    }catch(node &err){
        cout << "hello\n";
    }catch(runtime_error &err){
        delete []p;
        cout << err.what() << endl;
    }
}

int tmp(){ //在noexcept函数中抛出异常　遵守不在运行时抛出异常(调用terminate)
    //throw int(1);
    throw isbn_error("isbn_error");
}

int main()
{
    int a = 5;
    int b = 6;
    int *p = &a;
    int *q = &b;
    exercise(p,q);
    try{
        tmp();
    }catch(node &err){
        cout << "node\n";
    }catch(isbn_error &err){
        cout << "isbn_error\n";
    }
    return 0;
    //abort　没有刷新缓冲区呀，
}