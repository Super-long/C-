#ifndef CALL_BACK_H_
#define CALL_BACK_H_

#include <memory> //shared_ptr weak_ptr
#include <vector> //vector
#include <mutex> //mutex
#include <functional> //function
#include <boost/noncopyable.hpp> // noncopyable

template<typename Callback>
struct SlotImpl;

template<typename Callback>
struct SignalImpl : boost::noncopyable{
    using Slotlist = std::vector<std::weak_ptr<SlotImpl<Callback>>>;

    SignalImpl() : slots_(new Slotlist){}

    void CopyOnWrite(){ //用于修改时不进行插入
        std::lock_guard<std::mutex> guard(mutex_);
        if(!slots_.unique()){
            slots_.reset(new Slotlist(*slots_));
        }
    }

    void clean(){
        std::lock_guard<std::mutex> guard(mutex_);
        CopyOnWrite();
        Slotlist& list(*slots_);
        auto current = list.begin();
        while(current != list.end()){
            if(current->expired()){
                current = list.erase(current);
            }else{
                ++current;
            }
        }
    }

    std::shared_ptr<Slotlist> slots_;
    std::mutex mutex_;
};

template<typename Callback>
struct SlotImpl : boost::noncopyable{
public:
    using Data = SignalImpl<Callback>;
private:
    std::weak_ptr<Data> data_;
    Callback cb_;
    std::weak_ptr<void> tie_;
    bool tied_;
public:
    SlotImpl(const std::shared_ptr<Data>& data, Callback&& cb)
        :data_(data), cb_(cb), tie_(), tied_(false){}
    
    SlotImpl(const std::shared_ptr<Data>& data, Callback&& cb, const std::shared_ptr<void>* tie)
        :data_(data), cb_(cb), tie_(tie), tied_(true){}
    
    ~SlotImpl(){
        //事实上并没有给一个其他对象拿到的SlotImpl一个接口去使用signalImpl
/*         auto data(data_.lock());
        if(data){

        } */
    }
};

using Slot = std::shared_ptr<void>;

template<typename Signature> //这种写法牛皮 可以用一个参数搞出两个类型
class Signal;

template<typename RET, typename... ARGS>
class Signal<RET(ARGS...)> : boost::noncopyable{ //特化版本
public:
    using Callback = std::function<void(ARGS...)>;
    using SignalComponent = SignalImpl<Callback>;
    using SlotComponent = SlotImpl<Callback>;

    Signal() : pool(new SignalComponent()){}

    //~Signal(){} //一个奇怪的链接问题?

    SlotComponent connect(Callback&& func){
        std::shared_ptr<SlotComponent> slot(
            new SlotComponent(pool, std::forward<Callback>(func))
        );
        add(slot);
        return slot;
    }

    SlotComponent connect(Callback&& func, const std::shared_ptr<void>& tie){
        std::shared_ptr<SlotComponent> slot(
            new SlotComponent(pool, std::forward<Callback>(func), tie)
        );
        add(slot);
        return slot;
    }

    void call(ARGS&&... args){ //显然也可以是void
        SignalComponent& impl(*pool); //不增加引用计数的拷贝
        std::shared_ptr<typename SignalComponent::Slotlist> slots;
        {   
            std::lock_guard<std::mutex> guard(pool->mutex_);
            //std::lock_guard<std::mutex> guard(impl.mutex_);
            slots = impl.slots_;
        }
        typename SignalComponent::SlotList& List(*slots); //为什么要这样用 直接指针使用不好吗
        for(auto item : List){
            std::shared_ptr<SlotComponent> slot = item.lock();
            if(slot){
                std::shared_ptr<void> flag;
                if(slot->tied_){
                    flag = slot->tie_.lock();
                    if(flag){
                        slot->cb_(args...);
                    }
                }else {
                    slot->cb_(args...);
                }
            }
        }
    }

private:
    void add(const std::shared_ptr<SlotComponent>& slot){
        SignalComponent& impl(*pool);
        {
            std::lock_guard<std::mutex> guard(impl.mutex_);
            impl.CopyOnWrite();
            impl.slots_->push_back(slot);
        }
    }

    std::shared_ptr<SignalComponent> pool;
};

#endif //CALL_BACK_H_