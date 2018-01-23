
#include "BigramMap.h"
#include "Exception.h"

template <class T>
BigramMap<T>::BigramMap() {
    count = 1;
}

template <class T>
BigramMap<T>::BigramMap(int data) {
    count = 1;
    setOptionVal(data);
}
template <class T>
void BigramMap<T>::setOptionVal(int opt) {
    optionVal=opt;
}
template <class T>
void BigramMap<T>::setSize(int s){
    count=s;
}
template <class T>
void BigramMap<T>::readFile(const char* fileName) {
    fstream file;
    file.open(fileName); // dosya acma
    if (!file) {
        
        throw Exception(" UNABLE TO OPEN FILE!!! ");
    }
    
    T val1, temp;
    bool flag=true;
    int index = 0;
    while (!file.eof()) {
        if(flag==true){
           if(!(file >> val1)){
               throw Exception(" Corrupted file!!! ");
            }
            temp = val1;
            flag=false;
        }
        if(!(file >> val1)){
            throw Exception(" Corrupted file!!! ");
        }
        m[index] = pair<T, T>(temp, val1);
        temp = val1;
        ++index;
        setSize(size()+1);
        
    }
    
    file.close();
}
template <class T>
int BigramMap<T>::numGrams() {
    return size() - 1;
}
template <class T>
int BigramMap<T>::numOfGrams(T n1, T n2) {
    int count = 0;
    for(auto itr=m.begin();itr !=m.end();itr++){
        if (pair<T, T>(itr->second.first, itr->second.second) == 
                pair<T, T>(n1, n2))
            count++;
    }
    return count;
}
template <class T>
pair<T, T> BigramMap<T>::maxGrams() {

    pair<T, T> sayi;
    int frequency = 0;

    for(auto itr=m.begin();itr !=m.end();itr++) {
        int counter = 0;
        for(auto itr1=m.begin();itr1 !=m.end();itr1++) {
            if (pair<T, T>(itr1->second.first, itr1->second.second) == 
                    pair<T, T>(itr->second.first, itr->second.second)) {
                ++counter;
            }
        }
        if (counter > frequency) {
            frequency = counter;
            sayi = pair<T, T>(itr->second.first, itr->second.second);
            
        }
    }
    cout << "Frequency=> " << frequency << " MAXGRAM=> ";
    return sayi;
}
template <class T>
void BigramMap<T>::prints() const {
    map< pair<T,T> , int > a;
    
    for(auto itr=m.begin();itr !=m.end();itr++) {
        int counter = 0;
        for(auto itr1=m.begin();itr1 !=m.end();itr1++) {
            if (pair<T, T>(itr1->second.first, itr1->second.second) == 
                    pair<T, T>(itr->second.first, itr->second.second)) {
                ++counter;
            }
        }
            a[pair<T, T>(itr->second.first, itr->second.second)]=counter;
    }
    cout<<endl;
    int beginPos = smallestMapVal(a);
    int endPos = largestMapVal(a);
    for(int i = endPos; i >= beginPos; --i)
    {
        for(auto it = a.begin(); it != a.end(); ++it)
        {
            if(it->second == i)
            {
                cout <<" Frequency=> " <<it->second<< " ---- " 
                        <<" BIGRAM=> " << it->first.first << " "<< it->first.second << endl;
            }
        }
    }
}
template <class T>
int BigramMap<T>::smallestMapVal(const map< pair<T,T>, int>& m)const
{
    
    auto it= m.begin();
    int lowest = it->second;
    for(auto it = m.begin(); it != m.end(); ++it)
    {
        if(it->second < lowest)
            lowest = it->second;
    }
    return lowest;
}
template <class T>
int BigramMap<T>::largestMapVal(const map< pair<T,T>, int>& m)const
{
    auto it = m.begin();
    int highest = it->second;
    for(auto it = m.begin(); it != m.end(); ++it)
    {
        if(it->second > highest)
            highest = it->second;
    }
    return highest;
}