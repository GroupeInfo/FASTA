#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;

class database {
	
	private:
		char* text;
		
		uint32_t version;
		uint32_t databaseType;
		uint32_t titleLength;
		char** titleString;
		uint32_t timestampLength;
		char** timestamp;
		uint32_t sequencesNumber;
		uint32_t residuesNumber;
		uint32_t maximumSequence;
		uint32_t** pHeaderOffsetTable;
		uint32_t** pSequenceOffsetTable;
	
	public:
		//-Constructeur-//
		database(char* buffer);
		//-get et set-//
		uint32_t getVersion();
		uint32_t getDatabaseType();
		uint32_t getTitleLength();
		char* getTitleString();
		uint32_t getTimestampLength();
		char* getTimestamp();
		uint32_t getSequencesNumber();
		uint32_t getResiduesNumber();
		uint32_t getMaximumSequence();
		uint32_t* getHeaderOffsetTable();
		uint32_t* getSequenceOffsetTable();
		
		void dopin();
		vector<char> doquery();
		void dophr();
		
		
};
