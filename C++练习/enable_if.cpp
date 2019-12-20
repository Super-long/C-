#include<bits/stdc++.h>
using namespace std;

class AT{
public:
    void PrintT(){
        std::cout << "PrintT" << std::endl;
    }

    int ati;
};

typename std::enable_if<true, int>::type t = 5;


/* //is so important 
Checks whether T is a non-union class type. Provides the member constant value which is equal to true, 
if T is a class type (but not union). Otherwise, value is equal to false.
*/

int main(){
    //当第一个参数有定义的为true的时候 T 才有定义 默认为void
    std::enable_if_t<std::is_class<AT>::value, int> ati = 5;
    std::enable_if<std::is_class<AT>::value, AT>::type ai;
    ai.PrintT();
}

/*
template <bool, typename T=void>
struct enable_if {
};
 
template <typename T>
struct enable_if<true, T> {
  using type = T;
};
*/