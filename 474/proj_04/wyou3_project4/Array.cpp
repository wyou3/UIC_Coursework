//
//  Array.cpp
//  Collections
//
//  Created by Jin You on 4/25/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "Array.hpp"
#include <iostream>

using namespace std;

Array::~Array(){
    delete [] array;
}

void Array::add(int x){
    cout << "Add is not available in class array." << endl;
}

int& Array::operator[](int index){
    try{
        return array[index];
    }catch (std::exception e){
        throw e;
    }
}

Array& Array::operator=(Array& copy){
    Array newArray(copy.getSize());
    for(int i=0; i<copy.getSize(); i++)
        newArray[i] = copy[i];
    return *this;
}

void Array::print(){
    cout << "[";
    for(int i=0; i<size_; i++){
        if(i != size_-1)
            cout << (*this)[i] << " ";
        else
            cout << (*this)[i];
    }
    cout << "]" << endl;
}
