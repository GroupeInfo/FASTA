#include <vector>
#include <string>

using std::vector;
using std::string;

class ScoreMatrix {
	private :
		int nbrCols; 
		string aminoAcids;
	public :
		ScoreMatrix();
		ScoreMatrix(const string & filename, int nbrCols = 27);
		string removeSpaces(string input);
	
};
