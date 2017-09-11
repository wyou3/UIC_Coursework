//
//  carPtr.cpp
//  VCS
//
//  Created by Jin You on 4/5/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include "carPtr.hpp"
#include "car.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>

using namespace std;

CarPtr::CarPtr(){
    car = NULL;
};
CarPtr::~CarPtr(){
    if( car != NULL)
        delete car;
};


Car* CarPtr::operator->(){
    if(car == NULL)
        car = new Car();
    return car;
};
Car& CarPtr::operator*(){
    if(car == NULL)
        car = new Car();
    return *car;
};

void CarPtr::loadCarFromFile(){
    string make, model, date;
    int cost = 0;
    string fileName = "carData/ .txt";
    fileName[8] = (char)(id + '0');

    ifstream infile(fileName);
    string line;
    infile >> line;
    
    int i=0;
    int len = line.length();
    while(i < len && line[i] != ','){ i++;} // skip id
    i++;
    while(i < len && line[i] != ','){
        make += line[i];
        i++;
    }
    i++;
    while(i < len && line[i] != ','){
        model += line[i];
        i++;
    }
    i++;
    while(i < len && line[i] != ','){
        date += line[i];
        i++;
    }
    i++;
    while(i < len && line[i] != ','){
        cost = cost*10 + (int)(line[i] - '0');
        i++;
    }

    car = new Car();
    car->setCar(make, model, date, cost);
}

bool CarPtr::inMemory(){
    return (car != NULL);
}

void CarPtr::deleteCar(){
    delete car;
    car = NULL;
}

void CarPtr::setId(int id){
    this->id = id;
};

void CarPtr::display(){
    if(car != NULL)
        car->display();
};



