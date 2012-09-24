CXX = g++					# compiler
CXXFLAGS = -g -Wall -MMD			# compiler flags
LKFLAGS = -c                # linked flag
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = driver.o student.o WATCardOffice.o VendingMachine.o BottlingPlant.o server.o	WATCard.o printer.o truck.o # object files forming executable
EXEC = soda				# executable name

DEPENDS = ${OBJECT:.o=.d}			# substitute ".o" with ".d"

.PHONY : clean

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@

driver.o : driver.cc
	${CXX} ${LKFLAGS} $^
	
student.o : student.cc student.h Flavour.h WATCard.h WATCardOffice.h server.h Printer.h VendingMachine.h PRNG.h
	${CXX} ${LKFLAGS} $^

WATCardOffice.o : WATCardOffice.cc WATCardOffice.h Printer.h PRNG.h
	${CXX} ${LKFLAGS} $^

VendingMachine.o : VendingMachine.cc VendingMachine.h Printer.h PRNG.h
	${CXX} ${LKFLAGS} $^

BottlingPlant.o : BottlingPlant.cc BottlingPlant.h truck.h Printer.h PRNG.h
	${CXX} ${LKFLAGS} $^

server.o : server.cc server.h Printer.h
	${CXX} ${LKFLAGS} $^

WATCard.o : WATCard.h WATCard.cc Printer.h
	${CXX} ${LKFLAGS} $^

truck.o : truck.cc truck.h VendingMachine.h Printer.h
	${CXX} ${LKFLAGS} $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
