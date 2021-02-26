#include <iostream>
#include <format>
 
int main() {
    std::cout << std::format("Hello {}!\n", "world");
    std::cout << std::format("{} {}!\n", "Hello", "world", "something");
    std::cout << std::format("The answer is {}.", 42);
}