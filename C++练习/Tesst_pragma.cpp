#include<iostream>
#include<string>

//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wmissing-noreturn"
//#pragma once 保证头文件只编译一次 比起条件编译效率更高 但有些编译器不支持 
int n;
std::string T(){
    if(n>5){
        std::cout << "hello world\n";
        return std::string();//应该和C++的对象模型有关 知识太过浅显
    }
}

int main(){
    std::cin >> n;
    T();
}
//#pragma clang diagnostic pop