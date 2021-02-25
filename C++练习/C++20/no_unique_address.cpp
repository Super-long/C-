#include <iostream>
 
struct Empty {
    int no;
}; // 空类
 
struct X {
    int i;
    Empty e;
};
 
struct Y {
    int i;
    [[no_unique_address]] Empty e;
};
 
struct Z {
    char c;
    [[no_unique_address]] Empty e1, e2;
};
 
struct W {
    char c[2];
    [[no_unique_address]] Empty e1, e2;
};
 
int main()
{
    // 任何空类类型对象的大小至少为 1
    static_assert(sizeof(Empty) >= 1);
 
    // 至少需要多一个字节以给 e 唯一地址
    static_assert(sizeof(X) >= sizeof(int) + 1);
    X xx;
    printf("%p %p\n", &xx.i, &xx.e);
 
    // 优化掉空成员
    std::cout << "sizeof(Y) == sizeof(int) is " << std::boolalpha 
              << (sizeof(Y) == sizeof(int)) << '\n';
 
    // e1 与 e2 不能共享同一地址，因为它们拥有相同类型，尽管它们标记有 [[no_unique_address]]。
    // 然而，其中一者可以与 c 共享地址。
    static_assert(sizeof(Z) >= 2);
 
    // e1 与 e2 不能拥有同一地址，但它们之一能与 c[0] 共享，而另一者与 c[1] 共享
    std::cout << "sizeof(W) == 2 is " << (sizeof(W) == 2) << '\n';
}