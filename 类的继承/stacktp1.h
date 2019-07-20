#ifndef STACKTP1_H_
#define STACKTP1_H_

template<class Type>
class stack
{
    private:
        enum ={size = 10};
        int stacksize;
        Type *items;
        int top;
    public:
        explicit stack(int ss=size);
        stack(const stack & st);
        ~stack(delete [] items);
        bool isempty(){return top==0}
        bool isfull(){return top==stacksize}
        bool push(const Type &)
        bool pop(Type &);
        stack & operator=(const stack &);
};

template <class Type>
stack<Type>::stack(int ss) :stacksize(ss),top(0)
{
    items = new Type[stacksize];
}

template <class Type>
stack<Type>::stack(const stack & st)
{
    stacksize=st.stacksize;
    top=st.top;
    items = new Type [stacksize];
    for(int i=0;i<stacksize;i++)
        items[i]=st.items[i];
}

template <class Type>
bool stack<Type>::pop(Type &item)
{
    if(top>0)
    {
        item=items[--top];
        return true;
    }
    else
    {
        return false;
    }
}

template <class Type>
bool stack<Type>::push(const Type & item)
{
    if(top<stacksize)
    {
        item=items[top++];
        return true;
    }else
    {
        return false;
    }   
}

template <class Type>
stack<Type> & stack<Type>::operator=(const stack &st)
{
    if(this==&st)
        return *this;
    delete [] items;
    stacksize=st.stacksize;
    top=st.top;
    items=new Type [stacksize];
    for(int i=0;i<stacksize;i++)
        items[i]=st.items[i];
    return *this;
}
#endif