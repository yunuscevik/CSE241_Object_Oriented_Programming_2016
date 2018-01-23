#include "CPUProgram.h"

CPUProgram::CPUProgram(const string fileName){
    readFile(fileName);
}
int CPUProgram::readFile(const string fileName){
    fstream file;
    file.open(&fileName[0]); // dosya acma
    if(!file){
        cerr << " UNABLE TO OPEN FILE!!! ";
        return 0;
    }
    string str1[SIZE],str2[SIZE];
    for(int i=0;i<SIZE;i++){
        if(getline(file,str1[i]))
            setSize(size()+1); // satir sayisini hesaplama
    }
    bool q = true;
    int row=0,col=0;
    while(q){ /* str1 deki verilerin bosluk, ';' ve yorum satirlari olmadan 
              * str2 ye aktarilmasi*/
        if(str1[row][col] != ' ' && str1[row][col] !='\0' 
            &&str1[row][col] != '\t' && str1[row][col] != ';'){
            str2[row] += str1[row][col];
            col++; 
        }
        else if(str1[row][col] == ';'||str1[row][col+1] == '\0'){
            row++;
            col=0;   
        }
        else
            col++;
        
        if(row==size())
            q = false;
    }
    for(int i=0;i<size();i++){
        setLine(str2,i);
    }
    file.close();
    
}
void CPUProgram::setLine(string s[],int size){
    str[size]=s[size];
}
string CPUProgram::getLine(int size){
    return str[size-1];
}   
void CPUProgram::setSize(int s){
    count=s;
}