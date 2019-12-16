#include "scorematrix.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

ScoreMatrix::ScoreMatrix(const string & filename, int nbrCols) {
	aminoAcids = "";
	ifstream file;
	file.open(filename);
	this->nbrCols = nbrCols;  //default number of column  of a BLOSUM matrix is 27
	matrix.assign(nbrCols * nbrCols, 0);  //fill the matrix with zeros
	if (!file.is_open()) {
		cout<<"Erreur dans l'ouverture du fichier BLOSUM"<<endl;
		exit(1);
	}
	
	while (getline(file, line)) {
		
		if (line[0] == '#') { //ignore lines beginning with #
			continue;
		}

		else if (line[0] == ' ') { //new function will be better here... 
			aminoAcids.append(line, 1, line.size());
			aminoAcids = removeSpaces(aminoAcids);
			continue;
		}
		else{
			
		}
	}
}

string ScoreMatrix::removeSpaces(string input){
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}
