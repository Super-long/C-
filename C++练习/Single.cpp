#include <bits/stdc++.h>
using namespace std;

class test{
    private:
        int a;
        int b;
    public:
    explicit test(int lhs) : a(lhs), b(0) {
        cout << "one para\n";
    }
    test(int lhs, int rhs): a(lhs), b(rhs) {
        cout << "two para\n";
    }
    void show() const {
        cout << a << " " << b << endl;
    }
};

enum Level{
    one,
    two,
    three
};

template<Level x, typename... ARG>
class factory{
private:
    std::shared_ptr<test> LogData;
    std::once_flag resourse_flag;

    void init_resourse(ARG... args){
        LogData.reset(new test(args...));
    }
public:

    int get_log(ARG... args){
        std::call_once(resourse_flag, &factory::init_resourse, this, args...);
        return *LogData;
    }
    //
};

std::shared_ptr<int> resource_ptr;
std::once_flag resource_flag;  // 1

void init_resource()
{
  resource_ptr.reset(new int(5));
  cout << "loop\n";
}

void foo()
{
  std::call_once(resource_flag,init_resource);  // 可以完整的进行一次初始化
  cout << *resource_ptr << endl;
}

void test(){
    foo();
}

int main(){
    factory<one> onefactory;
    cout << onefactory.get_log() << endl;
    cout << onefactory.get_log() << endl;
    //std::thread t1(test);
    //test();
    //foo();
    //t1.join();
    return 0;

}