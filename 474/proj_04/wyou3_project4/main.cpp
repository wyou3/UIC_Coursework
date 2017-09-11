//
//  main.cpp
//  Collections
//
//  Created by Jin You on 4/22/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include <iostream>
#include "Collection.hpp"
#include "BST.hpp"
#include "Array.hpp"

using namespace std;

void test_array();
void test_bst();

int main(int argc, const char * argv[]) {
    test_array();
    cout << endl;
    test_bst();
    return 0;
}

void test_array(){
    cout << "***** Testing Array ******" << endl;
    Array a(5);
    for(int i=0; i<a.getSize(); i++)
        a[i] = i;
    cout << "Original: ";
    a.print();
    cout << "Size: " << a.getSize() << endl;

    // test indexing for Array
    cout << "-----Testing Indexing-----" << endl;
    cout << "Array[0]: " << a[0] << endl;
    cout << "Array[3]: " << a[3] << endl;
    cout << "Array[4]: " << a[4] << endl;

    // test copy for Array
    cout << "-----Testing Copy-----" << endl;
    Array copy = a;
    cout << "Original: ";
    a.print();
    cout << "Copy: ";
    copy.print();
    
    // test map for Array
    cout << "-----Testing Map------" << endl;
    cout << "Function -> (x + 5)" << endl;
    cout << "Before: ";
    a.print();
    cout << "After: ";
    a.map([](int a) { return a+5;});
    a.print();
}

void test_bst(){
    cout << "****** Testing BST *******" << endl;
    BST bst(-1);   
    cout << "Adding: " << -1 << endl;
    for(int i=0; i<5; i++){
        cout << "Adding: " << (i - 3) << endl;
        bst.add(i-3);
    }
    for(int i=4; i<9; i++){
        cout << "Adding: " << i << endl;
        bst.add(i);
    }

    // Original BST
    cout << "-----Original BST------" << endl;
    cout << "BST: ";
    bst.print();
    cout << "Num nodes: " << bst.numNodes(bst.getRoot()) << endl;

    // test indexing for BST
    cout << "-----Testing [] op------" << endl;
    cout << "Changing BST[0] to 5" << endl;
    bst[0] = -5;
    cout << "Changing BST[3] to 5" << endl;
    bst[5] = 3;
    cout << "BST: ";
    bst.print();    

    // test copy on BST 
    cout << "-----Testing Copy op------" << endl;
    cout << "Original: ";
    bst.print();  
    BST copy = bst;
    cout << "Copy:     ";
    copy.print();

    // test map on BST
    cout << "-----Testing Map------" << endl;
    cout << "Function -> (x + 5)" << endl;
    cout << "Before: ";
    bst.print();
    cout << "After: ";
    bst.map([](int a) { return a+5;});
    bst.print();
}
