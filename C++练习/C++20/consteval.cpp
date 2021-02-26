#include <bits/stdc++.h>
using namespace std;

consteval int sqr(int n) {
  return n*n;
}
constexpr int r = sqr(100);  // OK
 
int x = 100;
int r2 = sqr(x);  // 错误：调用不产生常量
 
consteval int sqrsqr(int n) {
  return sqr(sqr(n)); // 在此点非常量表达式，但是 OK
}
 
constexpr int dblsqr(int n) {
  return 2*sqr(n); // 错误：外围函数并非 consteval 且 sqr(n) 不是常量
}