#ifndef BASE_STRING_H_
#define BASE_STRING_H_

#include<initializer_list>
#include<exception>

namespace String{

    template<typename type, typename Traits, typename Alloc>
    class Basic_string{
        private:
            Alloc _alloc_;
            Traits _traits_;//这个成员需要吗 我们只需要函数
            size_type _String_length;

            enum {initial_capacity = 15 / sizeof(type)};

            union{
                type initial_buf[static_cast<int>(initial_capacity)];
                size_type alloc_capacity;
            };

        private:
/*------------------------------------------------*/
        //Following is to encapsulate the interface inplementation.  

/**
 *  _S_expansion() is for apply for new capacity and delete old 
    buffers as capacity increases.
 *  which has meaningless calculations I think.
 */
        void _S_expansion(size_type pos, size_type len1, const type* para, size_type len2);    
        
        
        public:
/*------------------------------------------------*/
        //Following is a constructor part.
            Basic_string() : _traits_(Traits()), _alloc_(Alloc())
            {} //TODO: is a default construct function.

            //from Nth to the N+pos th
            Basic_string(const Basic_string& _str, size_type n, size_type pos){

            }

            Basic_string(const Basic_string& _str, size_type n, size_type pos
            const Alloc& _all_) : _alloc_(_all_){

            }

            //from the Nth to the end.
            Basic_string(const Basic_string& _strm, size_type n);

            explicit Basic_string(Alloc&& _a) noexcept :
                _alloc_(std::move(_a)){

                }
            
            explicit Basic_string(const Alloc& _a) noexcept : 
                _alloc_(_a){

                }

            //copy construct function.
            Basic_string(Basic_string&& str) noexcept{

            }

            Basic_string(const Basic_string& str) {

            }

            Basic_string(const type* str, size_type n,
                Alloc& _all_ = Alloc()) : _alloc_(_all_){

                }

            Basic_string(cosnt type* str, Alloc& _all_ = Alloc())
            : _alloc_(_all_){

            }

            Basic_string(size_type n, type ch, Alloc& _all_ = Alloc())
            :_alloc_(_all_){

            }
            
            Basic_string(std::initializer_list<char> list_,
            Alloc& _all_ = Alloc()) : _alloc_(_all_){

            }

            Basic_string(const Basic_string& str,
            Alloc _all_) : _alloc_(_all_){

            }

            Basic_string(const Basic_string&& str,
            Alloc _all_) noexcept : _alloc_(_all_){

            }

/*------------------------------------------------*/
        //Following is a capacity function.

            size_type 
            size() const noexcept{
                return _String_length;
            }

            size_type
            length() const noexcept{
                return _String_length;
            }

            size_type
            max_size() const noexcept{
                //return (Alloc_Traits::max_size())
                //没办法实现 目前来说
            }

            //尺寸变小 多余的部分裁掉 尺寸变小 多余的部分用第二个参数填充
            void resize(size_type n, type ch);

            void resize(size_type n){
                this->resize(n, type());
            }

            size_type //经测试初始值为15
            capacity() const noexcept{

            }

#if __cplusplus >= 201103L
            void 
            shrink_to_fit() noexcept{
                if(capacity() > size()){
                    //这个函数 库中的实现太sb了 
                }
            }
#endif
            //容量初始15 reserve15-30之间为30 以上参数多少是多少
            void reserve(size_type inital_cap);

            void clear() noexcept{
                _String_length = 0;
            }

            bool empty() const noexcept{
                return this->length() == 0;
            }

/*------------------------------------------------*/
    //Following is a Element access.

/*
    Actually, the implementation of this function is not accurate.
    correct version dont't check parameter. only in at(), function 
    will perform boundary checks.
*/
            const_reference 
            operator[](size_type pos) const{
                if(pos > this->size())
                    throw std::out_of_range("'String[] 136行' out of range.");
                //TODO: Not sure where the value exists now.
                //return 
            }

            //
            reference 
            operator[](size_type pos){
                if(pos > this->size())
                    throw std::out_of_range("'String[] 144行' out of range.");
                //TODO
            }

/**
 *  @return Read-only (const) reference to the character.
 */
            const_reference
            at(size_type n) const{
                if(pos > this->size())
                    throw std::out_of_range("'String[] 158行' out of range.");
                //TODO
            }

/**
 *  @return Read/write reference to the character.
 */
            reference
            at(size_type n){
                if(pos > this->size())
                    throw std::out_of_range("'String[] 158行' out of range.");
                //TODO
            }

#if __cplusplus >= 201103L

        reference
        front() noexcept{
            
        }

        const_reference
        front() const noexcept{

        }

        reference
        back() noexcept{

        }

        const_reference
        back() const noexcept{

        }

#endif

/*------------------------------------------------*/
    //Following is a Member constants.

static const size_type	npos = static_cast<size_type>(-1);

/*------------------------------------------------*/
    //Following is a Member Modifiers.


/*------------------------------------------------*/
    //Following is a String operations


/*------------------------------------------------*/
    //Following is a Non-member function overloads

        /*
        template <class Type> struct rebind {
        typedef allocator<Type> other;
        };
        */  
       //reference part from cpluscplus and basic_string.h;  
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
        
        
        };
    
}

#endif