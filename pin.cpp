#include <iostream>
#include <fstream>
#include "pin.h"

void pinStuff(char* path) {

	FILE* fp;
	fp = fopen(path, "r");    

	// size of int32
	int int32_size = sizeof(char)*4;
	char str[1000];
	fgets(str, int32_size, fp);
	cout << str << endl;
	int version = atoi(&str[0]);
	cout << version << endl;
}


vector<BYTE> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<BYTE> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

int read_int32(const std::vector<BYTE>& data, int& index)
{
	int a = int((BYTE)(data[0+index])<< 24 |
				(BYTE)(data[1+index])<< 16 |
				(BYTE)(data[2+index])<< 8 |
				(BYTE)(data[3+index]));
	index += 4;
	return a;
}

string read_string(const vector<BYTE>& data, int& index, int characters)
{
	const unsigned char* data_array = &(data[index]);
	string str(reinterpret_cast<char const* >(data_array), characters);
	index += characters;
	return str;
}

int read_int64(const vector<BYTE>& data, int& index)
{
	//verifier la fonction warnings
	int a = int((BYTE)(data[0+index])<< 56 |
				(BYTE)(data[1+index])<< 48 |
				(BYTE)(data[2+index])<< 40 |
				(BYTE)(data[3+index])<< 32 |
				(BYTE)(data[4+index])<< 24 |
				(BYTE)(data[5+index])<< 16 |
				(BYTE)(data[6+index])<< 8 |
				(BYTE)(data[7+index]));
	index += 8;
	return a;
}

int* read_int32_array(const std::vector<BYTE>& data, int& index, int numbers)
{
	int* array = new int[numbers];
	for (int i = 0; i < numbers; i++) {
		int nbr = read_int32(data, index);
		array[numbers] = nbr;
	}
	return array;
}