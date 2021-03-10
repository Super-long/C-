#include<stdio.h>
#include <iostream>  
using namespace std;
struct sol {
    int a;
    int b;
};

int main()  
{  
   struct sol x = {1024, 1025};  
   int y = 2;  
   struct sol &b = x;  
   int d = 10;
   printf("&x=%x,&y=%x,&b=%x,b=%x  %x, d=%x\n",&x,&y,&y-1,*(&y-1),*(&y-2), &d);  
   return 0;
}