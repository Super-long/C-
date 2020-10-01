#include <iostream>
#include <chrono>
//只需下载include此文件
#include <Concurrent>
 
//SPSC通道，多个生产者或消费者，协程调度行为不好控制
coroutine::Channel<int> channel; 
 
string async_func()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    return "21";
}
 
void routine_func1()
{
    //从通道中获取消息，如果没有消息会yield
    int i = channel.pop();
    std::cout << i << std::endl;
	
    i = channel.pop();
    std::cout << i << std::endl;
}
 
void routine_func2(int i)
{
    std::cout << "20" << std::endl;
 
    //放弃当前协程的执行，返回恢复点
    coroutine::yield();
	
    std::cout << "21" << std::endl;
    
    //异步执行任务，如果任务无法立即执行完毕，会yield
    string str = coroutine::await(async_func);
    std::cout << str << std::endl;
}
 
void thread_func()
{
    //创建协称，回调函数形式为：std::function<void()>
    coroutine::routine_t rt1 = coroutine::create(routine_func1);
    coroutine::routine_t rt2 = coroutine::create(std::bind(routine_func2, 2));
    	
    std::cout << "00" << std::endl;
 
    //恢复rt1
    coroutine::resume(rt1);
 
    std::cout << "01" << std::endl;
 
    //恢复rt2
    coroutine::resume(rt2);
	
    std::cout << "02" << std::endl;
    //向通道推送消息
    channel.push(10);
	
    std::cout << "03" << std::endl;
    coroutine::resume(rt2);
	
    std::cout << "04" << std::endl;
    channel.push(11);
	
    std::cout << "05" << std::endl;
 
    //销毁协程。
    //建议：协程在执行完毕后统一释放，这样协程栈空间中的对象能够安全的被到释放。
    coroutine::destroy(rt1);
    coroutine::destroy(rt2);
}
 
int main()
{
    std::thread t1(thread_func);
    std::thread t2([](){
        //不支持跨线程的协程调度
    });
    t1.join();
    t2.join();
    return 0;
}