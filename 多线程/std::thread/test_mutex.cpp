#include<bits/stdc++.h>
using namespace std;

list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value){
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.emplace_back(new_value);
}

bool list_contains(int value_to_find){
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

stack<int> sta;

int main(){
    sta.pop();
    for(int i=0;i<10;++i){
        add_to_list(i);
    }
}