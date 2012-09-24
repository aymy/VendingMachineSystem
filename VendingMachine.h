 

#ifndef __VendingMachine_H__
#define __VendingMachine_H__


#include "Printer.h"
#include "server.h"
#include "WATCard.h"
#include "Flavour.h"

class NameServer;

class VendingMachine {
  protected:
    Printer* mprinter;   // pointer to a printer
    NameServer* mnameserver;   // pointer to nameserver
    unsigned int mid;   // machine id
    unsigned int mCost;  // sodacost
    unsigned int mstock_flavour;  // max num per flavour
    unsigned int stock [4];  // stock for each flavour
  public:
    enum Status { BUY, STOCK, FUNDS };
     VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
     virtual ~VendingMachine();
     virtual Status buy( Flavours flavour, WATCard *&card );
     virtual unsigned int *inventory();
     virtual void restocked();
     virtual unsigned int cost();
     virtual unsigned int getId();
};

class VendingMachineCardEater : public VendingMachine {
  public:
    VendingMachineCardEater( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    ~VendingMachineCardEater();
    Status buy( Flavours flavour, WATCard *&card );
    unsigned int *inventory();
    void restocked();
    unsigned int cost();
    unsigned int getId();
};


class VendingMachineOverCharger : public VendingMachine {
  public:
    VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    ~VendingMachineOverCharger();
    Status buy( Flavours flavour, WATCard *&card );
    unsigned int *inventory();
    void restocked();
    unsigned int cost();
    unsigned int getId();
};



#endif
