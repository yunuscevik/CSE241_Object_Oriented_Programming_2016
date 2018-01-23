/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.h
 * Author: asus-ubuntu
 *
 * Created on 24 Aralık 2016 Cumartesi, 21:54
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include <iostream>
#include <fstream>
#include <map>
#include "Bigram.h"


using namespace std;
template <class T>
class BigramMap : public Bigram<T>{
    public:
        BigramMap();
        BigramMap(int data);
        virtual void readFile(const char* fileName) ;
        virtual int numGrams();
        virtual int numOfGrams(T n1,T n2);
        virtual pair<T,T> maxGrams();
        virtual void prints()const ;
        int smallestMapVal(const map< pair<T,T>, int>& s)const;
        int largestMapVal(const map< pair<T,T>, int>& s)const;
        //setters
        void setOptionVal(int);
        void setSize(int);
        //getters
        int getOption() const{return optionVal;}
        int size()const{return count;}
        
        private:
            int count;
            int optionVal;
            map<int,pair<T,T> > m;
           
};


#endif /* BIGRAMMAP_H */

