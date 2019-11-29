CC=g++

all: handleDb.o
	$(CC) handleDb.o queryFinder.cpp -o queryFinder
handleDb.o: handleDb.cpp
	$(CC) -c handleDb.cpp
clean:
	rm *.o

#uniprot_sprot.fasta.pin uniprot_sprot.fasta.psq uniprot_sprot.fasta.phr P00533.fasta pour l'execution
	


