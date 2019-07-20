#include<valarray>
#include<iostream>
#include<vector>
#include<algorithm>
int main()
{
    using namespace std;
    vector<double> vec;
    double temp;
    cout << "enter number x<=0 to quit\n";
    while(cin >> temp && temp>0){
        vec.push_back(temp);
    }
    sort(vec.begin(),vec.end());
    int size=vec.size();
    valarray<double> val(size);
    for(int i=0;i<size;i++)
        val[i]=vec[i];
    valarray<double>val2(size);
    val2=sqrt(val);
    valarray<double> res(size);
    res=val+val2*2.0;
    cout.setf(ios_base::fixed);
    cout.precision(4);
    for(int i=0;i<size;i++)
    {
        cout.width(8);
        cout << val[i] << " :";
        cout.width(8);
        cout << res[i] << endl;
    }
    return 0;
}