#include "database.h"
const char table[28]={'-','A','B','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','U','*','O','J'};

//===Constructeur===//
database::database(char* buffer) {
	// Enregistrer aussi les longueurs ?
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
	
	char* text=buffer;
	
}

//===Fonctions===//

uint32_t database::getVersion(){
	return database::version;
}
uint32_t database::getDatabaseType(){
	return database::databaseType;
}
uint32_t database::getTitleLength(){
	return database::titleLength;
}
char* database::getTitleString(){
	return *database::titleString;
}
uint32_t database::getTimestampLength(){
	return database::timestampLength;
}
char* database::getTimestamp(){
	return *database::timestamp;
}

uint32_t database::getSequencesNumber(){
	return database::sequencesNumber;
}

uint32_t database::getResiduesNumber(){
	return residuesNumber;
}

uint32_t database::getMaximumSequence(){
	return maximumSequence;
}

uint32_t* database::getHeaderOffsetTable(){
	return *pHeaderOffsetTable;
}

uint32_t* database::pSequenceOffsetTable(){
	return *pSequenceOffsetTable;
}


void database::dopin() {
	
	//--Version--//
	f.read((char*)&database::version,sizeof(uint32_t));
	version = __builtin_bswap32(version);
	cout<<"The version number is " <<version<<endl;
	
	//--databaseType--//
	f.read((char*)&database::databaseType,sizeof(uint32_t));
	databaseType = __builtin_bswap32(databaseType);
	cout<<"The database type is " << databaseType<<endl;
	
	//--titleLength--//
	f.read((char*)&database::titleLength,sizeof(uint32_t));
	titleLength = __builtin_bswap32(titleLength);
	cout<<"The length of the title string is " << titleLength<<endl;
	
	//--titleString--//
	char titleString[titleLength];
	for(unsigned int i=0; i<titleLength; ++i){
		f.read((char*)&titleString[i], sizeof(char));
	}
	cout<<"The title string is "<<titleString<<endl;
	database::titleString=&titleString;
	
	//--timestampLength--//
	f.read((char*)&database::timestampLength,sizeof(uint32_t));
	timestampLength = __builtin_bswap32(timestampLength);
	cout<<"The length of the timestamp string is " << timestampLength<<endl;
	
	//--timestamp--//
	char timestamp[timestampLength];
	for(unsigned int i=0; i<timestampLength; ++i){
		f.read((char*)&timestamp[i], sizeof(char));
	}
	cout<<"The time of the database creation is "<<timestamp<<endl;
	database::timestamp=&timestamp;
	
	//--sequencesNumber--//
	f.read((char*)&database::sequencesNumber,sizeof(uint32_t));
	sequencesNumber = __builtin_bswap32(sequencesNumber);
	cout<<"The number of sequences in the database is " << sequencesNumber<<endl;
	
	int N = database::sequencesNumber; // Vrai gain ?? Assignation de la variable utile ?
	
	//--residuesNumber--//
	f.read((char*)&database::residuesNumber,sizeof(uint64_t));
	cout<<"The total number of residues in the database is " << residuesNumber<<endl;
	
	//--maximumSequence--//
	f.read((char*)&database::maximumSequence,sizeof(uint32_t));
	MaximumSequence = __builtin_bswap32(MaximumSequence);
	cout<<"The length of the longest sequence in the database is " << MaximumSequence<<endl;
	
	//--headerOffsetTable--//
	uint32_t headerOffsetTable[N+1];
	for(unsigned int i=0; i<N+1; ++i){
		f.read((char*)&HeaderOffsetTable[i], sizeof(uint32_t));
		HeaderOffsetTable[i] = __builtin_bswap32(HeaderOffsetTable[i]);
	}
	database::pHeaderOffsetTable=*HeaderOffsetTable;
	
	//--sequenceOffsetTable--//
	uint32_t sequenceOffsetTable[N+1];
	for(unsigned int i=0; i<N+1; ++i){
		f.read((char*)&sequenceOffsetTable[i], sizeof(uint32_t));
		sequenceOffsetTable[i] = __builtin_bswap32(sequenceOffsetTable[i]);
	}
	database::pSequenceOffsetTable=*sequenceOffsetTable;
}

vector<char> database::doquery() {
	vector<char> vect;
	char ch;
	// read() != EOF ?
	while(!queryFile.eof()) {
		queryFile >> ch;
		vect.push_back(ch);
	}
	vect.pop_back();
	return vect;
}

void database::dophr() {
	char c;
	int i = 0;
	int k = 0;
	while(!sequenceDB.eof()){
		sequenceDB.read((char *)&c, sizeof(char));
		////char ch=transform2(map, (int)c); // ch is the translated c character
		char ch = table[(int c];
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
				auto end = std::chrono::steady_clock::now();
				double elapsed_time_ns = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count());
				cout<<"Elapsed time (s): " << elapsed_time_ns /1e9<< endl;
				return k;
			}
		}
	}
	
}
string database::dopsq(int seqNum, uint32_t headOffTab[]){
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
	/*f.close();
	
	ifstream f4 (argv[4], ios::out|ios ::binary); // Database index file
	
	if(!f4.is_open()){
		cout<<"Impossible d'ouvrir un des fichiers."<<endl;
		exit(1);
	}
	
	vector<char> sequ;
	vector<char> queryVector = queryToVector(f4);
	f4.close();
	
	ifstream f2 (argv[2], ios::out|ios ::binary); // Database index file
	
	if(!f2.is_open()){
		cout<<"Impossible d'ouvrir un des fichiers."<<endl;
		exit(1);
	}
	
	////map<char,int> map = create_map();
	int sequenceNumber = search(table, f2, queryVector, sequenceOffsetTable);
	string str = getName(f3,sequenceNumber,HeaderOffsetTable);
	cout<<"The query corresponds to : "<<str<<endl;
}

vector<char> queryToVector(ifstream& queryFile){
	vector<char> vect;
	char ch;
	while(!queryFile.eof()){
		queryFile >> ch;
		vect.push_back(ch);
	}
	vect.pop_back();
	return vect;
}

int search(const char table[], ifstream& sequenceDB, const vector<char>& vec,uint32_t seqOffTab[]){
	char c;
	int i = 0;
	int k = 0;
	while(!sequenceDB.eof()){
		sequenceDB.read((char *)&c, sizeof(char));
		////char ch=transform2(map, (int)c); // ch is the translated c character
		char ch = table[(int c];
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
				auto end = std::chrono::steady_clock::now();
				double elapsed_time_ns = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count());
				cout<<"Elapsed time (s): " << elapsed_time_ns /1e9<< endl;
				return k;
			}
		}
	}
}*/
