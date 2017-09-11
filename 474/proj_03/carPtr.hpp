//
//  carPtr.hpp
//  VCS
//
//  Created by Jin You on 4/5/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef carPtr_hpp
#define carPtr_hpp

#include "car.hpp"

using namespace std;

class CarPtr {    
public:
    CarPtr();
    ~CarPtr();
    Car* operator->();  // send message to Car object
    Car& operator*();   // obtain reference to Car object
    void loadCarFromFile(); 
    bool inMemory();
    void deleteCar();
    void setId(int);
    void display();


protected:
    int id;
    Car* car;                // local copy of Car (NULL if swapped)
    CarPtr(const CarPtr&);   // no copying
    CarPtr& operator=(const CarPtr&) ; // no assignment operator
};

#endif /* carPtr_hpp */
