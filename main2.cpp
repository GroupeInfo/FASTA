#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include "handleDb.h"
#include <ctime>
#include <chrono>
using namespace std;

int N;

void search(const map<char,int>& map, ifstream& sequenceDB, const vector<char>& vec, uint32_t seqOffTab[]);
bool transform(const map<char,int>& m, const vector<int>& v, const vector<char>& vecto, vector<char>& seq, int i);
char transform2(const map<char,int>& m, int integer);
void fill(const map<char,int>& m, vector<char>& vec,int c);
vector<char> queryToVector(ifstream& queryFile);

auto start = std::chrono::steady_clock::now();
int main(int argc, char* argv[]){
	ifstream f (argv[1], ios::out|ios ::binary);
	ifstream f2 (argv[2], ios::out|ios::binary);
	ifstream f3 (argv[3]);
	if(!f.is_open() || !f2.is_open() || !f3.is_open()){
		cout<<"impossible d'ouvrire un des fichiers !"<<endl;
		exit(1);
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
		
		uint32_t HeaderOffsetTable[N+1];
		for(unsigned int i=0; i<N+1; ++i){
			f.read((char*)&HeaderOffsetTable[i], sizeof(uint32_t));
			HeaderOffsetTable[i] = __builtin_bswap32(HeaderOffsetTable[i]);
		}
		uint32_t sequenceOffsetTable[N+1];
		for(unsigned int i=0; i<N+1; ++i){
			f.read((char*)&sequenceOffsetTable[i], sizeof(uint32_t));
			sequenceOffsetTable[i] = __builtin_bswap32(sequenceOffsetTable[i]);
		}
		vector<char> sequ;
		vector<char> queryVector = queryToVector(f3);
		map<char,int> map = create_map();
		search(map, f2, queryVector, sequenceOffsetTable);
	}
	return 0;
	
};

void search(const map<char,int>& map, ifstream& sequenceDB, const vector<char>& vec,uint32_t seqOffTab[]){
	int length = vec.size();
	char c;
	int i = 0;
	int k = 1;
	bool found = false;
	sequenceDB.seekg(1); 
	while(!sequenceDB.eof() && !found){
		sequenceDB.read((char *)&c, sizeof(char));
		char ch=transform2(map, (int)c);
		if(ch!=vec[i]){
			sequenceDB.seekg(seqOffTab[k]);
			++k;
			i=0;
		}
		else{
			i++;
			if(i==((seqOffTab[k+1])-(seqOffTab[k]))-1){
				char sh;
				vector<char> stringSequence;
				for(int j =0; j<i; j++){
					sequenceDB.seekg(seqOffTab[k]);
					sequenceDB.read((char *)&sh, sizeof(char));
					fill(map,stringSequence,(int)sh);
				}
				cout<<"sizeof stringSequence :"<<stringSequence.size()<<endl;
				break;
			}
		}
	}
}

char transform2(const map<char,int>& m, int integer){ 
	for(map<char,int>::const_iterator itr = m.begin(); itr!=m.end(); itr++){
		if(itr->second==integer){
			return itr->first;
		}
	}														
};

void fill(const map<char,int>& m, vector<char>& vec,int c){
	for(map<char,int>::const_iterator itr = m.begin(); itr!=m.end(); itr++){
		if(itr->second==c){
			vec.push_back(itr->first);break;
		}
	}														
};

vector<char> queryToVector(ifstream& queryFile){
	vector<char> vect;
	char ch;
	while( !queryFile.eof()){
		queryFile >> ch;
		vect.push_back(ch);
	}
	vect.pop_back();
	return vect;
}
