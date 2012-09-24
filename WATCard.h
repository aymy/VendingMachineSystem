

#ifndef __WATCARD_H__
#define __WATCARD_H__


#include "Printer.h"

class WATCard {
  protected:
  	Printer* cprinter;
    unsigned int camount;
    unsigned int cid;
  public:
    WATCard( Printer &prt, unsigned int id, unsigned int amount);
    void credit( unsigned int amount );
    void debit( unsigned int amount );
    bool enoughFund( unsigned int vm_charge );
    unsigned int get_amount();
};
















#endif
