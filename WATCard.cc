
#include <iostream>
#include "WATCard.h"
#include "Printer.h"


WATCard::WATCard ( Printer &prt, unsigned int id, unsigned int amount ){
	this->cprinter=&prt;  // pointer to the printer
	this->camount=amount;   // amount of money in the card
	this->cid=id; // student id
	
}

// credit card with amount of money
void WATCard::credit( unsigned int amount ){
	camount+=amount;
}

// debit card with amount of money
void WATCard::debit( unsigned int amount ){
	camount-=amount;
}


// check to see if the card has enough fund
bool WATCard::enoughFund( unsigned int vm_charge ){
	return camount>=vm_charge;
}

// get amount of money in the card
unsigned int WATCard::get_amount(){
	return camount;
}
