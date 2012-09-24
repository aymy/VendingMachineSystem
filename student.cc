

#include <iostream>
#include "student.h"
#include "Flavour.h"
#include "WATCard.h"
#include "WATCardOffice.h"
#include "server.h"
#include "Printer.h"
#include "VendingMachine.h"
#include "PRNG.h"

// get global random number prng;
extern PRNG prng;

//Create student class
Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases){
	this->smaxPurchase=maxPurchases;                   //max num of purchases
	this->spurchase=prng(1, maxPurchases);             //num of purchases
	this->sprint=&prt;                                 //pointer to printer
	this->snameserver=&nameServer;                     //pointer to name server
	this->scardoffice=&cardOffice;                     //pointer to card office
	this->sid=id;                                      //student id
	this->sflavour=static_cast<Flavours>(prng(0,3));      //flavour student picked 
	this->scard=scardoffice->create(sid, 5);           //pointer to card created
    sprint->print(Printer::Student, id, 'S', static_cast<int>(sflavour), spurchase);
	this->vm=snameserver->getMachine(sid);             //pointer to the vending machine
}

//Student started to purchase soda from the vending machine.

bool Student::action(){	
    
    // if all the selected soda are purchased, return false
    if (spurchase<=0){
		return false;
    }
    
    // starts to buy soda from the machine.
    VendingMachine::Status to_buy=vm->buy(sflavour, scard);
    
    // if the WATCard is eaten by the machine, create a new card with initial balance 5.
	if (scard==NULL){
		sprint->print(Printer::Student, sid, 'D');
		this->scard=scardoffice->create( sid, 5);
	}
    
    // if the machine is ready to buy, return true;
	if (to_buy==0){  
		// reduce the number of bottles student wants to purchase by 1
        spurchase-=1;
		sprint->print(Printer::Student, sid, 'B', scard->get_amount());
		return true;
	}	
    
    // if there is insufficient stock, return true;
    else if (to_buy==1) { 
        // get a new machine number from the nameserver.
		this->vm=snameserver->getMachine(sid);
		return true;
	}
    
    // if there is insufficient funds, charge the WATcard by $3 until there is enough money to buy one bottle and return true;
	else if (to_buy==2){
		do {
            sprint->print(Printer::Student, sid, 't', 3);
            scardoffice->transfer(sid, 3, *scard);
            sprint->print(Printer::Student, sid, 'T', scard->get_amount());  
        } while (!scard->enoughFund(vm->cost()));
		return true;
	}
}

// delete student
Student::~Student(){
    // delete WATcard created by the student.
    delete this->scard;
	sprint->print(Printer::Student, sid, 'F');	
}
