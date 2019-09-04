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
        StrVec(StrVec&&) noexcept;//移动构造函数
        StrVec &operator=(StrVec&&)noexcept;//移动赋值构造函数
        ~StrVec();
        void push_back(const string &); //两个版本的push_back会根据参数的不同选择重载函数
        void push_back(string &&);      //避免在参数为右值的情况下进行不必要的拷贝
        size_t size() const {return first_free-elements;}
        size_t capacity() const {return cap-elements;}
        string* begin() const {return elements;}
        string* end() const {return cap;}
        template<typename... Args> void emplace_back(Args&& ... args);
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

StrVec::StrVec(StrVec&&tmp) noexcept
:elements(tmp.elements),first_free(tmp.first_free),cap(tmp.cap)
{
    cout << "yidonggouzao\n";
    tmp.first_free=tmp.elements=tmp.cap=nullptr;
}

//可变模板参数+完美转发　
//这种情况下初始化列表就不可以　因为可变模板参数允许数据类型不同
template<typename ...Args>//操作666
void StrVec::emplace_back(Args&& ... args){
    chk_n_alloc();
    alloc.construct(first_free++,std::forward<Args>(args)...);
}
//对于emplace_back我的理解是有时效率高于push_back 在参数是左值时仍然是执行拷贝构造函数
//emplace 至少做两次包的扩展　有效率上的损耗　但移动操作效率又高于拷贝操作
//所以左值push_back　右值emplace_back
//至此

StrVec &StrVec::operator=(StrVec&&tmp) noexcept
{
    cout << "yidongfuzhi\n";
    if(this!=&tmp)//防止自赋值
    {
        free();
        elements = tmp.elements;
        first_free = tmp.first_free;
        cap = tmp.cap;
        tmp.cap=tmp.first_free=tmp.elements=nullptr;
    }
    return *this;
}


StrVec::~StrVec()
{
    cout << "hello\n";
    free();
}

/* void StrVec::push_back(const string & str)
{
    chk_n_alloc();
    alloc.construct(first_free++,std::move(str));//这样效率会更高
    //以上写法不好说效率　　　　　　　　　　　　　　　　//上面是我没学函数的移动版本时写的　错误显然
}
 */

void StrVec::push_back(const string &str)
{
    chk_n_alloc();
    alloc.construct(first_free++,str);
}

//对于函数同时提供拷贝版本与移动版本　会使效率提高
void StrVec::push_back(string &&str)
{
    chk_n_alloc();
    alloc.construct(first_free++,std::move(str));
}

pair<string*,string*> 
StrVec::alloc_n_copy(const string *a,const string *b)
{
    //分配一段原始的内存
    auto data = alloc.allocate(b-a);
    //把a 到 b 的元素拷贝到data
    return {data,uninitialized_copy(make_move_iterator(a),make_move_iterator(b),data)};
    //利用移动迭代器　提高效率
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
    //shared_ptr<int>str = make_shared<int>(new int(5));
    StrVec temp;
    temp.push_back("hello");
    cout << temp.capacity() << endl;
    temp.push_back("world");
    temp.push_back("nihao");
    cout << temp.capacity() << endl;
    //StrVec tmp=std::move(temp);
    //StrVec tmp=temp;
    StrVec tmp;
    tmp = std::move(temp);//并没有调用析构函数
    cout << "up\n";
    cout << tmp.capacity() << endl;
    cout << temp.capacity() << endl;
    return 0;
    //移动构造函数的优缺点到这里就很清楚了
    //优：效率高，避免了无意义的拷贝
    //缺：会使移后源对象进行析构函数　
    //结论：在确保不需要等号后面的数据时　使用移动拷贝控制函数　得到效率的提升
}