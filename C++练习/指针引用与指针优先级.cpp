#include <bits/stdc++.h>
using namespace std;

class SourceFile
{
public:
template<int N>
SourceFile(const char (&arr)[N])
    : data_(arr),
    size_(N-1)
{
    cout << "one\n";
    const char* slash = strrchr(data_, '/'); // builtin function
    if (slash)
    {
    data_ = slash + 1;
    size_ -= static_cast<int>(data_ - arr);
    }
}

explicit SourceFile(const char* filename)
    : data_(filename)
{
    cout << "two\n";
    const char* slash = strrchr(filename, '/');
    if (slash)
    {
    data_ = slash + 1;
    }
    size_ = static_cast<int>(strlen(data_));
}

const char* data_;
int size_;
};

int main(){
    char fille[64] = {0};
    auto x = SourceFile(fille);
    auto y = SourceFile(__FILE__);
    getchar();
    return 0;
}