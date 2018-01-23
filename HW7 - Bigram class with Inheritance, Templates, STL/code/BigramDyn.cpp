#include "BigramDyn.h"
#include "Exception.h"
#include <map>
// default constructor
template <class T>
BigramDyn<T>::BigramDyn(): capacity(50), usedSection(0){
    arr = new T[capacity];

} 
// option parametesi alan constructor
template <class T>
BigramDyn<T>::BigramDyn(int opt): capacity(50), usedSection(0){
    setOptionVal(opt);
    arr = new T[capacity]; 
} 
// copy constructor
template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn& Object)
: capacity(Object.getCapacity()), usedSection(Object.size()) {
    arr = new T[capacity];
    for (int i = 0; i < usedSection; i++)
        arr[i] = Object.arr[i];
}
template <class T>
void BigramDyn<T>::setOptionVal(int opt) {
    optionVal=opt;
}
template <class T>
void BigramDyn<T>::setSize(int s){
    usedSection=s;
}
template <class T>
void BigramDyn<T>::setCapacity(int cap){
    capacity=cap;
}
/* " = " operatoru iki arrayin kapasitesine bakip büyük olan array in 
     * kapasitesi kadar yer olusturur ve iki pointer arrayi birbirine 
     * kopyalamaya yarar*/
template <class T>
BigramDyn<T>& BigramDyn<T>::operator =(const BigramDyn& rightSide) {
    if (getCapacity() != rightSide.getCapacity()) {
        delete [] arr;
        arr = new T[rightSide.getCapacity()];
    }
    capacity = rightSide.getCapacity();
    usedSection = rightSide.size();
    for (int i = 0; i < size(); i++)
        arr[i] = rightSide.arr[i];

    return *this;
}
/* "[]" operatoru getLine gibi calisir ve girilen index degerini programda 
* donderir */
template <class T>
T BigramDyn<T>::operator[](int index)const{
   if(index>size()-1 || index<0){
       cerr<<" OVERLOAD INDEX!!! "<<endl;
       throw Exception(" OVERLOAD INDEX!!! ");
   }
   return arr[index];
}

template <class T>
void BigramDyn<T>::readFile(const char* fileName){
    fstream file;
    file.open(fileName); // dosya acma
    if (!file) {
        //cerr << " UNABLE TO OPEN FILE!!! ";
        throw Exception(" UNABLE TO OPEN FILE!!! ");
    }
    T val;
    int index = 0;
    while (!file.eof() ) {
        file >> val;
        if(!(file)){
            throw Exception(" Corrupted file!!! ");
        }
        arr[index] =val;
        ++index;
        setSize(size()+1);
        
    }
    
    file.close();
}
template <class T>
int BigramDyn<T>:: numGrams(){
    return size()-1;
}
template <class T>
int BigramDyn<T>::numOfGrams(T n1,T n2){
    int val1=0,val2=1,count=0;
    while(val2<size()){
        if(pair<T,T>(arr[val1],arr[val2])==pair<T,T>(n1,n2))
            ++count;
        ++val1;
        ++val2;
    }
    return count;
}
template <class T>
pair<T,T> BigramDyn<T>:: maxGrams(){
    pair<T, T> sayi;
    int frequency = 0;
    for (int i = 0; i < size()-1; ++i) {
        int counter = 0;
        for (int k = 0; k < size()-1; ++k) {
            if (pair<T, T>(arr[k], arr[k+1]) == pair<T, T>(arr[i], arr[i+1])) {
                ++counter;
            }
            
        }
        if (counter > frequency) {
            frequency = counter;
            sayi = pair<T, T>(arr[i], arr[i+1]);
            
        }
    }
    cout << "Frequency=> " << frequency << " MAXGRAM=> ";
    return sayi;
}
template <class T>
void BigramDyn<T>:: prints() const{
//    bool flag=true,flag1=true,flag2=true,flag3=true;
//    pair<T, T> sayi;
//    T tempArr [size()*2];
//    int countArr[size()];
//    int t = 0,j=0;
//    int frequency = 0;
//       for (int i = 0; i < size()-1;++i) {
//        int counter = 0;
//        for (int k = 0; k < size()-1; ++k) {
//            if (pair<T, T>(arr[k], arr[k+1]) == pair<T, T>(arr[i], arr[i+1])) {
//                ++counter;
//            }
//            
//        }
//        
//        if (counter > frequency && flag1==true) {
//            frequency = counter;
//            sayi = pair<T, T>(arr[i], arr[i+1]);
//            flag1=false;
//            flag2=true;
//            flag=true;
//            flag3=true;
//                   
//        }
//        else if (counter < frequency && flag2==true) {
//            frequency = counter;
//            sayi = pair<T, T>(arr[i], arr[i+1]);
//            flag2=false;
//            flag1=true;
//            flag=true;
//            flag3=true;
//        }
//        else if (counter == frequency && flag3==true) {
//            frequency = counter;
//            sayi = pair<T, T>(arr[i], arr[i+1]);
//            flag3=false;
//            flag1=true;
//            flag=true;
//            flag2=true;
//        }
//        
//        if(flag==true){
//            
//            countArr[i]=frequency;
//            tempArr[j]=sayi.first;
//            tempArr[j+1]=sayi.second;
//            flag=false;
//        }
//    }
//    for(int i=0;i<size()-1;i++){
//        //cout<<countArr[i]<<endl;
//        cout<<tempArr[i]<<endl;
//    }
    
    /***********************************************************************/
    bool flag=true;
    int j=0;
    T tempArr [getCapacity()*4];
    int countArr[size()];
    
    for (int i = 0,t=0,s=0; i<size()-1 && t<(size()*2)-2; ++i,t+=2,s++) {
        int counter = 0;
        for (int k = 0; k < size()-1 ; ++k){
            if (pair<T,T>(tempArr[t],tempArr[t+1]) != pair<T,T>(arr[k],arr[k+1])){
                tempArr[j]=arr[k];
                tempArr[j+1]=arr[k+1];
                j+=2;
            }
 
        }
        
        for (int k=0; k < size()-1; ++k){
            if (tempArr[t]==arr[k] && tempArr[t+1] == arr[k+1]){  
                ++counter;
            }
        }
        countArr[s]=counter;
    }    
    cout<<endl;
    for (int i = 0,t=0; i<size()-1 && t<(size()*2)-4; ++i,t+=2){
        cout<<" Frequency=> "<<countArr[i]<<" --- " <<" BIGRAM=> " <<tempArr[t]<<" "<<tempArr[t+1]<<endl;
    }

}
template <class T>
BigramDyn<T>::~BigramDyn() {
    delete [] arr ;
}//Destructor
