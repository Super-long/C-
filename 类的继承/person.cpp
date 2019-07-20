#include"person.h"
#include<iostream>
int main()
{
	person p("Tree");
	Gunslinger g("Tree", 3, 1.2);
	Pokerplayer po("shana");
	BadDude b("yuuji", 2, 1.1);
 
	person *ptr = &p;
	ptr->show();
 
	ptr = &g;
	ptr->show();
 
	ptr = &po;
	ptr->show();
 
	ptr = &b;
	ptr->show();
 
	return 0;
}