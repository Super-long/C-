#include <bits/stdc++.h>
using namespace std;

int main(){
list<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
list<int> lst2 ={10}, lst3={10},lst4={10};
copy(lst.cbegin(), lst.cend(), back_inserter(lst2));
//lst2包含10,1,2,3,4,5,6,7,8,9
copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));//元素将被插入到给定迭代器所表示的元素之前
//lst3包含1,2,3,4,5,6,7,8,9,10
copy(lst.cbegin(), lst.cend(), front_inserter(lst4));//元素总是插入到容器第一个元素之前
//lst4包含9,8,7,6,5,4,3,2,1,10
for(auto x : lst2){
    cout << x << " ";
}
putchar('\n');
for(auto x : lst3){
    cout << x << " ";
}
putchar('\n');
for(auto x : lst4){
    cout << x << " ";
}
putchar('\n');
}