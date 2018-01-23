/* 
 * File:   main.cpp
 * Author: Yunus Cevik
 *
 * Created on 23 Ekim 2016 Pazar, 20:23
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

    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    Memory myMemory(option);
    myCPUProgram.ReadFile(filename);
    cout<<"------------------------------------------------------------------\n\n";
    cout<<"PDF deki elle girilen testler\n\n";
        cout <<myCPUProgram.getLine(0) << endl; 
        cout <<myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;
        myMemory.setMem(0, 100); 
        cout<< myMemory.getMem(0) << endl;
        myMemory.printAll();
        myCPU.execute("MOV #0, R1", myMemory);
        myCPU.execute("MOV R1, #1", myMemory);
        myCPU.print();
        cout<<"--------"<<endl;
        myMemory.printAll();
        cout<<endl<<endl;
    cout<<"------------------------------------------------------------------\n\n";
    cout<<"DOSYADAN "<<filename<<" "<<option<<" ISLEMI\n\n";
    myCPU.setPC(1); // dosyadan okurken PC=1 den baslamasi icin set islemi
    
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
    Computer myComputer2(option);
    myComputer2.setCPU(myComputer1.getCPU());
    myComputer2.setCPUProgram(myComputer1.getCPUProgram());
    myComputer2.setMemory(myComputer1.getMemory());
    myComputer2.execute();
    
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
