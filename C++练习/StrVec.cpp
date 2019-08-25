#include<memory>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

//简易Vector
class StrVec
{
    public:
        StrVec():
            elements(nullptr),first_free(nullptr),cap(nullptr){}
        StrVec(const StrVec&);
        StrVec &operator=(const StrVec &);
        ~StrVec();
        void push_back(const string &);
        size_t size() const {return first_free-elements;}
        size_t capacity() const {return cap-elements;}
        string* begin() const {return elements;}
        string* end() const {return cap;}
        
    private:
        static allocator<string> alloc;
        void chk_n_alloc(){
            if(size()==capacity())
            reallocate();//当初始分配的空间不够用时从新分配内存
        }
        pair<string*,string*> alloc_n_copy
        (const string *,const string *);
        void free();
        void reallocate();
        string *elements;//起始点
        string *first_free;//首元素位置
        string *cap;//结束点
};
allocator<string> StrVec::alloc;//静态变量类外初始化

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const string & str)
{
    chk_n_alloc();
    alloc.construct(first_free++,std::move(str));//这样效率会更高
}

pair<string*,string*> 
StrVec::alloc_n_copy(const string *a,const string *b)
{
    //分配一段原始的内存
    auto data = alloc.allocate(b-a);
    //把a 到 b 的元素拷贝到data
    return {data,uninitialized_copy(a,b,data)};
    //没有移动构造函数会很浪费资源
}

void StrVec::free()
{
/*     if(elements)
    {
        for(auto x = first_free ;x!=elements ;x--){
            alloc.destroy(x);
        }
        alloc.deallocate(elements,cap-elements);
        //deallocate只有对其中每一个元素执行destory才能调用
    } */

    if(elements)
    {
        for_each(elements,first_free,[](string &rhs){alloc.destroy(&rhs);});
        //利用for_each 与 lambda　可以使代码清晰不少
        alloc.deallocate(elements,cap-elements);
    }//语义更加明显
}

StrVec::StrVec(const StrVec&tmp)
{
    auto data = alloc_n_copy(tmp.begin(),tmp.end());
    elements = data.first;
    first_free = cap = data.second;
    //有多少元素便拷贝多少元素
}

StrVec & StrVec::operator=(const StrVec & tmp)
{
    auto data = alloc_n_copy(tmp.begin(),tmp.end());
    free();//销毁自身内存
    elements = data.first;
    first_free = cap = data.second;
    return *this; //返回本身
}

//重新分配内存　并保留以前的部分　拷贝赋值并销毁以前的数据这样会显得效率十分低下
//所以使用　　移动构造函数
void StrVec::reallocate()
{
    auto newcapacity = size()?2*size():1;
    auto newdata = alloc.allocate(newcapacity);//分配空间
    auto dest = newdata;
    auto elem = elements;
    for(size_t i=0;i!=size();i++){
        alloc.construct(dest++,std::move(*elem++));
        //把左值通过move转化为右值　然后就满足移动构造函数的条件　移动后elem其中就没有值了
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

int main()
{
    StrVec temp;
    temp.push_back("hello");
    cout << temp.capacity() << endl;
    temp.push_back("world");
    temp.push_back("nihao");
    cout << temp.capacity() << endl;
    return 0;
}