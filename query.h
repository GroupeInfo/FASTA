#include <vector>
#include <string>
#include <iostream>
#include "protein.h"
using std::string;
using std::vector;
class Query : public Protein{
	
	private :
		string decodeQuery();
	public :
	
		Query();
		Query(char* sequence, int length, string header);
		~Query();
		
		void loadFromFile(const string filename);
		char getChar(char letter);
		int getInt(char letter);
		void print(std::ostream & out = std::cout);
};
