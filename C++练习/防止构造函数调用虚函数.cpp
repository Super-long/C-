/*这种写法是一个标准的错误写法　把虚函数写在构造函数或虚函数中　想要实现在创建对象时添加多态的对象　
这实际上是不可行的　因为先构造基类　这个时候类型还是基类　所以放入的全是基类　解决方案在下一个中*/
 #include<iostream>
 #include<vector>
 using namespace std;

class Translate;
class BuyTranslate;
vector<Translate const*> vec;
class Translate{
    public:
        Translate();
        virtual void logTransaction() const = 0;
};

void Translate::logTransaction() const {
    cout << "in Translate\n";
    vec.emplace_back(this);
}

Translate::Translate(){
    logTransaction();
}

class BuyTranslate : public Translate{
    public:
        BuyTranslate() = default;
        virtual void logTransaction() const override;
};

void BuyTranslate::logTransaction() const {
    cout << "in BuyTranslate\n";
    vec.emplace_back(this);
}

/* BuyTranslate::BuyTranslate(){
    logTransaction();
} */

int main(){
    BuyTranslate tmp;
    BuyTranslate tmpa;
    cout << vec.size() << endl;
    return 0;
}