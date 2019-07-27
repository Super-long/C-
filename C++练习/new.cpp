#include<iostream>
#include<cstdlib>
#include<memory>
using namespace std;
int *p=new int[42];
int main()
{   
    int m(5);
    int i(0);
    while(m--)
    {
        cin >> *(p+i++);
    }
    for(int i=0;i<5;i++)
    cout << *(p+i) << " " << endl;
    delete [] p;

    auto *o=new auto(10);
    shared_ptr<int> k(o);
    cout << *k << endl;
    cout << *o << endl;
    //delete o;

    auto *l=new int[10]{1,2,3,4,5};
    shared_ptr<int[]> a(l,[](int *p){delete [] p;});
    cout << a[3] <<"" <<*(a.get()+3) << endl;
    cout << a.use_count() << endl;
    a.reset();
    //delete [] l;
    return 0;
}