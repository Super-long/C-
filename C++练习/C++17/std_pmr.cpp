#include <iostream>
//#include "/usr/include/c++/7/experimental/memory_resource"
#include <memory_resource>
#include <vector>

int main() {
    char buffer[64] = {};
    std::fill_n(std::begin(buffer), std::size(buffer)-1, '_');
    std::cout << buffer << '\n';

    std::pmr::monotonic_buffer_resource pool{
        std::data(buffer), std::size(buffer)
    };

    std::pmr::vector<char> vec{&pool};    
    for (char ch='a'; ch <= 'z'; ++ch)
        vec.push_back(ch);

    std::cout << buffer << '\n';
}