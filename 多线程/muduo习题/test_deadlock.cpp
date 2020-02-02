#include <bits/stdc++.h>
using namespace std;
#include<unistd.h>

class Request;
class Inventory{
public:
    void add(Request* para){
        std::lock_guard<std::mutex> guard(mutex_);
        requests_.insert(para);
    }

    void remove(Request* para){
        std::lock_guard<std::mutex> guard(mutex_);
        requests_.erase(para);
    }

    void PrintAll() const;
private:
    mutable std::mutex mutex_;
    std::set<Request*> requests_;
};

Inventory g_inventory;

class Request{
public:
    void print() const __attribute__ ((noinline)){
        std::lock_guard<std::mutex> guard(mutex_);
        printf("in request print.\n");
    }

    void process(){
        std::lock_guard<std::mutex> guard(mutex_);
        g_inventory.add(this);        
    }

    ~Request() __attribute__ ((noinline)){
        sleep(1);
        std::lock_guard<std::mutex> guard(mutex_);
        sleep(2);
        g_inventory.remove(this);
    }
private:
    mutable std::mutex mutex_;
};

void 
Inventory::PrintAll() const {
    {
        sleep(2);
        std::lock_guard<std::mutex> guard(mutex_);
        sleep(1);
        for(auto x : requests_){
            x->print();
        }
    }
    printf("printall unlcok\n");
}

void test(){
    Request* req = new Request;
    req->process();
    delete req;
}

int main(){
    std::thread run(test);
    //sleep(1);
    g_inventory.PrintAll();
    run.join();
    return 0;
}