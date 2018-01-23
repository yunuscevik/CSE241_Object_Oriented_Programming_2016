/* 
 * File:   CPU.h
 * Author: Yunus Cevik
 *
 * Created on 03 Kasim 2016 Persembe, 16:23
 */

#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#include <cstdlib>
#include "Memory.h"
#define INSTRUCTION_SIZE 3
#define REG_NUM 5
using namespace std;
class CPU{
public:
    CPU(); //default constructor
    CPU(const int);// option parametesi alan constructor
    //setters
    void setReg(int,int);
    void setPC(int);
    void setHalted(bool);
    void setOptionVal(int);
    //getters
    bool halted()const{return hlt;}
    int getReg(int index)const {return reg[index-1];}
    int getPC()const {return PC;}
    int getOption()const{return optionVal;}
    /*----------------------------------------*/
    void print(); // tum regesterleri ekrana basar
    void execute(string,Memory&);
    int split(string spStr,string& temp,string& temp1);
    int convertStrToInt(string str);
    
private:
    int optionVal;
    int reg[REG_NUM];
    int PC;
    bool hlt;
    int instructionControl (string insStr,Memory&);
    bool movF(string movStr,Memory&);
    bool prnF(string prnStr,Memory&);
    bool addF(string addStr,Memory&);
    bool subF(string subStr,Memory&);
    bool jmpF(string jmpStr,Memory&);
    bool jpnF(string jmpStr,Memory&);
    void hltF(Memory&);
};
#endif /* CPU_H */