#include "CPU.h"
CPU::CPU(){}
CPU::CPU(int opt){
    
    PC=1;
    hlt=false;
    setOptionVal(opt);
    for(int i=1;i<=REG_NUM;i++){
        setReg(i,0);
    }
    print();
}
void CPU::setPC(int pCount){
    PC=pCount;
}
void CPU::setReg(int a,int b){
    reg[a-1]=b;
}
void CPU::setHalted(bool h){
    hlt=h;
}
void CPU::setOptionVal(int opt){
    optionVal=opt;
}
void CPU::print(){
    
    for(int i=1;i<=REG_NUM;i++){
        cout<<"R"<<i<<" => "<<getReg(i)<<"\t";
    }
    cout<<"\t"<<"PC => "<<getPC();
    cout<<endl;
}
void CPU::execute(string exeStr,Memory& mem){
    string tempExeStr="";
    bool q = true;
    int col=0;
    while(q){ /* exeStr deki verilerin bosluk, ';' ve yorum satirlari olmadan 
              * tempExeStr ye aktarilmasi*/
        if(exeStr[col] != ' ' && exeStr[col] !='\0' 
            &&exeStr[col] != '\t' && exeStr[col] != ';'){
            tempExeStr += exeStr[col];
            col++; 
        }
        else if(exeStr[col] == ';'||exeStr[col+1] == '\0'){
            col=0;   
        }
        else
            col++;
        
        if(col==exeStr.size())
            q = false;
    }
    instructionControl(tempExeStr,mem);
    
}
int CPU::instructionControl (string insStr,Memory& mmry){
    
    string temp;
    // instructionlari bularak fonksiyonlarini cagirma
    for(int j=0;j<3;j++){
        temp += insStr[j];
    }
    if(temp=="MOV") 
        movF(insStr,mmry);
    else if(temp=="PRN") 
        CPU::prnF(insStr,mmry);
    else if(temp=="SUB")
        CPU::subF(insStr,mmry);   
    else if(temp=="HLT")
        CPU::hltF(mmry);
    else if(temp=="ADD")
        CPU::addF(insStr,mmry);
    else if(temp=="JMP")
        CPU::jmpF(insStr,mmry);
    else if(temp=="JPN")
        CPU::jpnF(insStr,mmry);
    else{
        cerr<<" SYNTAX ERROR!!! "<<endl;
        exit(1);
    }
    temp = "";  // degisken arrayi sifirlama 
    setPC((getPC()+1));    
    return 1;
}
int CPU::split(string spStr,string& temp,string& temp1){
    string tempStr= spStr.erase(0,INSTRUCTION_SIZE); /*gönderilen satirlarin
             *  instructionlarini silme ve geri kalanlari gecici stringe atma*/
    int len=tempStr.length();//gecici stringin satir uzunlugu
    int index = tempStr.find_first_of(','); // virgulun kacinci sirada oldugu
    
    // parametreleri ',' e göre bolerek iki parametreye ayirma
    if(tempStr[index]==','){
        temp=tempStr.substr(0,index+1);
        temp1=tempStr.substr(index+1,len);
    }
    else if(!(tempStr=="")){
        temp=tempStr; 
    }
    else{
        cerr<<" SYNTAX ERROR!!! "<<endl;
        exit(1);
    }
}
int CPU::convertStrToInt(string str){
    // stringleri integer a ceviren fonksiyon
    int len=str.length();
    int result = 0;
    int i=0;
    if(str[0]=='-')
        i++;
    while(i<len){
        result *= 10;
        result += str[i]-'0';
        i++;
    }
    if(str[0]=='-')
        result = -result;
    
    return result;
}
bool CPU::movF(string movStr,Memory& mem){
    int adress=0;
    string movx="",movy=""; 
    split(movStr,movx,movy);  
    if(movy==""){
        cerr<<" SYNTAX ERROR!!! "<<endl;
        exit(1);
    }
    movx=movx.erase(movx.size()-1); // regesterlerin ',' lerini siler 
    
    if(movx[0]=='R'){
        switch(movx[1]){
            case '1':   if(movy[0]=='R'){
                            switch(movy[1]){
                                case '1': setReg(1,getReg(1)); // R1=R1
                                    break;
                                case '2': setReg(2,getReg(1)); // R2=R1
                                    break;
                                case '3': setReg(3,getReg(1)); // R3=R1
                                    break;
                                case '4': setReg(4,getReg(1)); // R4=R1
                                    break;
                                case '5': setReg(5,getReg(1)); // R5=R1
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){ // adres 
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            mem.setMem(adress,getReg(1));
                        }
                        else
                            setReg(1,convertStrToInt(movy)); // R1=Constant
                        break;
            
            case '2':   if(movy[0]=='R'){
                            switch(movy[1]){
                                case '1': setReg(1,getReg(2)); // R1=R2
                                    break;
                                case '2': setReg(2,getReg(2)); // R2=R2
                                    break;
                                case '3': setReg(3,getReg(2)); // R3=R2
                                    break;
                                case '4': setReg(4,getReg(2)); // R4=R2
                                    break;
                                case '5': setReg(5,getReg(2)); // R5=R2
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){ // adres 
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            mem.setMem(adress,getReg(2));
                        } 
                        else
                            setReg(2,convertStrToInt(movy));  // R2=Constant
                        break;
            case '3':   if(movy[0]=='R'){
                              switch(movy[1]){
                                case '1': setReg(1,getReg(3)); // R1=R3
                                    break;
                                case '2': setReg(2,getReg(3)); // R2=R3
                                    break;
                                case '3': setReg(3,getReg(3)); // R3=R3
                                    break;
                                case '4': setReg(4,getReg(3)); // R4=R3
                                    break;
                                case '5': setReg(5,getReg(3)); // R5=R3
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){ // adres 
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            mem.setMem(adress,getReg(3));
                        }
                        else
                            setReg(3,convertStrToInt(movy));  // R3=Constant
                        
                        break;
            case '4': if(movy[0]=='R'){
                              switch(movy[1]){
                                case '1': setReg(1,getReg(4)); // R1=R4
                                    break;
                                case '2': setReg(2,getReg(4)); // R2=R4
                                    break;
                                case '3': setReg(3,getReg(4)); // R3=R4
                                    break;
                                case '4': setReg(4,getReg(4)); // R4=R4
                                    break;
                                case '5': setReg(5,getReg(4)); // R5=R4
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){ // adres 
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            mem.setMem(adress,getReg(4));
                        }
                        else
                            setReg(4,convertStrToInt(movy));  // R4=Constant  
                        break;
            case '5':   if(movy[0]=='R'){
                              switch(movy[1]){
                                case '1': setReg(1,getReg(5)); // R1=R5
                                    break;
                                case '2': setReg(2,getReg(5)); // R2=R5
                                    break;
                                case '3': setReg(3,getReg(5)); // R3=R5
                                    break;
                                case '4': setReg(4,getReg(5)); // R4=R5
                                    break;
                                case '5': setReg(5,getReg(5)); // R5=R5
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){ // adres 
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            mem.setMem(adress,getReg(5));
                        }
                        else
                            setReg(5,convertStrToInt(movy)); // R5=Constant
                        break;
        }
    }
    else if(movx[0]=='#'){
        string tempMovx=movx;
        tempMovx=tempMovx.erase(0,1);
        adress=convertStrToInt(tempMovx);
        if(movy[0]=='R'){
            switch(movy[1]){
                case '1': setReg(1,mem.getMem(adress));// R1=adress
                    break;
                case '2': setReg(2,mem.getMem(adress));// R2=adress
                    break;
                case '3': setReg(3,mem.getMem(adress));// R3=adress
                    break;
                case '4': setReg(4,mem.getMem(adress));// R4=adress
                    break;
                case '5': setReg(5,mem.getMem(adress));// R5=adress
                    break;
            }
        }
        else{ 
            mem.setMem(adress,convertStrToInt(movy));// #.. = Constant
        }
    }
    
    if(getOption()==1){
        cout<<"MOV "<<movx<<","<<movy<<" – ";
        print();
        cout<<endl;
    }
    else if(getOption()==2){
        cout<<"MOV "<<movx<<","<<movy<<" – ";
        print();
        cout<<endl;
        mem.printAll();
    }
    return true;
} 
bool CPU::prnF(string prnStr,Memory& mem){
    // ekrana cikti veren fonksiyon
    string prnx,prny="";
    int prnConst=0, adress=0;
    split(prnStr,prnx,prny);
    if(prnx[0]=='R'){
        switch(prnx[1]){
            case '1':   if(getOption()==1)
                            cout<<"PRN R1 – R1= "<<getReg(1)<<endl;
                        else if(getOption()==2){
                            cout<<"PRN R1 – R1= "<<getReg(1)<<endl;
                            mem.printAll();
                        }
                        else 
                            cout<<getReg(1)<<endl;
                          
                break;
            case '2':   if(getOption()==1)
                            cout<<"PRN R2 – R2=> "<<getReg(2)<<endl;
                        else if(getOption()==2){
                            cout<<"PRN R2 – R2=> "<<getReg(2)<<endl;
                            mem.printAll();
                        }
                        else 
                            cout<<getReg(2)<<endl;
                break;
            case '3':   if(getOption()==1)
                            cout<<"PRN R3 – R3=> "<<getReg(3)<<endl;
                        else if(getOption()==2){
                            cout<<"PRN R3 – R3=> "<<getReg(3)<<endl;
                            mem.printAll();
                        }
                        else 
                            cout<<getReg(3)<<endl;
                break;
            case '4':   if(getOption()==1)
                            cout<<"PRN R4 – R4=> "<<getReg(4)<<endl;
                        else if(getOption()==2){
                            cout<<"PRN R4 – R4=> "<<getReg(4)<<endl;
                            mem.printAll();
                        }
                        else 
                            cout<<getReg(4)<<endl;
                break;
            case '5':   if(getOption()==1)
                            cout<<"PRN R5 – R5=> "<<getReg(5)<<endl;
                        else if(getOption()==2){
                            cout<<"PRN R5 – R5=> "<<getReg(5)<<endl;
                            mem.printAll();
                        } 
                        else 
                            cout<<getReg(5)<<endl;
                break;
        }
    }
    else if(prnx[0]=='#'){
        prnx=prnx.erase(0,1);
        adress=convertStrToInt(prnx);
        if(getOption()==1)
            cout<<"PRN #"<<prnx<<" – "<<mem.getMem(adress)<<endl;
        else if(getOption()==2){
            cout<<"PRN #"<<prnx<<" – "<<mem.getMem(adress)<<endl;
            mem.printAll();
        }
        else
            cout<<mem.getMem(adress)<<endl;
    }
    else{
            prnConst = convertStrToInt(prnx);
            if(getOption()==1)
                cout<<"PRN "<<prnConst<<" – "<<prnConst <<endl;
            else if(getOption()==2){
                cout<<"PRN "<<prnConst<<" – "<<prnConst <<endl;
                mem.printAll();
            }
            else
                cout<<prnConst<<endl;   
    }
    
    return true;
}
bool CPU::addF(string addStr,Memory& mem){
    int adress=0;
    string addx,addy; 
    split(addStr,addx,addy);
    if(addy==""){
        cerr<<" SYNTAX ERROR!!! "<<endl;
        exit(1);
    }
    addx=addx.erase(addx.size()-1);
    if(addx[0]=='R'){
        switch(addx[1]){
            case '1':   if(addy[0]=='R'){
                          switch(addy[1]){
                                case '1': setReg(1,(getReg(1)+getReg(1)));//R1=R1+R1
                                    break;
                                case '2': setReg(1,(getReg(1)+getReg(2)));//R1=R1+R2
                                    break;
                                case '3': setReg(1,(getReg(1)+getReg(3)));//R1=R1+R3
                                    break;
                                case '4': setReg(1,(getReg(1)+getReg(4)));//R1=R1+R4
                                    break;
                                case '5': setReg(1,(getReg(1)+getReg(5)));//R1=R1+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){ // adres 
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            mem.setMem(adress,getReg(1));
                        } 
                        else
                            setReg(1,(getReg(1)+convertStrToInt(addy)));//R1=R1+Constant          
            break;
            case '2':   if(addy[0]=='R'){
                              switch(addy[1]){
                                case '1': setReg(2,(getReg(2)+getReg(1)));//R2=R2+R1
                                    break;
                                case '2': setReg(2,(getReg(2)+getReg(2)));//R2=R2+R2
                                    break;
                                case '3': setReg(2,(getReg(2)+getReg(3)));//R2=R2+R3
                                    break;
                                case '4': setReg(2,(getReg(2)+getReg(4)));//R2=R2+R4
                                    break;
                                case '5': setReg(2,(getReg(2)+getReg(5)));//R2=R2+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){ // adres 
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            mem.setMem(adress,getReg(2));
                        }
                        else
                            setReg(2,(getReg(2)+convertStrToInt(addy)));//R2=R2+Constant                        
            break;
            case '3':   if(addy[0]=='R'){
                            switch(addy[1]){
                                case '1': setReg(3,(getReg(3)+getReg(1)));//R3=R3+R1
                                    break;
                                case '2': setReg(3,(getReg(3)+getReg(2)));//R3=R3+R2
                                    break;
                                case '3': setReg(3,(getReg(3)+getReg(3)));//R3=R3+R3
                                    break;
                                case '4': setReg(3,(getReg(3)+getReg(4)));//R3=R3+R4
                                    break;
                                case '5': setReg(3,(getReg(3)+getReg(5)));//R3=R3+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){ // adres 
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            mem.setMem(adress,getReg(3));
                        }
                        else
                            setReg(3,(getReg(3)+convertStrToInt(addy)));//R3=R3+Constant
            break;
            case '4': if(addy[0]=='R'){
                              switch(addy[1]){
                                case '1': setReg(4,(getReg(4)+getReg(1)));//R4=R4+R1
                                    break;
                                case '2': setReg(4,(getReg(4)+getReg(2)));//R4=R4+R2
                                    break;
                                case '3': setReg(4,(getReg(4)+getReg(3)));//R4=R4+R3
                                    break;
                                case '4': setReg(4,(getReg(4)+getReg(4)));//R4=R4+R4
                                    break;
                                case '5': setReg(4,(getReg(4)+getReg(5)));//R4=R4+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){ // adres 
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            mem.setMem(adress,getReg(4));
                        }
                        else
                            setReg(4,(getReg(4)+convertStrToInt(addy)));//R4=R4+Constant                         
            break;
            case '5':   if(addy[0]=='R'){
                              switch(addy[1]){
                                case '1': setReg(5,(getReg(5)+getReg(1)));//R5=R5+R1
                                    break;
                                case '2': setReg(5,(getReg(5)+getReg(2)));//R5=R5+R2
                                    break;
                                case '3': setReg(5,(getReg(5)+getReg(3)));//R5=R5+R3
                                    break;
                                case '4': setReg(5,(getReg(5)+getReg(4)));//R1=R5+R3
                                    break;
                                case '5': setReg(5,(getReg(5)+getReg(5)));//R1=R1+R3
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){ // adres 
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            mem.setMem(adress,getReg(5));
                        }
                        else
                            setReg(5,(getReg(5)+convertStrToInt(addy)));//R5=R5+Constant
            break; 
        }
    }
    else if(addx[0]=='#'){
        string tempAddx=addx;
        tempAddx=tempAddx.erase(0,1);
        adress=convertStrToInt(tempAddx);
        if(addy[0]=='R'){
            switch(addy[1]){
                case '1': setReg(1,mem.getMem(adress));// R1=adress
                    break;
                case '2': setReg(2,mem.getMem(adress));// R2=adress
                    break;
                case '3': setReg(3,mem.getMem(adress));// R3=adress
                    break;
                case '4': setReg(4,mem.getMem(adress));// R4=adress
                    break;
                case '5': setReg(5,mem.getMem(adress));// R5=adress
                    break;
            }
        }
        else{ 
            mem.setMem(adress,convertStrToInt(addy));// #.. = Constant
        }
    }
    if(getOption()==1){
        cout<<"ADD "<<addx<<","<<addy<<" – ";
        print();
        cout<<endl;
    }
    else if(getOption()==2){
        cout<<"ADD "<<addx<<","<<addy<<" – ";
        print();
        cout<<endl;
        mem.printAll();
    }
    return true; 
}
bool CPU::subF(string subStr,Memory& mem){
    int adress=0;
    string subx,suby;
    split(subStr,subx,suby);
    if(suby==""){
        cerr<<" SYNTAX ERROR!!! "<<endl;
        exit(1);
    }
    subx=subx.erase(subx.size()-1);
    if(subx[0]=='R'){
        switch(subx[1]){
            case '1':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': setReg(1,(getReg(1)- getReg(1)));//R1=R1-R1
                                    break;
                                case '2': setReg(1,(getReg(1)- getReg(2)));//R1=R1-R2
                                    break;
                                case '3': setReg(1,(getReg(1)- getReg(3)));//R1=R1-R3
                                    break;
                                case '4': setReg(1,(getReg(1)- getReg(4)));//R1=R1-R4
                                    break;
                                case '5': setReg(1,(getReg(1)- getReg(5)));//R1=R1-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){ // adres 
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            mem.setMem(adress,getReg(1));
                        }
                        else
                            setReg(1,(getReg(1)-convertStrToInt(suby)));//R1=R1-Constant
            break;
            case '2':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': setReg(2,(getReg(2)- getReg(1)));//R2=R2-R1
                                    break;
                                case '2': setReg(2,(getReg(2)- getReg(2)));//R2=R2-R2
                                    break;
                                case '3': setReg(2,(getReg(2)- getReg(3)));//R2=R2-R3
                                    break;
                                case '4': setReg(2,(getReg(2)- getReg(4)));//R2=R2-R4
                                    break;
                                case '5': setReg(2,(getReg(2)- getReg(5)));//R2=R2-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){ // adres 
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            mem.setMem(adress,getReg(2));
                        }
                        else
                            setReg(2,(getReg(2)-convertStrToInt(suby)));//R2=R2-Constant
            break;
            case '3':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': setReg(3,(getReg(3)- getReg(1)));//R3=R3-R1
                                    break;
                                case '2': setReg(3,(getReg(3)- getReg(2)));//R3=R3-R2
                                    break;
                                case '3': setReg(3,(getReg(3)- getReg(3)));//R3=R3-R3
                                    break;
                                case '4': setReg(3,(getReg(3)- getReg(4)));//R3=R3-R4
                                    break;
                                case '5': setReg(3,(getReg(3)- getReg(5)));//R3=R3-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){ // adres 
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            mem.setMem(adress,getReg(3));
                        }
                        else
                            setReg(3,(getReg(3)-convertStrToInt(suby)));//R3=R3-Constant
            break;
            case '4': if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': setReg(4,(getReg(4)- getReg(1)));//R4=R4-R1
                                    break;
                                case '2': setReg(4,(getReg(4)- getReg(2)));//R4=R4-R2
                                    break;
                                case '3': setReg(4,(getReg(4)- getReg(3)));//R4=R4-R3
                                    break;
                                case '4': setReg(4,(getReg(4)- getReg(4)));//R4=R4-R4
                                    break;
                                case '5': setReg(4,(getReg(4)- getReg(5)));//R1=R4-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){ // adres 
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            mem.setMem(adress,getReg(4));
                        }
                        else
                            setReg(4,(getReg(4)-convertStrToInt(suby)));//R1=R1-Constant
            break;
            case '5':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': setReg(5,(getReg(5)- getReg(1)));//R5=R5-R1
                                    break;
                                case '2': setReg(5,(getReg(5)- getReg(2)));//R5=R5-R2
                                    break;
                                case '3': setReg(5,(getReg(5)- getReg(3)));//R5=R5-R3
                                    break;
                                case '4': setReg(5,(getReg(5)- getReg(4)));//R5=R5-R4
                                    break;
                                case '5': setReg(5,(getReg(5)- getReg(5)));//R5=R5-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){ // adres 
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            mem.setMem(adress,getReg(5));
                        }
                        else
                            setReg(5,(getReg(5)-convertStrToInt(suby)));//R5=R5-Constant
            break;  
        }
    }
    else if(subx[0]=='#'){
        string tempSubx=subx;
        tempSubx=tempSubx.erase(0,1);
        adress=convertStrToInt(tempSubx);
        if(suby[0]=='R'){
            switch(suby[1]){
                case '1': setReg(1,mem.getMem(adress));// R1=adress
                    break;
                case '2': setReg(2,mem.getMem(adress));// R2=adress
                    break;
                case '3': setReg(3,mem.getMem(adress));// R3=adress
                    break;
                case '4': setReg(4,mem.getMem(adress));// R4=adress
                    break;
                case '5': setReg(5,mem.getMem(adress));// R5=adress
                    break;
            }
        }
        else{ 
            mem.setMem(adress,convertStrToInt(suby));// #.. = Constant
        }
    }
    if(getOption()==1){
        cout<<"SUB "<<subx<<","<<suby<<" – ";
        print();
        cout<<endl;
    }
    else if(getOption()==2){
        cout<<"SUB "<<subx<<","<<suby<<" – ";
        print();
        cout<<endl;
        mem.printAll();
    }
    return true;
}
bool CPU::jmpF(string jmpStr,Memory& mem){  
    string jmpx="",jmpy="";
    split(jmpStr,jmpx,jmpy);
    if(jmpx[0]=='R'&&jmpx[1]=='1'&& getReg(1)==0)//R1==0
        setPC(convertStrToInt(jmpy)-1);

    else if(jmpx[0]=='R'&&jmpx[1]=='2'&& getReg(2)==0)//R2==0
        setPC(convertStrToInt(jmpy)-1);

    else if(jmpx[0]=='R'&&jmpx[1]=='3'&& getReg(3)==0)//R3==0
        setPC(convertStrToInt(jmpy)-1);

    else if(jmpx[0]=='R'&&jmpx[1]=='4'&& getReg(4)==0)//R4==0
        setPC(convertStrToInt(jmpy)-1);

    else if(jmpx[0]=='R'&&jmpx[1]=='5'&& getReg(5)==0)//R5==0
        setPC(convertStrToInt(jmpy)-1);

    else if(jmpx[0]!='R'&&(jmpx[0]>='0'&&jmpx[0]<='9')) // Constant ise
        setPC(convertStrToInt(jmpx)-1);    
    
    if(getOption()==1){
        cout<<"JMP "<<jmpx<<jmpy<<" – ";
        print();
        cout<<endl;
    }
    else if(getOption()==2){
        cout<<"JMP "<<jmpx<<jmpy<<" – ";
        print();
        cout<<endl;
        mem.printAll();
    }
    return true;
}
bool CPU::jpnF(string jpnStr,Memory& mem){
    string jpnx="",jpny="";
    split(jpnStr,jpnx,jpny);
    if(jpnx[0]=='R'&&jpnx[1]=='1'&& getReg(1)==0 || getReg(1)<0)//R1==0 || R1<0
        setPC(convertStrToInt(jpny)-1);

    else if(jpnx[0]=='R'&&jpnx[1]=='2'&& getReg(2)==0 || getReg(2)<0)//R2==0 || R1<0
        setPC(convertStrToInt(jpny)-1);

    else if(jpnx[0]=='R'&&jpnx[1]=='3'&& getReg(3)==0 || getReg(3)<0)//R3==0 || R1<0
        setPC(convertStrToInt(jpny)-1);

    else if(jpnx[0]=='R'&&jpnx[1]=='4'&& getReg(4)==0 || getReg(4)<0)//R4==0 || R1<0
        setPC(convertStrToInt(jpny)-1);

    else if(jpnx[0]=='R'&&jpnx[1]=='5'&& getReg(5)==0 || getReg(5)<0)//R5==0 || R1<0
        setPC(convertStrToInt(jpny)-1);
   
    
    if(getOption()==1){
        cout<<"JPN "<<jpnx<<jpny<<" – ";
        print();
        cout<<endl;
    }
    if(getOption()==2){
        cout<<"JPN "<<jpnx<<jpny<<" – ";
        print();
        cout<<endl;
        mem.printAll();
    }
    return true;
}
void CPU::hltF(Memory& mem){
    setHalted(true);
    
    if(getOption()==1){
        cout<<endl<<"HLT "<<" – ";
        print();
        cout<<endl;
    }
    else if(getOption()==2){
        cout<<endl<<"HLT "<<" – ";
        print();
        cout<<endl;
        mem.printAll();
    }
    else {
        cout<<endl;
        print();
        cout<<endl;
        mem.printAll();
    }
    
}