

#include <iostream>
#include "BottlingPlant.h"
#include "truck.h"
#include "PRNG.h"

extern PRNG prng;

// constructor
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ){
    this->printer = &prt;
    this->nameserver = &nameServer;
    this->numVM = numVendingMachines;
    this->maxShipPF = maxShippedPerFlavour;
    this->maxStockPF = maxStockPerFlavour;
    this->TBS = timeBetweenShipments;
    this->TotalProduced = 0;
    this->btruck = new Truck(*(this->printer), *(this->nameserver), *(this), this->numVM, this->maxStockPF);
    printer->print(Printer::BottlingPlant, 'S');

    for (int i = 0; i < 4; i++){        // produce random number of bottles
        this->PlantInventory[i] = prng(this->maxShipPF);
        TotalProduced = TotalProduced + this->PlantInventory[i];
    }
    this->printer->print(Printer::BottlingPlant, 'G', this->TotalProduced);
    this->btruck->action();
}

// produce soda and call truck to ship them
void BottlingPlant::action(){   // called by main
    this->TotalProduced = 0;
    if (prng(4) == 0){          // Plant is on strike
        this->printer->print(Printer::BottlingPlant, 'X');
        return;
    }
    if (prng(this->TBS - 1) != 0){ // truck not return
        return;
    }
    for (int i = 0; i < 4; i++){        // produce random number of bottles
        this->PlantInventory[i] = prng(this->maxShipPF);
        TotalProduced = TotalProduced + this->PlantInventory[i];
    }
    this->printer->print(Printer::BottlingPlant, 'G', this->TotalProduced);
    this->btruck->action();
}


// called by truck to update truck's inventory
void BottlingPlant::getShipment(unsigned int cargo[]){
    for (int i = 0; i < 4; i++){
        cargo[i] = this->PlantInventory[i];
    }
    this->printer->print(Printer::BottlingPlant, 'P');
    this->printer->print(Printer::Truck, 'P', this->TotalProduced);
}

// destructor
BottlingPlant::~BottlingPlant(){
    this->printer->print(Printer::BottlingPlant, 'F');
    delete this->btruck;
}
