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

int search(const map<char,int>& map, ifstream& sequenceDB, const vector<char>& vec, vector<char>& se);
bool transform(const map<char,int>& m, const vector<int>& v, const vector<char>& vecto, vector<char>& seq, int i);
bool compare(const vector<char>& s, const vector<char>& q, vector<char>& se);
void test(ifstream& sequenceDB);

auto start = std::chrono::steady_clock::now();
vector<char> queryToVector(ifstream& queryFile);
int main(int argc, char* argv[]){
	int N;
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
	}
	
	vector<char> sequ;
	
	vector<char> queryVector = queryToVector(f3);
	map<char,int> map = create_map();
	int Nseq = search(map, f2, queryVector, sequ);
	return 0;
};

void test(ifstream& sequenceDB){
	vector<int> sequence;
	char c;
	int i =0;
	while(i<15){
		sequenceDB.read((char *)&c, sizeof(char));
		sequence.push_back((int)c);
		++i;
		cout<<(int)c<<endl;
	}
};




int search(const map<char,int>& map, ifstream& sequenceDB, const vector<char>& vec, vector<char>& se){
	vector<int> sequence;
	char c;
	int i = 1;
	int sequenceNumber;
	sequenceDB.seekg(0);
	while(!sequenceDB.eof()){
		sequenceDB.read((char *)&c, sizeof(char));
		sequence.push_back((int)c);
		if(sequence[sequence.size()-1]==0){
			++sequenceNumber;
			bool b = transform(map, sequence, vec, se,i); //vec is query
			++i;
			if(b){
				for(int j = 0; j<se.size(); j++){
					cout<<se[j];
					}
				auto end = std::chrono::steady_clock::now();
				double elapsed_time_ns = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count());
				cout<<endl;
				cout<<"Elapsed time (s): " << elapsed_time_ns /1e9<< endl;
				cout<<"Sequence Number : "<< sequenceNumber<<endl;
				return sequenceNumber;
				
			}
			else{
				sequence.clear();
				}
		}
	}

};

bool transform(const map<char,int>& m, const vector<int>& v, const vector<char>& vecto, vector<char>& seq, int i){
	vector<char> stringSequence;
	for(int j = 0;j<v.size()-1;j++){
		for(map<char,int>::const_iterator itr = m.begin(); itr!=m.end(); itr++){
			if(itr->second==v[j]){
				stringSequence.push_back(itr->first);break;
			}
		}
	}
	if(stringSequence.size()==vecto.size()){
		if(compare( stringSequence, vecto, seq)){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
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

bool compare(const vector<char>& s, const vector<char>& q, vector<char>& se){
	bool b = false;
	if(s==q){
		cout<<"ok"<<endl;
		se = q;
		b=true;
	}
	return b;
}
