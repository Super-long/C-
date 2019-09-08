#include<cstring>
#include<cstdio>
#include<cstdarg>
#include<iostream>
#include<vector>
using namespace std;

typedef enum{
    CHAR_TYPE = 1,
    INT_TYPE,
    LONG_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    STR_TYPE,
    VECTOR_TYPE,
}E_VAR_TYPE;

//可以使得实现传入想一个函数传入无限个不同的参数且可以正确的解析
void parse_argtype(int num, ...){
    va_list pargs;
    va_start(pargs,num);
    for(int i=0;i<num;++i){
        E_VAR_TYPE eArgType = E_VAR_TYPE(va_arg(pargs,int));
        //int不能转换为枚举变量　进行显式强制类型转换
        switch (eArgType)
        {
            case INT_TYPE:
                printf("The no.%d argument is %d\n",i,va_arg(pargs,int));
                break;
            case STR_TYPE:
                printf("The no.%d argument is %s\n",i,va_arg(pargs,char*));
                break;
            case VECTOR_TYPE: //好像指定类型有点麻烦　可以在加再加一个标记位　来指示容器的实例化
                {
                    printf("The no.%d argument\n",i);
                    vector<int>vec = std::move(va_arg(pargs,vector<int>));
                    for(auto x : vec) cout << x << endl;
                }
                break;
            default:
                break;
        }
    }
}

void IntegerVarArgFunc(int i, ...){
    va_list pArgs;//定义指针
    va_start(pArgs, i);//初始化指针　使其指向第一个可变参数
    int j = va_arg(pArgs, int);//返回当前的参数值　并使其指向列表的笑一个实参　第二个参数是要返回的类型
    va_end(pArgs); //参数设置为无效　结束实参的获取
    printf("i=%d, j=%d\n", i, j);
}

void tmpa(int i, ...){ //可通过一个参数来标记大小　
    va_list pargs;
    va_start(pargs,i);
    int arga = 0;
    for(int argb = 1;argb<=i;++argb){
        //auto arga = va_arg(pargs,auto);
        arga = va_arg(pargs,int);
        printf("%d  %d\n",argb,arga);
    }
    va_end(pargs);
}

//绝大多数情况下可以用C++中的多态来完美替代　
//因为可变参数函数在类型安全上并不出色　
//不利于排错　不利于写出高质量代码　而且使用不确定参数且类型不确定的时候较少

int main(){
    //IntegerVarArgFunc(1);
    //tmpa(3,1,2,3); 
    vector<int>vec = {1,2,3};
    parse_argtype(3,INT_TYPE,5,STR_TYPE,"hello world!",VECTOR_TYPE,vec);
    return 0;
}