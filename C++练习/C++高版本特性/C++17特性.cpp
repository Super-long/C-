#include<bits/stdc++.h>
#include<tuple>
using namespace std;

void f() {
    map<int, string> m = {
      {0, "a"},
      {1, "b"},  
    };
    for (const auto &[i, s] : m) {
        cout << i << " " << s << endl;
    }
}

// ====================
int main() {
    std::pair a(1, 2.3f);
    auto[i, f] = a;
    cout << i << endl; // 1
    cout << f << endl; // 2.3f
    return 0;
}