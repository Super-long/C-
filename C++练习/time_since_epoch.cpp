#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

// 是毫秒
std::uint64_t get_mill_time_stamp() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    //auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    return tp.time_since_epoch().count();
}


int main(){
    cout << get_mill_time_stamp() << endl;
    sleep(1);
    cout << get_mill_time_stamp() << endl;
    return 0;
}