#include <array>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// 希望能够扩展std::vector的内容作为一个函数的实参输入

template <std::size_t... I>
std::vector<std::size_t> make_index_vector(std::index_sequence<I...>) {
    return {I...};
}

/*
 * apply underline implementation by invoke "func(c[0]...c[N-1] )
 * typename R         : decalre type of return value for the function signature
 * typename... Args   : decalre type of parameters for the function signature
 * typename Container : decalre type of parameters for the function input values
 *                      (could be any type that operator[] supported, such as  
 *                      std::vector)
 * size_t... I        : indexing list of the contianer[0 ... N-1]
 */
// 显然使用的是容器的前N个值 看名字就知道index_sequence是做下标的
template <typename R, typename... Args, typename Container, size_t... I>
R apply_impl(R (*func)(Args...), const Container& c, std::index_sequence<I...>) {
    return (*func)(c[I]...);   // c[I]挺骚
}

/*
 * invoke "func"(including return value) with container "c" as parameter
 * typename R         : decalre type of return value for the function signature
 * typename... Args   : decalre type of parameters for the function signature
 * typename Container : decalre type of parameters for the function input values
 *                      (could be any type that operator[] supported, such as 
 *                      std::vector)
 */
template <typename R, typename... Args, typename Container>
R apply(R (*func)(Args...), const Container& c) {
    printf("%s %lu\n", __func__, sizeof...(Args));
    return apply_impl(func, c, std::make_index_sequence<sizeof...(Args)>());
}

/*
 * invoke "func"(without return value) with container "c" as parameter
 * typename... Args   : decalre type of parameters for the function signature
 * typename Container : decalre type of parameters for the function input values
 *                      (could be any type that operator[] supported, such as 
 *                      std::vector)
 */
template <typename... Args, typename Container>
void apply(void (*func)(Args...), const Container& c) {
    printf("%s %lu\n", __func__, sizeof...(Args));
    apply_impl(func, c, std::make_index_sequence<sizeof...(Args)>());
}

struct context {
    static int add(int a, int b) {
        return a + b;
    }
};

void add_void(int a, int b) {
    printf("void-add %d + %d = %d\n", a, b, a + b);
}

int add(int a, int b) {
    printf("int-add %d + %d = %d\n", a, b, a + b);
    return a + b;
}

int main() {
    std::vector<int> vt = {1, 2};
    // 这样在编译期就可以推导出函数的参数了
    std::cout << apply(context::add, vt) << std::endl;

    // 用容器的内容作为函数的参数

    using array_type = std::array<int, 10>;
    // 这样显然只能是顺序的 更方便的赋初始值
    auto vec = make_index_vector(std::make_index_sequence<std::tuple_size<array_type>::value>());
    for (auto i : vec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

// g++ integer_sequence.cpp -o integer_sequence --std=c++14]