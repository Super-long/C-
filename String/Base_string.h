#ifndef BASE_STRING_H_
#define BASE_STRING_H_

#include<initializer_list>
#include<exception>
#include<iterator>
#include<cstring>
#include<ext/alloc_traits.h>
#include<ext/atomicity.h>
#include<ostream>
#include<istream>

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
#if __cplusplus > 201402L

        using _sv_type = string_view;

        //TODO 补充泛型继承的知识 搞清楚连接符 猜测像是&& ! 一样 还有其中的判断条件
        //TODO 很重要
        template<typename _Tp, typename _Res>
        using if_sv = enable_if_t< //if string_view
        __and_<is_convertible<const _Tp&, _sv_type>,
            __not_<is_convertible<const _Tp*, const Basic_sting*>>,
            __not_<is_convertible<const _Tp&, const type*>>
            >::value,
            _Res>;

#endif
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

        Alloc& _Return_alloc() noexcept{
            return _alloc_;
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

        static void _S_move(type* lhs, const type* rhs, size_type n){
            if(n == 1){
                traits::assign(*lhs, *rhs);
            }else{
                traits::move(lhs ,rhs, n); 
            }
        }

        //_S_replace() function in standard library is quite complicated. 
        Basic_string& _S_replace(size_type pos, size_type len1, const type* para, size_type len2);

        Basic_string& _S_replace(size_type n, const type& ch);

        Basic_string& _S_append(const type* str, size_type n);

        Basic_string& _S_append(size_type n, type ch);

        void _S_erase(size_type pos, size_type n);

        public:

        //其实写在这里比较蠢 但是不这样没办法输出啊
        bool _Data_is_local() const noexcept{
            return this->_Return_pointer() == this->_Return_local_pointer();
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

/**
 * @ The standard library approach is expanding when _str.size() > initial_capacity.
 * if old_capacity less than new_length, we can save time without expanding. But this
 * is likely to waste space.
*/
            Basic_string& 
            operator=(const Basic_string& _str){
                if(this == &str) return *this;

#if __cplusplus >= 201103L
                if(_Return_pointer() && 
                get_allocator() != _str.get_allocator()){
                    if(_str.size() < initial_capacity){
                        _S_Delete();
                        _S_SetUp_date(initial_buf);
                        _S_SetUp_length(_str.length());
                    }else if(_str.size() <= this->capacity()){
                        //we should weigh space and time. I choose time...
                        Traits::copy(_Return_pointer(),_str._Return_pointer(), _str.length());
                        _S_SetUp_length(_str.length());
                    }else{
                        const size_type len = _str.size();
                        auto alloc = _str.get_allocator();
                        auto ptr = alloc.allocate(len + 1);
                        _S_Delete();
                        _S_SetUp_date(ptr);
                        _S_SetUp_capacity(len);
                        _S_SetUp_length(len);
                    }
                }
                std::__alloc_on_copy(get_allocator(), alloc);
#endif
            return this->assign(_str);
            }

            Basic_string& 
            operator=(const type* str){
                return this->assign(str);
            }

            Basic_string&
            operator=(type ch){
                return this->assign(1, ch);
            }

#if __cplusplus >= 201103L
            Basic_string& 
            operator=(Basic_string&& _str){
                if(!_Return_pointer() 
                && get_allocator() != _str.get_allocator()){
                    //Guaranteed exception safety. ::Basic guarantee.
                    _S_Delete(); 
                    _S_SetUp_capacity(initial_capacity);
                    _S_SetUp_date(initial_buf);
                    _S_SetUp_length(0);
                }
                std::__alloc_on_move(get_allocator(), _str.get_allocator());

                if(!_str._Data_is_local()){
                    _S_SetUp_date(_str._Return_pointer());
                    _S_SetUp_length(_str.size());
                    _S_SetUp_capacity(_str.capacity());
                    //Guaranteed destructor safety.
                    _str._S_SetUp_date(_str.initial_buf);
                }else{
                    this->assign(_str);
                }
                return *this;
            }

        ~Basic_string(){
            _S_Delete();
        }
#endif

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

            //TODO
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

    Basic_string& append(const Basic_string& str){
        if(str._Data_is_local())
        return _S_append(str._Return_local_pointer(), str.length());
        return _S_append(str._Return_pointer(), str.length());
    }

    Basic_string& append(const Basic_string& str, size_type pos, size_type n){
        if(str._Data_is_local())
        return _S_append(str._Return_local_pointer() + pos, n);
        return _S_append(str._Return_pointer() + pos, n);
    }

    Basic_string& append(const type* para){
        if(!para) throw std::invalid_argument("'String append': parameter is nullptr.");
        return _S_append(para, strlen(para));   
    }

    Basic_string& append(const type* para, size_type n){
        if(!para) throw std::invalid_argument("'String append': parameter is nullptr.");
        return _S_append(para, n);  
    }

    Basic_string& append(size_type n, type ch){
        return _S_append(n, ch);
    }

    Basic_string& append(const type& ch){
        return _S_append(1, ch);
    }

#if __cplusplus >= 201103L
    /*Basic_string& append(initializer_list<type> list){

    }*/
#endif

    template<typename Inerator_ >
    Basic_string& 
    append(const Inerator_& lhs, const Inerator_& rhs){
        //TODO 有点难 放一放  
        //basic_string.h 1299行
    } 
    
    void push_back(const type& ch){
        const size_type len = length();
        if(len + 1 > capacity()){
            _S_expansion(len, static_cast<size_type>(0), nullptr, static_cast<size_type>(1));
            if(!_Data_is_local())
                traits::assign(_Return_pointer()[len], ch);
            else
                traits::assign(_Return_local_pointer()[len], ch); 
        }else{
            this->append(ch);
        }
        _S_SetUp_length(len + 1);
    }
    
    /**
     * brief @ set value to contents of another string.
    */
   Basic_string& assign(Basic_string& str){
       this->_S_assign(str);
       return *this;
   }

#if __cplusplus >= 201103L

    Basic_string& assign(Basic_string&& str) noexcept{
        return *this = std::move(str);
    }

#endif 
    
    //I didn't do boundary check. Because I'm so lazy.
    Basic_string& assign(const Basic_string& str, size_type pos, size_type n){
        if(str._Data_is_local())
            return this->_S_replace(length(), pos, str._Return_local_pointer(), n);
        return this->_S_replace(length(), pos, str._Return_pointer(), n);
    }

    Basic_string& assign(const type* str, size_type n){
        return this->_S_replace(length(), 0, str, n);
    }

    Basic_string& assign(const type* str){
        return this->_S_replace(length(), 0, str, strlen(str));
    }

    Basic_string& assign(size_type n, const type& ch){
        return this->_S_replace(n, ch);
    }

    //TODO 和append一样 对于列表初始化和string_view都没有实现.
    //resize 也没写
    //insert erase replace 涉及到迭代器 现在还没办法写 
    //迭代器板块还没写


#if __cplusplus >= 201103L

    void pop_back() noexcept{
        if(empty()) return;
        _S_erase(length() - 1, 1);
    }

#endif 

    void Swap(Basic_string& str) noexcept;

    Basic_string& 
    operator+=(const Basic_string& str){
        return this->append(str);
    }

    Basic_string& 
    operator+=(type* str){
        return this->append(str);
    }

    Basic_string& 
    operator+=(type ch){
        return this->append(ch);
    }

/*------------------------------------------------*/
    //Following is a String operations

    int compare(const Basic_string& str) const{
        const size_type len_a = this->size();
        const size_type len_b = str.size();

        if(len_a < len_b) return -1;
        else if(len_a > len_b) return 1;

        return traits::compare(_Return_pointer(), str._Return_pointer(), len_a);
    }

    int compare(const type* str) const{
        const size_type len_a = strlen(str);
        const size_type len_b = str.size();

        if(len_a < len_b) return -1;
        else if(len_a > len_b) return 1;

        return traits::compare(_Return_pointer(), str, len_a);        
    }

    const type* 
    c_str(){
        if(_Data_is_local())
            return _Return_local_pointer();
        else 
            return _Return_pointer();
    }

    Alloc
    get_allocator() const noexcept{
        return _Return_alloc();
    }

    const type* 
    data() const noexcept{
        if(_Data_is_local())
            return _Return_local_pointer();
        else 
            return _Return_pointer();
    }

#if __cplusplus > 201402L

    /**
     * @ Using pointer modify string was allowed in C++14.  
     */
    type*
    data() noexcept{
        if(_Data_is_local())
            return _Return_local_pointer();
        else 
            return _Return_pointer();    
    }

#endif

    /**
     * @ Copy substring into c string.
     * @ If pos > this->size() std::out_of_range
     * @ c string will copy the value.
    */
    size_type 
    copy(type* s, size_type len, size_type pos = 0) const;

    size_type
    find(const type* str, size_type pos, size_type n) const noexcept;

    size_type
    find(const Basic_string& str, size_type pos, size_type n) const noexcept{
        return find(str._Return_pointer(), pos, n);
    }

    size_type 
    find(type ch, size_type pos = 0) const noexcept;

/**
 * @ Supported find position of a string_view 
*/
#if __cplusplus > 201402L

    template<typename _Tp>
      if_sv<_Tp, size_type>
      find(const _Tp& Tp, size_type pos = 0) const noexcept{
          _sv_type sv = Tp; //隐式类型转换
          return this->find(sv.data(), pos, sv.length());
      }

#endif

    size_type 
    _rfind(type ch, size_type pos = 0) const noexcept;

    size_type 
    _rfind(const type* str, size_type pos, size_type n) const noexcept;

    size_type
    rfind(const type* str, size_type pos = npos)
    const{
        return _rfind(str, pos, strlen(str));
    }

    size_type
    rfind(const type* str, size_type pos, size_type n)
    const{
        return _rfind(str, pos, n);
    }

    size_type
    rfind(const Basic_string& str, size_type pos = npos)
    const noexcept{
        return _rfind(str._Return_pointer(), pos, strlen(str._Return_pointer()));
    }

    size_type
    rfind(type ch, size_type pos = npos)
    const noexcept{
        return _rfind(ch, pos);
    }

    size_type
    find_first_of(const type* str, size_type pos, size_type n)
    const noexcept;

    size_type
    find_first_of(type ch, size_type pos = 0){
        return this->find(ch, pos);
    }

    size_type
    find_first_of(const Basic_string& str, size_type pos = 0)
    const noexcept{
        return find_first_of(str._Return_pointer(), pos, str.size());
    }

    size_type
    find_first_of(const type* str, size_type pos = 0)
    const noexcept{
        return find_first_of(str, pos, strlen(str));
    }

    size_type
    find_last_of(const type* str, size_type pos, size_type n)
    const noexcept;

    size_type
    find_last_of(type ch, size_type pos = 0){
        return this->rfind(ch, pos);
    }

    size_type
    find_last_of(const Basic_string& str, size_type pos = 0)
    const noexcept{
        return find_last_of(str._Return_pointer(), pos, str.size());
    }

    size_type
    find_last_of(const type* str, size_type pos = 0)
    const noexcept{
        return find_last_of(str, pos, strlen(str));
    }

    size_type
    find_first_not_of(const type* str, size_type pos, size_type n)
    const noexcept;

    size_type
    find_first_not_of(type ch, size_type pos)
    const noexcept; 
    

    size_type
    find_first_not_of(type ch, size_type pos = 0){
        return this->find_first_not_of(ch, pos);
    }

    size_type
    find_first_not_of(const Basic_string& str, size_type pos = 0)
    const noexcept{
        return find_first_not_of(str._Return_pointer(), pos, str.size());
    }

    size_type
    find_first_not_of(const type* str, size_type pos = 0)
    const noexcept{
        return find_first_not_of(str, pos, strlen(str));
    }

    size_type
    find_last_not_of(const type* str, size_type pos, size_type n)
    const noexcept;
    
    size_type
    find_last_not_of(type ch, size_type pos = 0)
    const noexcept;

    size_type
    find_last_not_of(const Basic_string& str, size_type pos = 0)
    const noexcept{
        return find_last_not_of(str._Return_pointer(), pos, str.size());
    }

    size_type
    find_last_not_of(const type* str, size_type pos = 0)
    const noexcept{
        return find_last_not_of(str, pos, strlen(str));
    }

    Basic_string 
    substr(size_type pos = 0, size_type n = npos) const{
        if(pos > this->size()) pos = this->size();
        return Basic_string(*this, pos, n);
    }
};
/*------------------------------------------------*/
    //Following is a Non-member function overloads

/**
 * @ In standard library, Following function only has a part of
 * have noexcept. But in my library, all the function has this qualifer,
 * because in my library, if parameter out of boundary, I will set it
 * as the default parameter, but std will throw out_of_range.
 * 
 * @ Following is so boring. 
 */

    template<typename type, typename Traits, typename Alloc>
      Basic_string<type, Traits, Alloc> //RVO
      operator+(const Basic_string<type, Traits, Alloc>& lhs,
                const Basic_string<type, Traits, Alloc>& rhs){
                    Basic_string<type, Traits, Alloc> tool(lhs);
                    tool.append(rhs);
                    return tool;
                }

    template<typename type, typename Traits, typename Alloc>
      Basic_string<type, Traits, Alloc>
      operator+(const Basic_string<type, Traits, Alloc>& lhs,
                const type& rhs){
                    Basic_string<type, Traits, Alloc> tool(lhs);
                    tool.append(rhs);
                    return tool;
                }

    template<typename type, typename Traits, typename Alloc>
      Basic_string<type, Traits, Alloc>
      operator+(const type& lhs,
                const Basic_string<type, Traits, Alloc>& rhs){
                    Basic_string<type, Traits, Alloc> tool(rhs);
                    tool.append(lhs);
                    return tool;
                }

    template<typename type, typename Traits, typename Alloc>
      Basic_string<type, Traits, Alloc>
      operator+(const Basic_string<type, Traits, Alloc>& lhs,
                const type* rhs){
                    Basic_string<type, Traits, Alloc> tool(lhs);
                    tool.append(rhs);
                    return tool;
                }

    template<typename type, typename Traits, typename Alloc>
      Basic_string<type, Traits, Alloc>
      operator+(const type* lhs,
                const Basic_string<type, Traits, Alloc>& rhs){
                    Basic_string<type, Traits, Alloc> tool(lhs);
                    tool.append(rhs);
                    return tool;
                }

    template<typename type, typename Traits, typename Alloc>
    inline std::ostream& 
    operator<<(std::ostream& os, 
            const Basic_string<type, Traits, Alloc>& para){
                if(para._Data_is_local()){
                    os << para._Return_local_pointer();
                }else {
                    os << para._Return_pointer();
                }
                return os;
            }

    //这个现在没办法写 basic_istream<_CharT, _Traits>没办法直接创建 导致没办法从流中获取数据 
    template<typename type, typename Traits, typename Alloc>
    inline std::istream& 
    operator>>(std::istream& is, 
            const Basic_string<type, Traits, Alloc>& para){
                
                if(is.good()){
                    
                }else{
                    para = Basic_string<type, Traits, Alloc>();
                }
                return is;
            } 

    //getline也没办法写

    template<typename type, typename Traits, typename Alloc>
    void swap(Basic_string<type, Traits, Alloc>& lhs,
            Basic_string<type, Traits, Alloc>& rhs) noexcept{
                lhs.Swap(rhs);
            }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator==(const Basic_string<type, Traits, Alloc>& lhs,
            const Basic_string<type, Traits, Alloc>& rhs) noexcept{
                if(lhs.compare(rhs) == 0) return true;
                return false;
            }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator==(const Basic_string<type, Traits, Alloc>& lhs,
      type* rhs)noexcept{
            if(lhs.compare(rhs) == 0) return true;
            return false;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator==(type* lhs,
      const Basic_string<type, Traits, Alloc>& rhs)noexcept{
          if(rhs.compare(lhs)) return true;
          return false;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator!=(const Basic_string<type, Traits, Alloc>& lhs,
            const Basic_string<type, Traits, Alloc>& rhs)noexcept{
                return !(lhs == rhs);
            }
    
    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator!=(const Basic_string<type, Traits, Alloc>& lhs,
      type* rhs)noexcept{
            return !(lhs == rhs);
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator!=(type* lhs,
      const Basic_string<type, Traits, Alloc>& rhs)noexcept{
            return !(lhs == rhs);
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator<(const Basic_string<type, Traits, Alloc>& lhs,
            const Basic_string<type, Traits, Alloc>& rhs)noexcept{
                return lhs.compare(rhs) < 0;
            }
    
    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator<(const Basic_string<type, Traits, Alloc>& lhs,
      type* rhs)noexcept{
            return lhs.compare(rhs) < 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator<(type* lhs,
      const Basic_string<type, Traits, Alloc>& rhs)noexcept{
            return rhs.compare(lhs) >= 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator<=(const Basic_string<type, Traits, Alloc>& lhs,
            const Basic_string<type, Traits, Alloc>& rhs) noexcept{
                return lhs.compare(rhs) <= 0;
            }
    
    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator<=(const Basic_string<type, Traits, Alloc>& lhs,
      type* rhs)noexcept{
            return lhs.compare(rhs) <= 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator<=(type* lhs,
      const Basic_string<type, Traits, Alloc>& rhs)noexcept{
            return rhs.compare(lhs) > 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator>(const Basic_string<type, Traits, Alloc>& lhs,
            const Basic_string<type, Traits, Alloc>& rhs)noexcept{
                return lhs.compare(rhs) > 0;
            }
    
    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator>(const Basic_string<type, Traits, Alloc>& lhs,
      type* rhs)noexcept{
            return lhs.compare(rhs) > 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator>(type* lhs,
      const Basic_string<type, Traits, Alloc>& rhs)noexcept{
            return rhs.compare(lhs) <= 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator>=(const Basic_string<type, Traits, Alloc>& lhs,
            const Basic_string<type, Traits, Alloc>& rhs) noexcept{
                return lhs.compare(rhs) >= 0;
            }
    
    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator>=(const Basic_string<type, Traits, Alloc>& lhs,
      type* rhs)noexcept{
            return lhs.compare(rhs) >= 0;
      }

    template<typename type, typename Traits, typename Alloc>
      inline bool 
      operator>=(type* lhs,
      const Basic_string<type, Traits, Alloc>& rhs)noexcept{
            return rhs.compare(lhs) < 0;
      }

}

#endif