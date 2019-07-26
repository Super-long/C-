#include<iostream>
#include<memory>
#include<vector>
#include<string>
using namespace std;

class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;
    private:
        shared_ptr<vector<string>>ptr;
        void check(int i,const string );
    public:
        typedef std::vector<string>::size_type size_type;
        StrBlob();
        StrBlob(initializer_list<string> il);
        void push_back(const string &t){ptr->push_back(t);} //用引用减少一次拷贝
        void pop_back(){ptr->pop_back();}
        size_type size() {
            check(0,"asd");
            return ptr->size();}
        string & front() {return ptr->front();}
        string & back() {return ptr->back();}
        const string & front() const  {return ptr->front();} 
        //const放在这里保证不修改对象的值
        const string & back() const {return ptr->back();}
};

StrBlob::StrBlob():ptr(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string>il)
    :ptr(make_shared<vector<string>>(il)){}

void StrBlob::check(int i,const string str)
{
    cout << ptr.use_count() << endl;
    if(i>=ptr->size())
    throw out_of_range(str);
}

class StrBlobPtr{
    public:
        StrBlobPtr():curr(0){}
        StrBlobPtr(StrBlob &a,size_t tt=0):wptr(a.ptr){}
        string & deref() const; //解引用
        StrBlobPtr & incr();  //进行递增
    private:
        size_t curr;
        weak_ptr<vector<string>> wptr;   //防止循环引用导致内存泄露
        shared_ptr<vector<string>> check(size_t ans,const string&)const;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t ans,const string&)const
{
    auto let=wptr.lock();
    if(!let)//引用计数为零
    throw runtime_error("引用为零");
    else if(ans>=(*let).size())
    throw out_of_range("越界！");
    return let;
}

string & StrBlobPtr::deref()const  
{
    auto p=check(curr,"解应用指向:");
    return (*p)[curr]; //解引用指针 返回一个字符串
}

StrBlobPtr & StrBlobPtr::incr()
{
    check(curr,"递增");
    curr++;
    return *this;
}

int main()
{
    const int *p = new const int (5);
    cout << *p << endl;
    delete p;
    initializer_list<string> li={"as","plk","inn"};
    StrBlob a={"sasd","asdas","hello"};

    StrBlob b(a);
    cout << b.size() << endl;

    StrBlob ba=li;
    cout << ba.size() << endl;

    //输出证明想法没有错 只有在对象之间相互赋值才会使引用计数增加
    //输出为 5 2 3 1 3 
}
