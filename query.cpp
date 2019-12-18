#include <fstream>
#include <sstream>
#include <iostream>
#include "query.h"

using namespace std;

Query::Query() {}

Query::Query(char* sequence, int length, string header) {
	this->length = length;
	this->sequence = sequence;
	this->header = header;
}

Query::~Query(){}

void Query::loadFromFile(const string filename) { 
	string line;
	string str;
	ifstream file;
	file.open(filename);
	if(!file.is_open()){
		cout << "Unable to open file : " << filename << "\n";
		exit(1);
	}
		
	while (getline(file, line)) {
			
		if (line[0] == '>') {
			header = line;
		}
		else {	
			str+= line;
		}
	}
		
	length = str.size();
	sequence = new char[length+1];
	for (int i = 0; i <= length; i++) {
		sequence[i] = getInt(str[i]);
	}
}


string Query::decodeQuery() {
	string decodedSequence = "";
	
	for (int i = 0; i < length; i++) {
		decodedSequence += getChar(sequence[i]);
	}
	return decodedSequence;
}

char Query::getChar(char letter){
	switch (letter) { 
		case 0:  return '-'; break;
		case 1:  return 'A'; break; 
		case 2:  return 'B'; break; 
		case 3:  return 'C'; break; 
		case 4:  return 'D'; break; 
		case 5:  return 'E'; break; 
		case 6:  return 'F'; break; 
		case 7:  return 'G'; break; 
		case 8:  return 'H'; break; 
		case 9:  return 'I'; break; 
		case 27: return 'J'; break; 
		case 10: return 'K'; break; 
		case 11: return 'L'; break; 
		case 12: return 'M'; break; 
		case 13: return 'N'; break; 
		case 26: return 'O'; break; 
		case 14: return 'P'; break; 
		case 15: return 'Q'; break; 
		case 16: return 'R'; break; 
		case 17: return 'S'; break; 
		case 18: return 'T'; break;
		case 24: return 'U'; break;
		case 19: return 'V'; break; 
		case 20: return 'W'; break; 
		case 21: return 'X'; break;
		case 22: return 'Y'; break;
		case 23: return 'Z'; break;
		case 25: return '*'; break;	
		} 
	return '/';
}

int Query::getInt(char letter){
	switch (letter) { 
		case '-': return 0;  break;
		case 'A': return 1;  break; 
		case 'B': return 2;  break; 
		case 'C': return 3;  break; 
		case 'D': return 4;  break; 
		case 'E': return 5;  break; 
		case 'F': return 6;  break; 
		case 'G': return 7;  break; 
		case 'H': return 8;  break; 
		case 'I': return 9;  break; 
		case 'J': return 27; break; 
		case 'K': return 10; break; 
		case 'L': return 11; break; 
		case 'M': return 12; break; 
		case 'N': return 13; break; 
		case 'O': return 26; break; 
		case 'P': return 14; break; 
		case 'Q': return 15; break; 
		case 'R': return 16; break; 
		case 'S': return 17; break; 
		case 'T': return 18; break;
		case 'U': return 24; break;
		case 'V': return 19; break; 
		case 'W': return 20; break; 
		case 'X': return 21; break;
		case 'Y': return 22; break;
		case 'Z': return 23; break;
		case '*': return 24; break;	
		} 
	return -1;
}

void Query::print(ostream& out) {
	out << header << "\n";
	out << decodeQuery() << endl;
}
