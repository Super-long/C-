//对非模板友元的试验
#include<iostream>
using std::cout;
using std::endl;

// template <typename T>
// void reports(Hasfriend<int>a);
class A{
    private :
    int a ;
    void print(A&l) {
        l.a = 7;
        cout << a <<endl ;
        }
    public:
     A() {}
};

template<typename T>
class Hasfriend
{
    friend void print(A&l) ;
    friend void reports(Hasfriend<int>a);
    private:
        T item;
        static int ct;
    public: 
        
        Hasfriend(const T &i) : item(i){ct++;}
        ~Hasfriend(){ct--;}
        void reports();
};

template<typename T>
int Hasfriend<T>::ct=0;


template <typename T>
void Hasfriend<T>::reports() //以类为参数
{
    cout << "Hasfriend<>:" << item <<endl;
}

void print(A&l){
    cout << l.a <<endl ;
}

void reports(Hasfriend<int>a){
    cout << a.item <<endl ;
}

int main()
{
    Hasfriend<long> h(10);
    h.reports();
    Hasfriend<int>a(100);
    reports(a);
}