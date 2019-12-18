#include "protein.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Protein::Protein() {
	
}
/*une protéine a comme attributs sa taille, sa sequence et son titre*/
Protein::Protein(char* sequence, int length, string header) {
	this->length = length;
	this->sequence = sequence;
	this->header = header;
}

Protein::~Protein() {}

/*Setters*/
void Protein::setSequence(char* sequence, int length) {
	this->length = length;
	this->sequence = sequence;
}

void Protein::setHeader(string header) {
	this->header = header;
}

/*Getters*/
const char Protein::getResidue(int i) const {
	return sequence[i];
}

char* Protein::getSequence() const {
	return sequence;
}

/*Pour imprimer(uniquement le titre (header) )*/
void Protein::print(ostream& out) { 
	out << ">";  
	out << "s";
	out << header << "\n";
}

/*retourne la taille...*/
const int Protein::size() const {
	return length;
}
