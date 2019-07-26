#include<iostream>
#include<memory>
#include<vector>
using namespace std;

struct node
{
    int x;
    node(int a):x(a){}
};

int contest()
{
    cout << "hell\n";
}
int dele()
{
    cout << "ok\n";
}

void tmp(node * x)
{
    cout << "saddasd\n";
}

void f()
{ 
    node x(10);
    shared_ptr<node> T(&x,[](node *a)
    {dele();});
    //shared_ptr<node> v(&x,tmp);//先被析构 是一个栈嘛
    cout << "linajiejieshu\n";
}

int main()
{
    f();
    cout << "hello\n";
} 

/* #include <string>
#include <memory>
#include <iostream>

struct destination
{
    std::string des;
    destination(std::string des_) : des(des_){}
};

struct connection
{
    std::string conn;
    connection(std::string conn_) : conn(conn_){}
};

connection connect(destination *des_)
{
    std::cout << "connect to " << des_->des << std::endl;
    return connection (des_->des);
}

void disconnect(connection conn_)
{
    std::cout << "disconnect " << conn_.conn << std::endl;
}

void end_connection(connection *p){ disconnect(*p); }

void f(destination &d)
{
    connection c = connect(&d);
    std::shared_ptr<connection> p(&c, end_connection);
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

int main()
{
    destination des("aaa");
    f(des);

    return 0;
}
 */