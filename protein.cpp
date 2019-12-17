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

void Protein::print(ostream& out) { 
	out << ">";  
	out << "s";
	out << header << "\n";
}

const int Protein::size() const {
	return length;
}
