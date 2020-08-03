#include <bits/stdc++.h>
using namespace std;

class Person
{
    public:
   virtual void Display () = 0; // 纯虚函数
private:
   string name ; // 姓名
};
class Student : public Person
{
    public:
    void Display() override{
        cout << "nihaoya\n";
    }
};

int main(){
    Student* p1 = new Student();
    p1->Display();

    Person* p2 = p1;
    p2->Display();
}