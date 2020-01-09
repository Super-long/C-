#include <exception> //exception
#include <memory> //shared_ptr
#include <mutex> //mutex lock_guard
#include <queue> //queue
#include <thread> //thread
#include <vector> //vector
#include <iostream> //for debugging
#include <algorithm> //for_each
#include <functional> //mem_fn
#include <condition_variable>

template<typename Type>
class threadsafe_queue
{
    private:
        mutable std::mutex m;
        std::queue<Type> que;
        std::condition_variable data_cond;

    public:
        threadsafe_queue() = default;
        threadsafe_queue(const threadsafe_queue&) = default;
        threadsafe_queue(threadsafe_queue&&) noexcept = default;
        threadsafe_queue& operator=(const threadsafe_queue&) = delete;
        
        void push(const Type& new_value);
        void push(Type&& new_value);
        template<typename T>
        void push(T&& new_value);

        bool try_pop(Type& value);
        std::shared_ptr<Type> try_pop();

        void wait_and_pop(Type& value);
        std::shared_ptr<Type> wait_and_pop();

        bool empty() const;
        size_t size() const;
};

template<typename Type>
void 
threadsafe_queue<Type>::push(const Type& new_value){
    std::lock_guard<std::mutex> guard(m);
    que.emplace(std::forward<Type>(new_value));
    data_cond.notify_one();
}

template<typename Type>
void 
threadsafe_queue<Type>::push(Type&& new_value){
    std::lock_guard<std::mutex> guard(m);
    que.emplace(std::forward<Type>(new_value));
    data_cond.notify_one();
}

template<typename Type>
template<typename T> //TODO 为什么相比于上面这个的优先级更高呢
void //没啥必要 写着玩玩
threadsafe_queue<Type>::push(T&& new_value){
    std::cout << "ok\n";
    std::lock_guard<std::mutex> guard(m);
    que.emplace(std::forward<T>(new_value));
    data_cond.notify_one();
}

template<typename Type>
bool
threadsafe_queue<Type>::try_pop(Type& value){
    std::lock_guard<std::mutex> guard(m);
    if(que.empty()) return false;
    value = que.front();
    que.push();
    return true;
}

template<typename Type>
std::shared_ptr<Type>
threadsafe_queue<Type>::try_pop(){
    std::lock_guard<std::mutex> guard(m);
    if(que.empty()) return nullptr; //不应该返回一个空的智能指针
    auto res = std::make_shared<Type>(que.front());
    que.pop();
    return res;
}

template<typename Type>
void 
threadsafe_queue<Type>::wait_and_pop(Type& value){
    std::unique_lock<std::mutex> lk(m);
    data_cond.wait(lk, [this]{return !que.empty();}); //意味着empty也必须是线程安全的
    value = que.front();
    que.pop();
}

template<typename Type>
std::shared_ptr<Type>
threadsafe_queue<Type>::wait_and_pop(){
    std::unique_lock<std::mutex> lk(m);
    data_cond.wait(lk, [this]{return !que.empty();});
    auto res = std::make_shared<Type>(que.front());
    que.pop();
    return res;
}

template<typename Type>
bool
threadsafe_queue<Type>::empty() const {
    std::lock_guard<std::mutex> guard;
    return que.empty();
}

template<typename Type>
size_t
threadsafe_queue<Type>::size() const {
    std::lock_guard<std::mutex> guard;
    return que.size();
}

threadsafe_queue<int> que;

void Push(int i){
    que.push(i);
}

void pop(){
    auto T = que.wait_and_pop();
    std::cout << *T << std::endl;
}

void Pop(){
    auto T = que.try_pop();
    if(T == nullptr) std::cout << "空指针\n";
    else std::cout << *T << std::endl; 
}

int main(){
    std::vector<std::thread> threads(10);
    for(int i = 0; i < 10; i++){
        int emp = 0;
        if(!(i&1))
            threads[i] = std::thread(Push, i);
        else{ 
            threads[i] = std::thread(Pop);
        }
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));   
}