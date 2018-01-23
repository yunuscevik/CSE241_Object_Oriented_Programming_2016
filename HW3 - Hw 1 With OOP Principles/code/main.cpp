/* 
 * File:   main.cpp
 * Author: Yunus Cevik
 * HW3
 *
 * Created on 23 Ekim 2016 Pazar, 20:23
 */

#include <iostream>
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc != 3){
        cerr<<"INVALID ARGUMAN!!!"<<endl;
        return 0;
    }
	if(argv[2][0]>'1'){
        cerr<<"INVALID OPTION VALUE!!!"<<endl;
        return 0;
    }
    CPU myCPU(argv[2][0]); 
    CPUProgram myProg(argv[1]);
    while(!myCPU.halted()){ 
        string instruction = myProg.getLine(myCPU.getPC());
        myCPU.execute(instruction);    
    }
    return 0;
}

