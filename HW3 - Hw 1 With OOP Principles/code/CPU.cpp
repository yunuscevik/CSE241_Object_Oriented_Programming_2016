#include "CPU.h"
CPU::CPU(char ch){
    for(int i=0;i<5;i++){
        reg[i]=0;
    }
    optionVal=ch;
    PC=1;
    hlt=false;
    print();
}
void CPU::setPC(int pCount){
    PC=pCount;
}
void CPU::setReg(int a,int b){
    reg[a-1]=b;
}
void CPU::setHlted(bool h){
    hlt=h;
}
void CPU::print(){
    
    for(int i=1;i<=REG_NUM;i++){
        cout<<"R"<<i<<" => "<<getReg(i)<<"\t";
    }
    cout<<"\t"<<"PC => "<<getPC();
    cout<<endl;
}
void CPU::execute(string exeStr){
    instructionControl(exeStr);
    
}
int CPU::instructionControl (string insStr){
    
    string temp;
    // kucuk harfleri buyuk harfe cevirme
    for(int j=0;j<insStr.length();j++){
        if(insStr[j]>='a' && insStr[j]<='z')
        insStr[j] += 'A'-'a';
    } 
    //cout<<insStr<<endl;
    // instructionlari bularak fonksiyonlarini cagirma
    for(int j=0;j<3;j++){
        temp += insStr[j];
    }
    if(temp=="MOV"){ 
        if(CPU::movF(insStr) == false)
            return 0;
        
    }
    else if(temp=="PRN"){ 
        if(CPU::prnF(insStr) == false)
            return 0;
    }
    else if(temp=="SUB"){ 
        if(CPU::subF(insStr) == false)
            return 0;
        }
    else if(temp=="HLT"){
        CPU::hltF();
            
    }
    else if(temp=="ADD"){
        if(CPU::addF(insStr) == false)
            return 0;    
    }
    else if(temp=="JMP"){
        if(CPU::jmpF(insStr) == false)
           return 0;
    }
    else{
        cerr<< " SYNTAX ERROR!!! "<<endl;
        return 0;
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
        return 0;
    }
}
int CPU::controlParameters(string controlxStr,string controlyStr ){
    // Hatalar
    int lenx = controlxStr.length();
    int leny = controlyStr.length();
    int i=0,j=0;
    
    if(controlxStr[0]!='R'&&(!(controlxStr[0]>='0' && controlxStr[0]<='9'))){
        
        cerr<< " SYNTAX ERROR!!! "<<endl;
        return 0;
    }
    // Tek parametrelilerde R1 - R5 arasinda degilse (R1a  R4#)
    if( controlxStr[i]=='R'&&(controlxStr[i+1]>='0' && controlxStr[i+1]<='9') 
            &&lenx>2 && controlxStr[i+2]!=',' ){
        cerr<< " SYNTAX ERROR!!! "<<endl;
        return 0;       
    }
    // Cift parametreliler icin R1,- R5, arasinda degil ise  (Ra, R#,)  
    if(controlxStr[i]=='R'&& controlxStr[lenx-1]==','){
        i++;
        if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){ 
               cerr<< " SYNTAX ERROR!!! "<<endl;
               return 0;
        }
    }
    
    
    
    // Cift parametreliler icin   ,R1  ,10  iki parametreden 1. yok 2. var ise 
    else if(controlxStr[i]==','){
               cerr<< " SYNTAX ERROR!!! "<<endl;
               return 0;
        }
    // Tek parametreliler icin R1 - R5  arasinda degil ise  (Ra  R# ) 
    else if(controlxStr[i]=='R' &&controlxStr[lenx-1]!=',' ){
        i++;
        if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
               cerr<< " SYNTAX ERROR!!! "<<endl;
               return 0;
            }  
        }
    // Cift parametrelilerde 1. parametre sayi degilse (1a1,  11#, 222, )
    else if(controlxStr[lenx-1]==',' 
            && (controlxStr[i]>='0' && controlxStr[i]<='9')){
        
        for(int i=0;i<lenx;i++){
            if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                cerr<<" SYNTAX ERROR!!! "<<endl;
               return 0;
            }   
        } 
    }
    // Tek parametrelilerde 1. parametre sayi degilse  (1a1 11#)
    else if(controlxStr[lenx-1]!=',' && (controlxStr[i]>='0' 
            && controlxStr[i]<='9')){
        
        for(int i=0;i<lenx;i++){
            if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                cerr<< " SYNTAX ERROR!!! "<<endl;
                 return 0;
            }  
        }
    }
    
    
    else if(controlxStr[i]>='0' && controlxStr[i]<='9'){
        
        for(int i=0;i<lenx ;i++){
            if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                cerr<< " SYNTAX ERROR!!! "<<endl;
                 return 0;
            }     
        }
    }
    //---------------------------
    // Cift parametrelilerde Null, Regester veya sayi degilse 
    if(controlyStr[j]!='R'&&(!(controlyStr[j]>='0' && controlyStr[j]<='9'))
            &&controlyStr !="" ){         
            cerr<< " SYNTAX ERROR!!! "<<endl; 
            return 0;
        }
   
    // Cift parametrelilerde 2. parametre R1 - R5 arasinda degilse (Rr Ra R#)
    if(leny==2 && controlyStr[j]=='R'){
        j++;
        if(!(controlyStr[j]>='0' && controlyStr[j]<='9')){
                         
               cerr<< " SYNTAX ERROR!!! "<<endl; 
                return 0;
            }
        }
    
    // Cift parametrelilerde sayi degilse 
    else if(leny==2 && controlyStr[j]!='R'){
        j++;
            if(!(controlyStr[j]>='0' && controlyStr[j]<='9')){
                         
                cerr<< " SYNTAX ERROR!!! "<<endl; 
                return 0;
            }
        }
    // Cift parametrelilerde 2. parametre regester degilse (R1a R2#)
    else if(leny>2 && controlyStr[j]=='R'&&(controlyStr[j+1]>='0' && controlyStr[j+1]<='9')){          
            cerr<< " SYNTAX ERROR!!! "<<endl; 
            return 0;
        }
    // Cift parametrelilerde 2. parametre sayi degilse (1a1 1## )
    else if(controlyStr[j]>='0' && controlyStr[j]<='9'){
        
        for(int i=0;i<leny;i++){
            if(!(controlyStr[i]>='0' && controlyStr[i]<='9')){
                cerr<< " SYNTAX ERROR!!! "<<endl;
                 return 0;
            }
        }
        
    }
    
    return 1;
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
bool CPU::movF(string movStr){
    
    string movx="",movy=""; 
    split(movStr,movx,movy);  
    if(controlParameters(movx,movy) == 0)
	return false;
    if(movy==""){
        cerr<<" SYNTAX ERROR!!! "<<endl;
        return false;
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
                       
                        else{
                            setReg(1,convertStrToInt(movy)); // R1=Constant
                          
                        }
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
                        
                        else{
                            setReg(2,convertStrToInt(movy));  // R2=Constant
                        }
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
                        
                        else{
                            setReg(3,convertStrToInt(movy));  // R3=Constant
                        }
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
                        
                        else{
                            setReg(4,convertStrToInt(movy));  // R4=Constant
                        }
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
                        
                        else{
                            setReg(5,convertStrToInt(movy)); // R5=Constant
                        }
            break;
        }
    }
    
    if(optionVal=='1'){
        cout<<"PRN "<<movx<<","<<movy<<" – ";
        print();
        cout<<endl;
    }
    return true;
} 
bool CPU::prnF(string prnStr){
    // ekrana cikti veren fonksiyon
    string prnx,prny="";
    int prnConst=0;
    split(prnStr,prnx,prny);
    if(controlParameters(prnx,prny) == 0)
	return false;
    if(prnx[0]=='R'){
        switch(prnx[1]){
            case '1':   if(optionVal=='1')
                            cout<<"PRN R1 – R1= "<<getReg(1)<<endl;
                        else
                            cout<<getReg(1)<<endl;
                break;
            case '2':   if(optionVal=='1')
                            cout<<"PRN R2 – R2=> "<<getReg(2)<<endl;                        
                        else
                            cout<<getReg(2)<<endl;
                break;
            case '3':   if(optionVal=='1')
                            cout<<"PRN R3 – R3=> "<<getReg(3)<<endl;
                        else
                            cout<<getReg(3)<<endl;
                break;
            case '4':   if(optionVal=='1')
                            cout<<"PRN R4 – R4=> "<<getReg(4)<<endl;
                        else
                            cout<<getReg(4)<<endl;
                break;
            case '5':   if(optionVal=='1')
                            cout<<"PRN R5 – R5=> "<<getReg(5)<<endl;
                        else
                            cout<<getReg(5)<<endl;
                break;
        }
    }
    else{
            prnConst = convertStrToInt(prnx);
            if(optionVal=='1')
                cout<<"PRN "<<prnConst<<" – "<<prnConst <<endl;
            else
                cout<<prnConst<<endl;   
    }
    
    return true;
}
bool CPU::addF(string addStr){
    
    string addx,addy; 
    split(addStr,addx,addy);
    if(controlParameters(addx,addy) == 0)
		return false;
    if(addy==""){
        cerr<<" SYNTAX ERROR!!! "<<endl;
        return false;
    }
    addx=addx.erase(addx.size()-1);
    if(addx[0]=='R')
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
                        
                        else{
                            setReg(1,(getReg(1)+convertStrToInt(addy)));//R1=R1+Constant
                            
                        }
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
                        else
                            setReg(5,(getReg(5)+convertStrToInt(addy)));//R5=R5+Constant
            break; 
        }
        if(optionVal=='1'){
            cout<<"ADD "<<addx<<","<<addy<<" – ";
            print();
            cout<<endl;
        }
	return true; 
}
bool CPU::subF(string subStr){
    
    string subx,suby;
    split(subStr,subx,suby);
    if(controlParameters(subx,suby) == 0)
	return false;
    if(suby==""){
        cerr<<" SYNTAX ERROR!!! "<<endl;
        return false;
    }
    subx=subx.erase(subx.size()-1);
    if(subx[0]=='R')
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
                        
                        else
                            setReg(5,(getReg(5)-convertStrToInt(suby)));//R5=R5-Constant
            break;  
        }
        if(optionVal=='1'){
            cout<<"SUB "<<subx<<","<<suby<<" – ";
            print();
            cout<<endl;
        }
	return true;
}
bool CPU::jmpF(string jmpStr){
    
    string jmpx="",jmpy="";
    split(jmpStr,jmpx,jmpy);
    if(controlParameters(jmpx,jmpy) == 0)
	return false;
    if(jmpx[0]=='R'&&jmpx[1]=='1'&& getReg(1)==0){ //R1==0
        setPC(convertStrToInt(jmpy)-1);
    }
    else if(jmpx[0]=='R'&&jmpx[1]=='2'&& getReg(2)==0){ //R2==0
        setPC(convertStrToInt(jmpy)-1);
        
    }
    else if(jmpx[0]=='R'&&jmpx[1]=='3'&& getReg(3)==0){ //R3==0
        setPC(convertStrToInt(jmpy)-1);
        
    }
    else if(jmpx[0]=='R'&&jmpx[1]=='4'&& getReg(4)==0){ //R4==0
        setPC(convertStrToInt(jmpy)-1);
        
    }
    else if(jmpx[0]=='R'&&jmpx[1]=='5'&& getReg(5)==0){ //R5==0
        setPC(convertStrToInt(jmpy)-1);
        
    }
    else if(jmpx[0]!='R'&&(jmpx[0]>='0'&&jmpx[0]<='9')){ // Constant ise
        setPC(convertStrToInt(jmpx)-1);    
    }
    
    if(optionVal=='1'){
        cout<<"JMP "<<jmpx<<jmpy<<" – ";
        print();
        cout<<endl;
    }
    return true;
}
void CPU::hltF(){
    setHlted(true);
    
    if(optionVal=='1'){
        cout<<endl<<"HLT "<<" – ";
        print();
        cout<<endl;
    }
    else {
        cout<<endl;
        print();
        cout<<endl;      
    }
    
}