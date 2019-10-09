//尽量使用const　可以在编译阶段找到错误的用法
#include<iostream>
using namespace std;

class hello{
    private:
        char* book;
    public:
        explicit hello(char* tmp):book(tmp){}
        const char& operator[](std::size_t position) const{
            cout << book[position] << endl;
        }
//利用const实现non_const 为了代码复用 这个比较小　但是如果向其中加一些异常检查那重复的部分就比较多了
        char& operator[](std::size_t position){
            return 
                const_cast<char&>(
                    static_cast<const hello&>(*this)[position]
                );
        }
};
//上述的反向做法则不被允许　最好不要修改const

int main(){
    char book[50] = "nihaoya";
    hello temp(book);
    cout << temp[4] << endl;
    return 0;
}