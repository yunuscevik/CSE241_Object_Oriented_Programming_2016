#include "Computer.h"
Computer::Computer(){}
Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory& myMemory, int optionVal){
    setCPU(myCPU);
    setCPUProgram(myCPUProgram);
    setMemory(myMemory);
    setOption(optionVal);

}
Computer::Computer(int optionVal){
    setOption(optionVal);
}
void Computer::setCPU(CPU cpu){
    myCPU=cpu;
}
void Computer::setCPUProgram(CPUProgram cpuprog){
    myCPUProgram=cpuprog;
}
void Computer::setMemory(Memory& mmry){
    myMemory=mmry;
}
void Computer::setOption(int opt){
    optionVal=opt;
}
void Computer::execute(){
    
    while(!getCPU().halted()){ 
        string instruction = getCPUProgram().getLine(getCPU().getPC()-1);
        getCPU().execute(instruction,getMemory());    
    }
}