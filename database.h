#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;

class database{
	
	private:
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
		database();
		//-get et set-//
		uint32_t database::getVersion();
		uint32_t database::getDatabaseType();
		uint32_t database::getTitleLength();
		char* database::getTitleString();
		uint32_t database::getTimestampLength();
		char* database::getTimestamp();
		uint32_t database::getSequencesNumber();
		uint32_t database::getResiduesNumber();
		uint32_t database::getMaximumSequence();
		uint32_t* database::getHeaderOffsetTable();
		uint32_t* database::pSequenceOffsetTable();
		
		void database::doData(char* argv[])
	
		
};
