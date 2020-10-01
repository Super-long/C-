#include <iostream>
#include <string>
#include <vector>
#include <execution>

int main()
{
	std::cout << std::endl;

	// for_each_n
/*
template< class InputIt, class Size, class UnaryFunction >
InputIt for_each_n( InputIt first, Size n, UnaryFunction f );
按顺序应用给定的函数对象 f 到解引用范围 [first, first + n) 中每个迭代器的结果
*/
	std::vector<int> intVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };                        // 1
	std::for_each_n(std::execution::par,                       // 2
		intVec.begin(), 5, [](int& arg) { arg *= arg; });

	std::cout << "for_each_n: ";
	for (auto v : intVec) std::cout << v << " ";
	std::cout << "\n\n";

	// exclusive_scan and inclusive_scan
	std::vector<int> resVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::exclusive_scan(std::execution::par,                   // 3
		resVec.begin(), resVec.end(), resVec.begin(), 1,
		[](int fir, int sec) { return fir * sec; });

	std::cout << "exclusive_scan: "; // 没看懂为什么全部是1
	for (auto v : resVec) std::cout << v << " ";
	std::cout << std::endl;

	std::vector<int> resVec2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // 就相当于求前缀和 每次用n和n-1进行运算
	std::inclusive_scan(std::execution::par,                   // 5 
		resVec2.begin(), resVec2.end(), resVec2.begin(),
		[](int fir, int sec) { return fir * sec; }, 1);

	std::cout << "inclusive_scan: ";
	for (auto v : resVec2) std::cout << v << " ";
	std::cout << "\n\n";

	// transform_exclusive_scan and transform_inclusive_scan
	std::vector<int> resVec3{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> resVec4(resVec3.size());
	std::transform_exclusive_scan(std::execution::par,         // 6
		resVec3.begin(), resVec3.end(),
		resVec4.begin(), 0,
		[](int fir, int sec) { return fir + sec; },
		[](int arg) { return arg *= arg; });

	std::cout << "transform_exclusive_scan: ";
	for (auto v : resVec4) std::cout << v << " ";
	std::cout << std::endl;

	std::vector<std::string> strVec{ "Only", "for", "testing", "purpose" };             // 7
	std::vector<int> resVec5(strVec.size());

	std::transform_inclusive_scan(std::execution::par,         // 8
		strVec.begin(), strVec.end(),
		resVec5.begin(),
		[](auto fir, auto sec) { return fir + sec; },
		[](auto s) { return s.length(); });

	std::cout << "transform_inclusive_scan: ";
	for (auto v : resVec5) std::cout << v << " ";
	std::cout << "\n\n";

	// reduce and transform_reduce
	std::vector<std::string> strVec2{ "Only", "for", "testing", "purpose" };

	std::string res = std::reduce(std::execution::par,         // 9
		strVec2.begin() + 1, strVec2.end(), strVec2[0],
		[](auto fir, auto sec) { return fir + ":" + sec; });

	std::cout << "reduce: " << res << std::endl;

	// 11 对每个参数应用一个函数以后再合并
	std::size_t res7 = std::transform_reduce(std::execution::par,
		strVec2.begin(), strVec2.end(), 0u,
		[](std::size_t a, std::size_t b) { return a + b; },
		[](std::string s) { return s.length(); }
	    );

	std::cout << "transform_reduce: " << res7 << std::endl;

	std::cout << std::endl;
	
	return 0;
}
