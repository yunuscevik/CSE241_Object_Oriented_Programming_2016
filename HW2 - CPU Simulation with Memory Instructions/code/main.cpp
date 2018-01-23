/* 
 * File:   main.cpp
 * Author: HW2_141044080_Yunus_CEVIK
 *
 * Created on 11 Ekim 2016 Sali, 18:32
 */

/*      #DEFINE      */
#define SIZE 256
#define REG_NUM 5
#define INSTRUCTION_SIZE 3
#define MEMORY_SIZE 50
/*      #INCLUDE     */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*   Function Prototypes     */
int instructionControl (string insStr[],int* cntr,int x[],int y[], char** argv);
int split(string spStr,string& temp,string& temp1);
int controlParameters(string controlxStr,string controlyStr );
int convertStrToInt(string str);
bool movF(string movStr,int movReg[],int movMmry[],char** argv);
bool prnF(string prnStr,int prnReg[],int prnMmry[],char** argv);
bool addF(string addStr,int addReg[],int addMmry[],char** argv);
bool subF(string subStr,int subReg[],int subMmry[],char** argv);
bool jmpF(string jmpStr,int jmpReg[],int jmpMmry[],int *a,char** argv);
bool jpnF(string jpnStr,int jpnReg[],int jpnMmry[],int *a,char** argv);
/* 
 *  Bu program *.txt dosyasi icindeki instructionlarla 5 regester uzerinde 
 * islemler yapmamizi saglar. Bu instructionlar: MOV,ADD,SUB,JMP,PRN,HLT .
 * Programin yardimci fonksiyonlari instructionControl: Satir satir okunan 
 * verilerin hangi instructiona ait oldugunu belirler ve o instruction 
 * fonksiyonunu cagirir. split: Okunan satirin  instruction,regester ve 
 * constant number oldugunu belirleyip iki ayri stringe cevirir ve geri donderir
 * controlParameters: Iki ayri parametreye ayrilan stringleri yazim kurallarina 
 * uygun olup olmadigini kontrol eder.
 * convertStrToInt: Bir string ifadeyi integer ifadeye cevirmeye yarayan 
 * yardimci fonksiyondur.
 * 
 */
int main(int argc, char** argv) {
    
    fstream file; 
    if(argc != 3){
        cerr<<"INVALID ARGUMAN!!!"<<endl;
        return 0;
    }
    file.open(argv[1]); //dosya acma.
    
    if(!file)
    {
        cerr << " UNABLE TO OPEN FILE!!! ";
        return 0;
    }
    int count = 0;
    string str1[SIZE],str2[SIZE]; //str1= dosyadan bu diziye aktarilir
    //str2= alinan verilerin bosluk, ';' ve yorum satirlari olmadan aktarilir 
    
    int reg[REG_NUM]; //regesters
    for(int i=0;i<REG_NUM;i++){
        reg[i]=0;
    }
    int mmry[MEMORY_SIZE];
    for(int i=0;i<MEMORY_SIZE;i++){
        mmry[i]=0;
    }
    
    for(int i=0;i<SIZE;i++){
        if(getline(file,str1[i])) //dosyadaki satirlari tek tek str ye aktarma
        count++; // dosyada kac satir oldugu
    }
    bool q = true;
    int row=0,col=0;
    int j=0;
    
    // kucuk harfleri buyuk harfe cevirme
    for(int i=0;i<count;i++){
        for(int j=0;j<str1[i].length();j++){
            if(str1[i][j]>='a' && str1[i][j]<='z')
            str1[i][j] += 'A'-'a';
        } 
    }
        
    while(q) /* str1 deki verilerin bosluk, ';' ve yorum satirlari olmadan 
              * str2 ye aktarilmasi*/
    {
        if(str1[row][col] != ' ' && str1[row][col] !='\0' 
            &&str1[row][col] != '\t' && str1[row][col] != ';'){
            str2[row] += str1[row][col];
            col++;
            j++;
        }
        else if(str1[row][col] == ';'||str1[row][col+1] == '\0'){
            row++;
            col=0;   
        }
        else
            col++;
        
        if(row==count)
            q = false;
    }
    
    instructionControl(str2,&count,reg,mmry,argv); 
    return 0;
}
int instructionControl (string insStr[],int *cntr,int x[],int y[],char** argv){
    string temp;
    int counter=0;
    // kucuk harfleri buyuk harfe cevirme
    for(int i=0;i<*cntr;i++){
        for(int j=0;j<insStr[i].length();j++){
            if(insStr[i][j]>='a' && insStr[i][j]<='z')
            insStr[i][j] += 'A'-'a';
        } 
    }
    // instructionlari bularak fonksiyonlarini cagirma
    for(int i=0;i<*cntr;i++){
        for(int j=0;j<3;j++){
            temp += insStr[i][j];
        }
        if(temp=="MOV"){
            if(movF(insStr[i],x,y,argv) == false)
                return 0;
        }
        else if(temp=="PRN"){
            if(prnF(insStr[i],x,y,argv) == false)
                return 0;
        }
        else if(temp=="SUB"){
            if(subF(insStr[i],x,y,argv) == false)
                return 0;
            }
        else if(temp=="HLT"){
            if(argv[2][0]=='1'){
                cout<<"HLT "<<" –  R1="<<x[0]
                <<", R2="<<x[1]<<", R3="<<x[2]<<", R4="
                <<x[3]<<", R5="<<x[4]<<endl;
                return 0;
            }
            else if(argv[2][0]=='2'){
                cout<<"HLT "<<" –  R1="<<x[0]
                <<", R2="<<x[1]<<", R3="<<x[2]<<", R4="
                <<x[3]<<", R5="<<x[4]<<endl;
                for(int i=0;i<MEMORY_SIZE;i++){
                    cout<<"#"<<i<<"=> "<<y[i]<<"\t";
                    counter++;
                    if(counter==10){
                        cout<<endl;
                        counter=0;
                    }
                }
            }
            else {
                cout<<"R1="<<x[0]
                <<", R2="<<x[1]<<", R3="<<x[2]<<", R4="
                <<x[3]<<", R5="<<x[4]<<endl;
                for(int i=0;i<MEMORY_SIZE;i++){
                    cout<<"#"<<i<<"=> "<<y[i]<<"\t";
                    counter++;
                    if(counter==10){
                        cout<<endl;
                        counter=0;
                    }
                }
            }
        }
        else if(temp=="ADD"){
            if(addF(insStr[i],x,y,argv) == false)
                return 0;    
        }
        else if(temp=="JMP"){
            if(jmpF(insStr[i],x,y,&i,argv) == false)
               return 0;
        }
        else if(temp=="JPN"){
            if(jpnF(insStr[i],x,y,&i,argv) == false)
               return 0;
        }
        else{
            cerr<< " SYNTAX ERROR!!! "<<endl;
            return 0;
        }
        temp = "";  // degisken arrayi sifirlama 
    }
    return 1;
}
int split(string spStr,string& temp,string& temp1){
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
int controlParameters(string controlxStr,string controlyStr ){
    // Hatalar
    int lenx = controlxStr.length();
    int leny = controlyStr.length();
    int i=0,j=0;
    
    if(controlxStr[0]!='R'&&controlxStr[0]!='#'
            &&(!(controlxStr[0]>='0' && controlxStr[0]<='9'))){
        
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
    // Cift parametreliler icin 1.parametre adres degilse #20s, #s10, 
    else if(controlxStr[i]=='#'&& controlxStr[lenx-1]==','){
        for(int i=1;i<lenx-1;i++){
            if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){ 
               cerr<< " SYNTAX ERROR!!! "<<endl;
               return 0;
            }
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
    // Tek parametrelilerde adres degilse #2a
    else if(controlxStr[i]=='#'&& controlxStr[lenx-1]!=','){
        for(int i=1;i<lenx;i++){
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
    if(controlyStr[j]!='R'&&(!(controlyStr[j]>='0' && controlyStr[j]<='9'))&&controlyStr !="" &&controlyStr[j] !='#'){         
            cerr<< " SYNTAX ERROR!!! "<<endl; 
            return 0;
        }
    // Cift parametrelilerde 2. parametre adres degilse
    else if(controlyStr[j]=='#'){
        for(int i=1;i<leny;i++){
            if(!(controlyStr[i]>='0' && controlyStr[i]<='9')){ 
               cerr<< " SYNTAX ERROR!!! "<<endl;
               return 0;
            }
        }
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
int convertStrToInt(string str){
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
bool movF(string movStr,int movReg[],int movMmry[], char** argv){
    string movx="",movy=""; 
    int adress=0;
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
                                case '1': movReg[0] = movReg[0]; // R1=R1
                                    break;
                                case '2': movReg[1] = movReg[0]; // R2=R1
                                    break;
                                case '3': movReg[2] = movReg[0]; // R3=R1
                                    break;
                                case '4': movReg[3] = movReg[0]; // R4=R1
                                    break;
                                case '5': movReg[4] = movReg[0]; // R5=R1
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){ // adres 
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            movMmry[adress]=movReg[0];
                        }
                        else{
                            movReg[0]= convertStrToInt(movy); // R1=Constant
                          
                        }
            break;
            
            case '2':   if(movy[0]=='R'){
                            switch(movy[1]){
                                case '1': movReg[0]=movReg[1];// R1=R2
                                    break;
                                case '2': movReg[1]=movReg[1];// R2=R2
                                    break;
                                case '3': movReg[2]=movReg[1];// R3=R2
                                    break;
                                case '4': movReg[3]=movReg[1];// R4=R2
                                    break;
                                case '5': movReg[4]=movReg[1];// R5=R2
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            movMmry[adress]=movReg[1];
                        }
                        else{
                            movReg[1]=convertStrToInt(movy);  // R2=Constant
                        }
            break;
            case '3':   if(movy[0]=='R'){
                            switch(movy[1]){
                                case '1': movReg[0]=movReg[2];// R1=R3
                                    break;
                                case '2': movReg[1]=movReg[2];// R2=R3
                                    break;
                                case '3': movReg[2]=movReg[2];// R3=R3
                                    break;
                                case '4': movReg[3]=movReg[2];// R4=R3
                                    break;
                                case '5': movReg[4]=movReg[2];// R5=R3
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            movMmry[adress]=movReg[2];
                        }
                        else{
                            movReg[2]=convertStrToInt(movy);   // R3=Constant
                        }
            break;
            case '4': if(movy[0]=='R'){
                            switch(movy[1]){
                                case '1': movReg[0]=movReg[3];// R1=R4
                                    break;
                                case '2': movReg[1]=movReg[3];// R2=R4
                                    break;
                                case '3': movReg[2]=movReg[3];// R3=R4
                                    break;
                                case '4': movReg[3]=movReg[3];// R4=R4
                                    break;
                                case '5': movReg[4]=movReg[3];// R5=R4
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            movMmry[adress]=movReg[3];
                        }
                        else{
                            movReg[3]=convertStrToInt(movy);  // R4=Constant// R1=R5
                        }
            break;
            case '5':   if(movy[0]=='R'){
                            switch(movy[1]){
                                case '1': movReg[0]=movReg[4];// R1=R5
                                    break;
                                case '2': movReg[1]=movReg[4];// R2=R5
                                    break;
                                case '3': movReg[2]=movReg[4];// R3=R5
                                    break;
                                case '4': movReg[3]=movReg[4];// R4=R5
                                    break;
                                case '5': movReg[4]=movReg[4];// R5=R5
                                    break;
                            }
                        }
                        else if(movy[0]=='#'){
                            movy=movy.erase(0,1);
                            adress=convertStrToInt(movy);
                            movMmry[adress]=movReg[4];
                        }
                        else{
                            movReg[4]=convertStrToInt(movy); // R5=Constant
                        }
            break;
        }
    }
    else if(movx[0]=='#'){
        movx=movx.erase(0,1);
        adress=convertStrToInt(movx);
        if(movy[0]=='R'){
            switch(movy[1]){
                case '1': movReg[0]= movMmry[adress];// R1=adress
                    break;
                case '2': movReg[1]= movMmry[adress];// R2=adress
                    break;
                case '3': movReg[2]= movMmry[adress];// R3=adress
                    break;
                case '4': movReg[3]= movMmry[adress];// R4=adress
                    break;
                case '5': movReg[4]= movMmry[adress];// R5=adress
                    break;
            }
        }
        else{
            movMmry[adress]= convertStrToInt(movy); // #.. = Constant
        }
    }
    int counter=0;   
    if(argv[2][0]=='1')
         cout<<"MOV "<<movx<<","<<movy<<" –  R1="<<movReg[0]<<", R2="<<movReg[1]
            <<", R3="<<movReg[2]<<", R4="<<movReg[3]<<", R5="<<movReg[4]<<endl;
    else if(argv[2][0]=='2'){
        cout<<"MOV "<<movx<<","<<movy<<" –  R1="<<movReg[0]<<", R2="<<movReg[1]
            <<", R3="<<movReg[2]<<", R4="<<movReg[3]<<", R5="<<movReg[4]<<endl;
        for(int i=0;i<MEMORY_SIZE;i++){
            cout<<"#"<<i<<"=> "<<movMmry[i]<<"\t";
            counter++;
            if(counter==10){
            cout<<endl;
            counter=0;
            }
        }
    }
    return true;
}
bool prnF(string prnStr,int prnReg[],int prnMmry[], char** argv){
    // ekrana cikti veren fonksiyon
    string prnx,prny="";
    int prnConst=0,adress=0,counter=0;
    split(prnStr,prnx,prny);
    if(controlParameters(prnx,prny) == 0)
	return false;
    if(prnx[0]=='R'){
        switch(prnx[1]){
            case '1':   if(argv[2][0]=='1')
                            cout<<"PRN R1 – R1= "<<prnReg[0]<<endl;
                        else if(argv[2][0]=='2'){
                            cout<<"PRN R1 – R1= "<<prnReg[0]<<endl;
                            for(int i=0;i<MEMORY_SIZE;i++){
                                cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                                counter++;
                                if(counter==10){
                                    cout<<endl;
                                    counter=0;
                                }
                            }
                        }
                        else
                            cout<<prnReg[0]<<endl;
                break;
            case '2':   if(argv[2][0]=='1')
                            cout<<"PRN R2 – R2= "<<prnReg[1]<<endl;
                        else if(argv[2][0]=='2'){
                            cout<<"PRN R2 – R2= "<<prnReg[1]<<endl;
                            for(int i=0;i<MEMORY_SIZE;i++){
                                cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                                counter++;
                                if(counter==10){
                                    cout<<endl;
                                    counter=0;
                                }
                            }
                        }
                        else
                            cout<<prnReg[1]<<endl;
                break;
            case '3':   if(argv[2][0]=='1')
                            cout<<"PRN R3 – R3= "<<prnReg[2]<<endl;
                        else if(argv[2][0]=='2'){
                            cout<<"PRN R3 – R3= "<<prnReg[2]<<endl;
                            for(int i=0;i<MEMORY_SIZE;i++){
                                cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                                counter++;
                                if(counter==10){
                                    cout<<endl;
                                    counter=0;
                                }
                            }
                        }
                        else
                            cout<<prnReg[2]<<endl;
                break;
            case '4':   if(argv[2][0]=='1')
                            cout<<"PRN R4 – R4= "<<prnReg[3]<<endl;
                        else if(argv[2][0]=='2'){
                            cout<<"PRN R4 – R4= "<<prnReg[3]<<endl;
                            for(int i=0;i<MEMORY_SIZE;i++){
                                cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                                counter++;
                                if(counter==10){
                                    cout<<endl;
                                    counter=0;
                                }
                            }
                        }
                        else
                            cout<<prnReg[3]<<endl;
                break;
            case '5':   if(argv[2][0]=='1')
                            cout<<"PRN R5 – R5= "<<prnReg[4]<<endl;
                        else if(argv[2][0]=='2'){
                            cout<<"PRN R5 – R5= "<<prnReg[4]<<endl;
                            for(int i=0;i<MEMORY_SIZE;i++){
                                cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                                counter++;
                                if(counter==10){
                                    cout<<endl;
                                    counter=0;
                                }
                            }
                        }
                        else
                            cout<<prnReg[4]<<endl;
                break;
        }
    }
    else if(prnx[0]=='#'){
        prnx=prnx.erase(0,1);
        adress=convertStrToInt(prnx);
        if(argv[2][0]=='1')
        cout<<"PRN #"<<prnx<<" – "<<prnMmry[adress]<<endl;
        else if(argv[2][0]=='2'){
            cout<<"PRN #"<<prnx<<" – "<<prnMmry[adress]<<endl;
            for(int i=0;i<MEMORY_SIZE;i++){
                cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                counter++;
                if(counter==10){
                    cout<<endl;
                    counter=0;
                }
            }
        }
        else
            cout<<prnMmry[adress]<<endl;
    }
    else{
            prnConst = convertStrToInt(prnx);
            if(argv[2][0]=='1')
                cout<<"PRN "<<prnConst<<" – "<<prnConst <<endl;
            else if(argv[2][0]=='2'){
                 cout<<"PRN "<<prnConst<<" – "<<prnConst <<endl;
                for(int i=0;i<MEMORY_SIZE;i++){
                    cout<<"#"<<i<<"=> "<<prnMmry[i]<<"\t";
                    counter++;
                    if(counter==10){
                        cout<<endl;
                        counter=0;
                    }
                }
            }
            else
                cout<<prnConst<<endl;   
    }
    return true;
}
bool addF(string addStr,int addReg[],int addMmry[], char** argv){
    string addx,addy; 
    int adress=0;
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
                                case '1': addReg[0]+=addReg[0]; //R1=R1+R1
                                    break;
                                case '2': addReg[0]+=addReg[1];//R1=R1+R2
                                    break;
                                case '3': addReg[0]+=addReg[2];//R1=R1+R3
                                    break;
                                case '4': addReg[0]+=addReg[3];//R1=R1+R3
                                    break;
                                case '5': addReg[0]+=addReg[4];//R1=R1+R3
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            addReg[0] += addMmry[adress];
                        }
                        else{
                            addReg[0]+= convertStrToInt(addy);//R1=R1+Constant
                            
                        }
            break;
            case '2':   if(addy[0]=='R'){
                            switch(addy[1]){
                                case '1': addReg[1]+=addReg[0];//R2=R2+R1
                                    break;
                                case '2': addReg[1]+=addReg[1];//R2=R2+R2
                                    break;
                                case '3': addReg[1]+=addReg[2];//R2=R2+R3
                                    break;
                                case '4': addReg[1]+=addReg[3];//R2=R2+R4
                                    break;
                                case '5': addReg[1]+=addReg[4];//R2=R2+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            addReg[1] += addMmry[adress];
                        }
                        else{
                            addReg[1]+=convertStrToInt(addy);  //R2=R2+Constant
                        }
            break;
            case '3':   if(addy[0]=='R'){
                            switch(addy[1]){
                                case '1': addReg[2]+=addReg[0];//R3=R3+R1
                                    break;
                                case '2': addReg[2]+=addReg[1];//R3=R3+R2
                                    break;
                                case '3': addReg[2]+=addReg[2];//R3=R3+R3
                                    break;
                                case '4': addReg[2]+=addReg[3];//R3=R3+R4
                                    break;
                                case '5': addReg[2]+=addReg[4];//R3=R3+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            addReg[2] += addMmry[adress];
                        }
                        else{
                            addReg[2]+=convertStrToInt(addy);//R3=R3+Constant
                        }
            break;
            case '4': if(addy[0]=='R'){
                            switch(addy[1]){
                                case '1': addReg[3]+=addReg[0];//R4=R4+R1
                                    break;
                                case '2': addReg[3]+=addReg[1];//R4=R4+R2
                                    break;
                                case '3': addReg[3]+=addReg[2];//R4=R4+R3
                                    break;
                                case '4': addReg[3]+=addReg[3];//R4=R4+R4
                                    break;
                                case '5': addReg[3]+=addReg[4];//R4=R4+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            addReg[3] += addMmry[adress];
                        }
                        else{
                            addReg[3]+=convertStrToInt(addy);//R4=R4+Constant
                        }
            break;
            case '5':   if(addy[0]=='R'){
                            switch(addy[1]){
                                case '1': addReg[4]+=addReg[0];//R5=R5+R1
                                    break;
                                case '2': addReg[4]+=addReg[1];//R5=R5+R2
                                    break;
                                case '3': addReg[4]+=addReg[2];//R5=R5+R3
                                    break;
                                case '4': addReg[4]+=addReg[3];//R5=R5+R4
                                    break;
                                case '5': addReg[4]+=addReg[4];//R5=R5+R5
                                    break;
                            }
                        }
                        else if(addy[0]=='#'){
                            addy=addy.erase(0,1);
                            adress=convertStrToInt(addy);
                            addReg[4] += addMmry[adress];
                        }
                        else{
                            addReg[4]+=convertStrToInt(addy);//R5=R5+Constant 
                        }
            break; 
        }
    int counter=0;
    if(argv[2][0]=='1')
        cout<<"ADD "<<addx<<","<<addy<<" –  R1="<<addReg[0]<<", R2="<<addReg[1]
            <<", R3="<<addReg[2]<<", R4="<<addReg[3]<<", R5="<<addReg[4]<<endl;
    else if(argv[2][0]=='2'){
        cout<<"ADD "<<addx<<","<<addy<<" –  R1="<<addReg[0]<<", R2="<<addReg[1]
            <<", R3="<<addReg[2]<<", R4="<<addReg[3]<<", R5="<<addReg[4]<<endl;
        for(int i=0;i<MEMORY_SIZE;i++){
            cout<<"#"<<i<<"=> "<<addMmry[i]<<"\t";
            counter++;
            if(counter==10){
            cout<<endl;
            counter=0;
            }
        }
    }
	return true; 
}
bool subF(string subStr,int subReg[],int subMmry[], char** argv){
    string subx,suby;
    int adress=0;
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
                                case '1': subReg[0]-=subReg[0];//R1=R1-R1
                                    break;
                                case '2': subReg[0]-=subReg[1];//R1=R1-R2
                                    break;
                                case '3': subReg[0]-=subReg[2];//R1=R1-R3
                                    break;
                                case '4': subReg[0]-=subReg[3];//R1=R1-R4
                                    break;
                                case '5': subReg[0]-=subReg[4];//R1=R1-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            subReg[0] -= subMmry[adress];
                        }
                        else{
                            subReg[0]-= convertStrToInt(suby);//R1=R1-Constant
                        }
            break;
            case '2':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': subReg[1]-=subReg[0];//R2=R2-R1
                                    break;
                                case '2': subReg[1]-=subReg[1];//R2=R2-R2
                                    break;
                                case '3': subReg[1]-=subReg[2];//R2=R2-R3
                                    break;
                                case '4': subReg[1]-=subReg[3];//R2=R2-R4
                                    break;
                                case '5': subReg[1]-=subReg[4];//R2=R2-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            subReg[1] -= subMmry[adress];
                        }
                        else{
                            subReg[1]-=convertStrToInt(suby); //R2=R2-Constant
                            
                        }
            break;
            case '3':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': subReg[2]-=subReg[0];//R3=R3-R1
                                    break;
                                case '2': subReg[2]-=subReg[1];//R3=R3-R2
                                    break;
                                case '3': subReg[2]-=subReg[2];//R3=R3-R3
                                    break;
                                case '4': subReg[2]-=subReg[3];//R3=R3-R4
                                    break;
                                case '5': subReg[2]-=subReg[4];//R3=R3-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            subReg[2] -= subMmry[adress];
                        }
                        else{
                            subReg[2]-=convertStrToInt(suby);//R3=R3-Constant
                            
                        }
            break;
            case '4': if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': subReg[3]-=subReg[0];//R4=R4-R1
                                    break;
                                case '2': subReg[3]-=subReg[1];//R4=R4-R2
                                    break;
                                case '3': subReg[3]-=subReg[2];//R4=R4-R3
                                    break;
                                case '4': subReg[3]-=subReg[3];//R4=R4-R4
                                    break;
                                case '5': subReg[3]-=subReg[4];//R4=R4-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            subReg[3] -= subMmry[adress];
                        }
                        else{
                            subReg[3]+=convertStrToInt(suby);//R4=R4-Constant
                        }
            break;
            case '5':   if(suby[0]=='R'){
                            switch(suby[1]){
                                case '1': subReg[4]-=subReg[0];//R5=R5-R1
                                    break;
                                case '2': subReg[4]-=subReg[1];//R5=R5-R2
                                    break;
                                case '3': subReg[4]-=subReg[2];//R5=R5-R3
                                    break;
                                case '4': subReg[4]-=subReg[3];//R5=R5-R4
                                    break;
                                case '5': subReg[4]-=subReg[4];//R5=R5-R5
                                    break;
                            }
                        }
                        else if(suby[0]=='#'){
                            suby=suby.erase(0,1);
                            adress=convertStrToInt(suby);
                            subReg[4] -= subMmry[adress];
                        }
                        else{
                            subReg[4]-=convertStrToInt(suby);//R5=R5-Constant   
                        }
            break;  
        }
    int counter=0;
    if(argv[2][0]=='1')
        cout<<"SUB "<<subx<<","<<suby<<" –  R1="<<subReg[0]<<", R2="<<subReg[1]
            <<", R3="<<subReg[2]<<", R4="<<subReg[3]<<", R5="<<subReg[4]<<endl;
    else if(argv[2][0]=='2'){
        cout<<"SUB "<<subx<<","<<suby<<" –  R1="<<subReg[0]<<", R2="<<subReg[1]
            <<", R3="<<subReg[2]<<", R4="<<subReg[3]<<", R5="<<subReg[4]<<endl;
        for(int i=0;i<MEMORY_SIZE;i++){
            cout<<"#"<<i<<"=> "<<subMmry[i]<<"\t";
            counter++;
            if(counter==10){
            cout<<endl;
            counter=0;
            }
        }
    }
	return true;
}
bool jmpF(string jmpStr,int jmpReg[],int jmpMmry[],int *a, char** argv){
    string jmpx="",jmpy="";
    split(jmpStr,jmpx,jmpy);
    if(controlParameters(jmpx,jmpy) == 0)
	return false;
    if(jmpx[0]=='R'&&jmpx[1]=='1'&& jmpReg[0]==0) //R1==0
        *a = convertStrToInt(jmpy)-2;
    
    else if(jmpx[0]=='R'&&jmpx[1]=='2'&& jmpReg[1]==0) //R2==0
        *a= convertStrToInt(jmpy)-2;
    
    else if(jmpx[0]=='R'&&jmpx[1]=='3'&& jmpReg[2]==0) //R3==0
        *a= convertStrToInt(jmpy)-2;
    
    else if(jmpx[0]=='R'&&jmpx[1]=='4'&& jmpReg[3]==0) //R4==0
        *a= convertStrToInt(jmpy)-2;
    
    else if(jmpx[0]=='R'&&jmpx[1]=='5'&& jmpReg[4]==0) //R5==0
        *a= convertStrToInt(jmpy)-2;

    else if(jmpx[0]!='R'&&(jmpx[0]>='0'&&jmpx[0]<='9')) // Constant ise
        *a= convertStrToInt(jmpx)-2;
    else
        *a++;
    int counter=0;
    if(argv[2][0]=='1')
    cout<<"JMP "<<jmpx<<jmpy<<" –  R1="<<jmpReg[0]<<", R2="<<jmpReg[1]
            <<", R3="<<jmpReg[2]<<", R4="<<jmpReg[3]<<", R5="<<jmpReg[4]<<endl;
    else if(argv[2][0]=='2'){
        cout<<"JMP "<<jmpx<<jmpy<<" –  R1="<<jmpReg[0]<<", R2="<<jmpReg[1]
            <<", R3="<<jmpReg[2]<<", R4="<<jmpReg[3]<<", R5="<<jmpReg[4]<<endl;
        for(int i=0;i<MEMORY_SIZE;i++){
            cout<<"#"<<i<<"=> "<<jmpMmry[i]<<"\t";
            counter++;
            if(counter==10){
            cout<<endl;
            counter=0;
            }
        }
    }
    return true;
}
bool jpnF(string jpnStr,int jpnReg[],int jpnMmry[],int *a, char** argv){
    
    string jpnx="",jpny="";
    split(jpnStr,jpnx,jpny);
    if(controlParameters(jpnx,jpny) == 0)
	return false;
    if(jpnx[0]=='R'&&jpnx[1]=='1'&& (jpnReg[0]==0||jpnReg[0]<0)) //R1==0 || R1<0
        *a = convertStrToInt(jpny)-2;
    
    else if(jpnx[0]=='R'&&jpnx[1]=='2'&& (jpnReg[1]==0||jpnReg[1]<0)) //R2==0||R2<0
        *a= convertStrToInt(jpny)-2;
    
    else if(jpnx[0]=='R'&&jpnx[1]=='3'&& (jpnReg[2]==0||jpnReg[2]<0)) //R3==0
        *a= convertStrToInt(jpny)-2;
    
    else if(jpnx[0]=='R'&&jpnx[1]=='4'&& (jpnReg[3]==0||jpnReg[3]<0)) //R4==0
        *a= convertStrToInt(jpny)-2;
    
    else if(jpnx[0]=='R'&&jpnx[1]=='5'&& (jpnReg[4]==0||jpnReg[4]<0)) //R5==0
        *a= convertStrToInt(jpny)-2;

    else
        *a++;
    int counter=0;
    if(argv[2][0]=='1')
    cout<<"JPN "<<jpnx<<jpny<<" –  R1="<<jpnReg[0]<<", R2="<<jpnReg[1]
            <<", R3="<<jpnReg[2]<<", R4="<<jpnReg[3]<<", R5="<<jpnReg[4]<<endl;
    else if(argv[2][0]=='2'){
        cout<<"JPN "<<jpnx<<jpny<<" –  R1="<<jpnReg[0]<<", R2="<<jpnReg[1]
            <<", R3="<<jpnReg[2]<<", R4="<<jpnReg[3]<<", R5="<<jpnReg[4]<<endl;
        for(int i=0;i<MEMORY_SIZE;i++){
            cout<<"#"<<i<<"=> "<<jpnMmry[i]<<"\t";
            counter++;
            if(counter==10){
            cout<<endl;
            counter=0;
            }
        }
    }
    return true;
}