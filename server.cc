
#include <iostream>
#include "server.h"
#include "Printer.h"

using namespace std;

// constructor
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ){
    this->printer = &prt;
    this->numVM = numVendingMachines;
    this->numStd = numStudents;
    this->registeredVM = 0;
    this->RegisteredMachine = new VendingMachine*[numVendingMachines];
    for (int i = 0; i < this->numStd; i++){
        this->students.push_back(-1);
    }
    prt.print(Printer::NameServer, 'S');
}

void NameServer::VMregister( VendingMachine *vendingmachine ){
    (this->RegisteredMachine)[this->registeredVM] = vendingmachine;
    this->registeredVM++;
    printer->print(Printer::NameServer, 'R', vendingmachine->getId());
}

// consume a student id and assign a mechine to that student
VendingMachine * NameServer::getMachine(unsigned int id){
    unsigned int assigned_machine;
    
    if (this->students.at(id) < 0){
        assigned_machine = id % this->numVM;
    } else {
        assigned_machine = (this->students.at(id) + 1 ) % this->numVM;
    }
    this->students.at(id) = assigned_machine;
    this->printer->print(Printer::NameServer, 'N', id, RegisteredMachine[assigned_machine]->getId());
    this->printer->print(Printer::Student, id, 'V', RegisteredMachine[assigned_machine]->getId());
    return this->RegisteredMachine[assigned_machine];
}

VendingMachine ** NameServer::getMachineList(){ // get registered machine
    return this->RegisteredMachine;
}

NameServer::~NameServer(){
    delete[] this->RegisteredMachine;
    this->printer->print(Printer::NameServer, 'F');
}
