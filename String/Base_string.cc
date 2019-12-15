#include"Base_string.h"
#include<iostream>
using std::cout;
using std::endl;
//for debugging

namespace String{
    template<typename type, typename Traits, typename Alloc>
    void Basic_string<type, Traits, Alloc>::
    _S_assign(Basic_string& str){
        if(*this != str){
            const size_type len = str.length();
            const size_type My_capacity = capacity();

            if(My_capacity < len){
                pointer ptr_ = _S_create(len, My_capacity);
                _S_Delete();
                _S_SetUp_date(ptr_);
                _S_SetUp_capacity(len); 
            }

            if(len) 
                this->S_copy_(_Return_pointer(),str._Return_pointer(),len);

            this->_S_SetUp_length(len);
        }
    }


    template<typename type, typename Traits, typename Alloc>
    void Basic_string<type, Traits, Alloc>::
    S_copy_(type* _new_, const type* _old_, size_type n){
        // if(n == 1) assign faster than copy.
        if(n == 1)
            traits::assign(*_new_, *_old_);
        else 
            traits::copy(_new_, _old_, n);
    }

    template<typename type, typename Traits, typename Alloc>
    void Basic_string<type, Traits, Alloc>::
    _S_expansion(size_type pos, size_type len1, const type* para, size_type len2){
        size_type new_capacity = this->length() + len2 - len1;
        pointer ptr = _S_create(new_capacity, this->capacity());

        S_copy_(ptr, _Return_pointer(), pos);

        _S_Delete();
        _S_SetUp_date(ptr);
        _S_SetUp_capacity(new_capacity); 
    }

    template<typename type, typename Traits, typename Alloc>
    typename Basic_string<type, Traits, Alloc>::pointer
    Basic_string<type, Traits, Alloc>::
    _S_create(size_type& new_capacity, size_type old_capacity){
        if(new_capacity > this->max_size()){
            throw std::invalid_argument("'String _S_creatr' Too big capacity.");
        }
        if(new_capacity > old_capacity && new_capacity <= 2 * old_capacity){
            new_capacity = 2 * old_capacity;
        }
        if(new_capacity > this->max_size()){
            new_capacity = max_size();
        }
        return _alloc_.allocate(new_capacity + 1);
    }

    template<typename type, typename Traits, typename Alloc>
      template<typename IntIterator> void 
        Basic_string<type, Traits, Alloc>::_S_construct(IntIterator _start, IntIterator _end){
            if(_start == nullptr || _end == nullptr){
                throw std::invalid_argument("'String::construct' parameter is nullptr.");
            }
            size_type len = static_cast<size_type>(std::distance(_start, _end));
            if(len > static_cast<size_type>(initial_capacity)){
                _S_SetUp_capacity(len);
                _S_SetUp_date(_S_create(len, static_cast<size_type>(0)));
            }

            try{
                if(_Data_is_local())
                    _S_copy_of_interval(_Return_local_pointer(), _start, _end);
                else
                    _S_copy_of_interval(_Return_pointer(), _start, _end);
                _S_SetUp_capacity(len);
            }catch(...){
                _S_Delete();
                throw;
            }
            _S_SetUp_length(len);
        }

    template<typename type, typename Traits, typename Alloc>
    void Basic_string<type, Traits, Alloc>::
    _S_construct(size_type n, type para){
        size_type len = n;
        if(n > static_cast<size_type>(initial_capacity)){
            _S_SetUp_date(_S_create(len, static_cast<size_type>(0)));
            _S_SetUp_capacity(len);
        }
        if(n) _S_assign(_Return_pointer(), n, para);
        _S_SetUp_length(n);
    }

    template<typename type, typename Traits, typename Alloc>
    void Basic_string<type, Traits, Alloc>::
    reserve(size_type _ideal){
        //We can't shrink capacity.
        if(_ideal < this->length())
            _ideal = this->length();
        
        const size_type _capacity = capacity();

        if(_ideal != _capacity){
            if(_ideal > _capacity
            || _ideal > static_cast<size_type>(initial_capacity)){
                pointer ptr = _S_create(_ideal, _capacity);
                this->S_copy_(ptr, _Return_pointer(), length());
                _S_Delete();
                _S_SetUp_date(ptr);
                _S_SetUp_capacity(_ideal);
            }else if(!_Data_is_local()){
                this->S_copy_(_Return_local_pointer(), _Return_pointer(), length());
                _S_Delete();
                _S_SetUp_date(_Return_local_pointer());
            }
        }
    }

}