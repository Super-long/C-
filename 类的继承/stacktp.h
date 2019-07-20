#ifndef STACKTP_H_
#define STACKTP_H_
//要加一个空行
template <class Type>
class stack
{
    private:
        enum {MAX=10};
        Type items[MAX];
        int top;
    public:
        stack();
        bool isempty();
        bool isfull();
        bool push(const Type & item);
        bool pop(Type & item);
};

template<class Type>
stack<Type>::stack()
{
    top=0;
}

template<class Type>
bool stack<Type>::isempty()
{
    return top==0;
}

template<class Type>
bool stack<Type>::isfull()
{
    return top==MAX;
}

template<class Type>
bool stack<Type>::push(const Type & item)
{
    if(top<MAX)
    {
        items[top++]=item;
        return true;
    }else
    {
        return false;
    }
}

template <class Type>
bool stack<Type>::pop(Type & item)
{
    if(top>0)
    {
        item=items[--top];
        return true;
    }else
    {
        return false;
    }
}
#endif