#include <iostream>
#include "class.hpp"

Vehicle::Vehicle(int x, int y) { 
    absis = x;
    ordinat = y;
}

Vehicle::~Vehicle() { 
    std::cout<< "Your vehicle has been destructed" << std::endl;
}

double Vehicle::getVelocity(){
    return speed;
}

void Vehicle::setSpeed (double newSpeed){
    if (!isEngineOn) {
        std::cout << "The engine is not turned on yet" << std::endl;
        return;
    }

    if (newSpeed < 0) {
        std::cout << "Speed cannot be under 0" << std::endl;
    } else {
        speed = newSpeed;
        std::cout << "Speed has been changed to " << newSpeed << std::endl;
    }
}

void Vehicle::turnOnEngine(){
    if (isEngineOn){
        std::cout << "Engine is already on" << std::endl;
        return;
    }
    isEngineOn = true;
    std::cout<<"Engine is turned on" << std::endl;
}

void Vehicle::move(int x, int y) {
    if (!isEngineOn) {
        std::cout << "The engine is not turned on yet" << std::endl;
        return;
    }

    if (speed == 0) {
        std::cout << "Please set your speed > 0 first" << std::endl;
        return;
    }

    int moveX = x, moveY = y;
    if (x < 0) { moveX = -x; }
    if (y < 0) { moveY = -y; }
    double loss = lossFuel(moveX,moveY,speed); 
    
    if (loss > fuelCapacity){
        std::cout << "Not enough fuel" << std::endl;
        return;
    } else {
        absis += x;
        ordinat += y;
        fuelCapacity -= loss;
        std::cout << "You have moved to (" << absis << "," << ordinat << ")" << std::endl;
    }
}

void Vehicle::addPassanger() {
    if (passanger < maxSeats){
        passanger += 1;
        std::cout << "Passanger has been added" << std::endl;
    } else {
        std::cout << "Seats are full" << std::endl;
    }
}

void Vehicle::printCommand() {
    std::cout << "1. Turn on engine" << std::endl;
    std::cout << "2. Set speed" << std::endl;
    std::cout << "3. Move" << std::endl;
    std::cout << "4. Refuel" << std::endl;
    std::cout << "5. Add passanger" << std::endl;
    std::cout << "6. Display information" << std::endl;
}

void Vehicle::printInformation() {
    std::cout << "\n> Information <" << std::endl;
    std::cout << "1. Engine is " << (isEngineOn ? "on" : "off") <<std::endl;
    std::cout << "2. Speed: " << speed <<std::endl;
    std::cout << "3. Position: (" << absis << "," << ordinat << ")" <<std::endl;
    std::cout << "4. Fuel: " << fuelCapacity <<std::endl;
    std::cout << "5. Passanger: " << passanger << std::endl;
}

LandVehicle::LandVehicle(int x,int y): Vehicle(x,y) {};

Motorcycle::Motorcycle(int x, int y, bool helmStorage): LandVehicle(x,y) {
    hasHelmStorage = helmStorage;
    std::cout<< "Motorcycle in (" << absis << "," << ordinat << ") has been constructed ";
    if (hasHelmStorage) {
        std::cout << "with helm storage" <<std::endl;
    } else {
        std::cout << "without helm storage" << std::endl;
    }
    maxSeats = 2;
    passanger = 1;
    usedSeats = 1;
}

void Motorcycle::addExternalHelmStorage(){
    if (hasHelmStorage){
        std::cout << "Already has helm storage" << std::endl;
    } else {
        hasHelmStorage = true;
        std::cout << "External helm storage has been added" << std::endl;
    }
}

double Motorcycle::lossFuel(int inputX, int inputY, double inputSpeed) {
    return 0.5*(inputSpeed*inputX + inputSpeed*inputY)*passanger;
}

void Motorcycle::refuel() {
    fuelCapacity = 500;
    std::cout << "Your vehicle has been refueled" << std::endl;
}

void Motorcycle::printStats(){
    std::cout << "> Motorcycle Statistics <" << std::endl;
    std::cout << "1. LossFuel : 0.5 * (speed*moveX + speed*moveY) * passanger" << std::endl;
    std::cout << "2. Maximum number of seats : 2" << std::endl;
    std::cout << "3. Maximum fuel capacity : 500" << std::endl;
}

void Motorcycle::printCommand(){
    std::cout << "> Motorcycle Commands" << std::endl;
    Vehicle::printCommand();
    std::cout << "7. Add external helm storage" << std::endl;
    std::cout << "0. Stop riding\n" << std::endl;
    std::cout << "Input yout choice: ";
}

void Motorcycle::printInformation() {
    Vehicle::printInformation();
    std::cout << "6. Helm storage: " << (hasHelmStorage ? "yes" : "no") <<std::endl;
}

void Motorcycle::addPassanger() {
    if (hasHelmStorage) {
        Vehicle::addPassanger();
    } else {
        std::cout << "Please add helm storage before add passanger" << std::endl;
    }
}

Car::Car(int x, int y): LandVehicle(x,y) {
    std::cout << "How many number of seats of your car: "; std::cin >> maxSeats;
    while (maxSeats < 1) {
        std::cout << "Your input is invalid, number of seats must be > 1" << std::endl;
        std::cout << "How many number of seats of your car: "; std::cin >> maxSeats;
    }
    std::cout<< "Car in (" << absis << "," << ordinat << ") has been constructed with " << maxSeats << " number of seats" << std::endl;
    number_of_wheels = 4;
    passanger = 1;
    usedSeats = 1;
}

double Car::lossFuel(int inputX, int inputY, double inputSpeed) { 
    return (inputSpeed * (1.5) * (inputX + inputY) * (0.75 * passanger)); 
}

void Car::refuel() {
    fuelCapacity = 2000;
    std::cout << "Your vehicle has been refueled" << std::endl;
}

void Car::printStats() {
    std::cout << "> Car Statistics <" << std::endl;
    std::cout << "1. LossFuel : speed * (1.5) * (moveX + moveY) * (0.75 * passanger)" << std::endl;
    std::cout << "2. Maximum number of seats : " << maxSeats << std::endl;
    std::cout << "3. Maximum fuel capacity : 2000" << std::endl;
}

void Car::printCommand() {
    std::cout << "> Car Commands <" << std::endl;
    Vehicle::printCommand();
    std::cout << "0. Stop driving\n" << std::endl;
    std::cout << "Input yout choice: ";
}

void Car::printInformation() {
    std::cout << "\n> Information <" << std::endl;
    std::cout << "1. Engine is " << (isEngineOn ? "on" : "off") <<std::endl;
    std::cout << "2. Speed: " << speed <<std::endl;
    std::cout << "3. Position: (" << absis << "," << ordinat << ")" <<std::endl;
    std::cout << "4. Fuel: " << fuelCapacity <<std::endl;
    std::cout << "6. Passanger: " << passanger << std::endl;
}

void wrongInput(){
    std::cout << "Your input is invalid!" << std::endl;
}