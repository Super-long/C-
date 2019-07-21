#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

struct Review{
    std::string title;
    int rating;
};

using std::string;
bool operator<(const Review &s1,const Review &s2)
{
    if(s1.title<s2.title)
        return true;
    if(s1.title==s2.title && s1.rating<s2.rating)
        return true;
    return false;
}             //重载一个容器类的<运算符 为了可以使用sort
bool Fillreview(Review & rr);
void showreview(const Review & rr);

int main()
{
    using std::cout;
    using std::vector;
    vector<Review> books;
    Review temp;
    while(Fillreview(temp))
        books.push_back(temp);
    int num=books.size();
    if(num>0){
        for(int i=0;i<num;i++)
            showreview(books[i]);
        vector<Review>::iterator pd;
        for(pd=books.begin();pd!=books.end();pd++)
            showreview(*pd);
        vector<Review> oldlist(books);   //拷贝一份
        if(num>3)
        {
            books.erase(books.begin()+1,books.begin()+3);
            for(pd=books.begin();pd!=books.end();pd++)
                showreview(*pd);
            books.insert(books.begin(),oldlist.begin()+1,oldlist.begin()+3);
            for(pd=books.begin();pd!=books.end();pd++)
                showreview(*pd);
        }
        books.swap(oldlist);
        cout << "转换后\n";
        for(pd=books.begin();pd!=books.end();pd++)
            showreview(*pd);
        std::sort(oldlist.begin(),oldlist.end());
        for(int i=0;i<oldlist.size();i++)
            showreview(oldlist[i]);
    }
}
bool Fillreview(Review & rr)
{
    std::cout << "enter books title(quit to quit): ";
    std::getline(std::cin,rr.title);
    if(rr.title=="quit")
        return false;
    std::cout << "enter books rating:\n";
    std::cin >> rr.rating;
    if(!std::cin) return false;
    while(std::cin.get()!='\n')
        continue;
    return true;
}

void showreview(const Review & rr)
{
    std::cout << rr.title <<"'s rating is " << rr.rating << std::endl;
}