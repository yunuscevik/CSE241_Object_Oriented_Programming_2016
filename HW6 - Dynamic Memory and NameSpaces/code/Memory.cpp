#include "Memory.h"
Memory::Memory(){}
Memory::Memory(int a){
    for(int i=0;i<MEMORY_SIZE;i++){
        setMem(i,0);
        setOptionVal(a);
    }
}
void Memory::setMem(int i, unsigned int s) {
    mmry[i]=s;
}
void Memory::setOptionVal(int opt){
    optionVal=opt;
}
void Memory::printAll() {
    int counter=0;
    for(int i=0;i<MEMORY_SIZE;i++){
        cout<<"#"<<i<<" => "<<getMem(i)<<"\t";
        counter++;
        if(counter==5){
            cout<<endl;
            counter=0;
        }
    }   
}