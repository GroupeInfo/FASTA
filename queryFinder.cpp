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

int search(const map<char,int>& map, ifstream& sequenceDB, const vector<char>& vec, uint32_t seqOffTab[]);
bool transform(const map<char,int>& m, const vector<int>& v, const vector<char>& vecto, vector<char>& seq, int i);
char transform2(const map<char,int>& m, int integer);
void fill(const map<char,int>& m, vector<char>& vec,int c);
string getName(ifstream& headerDB, int seqNum, uint32_t headOffTab[]);
vector<char> queryToVector(ifstream& queryFile);

auto start = std::chrono::steady_clock::now();
int main(int argc, char* argv[]){
	ifstream f (argv[1], ios::out|ios ::binary);
	ifstream f2 (argv[2], ios::out|ios::binary);
	ifstream f3 (argv[3], ios::out|ios::binary);
	ifstream f4 (argv[4]);
	if(!f.is_open() || !f2.is_open() || !f3.is_open() || !f4.is_open()){
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
		int N = sequencesNumber;
		
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
		vector<char> queryVector = queryToVector(f4);
		map<char,int> map = create_map();
		int sequenceNumber = search(map, f2, queryVector, sequenceOffsetTable);
		string str = getName(f3,sequenceNumber,HeaderOffsetTable);
		cout<<"The query corresponds to : "<<str<<endl;
	}
	return 0;
	
};

int  search(const map<char,int>& map, ifstream& sequenceDB, const vector<char>& vec,uint32_t seqOffTab[]){
	char c;
	int i = 0;
	int k = 0;
	while(!sequenceDB.eof()){
		sequenceDB.read((char *)&c, sizeof(char));
		char ch=transform2(map, (int)c);
		if(ch!=vec[i]){
			++k;
			sequenceDB.seekg(seqOffTab[k]); 
			i=0;
		}
		else{
			i++;
			if(i==((seqOffTab[k+1])-(seqOffTab[k]))-1){
				char sh;
				vector<char> stringSequence;
				sequenceDB.seekg(seqOffTab[k]);
				for(int j =0; j<i; j++){
					sequenceDB.read((char *)&sh, sizeof(char));
					fill(map,stringSequence,(int)sh);
				}
				return k;
				auto end = std::chrono::steady_clock::now();
				double elapsed_time_ns = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count());
				cout<<"Elapsed time (s): " << elapsed_time_ns /1e9<< endl;
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

string getName(ifstream& headerDB, int seqNum, uint32_t headOffTab[]){
	string s;
	char sh;
	int offset = headOffTab[seqNum];
	headerDB.seekg(offset+7);
	headerDB.read((char *)&sh, sizeof(sh));
	int length = (int)sh;
	headerDB.seekg(offset+8);
	for(unsigned int i=0; i<length; i++){
		headerDB.read((char *)&sh, sizeof(char));
		s.append(1,sh);
		}
	return s;
}

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