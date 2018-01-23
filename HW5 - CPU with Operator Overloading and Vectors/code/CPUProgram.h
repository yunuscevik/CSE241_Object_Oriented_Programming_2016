/* 
 * File:   CPUProgram.h
 * Author: Yunus Cevik
 *
 * Created on 14 Kasim 2016 Persembe, 19:23
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "CPU.h"
#define SIZE 256
#define INSTRUCTION_SIZE 3
using namespace std;
class CPUProgram{
public:
    CPUProgram();// default constructor
    CPUProgram(const int); // option parametesi alan constructor
    void ReadFile(const string fileName);
    bool parse(string& );
    void clear(string&);
    int split(string spStr,string& temp,string& temp1);
    int controlParameters(string controlxStr,string controlyStr );
    //setters
    void setLine(vector<string>&);
    void setOptionVal(int);
    //getters
    const string getLine(int);
    int getOption() const{return optionVal;}
    int size()const;
    
    friend ostream& operator <<(ostream&,const CPUProgram&);
    const CPUProgram operator()(int,int);
    const CPUProgram operator+(string)const;
    const CPUProgram operator+(const CPUProgram&);
    //const CPUProgram operator+(const CPUProgram&,const CPUProgram&);
    const CPUProgram operator+=(string);
    CPUProgram operator--();
    CPUProgram operator--(int);
    string operator[](int)const;
    bool operator==(const CPUProgram&)const;
    bool operator!=(const CPUProgram&)const;
    bool operator<(const CPUProgram&)const;
    bool operator>(const CPUProgram&)const;
    bool operator>=(const CPUProgram&)const;
    bool operator<=(const CPUProgram&)const;
private:
    int optionVal;
    vector<string> str;
    
};
#endif /* CPUPROGRAM_H */
