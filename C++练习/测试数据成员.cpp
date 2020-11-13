#include <bits/stdc++.h>
using namespace std;

typedef int length;

class point3D{
/*         private:
        typedef float length;
        length _val; */
    public:
        // 参数的列表的说明不遵寻名称查找法则，这里直接匹配到了global变量，后面出现了冲突
        void mumble(length val){_val = val;};
        length mumble(){return _val;};
            private:
        typedef float length;   // 所以一般把声明放在类的开头比较好
        length _val;
};

int main(){
    point3D po;
    po.mumble(5);
    cout << po.mumble() << endl;
}