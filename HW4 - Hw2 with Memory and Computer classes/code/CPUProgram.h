/* 
 * File:   CPUProgram.h
 * Author: Yunus Cevik
 *
 * Created on 03 Kasim 2016 Persembe, 16:23
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
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
    void setLine(string[],int);
    void setOptionVal(int);
    void setSize(int);
    //getters
    const string getLine(int);
    int getOption() const{return optionVal;}
    int size()const{return count;}
private:
    int optionVal;
    string str[SIZE];
    int count;
};
#endif /* CPUPROGRAM_H */