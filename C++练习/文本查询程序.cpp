#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<sstream>
#include<fstream>
using namespace std;

class QueryResult
{
    private:
        string word;//查询的单词
        shared_ptr<vector<string>> file;
        shared_ptr<set<size_t>> page;
    public:
        QueryResult(string &s,shared_ptr<vector<string>>f,shared_ptr<set<size_t>> p)
        :word(s),file(f),page(p){}
        void print();
};

class TextQuery
{
    //friend class QueryResult;
    private:
        shared_ptr<vector<string>> ptr;
        map<string,shared_ptr<set<size_t>>>mp; //使用set也是为了快速检索
    public:
        TextQuery(ifstream &);
        QueryResult query(string &)const; //仅查询当然不希望修改
};

void QueryResult::print()
{
    auto x = page->size(); //总页数
    for(auto a : *page)
    {
        cout << "lines " << a+1 << ":" << *(file->begin()+a) << endl;
        //不使用下标运算符的原因是因为那样多调用一次函数
    }
}

TextQuery::TextQuery(ifstream &is):ptr(new vector<string>)
{
    string str;
    while(getline(is,str))
    {
        if(str=="q") break;
        else
        {
            ptr->push_back(str);
            int n=ptr->size()-1; //下标
            istringstream line(str);
            string word;
            while(line >> word)
            {
                if(mp.find(word) == mp.end()) //更优于直接赋值
                mp[word].reset(new set<size_t>);
                //mp[word]=make_shared(set<size_t>);
                mp[word]->insert(n);//在set中存入出现单词的行数
            }
        }
    }
}

QueryResult TextQuery::query(string & str)const
{
    auto loc=mp.find(str);
    if(loc==mp.end())
    {
        static shared_ptr<set<size_t>> se;
        return QueryResult(str,ptr,se);
    }else
    return QueryResult(str,ptr,loc->second);
    //mp[str]; //函数被限定为const 使用mp有可能修改数据 所以不能直接使用数据成员
}

int main()
{
    ifstream fcin;
    fcin.open("test111.txt");
    TextQuery tt(fcin);
    string w("hello");
    QueryResult qq=tt.query(w);
    qq.print();
    fcin.close();
    return 0;
}