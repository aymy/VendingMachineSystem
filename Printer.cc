#include <iostream>
#include <vector>
#include <sstream>
#include "Printer.h"

using std::ostringstream;



Printer & Printer::operator=(Printer & prin){
 //   this->impl=prin.impl;
  //  return *this;
}

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines ){
    
	impl.numStudents=numStudents;
	impl.numVendingMachines=numVendingMachines;
	impl.totalColumns=numStudents+numVendingMachines+4;
	impl.buffer_row.resize(impl.totalColumns);
	std::cout<<"WATOff\tNames\tTruck\tPlant\t";
	for (int i=0; i<numStudents; i+=1){
		std::cout<<"Stud"<<i<<"\t";
	}
	for (int j=0; j<numVendingMachines; j+=1){
		std::cout<<"Mach"<<j<<"\t";
	}
	std::cout<<std::endl;
	for (int t=0; t<impl.totalColumns; t+=1){
		std::cout<<"*******"<<"\t";
	}
	std::cout<<std::endl;
}

Printer::~Printer(){
	std::cout<<"***********************"<<std::endl;
}

void Printer::print( Kind kind, char state ){
	ostringstream os;
	os<<state;
	buffer_in_row(kind, os.str());
}

void Printer::print( Kind kind, char state, int value1 ){
	ostringstream os;
	os<<state<<value1;
	buffer_in_row(kind, os.str());
}
void Printer::print( Kind kind, char state, int value1, int value2 ){
	ostringstream os;
	os<<state<<value1<<value2;
	buffer_in_row(kind, os.str());
}
void Printer::print( Kind kind, unsigned int lid, char state ){
	ostringstream os;
	os<<state;
	buffer_in_row(kind, os.str(), lid);
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
	ostringstream os;
	os<<state<<value1;
	buffer_in_row(kind, os.str(), lid);
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
	ostringstream os;
	os<<state<<value1<<value2;
	buffer_in_row(kind, os.str(), lid);
}

void Printer::buffer_in_row( Kind kind, std::string state){
	int column_num;
	switch(kind){
		case WATCardOffice:
			column_num=0;
			break;
		case NameServer:
			column_num=1;
			break;
		case Truck:
			column_num=2;
			break;
		case BottlingPlant:
			column_num=3;
			break;
		default:
			return;
	}
	print_buffer(column_num, state);
}
void Printer::buffer_in_row(Kind kind, std::string state, unsigned int id){
	int column_num;
	switch(kind){
		case Student:
			column_num=4+id;
			break;
		case Vending:
			column_num=4+impl.numStudents+id;
			break;
		default:
			return;
	}
	print_buffer(column_num, state);
}

void Printer::print_buffer(int col, std::string state){
	if (state=="F"){
		buffer_flush();
		for (int i=0; i<impl.totalColumns; i+=1){
			if (i==col){
				impl.buffer_row.at(col)="F";
			}
			else{
				impl.buffer_row.at(i)="...";
	
			}
		}
		buffer_flush();
		return;

	}
	if (impl.buffer_row.at(col)==""){
		impl.buffer_row.at(col)=state;
		return;
	}
	else {
		buffer_flush();
		impl.buffer_row.at(col)=state;
		return;
	}
}

void Printer::buffer_flush(){
    std::vector<std::string>::iterator it;
	int total_print=0;
	for (it=impl.buffer_row.begin(); it<impl.buffer_row.end(); it++){
		if(*it!=""){
			total_print+=1;
		}
	}
	if (total_print==0){
		return;
	}
	else{
		for (int i=0; i<impl.totalColumns; i+=1){
			std::cout<<impl.buffer_row.at(i)<<"\t";
		}
		std::cout<<std::endl;
	}
	impl.buffer_row.clear();
	impl.buffer_row.resize(impl.totalColumns);
	return;
}


//end of file



