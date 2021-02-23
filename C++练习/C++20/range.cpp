#include <bits/stdc++.h>
#include <ranges>
using namespace std;

void cpp_11() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::vector<int> even;
    std::copy_if(v.begin(), v.end(), std::back_inserter(even),
                 [](int i) { return i % 2 == 0; });

    std::vector<int> results;
    std::transform(even.begin(), even.end(),
                   std::back_inserter(results),
                   [](int i) { return i * 2; });

    for (int n : results) std::cout << n << ' ';
    putchar('\n');
}

void cpp_20() {
    std::vector<int> v{1, 2, 3, 4, 5};
    for(int i : v   | ranges::views::filter([](int i) { return i % 2 == 0; })
                    | ranges::views::transform([](int i) { return i * 2; })){
        cout << i << " ";
    }
    putchar('\n');
}

int main(){
    cpp_11();
    cpp_20();
    return 0;
}