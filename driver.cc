#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>					// numeric_limits
#include <cstdlib>					// exit
using namespace std;
#include "PRNG.h"

#include "soda.h"					// YOUR INCLUDES GO IN THIS FILE

PRNG prng( getpid() );					// default seed of random-number generator


struct ConfigParms {
    unsigned int sodaCost;				// MSRP per bottle
    unsigned int numStudents;				// number of students to create
    unsigned int maxPurchases;				// maximum number of bottles a student purchases
    unsigned int numVendingMachines;			// number of vending machines
    unsigned int maxStockPerFlavour;			// maximum number of bottles of each flavour stocked
    unsigned int maxShippedPerFlavour;			// number of bottles of each flavour in a shipment
    unsigned int timeBetweenShipments;			// length of time between shipment pickup
}; // ConfigParms

void processConfigFile( const char *configFile, ConfigParms &cparms );

// Process the configuration file to set the parameters of the simulation.
void processConfigFile( const char *configFile, ConfigParms &cparms ) {
    enum { Parmnum = 7 };
    struct {
        const char *name;
        bool used;
        unsigned int *value;
    } static parms[Parmnum] = {
        { "SodaCost", false, &cparms.sodaCost },
        { "NumStudents", false, &cparms.numStudents },
        { "MaxPurchases", false, &cparms.maxPurchases },
        { "NumVendingMachines", false, &cparms.numVendingMachines },
        { "MaxStockPerFlavour", false, &cparms.maxStockPerFlavour },
        { "MaxShippedPerFlavour", false, &cparms.maxShippedPerFlavour },
        { "TimeBetweenShipments", false, &cparms.timeBetweenShipments },
    };
    string name;
    unsigned int value, cnt, posn;
    unsigned int numOfParm = 0;

    ifstream in( configFile );				// open configuration file for input
    if ( in.fail() ) {
        cerr << "Error: could not open input file \"" << configFile << "\"" << endl;
        exit( EXIT_FAILURE );
    } // if

    for ( cnt = 0 ; cnt < Parmnum; cnt += 1 ) {		// parameter names may appear in any order
	for ( ;; ) {
	    in >> name;
      if ( in.fail() ) goto fini;			// multi-level exit
	  if ( name.substr(0,1) != "#" ) break;
	    in.ignore( numeric_limits<int>::max(), '\n' ); // ignore remainder of line
	} // for
	for ( posn = 0; posn < Parmnum && name != parms[posn].name; posn += 1 ); // linear search
      if ( posn == Parmnum ) break;			// configuration not found ?
      if ( parms[posn].used ) break;			// duplicate configuration ?
	in >> value;
      if ( in.fail() ) break;				// no input
      if ( value < 1 ) break;				// error check
	in.ignore( numeric_limits<int>::max(), '\n' );	// ignore remainder of line
	numOfParm += 1;
	parms[posn].used = true;
	*parms[posn].value = value;
    } // for
  fini:
    if ( numOfParm != Parmnum ) {
	cerr << "Error: file \"" << configFile << "\" is corrupt." << endl;
	exit( EXIT_FAILURE );    
    } // if
} // processConfigFile


static void shuffle( unsigned int set[], const int size ) {
    int i, p1, p2, temp;

    for ( i = 0; i < size; i += 1 ) {
	set[ i ] = i;
    } // for
    for ( i = 0; i < 10; i +=1 ) {			// shuffle N times
	p1 = prng( size - 1 );
	p2 = prng( size - 1 );
	temp = set[p1];
	set[p1] = set[p2];
	set[p2] = temp;
    } // for
} // shuffle


bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (1..N)] ]" << endl;
    exit( EXIT_FAILURE );
} // usage


int main( int argc, char *argv[] ) {
    const char *configFile = "soda.config";
    ConfigParms pm;
    unsigned int i;
    int seed;						// seed for random number generator

    switch ( argc ) {
      case 3:
	if ( ! convert( seed, argv[2] ) || seed < 1 ) usage( argv ); // invalid ?
	prng.seed( seed );				// seed the random number generator
	// FALL THROUGH
      case 2:
	configFile = argv[1];
	// FALL THROUGH
      case 1:						// all defaults
	break;
      default:						// wrong number of options
	usage( argv );
    } // switch

    processConfigFile( configFile, pm );		// process configuration file
    Printer prt( pm.numStudents, pm.numVendingMachines );
    WATCardOffice office( prt );			// students get WATCard transfers here
    NameServer nameServer( prt, pm.numVendingMachines, pm.numStudents ); // manages vending machine names

    VendingMachine *machines[ pm.numVendingMachines ];
    unsigned int vset[ pm.numVendingMachines ];
    shuffle( vset, pm.numVendingMachines );

    for ( i = 0; i < pm.numVendingMachines; i += 1 ) {	// randomize vending machines
	if ( prng( 1 ) == 0 ) {
	    machines[ vset[ i ] ] = new VendingMachineCardEater( prt, nameServer, vset[ i ], pm.sodaCost, pm.maxStockPerFlavour );
	} else {
	    machines[ vset[ i ] ] = new VendingMachineOverCharger( prt, nameServer, vset[ i ], pm.sodaCost, pm.maxStockPerFlavour );
	} // if
    } // for

    BottlingPlant plant( prt, nameServer, pm.numVendingMachines, pm.maxShippedPerFlavour, pm.maxStockPerFlavour, pm.timeBetweenShipments );

    vector<Student *> students( pm.numStudents );	// variable-size array
    unsigned int sset[ pm.numStudents ];
    shuffle( sset, pm.numStudents );

    for ( i = 0; i < pm.numStudents; i += 1 ) {		// randomize students
	students[ sset[ i ] ] = new Student( prt, nameServer, office, sset[ i ], pm.maxPurchases );
    } // for

    for ( ; students.size() != 0; ) {			// students finished ?
        unsigned int stud = prng( students.size() - 1 ); // select a random student
        if ( ! students[ stud ]->action() ) {		// invoke student, student finished ?
            delete students[ stud ];			// delete student
            students.erase( students.begin() + stud );	// remove entry from vector
        } // if
        if ( students.size() != 0 ) plant.action();	// don't call plant if no students 
    } // for
    
    shuffle( vset, pm.numVendingMachines );		// randomize vending machines (again)
    for ( i = 0; i < pm.numVendingMachines; i += 1 ) {	// delete in random order
        delete machines[ vset[ i ] ];
    } // for
} // main

// Local Variables: //
// compile-command: "make" //
// End: //
