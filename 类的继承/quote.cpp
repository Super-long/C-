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
        virtual ~Quote() = default;
    private:
        string bookNo;  //书籍编号
    protected:
        double price=0.0;//不打折价格 默认为零
};

class Bulk_Quote : public Quote
{
    public:
        Bulk_Quote() = default;
        Bulk_Quote(const string&book,double sales_price,size_t min,double discount)
            :Quote(book,sales_price),min_qty(min),discount(discount){}
        double net_price(size_t n) const override;//显式的声明用成员函数覆盖了继承的虚函数
    private:
        size_t min_qty = 0;//到达最低折扣的购买量
        double discount = 0.0;//小数表示的折扣额
};

double Bulk_Quote::net_price(size_t n) const
{
    if(n<=min_qty)
    return (1-discount)*price*n;
    else 
    return n*price;
}