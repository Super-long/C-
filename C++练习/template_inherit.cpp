#include<iostream>
#include<string>
using namespace std;

class companya{
    public:
    void send(const string& str){
        cout << "companya : " << str << endl;
    }
};

class companyb{
    public:
    void send(const string& str){
        cout << "companyb\n"  << str << endl;
    }
};

template<typename company>
    class msgsender{
    public:
        void sendclear(){
            company T;
            T.send("hello world");
        }
};

template<typename company>
class logingmsgsend : public msgsender<company>{
public:
    //using msgsender<company>::sendclear; //得放在这里 放到函数中是不可以的
    void sendclearmsg(const string& str){
        //this->sendclear();
        //msgsender<company>::sendclear();//这种方法
        sendclear();//泛型编程中编译器默认不能看到基类的函数 因为基类可能有特化
    }
    //1.加一个this 假设被继承
    //2.使用using 声明这个继承的函数
    //3.明确指出调用函数位于base中
    //以上操作其实就是给编译器一个承诺 任何特化版本都支持一般的接口 否则容易编译时出现隐式错误

    //特化是可以改变接口的 但个人感觉不太好 很难调用 感觉改个实现就刚好 
};

int main()
{
    logingmsgsend<companyb> T;
    T.sendclearmsg("in inherit.");
    return 0;
}