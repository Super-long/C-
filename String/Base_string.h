#ifndef BASE_STRING_H_
#define BASE_STRING_H_

#include<initializer_list>
#include<exception>
#include<iterator>
#include<cstdlib>
namespace String{

    template<typename type, typename Traits, typename Alloc>
    class Basic_string{
        private:
            Alloc _alloc_;
            //Traits _traits_;//这个成员需要吗 我们只需要函数
            size_type _String_length;
            pointer _True_value;

            enum {initial_capacity = 15 / sizeof(type)};

            union{
                type initial_buf[static_cast<int>(initial_capacity)];
                size_type alloc_capacity;
            };

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

        pointer _Return_local_pointer() const noexcept{
            return initial_buf;
        }

        Alloc& _Return_alloc() noexcept{
            return _alloc_;
        }

        bool _Data_is_local() const noexcept{
            return _Return_pointer() == _Return_local_pointer();
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
                traits::assign(ptr, n, ch)
        }


        public:
/*------------------------------------------------*/
        //Following is a constructor part.
            Basic_string() :
            _True_value(_Return_local_pointer()), _alloc_(Alloc())
            {_S_SetUp_length(0);}

            //from Nth to the N+pos th
            Basic_string(const Basic_string& _str, size_type pos, size_type n):
            _True_value(_Return_local_pointer()){
                size_type len = _str.length();
                size_type _end = pos + n;
                if(_end > len) _end = len;
                _S_construct(_str._Return_pointer() + pos,
                             _str._Return_pointer() + _end); 
            }

            Basic_string(const Basic_string& _str, size_type pos, size_type n
            const Alloc& _all_) :_True_value(_Return_local_pointer()), _alloc_(_all_){
                size_type len = _str.length();
                size_type _end = pos + n;
                if(_end > len) _end = len;
                _S_construct(_str._Return_pointer() + pos,
                             _str._Return_pointer() + _end); 
            }

            //from the Nth to the end.
            Basic_string(const Basic_string& _strm, size_type n, const Alloc& _all = Alloc()) : 
                _True_value(_Return_local_pointer()),_alloc_(Alloc(_all)){
                    size_type _start_ = n;
                    size_type len = _strm.length();
                    if(n > len)  _start_ = len;
                    _S_construct(_strm._Return_pointer() + _start_,
                                 _strm._Return_pointer() + len);
                }

            explicit Basic_string(Alloc&& _a) noexcept :
                _True_value(_Return_local_pointer()), _alloc_(std::move(_a)){
                    _S_SetUp_length(0);
                }
            
            explicit Basic_string(const Alloc& _a) noexcept : 
                _True_value(_Return_local_pointer()), _alloc_(_a){
                    _S_SetUp_length(0);
                }

            //copy construct function.
            //TODO 写的很好 值得学习
            Basic_string(Basic_string&& str): 
            _True_value(_Return_local_pointer()), 
            _alloc_(std::move(str._Return_alloc())) noexcept{
                if(str._Data_is_local()){
                    this->S_copy_(initial_buf, str._Return_local_pointer(), str.length());
                }else{
                    _S_SetUp_date(str._Return_pointer());
                    _S_SetUp_capacity(str.capacity());
                }
            }

            Basic_string(const Basic_string& str) :
                _True_value(_Return_local_pointer()), 
                _alloc_(Alloc()) {
                _S_construct(str._Return_pointer(), str._Return_pointer() + str.length());
            }

            //: @a str must have at least n characters.
            Basic_string(const type* str, size_type n,
                Alloc& _all_ = Alloc()) :
                _True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(str, str + n);
                }

            Basic_string(const type* str, Alloc& _all_ = Alloc())
                : _True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(str, str + strlen(str));
            }

            Basic_string(size_type n, type ch, Alloc& _all_ = Alloc())
                :_True_value(_Return_local_pointer()), _alloc_(_all_){
                    _S_construct(n, ch);
            }
            
            Basic_string(std::initializer_list<char> list_,
            Alloc& _all_ = Alloc()) : 
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
                return _Return_pointer()[pos];
            }

            reference 
            operator[](size_type pos){
                if(pos > this->size())
                    throw std::out_of_range("'String[] 144行' out of range.");
                return _Return_pointer()[pos];
            }

/**
 *  @return Read-only (const) reference to the character.
 */
            const_reference
            at(size_type n) const{
                if(pos > this->size())
                    throw std::out_of_range("'String[] 158行' out of range.");
                return _Return_pointer()[pos];
            }

/**
 *  @return Read/write reference to the character.
 */
            reference
            at(size_type n){
                if(pos > this->size())
                    throw std::out_of_range("'String[] 158行' out of range.");
                return _Return_pointer()[pos];
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