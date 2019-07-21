//不全部显示的原因是inchargeof是int getline无法正确获取值
//我们学到了对与同一个基类的不同继承类在同一个数组中
//从文件中读取我们可以设置一个标记来区分
#include<iostream>
#include"17:6.h"
#include"17:6.hpp"
#include<string>
using namespace std;
const int MAX = 10;
string filename="testd.cpp";
abstr_emp * book[MAX];
int main()
{
    int count = 0;
    ifstream fin;
    do
    {
        fin.clear();
        fin.open(filename);
        while(fin.is_open())
        {
            cout << "current file: "<< filename << " constents is:";
            int count = 0;
            string str;
            while(getline(fin,str))
            {
                abstr_emp *ptr=NULL;
                if(str=="1")
                {
                    string fname,lname,job;
                    getline(fin,fname);
                    getline(fin,lname);
                    getline(fin,job);

                    ptr = new employee(fname,lname,job);
                    ptr->showAll();
                    book[count++]=ptr;
                }
                else if(str=="2")
                {
                    string fname,lname,job;
                    int inchargeof=0;
                    getline(fin,fname);
                    getline(fin,lname);
                    getline(fin,job);
                    fin >> inchargeof;
                    cout << inchargeof << endl;
                    getchar();

                    ptr = new manager(fname,lname,job,inchargeof);
                    ptr->showAll();
                    book[count++]=ptr;
                }
                else if(str=="3")
                {
					std::string fname, lname, job, reportsto;
					std::getline(fin, fname);
					std::getline(fin, lname);
					std::getline(fin, job);
					std::getline(fin, reportsto);
 
					ptr = new fink(fname, lname, job, reportsto);
					ptr->showAll();
                    book[count++]=ptr;
                }
                else if(str=="4")
                {
					std::string fname, lname, job, inchargeof, reportsto;
					std::getline(fin, fname);
					std::getline(fin, lname);
					std::getline(fin, job);
					std::getline(fin, inchargeof);
					std::getline(fin, reportsto);
 
					ptr = new highfink(fname, lname, job, reportsto, atoi(inchargeof.c_str()));
					ptr->showAll();
                    book[count++]=ptr;
                }
                std::getline(fin, str);
                //这句很重要 用来跳出循环
            }
            fin.close();
        }

        ofstream fout(filename,ios_base::out|ios_base::app);
        if(!fout.is_open())
        {
            cerr << "Error in open fout!\n";
            exit(EXIT_FAILURE);
        }

        abstr_emp *ptr = NULL;
		cout << "选择要生成的类型:\n";
		cout << "1、employee\t2、manager\n3、fink\t4、highfink\n";
        int ans;
        string ff;
        cin >> ans;
        cin.get();//消除流中的回车
        switch (ans)
        {
            case 1:
                ptr = new employee;
                ff="1";
                break;
		    case 2:
			    ptr = new manager;
                ff="2";
			    break;
		    case 3:
			    ptr = new fink;
                ff="3";
			    break;
		    case 4:
			    ptr = new highfink;
                ff="4";
			    break;
		    default:
			    break;
        }
        fout << ff << endl;
        book[count++]=ptr;
        ptr->setAll();
        ptr->writeall(fout);

        string f;
        cout << "continue?(yes or no)\n";
        cin >> f;
        fout.close();
        fout.clear();
        if(f[0]=='n') break;
    }while(true);

    fin.close();
    return 0;
}