#include <bits/stdc++.h>
using namespace std;

class point{
    public:
        point(){
            x = 1;
            y = 2;
            z = 3;
        }
        point(const point& po){
            x = po.x;
            y = po.y;
            z = po.z;
            //memcpy(this, &po, sizeof(point));
        }
    private:
        int x;
        int y;
        int z;
};

int main(){
    point po;
    cout << sizeof(point) << endl;
    auto start = std::chrono::high_resolution_clock::now(); 

    for (size_t i = 0; i < 10000000; i++)
    {
        point temp = po;
    }
    

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::ratio<1,1000>> time_span 
    = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1,1000>>>(end - start);

    std::cout << time_span.count() << std::endl;
}