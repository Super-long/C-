/*解决方案为把虚函数改为一般的成员函数　然后通过在派生类中构造基类是传递参数来变相实现多态*/
//这样就解决了上一个代码中留下的问题　Eddective C++ 第九条
 #include<iostream>
 #include<vector>
 #include<string>
 using namespace std;

class Translate;
class BuyTranslate;
vector<Translate const*> vec;
class Translate{
    public:
        Translate() = default;
        explicit Translate(const string&);
        void logTransaction(const string&) const;
        void show() const { cout << str << endl;}
    private:
        string str;
};

void Translate::logTransaction(const string& tmp) const {
    cout << "in Translate\n";
    vec.emplace_back(this);
}

Translate::Translate(const string&strcmp):str(strcmp){
    logTransaction("hello");
}

class BuyTranslate : public Translate{
    public:
        explicit BuyTranslate(const string&);
    private:
        const string str;
        const string Createstring(const string &str){return str;}
};

BuyTranslate::BuyTranslate(const string &strtmp)
:str(strtmp),Translate(Createstring(strtmp)){}
//这里偶然间发现了列表初始化一个缺点　就是你前一个赋值的成员后面是没有办法直接使用的
//写在函数内就可以　注意这一点　

int main(){
    string str = "buy";
    BuyTranslate tmp(str);
    BuyTranslate tmpa("buy");
    cout << vec.size() << endl;
    vec[0]->show();
    return 0;
}

/*
 #include<iostream>
 #include<vector>
 #include<string>
 using namespace std;

class Translate;
class BuyTranslate;
vector<Translate const*> vec;
class Translate{
    public:
        Translate() = default;
        explicit Translate(const string&);
        void logTransaction(const string&) const;
        void show() const { cout << str << endl;}
    private:
        string str;
};

void Translate::logTransaction(const string& tmp) const {
    cout << "in Translate\n";
    vec.emplace_back(this);
}

Translate::Translate(const string&strcmp){
    cout << strcmp << endl;
    logTransaction("hello");
}

class BuyTranslate : public Translate{
    public:
        explicit BuyTranslate(const string&);
    private:
        const string str;
        const string Createstring(){ cout << "one : " << str << endl; return str;}
};

BuyTranslate::BuyTranslate(const string &strtmp)
:str(strtmp),Translate(Createstring()){cout << strtmp << endl;}

int main(){
    string str = "buy";
    BuyTranslate tmp(str);
    BuyTranslate tmpa("buy");
    cout << vec.size() << endl;
    //vec[0]->show();
    return 0;
}
*/