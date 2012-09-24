
#ifndef __BOTTLINGPLANT__H
#define __BOTTLINGPLANT__H

#include "Printer.h"
#include "server.h"
#include "truck.h"

class Truck;

class BottlingPlant { 
    Printer* printer;
    NameServer* nameserver;
    unsigned int numVM;         // number of vending machines
    unsigned int maxShipPF;     // max shipped per flavour
    unsigned int maxStockPF;    // max stock per flavour
    unsigned int TBS;           // time between shipments
    unsigned int TotalProduced; // total bottles produced
    Truck* btruck;
    unsigned int PlantInventory[4];
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
    void action(); 
    ~BottlingPlant();
};


#endif
