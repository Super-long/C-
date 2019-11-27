#include<iostream>
#include<memory>
using namespace std;

class top{};
class middle : public top{};
class bottom : public middle{};

template <typename T>
class smartptr{
    public:
        //这个在我写智能指针时确实没有考虑到
        explicit smartptr(T* pt) : ptr(pt) {}  
        smartptr(const smartptr& pt){cout << "no template\n";}
        template<typename type>
        smartptr(const smartptr<type>& other) : ptr(other.get()){cout << "template\n";}
        //利用指针的强制转换 也可以自动筛除掉一些不成立的内置类型转换
        T* get() const {return ptr;}
    private:
        T* ptr;

};

//Effective C++ 中221页
int main(){
    top* pt1 = new middle;
    top* pt2 = new bottom;
    const top* pt3 = pt1;
    smartptr<middle> p1(new middle);
    smartptr<top> p2(p1);
}