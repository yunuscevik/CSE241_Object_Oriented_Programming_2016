#include "CPUProgramDyn.h"
#include "CPU.h"
namespace cpuProDyn{ 
    // default constructor
    CPUProgramDyn::CPUProgramDyn(): capacity(50), usedSection(0){
        str = new string[capacity];
        
    } 
    // option parametesi alan constructor
    CPUProgramDyn::CPUProgramDyn(int opt): capacity(50), usedSection(0){
        setOptionVal(opt);
        str = new string[capacity]; 
    } 
    // copy constructor
    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& pfaObject)
    : capacity(pfaObject.getCapacity()), usedSection(pfaObject.size()) {
        str = new string[capacity];
        for (int i = 0; i < usedSection; i++)
            str[i] = pfaObject.str[i];
    }
    void CPUProgramDyn::ReadFile(const char* fileName){
        fstream file;
        file.open(fileName); // dosya acma
        if(!file){
            cerr << " UNABLE TO OPEN FILE!!! ";
            exit(1);
        }
        string *str1;
        str1 = new string[getCapacity()];
        int i=0;
        while(getline(file,str1[i])){
            
            setSize(size()+1); // satir sayisini hesaplama
            i++;
            if(full()){
                setCapacity(getCapacity()*2);
                string* newData = new string[getCapacity()];
                for (int i = 0; i < size(); i++){
                    newData[i] = str1[i];
                }
                delete[] str1;
                str1 = newData;   
            }    
        }
        // kucuk harfleri buyuk harfe cevirme
        for(int i=0;i<size();i++){
            for(int j=0;j<str1[i].length();j++){
                if(str1[i][j]>='a' && str1[i][j]<='z')
                str1[i][j] += 'A'-'a';
            } 
        }
        for(int i=0;i<size();i++){
            // satir alip " instruction parametre, parametre " formatini veriyor
            parse(str1[i]);
        }
        string *str2;
        str2 = new string[getCapacity()];
        bool q = true; //flag 
        int row=0,col=0;// arraydeki satir, sutun
        while(q){ /* str1 deki verilerin bosluk, ';' ve yorum satirlari olmadan 
                  * str2 ye aktarilmasi*/
            if(str1[row][col] != ' ' && str1[row][col] !='\0' 
                &&str1[row][col] != '\t' && str1[row][col] != ';'){
                str2[row] += str1[row][col];
                col++; 
            }
            else if(str1[row][col] == ';'||str1[row][col] == '\0'){
                row++;
                col=0;   
            }
            else
                col++;

            if(row==size())
                q = false;
        }
        
        for(int i=0;i<size()-1;i++){
            string cntrlTemp1="",cntrlTemp2=""; 
            split(str2[i],cntrlTemp1,cntrlTemp2); // instructionlar daki parametreleri ayirir.
            if(controlParameters(cntrlTemp1,cntrlTemp2) == 0 && q==true )
                q=false;
        }
        delete [] str;
        str=new string [getCapacity()];
        setLine(str2);
        file.close();
        return ; 
    }
    void CPUProgramDyn::clear(string& param){
        int i = param.find_first_not_of(' ');
        param.erase(0,i);  
        i = param.find_last_not_of(' ');
        param.erase(i+1,param.size());
    }
    bool CPUProgramDyn::parse(string& param){
        int index;
        string d1 = "";
        string d2 = "";
        string d3 = "";
        index = param.find_first_of(';');
        if(index != -1)
            param.erase(index,param.size());
        clear(param);
        index = param.find_first_of(' ');
        d1 = param.substr(0,index); // degisken 1, instructionlari degiskene alma
        param.erase(0,index);
        clear(param); 
        if(d1 != "MOV" && d1 != "PRN" && d1 != "ADD" && d1 != "SUB" && d1 != "JMP"
              && d1 != "JPN"  && d1 != "HLT")
            return false; 
        index = param.find_first_of(',');
        if(index != -1){
            index = param.find_first_of(' ');
            d2 = param.substr(0,index); // degisken 2, instructionlarin 1. parametesi
            param.erase(0,index);
            clear(param);
            d3 = param; // degisken 3, instructionlarin 2.parametresi
            clear(d3);
            param = d1 + " "+d2+" "+d3;
            if(d1=="HLT")
                return true; 
            else if(d1!="HLT")
                controlParameters(d2,d3);
            return true;
        }
        else{

            d2 = param; // degisken 2, instructionlarin 1. parametesi
            clear(d2);
        }
        param = d1 + " " + d2;
        if(d1=="HLT")
            return true;
        else if(d1!="HLT")
           controlParameters(d2,"");
        return true;
    }
    int CPUProgramDyn::split(string spStr,string& temp,string& temp1){
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

            cerr<<" 0SYNTAX ERROR!!! "<<endl;
            exit(1);
        }
        return 1;
    }
    int CPUProgramDyn::controlParameters(string controlxStr,string controlyStr ){
        // Hatalar, dosyada her hangi bir yazim hatasi varsa programi calistirmaz
        int lenx = controlxStr.length();
        int leny = controlyStr.length();
        int i=0,j=0;

        if(controlxStr[0]!='R'&&controlxStr[0]!='#'
                &&(!(controlxStr[0]>='0' && controlxStr[0]<='9'))){
            cerr<< " SYNTAX ERROR!!! "<<endl;
            exit(1);
        }

        // Tek parametrelilerde R1 - R5 arasinda degilse (R1a  R4#)
        if( controlxStr[i]=='R'&&(controlxStr[i+1]>='0' && controlxStr[i+1]<='9') 
                &&lenx>2 && controlxStr[i+2]!=',' ){
            cerr<< " SYNTAX ERROR!!! "<<endl;
            exit(1);       
        }
        // Cift parametreliler icin R1,- R5, arasinda degil ise  (Ra, R#,)  
        if(controlxStr[i]=='R'&& controlxStr[lenx-1]==','){
            i++;
            if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){ 
               cerr<< " SYNTAX ERROR!!! "<<endl;
               exit(1);
            }
        }
        // Cift parametreliler icin 1.parametre adres degilse #20s, #s10, 
        else if(controlxStr[i]=='#'&& controlxStr[lenx-1]==','){
            for(int i=1;i<lenx-1;i++){
                if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){ 
                   cerr<< " SYNTAX ERROR!!! "<<endl;
                   exit(1);
                }
            }
        }
        // Cift parametreliler icin   ,R1  ,10  iki parametreden 1. yok 2. var ise 
        else if(controlxStr[i]==','){
               cerr<< " SYNTAX ERROR!!! "<<endl;
               exit(1);
        }
        // Tek parametreliler icin R1 - R5  arasinda degil ise  (Ra  R# ) 
        else if(controlxStr[i]=='R' &&controlxStr[lenx-1]!=',' ){
            i++;
            if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                   cerr<< " SYNTAX ERROR!!! "<<endl;
                   exit(1);
                }  
            }
        // Cift parametrelilerde 1. parametre sayi degilse (1a1,  11#, 222, )
        else if(controlxStr[lenx-1]==',' 
                && (controlxStr[i]>='0' && controlxStr[i]<='9')){

            for(int i=0;i<lenx;i++){
                if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                   cerr<<" SYNTAX ERROR!!! "<<endl;
                   exit(1);
                }   
            } 
        }
        // Tek parametrelilerde 1. parametre sayi degilse  (1a1 11#)
        else if(controlxStr[lenx-1]!=',' && (controlxStr[i]>='0' 
                && controlxStr[i]<='9')){

            for(int i=0;i<lenx;i++){
                if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                    cerr<< " SYNTAX ERROR!!! "<<endl;
                    exit(1);
                }  
            }
        }
        // Tek parametrelilerde adres degilse #2a
        else if(controlxStr[i]=='#'&& controlxStr[lenx-1]!=','){
            for(int i=1;i<lenx;i++){
                if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){ 
                   cerr<< " SYNTAX ERROR!!! "<<endl;
                   exit(1);
                }
            }
        }

        else if(controlxStr[i]>='0' && controlxStr[i]<='9'){

            for(int i=0;i<lenx ;i++){
                if(!(controlxStr[i]>='0' && controlxStr[i]<='9')){
                    cerr<< " SYNTAX ERROR!!! "<<endl;
                    exit(1);
                }     
            }
        }
        //---------------------------
        // Cift parametrelilerde Null, Regester veya sayi degilse 
        if(controlyStr[j]!='R'&&(!(controlyStr[j]>='0' && controlyStr[j]<='9'))&&controlyStr !="" &&controlyStr[j] !='#'){         
                cerr<< " SYNTAX ERROR!!! "<<endl; 
                exit(1);
            }
        // Cift parametrelilerde 2. parametre adres degilse
        else if(controlyStr[j]=='#'){
            for(int i=1;i<leny;i++){
                if(!(controlyStr[i]>='0' && controlyStr[i]<='9')){ 
                   cerr<< " SYNTAX ERROR!!! "<<endl;
                   exit(1);
                }
            }
        }
        // Cift parametrelilerde 2. parametre R1 - R5 arasinda degilse (Rr Ra R#)
        if(leny==2 && controlyStr[j]=='R'){
            j++;
            if(!(controlyStr[j]>='0' && controlyStr[j]<='9')){
                cerr<< " SYNTAX ERROR!!! "<<endl; 
                exit(1);
            }
        }

        // Cift parametrelilerde sayi degilse 
        else if(leny==2 && controlyStr[j]!='R'){
            j++;
            if(!(controlyStr[j]>='0' && controlyStr[j]<='9')){            
                cerr<< " SYNTAX ERROR!!! "<<endl; 
                exit(1);
            }
        }
        // Cift parametrelilerde 2. parametre regester degilse (R1a R2#)
        else if(leny>2 && controlyStr[j]=='R'&&(controlyStr[j+1]>='0' 
                && controlyStr[j+1]<='9')){          
            cerr<< " SYNTAX ERROR!!! "<<endl; 
            exit(1);
        }
        // Cift parametrelilerde 2. parametre sayi degilse (1a1 1## )
        else if(controlyStr[j]>='0' && controlyStr[j]<='9'){

            for(int i=0;i<leny;i++){
                if(!(controlyStr[i]>='0' && controlyStr[i]<='9')){
                    cerr<< " SYNTAX ERROR!!! "<<endl;
                    exit(1);
                }
            } 
        }

        return 1;
    }
    void CPUProgramDyn::setLine(string* s){
        str=s;
    }
    const string CPUProgramDyn::getLine(int size){
        return str[size];
    }
    void CPUProgramDyn::setOptionVal(int opt) {
        optionVal=opt;
    }
    void CPUProgramDyn::setSize(int s){
        usedSection=s;
    }
    void CPUProgramDyn::setCapacity(int cap){
        capacity=cap;
    }
    /* " = " operatoru iki arrayin kapasitesine bakip büyük olan array in 
     * kapasitesi kadar yer olusturur ve iki pointer arrayi birbirine 
     * kopyalamaya yarar*/
    CPUProgramDyn& CPUProgramDyn::operator =(const CPUProgramDyn& rightSide) {
        if (getCapacity() != rightSide.getCapacity()) {
            delete [] str;
            str = new string[rightSide.getCapacity()];
        }
        
        capacity = rightSide.getCapacity();
        usedSection = rightSide.size();
        for (int i = 0; i < size(); i++)
            str[i] = rightSide.str[i];

        return *this;
    }
    // "<<" operatoru programi yazdirir.
    ostream& operator<<(ostream& os, const CPUProgramDyn& cpuP) {
        for(int i=0;i<cpuP.size();i++){
            os<< cpuP[i]<<endl;
        }
        return os;
    }
    /* "()" operatoru  iki tam sayi degeri alir ve bu degerler arasini iceren  
     * yeni bir program dondurur.*/
    const CPUProgramDyn CPUProgramDyn::operator()(int begin,int end){

        CPUProgramDyn temp;
        for(int j=0;begin<=end;begin++,j++){
            temp.str[j]=str[begin];
            temp.setSize(temp.size()+1);
        }
        return temp;

    }
    /* "+" operatoru string ifadesini alir ve gecici arrayin sonuna ekler orjinal 
     * array ayni kalir*/
    const CPUProgramDyn CPUProgramDyn::operator+(string s)const{
        if(s==""){
            cerr<<" BLANK LINE INSERTION ERROR!!! "<<endl;
            return *this;
        }
        CPUProgramDyn temp;
        if (temp.getCapacity() < getCapacity()) {
            delete [] temp.str;
            temp.str = new string[getCapacity()];
            temp.setCapacity(getCapacity());
        }
        else{
            delete [] temp.str;
            temp.str = new string[getCapacity()+1];
            temp.setCapacity(getCapacity()+1);
        }
        for(int i=0;i<size();i++){
            temp.str[i]=str[i];
            temp.setSize(temp.size()+1);
        }
        temp.str[temp.size()]=s;
        temp.setSize(temp.size()+1);
        return temp;
        
    }
    /* "+" operatoru iki program alir ve 2.programi 1.programin devamina ekler*/
    const CPUProgramDyn CPUProgramDyn::operator+(const CPUProgramDyn& o2){
        CPUProgramDyn temp;
        int sumCapacity= o2.getCapacity() + getCapacity();
        int sumSize= size()+ o2.size();
        if (temp.getCapacity() != sumCapacity) {
            delete [] temp.str;
            temp.str = new string[sumCapacity];
        }
        temp.setCapacity(sumCapacity);
        temp.setSize(sumSize);
        for(int i=0;i<size();i++){
            temp.str[i]=str[i];
        }
        for(int i=size(),j=0;i<temp.size();i++,j++){
            temp.str[i] = o2.str[j];
        }
        temp.setSize(temp.size()+1);
        return temp;
    }
    /* "+=" operatoru string ifadesini alir ve programin devamina ekler*/
    const CPUProgramDyn CPUProgramDyn::operator+=(string s){
        if(s==""){
            cerr<<" BLANK LINE INSERTION ERROR!!! "<<endl;
            return *this;
        }
        if(size()==getCapacity())
        {
            capacity=getCapacity()+1;
        }
        str[size()]=s;
        setSize(size()+1);
        return *this;
    }
    /* "--" operatoru programin sonundan bir satir siler */
    CPUProgramDyn CPUProgramDyn::operator--(){
        str[size()]="";
        return *this;
    }
    /* "--" operatoru programin sonundan bir satir siler */
    CPUProgramDyn CPUProgramDyn::operator--(int ignoreMe){
        CPUProgramDyn temp;
        for(int i=0;i<size();i++){
            temp.str[i]=str[i];
        }
        str[size()]="";
        return temp;
    }
    /* "[]" operatoru getLine gibi calisir ve girilen index degerini programda 
     * donderir */
    string CPUProgramDyn::operator[](int index)const{
        if(index>size()-1 || index<0){
            cerr<<" OVERLOAD INDEX!!! "<<endl;
            return "";
        }
        return str[index];
    }
    /* "==" operatoru programlarin esitligini kontrol eder*/
    bool CPUProgramDyn::operator==(const CPUProgramDyn& cpuP2)const{
        return (size()==cpuP2.size());
    }
    /* "!=" operatoru programlarin esit olmadiklarini kontrol eder */
    bool CPUProgramDyn::operator!=(const CPUProgramDyn& cpuP2)const{
        return (size()!= cpuP2.size());
    }
    /* "<" operatoru 1.programin 2. programdan kucuk olup olmadigini test eder */
    bool CPUProgramDyn::operator<(const CPUProgramDyn& cpuP2)const{
        return (size() < cpuP2.size());
    }
    /* ">" operatoru 1.programin 2. programdan kucuk olup olmadigini test eder */
    bool CPUProgramDyn::operator>(const CPUProgramDyn& cpuP2)const{
        return (size() > cpuP2.size());
    }
    /* ">=" operatoru 1.programin 2. programdan kucuk yada esit olup olmadigini 
     * test eder */
    bool CPUProgramDyn::operator>=(const CPUProgramDyn& cpuP2)const{
        return (size() >= cpuP2.size());
    }
    /* "<=" operatoru 1.programin 2. programdan kucuk yada esit olup olmadigini 
     * test eder */
    bool CPUProgramDyn::operator<=(const CPUProgramDyn& cpuP2)const{
        return (size() <= cpuP2.size());
    }
    CPUProgramDyn::~CPUProgramDyn() {
        delete [] str ;
    }//Destructor
}


