//这是plus第十四章课后第五题 关于MI的练习
#ifndef EMP_H_
#define EMP_H_

#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;

class abstr_emp
{
    private:
        string fname;
        string lname;
        string job;
    public:
        abstr_emp(){}
        abstr_emp(const string s1,const string s2,const string s3)
            :fname(s1),lname(s2),job(s3){}
        virtual void showAll() const;
        virtual void setAll();
        friend ostream & 
                operator<<(ostream & os,const abstr_emp & ab);
        virtual ~abstr_emp() = 0;
};

class employee : public abstr_emp
{
    public:
        employee(){}
        employee(const string &s1,const string &s2,const string &s3)
            :abstr_emp(s1,s1,s3){}
        virtual void showAll() const{abstr_emp::showAll();};
        virtual void setAll() {abstr_emp::setAll();}
};

class manager: virtual public abstr_emp
{
    private:
        int inchargeof;
    protected:
        int InChargeof() const {return inchargeof;}
        int & InChargeof() {return inchargeof;}
    public:
        manager(){}
        manager(const string &s1,const string &s2,const string &s3,int in=0)
            :abstr_emp(s1,s2,s3),inchargeof(in){}
        manager(const abstr_emp & ab,int in=0)
            :abstr_emp(ab),inchargeof(in){}
        manager(const manager & man);
        virtual void showAll() const;
        virtual void setAll();
};

class fink: virtual public abstr_emp
{
    private:
        string reportsto;
    protected:
        const string ReportsTo() const {return reportsto;}
        string & ReportsTo() {return reportsto;}
    public:
        fink(){}
        fink(const string &s1,const string &s2,const string &s3,const string in)
            :abstr_emp(s1,s2,s3),reportsto(in){}
        fink(const abstr_emp & ab,string in)
            :abstr_emp(ab),reportsto(in){}
        fink(const fink & f);
        virtual void showAll() const;
        virtual void setAll();
};

class highfink: public manager, public fink
{
    public:
        highfink(){}
        highfink(const string &s1,const string &s2,const string &s3,const string s,int in=0)
            :abstr_emp(s1,s2,s3),manager(s1,s2,s3,in),fink(s1,s2,s3,s){}
        highfink(abstr_emp & ab,const string &s,int in=0)
            :abstr_emp(ab),manager(ab,in),fink(ab,s){}
        highfink(const fink & f,int in=0);
        highfink(const manager & m,const string &s);
        highfink(const highfink & high);
        virtual void showAll() const;
        virtual void setAll();
};

#endif