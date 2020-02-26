#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
inline int gcd(int a,int b){
    int t;
    while(b){
        t=a;
        a=b;
        b=t%b;
    }
    return a;
}
bool prime_w(int a,int b){
    if(gcd(a,b) == 1)
    return true;
    else
    return false;
}
inline int mod_inverse(int a,int r){
    int b=1;
    while(((a*b)%r)!=1){
        b++;
        if(b<0){
            printf("error ,function can't find b ,and now b is negative number");
            return -1;
        }
    }
    return b;
} 
inline bool prime(int i){ 
    if(i<=1)
        return false;    
    for(int j=2;j<i;j++){
        if(i%j==0)return false;
    }
    return true;
}
void secret_key(int* p, int *q){
    int s = time(0);
    srand(s);
    do{ 
        *p = rand()%50+1;
    }while(!prime(*p));
    do{
        *q = rand()%50+1;
    }while( p==q || !prime(*q ));
}
int getRand_e(int r){
    int e = 2;
    while( e<1||e>r|| !prime_w(e,r) ){
        e++;
        if(e<0){
            printf("error ,function can't find e ,and now e is negative number");
            return -1;
        }
    }
    return e;
}
int rsa(int a,int b,int c){ 
    int aa = a,r=1;
    b=b+1;
    while(b!=1){
        r=r*aa;
        r=r%c;
        b--;
    }
    return r;
}
int getlen(char *str){
    int i=0;
    while(str[i]!='\0'){
        i++;
        if(i<0)return -1;
    }
    return i;
}
int main(int argc, char** argv) {    
    FILE *fp;
    fp = fopen("text.txt","w");
    for(int i=2;i<=65535;i++)
        if(prime(i))
            fprintf(fp,"%d ",i);
    fclose(fp);
    int p , q , N , r , e , d;
    p=0,q=0,N=0,e=0,d=0;
    secret_key(&p,&q);
    N = p*q;
    r = (p-1)*(q-1);
    e = getRand_e(r);
    d = mod_inverse(e,r);
 cout<<"N:"<<N<<'\n'<<"p:"<<p<<'\n'<<"q:"<<q<<'\n'<<"r:"<<r<<'\n'<<"e:"<<e<<'\n'<<"d:"<<d<<'\n';
    char mingwen,jiemi;
    int miwen;
    char mingwenStr[1024],jiemiStr[1024];
    int mingwenStrlen;
    int *miwenBuff;
    cout<<"\n\n输入明文：";
    fgets(mingwenStr, 1024, stdin);
    mingwenStrlen = getlen(mingwenStr);
    miwenBuff = (int*)malloc(sizeof(int)*mingwenStrlen);
    for(int i = 0;i<mingwenStrlen;i++){
        miwenBuff[i] = rsa((int)mingwenStr[i],e,N);
    }    
    for(int i = 0;i<mingwenStrlen;i++){
        jiemiStr[i] = rsa(miwenBuff[i],d,N);
    }
    jiemiStr[ mingwenStrlen ] = '\0';    
    cout<<"明文："<<mingwenStr<<'\n'<<"明文长度："<<mingwenStrlen<<'\n';    
    cout<<"密文：";
    for(int i = 0;i<mingwenStrlen;i++)
        cout<<miwenBuff[i]<<" ";
    cout<<'\n';
    cout<<"解密："<<jiemiStr<<'\n';         
    system("pause");
    return 0;
}