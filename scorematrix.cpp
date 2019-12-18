#include "scorematrix.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

ScoreMatrix::ScoreMatrix(const string & filename, int nbrCols) {
	aminoAcids = "";
	ifstream file;
	file.open(filename);
	this->nbrCols = nbrCols;  
	matrix.assign(nbrCols * nbrCols, 0);  
	string line;
	decoder = {'-','A','B','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','U','*','O','J'};
	if (!file.is_open()) {
		cout<<"Erreur dans l'ouverture du fichier BLOSUM"<<endl;
		exit(1);
	}
	
	int value;
	unsigned int j = 0;
	while (getline(file, line)) {
		
		if (line[0] == '#') { 
			continue;
		}

		else if (line[0] == ' ') { 
			aminoAcids.append(line, 1, line.size());
			aminoAcids = removeSpaces(aminoAcids);
			continue;
		}
		unsigned int i = 0;
		stringstream converter;
		converter << &line[1];
		int aminoAcidVer = decode(aminoAcids[j]);
		while (converter >> value){
			if (i < aminoAcids.size() && j < aminoAcids.size()) {
				
				int aminoAcidHor = decode(aminoAcids[i]); 
				this->operator()(aminoAcidHor, aminoAcidVer) = (int) value;
				i++;
			}	
		}
		j++;
	}
}

string ScoreMatrix::removeSpaces(string input){
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

int ScoreMatrix::decode(char c){
	unsigned int i = 0;
	while(i<decoder.size()){
		if((char)decoder[i] == c){
			break;
		}
		else{
			++i;
		}
	}
	return i;
}

int & ScoreMatrix::operator()(char i, char j) {
	return matrix[nbrCols * i + j]; 
	
}

