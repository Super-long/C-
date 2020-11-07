#include<bits/stdc++.h>
using namespace std;

int fun(int a, int b, int c, int d)
{
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	return 0;
}
void bind_test()
{
	auto f = std::bind(fun, std::placeholders::_1, std::placeholders::_2, 300, 400);
	f(100, 200);
}
int main()
{
	bind_test();
    return 0;
}