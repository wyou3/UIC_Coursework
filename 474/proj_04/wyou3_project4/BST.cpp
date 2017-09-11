//
//  BST.cpp
//  Collections
//
//  Created by Jin You on 4/25/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "BST.hpp"
#include "Node.hpp"
#include <iostream>

using namespace std;

void BST::destructorHelper(Node * node){
    if(node == NULL)
        return;
    if(node->getLeft() != NULL)
        destructorHelper(node->getLeft());
    if(node->getRight() != NULL)
        destructorHelper(node->getRight());
    delete node;
}

BST::~BST(){
    destructorHelper(root);
}

void BST::addHelper(Node * root, int x){
    if(x < root->getVal()){
        if(root->getLeft() == NULL){
            root->setLeft(new Node(x));
            size_++;
        }else
            addHelper(root->getLeft(), x);
    }else if(x > root->getVal()){
        if(root->getRight() == NULL){
            root->setRight(new Node(x));
            size_++;
        }else
            addHelper(root->getRight(), x);
    }
}

void BST::add(int x){
    if(root == NULL){
        root = new Node(x);
        size_++;
    }else
        addHelper(root, x);
}

int BST::numNodes(Node * root){
    if(root == NULL)
        return 0;
    int count = 1;
    if(root->getLeft() != NULL)
        count += this->numNodes(root->getLeft());
    if(root->getRight() != NULL)
        count += this->numNodes(root->getRight());
    return count;
}

int& BST::indexHelper(Node * node, int index){
    int numNodesToLeft = this->numNodes(node->getLeft());
    if(index < numNodesToLeft)
        return indexHelper(node->getLeft(), index);
    if(index > numNodesToLeft)
        return indexHelper(node->getRight(), index - numNodesToLeft - 1);
    return node->getValRef();
}
int& BST::operator[](int index){
    if(index >= size_){
        cout << "Index out of bounds" << endl;
        exit(1);
    }
    return indexHelper(root, index);
}

void printHelper(Node * root_){
    if(root_ == NULL)
        return;
    if(root_->getLeft() == NULL){
        int val = root_->getVal();
        cout << val << " ";
        printHelper(root_->getRight());
    }else{
        printHelper(root_->getLeft());
        cout << root_->getVal() << " ";
        printHelper(root_->getRight());
    }
}

void BST::print(){
    cout << "[";
    printHelper(root);
    cout << "]" << endl;
}
