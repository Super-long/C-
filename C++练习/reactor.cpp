#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>

class EventLoop{
private:
    bool looping;
    const std::thread::id threadID;
    int x;
public:
    EventLoop();
    ~EventLoop();
    void loop();
};

thread_local EventLoop* EventLoopInThisThread = nullptr;

EventLoop::EventLoop()
        : threadID(std::this_thread::get_id()), looping(false), x(5){
    if(EventLoopInThisThread){
        std::cout << "errno in eventloop.cc : \n";
        abort();
    } else {
        EventLoopInThisThread = this;
    }
}

EventLoop::~EventLoop(){
    assert(!looping);
    EventLoopInThisThread = nullptr;
}

void
EventLoop::loop(){
    assert(!looping);
    looping = true;

    //do something.

    looping = false;
}

class reactor{
private:
    EventLoop* event;
    int a= 5;
public:
    reactor(EventLoop* loop) : event(EventLoopInThisThread){

    }
    int show(){
        return a;  
    }
    void set(int x){
        a = x;
    }
};

void test(std::promise<reactor*>& pro){
    try{
        EventLoop loop;
        reactor rea(&loop);
        pro.set_value(&rea);
/*         try{
            cout << "ok\n";
            }catch(...){
                pro.set_exception(std::current_exception());
            } */
        
            while(true){
                sleep(1);
                std::cout << std::this_thread::get_id() << " : " << rea.show() << std::endl;
            }
    }catch(...){
        std::cerr << "error in : " << std::this_thread::get_id() << std::endl;//log_fatal
    }
}

int main(){
    std::vector<std::thread> pool;
    std::vector<std::future<reactor*> > vec;
    std::vector<reactor*> store_;

    for(size_t i = 0; i < 3; i++){
        cout << "loop : " << i << std::endl;
        std::promise<reactor*> Temp;
        vec.push_back(Temp.get_future());
        pool.push_back(std::thread(test,std::ref(Temp)));
        store_.push_back(vec[i].get());
    }
    sleep(3);
    for(size_t i = 0; i < 3; i++)
    {
        store_[i]->set(i);
    }
    std::for_each(pool.begin(), pool.end(), std::mem_fn(&std::thread::join));
    return 0;
}