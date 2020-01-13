#include<bits/stdc++.h>
using namespace std;

//一个函数式风格的快排 functional pragramming
template<typename T>
std::list<T> quick_sort(std::list<T> input){
    if(input.empty()) return input;

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    const T& pivot = *result.begin(); //pivot : 枢纽,中心点

    auto divide_point = std::partition(input.begin(), input.end(),
        [&](const T& t){return t < pivot;});

    std::list<T> lower_part;
    lower_part.splice(lower_part.begin(), input, input.begin(), divide_point);

    auto new_lower(quick_sort(std::move(lower_part)));
    auto new_higher(quick_sort(std::move(input)));

    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_higher);

    return result;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input){
    if(input.empty()) return input;

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    const T& pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(),
        [&](const T& t){return t < pivot;});

    std::list<T> lower_part;
    lower_part.splice(lower_part.begin(), input, input.begin(), divide_point);

    std::future<std::list<T>> new_lower(
        std::async(std::launch::deferred, &parallel_quick_sort<T>, std::move(lower_part))
    );
    std::future<std::list<T>> new_higher(
        std::async(std::launch::deferred, &parallel_quick_sort<T>, std::move(input))
    );

    //这样写有如果写上std::launch_deferred 可能导致死锁
    //答 : 好像并没有出现死锁
    result.splice(result.end(), new_higher.get());
    result.splice(result.begin(), new_lower.get());

    return result;
}

int main(){
    list<int> li({1,2,3,12,6,1,0,23,12});
    auto T = parallel_quick_sort(li);
    for(auto t : T){
        cout << t << " ";
    }
    return 0;
}