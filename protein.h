#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::vector;

class Protein {
	protected :
		char* sequence;
		string header;
		int length;
	
	public :
	
		Protein();
		Protein(char* sequence, int length, string header);
		~Protein();
		char* getSequence() const;
		void setSequence(char* sequence, int length);
		string getHeader();
		void setHeader(string header);
		const char getResidue(int i) const;
		const int size() const;
		void print(std::ostream & out = std::cout);
	
};
