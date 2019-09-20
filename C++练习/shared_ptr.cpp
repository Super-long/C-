#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

template <typename T> class Shared_ptr;

template<typename T,typename ... Args>
inline Shared_ptr<T> 
make_Shared(Args&& ... args){
    return Shared_ptr<int>(std::forward<Args>(args)...);
}
//这里只是简单的实现而已　其中并没有涉及到内存的分配　也就使得第一个参数有点浪费

template <typename T>
class Shared_ptr
{
    private:    
        size_t *Ptr_Count;//引用计数
        T* Mem_Ptr;//数据
        void (*Del_Ptr)(T *); //删除器　用于在运行时绑定删除器
    public:
        //默认构造函数
        Shared_ptr():Ptr_Count(nullptr),Mem_Ptr(nullptr),Del_Ptr(nullptr){}
        
        //接收一个参数的构造函数(防止隐性转换)
        explicit Shared_ptr(T *tmp_ptr) try:
        Mem_Ptr(tmp_ptr),Ptr_Count(new size_t(1)),Del_Ptr(nullptr)
        {} catch(const std::bad_alloc &err) {cout << "error in new\n";}
        
        //拷贝构造函数
        Shared_ptr(Shared_ptr &tmp_ptr) noexcept(false){ //模板内部可简化为类名而不需要加类型
            Mem_Ptr = tmp_ptr.Mem_Ptr;
            Ptr_Count = tmp_ptr.Ptr_Count;
            Del_Ptr = nullptr;
            ++*Ptr_Count;
        }
        //拷贝赋值运算符
        void operator=(const Shared_ptr& tmp_ptr) & noexcept(false){
            Shared_ptr(std::move(tmp_ptr));//并没有什么数据成员　所以效率并没有什么提升　练下手
        }
        //移动构造函数
        Shared_ptr(Shared_ptr && tmp_ptr) noexcept:
        Mem_Ptr(tmp_ptr.Mem_Ptr),Ptr_Count(tmp_ptr.Ptr_Count),Del_Ptr(nullptr)
        {++*Ptr_Count;}

        //移动赋值运算符 //强制等号左边为左值
        void operator=(Shared_ptr && ptr) & noexcept{
            Shared_ptr(std::move(ptr));
        }

        //重载解引用运算符
        T& operator*(){
            return *Mem_Ptr;
        }
        T* operator->(){//至于为什么返回一个指针　因为Shared_ptr是一个类 类就应该返回一个成员
            return Mem_Ptr;
        } 
        T* get(){ //返回智能指针所保存的指针　操作危险
            return Mem_Ptr;
        }
        size_t use_count(){
            return *Ptr_Count;
        }
        bool unique(){
            return *Ptr_Count == 1;
        }
        void swap(Shared_ptr &tmp_ptr){
            //测试时使用原版本swap
            //std::swap(*this,tmp_ptr); 这里概念还有问题　搞懂move原理以后再来

            //交换指针效率更高
            std::swap(Mem_Ptr,tmp_ptr.Mem_Ptr);
            std::swap(Ptr_Count,tmp_ptr.Ptr_Count);
            std::swap(Del_Ptr,tmp_ptr.Del_Ptr);
        }
        void reset(){ //当reset为空时　只是把reset的指针
            if(*Ptr_Count == 1){
                delete Mem_Ptr;
                *Ptr_Count = 0; //防止析构时两次delete 用Ptr_count在析构时进行特判
            }else {
                Mem_Ptr = nullptr;
                --*Ptr_Count;
            }
        }
        void reset(T *tmp_ptr){
            if(*Ptr_Count==1){ //本对象是唯一对象则会释放　　　//不唯一的话其他对象还需要这两个指针
                Del_Ptr ? Del_Ptr(Mem_Ptr) : delete Mem_Ptr;
                delete Ptr_Count;
            }else{
                --*Ptr_Count; 
            }
            Mem_Ptr = tmp_ptr;
            Ptr_Count = new size_t(1);//看起来很奇怪　仔细想想　如果count不为零的话其他智能指针还要使用
        }
        //接收一个指针和一个自定义的删除器　用于在析构时正确释放对象　默认为delete
        void reset(T *tmp_ptr,void (*del_ptr)(T *)){
            if(*Ptr_Count==1){
                delete Mem_Ptr;
                delete Ptr_Count;
            }
            --(*Ptr_Count);
            Mem_Ptr = tmp_ptr;
            Ptr_Count = new size_t(1);
            Del_Ptr = del_ptr; //定义一个删除器
        }
        ~Shared_ptr(){
            try{
                cout << "Commen complete the destructor.\n";

                if(Mem_Ptr == nullptr && Ptr_Count == nullptr){ //防止默认构造出现对仅有delete 而无new
                    return;
                }

                if((*Ptr_Count) == 0){ //证明被reset了　特殊处理
                    delete Ptr_Count;
                    Ptr_Count = nullptr;
                    return;
                }
                --*Ptr_Count;
                if(*Ptr_Count==0){
                    Del_Ptr ? Del_Ptr(Mem_Ptr) : delete Mem_Ptr;
                    delete Ptr_Count;
                    Ptr_Count = nullptr;
                    Mem_Ptr = nullptr;
                }
            }catch(...){
                cout << "error in delete\n";
            }
        }
};

//一个测试用的聚合类
struct text{
    int ans;
    int weight;
};

void Del(text* tmp){//聚合类 text 的删除器
    delete tmp;
    cout << "Special complete the destructor.\n";
}

//demo
int main()
{
    cout << "测试make_shared:\n";
    Shared_ptr<int> str=make_Shared<int>(new int(5));
    cout << ": " << *str << endl;
    cout << "测试基本操作\n";
    Shared_ptr<int> tmpa_ptr(new int(10));
    cout << *tmpa_ptr << endl;
    cout << tmpa_ptr.use_count() << endl;
    Shared_ptr<int> tmpb_ptr(tmpa_ptr);
    cout << *tmpb_ptr << endl;
    cout << tmpb_ptr.use_count() << endl;
    
    cout << "交换操作\n";
    Shared_ptr<int> tmp_swap(new int(5));
    cout << *tmpa_ptr << " " << *tmp_swap << endl;
    tmpa_ptr.swap(tmp_swap);
    cout << *tmpa_ptr << " " << *tmp_swap << endl;

    cout << "测试三种参数的reset函数\n";
    tmpa_ptr.reset();
    cout << tmpa_ptr.use_count() << " " << tmpb_ptr.use_count() << endl;

    shared_ptr<text> tmpc_ptr(new text({5,5}));
    cout << (*tmpc_ptr).ans << " " << (*tmpc_ptr).weight << endl;
    tmpc_ptr.reset(new text({10,10}));
    cout << (*tmpc_ptr).ans << " " << (*tmpc_ptr).weight << endl;
    tmpc_ptr.reset(new text({20,20}),Del);//shared_ptr删除器运行时绑定　所以使用指针存储删除器

    cout << "测试get函数\n";
    text *temp_text_ptr = tmpc_ptr.get(); //此函数小心使用 会返回智能指针所维护的指针域
    cout << temp_text_ptr->ans << " " << temp_text_ptr->weight << endl;

    cout << "开始析构\n";

    return 0;
}