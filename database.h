#include <string>
#include <vector>
#include <iostream>
#include "query.h"
using std::vector;
using std::string;

class Database {
	
	private :	
		string filename;
		uint32_t version;
		uint32_t databaseType;
		uint32_t titleLength;
		string title;
		uint32_t timestampLength;
		string timestamp;
		uint32_t nbrSequences;
		uint32_t nbrResidues;
		uint32_t maxSequence;
		vector<int> headerOffsets;
		vector<int> sequenceOffsets;
		vector<Protein> proteins;

		void loadData(const string &filename);
		void loadProteins(const string &filename);
		void loadHeaders(const string &filename);
		
	public : 
		Database(string dbName);
		//~Database();
		void print(std::ostream & out = std::cout);
		Protein & getProtein(unsigned int index); 
		int getNbrSequences();
		
};


