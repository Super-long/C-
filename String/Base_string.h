#ifndef BASE_STRING_H_
#define BASE_STRING_H_

namespace String{

    template<typename type, typename Traits, typename Alloc>
    class Basic_string{
        private:
            Alloc _alloc_;
            Traits _traits_;//这个成员需要吗 我们只需要函数
        
        public:
            Basic_string() : _traits_(Traits()), _alloc_(Alloc())
            {} //TODO 一个默认构造

            Basic_string(const Basic_string& __str, size_type lhs, size_type rhs){

            }

            explicit Basic_string(Alloc&& _a) noexcept :
                _alloc_(std::move(_a)){

                }
            
            explicit Basic_string(const Alloc& _a) noexcept : 
                _alloc_(_a){

                }

            //拷贝构造函数
            Basic_string(Basic_string&& str){

            }

            Basic_string(const Basic_string& str) {

            }

            Basic_string()
            
        



        /*
        template <class Type> struct rebind {
        typedef allocator<Type> other;
        };
        */  

       //参考cpluscplus basic_string.h;  
        using alloc_type = typename __alloc_traits<Alloc>::template
	        rebind<type>::other;

        using Alloc_Traits = __alloc_traits<alloc_type>;

        public:
            using traits = Traits;
            using value_type =  typename Traits::char_type;
            using size_type = typename _Alloc_traits::size_type;
            using difference_type = typename _Alloc_traits::difference_type	difference_type;
            using reference = typename _Alloc_traits::reference;
            using const_reference = typename _Alloc_traits::const_reference;
            using pointer = typename _Alloc_traits::pointer;
            using const_pointer = typename _Alloc_traits::const_pointer;
    
            //TODU 迭代器和反向迭代器

            static const size_type	npos = static_cast<size_type>(-1);
        };
    
}







#endif