#include<bits/stdc++.h>
using namespace std;

//这种情况适用于资源本身对于并发访问是安全的 转换成多线程唯一需要注意的就是初始化

std::shared_ptr<int> ptr;

void foo_one(){
    if(!ptr){//显然初始化不线程安全
        ptr.reset(new int());
    }
}

std::shared_ptr<int> ptr_;
std::mutex resource_mutex;

//会引起使用该资源的线程产生不必要的序列化 因为每一个线程都必须等待互斥元 相对来说效率不高 有很多的不必要的资源浪费
void foo_two(){
    std::unique_lock<std::mutex> lk(resource_mutex);
    if(!ptr_){
        ptr_.reset(new int(10));
    }
    lk.unlock();//减小锁的粒度
    //do something. 
}

//Double-Checked Locking.
//这种情况生效与否取决于编译器.
//参见P57 
void foo_three(){
    if(!ptr_){
        std::unique_lock<std::mutex> lk(resource_mutex);
        if(!ptr_){
            ptr_.reset(new int(20));
        }
    }
    //do something.
}

//通常比互斥元有更低的开销 保证多线程只初始化一次
//经测试发现其实差不多
std::once_flag resource_flag;

void init_resource(){
    //cout << "hello world\n";
    ptr_.reset(new int(30));
}

void foo_four(){
    std::call_once(resource_flag, init_resource);
    //do something.
}

//发现其实三种差不多 28原则
void test(){
    //foo_two();
    //foo_three();
    foo_four();
}

int main(){
    vector<std::thread> vec(10000);
    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < 10000; i++){
        vec[i] = std::thread(test);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout<< "time: "  << elapsed.count() << "us" << std::endl;
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    return 0;
}