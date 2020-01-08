#include<bits/stdc++.h>
using namespace std;

class Y{
    private:
        int some_detail;
        mutable std::mutex m;

        int get_detail() const {
            std::lock_guard<std::mutex> guard(m);
            return some_detail;
        }

        int return_detail() const {
            return some_detail;
        }

    public:
        explicit Y(int sd) : some_detail(sd){}

        /**
         * 两种实现方式中优劣明显 第一种的锁粒度更小 占有锁的时间更小 且每次持有一个锁(避免死锁)
         * 缺陷是改变了语义 : 这是两个时间点的比较 从而在某些情况下使得比较毫无意义
         * */

        friend bool operator==(const Y& lhs, const Y& rhs){
            if(&lhs == &rhs)
                return true;
            const int lhsvalue = lhs.get_detail();
            const int rhsvalue = rhs.get_detail();
            return lhsvalue == rhsvalue;
        }

//        friend bool operator==(const Y& lhs, const Y& rhs){
//            std::lock(lhs.m, rhs.m);
//            std::lock_guard<std::mutex> lhs_guard(lhs.m, std::adopt_lock);
//            std::lock_guard<std::mutex> rhs_guard(rhs.m, std::adopt_lock);
//            return lhs.return_detail() == rhs.return_detail();
//        }
};

int main(){
    Y one(3),two(3);
    if(one == two){
        std::cout << "equal.\n";
    }
}