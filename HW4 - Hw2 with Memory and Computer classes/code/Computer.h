/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: Yunus Cevik
 *
 * Created on 03 Kasim 2016 Persembe, 16:23
 */

#ifndef COMPUTER_H
#define COMPUTER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Memory.h"
#include "CPU.h"
#include "CPUProgram.h"
class Computer{
public:
    Computer();
    Computer(CPU, CPUProgram, Memory&, int);
    Computer(int);// option parametesi alan constructor
    //setters
    void setCPU(CPU);
    void setCPUProgram(CPUProgram);
    void setMemory(Memory&);
    void setOption(int);
    //getters
    CPU& getCPU(){return myCPU;}
    CPUProgram& getCPUProgram(){return myCPUProgram;}
    Memory& getMemory(){return myMemory;}
    int getOption()const{return optionVal;}
    
    void execute();
private:
    CPU myCPU;
    CPUProgram myCPUProgram;
    Memory myMemory;
    int optionVal;
};


#endif /* COMPUTER_H */

