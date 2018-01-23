
/* 
 * File:   Bigram.h
 * Author: asus-ubuntu
 *
 * Created on 24 Aralık 2016 Cumartesi, 21:53
 */

#ifndef BIGRAM_H
#define BIGRAM_H
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Bigram{
    public:
        
        virtual void readFile(const char* fileName)=0;
        virtual int numGrams()=0;
        virtual int numOfGrams(T n1,T n2)=0;
        virtual pair<T,T> maxGrams()=0;
        virtual void prints() const=0;
        friend ostream& operator <<(ostream& os ,const Bigram& bg){
            bg.prints();
            return os;
        }
        
};


#endif /* BIGRAM_H */

