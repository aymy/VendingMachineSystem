

#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__


#include "Printer.h"
#include "WATCard.h"

class WATCardOffice {
  private:
    Printer* office_printer; // pointer to the printer
  public:
    WATCardOffice( Printer &prt );
    WATCard* create( unsigned int id, unsigned int amount );
    void transfer( unsigned int id, unsigned int amount, WATCard &Card );
    ~WATCardOffice();
};


#endif
