#include<bits/stdc++.h>
using namespace std;

void test(std::promise<int>& T){
    try{
        T.set_value(10);
    }catch(...){
        T.set_exception(std::current_exception());
    }
}

void shared(std::shared_future<int>& T){
    cout << T.get() << endl;//与future的区别就是改成了返回一个const& 也是线程安全的 因为是只读嘛
}

//简单测试下shared_future
int main(){
    std::promise<int> p;
    auto T = p.get_future().share();
    vector<std::thread> vec(10);
    for(size_t i = 0; i < 10; i++){
        if(i == 0) vec[i] = std::thread(test, std::ref(p));
        else vec[i] = std::thread(shared, std::ref(T));
    }
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    return 0;
}