#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include <sys/eventfd.h>
#include <assert.h>

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
    std::queue<int> ptr_que;
    int Eventfd_ ;
public:
    reactor(EventLoop* loop, int fd) : event(EventLoopInThisThread), Eventfd_(fd){}

    int show(){
        return a;  
    }
    void set(int x){
        a = x;
    }
    std::queue<int>* return_ptr(){
        return &ptr_que;
    }

    int Return_fd() const{
        return Eventfd_;
    }
};

void test(std::promise<std::queue<int>*>& pro, int T){
    try{
        EventLoop loop;
        reactor rea(&loop, T);
        pro.set_value(rea.return_ptr());
/*         try{
            cout << "ok\n";
            }catch(...){
                pro.set_exception(std::current_exception());
            } */
        
            while(true){
                sleep(1);
                uint64_t Temp = 0;
                read(rea.Return_fd(), &Temp, sizeof(Temp));
                cout << "size : " << Temp << endl;
                while(Temp--){
                    assert(!rea.return_ptr()->empty());
                    cout << std::this_thread::get_id() << " : " <<rea.return_ptr()->front() << endl;
                    rea.return_ptr()->pop();
                }
            }
    }catch(...){
        std::cerr << "error in : " << std::this_thread::get_id() << std::endl;//log_fatal
    }
}

int main(){
    std::vector<std::thread> pool;
    std::vector<std::future<std::queue<int>*> > vec;
    std::vector<std::queue<int>*> store_;
    std::vector<int> eventfd_;

    for(size_t i = 0; i < 3; i++){
        std::promise<std::queue<int>*> Temp;
        vec.push_back(Temp.get_future());
        int T = eventfd(0,EFD_CLOEXEC | EFD_NONBLOCK);
        pool.push_back(std::thread(test, std::ref(Temp), T));
        store_.push_back(vec[i].get());
        cout << store_[i]->size() << endl;
        eventfd_.push_back(T);
    }
    constexpr uint64_t Temp = 1;
    for(size_t i = 0; i < 3; i++){
        cout << "loop\n";
        store_[i]->push(5);
        write(eventfd_[i], &Temp, sizeof(Temp));
                cout << "two\n";
    }
    sleep(3);
    for(size_t i = 0; i < 3; i++){
        cout << "loop\n";
        store_[i]->push(5);
        write(eventfd_[i], &Temp, sizeof(Temp));
                cout << "two\n";
    }
    std::for_each(pool.begin(), pool.end(), std::mem_fn(&std::thread::join));
    return 0;
}