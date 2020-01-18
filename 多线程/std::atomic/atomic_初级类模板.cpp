#include<bits/stdc++.h>
using namespace std;

class one : public std::atomic<int>{
    //允许用户创建一个用户定义的类型的原子变种
    private:
        int on;
    public:
        void show(){
            cout << on << endl;
        }
};

one Temp;
int TT;
void test(){
    ++Temp;
    //++TT; //相比之下 用户自定义的类型确实是原子的
}

int main(){
    std::atomic_int T;

    vector<std::thread> threads(100);
    for(int i=0;i<100;++i){
        //threads.emplace_back(thread(test));
        threads[i] = std::thread(test);
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    cout << Temp.load() << endl;
    //cout << TT << endl;
    cout << Temp.is_lock_free() << endl;
    //实际还用的是库 所以还是谨慎使用
    Temp.show();
    return 0;
}