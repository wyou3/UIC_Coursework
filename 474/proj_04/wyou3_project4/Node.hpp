//
//  Node.hpp
//  Collections
//
//  Created by Jin You on 4/27/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <iostream>

class Node {
private:
    int val;
    Node * left;
    Node * right;
    
public:
    Node(int val_);
    Node(Node * copy);
    
    // getters/setters
    int getVal(){ return val;}
    int & getValRef(){ return val;}
    Node * getLeft(){ return left;}
    Node * getRight(){ return right;}
    void setVal(int val_){ val = val_;}
    void setLeft(Node * left_){ left = left_;}
    void setRight(Node * right_){ right = right_;}
};

#endif /* Node_hpp */
