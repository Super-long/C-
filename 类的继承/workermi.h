//这个代码使用了多重继承中的虚基类
#ifndef WORKERMI_H_
#define WORKERMI_H_

#include<string>
using std::string;

class worker
{
    private:
        string fullname;
        long id;
    protected:
        virtual void data() const;
        virtual void get(); 
    public:
        worker():fullname("Null name"),id(0L){}
        worker(const string &s,long n):fullname(s),id(n){}
        virtual ~worker() = 0;
        virtual void set() = 0;
        virtual void show()const = 0;
};

class waiter : virtual public worker//也是公有继承
{
    private:
        int panache;
    protected:
        void data()const;//输出数据
        void get();//得到数据
    public:
        waiter():worker(),panache(0){}
        waiter(const string &s,long n,int p=0):
            worker(s,n),panache(p){}
        waiter(const worker & wk,int p=0):
            worker(wk),panache(p){}
        void set();
        void show() const;
};

class singer : virtual public worker
{
    protected:
        void data() const;
        void get();
        enum{other,alto,contralto,sprano,bass,baritone,teror};
        enum{Vtypes = 7};
    private:
        static char *pv[Vtypes];  //存储字符串
        int voice;
    public:
        singer() : worker(),voice(0){}
        singer(const string &s,long n,int v=0):
            worker(s,n),voice(v){}
        singer(const worker & wk,int v=0):
            worker(wk),voice(v){}
        void set();
        void show() const;
};

class singingwaiter :public singer,public waiter
{
    protected:
        void data() const;
        void get();
    public:
        singingwaiter(){}
        //使用默认构造函数 因为没有私有成员 不用初始化
        singingwaiter(const string &s,long n,int p=0,int v=0):
            worker(s,n),waiter(s,n,p),singer(s,n,v){}
        singingwaiter(const worker & wk,int p=0,int v=0):
            worker(wk),waiter(wk,p),singer(wk,v){}
        singingwaiter(const waiter & wt,int v=0):
            worker(wt),waiter(wt),singer(wt,v){}
        singingwaiter(const singer & wt,int p=0):
            worker(wt),waiter(wt,p),singer(wt){}
        void set();
        void show() const;
};

#endif