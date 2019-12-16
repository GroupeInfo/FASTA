#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::vector;

class Protein {
	protected :
		char* sequence;
		string header;
		int length; //length of the sequence
		//return a sequence string in readable format (letters instead of binary)
	
	public :
	
		Protein();
		Protein(char* sequence, int length, string header);
		~Protein();
		//load the header and the sequence of a protein from a fasta file containing only one protein
		char* getSequence() const;
		void setSequence(char* sequence, int length);
		string getHeader();
		void setHeader(string header);
		const char getResidue(int i) const;
