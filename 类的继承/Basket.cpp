//这个代码有点漂亮 就像诗一样
#include<set>
#include<memory>
#include<string>
#include<vector>
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
        Quote(const Quote &) = default;
        Quote(Quote &&) = default;
        virtual Quote* clone() const & {return new Quote(*this);} //const不希望修改原值
        virtual Quote* clone() && {return new Quote(std::move(*this));}
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

class Bulk_Quote : public Quote
{
    public:
        Bulk_Quote() = default;
        Bulk_Quote(const string &book,double sales_price,size_t min,double discount)
            :Quote(book,sales_price),min_qty(min),discount(discount){}
        virtual double net_price(size_t n) const override;//显式的声明用成员函数覆盖了继承的虚函数
        virtual void debug() const override;
        Bulk_Quote(const Bulk_Quote &) = default;
        Bulk_Quote(Bulk_Quote &&) = default;
        virtual Bulk_Quote* clone() const & {return new Bulk_Quote(*this);} //const不希望修改原值
        virtual Bulk_Quote* clone() && {return new Bulk_Quote(std::move(*this));}
    private:
        size_t min_qty = 0;//到达最低折扣的购买量
        double discount = 0.0;//小数表示的折扣额
};

void Bulk_Quote::debug() const
{
    Quote::debug();//回避虚函数机制
    cout << "min_qty:" << min_qty << endl;
    cout << "discount:"<< discount<< endl;
}

double Bulk_Quote::net_price(size_t n) const
{
    if(n<=min_qty)
    return (1-discount)*price*n;
    else 
    return n*price;
}

class Basket //购物车
{
    public:
        void add_item(const shared_ptr<Quote> &sale)
        {items.insert(sale);}
        //为了对用户友好 写一个直接传对象的类
        void add_item(const Quote &sale)//利用多态
        {items.insert(make_shared<Quote>(*sale.clone()));}
        void add_item(Quote &&sale) //右值在有名字时也是左值 所以要再move一下
        {items.insert(make_shared<Quote>(*std::move(sale).clone()));}
        double total_receipt(ostream &) const;
    private:
        double print_total(ostream &,Quote &,size_t) const; //这个接口不希望对用户可见
        static bool compare(const shared_ptr<Quote> &rh,const shared_ptr<Quote> &lh){
            return rh->isbn() < lh->isbn(); //按照书籍编号排序
        }
        multiset<shared_ptr<Quote>,decltype(compare)*> items{compare};
};

double Basket::print_total(ostream &os,Quote &ans,size_t total) const
{
    double tmp = ans.net_price(total);
    os << ans.isbn() << ": " << total << " --> " << tmp << endl;
    return tmp;
}

double Basket::total_receipt(ostream &os) const
{
    double sum = 0.0;
    for(auto iter = items.cbegin();
    iter!=items.cend();iter=items.upper_bound(*iter)){
        sum+=print_total(os,**iter,items.count(*iter));//第一次解引用是迭代器 第二次是智能指针
    }
    os << "Total Sales : " << sum << endl;
    return sum;
}

int main()
{
    Basket bas;
    Quote tmpa("10",100);
    Bulk_Quote tmpb("11",100,10,0.3);
    bas.add_item(tmpa);
    bas.add_item(tmpb);
    bas.total_receipt(cout);
    return 0;
}   