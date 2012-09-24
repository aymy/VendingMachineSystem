

#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "Printer.h"
#include "server.h"
#include "BottlingPlant.h"

class BottlingPlant;

class Truck { 
    Printer* printer;
    NameServer* nameserver;
    BottlingPlant* plant;
    unsigned int numVM;     // number of VendingMachines
    unsigned int maxSPF;    // maxStockPerFlavour
    unsigned int Cargo[4];  // truck's inventory
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    void action(); 
    ~Truck();
};

#endif
