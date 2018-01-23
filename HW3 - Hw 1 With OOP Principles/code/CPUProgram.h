/* 
 * File:   CPUProgram.h
 * Author: Yunus Cevik
 *
 * Created on 23 Ekim 2016 Pazar, 18:23
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <fstream>
#include <string>
#define SIZE 256
#define INSTRUCTION_SIZE 3
using namespace std;
class CPUProgram{
public:
    CPUProgram(const string fileName); // constructor
    string sgh[];// hocam bunu olusturdum ama kullanmadim silince bad allocac hatasi aliyorum.
    int readFile(const string fileName);
    void setLine(string[],int);
    string getLine(int);
    void setSize(int);
    int size(){return count;}
private:
    string str[SIZE];
    int count;
};
#endif /* CPUPROGRAM_H */

