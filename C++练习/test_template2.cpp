#include <iostream>
#include <string_view>
template<class STR>
using string_view_test = std::basic_string_view<typename STR::value_type>;

typedef string_view_test<std::string> stringPiece;
typedef string_view_test<std::wstring> wstringPiece;

template<typename STR>
size_t copyT(const string_view_test<STR> self)
{
    //doSomething
    return self.size();
}

int main()
{
    stringPiece s("test");
    copyT(s);
    return 0;
}

