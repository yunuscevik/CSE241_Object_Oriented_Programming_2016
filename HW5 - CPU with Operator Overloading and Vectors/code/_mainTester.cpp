/* 
 * File:   main.cpp
 * Author: Yunus Cevik
 *
 * Created on 14 Kasim 2016 Pazar, 18:22
 */

#include "requiredIncs.h"
using namespace std;
int convertStrToInt(string);

/*
 * 
 */

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "INVALID ARGUMAN!!!" << endl;
        return 0;
    }
    int option = convertStrToInt(argv[2]);
    if (!(option >= 0 && option<=2)) {
        cerr << "INVALID OPTION VALUE!!!" << endl;
        return 0;
    }


    const char* filename = argv[1];

    //////////////////////////////////////////////////////////////////////////
    //Testing class CPUProgram
    //op []
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    cout << myCPUProgram[0] << endl;
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    //op +
    cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size()]) << endl;
    //op +=
    myCPUProgram += "MOV R2, #50";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
//    //op + <<
    CPUProgram myOtherCPUProgram(option);
    myOtherCPUProgram.ReadFile(filename);
    cout << (myCPUProgram + myOtherCPUProgram) << endl;
    
//
//    //op COMP --
    cout<< (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout<< (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout<< (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    --myOtherCPUProgram;
    cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    //op ()
    cout << myCPUProgram(5, 10) << endl;
    //error check
    cout <<myCPUProgram[myCPUProgram.size()] << endl;
    myCPUProgram += "";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    //////////////////////////////////////////////////////////////////////////
    
    return 0;
}

int convertStrToInt(string str) {
    // stringleri integer a ceviren fonksiyon
    int len = str.length();
    int result = 0;
    int i = 0;
    if (str[0] == '-')
        i++;
    while (i < len) {
        result *= 10;
        result += str[i] - '0';
        i++;
    }
    if (str[0] == '-')
        result = -result;

    return result;
}
