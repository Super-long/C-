#include<bits/stdc++.h>
using namespace std;
//自旋锁主要适用于被持有时间短，线程不希望在重新调度上花过多时间的情况
//因为其会使的CPU空转很长时间


int main(){
    std::string str = "你好";
    std::wstring Str = L"你好";

clock_t start,end;
/*     std::u32string tr = U"你好";
    std::u16string r = u"你好"; */
    //cout << str.length() << " " << Str.length() << " " <<tr.length() << " " << r.length() << endl;
    start = clock();
	setlocale(LC_ALL, "chs");
    for(int i=0;i<10000;++i){
        wcout << Str;
    }
    end = clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    cout << endtime*1000<<"ms" << endl;
    return 0;
}