#include <bits/stdc++.h>
using namespace std;

#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

class Test {
private:
  int num;

public:
  Test(int x):num(x){std::cout << "constructed\n";}

  /*拷贝构造函数*/
  Test(const Test &obj) {
      num = obj.num;
      std::cout << "copy constructed\n";
  }

  /*C++11 支持的 转移构造函数*/
  Test (Test &&obj) {
      num = std::move(obj.num);
      std::cout << "moved constructed\n";
  }

};

int main() {
    vector<Test> arr;
    vector<Test> t_arr;
    Test tes(2);
    std::cout << "push_back : Test(1)\n";
    arr.push_back(1);

    std::cout << "push_back : Test(tes)\n";
    arr.push_back(tes);

    
    std::cout << "emplace_back : Test(1)\n";
    t_arr.emplace_back(1);

    std::cout << "emplace_back : Test(tes)\n";
    t_arr.emplace_back(tes);

    return 0;
}
