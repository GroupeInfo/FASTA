#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main(){
	//int titlelength;
	//char timeStampLength; 
	//char timeStamp;
	//char numberOfSequences;
	//char maximumLength;
	//char headerOffsetTable;
	//char sequenceOffsetTable;
	//char ambiguityOffsetTable;
	int N;
	ifstream f ("uniprot_sprot.fasta.pin", ios::out|ios ::binary);
	
	if(!f.is_open()){
		cout<<"impossible d'ouvrire le fichier !"<<endl;
		}
	else{
		uint32_t version ;
		f.read((char*)&version,sizeof(uint32_t));
		version = __builtin_bswap32(version);
		cout<<"Version : " << version<<endl;
		
		uint32_t databaseType ;
		f.read((char*)&databaseType,sizeof(uint32_t));
		databaseType = __builtin_bswap32(databaseType);
		cout<<"DatabaseType : " << databaseType<<endl;
		
		uint32_t titleLength ;
		f.read((char*)&titleLength,sizeof(uint32_t));
		titleLength = __builtin_bswap32(titleLength);
		cout<<"Title length : " << titleLength<<endl;	
		
		char titleString[titleLength];
		for(unsigned int i=0; i<titleLength; ++i){
			f.read((char*)&titleString[i], sizeof(char));
		}
		cout<<"Title string : "<<titleString<<endl;
		
		uint32_t timestampLength ;
		f.read((char*)&timestampLength,sizeof(uint32_t));
		timestampLength = __builtin_bswap32(timestampLength);
		cout<<"timestamp length : " << timestampLength<<endl;
		
		char timestamp[timestampLength];
		for(unsigned int i=0; i<timestampLength; ++i){
			f.read((char*)&timestamp[i], sizeof(char));
		}
		cout<<"timestamp : "<<timestamp<<endl;
		
		uint32_t sequencesNumber ;
		f.read((char*)&sequencesNumber,sizeof(uint32_t));
		sequencesNumber = __builtin_bswap32(sequencesNumber);
		cout<<"Number of sequences : " << sequencesNumber<<endl;
		N = sequencesNumber;
		
		uint64_t residuesNumber ;
		f.read((char*)&residuesNumber,sizeof(uint64_t));
		cout<<"Total number of residues : " << residuesNumber<<endl;
		
		uint32_t MaximumSequence ;
		f.read((char*)&MaximumSequence,sizeof(uint32_t));
		MaximumSequence = __builtin_bswap32(MaximumSequence);
		cout<<"Maximum Sequence: " << MaximumSequence<<endl;
		
		int counter2 = 0;
		uint32_t HeaderOffsetTable[N+1];
		for(unsigned int i=0; i<N+1; ++i){
			++counter2;
			f.read((char*)&HeaderOffsetTable[i], sizeof(uint32_t));
			HeaderOffsetTable[i] = __builtin_bswap32(HeaderOffsetTable[i]);
		}
		for(unsigned int i=0; i<N+1; ++i){
			cout<<"header Offset: " << HeaderOffsetTable[i]<<endl;
		}
		
		uint32_t sequenceOffsetTable[N+1];
		for(unsigned int i=0; i<N+1; ++i){
			f.read((char*)&sequenceOffsetTable[i], sizeof(uint32_t));
			sequenceOffsetTable[i] = __builtin_bswap32(sequenceOffsetTable[i]);
		}
		int counter = 0;
		for(unsigned int i=0; i<N+1; ++i){
			++counter;
			cout<<"Sequence Offset: " << sequenceOffsetTable[i]<<endl;
		}
		cout<<"je t'ai affiché"<<counter<<" offset de sequences"<<endl;
		cout<<"je t'ai affiché"<<counter2<<" offset de header"<<endl;
	}
	return 0;
};
