/* 
 * File:   CPU.h
 * Author: Yunus Cevik
 *
 * Created on 23 Ekim 2016 Pazar, 19:13
 */

#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#define INSTRUCTION_SIZE 3
#define REG_NUM 5
using namespace std;
class CPU{
public:
    CPU(char ch);// constructor
    //setters
    void setReg(int,int);
    void setPC(int);
    void setHlted(bool);
    //getters
    bool halted(){return hlt;}
    int getReg(int index)const {return reg[index-1];}
    int getPC()const {return PC;}
    void print(); // tum regesterleri ekrana basar
    void execute(string);
    int split(string spStr,string& temp,string& temp1);
    int controlParameters(string controlxStr,string controlyStr );
    int convertStrToInt(string str);
    
private:
    char optionVal;
    int reg[REG_NUM];
    int PC;
    bool hlt;
    int instructionControl (string insStr);
    bool movF(string movStr);
    bool prnF(string prnStr);
    bool addF(string addStr);
    bool subF(string subStr);
    bool jmpF(string jmpStr);
    void hltF();
};
#endif /* CPU_H */