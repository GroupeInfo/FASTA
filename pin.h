#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef unsigned char BYTE; 

vector<BYTE> readFile(const char* filename);

int read_int32(const std::vector<BYTE>& data, int& index);

string read_string(const std::vector<BYTE>& data, int& index, int characters);

int read_int64(const vector<BYTE>& data, int& index);

int* read_int32_array(const std::vector<BYTE>& data, int& index, int numbers);