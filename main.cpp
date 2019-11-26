#include <iostream>
#include "pin.h"
using namespace std;

int main()
{
	//pinStuff("uniprot_sprot.fasta.pin");
	vector<BYTE> data = readFile("uniprot_sprot.fasta.pin");
	int index = 0;
	int version = read_int32(data, index);
	int database_type = read_int32(data, index);
	int title_length = read_int32(data, index);
	string title = read_string(data, index, title_length);
	int timestamp_length = read_int32(data, index);
	string timestamp = read_string(data, index, timestamp_length);
	int number_of_sq = read_int32(data, index);
	int residue_count = read_int64(data, index);
	int max_sq = read_int32(data, index);
	/*int* header_offset_table = read_int32_array(data, index, number_of_sq+1);
	int* sequence_offset_table = read_int32_array(data, index, number_of_sq+1);*/


	cout << "version " << version <<endl;
	cout << "Database Type " << database_type << endl;
	cout << "Title length " << title_length << endl;
	cout << "The title is " << title << endl;
	cout << "The timestamp length " << timestamp_length << endl;
	cout << "The timestamp length is " << timestamp << endl;
	cout << "The number of sequeces is  " << number_of_sq << endl;
	cout << "The residue count is  " << residue_count << endl;
	cout << "The length of the longest sequence is  " << max_sq << endl;

	/*for (int i = 0; i < number_of_sq+1; i++) {
		cout << sequence_offset_table[i] << endl;	
	}*/
	
	return 0;
}