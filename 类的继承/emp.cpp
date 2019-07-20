//这道题不好做的地方在highfink类中的构造函数
//需要强制类型转换

#include"emp.h"
#include"emp.hpp"
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;

int main()
{
	employee em("Trip", "Harris", "Thumper");
	cout << em << endl;
	em.showAll();
	manager ma("Amorphia", "Spindragon", "Nuancer", 5);
	cout << ma << endl;
	ma.showAll();
 
	fink fi("Matt", "Ogga", "Oiler", "Juno Barr");
	cout << fi << endl;
	fi.showAll();
	highfink hf(ma, "Curly Kew");
	hf.showAll();
	cout << "Press a key for next phase:\n";
	cin.get();
	highfink hf2;
	hf2.setAll();
 
	cout << "Using an abstr_emp * pointer:\n";
	abstr_emp *tri[4] = { &em, &fi, &hf, &hf2 };
	for (int i = 0; i < 4; ++i)
		tri[i]->showAll();
 
	return 0;
}