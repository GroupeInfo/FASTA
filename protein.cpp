#include "protein.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Protein::Protein() {
	
}

Protein::Protein(char* sequence, int length, string header) {
	this->length = length;
	this->sequence = sequence;
	this->header = header;
}

Protein::~Protein() {}

void Protein::setSequence(char* sequence, int length) {
	this->length = length;
	this->sequence = sequence;
}

const char Protein::getResidue(int i) const {
	return sequence[i];
}

char* Protein::getSequence() const {
	return sequence;
}

void Protein::setHeader(string header) {
	this->header = header;
}

void Protein::print(ostream& out) { //only print the header  //if there is already a >, don't print another !
	out << ">";  //this is because of weird caracters at the begining (can't figure out why) -> solution : skip the 's' when reading the header
	out << "s";
	out << header << "\n";
}

const int Protein::size() const {
	//return the lenght of the sequence
	return length;
}
