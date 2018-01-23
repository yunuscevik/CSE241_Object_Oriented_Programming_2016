/* 
 * File:   Memory.h
 * Author: Yunus Cevik
 *
 * Created on 03 Kasim 2016 Persembe, 16:24
 */

#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#define MEMORY_SIZE 50
using namespace std;
class Memory{
public:
    Memory(); //default constructor
    Memory(const int); // option parametesi alan constructor
    void printAll();
    //setters
    void setMem(int,unsigned int);
    void setOptionVal(int);
    //getters
    int getMem(unsigned int index){return mmry[index];}
    int getOption()const{return optionVal;}
private:
    int optionVal;
    unsigned int mmry[MEMORY_SIZE];
};
#endif /* MEMORY_H */

