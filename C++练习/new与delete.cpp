#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<algorithm>
#include<fstream>
#include<assert.h>
using namespace std;

namespace NEW{
    class people{
        public:
            void* operator new(size_t size){
                if(void* mem = malloc(size))
                return mem;
                else
                throw bad_alloc();
            }
            void operator delete(void* mem) noexcept {
                free(mem);
            }
    };
}

int main(){
    int *q = new int(5);
    delete(q);
}