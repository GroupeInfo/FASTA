all : database.o query.o protein.o scorematrix.o threadpool.o main.cpp 
	g++ -Wall -std=c++11 -pthread database.o query.o protein.o threadpool.o  scorematrix.o main.cpp -o gotoh
	
database.o : database.cpp protein.h
	g++ -Wall -std=c++11 -c database.cpp
	
query.o : query.cpp query.h
	g++ -Wall -std=c++11 -c query.cpp

protein.o : protein.cpp 
	g++ -Wall -std=c++11 -c protein.cpp 
	
scorematrix.o : scorematrix.cpp
	g++ -Wall -std=c++11 -c scorematrix.cpp
	
threadpool.o : threadpool.cpp
	g++ -Wall -std=c++11 -pthread -c threadpool.cpp
	
clean :
	rm -rf *.o
