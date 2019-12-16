#include <iostream>
#include <string>
#include <string_view>
using namespace std;
//因为string会对短字符串做优化 不分配堆上内存
//所以string_view的优点在于字符串较长的时候又要进行大量的子串操作
//因为string_view不进行拷贝 且string_view的substr操作是O(1) 而string的substr是线性的
//

/*
string_view通常用于函数参数类型，可用来取代 const char* 和 const string&。 
string_view 代替 const string&，可以避免不必要的内存分配。
*/
int main(){
    string str("hello world"); 
    std::string_view str_(str.c_str(), 11);
    //str_.remove_suffix(7);
    //str_.remove_prefix(1);
    string_view T;
    char TT[20];
    str_.copy(TT, 11);
    cout << TT << endl;
    cout << str_ << endl;
    //str = "okokokosdasddd"; //这样输出算是一个bug 
/*     auto x = str_.substr(0, 10);
    cout << x << endl;
    cout << str_ << endl;
    cout << str << endl; */
    return 0;
}