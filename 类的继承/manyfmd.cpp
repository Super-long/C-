//模板类的非约束模板友元函数
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
template<typename T>
class manyfriend
{
    private:
        T item;
    public:
        manyfriend(const T & i) : item(i){}
        template<typename C,typename D>
        friend void show(C & c,D & d);
};

template<typename C,typename D> void show(C&c,D&d)
{
    cout << c.item << " " << d.item << endl;
}

int main()
{
    manyfriend<int> fri1(10);
    manyfriend<int> fri2(20);
    manyfriend<double> fri3(10.5);
    cout << "fri1,fri2: ";
    show(fri1,fri2);
    cout << "fri2,fri3: ";
    show(fri2,fri3);
    return 0;
}