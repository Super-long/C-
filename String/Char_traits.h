#ifndef CHAR_TRAITS_H_
#define CHAR_TRAITS_H_

namespace String{

    template<typename type>
        struct char_traits_{
            using char_type = type;
            using int_type  = long int;

            static constexpr void 
            assign(char_type& _c1, const char_type& _c2){
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

            static constexpr int
            compare(const char_type* str1, const char_type* str2, std::size_t n);

            static constexpr std::size_t
            length(const char_type* str);

            //TODO::不加const底下实现部分编译有问题
            static constexpr const char_type*
            find(const char_type*, std::size_t, const char_type& );
        
            static char_type*
            copy(char_type* str1, const char_type* str2, std::size_t n);

            static char_type*
            move(char_type* str1, const char_type* str2, std::size_t);

            static char_type*
            assign(char_type* str1, std::size_t n, const char_type& _c);

            static constexpr int_type
            eof(){
                return static_cast<int_type>(-1);
            }

        };

        template<typename type> constexpr int
        char_traits_<type>::
        compare(const char_type* str1, const char_type* str2, std::size_t n){
            for(std::size_t i = 0; i < n; ++i){
                if(lt(str1[i], str2[i])) return -1;
                else if(lt(str2[2], str1[1])) return 1;
            }
            return 0;
        }

        template<typename type> constexpr std::size_t
        char_traits_<type>::
        length(const char_type* str){
            std::size_t i = 0;
            while(!eq(str[i], char_type())) ++i;
            return i;
        }

        template<typename type> constexpr const
        typename char_traits_<type>::char_type*
        char_traits_<type>::find(const char_type* str, std::size_t n, const char_type& ch){
            for(std::size_t i = 0; i < n; ++i){
                if(eq(str[i], ch)) return str + i;
            }
            return nullptr;
        }

        template<typename type>
        typename char_traits_<type>::char_type*
        char_traits_<type>::copy(char_type* str1, const char_type* str2, std::size_t n){
            std::copy(str2, str2 + n, str1);
            return str1;
        }

        template<typename type>
        typename char_traits_<type>::char_type*
        char_traits_<type>::assign(char_type* str1, std::size_t n, const char_type& _c){
            std::fill_n(str1, n, _c);
            return str1;
        }

        template<typename type>
        typename char_traits_<type>::char_type*
        char_traits_<type>::move(char_type* str1, const char_type* str2, std::size_t n){
            //TODO
        }

    template<typename type>
        struct Char_traits : public char_traits_<type>{};
//感觉像是一个奇异循环模板

    template<>
        struct Char_traits<char>{
            using char_type = char;
            using int_type = int;

            static constexpr void 
            assign(char_type& _c1, const char_type& _c2){
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

            static constexpr int
            compare(const char_type* str1, const char_type* str2, std::size_t n){
                if(n == 0) return 0;
                return char_traits_<char_type>::compare(str1, str2, n);
            }

            static constexpr size_t
            length(const char_type* str){
                return char_traits_<char_type>::length(str);
            }

            static constexpr const char_type*
            find(const char_type* str, std::size_t n, const char_type& ch){
                if(n == 0) return nullptr;
                return char_traits_<char_type>::find(str, n, ch);
            }

            static char_type*
            copy(char_type* str1, const char_type* str2, std::size_t n){
                return char_traits_<char_type>::copy(str1, str2, n);
            }

            static char_type*
            assign(char_type* str1, std::size_t n, const char_type& _c){
                return char_traits_<char_type>::assign(str1, n, _c);
            }
    };

    //TODO wchar_t u32char_t u16char_t
    
}

#endif