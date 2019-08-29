#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;

template<typename T,unsigned U>
T* end(const T(*p1)[U])
{
    return p1+U;
}

template<typename T,unsigned U>
T* begin(const T(*p1)[U])
{
    return p1;
}