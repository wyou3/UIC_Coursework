//
//  Array.hpp
//  Collections
//
//  Created by Jin You on 4/25/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdio.h>
#include "Collection.hpp"

class Array: public Collection{
public:
    Array(int size) : Collection(size){ array = new int[size_];}
    Array(Array & rhs) : Collection(rhs.getSize()){
        array = new int[size_];
        for(int i=0; i<rhs.getSize(); i++)
            array[i] = rhs[i];
    }
    ~Array();
    
    virtual void add(int x);
    virtual int& operator[](int index);
    virtual Array& operator=(Array& rhs);
    void print();
private:
    int* array;
};

#endif /* Array_hpp */
