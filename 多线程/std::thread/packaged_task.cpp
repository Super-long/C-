#include<bits/stdc++.h>
using namespace std;

std::mutex m;
std::deque<std::packaged_task<string()>> tasks;


void gui_thread(){
    while(true){
        //cout << "world\n";
        std::packaged_task<string()> task;
        {
            std::lock_guard<std::mutex> guard(m);
            if(tasks.empty()) continue;
            task = std::move(tasks.front());
            tasks.pop_front(); 
        }
        task(); //future与任务相分离
    }
}

//我觉得packaged_task最大的用处就是把future与任务相互关联
//更容易的收集返回值
//从包装可调用对象意义上来讲，std::packaged_task 与 std::function 类似，只不过 std::packaged_task 将其包装的可调用对象的执行结果传递
//给一个 std::future 对象（重点:该对象通常在另外一个线程中获取 std::packaged_task 任务的执行结果
//即在线程之间传递任务
template<typename Func>
std::future<string> posk_task_for_gui_thread(Func fun){
    std::packaged_task<string()> f(fun);
    std::future<string> res = f.get_future();
    std::unique_lock<std::mutex> guard(m); //改成lock_guard在底下res.get就死锁了
    tasks.emplace_front(std::move(f));
    guard.unlock();
    cout << res.get() << endl;
    return res;
}

string test(){
    return "test";
}

int main(){
    //这辣鸡程序编译了八秒 
    auto T = std::thread(gui_thread);
    std::vector<std::thread> vec(10);
    for(size_t i = 0; i < 10; i++){
        vec[i] = std::thread(posk_task_for_gui_thread<string()>, test);
    }
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    cout <<"ok\n";
    T.join();
    return 0;
}
