#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>

class Observable;

class Observer{
public:
    virtual ~Observer();
    virtual void update() = 0;
};

class Observer_ : public Observer{
private:
    std::weak_ptr<Observable> subject_; //保证析构时subject_存在
public:

    void update() override {

    }

    void observe(Observable* para){
        para->Register(std::shared_ptr<Observer>(this));
    }

    ~Observer_(){
        if(auto shared = subject_.lock()){
            shared->unRegister(std::shared_ptr<Observer>(this));
        }
    }
};

class Observable{
private:
    mutable std::mutex mutex_;
    std::vector<std::weak_ptr<Observer>> observers;
    using Iterator = typename std::vector<std::weak_ptr<Observer>>::iterator;

public:
    void Register(const std::weak_ptr<Observer>&);
    void unRegister(const std::weak_ptr<Observer>&);
    void notifyObservers();
};

void
Observable::Register(const std::weak_ptr<Observer>& para){
    std::lock_guard<std::mutex> guard(mutex_);    
    observers.push_back(para);
}

/* void
Observable::unRegister(const std::weak_ptr<Observer>& para){
    std::lock_guard<std::mutex> guard(mutex_);    
    std::find_if(observers.begin(), observers.end(), 
    [&](const Iterator& item){
        if(para == item) return true; //如何删除一个weak_ptr
    });
} */

void 
Observable::notifyObservers(){
    std::lock_guard<std::mutex> guard(mutex_);
    Iterator it = observers.begin();
    while(it != observers.end()){
        std::shared_ptr<Observer> obj(it->lock());
        if(obj){
            obj->update();//使用用户代码 可能造成死锁 且可能执行无上限的时长
        }else{
            it = observers.erase(it);
        }
    }
}

#endif //OBSERVER_H_