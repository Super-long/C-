#include<bits/stdc++.h>
using namespace std;

class a{
public:
    explicit a(int para) : res(para){
        std::cout << "in construct\n";
    }
    a& operator=(const a& para){
        res = para.res;
        std::cout << "in operator =\n"; 
    } 
private:
    int res;
};

void test(){
    while(1){
        std::this_thread::yield();
    }
}

int main()
{
    int sum = 0;
    std::vector<std::thread> vec;
    for(size_t i = 0; i < 6; i++){
        vec.emplace_back(std::thread(test));
    }
    getchar();
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
/*     scanf("%d",&sum);
    if(sum&1){
        printf("%d\n",(1+(sum-1))*(sum-1)/2 + sum);
    }else{
        printf("%d\n",(1+sum)*sum/2);
    } */

    return 0;
}