//
//  main.cpp
//  VCS
//
//  Created by Jin You on 4/2/17.
//  Copyright © 2017 Jin You. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "car.hpp"
#include "carPtr.hpp"
#include "string.hpp"
#include "date.hpp"

using namespace std;

CarPtr* setGarage(int n);
void createCar(CarPtr carPtrs[]);
void listCars(CarPtr carPtrs[]);
void changeCarPrice(CarPtr carPtrs[]);
void saveAllCars(CarPtr carPtrs[]);
void saveCar(int i, CarPtr carPtrs[]);
void cleanCarFiles();
void deleteCarFromMem(CarPtr carPtrs[]);

string printError = "Invalid command. Try again.";
int numCars = 5;
int carsInGarage = 0;
int inMemory[2] = {-1, -1};     // ids of cars in memory
int numInMemory = 0; // number of cars in memory

int main(int argc, const char * argv[]) {    
    
    cleanCarFiles(); // wipe all previous car data

    CarPtr* garage = setGarage(numCars);

    string input;
    
    do{
        cout << "Enter command (c, l, p, s, q):" << endl;
        cin >> input;
        
        if(input == "c")      { createCar(garage);}
        else if(input == "l") { listCars(garage);}
        else if(input == "p") { changeCarPrice(garage);}
        else if(input == "s") { saveAllCars(garage);}
        else if(input != "q") { cout << printError << endl;}
    }while( input != "q");
    
    return 0;
}


// Deletes all previously set
// car data files
void cleanCarFiles(){
    for(int i=0; i<numCars; i++){
        char fileName[] = "carData/ .txt";
        fileName[8] = (char)((i+1) + '0');
        remove((char *) fileName);
    }
}

// Creates empty CarPtr array
CarPtr* setGarage(int n){
    CarPtr* garage = new CarPtr[n];
    for(int i=0; i<n; i++)
        garage[i].setId(i+1);

    return garage;
};

// Asks user for car information and
// creates a new car instance within
// garage.
void createCar(CarPtr carPtrs[]){

    if( carsInGarage >= 5){
        cout << "*** Garage is full ******" << endl;
        cout << "*** unable to add car ***" << endl;
        return;
    }

    string make, model;
    string date;
    int cost;
    
    cout << "\n--Enter in car information--" << endl;
    cout << "Enter the make of your car: " << endl;
    cin >> make;
    cout << "Enter the model of your car: " << endl;
    cin >> model;
    cout << "Enter the date, with format MM/DD/YYYY, the car was aquired: " << endl;
    cin >> date;
    cout << "Enter the amount, in dollars, the car was purchased at: " << endl;
    cin >> cost;
 
    deleteCarFromMem(carPtrs);

    cout << "\n***Creating car***" << endl;
    carPtrs[carsInGarage]->setCar(make, model, date, cost);
    carPtrs[carsInGarage]->display();
    cout << "******************\n" << endl;

    inMemory[numInMemory] = carsInGarage;
    numInMemory++;
    carsInGarage++;
    
};

// Save on file and delete
// car from memory if 2
// or more cars are allocated 
void deleteCarFromMem(CarPtr carPtrs[]){
    if( numInMemory >= 2){
        int i = inMemory[0];
        inMemory[0] = inMemory[1];
        inMemory[1] = -1;

        saveCar(i, carPtrs);
        carPtrs[i].deleteCar();

        numInMemory--;
    }
}

// Lists all cars and associated
// information
void listCars(CarPtr carPtrs[]){
    cout << "\n--Listing cars--" << endl;

    deleteCarFromMem(carPtrs);

    for(int i=0; i<carsInGarage; i++){

        cout << "*** Car " << (i+1) << " ***" << endl;
        if( carPtrs[i]->isInMemory()){
            carPtrs[i]->display();
            cout << endl;
        }else{
            carPtrs[i].loadCarFromFile();
            carPtrs[i]->display();
            saveCar(i, carPtrs);
            carPtrs[i].deleteCar();
            cout << endl;
        }
    }
}

// Changes the price on the car
// at with given id
void changeCarPrice(CarPtr carPtrs[]){
    cout << "\n--Enter car information--" << endl;
    
    int id, i;
    
    cout << "Enter car id: " << endl;
    cin >> id;
    i = id - 1;
    
    if( i < 0 || i >= carsInGarage){
        cout << "Error: Car was not put in inventory!\n" << endl;
    }else{
        int newPrice;
        
        cout << "Enter new car price: " << endl;
        cin >> newPrice;
        
        if( !carPtrs[i]->isInMemory()){
            deleteCarFromMem(carPtrs);
            carPtrs[i].loadCarFromFile();
            carPtrs[i]->setCost(newPrice);
            cout << carPtrs[i]->getCost() << endl;
            saveCar(i, carPtrs);
            carPtrs[i].deleteCar();
            cout << endl;
        } else{
            carPtrs[i]->setCost(newPrice);
            cout << endl;
        }
    }
    
}

// Saves all in memory instances
// of cars and saves into disk
void saveAllCars(CarPtr carPtrs[]){
    cout << "\n--Saving all cars--" << endl;
    for(int i=0; i<numCars; i++){
        if(carPtrs[i]->isInMemory())
            saveCar(i, carPtrs);
    }
    cout << endl;
}

// Saves car at index i
void saveCar(int i, CarPtr carPtrs[]){

    // clean file 
    char cleanFile[] = "carData/ .txt";
    cleanFile[8] = (char)((i+1) + '0');
    remove((char *) cleanFile);

    ofstream file;
    string fileName = "carData/ .txt";
    fileName[8] = (char)((i+1) + '0');  // set file name to [(car id) + .txt]
    
    file.open (fileName);

    // id,make,model,date,cost
    file << (i+1) << "," 
         << carPtrs[i]->getMake() << ","
         << carPtrs[i]->getModel() << ","
         << carPtrs[i]->getDate() << ","
         << carPtrs[i]->getCost() << endl;

    file.close();
    cout << "*** Saved car " << (i+1) << " ***" << endl;    
}