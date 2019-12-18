#include "scorematrix.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

/*le constructeur de Scorematrix ouvre le fichier BLOSUM et place dans le vector matrix
 *les résultats de combinaisons. L'ordre ne suit pas celui du fichier BLOSUM(A puis R...) mais
 * plutot l'odre suivi dans le fichier psq (- puis A ...), ordre du décodeur ci-dessous.
 * Ceci permettera un accès directe à un résultat de combinaisons particulier.
 * */
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
/*Fonction permettant d'enlever les espaces, utile car dans le ficheir BLOUSM les amino acides sont séparés par des espaces*/
string ScoreMatrix::removeSpaces(string input){
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

/*retourne l'index d'un caractère dans le décodeur*/
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

/*Opérateur facilitant l'accès à un élement dans la matrice*/
int & ScoreMatrix::operator()(char i, char j) {
	return matrix[nbrCols * i + j]; 
	
}

