#include "database.h"
#include "scorematrix.h"
#include <algorithm>
#include <iostream>
#include <time.h>

using namespace std;

void gotoh(Database& data, ScoreMatrix& blosum, Query& query, int protIndex, int ext_penalty, int sum_penalty) {
	
	Protein& prot = data.getProtein(protIndex);
	
	//Matrice MxN
	const unsigned int n = query.size(); // Taille max colonne
	const unsigned int m = prot.size(); // Taille max ligne
	
	// ext_penalty = R
	// sum_penalty = Q
	
	int H[m+1];
	int F[m+1];
	
	int H_diag;
	int H_diag_buffer;
	int E;
	int score = 0; // return 0 si H[i,j] toujours < 0
	
	//-Initialisation H et F-//
	// Eviter les pointeurs fous
	for (unsigned int j = 0; j <= m; j++) {
		H[j] = 0;
		F[j] = 0; // Valeur de fin de récurrence de F
	}
	
	for (unsigned int i = 1; i <= n; i++) {
		// Valeurs de fin de récurrence de E et H
		E = 0; // E = E[i,j]
		H_diag = 0; // H_diag = H[i-1,j-1]
		//cout << "H_diag0 = " << H_diag << endl;
		//cout << "E0 = " << E << endl;
		
		for (unsigned int j = 1; j <= m; j++) {
			// E[i,j] = max(H[i,j-1] - Q, E[i,j-1] - R)
			E = max(H[j-1] - sum_penalty,  E - ext_penalty);
			// F[i,j] = max(H[i-1,j] - Q, F[i-1,j] - R)
			F[j] = max(H[j] - sum_penalty, F[j] - ext_penalty);
			
			H_diag_buffer = H[j];
			cout << "H_diag_buffer = " << H_diag_buffer << endl;
			// H[i,j] = max(H[i-1,j-1] + BLOSUM62, E[i,j], F[i,j], 0)
			H[j] = max( max( H_diag + (int) blosum(prot.getResidue(j-1), (int) query.getResidue(i-1)), E ), max( F[j], 0 ));
			
			H_diag = H_diag_buffer; // H[i-1,j-1] sauvé pour la prochaine itération
			
			cout << "H_diag = " << H_diag << endl;
			cout << "E = " << E << endl;
			
			cout << "H[j] = " << H[j] << endl;
			cout << "score = " << score << endl;
			// score = max(H[i,j]) où 0<=i<=n et 0<=j<=m
			if (H[j] > score) {
				score = H[j];
			}
		}
	}
	
}

int main(int argc, char* argv[]) {
	/* utilisation de time_t ou alors compilation en utilisant time lors de l'essais :
	 * time ./gotoh uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1
	 * ou
	 * time ./gotoh newE.fasta P00533.fasta BLOSUM62.txt 11 1 */
	time_t start, end;
	time(&start);
	
	// Vérification Arguments
	if (argc != 6) { // argv[0] est le nom de la fonction
		cout << "5 arguments attendus : [database] [query_protein] [blosum62_matrix] [gap_penalty] [extend_gap_penalty]" << endl;
		return EXIT_FAILURE;
	}
	
	char* database_path = argv[1];
	char* protein_path = argv[2];
	string blosum_path = argv[3]; 
	int penalty = atoi(argv[4]);
	int ext_penalty = atoi(argv[5]);
	
	//== Initialisation Database ==//
	Database data = Database(database_path);
	
	//== Initialisation Query Protein ==//
	Query query;
	query.loadFromFile(protein_path);
	cout << "===== Query Protein =====" << endl;
	query.print();
	cout << "=========================" << endl;
	cout << "\n" << endl;
	
	//== Initialisation Blosum Matrix ==//
	ScoreMatrix blosum = ScoreMatrix(blosum_path);
	
	int sum_penalty = ext_penalty + penalty;
	
	gotoh(Database& data, ScoreMatrix& blosum, Query& query, int protIndex, int ext_penalty, int sum_penalty);
	
	time(&end);
	int t_exec = difftime(end, start);
	cout << "Temps d'éxecution : " << t_exec << " secondes" << endl;
	return 0;
}
