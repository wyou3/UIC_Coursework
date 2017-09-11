//
//  Node.cpp
//  Collections
//
//  Created by Jin You on 4/27/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "Node.hpp"
Node::Node(int val_){
    val = val_;
    left = NULL;
    right = NULL;
}

Node * copyHelper(Node * copy){
	Node * clone = new Node(copy->getVal());
	Node * left = NULL;
	Node * right = NULL;
	if(copy->getLeft() != NULL)
		left = copyHelper(copy->getLeft());
 	if(copy->getRight() != NULL)
		right = copyHelper(copy->getRight());
 	clone->setLeft(left);
 	clone->setRight(right);
 	return clone;
}

Node::Node(Node * copy){
	val = copy->getVal();
	left = NULL;
	right = NULL;

	if(copy->getLeft() != NULL)
		left = copyHelper(copy->getLeft());
	if(copy->getRight() != NULL)
		right = copyHelper(copy->getRight());
}