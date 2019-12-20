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
            size_type len = str.length();
            size_type My_capacity = capacity();

            if(My_capacity < len){
                pointer ptr_ = _S_create(len, My_capacity);
                _S_Delete();
                _S_SetUp_date(ptr_);
                _S_SetUp_capacity(len); 
            }

            if(len) 
                if(!str._Data_is_local())
                    this->S_copy_(_Return_pointer(),str._Return_pointer(),len);
                else 
                    this->S_copy_(_Return_pointer(),str._Return_local_pointer(),len);

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
        _new_[n] = '\0';
    }

    //Following function is inefficient in the standard library.
    template<typename type, typename Traits, typename Alloc>
    void Basic_string<type, Traits, Alloc>::
    _S_expansion(size_type pos, size_type len1, const type* para, size_type len2){
        size_type new_capacity = this->length() + len2 - len1;
        pointer ptr = _S_create(new_capacity, this->capacity());
        
        if(pos)
            S_copy_(ptr, _Return_pointer(), pos);//using in construct.
        if(para && len2)
            S_copy_(ptr + pos, para, len2); //using in append.
        
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

    template<typename type, typename Traits, typename Alloc>
    Basic_string<type, Traits, Alloc>&
    Basic_string<type, Traits, Alloc>::
    _S_append(const type* str, size_type n){
        const size_type len = n + this->length();

        if(len <= this->capacity()){
            if(n)
                if(_Data_is_local())
                    this->S_copy_(_Return_local_pointer() + length(),
                                   str, n);
                else
                    this->S_copy_(_Return_pointer() + length(),
                                   str, n);
        }else{
            this->_S_expansion(length(), static_cast<size_type>(0), str, n);
        }
        _S_SetUp_length(len);
        return *this;
    }

    template<typename type, typename Traits, typename Alloc>
    Basic_string<type, Traits, Alloc>&
    Basic_string<type, Traits, Alloc>::
    _S_append(size_type n, type ch){
        size_type len = length() + n;

        if(n){
            if(len > capacity()){
                _S_expansion(length(), 0, nullptr, n);
                traits::assign(_Return_pointer() + length(), n, ch);
            }else{
                if(_Data_is_local())
                    traits::assign(_Return_local_pointer() + length(), n, ch);
                else 
                    traits::assign(_Return_pointer() + length(), n, ch);
            }
        }
        if(_Data_is_local()){
            _Return_local_pointer()[len] = '\0';
        }else{
            _Return_pointer()[len] = '\0';
        }
        _S_SetUp_length(len);
        return *this;
    }

    //TODO: The function is incomplete.
    template<typename type, typename Traits, typename Alloc>
    Basic_string<type, Traits, Alloc>&
    Basic_string<type, Traits, Alloc>::
    _S_replace(size_type pos, size_type len1, const type* para, size_type len2){
        size_type new_length = len2 - len1;
        size_type old_capacity = capacity();

        if(new_length <= old_capacity){
            if(_Data_is_local()){
                this->S_copy_(_Return_local_pointer(), para + len1, len2 - len1);
                _S_Delete();
            }
            else 
                this->S_copy_(_Return_pointer(), para + len1, len2 - len1);
                //capacity is changeless.
                //But in standard library, if the length is reduced, the capacity will reduced.  
                //Why I don't perfect this function, Because I'm so lazy.
        }else{
            _S_expansion(pos, len1, para, len2);
            this->S_copy_(_Return_pointer(), para + len1, len2 - len1);
        }
        _S_SetUp_length(new_length);

        return *this;
    }

    template<typename type, typename Traits, typename Alloc>
    Basic_string<type, Traits, Alloc>&
    Basic_string<type, Traits, Alloc>::
    _S_replace(size_type n, const type& ch){
        size_type new_length = n ;
        size_type old_length = length();
        if(new_length > capacity()){
            _S_expansion(length(),0 ,0 ,n);
            if(_Data_is_local())
                traits::assign(_Return_local_pointer(), n, ch);
            else 
                traits::assign(_Return_pointer(), n, ch);            
        }else{
            if(_Data_is_local())
                traits::assign(_Return_local_pointer(), n, ch);
            else 
                traits::assign(_Return_pointer(), n, ch);
        }
        _S_SetUp_length(new_length);

        return *this;
    }


    template<typename type, typename Traits, typename Alloc>
    void 
    Basic_string<type, Traits, Alloc>::
    _S_erase(size_type pos, size_type n){
        const size_type len = length() - pos - n;
        pointer ptr_l = _Return_local_pointer();
        pointer ptr_nl = _Return_pointer();
        if(len && n){
            if(_Data_is_local())
                _S_move(ptr_l + pos, ptr_l + pos + n, len);
            else
                _S_move(ptr_nl + pos, ptr_nl + pos + n, len);
        }
        _S_SetUp_length(pos);
        if(_Data_is_local()){
            _Return_local_pointer()[pos] = static_cast<type>(0);
        }else{
            _Return_pointer()[pos] = static_cast<type>(0);
        }
    }

    template<typename type, typename Traits, typename Alloc>
    void 
    Basic_string<type, Traits, Alloc>::
    Swap(Basic_string& str) noexcept {
        if(this == &str) return;

        Alloc_Traits::_S_on_swap(_Return_alloc(), str._Return_alloc());
        size_type len = length() + 1;
        _S_SetUp_length(str.length());
        str._S_SetUp_length(len - 1);

        bool lhs_local = _Data_is_local();
        bool rhs_local = str._Data_is_local();

        if(!(lhs_local && rhs_local)){
            size_type capa = capacity();
            _S_SetUp_capacity(str.capacity());
            str._S_SetUp_capacity(capa);
        }

        //Following is swap to pointer.
        if(lhs_local && rhs_local){
            type Temp_Data[initial_capacity];
            Traits::copy(Temp_Data, initial_buf, len);
            Traits::copy(initial_buf, str.initial_buf, str.length());
            Traits::copy(str.initial_buf, Temp_Data, len);
        
        }else if(!lhs_local && !rhs_local){
            pointer Temp = _True_value;
            _True_value = str._True_value;
            str._True_value = Temp;

        }else{
            type Temp_Data[initial_capacity];
            Traits::copy(Temp_Data, initial_buf, 15);
            Traits::copy(initial_buf, str.initial_buf, 15);
            Traits::copy(str.initial_buf, Temp_Data, 15);
            
            pointer Temp = _True_value;
            _True_value = str._True_value;
            str._True_value = Temp;
            
            if(lhs_local){
                _S_SetUp_date(_True_value);
                str._S_SetUp_date(str.initial_buf);
            }else{
                _S_SetUp_date(initial_buf);
                str._S_SetUp_date(str._True_value);
            }
        }
    }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      copy(type* s, size_type len, size_type pos) const{
        if(pos > this->size()){
            throw std::out_of_range("'String copy' pos is out of range.");
        }
        if(n < 0) return 0;
        pos + n <= this->size() : ? n = (this->size() - pos);

        if(n > 0){
            if(_Data_is_local())
                S_copy_(s, _Return_local_pointer(), len);
            else 
                S_copy_(s, _Return_pointer(), len);
        }
        return n;
      }

    //TODO: The third parameter is not processed.
    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find(const type* str, size_type pos, size_type n) const noexcept{
        size_type len = strlen(str);
        
        if(n == 0)
            return pos > len : npos ? pos;
        if(n >= len) 
            return npos;

        const type* const _data = _Return_pointer();
        const type* first = _data + pos;

        const type* Temp = strstr(_data, first);
        return static_cast<size_type>(std::distance(_data, Temp));
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find(type ch, size_type pos = 0) const noexcept{
          size_type ret = npos;
          const size_type __size = this->size();
          
          if(pos < __size){
              const type* _data = _Return_pointer();
              const size_type n = __size - pos;
              const type* end_ = Traits::find(data, n, ch);
              if(end_) 
                ret = static_cast<size_type>(std::distance(_data, end_));
          }
          return ret;
      }

}

/**
 * @在其中得到的收获
 * 1.仔细思考 为自己在写的东西提供一套泛型的接口 可以避免大量无意义的工作
 * 2.擅于使用库
*/