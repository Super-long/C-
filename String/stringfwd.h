#ifndef _STRINGFED_H_
#define _STRINGFED_H

#include<memory>
#include"Char_traits.h"
#include"Base_string.h"
#include"Base_string.cc"

namespace String{
    template<typename Char_type, typename _Traits = Char_traits<Char_type>,
    typename _Alloc = std::allocator<Char_type>>
    class Basic_String;

    using string = Basic_String<char>;

#ifdef _GLIBCXX_USE_WCHAR_T

    using wstring = Basic_String<wchar_t>;  
 
#endif

#if ((__cplusplus >= 201103L) \
     && defined(_GLIBCXX_USE_C99_STDINT_TR1))
  using u16string = Basic_String<char16_t>;

  using u32string = Basic_String<char32_t>;

#endif

}

#endif