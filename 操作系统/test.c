#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>//动态链接库

//这段代码的好处是不用关服务器也可以修改函数内容　
//构建高性能web服务器
//gcc -rdynamic -o prog2r test.c -ldl
int main()
{
    void *handle;
    void (*foo)(int *);
    char *error;
    //void foo(int *);
    int x=2;
    while(1)
    {
        handle=dlopen("./test_dy.so",RTLD_LAZY);
        if(!handle)
        {
            fprintf(stderr,"%s\n",dlerror());
            exit(1);
        }
        foo=dlsym(handle,"foo");

        foo(&x);
        getchar();
        dlclose(handle);
    }
    return 0;
}