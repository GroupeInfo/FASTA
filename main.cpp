#include <iostream>
#include <string>
#include <fstream>
//#include <map>
#include <vector>
#include <iterator>
#include "database.h"
#include "database.cpp"
#include <ctime>
#include <chrono>


int main(int argc, char* argv[]) {
	
	char* fpin=create_buffer_bin(argv[1]);
	char* fphr=create_buffer_bin(argv[2]);
	char* fpsq=create_buffer_bin(argv[3]);
	char* fquery=create_buffer_bin(argv[4]);
	
	if (*fpin != NULL) {
		std::cout<< "Error opening pin file" <<std::endl
		exit(1)
	}
	
	if (*fphr != NULL) {
		std::cout<< "Error opening phr file" <<std::endl
		exit(1)
	}
	
	if (*fpsq != NULL) {
		std::cout<< "Error opening psq file" <<std::endl
		exit(1)
	}
	
	if (*fquery != NULL) {
		std::cout<< "Error opening psq file" <<std::endl
		exit(1)
	}
	
	database pin(fpin);
	database phr(fphr);
	database psq(fpsq);
	database query(fpsq);
	
	pin.dopin();
	vect<char> queryVector = query.doquery();
	phr.dophr(&queryVector);
	
	string psq.dopsq(pin.getSequencesNumber(), pin.getHeaderOffsetTable());
	
	
}
