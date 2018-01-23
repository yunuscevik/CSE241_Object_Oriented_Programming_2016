/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramDyn.h
 * Author: asus-ubuntu
 *
 * Created on 24 Aralık 2016 Cumartesi, 21:54
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H
#include <iostream>
#include <fstream>
#include <map>
#include "Bigram.h"
using namespace std;

template <class T>
class BigramDyn: public Bigram<T>{
    public:
    BigramDyn();// default constructor
    BigramDyn(int); // option parametesi alan constructor
    BigramDyn(const BigramDyn& );//copy constructor
    ~BigramDyn(); // destructor
    virtual void readFile(const char* fileName);
    virtual int numGrams();
    virtual int numOfGrams(T n1,T n2);
    virtual pair<T,T> maxGrams();
    virtual void prints()const ;
    BigramDyn& operator=(const BigramDyn& rightSide);
    T operator[](int)const;
    //setters
    void setOptionVal(int);
    void setSize(int);
    void setCapacity(int);
    //getters
    int getOption() const{return optionVal;}
    int size()const{return usedSection;}
    int getCapacity( ) const { return capacity; }
    private:
        T * arr;
        int capacity;
        int usedSection;
        int optionVal;
};


#endif /* BIGRAMDYN_H */

