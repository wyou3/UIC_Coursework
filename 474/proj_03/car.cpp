//
//  car.cpp
//  VCS
//
//  Created by Jin You on 4/5/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include <iostream>
#include <string>
#include "car.hpp"

using namespace std;

Car::Car(){
    inMemory = false;
};
void Car::setCar(string make, string model, string date, int cost){
    this->make = make;
    this->model = model;
    this->date = date;
    this->cost = cost;
    this->inMemory = true;
}

bool Car::isInMemory(){
    return inMemory;
}

void Car::display(){
    cout << "Make: " + make << endl;
    cout << "Model: " + model << endl;
    cout << "Date: " <<  date << endl;
    cout << "Cost: " << cost<< endl;
}

void Car::setCost(int Cost){ this->cost = Cost;}

string Car::getMake(){ return make;}
string Car::getModel(){ return model;}
string Car::getDate(){ return date;}
int Car::getCost(){ return cost;}
