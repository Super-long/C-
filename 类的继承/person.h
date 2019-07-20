//虚基类的练习 需要注意的是19行的不可以不加const限定符 否则会无法通过编译
//原因是const无法调用非const类型
//对于虚函数 声明一定要一致 否则会无法通过编译 尤其注意const限定符
#ifndef PERSON_H_
#define PERSON_H_

#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class person
{
    private:
        string name;
    protected:
        virtual void data()const {cout <<"name: " << name;}

    public:
        person() :name("No name") {}
        person(string s1) :name(s1){}
        person(char *s): name(s){}
        virtual ~person(){}
        virtual void show()const{data();};
};

class Gunslinger : virtual public person
{
    private:
        double time;
        int scratch;
    protected:
        void data()const{
            cout <<"time: " << time << endl;
            cout <<"scratch: " << scratch << endl;
        }
    public:
        Gunslinger():person(),time(0),scratch(0){}
        Gunslinger(string s1,double t,int s)
        :person(s1),time(t),scratch(s){}
        Gunslinger(person & p,double t,int s)
        :person(p),time(t),scratch(s){}
        double Draw() const {return time;}  //如果返回值为引用则可修改成员 题目没说 但最好不那么做
        void show() const //这里是const
        {
            person::data();//这里也必须是const
            data();
        }
};

class Pokerplayer : virtual public person
{
    public:
        Pokerplayer() :person() {}
        Pokerplayer(person & p):person(p) {}
        Pokerplayer(string s):person(s) {}
        int Draw() {return std::rand()%53+1;}
        void show() const {person::data();}
};

class BadDude:public Pokerplayer,public Gunslinger
{
    protected:
        void data() const{
            Gunslinger::data();
        }
    public:
        BadDude():person(),Gunslinger() {}
        BadDude(string s1,double t,int s)
            :person(s1),Gunslinger(s1,t,s) {}
        BadDude(person & p,double t,int s)
            :person(p),Gunslinger(p,t,s) {}
        int Gdraw() const{Pokerplayer::show();}
        int Cdraw() {return std::rand()%53+1;}
        void show()const{
            data();
            person::data();
        }
};

#endif