#include "database.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;

Database::Database(string filename) {
	
	this->filename = filename;
	loadData(filename);
	printInfos();
	loadProteins(filename);
	loadHeaders(filename);
}

void Database::loadData(const string &filename) {
	
	ifstream pinFile;
	pinFile.open(filename + ".pin", ios::binary | ios::in);

	if (pinFile.is_open()) {
		
		//version 
		pinFile.read((char*)&version,sizeof(uint32_t));
		version = __builtin_bswap32(version);
		
		//databaseType
		pinFile.read((char*)&databaseType,sizeof(uint32_t));
		databaseType = __builtin_bswap32(databaseType);
		cout<<"The database type is " << databaseType<<endl;
		
		//titleLength
		pinFile.read((char*)&titleLength,sizeof(uint32_t));
		titleLength = __builtin_bswap32(titleLength);	
		
		//title
		char titleString[titleLength];
		for(unsigned int i=0; i<titleLength; ++i){
			pinFile.read((char*)&titleString[i], sizeof(char));
		}
		title = (string)titleString;
		//timestampLength
		pinFile.read((char*)&timestampLength,sizeof(uint32_t));
		timestampLength = __builtin_bswap32(timestampLength);
		
		//timestamp
		char timestampcopy[timestampLength];
		for(unsigned int i=0; i<timestampLength; ++i){
			pinFile.read((char*)&timestampcopy[i], sizeof(char));
		}
		timestamp = string(timestampcopy);
		
		//Number of sequences
		pinFile.read((char*)&nbrSequences,sizeof(uint32_t));
		nbrSequences = __builtin_bswap32(nbrSequences);
		
		//Number of residues
		pinFile.read((char*)&nbrResidues,sizeof(uint64_t));
		
		//Maximum sequence
		pinFile.read((char*)&maxSequence,sizeof(uint32_t));
		maxSequence = __builtin_bswap32(maxSequence);
		
		//header offset table
		headerOffsets.reserve(nbrSequences+1); 		//fix the size of the vector
		uint32_t offset; 						//the offset is get as 4 bytes before convert it into an integer
		for (unsigned int i = 0; i <= nbrSequences; i++) {
			pinFile.read((char*) &offset, sizeof(uint32_t));
			headerOffsets.push_back(__builtin_bswap32(offset)); //convert bytes and store them as integer
		}	
		
		//sequence offset table
		sequenceOffsets.reserve(nbrSequences+1); 	//fix the size of the vector
		for (unsigned int i = 0; i <= nbrSequences; i++) {
			pinFile.read((char*) &offset, sizeof(uint32_t));
			sequenceOffsets.push_back(__builtin_bswap32(offset)); //convert bytes and store them as integer
		}
		pinFile.close();		
	}
	else {
		cout << "Unable to open database file : " << filename << ".pin\n";
		exit(1);
	}
}

void Database::loadProteins(const string &filename) {
	//load sequences from file
	
	if (!headerOffsets.empty() && !sequenceOffsets.empty()) {
		
		ifstream psqFile;
		psqFile.open(filename + ".psq", ios::binary | ios::in);
		psqFile.seekg(0, ios::beg);
		
		if (psqFile.is_open()) {
	
			int sequenceSize;
			for (unsigned int i = 0; i <= nbrSequences-1 ; i++){  //nbrSequences + 1
				
				char firstByte[1];  
				psqFile.read((char*) &firstByte, sizeof(firstByte));  // go one byte forward to avoid the null byte at the beginning
				
				sequenceSize = sequenceOffsets[i+1] - sequenceOffsets[i] -1  ;
				char* sequence = new char[sequenceSize];
				psqFile.read(sequence, sequenceSize);
				//cout<<"sequence : "<<sequence<<endl;
				Protein * prot = new Protein();
				prot->setSequence(sequence, sequenceSize);
				proteins.push_back(*prot);
			}
		}
		else {
			cout << "Unable to open database file : " << filename << ".psq\n";
			throw string("Unable to load file");
		}
	}
	else cout << "Header offsets or sequence offsets not yet loaded\n";
}

void Database::loadHeaders(const string &filename) {
	//load headers from file
	
	if (headerOffsets.empty() && sequenceOffsets.empty()) {
		cout << "Header offsets or sequence offsets not yet loaded\n";
	}
		
	ifstream phrFile;
	phrFile.open(filename + ".phr", ios::binary | ios::in);
	phrFile.seekg(1, ios::beg);
		
	if (!phrFile.is_open()) {
		cout << "Unable to open database file : " << filename << ".phr\n";
		exit(1);
	}
	
	int headerSize;
	for (unsigned int i = 0; i < nbrSequences ; i++){  
				
		headerSize = headerOffsets[i+1] - headerOffsets[i];
		char header[headerSize];
		phrFile.read((char*) &header, headerSize);
				
		proteins[i].setHeader(string(header).substr(8, string::npos));
	}
}

Protein & Database::getProtein(unsigned int index) {
	if (index < nbrSequences) {
		return proteins[index];
	}
	return proteins[nbrSequences-1]; //if index not valid, return last protein
}

void Database::printInfos(std::ostream & out) {
	
	out << "===== Database informations =====" << endl;
	out << " - Version : " <<  version << "\n";
	out << " - Type : " << databaseType  << "\n";
	//out << " - Title lenght : " << titleLength  << "\n";
	out << " - Title : " << title << "\n";
	//out << " - Timestamp Length : " <<  timestampLength  << "\n";
	out << " - Timestamp : " << timestamp  << "\n";
	out << " - Number of sequences : "  <<  nbrSequences << "\n";
	out << " - Residue count : " <<  nbrResidues << "\n";
	out << " - Longuest sequence : " << maxSequence << "\n";
	out << " ================================ " << endl;
	out<<endl;
}

int Database::getNbrSequences() {
	return nbrSequences;
}




