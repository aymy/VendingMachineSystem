

#include <iostream>
#include "WATCardOffice.h"
#include "WATCard.h"

#include "Printer.h"
#include "PRNG.h"

// extern global random number prng;
extern PRNG prng;

// WATCardOffice creation
WATCardOffice::WATCardOffice( Printer &prt ){
	this->office_printer=&prt; // pointer to printer
	office_printer->print( Printer::WATCardOffice, 'S' );
}

// create a new WATCard
WATCard *WATCardOffice::create( unsigned int id, unsigned int amount ){
	WATCard* a_card = new WATCard( *office_printer, id, amount );
	office_printer->print(Printer::WATCardOffice, 'C', id, amount);
	return a_card;
}

// transfer money to the WATCard of student with id.
void WATCardOffice::transfer( unsigned int id, unsigned int amount, WATCard &card ){
	office_printer->print(Printer::WATCardOffice, 't', id, amount);
    //1/4 chances that only half money is deposited
	if (prng(3)==0){
		card.credit(0.5*amount);
		office_printer->print(Printer::WATCardOffice, 'T', id, 0.5*amount);
	}
	else{
		card.credit(amount);
		office_printer->print(Printer::WATCardOffice, 'T', id, amount);
	}
		
}


// delete WATCardOffice
WATCardOffice::~WATCardOffice(){
	office_printer->print(Printer::WATCardOffice, 'F');	
}
