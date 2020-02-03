#include<bits/stdc++.h>
using namespace std;

/**
 * @ 借以shared_ptr实现copy_on_write
 * @ 对于实现的读写锁来说
 * 优点:解决了写线程饥饿问题
 * 缺点:1.拷贝效率太低,且在临界区内,导致并发潜力不高,且局限性太高(例如不可拷贝的对象)
 *      2.拷贝会造成异常安全问题 bad_alloc
 * 总结:思路牛逼
*/      

class Foo{
private:
    int flag;
public:
    explicit Foo(int a) : flag(a){}
    void show(){
        cout << "hello world" << flag << endl;
    }
};

using Foolist = std::vector<Foo>;
using Foolistptr = std::shared_ptr<Foolist>;
std::mutex mutex_;
Foolistptr g_foos(new Foolist());

void traverse(){
    Foolistptr foos;
    {
        std::lock_guard<std::mutex> guard(mutex_);
        foos = g_foos;
        assert(!g_foos.unique());
    }
    for(auto x : *foos){
        x.show();
    }
}

void post(const Foo& f){
    std::lock_guard<std::mutex> guard(mutex_);
    if(!g_foos.unique()){
        g_foos.reset(new Foolist(*g_foos));
        cout << "copy the whole list.\n";
    }
    assert(g_foos.unique());
    g_foos->push_back(std::move(f));
}

int main(){
    vector<std::thread> vec(20);
    for(size_t i = 0; i < 20; i++){
        if(i < 15 || i == 19)
            vec[i] = std::thread(post, Foo(i));
        else
            vec[i] = std::thread(traverse); 
    }
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    return 0;
}