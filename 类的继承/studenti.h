#ifndef STUDENTI_H_
#define STUDENTI_H_
//这个类是关于私有继承的样例

#include<iostream>
#include<valarray>
#include<string>

class student :private std::string, private std::valarray<double>
{
    private:
        typedef std::valarray<double> ArrayDb;
        std::ostream & arr_out(std::ostream &os) const;
    public:
        student() :std::string("Nullname"),ArrayDb(){}
        explicit student(const std::string &s)
            :std::string(s),ArrayDb(){}
        explicit student(int n)
            :std::string("Nullname"),ArrayDb(n){}
        student(const std::string &s,int n) 
            :std::string(s),ArrayDb(n){}
        student(const std::string &s,const ArrayDb &a)
            :std::string(s),ArrayDb(a){}
        student(const char *s,const double *pb,int n)
            :std::string(s),ArrayDb(pb,n){}
        ~student() {}
        double avarage() const;
        double & operator[](int n);
        double operator[](int n) const;
        const std::string & Name() const;

        friend std::istream & operator>>(std::istream &is,student & stu);
        friend std::ostream & operator<<(std::ostream &os,student & stu);
        friend std::istream & getline(std::istream &is,student &stu);
        //第三个用于中间有空格的输入
};
#endif