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
        if(len < 0) return len;

        if(pos + len > this->size())
            len = (this->size() - pos);

        if(len > 0){
            if(_Data_is_local())
                S_copy_(s, _Return_local_pointer() + pos, len);
            else 
                S_copy_(s, _Return_pointer() + pos, len);
        }
        return len;
      }

    //TODO: The third parameter is not processed.
    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find(const type* str, size_type pos, size_type n) const noexcept{
        size_type len = strlen(str);
        if(n == 0)
            return pos > len ? npos : pos;
        if(n > len) 
            return npos;

        const type* const _data = _Return_pointer();
        const type* first = str + pos;

        const type* Temp = strstr(_data, first);
        return static_cast<size_type>(std::distance(_data, Temp));
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find(type ch, size_type pos) const noexcept{
          size_type ret = npos;
          const size_type __size = this->size();
          
          if(pos < __size){
              const type* _data = _Return_pointer();
              const size_type n = __size - pos;
              const type* end_ = Traits::find(_Return_pointer() + pos, n, ch);
              if(end_) 
                ret = static_cast<size_type>(std::distance(_data, end_));
          }
          return ret;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
       _rfind(const type* str, size_type pos, size_type n)
        const noexcept{
            const size_type length = this->size();
            pos = std::min(length - n, pos);
            if(n <= length){
                const type* _data = _Return_pointer();
                do{
                    if(Traits::compare(_data + pos, str, n) == 0)
                    return pos - 1;
                }while(pos-- > 0);
            }
            return npos;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      _rfind(type ch, size_type pos)
      const noexcept{
          size_type length = this->length();
          if(length){
              if(length > pos)
                length = pos;
                for(; length-- > 0; ){
                    if(_Return_pointer()[length] == ch)
                        return length;
                }
          }
          return npos;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find_first_of(const type* str, size_type pos, size_type n)
      const noexcept{
            for(; n && pos < this->size(); ++pos){
                const type* ptr = Traits::find(str, n, _Return_pointer()[pos]);
                if(ptr) return pos; 
          }
          return npos;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find_last_of(const type* str, size_type pos, size_type n)
      const noexcept{
          size_type Temp = strlen(str);
          if(n > Temp) n = Temp;

          size_type len = this->size();
          if(len && n){
              if(len > pos){
                  len = pos;
              }
              for(;len > 0; --len){
                  if(Traits::find(str, n, _Return_pointer()[len])) 
                    return len;
              }
          }
          return npos;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find_first_not_of(const type* str, size_type pos, size_type n)
      const noexcept{
          size_type len = strlen(str);
          if(n < 0 || n > len) n = len;
          if(pos < 0 || pos > this->size()) pos = 0;

          for(; pos < this->size(); ++pos)
            if(!Traits::find(str, n, _Return_pointer()[pos]))
              return pos;
        return npos;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find_first_not_of(type ch, size_type pos)
      const noexcept{
          if(pos < 0 || pos > this->size()) pos = 0;

          for(; pos < this->size(); ++pos)
            if(!Traits::eq(_Return_pointer()[pos], ch))
              return pos;
        return npos;     
      }


    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find_last_not_of(const type* str, size_type pos, size_type n)
      const noexcept{
          size_type len = strlen(str);
          if(n < 0 || n > len) n = len;
          if(pos < 0 || pos > this->size()) pos = this->size() - 1;

          for(; pos > 0; --pos)
            if(!Traits::find(str, n, _Return_pointer()[pos]))
              return pos;
        return npos;
      }

    template<typename type, typename Traits, typename Alloc>
      typename Basic_string<type, Traits, Alloc>::size_type
      Basic_string<type, Traits, Alloc>::
      find_last_not_of(type ch, size_type pos)
      const noexcept{
          if(pos == npos || pos > this->size()) pos = this->size() - 1;
        
          if(pos > 0)
          for(; pos >= 0; --pos)
            if(!Traits::eq(_Return_pointer()[pos], ch))
              return pos;
        return npos;     
      }

}

/**
 * @在其中得到的收获
 * 1.仔细思考 为自己在写的东西提供一套泛型的接口 可以避免大量无意义的工作
 * 2.擅于使用库
 * 3.string的find族方法效率低下 大于N 不建议使用
*/