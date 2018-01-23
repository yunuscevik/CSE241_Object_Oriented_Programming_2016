

/* 
 * File:   Exception.h
 * Author: asus-ubuntu
 *
 * Created on 25 Aralık 2016 Pazar, 04:44
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
class Exception:public exception{
public:
    Exception(){};
    Exception(string s){str = s;}
    virtual const char* what() const throw(){return str.c_str();}
    
private:
    string str;
};


#endif /* EXCEPTION_H */

