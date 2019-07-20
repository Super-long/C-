//利用peek来判断是否超过所设的字符串限制 超过会提示
#include<iostream>
const int len=35;
inline void eatline(){while(std::cin.get()!='\n')continue;}

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    char name[len];
    char title[len];
    cin.get(name,10);
    if(cin.peek()!='\n')
    cout << "only this name is useful\n";
    cout << name << endl;
    eatline();
    cin.get(title,10);
    if(cin.peek()!='\n')
    cout << "we are forced to truncate you title\n";
    cout << title << endl;
    return 0;
}