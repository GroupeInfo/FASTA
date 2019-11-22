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
int compare( ifstream& database, string query);

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
	
	//ifstream bitFile;
	//bitFile.open(argv[2]);
	int foo = compare(fileIn,q);
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
		return str;
}

int compare(ifstream& database, string query){
	char c;
	string bin[20];
	int counter = -1;
	int counter2 = 0;
	string* pa = NULL;
	bool foo = false;
	string swr = "";
	while( !database.eof()){
		++counter;
		database >> c;
		swr.append(1,c);
		if(counter==7){
			bin[counter2] = swr;
			pa = &bin[counter2];
			cout<<bin[counter2]<<endl;
			++counter2;
			counter = -1;
			if(swr=="00000000"){
				foo = true;
				}
			swr="";
		}
		if(foo==true){
			int sequence_length = counter2-1;
			string s ="";
			for(int j = 0; j<sequence_length; j++){
				s+=bin[j];
			}
			if(s==query){
				cout<<"wohoooo"<<endl;
				return 1;
			}
			else{
				counter2=0;
				foo = false;
				}
			
		}
	}
}

	




