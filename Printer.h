#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>
#include <vector>

class Printer {
    struct PrinterImpl; PrinterImpl &impl;
public:
    enum Kind { WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending }; Printer( unsigned int numStudents, unsigned int numVendingMachines );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};


#endif
