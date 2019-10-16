#include<iostream>
#include<string>
using namespace std;

class FontHandle{
    public:
        explicit FontHandle(int S):size(S) {}
        void show()const{
            cout << size << endl;
        }
    private:
        int size;
};

class Font{
    public:
        explicit Font(FontHandle F):f(F){}
        /*注意转换函数的一点是没有返回值　也就是说返回值不是一个左值 
        若把返回值当做实参不能单单拿一个引用去作为形参*/
        operator FontHandle() const{
            return f;
        } 
    private:
        FontHandle f;
};

int judge(const FontHandle& f){
    f.show();
}

typedef string address[4];
//以前真没见过这样用的　但最好也不要这样写　容易new的时候导致亡了delete加[]

int main(){
    address tmp;
    cin >> tmp[0];
    FontHandle f1(5);
    Font f2(f1);
    judge(f2);
    return 0;
}