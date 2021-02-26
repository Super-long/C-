#include <bits/stdc++.h>
using namespace std;

struct Memory {
    virtual constexpr unsigned int capacity() const = 0;
};

struct EEPROM_25LC160C : Memory {
    constexpr unsigned int capacity() const override {
        return 2048;
    }
};

int main(){
    constexpr EEPROM_25LC160C para;
    cout << para.capacity() << endl;
}