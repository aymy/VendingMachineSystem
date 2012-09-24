

#include "VendingMachine.h"
#include "PRNG.h"
#include <iostream>

// global random number prng;
extern PRNG prng;


// VendingMachine creation
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ){
	this->mprinter=&prt;   // pointer to a printer
	this->mnameserver=&nameServer;   // pointer to nameserver
	this->mid=id;   // machine id
	this->mCost=sodaCost;  // soda cost for the vending machine
	this->mstock_flavour=maxStockPerFlavour;  // max stock per flavour in the machine
    
    // initialize the stock for each flavour to be 0
	for (int i=0; i<4; i+=1){
		this->stock[i]=0;
	}
}


// VendingMachineCardEater creation
VendingMachineCardEater::VendingMachineCardEater( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ): VendingMachine ( prt, nameServer, id, sodaCost, maxStockPerFlavour ){
    mprinter->print(Printer::Vending, id, 'S', this->cost());
    // register the machine to nameserver
	nameServer.VMregister(this);
}


// VendingMachineOverCharger creation
VendingMachineOverCharger::VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ):VendingMachine ( prt, nameServer, id, sodaCost, maxStockPerFlavour ){
    // change the soda cost for the machine
    this->mCost = 2*sodaCost;
    mprinter->print(Printer::Vending, id, 'S', this->cost());
    // register the vending machine
	nameServer.VMregister(this);
}

// student buying soda from the machine
VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard *&card ){
    VendingMachine::Status s;
    
    // if out of stock, return STOCK
	if (stock[static_cast<int>(flavour)]==0){
		s=STOCK;
	}
    
    // if out of funds, return FUNDS
	else if (!card->enoughFund(this->cost())){
		s=FUNDS;
	}
    
    // if no other issue, debit the card and decrease the stock of that flavour by 1 and return BUY;
	else {
        card->debit(this->mCost);
		stock[static_cast<int>(flavour)]-=1;
        mprinter->print(Printer::Vending, mid, 'B', static_cast<int>(flavour), stock[static_cast<int>(flavour)]); 
		s=BUY;
	}
    return s;
}


// student buy soda from the VendingMachineCardEater
VendingMachine::Status VendingMachineCardEater::buy( Flavours flavour, WATCard *&card ){
    VendingMachine::Status s;
	s=VendingMachine::buy(flavour, card);
    // delete the card being eaten
	if (prng(9)==0){
		delete card;
		card=NULL;
	}
	return s;
}


// student buy soda from the VendingMachineOverCharger
VendingMachine::Status VendingMachineOverCharger::buy( Flavours flavour, WATCard *&card ){
    return VendingMachine::buy(flavour, card);
}
 
// return the inventory of the vending machine in general
unsigned int* VendingMachine::inventory(){
	return this->stock;
}

// return the inventory of the vending machine card eater
unsigned int* VendingMachineCardEater::inventory(){
	return this->stock;
}

// return the inventory of the vending machine over charger
unsigned int* VendingMachineOverCharger::inventory(){
	return this->stock;
}

// truck restock vending machine
void VendingMachine::restocked(){
    mprinter->print(Printer::Vending, this->getId(), 'R');
}

// truck restock vending machine
void VendingMachineCardEater::restocked(){
    mprinter->print(Printer::Vending, this->getId(), 'R');
}

// truck restock vending machine
void VendingMachineOverCharger::restocked(){
    mprinter->print(Printer::Vending, this->getId(), 'R');
}

// return the cost for the vending machine
unsigned int VendingMachine::cost(){
	return this->mCost;
}

// return the cost for the vending machine card eater
unsigned int VendingMachineCardEater::cost(){
	return this->mCost;
}

// return the cost for the vending machine over charger
unsigned int VendingMachineOverCharger::cost(){
	return this->mCost;
}

// return the id of the machine card eater
unsigned int VendingMachineCardEater::getId(){
	return this->mid;
}

// return the id of the machine over charger
unsigned int VendingMachineOverCharger::getId(){
	return this->mid;
}

// return the id of the machine
unsigned int VendingMachine::getId(){
	return this->mid;
}

// destroy the vending machine
VendingMachine::~VendingMachine(){
    return;
}

// destroy the vending machine
VendingMachineCardEater::~VendingMachineCardEater(){
    mprinter->print(Printer::Vending, this->getId(), 'F');
}

// destroy the vending machine
VendingMachineOverCharger::~VendingMachineOverCharger(){
    mprinter->print(Printer::Vending, this->getId(), 'F');
}
