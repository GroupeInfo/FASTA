#include "database.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;

Database::Database(string filename) {
	//== Constructeur ==//
	this->filename = filename;
	loadData(filename);
	print();
	loadProteins(filename);
	loadHeaders(filename);
}

void Database::loadData(const string &filename) {
	//== Partie d'extraction d'information du fichier .pin ==//
	ifstream pinFile;
	pinFile.open(filename + ".pin", ios::binary | ios::in);
	
	// Vérification d'erreur d'ouverture
	if (!pinFile.is_open()) {
		cout << "Erreur ouverture de " << filename << ".pin\n";
		exit(1);
	}
	
	//--Extraction--//
	
	//-Version-// 
	pinFile.read((char*)&version,sizeof(uint32_t));
	version = __builtin_bswap32(version);
	
	//-DatabaseType-//
	pinFile.read((char*)&databaseType,sizeof(uint32_t));
	databaseType = __builtin_bswap32(databaseType);
	
	//-TitleLength//
	pinFile.read((char*)&titleLength,sizeof(uint32_t));
	titleLength = __builtin_bswap32(titleLength);	
	
	//-Title-//
	char titleString[titleLength];
	for(unsigned int i=0; i<titleLength; ++i){
		pinFile.read((char*)&titleString[i], sizeof(char));
	}
	title = (string)titleString;
	
	//-TimestampLength-//
	pinFile.read((char*)&timestampLength,sizeof(uint32_t));
	timestampLength = __builtin_bswap32(timestampLength);
	
	//-Timestamp-//
	char timestampcopy[timestampLength];
	for(unsigned int i=0; i<timestampLength; ++i){
		pinFile.read((char*)&timestampcopy[i], sizeof(char));
	}
	timestamp = string(timestampcopy);
	
	//-NbrSequences-//
	pinFile.read((char*)&nbrSequences,sizeof(uint32_t));
	nbrSequences = __builtin_bswap32(nbrSequences);
	
	//-NbrResidues-//
	pinFile.read((char*)&nbrResidues,sizeof(uint64_t));
	
	//-MaxSequence-//
	pinFile.read((char*)&maxSequence,sizeof(uint32_t));
	maxSequence = __builtin_bswap32(maxSequence);
	
	//-HeaderOffsetTable-//
	headerOffsets.reserve(nbrSequences+1); 		//fix the size of the vector
	uint32_t offset; 						//the offset is get as 4 bytes before convert it into an integer
	for (unsigned int i = 0; i <= nbrSequences; i++) {
		pinFile.read((char*) &offset, sizeof(uint32_t));
		headerOffsets.push_back(__builtin_bswap32(offset)); //convert bytes and store them as integer
	}	
	
	//-SequenceOffsetTable-//
	sequenceOffsets.reserve(nbrSequences+1); 	//fix the size of the vector
	for (unsigned int i = 0; i <= nbrSequences; i++) {
		pinFile.read((char*) &offset, sizeof(uint32_t));
		sequenceOffsets.push_back(__builtin_bswap32(offset)); //convert bytes and store them as integer
	}
	pinFile.close();
}

void Database::loadProteins(const string &filename) {
	//== Partie d'extraction d'informations du fichier .psq ==//
	ifstream psqFile;
	psqFile.open(filename + ".psq", ios::binary | ios::in);
	psqFile.seekg(0, ios::beg);
	
	// Vérification d'erreur d'ouverture
	if (!psqFile.is_open()) {
		cout << "Erreur Ouverture de " << filename << ".psq\n";
		exit(1);
	}
	//--Extraction--//
	int sequenceLength;
	for (unsigned int i = 0; i < nbrSequences ; i++){
		
		char firstByte[1];  
		psqFile.read((char*) &firstByte, sizeof(firstByte));
		
		sequenceLength = sequenceOffsets[i+1] - sequenceOffsets[i] -1  ;
		char* sequence = new char[sequenceLength];
		psqFile.read(sequence, sequenceLength);
		Protein * prot = new Protein();
		prot->setSequence(sequence, sequenceLength);
		proteins.push_back(*prot);
	}
	psqFile.close();
}

void Database::loadHeaders(const string &filename) {
	//== Partie d'extraction d'informations du fichier .phr ==//
	
	ifstream phrFile;
	phrFile.open(filename + ".phr", ios::binary | ios::in);
	phrFile.seekg(1, ios::beg);
	
	// Vérification d'erreur d'ouverture
	if (!phrFile.is_open()) {
		cout << "Erreur ouverture de " << filename << ".phr\n";
		exit(1);
	}
	//--Extraction--//
	int headerLength;
	for (unsigned int i = 0; i < nbrSequences ; i++){  
		
		headerLength = headerOffsets[i+1] - headerOffsets[i];
		char header[headerLength];
		phrFile.read((char*) &header, headerLength);
		
		proteins[i].setHeader(string(header).substr(8, string::npos));
	}
	phrFile.close();
}

Protein & Database::getProtein(unsigned int index) {
	return proteins[index];
}

void Database::print(std::ostream & out) {
	//== Print les infos contenue dans la database ==//
	
	out << " ===== Database =====" << endl;
	out << " - Version : " <<  this->version << endl;
	out << " - Type de la Database : " << this->databaseType  << endl;
	out << " - Titre : " << this->title << endl;
	out << " - Timestamp : " << this->timestamp  << endl;
	out << " - Nombre de Séquences : "  <<  this->nbrSequences << endl;
	out << " - Nombre de Residues : " <<  this->nbrResidues << endl;
	out << " - Plus Longue Séquence : " << this->maxSequence << endl;
	out << " ====================" << endl;
	out<< "\n" <<endl;
}

int Database::getNbrSequences() {
	return nbrSequences;
}




