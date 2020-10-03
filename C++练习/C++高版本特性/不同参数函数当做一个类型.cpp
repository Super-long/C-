#include<bits/stdc++.h>
using namespace std;

template <typename R, typename... Args, typename Container, size_t... I>
R apply_impl(R (*func)(Args...), const Container& c, std::index_sequence<I...>) {
    return (*func)(c[I]...);   // c[I]挺骚
}

template <typename R, typename... Args, typename Container>
R apply(R (*func)(Args...), const Container& c) {
    return apply_impl(func, c, std::make_index_sequence<sizeof...(Args)>());
}
struct one{
    int lhs;
    int rhs;
};

struct two{
    string str;
};



void* func_one(void* para) {
    one* temp = static_cast<one*>(para);
    cout << temp->lhs << endl;
    return nullptr;
}

void* func_two(void* para){
    two* temp = static_cast<two*>(para);
    cout << temp->str << endl;
    return nullptr;
}

unordered_map<string, function<void*(void*)>> mp;


int main(){
    mp["login"] = func_one;
    mp["exit"] = func_two;

    struct two lhs;
    lhs.str = "nihao";
    mp["exit"](static_cast<void*>(&lhs));
    return 0;
}