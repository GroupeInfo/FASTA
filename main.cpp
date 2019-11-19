#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Bitmap.h"
#define BINSEPARATOR 8
using namespace std;

void printout(const string& s, ofstream& out);
void transform(const map<string, string>& m, const string& c, string& s);
string dostuff(const map<string,string>& liste, ifstream& finput, ofstream& foutput);
bool compare( ifstream& database, string query);

int main(int argc, char* argv[]){
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile;
	outFile.open(argv[2]);
	ifstream fileIn;
	fileIn.open(argv[3]);
	map<string,string> Bitmap = create_Bitmap();
	
	if(inFile.fail() || outFile.fail() || fileIn.fail()){
		cerr<< "Error Opening file" << endl;
		exit(1);
		}
	string q = dostuff(Bitmap,inFile, outFile);
	
	ifstream bitFile;
	bitFile.open(argv[2]);
	bool foo = compare(fileIn,q);
	cout<<foo<<endl;
	return 0;
}



void transform(const map<string,string>& m, const string& c, string& s){
	for(map<string,string>::const_iterator itr = m.begin(); itr!=m.end(); itr++){
		if(itr->first==c){
			s.append(itr->second);
		}															
	}
};

void printout(const string& s, ofstream& out){
	out<<s<<endl;
	out.close();
	}

string dostuff(const map<string,string>& liste, ifstream& finput, ofstream& foutput){
		char ch;
		string str ="";
		while( !finput.eof()){
			finput >> ch;
			string sh ="";
			sh.append(1,ch);
			transform(liste, sh, str);
			}
		finput.close();
		printout(str,foutput);
		//cout<<str<<endl;
		return str;
}

bool compare(ifstream& database, string query){
	char c;
	int bin[150];
	int counter = 0;
	int* pa = NULL;
	int a = 0;
	while( !database.eof()){
		++counter;
		database >> c;
		int binary = (int)c;
		bin[counter] = binary;
		pa = &bin[counter];
		if(counter>=BINSEPARATOR){
			for(int i =0; i<BINSEPARATOR;++i){
				if(*(pa-i)== 0){
					++a;
				}
			}
		}
		if(a==8){
			int sequence_length = counter-BINSEPARATOR-1;
			string s ="";
			for(int j = 0;j<sequence_length;j++){
				s.append(1,bin[j]);
			}
			if(s==query){
				return true;
			}
			else{
				counter = 0;
				}
			
		}
		else{
			a=0;
		}
	}
}

	




