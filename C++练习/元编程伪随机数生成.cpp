#include<bits/stdc++.h>
using namespace std;


template<unsigned N>
struct RandomGen {
    struct next {
        static const unsigned value = N * 1103515245 + 12345;
        typedef RandomGen<value> type;
    };
};

int main(){
    RandomGen<122> ad;
    cout << RandomGen<122>::next::value << endl;
    cout << RandomGen<122>::next::type::next::value << endl;    
    //cout << ad.next.value << endl;
    return 0;
}