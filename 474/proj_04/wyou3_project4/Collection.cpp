//
//  Collection.cpp
//  Collections
//
//  Created by Jin You on 4/27/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "Collection.hpp"

Collection::~Collection(){}

Collection& Collection::map(int fn(int x)){
    for(int i=0; i<size_; i++)
        (*this)[i] = fn((*this)[i]);
    return *this;
}

bool Collection::contains(int x){
    for(int i=0; i<size_; i++)
        if((*this)[i] == x)
            return true;
    return false;
}

int Collection::getSize(){
    return size_;
}

Collection& Collection::operator=(Collection& copy){
    return *this;
}

