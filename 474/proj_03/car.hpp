//
//  car.hpp
//  VCS
//
//  Created by Jin You on 4/5/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#ifndef car_hpp
#define car_hpp

#include <iostream>

using namespace std;

class Car{
private:
    bool inMemory;
    string make, model;
    string date;
    int cost;

public:
    Car();
    void setCar(string make, string model, string date, int cost);
    bool isInMemory();
    void display();

    void setCost(int cost);
    string getMake();
    string getModel();
    string getDate();
    int getCost();
};

#endif /* car_hpp */
