//
//  Collection.hpp
//  Collections
//
//  Created by Jin You on 4/27/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef Collection_hpp
#define Collection_hpp

#include <stdio.h>

class Collection{
public:
    // deffered methods
    virtual void add(int x)=0;
    virtual int& operator[](int index)=0;
    
    // concrete methods
    Collection() : size_(0){};
    Collection(int size) : size_(size){};
    Collection(Collection const &collection);
    ~Collection();
    Collection& map(int fn(int x));
    bool contains(int x);
    Collection& operator=(Collection& rhs);
    
    // getters/setter
    int getSize();
protected:
    int size_;
};

#endif /* Collection_hpp */
