#include <memory>
#include <string>
#include <mutex>
#include <assert.h>
#include <functional>
#include <unordered_map>
#include <boost/noncopyable.hpp>

#include <iostream> //for debug

/**
 * @ 一个精彩纷呈的多线程对象池
*/

class Stack{
private:
    std::string key_;
public:
    explicit Stack(const std::string& str) : key_(str){}
    std::string key() const{
        return key_;
    }
};

class StockFactory 
: public std::enable_shared_from_this<StockFactory>,
boost::noncopyable
{
private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::weak_ptr<Stack>> stacks_;
public:
    std::shared_ptr<Stack> get(const std::string& key){
        using namespace std::placeholders;
        std::shared_ptr<Stack> Temp_stack;
        std::lock_guard<std::mutex> guard(mutex_);
        std::weak_ptr<Stack>& wkstack = stacks_[key];
        Temp_stack = wkstack.lock();
        if(!Temp_stack){
            std::cout << "Reallocate.\n";
            Temp_stack.reset(new Stack(key),
            std::bind(&StockFactory::DeleteCallBack, 
                std::weak_ptr<StockFactory>(shared_from_this()),_1));
            wkstack = Temp_stack;
        }
        return Temp_stack;
    }
    
private:
    static void DeleteCallBack(const std::weak_ptr<StockFactory>& wkStack, Stack* stack){
        auto factory = wkStack.lock();
        if(factory){
            factory->removeStock(stack);
        }else{
            std::cout << "died.\n";
        }
        delete stack; //应该是好的C++代码中唯一可以看到delete的地方了
    }

    void removeStock(Stack* stack){ //static函数中无法使用no-static成员
        if(stack){
            std::lock_guard<std::mutex> guard(mutex_);
            stacks_.erase(stack->key());
        }
    }
};

void
removeStock(){
    std::shared_ptr<StockFactory> factory(new StockFactory);
    {
        std::shared_ptr<Stack> T1 = factory->get("one");
        std::shared_ptr<Stack> T2 = factory->get("one");
        std::cout <<"interval.\n";
        assert(T1 == T2);
    }
    std::shared_ptr<Stack> T1 = factory->get("one");
}

void
TestStockFactory(){
    std::shared_ptr<Stack> T1;
    {
        std::shared_ptr<StockFactory> factory(new StockFactory);
        T1 = factory->get("one");
        std::shared_ptr<Stack> T2 = factory->get("two");
        assert(T1 != T2);
    }
}

int main(){
    removeStock();
    TestStockFactory();
    return 0;
}