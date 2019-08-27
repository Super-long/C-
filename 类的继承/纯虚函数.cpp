#include<memory>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;

class Quote
{
    public:
        Quote() = default; //没有指针 默认即可
        Quote(const string &book,double sales_price):
            bookNo(book),price(sales_price){}
        string isbn()const {return bookNo;}
        //返回销售总额
        virtual double net_price(size_t n) const
        {return n*price;} 
        virtual void debug() const;
        virtual ~Quote() = default;
    private:
        string bookNo;  //书籍编号
    protected:
        double price=0.0;//不打折价格 默认为零
};

void Quote::debug() const 
{
    cout << "bookno: " << bookNo << endl;
    cout << "price : " << price  << endl;
}

class Disc_quote : public Quote
{
    public:
        Disc_quote() = default;
        Disc_quote(const string& bookNo,double price,size_t qua,double dis):
            Quote(bookNo,price),quantity(qua),discount(dis){}
        virtual double net_price(size_t) const = 0;//纯虚函数
    protected: //派生类可直接使用
        size_t quantity=0;//折扣适用的购买量
        double discount=0.0;//折扣
};

class Bulk_quote : public Disc_quote
{
    public:
        Bulk_quote() = default;
        Bulk_quote(const string& bookNo,double price,size_t qua,double dis):
            Disc_quote(bookNo,price,qua,dis){}
        virtual double net_price(size_t) const override;
};

double Bulk_quote::net_price(size_t ret) const
{
    if(ret>=quantity)
    return quantity*(1-discount)*price+(ret-quantity)*price;
    else 
    return ret*(1-discount)*price;
}

int main()
{
    //Disc_quote tmp;//不能实例化对象
    return 0;
}