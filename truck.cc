
#include <iostream>
#include "truck.h"
#include "VendingMachine.h"

// return the minimum of two ints
int min(int a, int b){
   return a < b ? a : b;
}

// constructor
Truck::Truck(Printer &prt, NameServer &nameserver, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour){
    this->printer = &prt;
    this->nameserver = &nameserver;
    this->plant = &plant;
    this->numVM = numVendingMachines;
    this->maxSPF = maxStockPerFlavour;
    printer->print(Printer::Truck, 'S');
}


// called by BottlingPlant to ship the soda to vending machines
void Truck::action(){
    VendingMachine **machines = this->nameserver->getMachineList();
    
    this->plant->getShipment(this->Cargo);
    if (Cargo[0]+Cargo[1]+Cargo[2]+Cargo[3] == 0){      // if total number of bottles produced is zero
        return;
    }
    
    for (int i = 0; i < this->numVM; i++){ // loop over machines
        VendingMachine* VM = machines[i];
        this->printer->print(Printer::Vending, VM->getId(), 'r');
        
        unsigned int remaining = (this->Cargo)[0]+(this->Cargo)[1]+(this->Cargo)[2]+(this->Cargo)[3];   // number of remaining bottles in truck
        this->printer->print(Printer::Truck, 'd', VM->getId(), remaining);
        
        unsigned int *stock = VM->inventory();  // machine's inventory
        
        unsigned int unfilled = 0;
        for (int j = 0; j < 4; j++){ // loop over flavour
            int old_stock = stock[j];
            
            stock[j] = min(this->maxSPF, old_stock+this->Cargo[j]); // update VM inventory
            this->Cargo[j] = this->Cargo[j] + old_stock - stock[j]; // update truck's inventory
            
            unfilled = unfilled + this->maxSPF - stock[j];
        } // loop over flavour
        remaining = (this->Cargo)[0]+(this->Cargo)[1]+(this->Cargo)[2]+(this->Cargo)[3];
        
        if (unfilled !=0) {
            this->printer->print(Printer::Truck, 'U', VM->getId(), unfilled);
        }
        this->printer->print(Printer::Truck, 'D', VM->getId(), remaining);
        
        VM->restocked();
        if (remaining==0){
			return;
        }
    } // loop over machines
    
}

// destructor
Truck::~Truck(){
    this->printer->print(Printer::Truck, 'F');
}