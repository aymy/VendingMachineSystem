

#ifndef __STUDENT_H__
#define __STUDENT_H__



#include "Flavour.h"
#include "Printer.h"
#include "server.h"
#include "WATCard.h"
#include "VendingMachine.h"
#include "WATCardOffice.h"

class Student {
  protected:
    unsigned int smaxPurchase; // max num of purchases
    unsigned int spurchase;  // num of purchases
    Printer* sprint; //pointer to printer
    NameServer* snameserver; // pointer to name serer.
    WATCardOffice* scardoffice;  //pointer to card office
    unsigned int sid;  // student id
    Flavours sflavour;  // flavour student picked
    WATCard* scard;  // pointer to card created
    VendingMachine* vm;  // pointer to the vending machine
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
    bool action();
    ~Student();
};





































#endif
