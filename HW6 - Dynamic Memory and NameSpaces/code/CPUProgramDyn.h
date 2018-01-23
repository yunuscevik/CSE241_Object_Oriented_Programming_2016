/* 
 * File:   CPUProgramDyn.h
 * Author: Yunus Cevik
 *
 * Created on 26 Kasım 2016 Cumartesi, 15:28
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "CPU.h"
#define INSTRUCTION_SIZE 3
using namespace std;
namespace cpuProDyn{
    class CPUProgramDyn{
    public:
        CPUProgramDyn();// default constructor
        CPUProgramDyn(int); // option parametesi alan constructor
        CPUProgramDyn(const CPUProgramDyn& );//copy constructor
        ~CPUProgramDyn(); // destructor
        void ReadFile(const char* fileName);
        bool parse(string& );
        void clear(string&);
        int split(string spStr,string& temp,string& temp1);
        int controlParameters(string controlxStr,string controlyStr );
        bool full( ) const { return (capacity == usedSection); }
        //setters
        void setLine(string*);
        void setOptionVal(int);
        void setSize(int);
        void setCapacity(int);
        //getters
        const string getLine(int);
        int getOption() const{return optionVal;}
        int size()const{return usedSection;}
        int getCapacity( ) const { return capacity; }
        //operators
        friend ostream& operator <<(ostream&,const CPUProgramDyn&);
        const CPUProgramDyn operator()(int,int);
        const CPUProgramDyn operator+(string)const;
        const CPUProgramDyn operator+(const CPUProgramDyn&);
        const CPUProgramDyn operator+=(string);
        CPUProgramDyn operator--();
        CPUProgramDyn operator--(int);
        string operator[](int)const;
        bool operator==(const CPUProgramDyn&)const;
        bool operator!=(const CPUProgramDyn&)const;
        bool operator<(const CPUProgramDyn&)const;
        bool operator>(const CPUProgramDyn&)const;
        bool operator>=(const CPUProgramDyn&)const;
        bool operator<=(const CPUProgramDyn&)const;
        CPUProgramDyn& operator=(const CPUProgramDyn& rightSide);
    private:
        int optionVal;
        string *str;
        int capacity; //for the size of the array.
        int usedSection; //for the number of array positions currently in use.
    };
}
#endif /* CPUPROGRAMDYN_H */

