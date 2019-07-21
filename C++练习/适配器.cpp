/*因为迭代器返回的是一个值 而有的伪函数是两个参数 也就是在stl函数中没有办法使用这些函数
 适配器的出现就是把两个参数的伪函数变成了一个参数（就是把其中一个已知的参数变为对象的私有成员）*/
 #include<iostream>
 #include<algorithm>
 #include<vector>
 #include<iterator>
 #include<functional>
 using namespace std;
 
 void show(double i){cout << i <<" ";}
 //cout.width(6);
 const int Len=10;

 int main()
 {
     double arr1[10]={2,5,6,45,65,24,45,78,94,36};
     double arr2[10]={56,45,23,89,75,61,21,23,81};
     vector<double> vec1(arr1,arr1+Len);
     vector<double> vec2(arr2,arr2+Len);
     cout << " vec1:\n";
     for_each(vec1.begin(),vec1.end(),show);
     cout << endl;
     cout << " vec2:\n";
     for(auto pr : vec2) cout << pr << " ";
     cout << endl;
     
     vector<double> tmp(Len);  //注意申请空间
     transform(vec1.begin(),vec1.end(),vec2.begin(),tmp.begin(),plus<double>());
     //transform的两个参数类型  后面函数需要两个接口
     cout << " tmp:\n";
     for(auto pr : tmp) cout << pr << " ";
     cout << endl;

     vector<double> mul(Len);
     transform(vec1.begin(),vec1.end(),mul.begin(),bind1st(multiplies<double>(),2.5));
     //transform的一个参数类型 后面函数需要一个接口
     //函数bind1st返回一个binder1st类的对象 可以被用作函数的函数符参数
     cout << " mul:\n";
     for(auto pr : mul) cout << pr << " ";
     cout << endl;
     return 0;
 }