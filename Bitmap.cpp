#include <iostream>
#include <string>
#include <map>
#include "Bitmap.h"
using namespace std;

map<string,string> create_Bitmap()
{
	pair<map<string,string>::iterator,bool> ret;
	map<string,string> Binmap;
	//On essaye d'insérer le mot "test" avec la valeur 10.
	ret=Binmap.insert(pair<string,string>("A","00000001"));//1
	ret=Binmap.insert(pair<string,string>("B","00000010"));//2
	ret=Binmap.insert(pair<string,string>("C","00000011"));//3
	ret=Binmap.insert(pair<string,string>("D","00000100"));//4
	ret=Binmap.insert(pair<string,string>("F","00000101"));//5
	ret=Binmap.insert(pair<string,string>("E","00000110"));//6
	ret=Binmap.insert(pair<string,string>("G","00000111"));//7
	ret=Binmap.insert(pair<string,string>("H","00001000"));//8
	ret=Binmap.insert(pair<string,string>("I","00001001"));//9
	ret=Binmap.insert(pair<string,string>("J","00011011"));//27
	ret=Binmap.insert(pair<string,string>("K","00001010"));//10
	ret=Binmap.insert(pair<string,string>("L","00001011"));//11
	ret=Binmap.insert(pair<string,string>("M","00001100"));//12
	ret=Binmap.insert(pair<string,string>("N","00001101"));//13
	ret=Binmap.insert(pair<string,string>("O","00011010"));//26
	ret=Binmap.insert(pair<string,string>("P","00001110"));//14
	ret=Binmap.insert(pair<string,string>("Q","00001111"));//15
	ret=Binmap.insert(pair<string,string>("R","00010000"));//16
	ret=Binmap.insert(pair<string,string>("S","00010001"));//17
	ret=Binmap.insert(pair<string,string>("T","00010010"));//18
	ret=Binmap.insert(pair<string,string>("U","00011000"));//24
	ret=Binmap.insert(pair<string,string>("V","00010011"));//19
	ret=Binmap.insert(pair<string,string>("W","00010100"));//20
	ret=Binmap.insert(pair<string,string>("X","00010101"));//21
	ret=Binmap.insert(pair<string,string>("Y","00010110"));//22
	ret=Binmap.insert(pair<string,string>("Z","00010111"));//23
	ret=Binmap.insert(pair<string,string>("*","00011001"));//25
	
	/*int counter = 0;
	for(map<string,string>::const_iterator itr = Binmap.begin(); itr!=Binmap.end(); itr++){ 
		cout<<(itr->first)<< " : "<<(itr->second)<<endl;
		++counter;
	}
	
	cout<<"size of the map is : " <<counter<<endl;*/
	return Binmap;
}

