#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
	
	if (argc != 6) { // argv[0] est le nom de la fonction
		cout << "5 arguments attendus : [database] [query_protein] [blosum62_matrix] [gap_penalty] [extend_gap_penalty]" << endl;
		return EXIT_FAILURE;
	}
	
	char* database_path = argv[1];
	char* protein_path = argv[2];
	string blosum_path = argv[3]; 
	int penalty = atoi(argv[4]);
	int ext_penalty = atoi(argv[5]);
	
	Database data = Database(database_path);
	
	Query query;
	query.loadFromFile(protein_path);
	cout << "===== Query Protein =====" << endl;
	query.print();
	cout << "=========================" << endl;
	cout << "\n" << endl;
	
	
	int nbrSequences = data.getNbrSequences();
	vector<Protein> proteines; // contient toutes les proteines
	proteines.resize(nbrSequences); // nbrSequence = max(index)
	
	return 0;
}
