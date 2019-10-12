#include<iostream>
using namespace std;

class uncopyable{
    protected:
        uncopyable();
        ~uncopyable();
    private:
        uncopyable(const uncopyable&);
        uncopyable& operator=(const uncopyable&);
};

class Homeforsale : private uncopyable{
    
};

class Uncopyable{
    public:
        Uncopyable() = default; //这东西被默认删除了
        Uncopyable(const Uncopyable&) = delete;
        Uncopyable& operator=(const Uncopyable&) = delete;
};

class a{
    public:
        ~a(){}
};
class b{
    public:
        virtual ~b(){}
};

class c{
    public:
        ~c(){
            try{
                throw std::out_of_range("error in ~");
                printf("okok\n");
            }catch(...){
                printf("hello\n");
            }
        }
};

int main(){
    //Homeforsale a,b;
/*     Uncopyable aa,bb;
    aa = bb; */
    cout << sizeof(a) << " " << sizeof(b) << endl;
    c aaa;
    return 0;
}