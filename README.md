To align protein sequences, smart ways of comparing have to be developed. 
This program implements a sequence alignment algorithm,  as well as 
mutlithreading. 
It was written by Sacha Verheeke, Cécile Castiaux and Hassan Nehme.

Sources:

[1] M S Farrar - NCBI BLAST Database Format (2010).pdf
[2] T Rognes - Faster Smith-Waterman database searches with inter-sequence SIMD parallelisation.pdf
[3] O Gotoh - An improved algorithm for matching biological subsequences.pdf
[4] T Smith and M Waterman - Identification of common molecular subsequences.pdf

How to start the program?

1)Compilation: make
2)Execution: ./gotoh Database* Query_Sequence BLOSUM_Matrix gap_open_penalty gap_extend_penalty 

For example: 
$./gotoh uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1 

PS: make sure that the following files are in the directory where the program is beeing executed!

1 query sequence file.
2 The database files: pin, psq and phr.
3 BLOSUM matrix file.
