#ifndef TIMINGWHEEL_H_
#define TIMINGWHEEL_H_
//高精度时间轮适合的场景是需要大量不等的定时任务 这样可以使每个时间槽上的链表长度显著减少 提高效率 但涉及到移动链表
//单个时间轮其实在定时任务差别不大 加大时间轮的槽数 可以使得分配平均 效率同样不低 
#include<list>
#include<iostream>
#include<vector>
#include<memory>
#include<stdexcept>
#include<unordered_map>
// 第1个轮占的位数
#define TVR_BITS 8
// 第1个轮的长度
#define TVR_SIZE (1 << TVR_BITS)
// 第n个轮占的位数
#define TVN_BITS 6
// 第n个轮的长度
#define TVN_SIZE (1 << TVN_BITS)
// 掩码：取模或整除用
#define TVR_MASK (TVR_SIZE - 1)
#define TVN_MASK (TVN_SIZE - 1)

// 第1个圈的当前指针位置
#define FIRST_INDEX(v) ((v) & TVR_MASK)
// 后面第n个圈的当前指针位置
#define NTH_INDEX(v, n) (((v) >> (TVR_BITS + (n) * TVN_BITS)) & TVN_MASK)
struct timernode;

class timernode{
    public:
        explicit timernode(uint16_t solt , int fd_, uint32_t ex) :
            time_solt(solt), fd(fd_), expire(ex){}
        int Return_fd() const noexcept {return fd;}
        uint32_t Return_expire() const noexcept {return expire;}  
        int Return_solt() const noexcept {return static_cast<int>(time_solt);}
        int Return_wheel() const noexcept {return static_cast<int>(time_wheel);}
        void Set_Wheel(uint8_t si) noexcept {time_wheel = si;}
    private:
        uint16_t time_solt;//槽数
        uint8_t time_wheel;//轮数
        int fd;//socket套接字
        uint32_t expire;  //到期时间
};

class TimerWheel{
    using itr = std::list<std::shared_ptr<timernode>>::iterator;
    using TVN_ = std::list<std::shared_ptr<timernode>>[256];
    using TVR_ = std::list<std::shared_ptr<timernode>>[64];
    public:
        TimerWheel() : currenttime(0){} 
        void TW_Add(int fd, int ticks = 10){//传入fd 与 定时时间
            if(ticks < 0) throw std::invalid_argument("'Timer_Wheel::TW_Add' : error parameter."); 
            int ex = currenttime + ticks;
            _TW_Add_(fd, ex);
        }
        void TW_tick(); //放在信号接收函数中
        void TW_update(int fd);
    private:
        std::unordered_map<int, itr> mp;
        void _TW_Add_(int fd, int ex);
        uint32_t currenttime;
        TVN_ tvroot;
        TVR_ tv[4];
};

void TimerWheel::_TW_Add_(int fd, int ex){ //可以在user数据中存储迭代器 用一个map也可
    uint32_t ex_ = static_cast<uint32_t>(ex);
    uint32_t idx = ex_ - currenttime;
    auto ptr = std::make_shared<timernode>(FIRST_INDEX(ex_),fd, ex_);
    if(idx < TVR_SIZE){
        ptr->Set_Wheel(0);
        tvroot[FIRST_INDEX(ex_)].emplace_back(std::move(ptr));
        //return --(tvroot[FIRST_INDEX(ex_)].end());
        mp[fd] = --(tvroot[FIRST_INDEX(ex_)].end());
    } else {
        uint64_t sz;
        for(int i = 0; i < 4; ++i){
            sz = (1ULL << (TVR_BITS + (i+1) * TVN_BITS));
            if(idx < sz){
                idx = NTH_INDEX(ex, i);
                tv[i][idx].emplace_back(std::move(ptr));
                //return --(tv[i][idx].end());
                mp[fd] = --(tv[i][idx].end());;
                ptr->Set_Wheel(i + 1);
                break;
            }
        }
    }
}

void TimerWheel::TW_tick(){
    ++currenttime;
    uint32_t currtick = currenttime;
    int index = (currtick & TVR_MASK);
    if(index == 0){
        int i = 0;
        int idx = 0;
        do{
            idx  = NTH_INDEX(currenttime, i);
            for(auto x = tv[i][idx].begin(); x != tv[i][idx].end(); ++x){
                TW_Add((*x)->Return_fd(), static_cast<int>(currenttime - (*x)->Return_expire()));
                tv[i][idx].erase(x);
            }
        }while (idx == 0 && ++i < 4);
    }
    for(auto x = tvroot[index].begin(); x != tvroot[index].end(); ++x){
        int fd = (*x)->Return_fd();
        //这个时候可以任意操作 不过一般是close 
        tvroot[index].erase(x);
    }
}

void TimerWheel::TW_update(int fd){ //当一个连接发送数据时 更新这个时间轮
    TW_Add(fd);
    int solt = (*mp[fd])->Return_solt();
    int wheel = (*mp[fd])->Return_wheel();
    if(!solt){
        tvroot[wheel].erase(mp[fd]);
    }else{
        tv[solt - 1][wheel].erase(mp[fd]); 
    }
}

#endif