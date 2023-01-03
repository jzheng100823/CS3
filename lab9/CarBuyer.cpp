// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
    CarLot() {

        // creates 2 Ford factories and 2 Toyota factories 
        factories_.push_back(new FordFactory());
        factories_.push_back(new ToyotaFactory());
        factories_.push_back(new FordFactory());
        factories_.push_back(new ToyotaFactory());

        // fills the lot with 10 cars randomly generated from the two car factories
        for (int i = 0; i < lotSize_; ++i) {
            car4sale_[i] = *(factories_[rand() % factories_.size()]->requestCar());
        }
    }

    Car* testDriveCar() { return car4sale_; }

    // if a car is bought, requests a new one
    Car* buyCar() {
        Car* bought = &car4sale_[car_index];
        car4sale_[car_index] = *(factories_[rand() % factories_.size()]->requestCar());
        return bought;
    }
    //gets the next car in the car lot 
    Car* nextCar() {
        ++car_index;
        if (car_index == lotSize_){
            car_index = 0;
        }

        Car* result = &car4sale_[car_index];
        return result;
    }
    int lotSize() {
        return lotSize_;
    }
private:
    static const int lotSize_= 10;
    Car car4sale_[lotSize_];
    vector<CarFactory*> factories_;
    static int car_index;
};
int CarLot::car_index = 0;



CarLot* carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    //string array of toyota models
    static const std::array<std::string, 5> toyotaModels = { "Corolla", "Camry", "Prius", "4Runner", "Yaris" };

    //randomly selects one of those models 
   std::string buyModel = toyotaModels[rand() % toyotaModels.size()];
   for (int i = 0; i < carLotPtr->lotSize(); ++i) {
       Car* toBuy = carLotPtr->nextCar();
       cout << "Buyer" << id << " " << "test driving " <<" " << toBuy->getMake() <<" " << toBuy->getModel();

       // if the buyers likes the make and model they love it otherwise they hate it 
       if (toBuy->getMake() == "Toyota" && toBuy->getModel() == buyModel) {
           cout << " they love it! buying it" << endl;
       }
       else {
           cout << " They hate it not buying it" << endl;
       }
   }
}

// test-drives a car
// buys it if Ford
void fordLover(int id) {
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();
    //creates an array of ford models
    static const std::array<std::string,4> fordModels={ "Focus", "Mustang", "Explorer", "F-150" };
    // randomly selects one of the models form the array
    std::string buyModel = fordModels[rand() % fordModels.size()];

    //the buyer test drives all the cars in the lot
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car* toBuy = carLotPtr->nextCar();
        cout << "Buyer" << id <<" " << "test driving" <<" "<< toBuy->getMake() << " " << toBuy->getModel();

        //if they like the make and model they will buy it otherwise they dont like it 
        if (toBuy->getMake() == "Ford" && toBuy->getModel() == buyModel) {
            cout << " they love it! buying it" << endl;
        }
        else {
            cout << " They hate it not buying it" <<endl;
        }

    }
}



int main() {
    srand(time(nullptr));

    const int numBuyers = 20;
    for (int i = 0; i < numBuyers; ++i)
        if (rand() % 2 == 0)
            toyotaLover(i);
        else
            fordLover(i);

}