#include <boost/ptr_container/ptr_vector.hpp>
#include <bits/stdc++.h>
using namespace std;
typedef boost::ptr_vector<int> TPtrVector;

int main(){
    TPtrVector vec;
    int a = 10;
    //vec.push_back(&a);
    //vec.push_back(nullptr);
    for(size_t i = 0; i < 10; i++)
    {
        int* Temp = new int(10);
        vec.push_back(Temp);
    }
    auto T = vec.clone();
/*     for(auto x : *T){
        std::cout << x << endl;
    } */
    vec[5] = 20;
    using type = decltype(vec.begin());
    for_each(vec.begin(), vec.end(),[](int T){cout << T << endl;});
    for(auto x : *T){ //深拷贝
        cout << x << endl;
    }
    for(auto x : vec){
        cout << x << endl;
    }
}