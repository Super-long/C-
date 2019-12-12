#ifndef _STRINGFED_H_
#define _STRINGFED_H
#include<string>
#include<memory>
#include"Char_traits.h"
std::string str;
namespace String{
    template<typename Char_type, typename _Traits = Char_traits<Char_type>,
    typename _Alloc = std::allocator<Char_type>>
    class Basic_String;

    using string = Basic_String<char>;

#ifdef _GLIBCXX_USE_WCHAR_T

    using wstring = Basic_String<wchar_t>;  
 
#endif//测试能否支持C++11编译

#if ((__cplusplus >= 201103L) \
     && defined(_GLIBCXX_USE_C99_STDINT_TR1))
  using u16string = Basic_String<char16_t>;

  using u32string = Basic_String<char32_t>;

#endif

}

#endif