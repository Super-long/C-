#include<bits/stdc++.h>
using namespace std;

class player{
    public:
        player(int a, char b) : age(a), sexual(b){}
        virtual ~player(){
            cout << "base class\n"; 
        }
        virtual void show(){
            cout << "this is base class\n";
        }
    private:
        int age;
        char sexual;
};

class person : public player{
    public:
        person(int a,char b, const string& c) : 
            player(a, b), str(c){ }
        person() : player(0, 'a'), str("string"){}
        ~person() final{
            cout << "derive class\n";
        }
        void show() final{
            cout << "this a derive class\n";
        }
    private:
        string str;
};

int main(){
/* @ 这是一种危险的行为
 * @ 数组指针会有问题 因为其中涉及到指针运算 但是指针数组就不会有问题 因为其中存储的是指针 
 * @ 因为数组指针分配的是一大块内存 
 * @ 且一个引用的数组是写不出来的 所以只有数组指针可能出现这种情况
 */

    //int a=1,b=2,c=3;
    //int& ff[3] = {a,b,c}; //这样不行呀
    player* Temp[3];
    person one,two,three;
    Temp[0] = &one;
    Temp[1] = &two;
    Temp[2] = &three;
    for(int i=0; i<3; ++i){
        Temp[i]->show();
    }
    player* arr = new person[3];
    //arr[1].show();
/*     for(int i=0; i<3; ++i){
        arr[i].show();
    } */
}