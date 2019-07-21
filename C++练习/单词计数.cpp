#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include<iterator>
#include<cctype>
using namespace std;
char toLower(char & ch)
{
    return tolower(ch);
}
void show(const string & str)
{
    cout << str << " ";
}
string Tolower(string & st);
int main()
{
    vector<string> words;
    cout << "please enter a number of strings\n";
    string input;
    while(cin >> input && input !="quit")
        words.push_back(input);
    cout << "your entered the following words:\n";
    for_each(words.begin(),words.end(),show);
    cout << endl;
    set<string> wordst;
    transform(words.begin(),words.end(),
        insert_iterator<set<string> > (wordst,wordst.begin()),
        Tolower);
    cout << "this is a list of wordst:\n";
    for_each(wordst.begin(),wordst.end(),show);

    map<string,int> mp;
    for(auto pr=wordst.begin();pr!=wordst.end();pr++)
        mp[*pr]=count(words.begin(),words.end(),*pr);
    for(auto pr=wordst.begin();pr!=wordst.end();pr++)
        cout << *pr << "  :" << mp[*pr] << endl;
    return 0;
}
string Tolower(string & st)
{
    transform(st.begin(),st.end(),st.begin(),toLower);
    //tolower返回的是int  接受到的元素也是int 所以不能直接放在这里
    //编辑器认为函数与元素类型最好匹配
    return st;
}