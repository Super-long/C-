#include<bits/stdc++.h>
using namespace std;

int GetOne(void) {
    int level = 1;

    while ((random()&0xFFFF) < (0.25 * 0xFFFF))
        level += 1;

    return (level<32) ? level : 32;
}

int GetTwo(){
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed1); //梅森旋转法
    int level = 1;
    while(true){
        int t = generator()%2;
        if(t&1){
            ++level;
        }else{
            break;
        }
    }
    return level;
}

int GetThree(){
    int sum = 1;
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 9);
    while(1){
        if(u(e) < 5 && sum<32){
            sum++;
        }else break;
    }
    return sum;
}

int main(){
    for(int i=0;i<10;++i){
        cout << GetOne() << " "<< GetTwo() << " " <<GetThree() << endl;
    }
    return 0;
}

/*
其概率分布使得第i层中有50%的节点同时数据第i+1层。
先抛开具体数值，我们在讨论一个分数p，对于有i层指针的节点中p部分，同时拥有i+1层指针。
随机层数生成与跳表元素及规模无关

*/