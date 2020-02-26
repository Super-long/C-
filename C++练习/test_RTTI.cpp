#include <bits/stdc++.h>
using namespace std;

class shape{
public:
virtual ~shape(){}
};

class cricle : public shape{

};

int main(){
shape* B = new cricle;
//shape* A = B;
//cout << typeid(A).name() << endl;
cout << typeid(B).name() << endl;
cricle* C = dynamic_cast<cricle*>(B);
cout << typeid(C).name() << endl;
} 


/* class Shape {};
class Rollable {};
class Circle : public Shape, public Rollable {};
class Square : public Shape {};
 
int main(){
//cross cast fail
Shape *pShape1 = new Square();
Rollable *pRollable1 = dynamic_cast<Rollable*>(pShape1);//pRollable为NULL
 
//cross cast success
Shape *pShape2 = new Circle();
Rollable *pRollable2 = dynamic_cast<Rollable*>(pShape2);//pRollable不为NULL
} */
