#ifndef CHAR_TRAITS_H_
#define CHAR_TRAITS_H_

namespace String{

    template<typename type>
        struct char_traits_{
            using char_type = type;
            using int_type  = long int;
        };

    template<typename type>
        struct Char_traits : public char_traits_<type>{};
//感觉像是一个奇异循环模板

    template<>
        struct Char_traits<char>{
            using char_type = char;
            using int_type = int;
            static constexpr void 
            assign(char_type& _c1, char_type& _c2){
                _c1 = _c2;
            }

            static constexpr bool
            eq(const char_type& _c1, const char_type& _c2){
                return _c1 == _c2;
            }

            static constexpr bool
            lt(const char_type& _c1, const char_type& _c2){
                return (static_cast<unsigned char>(_c1)
		            < static_cast<unsigned char>(_c2));
            }
    };
}

#endif