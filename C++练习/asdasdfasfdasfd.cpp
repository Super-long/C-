#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;


shared_ptr<int> tmp_ptr(new int(5));
 
void ggg(int *a){
    cout << a << endl;
    cout << "reset\n";
}

int main()
{
    int tmpa = 6;
    shared_ptr<int> ttt(new int(6));
    cout << ttt.get() << endl;

    shared_ptr<int> tmpb_ptr(tmp_ptr);
    cout << tmp_ptr.use_count() << endl;
    tmp_ptr.reset(ttt.get(),ggg);
    cout << tmp_ptr.get() << endl;
    cout << "star\n";
    cout << tmp_ptr.use_count() << endl;
    cout << ttt.use_count() << endl;
    cout << "end\n";
    cout << tmpb_ptr.use_count() << endl;
}