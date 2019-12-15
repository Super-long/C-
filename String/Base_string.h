#ifndef BASE_STRING_H_
#define BASE_STRING_H_

#include<initializer_list>
#include<exception>
#include<iterator>
#include<cstring>
#include<ext/alloc_traits.h>
#include<ext/atomicity.h>

#include<iostream>
using std::cout;
using std::endl;
//For debugging

namespace String{

    template<typename type, typename Traits, typename Alloc>
    class Basic_string{
        public:

        /*
        template <class Type> struct rebind {
        typedef allocator<Type> other;
        };
        */  
        //reference part from cpluscplus and basic_string.h;  
        
        using alloc_type = typename __gnu_cxx::__alloc_traits<Alloc>::template
	        rebind<type>::other;

        using Alloc_Traits = __gnu_cxx::__alloc_traits<alloc_type>;

        public:
            using traits = Traits;
            using value_type =  typename Traits::char_type;
            using size_type = typename Alloc_Traits::size_type;
            using difference_type = typename Alloc_Traits::difference_type;
            using reference = typename Alloc_Traits::reference;
            using const_reference = typename Alloc_Traits::const_reference;
            using pointer = typename Alloc_Traits::pointer;
            using const_pointer = typename Alloc_Traits::const_pointer;
    
            //TODU 迭代器和反向迭代器
        
        
        
        private:
            Alloc _alloc_;
            size_type _String_length;
            pointer _True_value;

            enum {initial_capacity = 15 / sizeof(type)};

            
            type initial_buf[static_cast<int>(initial_capacity)];
            size_type alloc_capacity;
            //使用联合体会出现一点点意外 在拷贝时数据总是不对 
            

        private:
/*------------------------------------------------*/
    //Following is to encapsulate the interface inplementation.  

/**
 *  @ _S_expansion() is for apply for new capacity and delete old 
    buffers as capacity increases.
 *  @ which has meaningless calculations I think.
 */
        void _S_assign(Basic_string& str);

        void _S_expansion(size_type pos, size_type len1, const type* para, size_type len2);    
        
        pointer _S_create(size_type& new_capacity, size_type old_capacity);

        static void S_copy_(type* _new_, const type* _old_, size_type n);

        template<typename IntIterator>
        void _S_construct(IntIterator _start, IntIterator _end);

        void _S_construct(size_type n, type para);

        void _S_copy_of_interval(type* ptr, const type* _start, const type* _end){
            this->S_copy_(ptr, _start, static_cast<size_type>(std::distance(_start, _end)));
        }

        pointer _Return_pointer() const noexcept{
            return _True_value;
        }

        pointer _Return_local_pointer(){
            #if __cplusplus >= 201103L
                return std::pointer_traits<pointer>::pointer_to(*initial_buf);
            #else
                return pointer(initial_buf);
            #endif
            //return static_cast<pointer>(initial_buf);
        }

        //TODO 搞清楚这个参数为什么不能直接转换
        const_pointer _Return_local_pointer() const {
            #if __cplusplus >= 201103L
                return std::pointer_traits<const_pointer>::pointer_to(*initial_buf);
            #else
                return const_pointer(initial_buf);
            #endif
            //return static_cast<pointer>(initial_buf);
        }

        Alloc& _Return_alloc() noexcept{
            return _alloc_;
        }

        bool _Data_is_local() const noexcept{
            return this->_Return_pointer() == this->_Return_local_pointer();
        }

        void _S_SetUp_date(pointer p_) noexcept{
            _True_value = p_;
        }

        void _S_SetUp_capacity(size_type n) noexcept{
            alloc_capacity = n;
        } 

        void _S_SetUp_length(size_type n) noexcept{
            _String_length = n;
        }

        void _S_Delete(){
            if(!_Data_is_local()){
                _alloc_.deallocate(_True_value, static_cast<size_type>(alloc_capacity));
            }
        }

        void _S_assign(type* ptr, size_type n, type ch){
            if(n == 1)
                traits::assign(*ptr, ch);
            else 
                traits::assign(ptr, n, ch);
        }

        public:
/*------------------------------------------------*/
        //Following is a constructor part.
            Basic_string() :
            _True_value(_Return_local_pointer()), _alloc_(Alloc())
            {_S_SetUp_length(0);}

            //from posth to the N+pos th
            Basic_string(const Basic_string& _str, size_type pos, size_type n):
            _True_value(_Return_local_pointer()), _alloc_(Alloc()){
                _S_SetUp_length(0);
                size_type len = _str.length();
                size_type _end = pos + n;
                if(_end > len) _end = len;
                if(!_str._Data_is_local())
                _S_construct(_str._Return_pointer() + pos,
                             _str._Return_pointer() + _end); 
                else
                _S_construct(_str._Return_local_pointer() + pos,
                             _str._Return_local_pointer() + _end); 
            }

            Basic_string(const Basic_string& _str, size_type pos, size_type n,
            const Alloc& _all_) :_True_value(_Return_local_pointer()), _alloc_(_all_){
                size_type len = _str.length();
                size_type _end = pos + n;
                if(_end > len) _end = len;
                if(!_str._Data_is_local())
                _S_construct(_str._Return_pointer() + pos,
                             _str._Return_pointer() + _end); 
                else
                _S_construct(_str._Return_local_pointer() + pos,
                             _str._Return_local_pointer() + _end); 
            }

            //from the Nth to the end.
            Basic_string(const Basic_string& _str, size_type n, const Alloc& _all = Alloc()) : 
                _True_value(_Return_local_pointer()),_alloc_(Alloc(_all)){
                    size_type _start_ = n;
                    size_type len = _str.length();
                    if(n > len)  _start_ = len;
                    
                    if(!_str._Data_is_local())
                    _S_construct(_str._Return_pointer() + n,
                                _str._Return_pointer() + len); 
                    else
                    _S_construct(_str._Return_local_pointer() + n,
                                _str._Return_local_pointer() + len); 
                }

            explicit Basic_string(Alloc&& _a) noexcept :
                _True_value(_Return_local_pointer()), _alloc_(std::move(_a)){
                    _S_SetUp_length(0);
                }
            
            explicit Basic_string(const Alloc& _a) noexcept : 
                _True_value(_Return_local_pointer()), _alloc_(_a){
                    _S_SetUp_length(0);
                }
            /**
             * @ copy construct function.
             * @ A good design idea which is generic code reuse.
             */
            Basic_string(Basic_string&& str) noexcept : 
            _True_value(_Return_local_pointer()), 
            _alloc_(std::move(str._Return_alloc())){
                if(str._Data_is_local()){
                    this->S_copy_(initial_buf, str._Return_local_pointer(), str.length());
                }else{
                    _S_SetUp_date(str._Return_pointer());
                    _S_SetUp_capacity(str.capacity());
                }
                _S_SetUp_length(str.length());
            }

            Basic_string(const Basic_string& str) :
                _True_value(_Return_local_pointer()), 
                _alloc_(Alloc()) {
                _S_construct(str._Return_pointer(), str._Return_pointer() + str.length());
            }
            /**
             * @ str must have at least n characters.
             * @ if str length less than n, Behavior is undefined at this time.
             */
            Basic_string(const type* str, size_type n,
                const Alloc& _all_ = Alloc()) :
                _True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(str, str + n);
                }

            //TODO: what do with const and noconst?
            explicit Basic_string(const type* str, const Alloc& _all_ = Alloc())
                : _True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(str, str + strlen(str));
            }

            explicit Basic_string(type* str, const Alloc& _all_ = Alloc())
                : _True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(str, str + strlen(str));
            }

            Basic_string(size_type n, type ch, const Alloc& _all_ = Alloc())
                :_True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(n, ch);
            }
            
            Basic_string(std::initializer_list<char> list_,
            const Alloc& _all_ = Alloc()) : 
            _True_value(_Return_local_pointer()), _alloc_(_all_){
                _S_construct(list_.begin(), list_.end());
            }

            Basic_string(const Basic_string& str,
            Alloc _all_) : 
            _True_value(_Return_local_pointer()), _alloc_(_all_){
                _S_construct(str._Return_pointer(), str._Return_pointer() + str.length());
            }

            Basic_string(const Basic_string&& str,
            Alloc _all_) noexcept : _alloc_(_all_){
                if(str._Data_is_local()){
                    this->S_copy_(initial_buf, str._Return_local_pointer(), str.length());
                }else{
                    _S_SetUp_date(str._Return_pointer());
                    _S_SetUp_capacity(str.capacity());
                }
                _S_SetUp_length(str.length());
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
                return _alloc_.max_size();
            }

            //尺寸变小 多余的部分裁掉 尺寸变小 多余的部分用第二个参数填充
            void resize(size_type n, type ch);

            void resize(size_type n){
                this->resize(n, type());
            }

            size_type
            capacity() const noexcept{
                return _Data_is_local() ? static_cast<size_type>(initial_capacity)
                                        : alloc_capacity;
            }

#if __cplusplus >= 201103L
            void 
            shrink_to_fit() noexcept{
                if(capacity() > size()){
                    //TODO:这个函数 库中的实现太sb了 
                }
            }
#endif
            void reserve(size_type _ideal);

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
                if(_Data_is_local()) return _Return_local_pointer()[pos];
                return _Return_pointer()[pos];
            }

            reference 
            operator[](size_type pos){
                if(pos > this->size())
                    throw std::out_of_range("'String[] 144行' out of range.");
                if(_Data_is_local()) return _Return_local_pointer()[pos];
                return _Return_pointer()[pos];
            }

/**
 *  @return Read-only (const) reference to the character.
 */
            const_reference
            at(size_type n) const{
                if(n > this->size())
                    throw std::out_of_range("'String[] 158行' out of range.");
                if(_Data_is_local()) return _Return_local_pointer()[n];
                return _Return_pointer()[n];
            }

/**
 *  @return Read/write reference to the character.
 */
            reference
            at(size_type n){
                if(n > this->size())
                    throw std::out_of_range("'String[] 158行' out of range.");
                if(_Data_is_local()) return _Return_local_pointer()[n];
                return _Return_pointer()[n];
            }

#if __cplusplus >= 201103L

        reference
        front() noexcept{
            if(!this->empty())
            return at(0);
            return at(0);
        }

        const_reference
        front() const noexcept{
            if(!this->empty())
            return at(0);
            return at(0);
        }

        reference
        back() noexcept{
            if(!this->empty())
            return at(this->length() - 1);
            return at(0);
        }

        const_reference
        back() const noexcept{
            if(!this->empty())
            return at(this->length() - 1);
            return at(0);
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

        };
    
}

#endif