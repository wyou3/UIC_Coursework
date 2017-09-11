//
//  BST.hpp
//  Collections
//
//  Created by Jin You on 4/25/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include "Collection.hpp"
#include "Node.hpp"

class BST: public Collection{
public:
    BST() : Collection(){ root = NULL;};
    BST(Node * root_) : Collection(){ root = root_;};
    BST(int val) : Collection(){ 
        root = new Node(val);
        size_ = 1;
    };
    BST(BST & rhs) : Collection(){ 
        root = new Node(rhs.getRoot());
        size_ = numNodes(rhs.getRoot());
    }
    void destructorHelper(Node * node);
    ~BST();

    // deffered from Collection
    virtual void add(int x);
    void addHelper(Node * root, int x);
    virtual int& operator[](int index);

    BST& operator=(const BST& rhs) const;
    int& indexHelper(Node * node, int index);
    int numNodes(Node * root);
    void print();
    
    // getters/setters
    Node * getRoot(){ return root;}
    void setRoot(Node * root_){ root = root_;}
private:
    Node * root;
};

#endif /* BST_hpp */
