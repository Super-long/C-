#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> myvector;
	for (int i = 0; i < 100; i++)
	{
		myvector.push_back(i);
	}
	cout << "capacity值为："<<myvector.capacity() << endl;
	cout << "size值为：" << myvector.size() << endl;
	myvector.clear();
	cout << "clear之后...." << endl;
	cout << "capacity值为：" << myvector.capacity() << endl;
	cout << "size值为：" << myvector.size() << endl;
	//vector<int>().swap(myvector);
    myvector.resize(2);
	cout << "swap操作后..." << endl;
	cout << "capacity值为：" << myvector.capacity() << endl;
	cout << "size值为：" << myvector.size() << endl;
	for (int i = 0; i < 100; i++)
	{
		myvector.push_back(i);
	}
	cout << "重新push_back后...." << endl;
	cout << "capacity值为：" << myvector.capacity() << endl;
	cout << "size值为：" << myvector.size() << endl;
	myvector.clear();
	myvector.shrink_to_fit();
	cout << "clear+ shrink_to_fit()后..." << endl;
	cout << "capacity值为：" << myvector.capacity() << endl;
	cout << "size值为：" << myvector.size() << endl;
	cin.get();
}
