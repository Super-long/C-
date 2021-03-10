#include<bits/stdc++.h>
using namespace std;

//一般情况下保证上锁的顺序就没有死锁问题,
class X{
    private:
        std::mutex m;
        vector<int> vec;
    public:
        X(vector<int>& v) : vec(v){}
        friend void swap(X& lhs, X& rhs){
            if(&lhs == &rhs) return;

            /**
             * 对以下函数可能发生死锁的情况:
             * 自赋值
             * 在另一个使用同样两个对象的锁的时候顺序不同 就可能造成死锁
            */
            //lock帮我们实现的是两个锁要一起使用时的全或无的语义 这样可以避免死锁 但两个锁分开就没办法了
            std::lock(lhs.m, rhs.m);//感觉adopt_lock就是为了这种情况而存在的
            std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
            std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
            //std::adopt_lock 只有一个作用: 此锁已经上锁 在lock_guard构造函数里面不用给这个锁上锁了
            swap(lhs.vec, rhs.vec);
        }

        size_t show() const{
            return vec.size();
        }
};

vector<int> on(5),tw(10);
X one(on),two(tw);

void test_swap(){
    swap(one, two);
}

int main(){
    auto T1 = std::thread(test_swap);
    auto T2 = std::thread(test_swap);
    cout << "end: " << one.show() << endl;
    T1.join();
    T2.join();
    getchar();
    cout << "one : " << one.show() << endl;
    cout << "two : " << two.show() << endl;
    return 0;
}