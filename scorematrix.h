#include <vector>
#include <string>

using std::vector;
using std::string;

class ScoreMatrix {
	private :
		vector<int> matrix;
		int nbrCols; 
		vector<char> decoder;
		string aminoAcids;
	public :
	
		ScoreMatrix();
		ScoreMatrix(const string & filename, int nbrCols = 27);
		void createMatrix(const string & filename, int nbrCols, string aminoAcids, int seeker);  
		int decode(char c);
		string removeSpaces(string input);
		//retourne l'entier [i,j] de la matrice
		int &operator()(char i, char j);
	
};
