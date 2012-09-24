

#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include "VendingMachine.h"
#include "Printer.h"

class VendingMachine;

class NameServer{
    Printer *printer;
    unsigned int numVM;     // number of total VM
    unsigned int numStd;    // number of students
    VendingMachine **RegisteredMachine; // array of pointers to regiistered VM
    unsigned int registeredVM; // number of registered VM
    std::vector<int> students;
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ); 
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );  // consume student id
    VendingMachine **getMachineList();
    ~NameServer(); // destructor
};

#endif
