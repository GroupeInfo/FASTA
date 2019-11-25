#include <iostream>
#include <string>
#include <map>
//#include "handleDb.h"
using namespace std;

map<char,int> create_map()
{
	pair<map<char,int>::iterator,bool> ret;
	map<char,int> map;
	//On essaye d'insérer le mot "test" avec la valeur 10.
	ret=map.insert(pair<char,int>('-',0));//1
	ret=map.insert(pair<char,int>('A',1));//1
	ret=map.insert(pair<char,int>('B',2));//2
	ret=map.insert(pair<char,int>('C',3));//3
	ret=map.insert(pair<char,int>('D',4));//4
	ret=map.insert(pair<char,int>('E',5));//5
	ret=map.insert(pair<char,int>('F',6));//6
	ret=map.insert(pair<char,int>('G',7));//7
	ret=map.insert(pair<char,int>('H',8));//8
	ret=map.insert(pair<char,int>('I',9));//9
	ret=map.insert(pair<char,int>('J',27));//27
	ret=map.insert(pair<char,int>('K',10));//10
	ret=map.insert(pair<char,int>('L',11));//11
	ret=map.insert(pair<char,int>('M',12));//12
	ret=map.insert(pair<char,int>('N',13));//13
	ret=map.insert(pair<char,int>('O',26));//26
	ret=map.insert(pair<char,int>('P',14));//14
	ret=map.insert(pair<char,int>('Q',15));//15
	ret=map.insert(pair<char,int>('R',16));//16
	ret=map.insert(pair<char,int>('S',17));//17
	ret=map.insert(pair<char,int>('T',18));//18
	ret=map.insert(pair<char,int>('U',24));//24
	ret=map.insert(pair<char,int>('V',19));//19
	ret=map.insert(pair<char,int>('W',20));//20
	ret=map.insert(pair<char,int>('X',21));//21
	ret=map.insert(pair<char,int>('Y',22));//22
	ret=map.insert(pair<char,int>('Z',23));//23
	ret=map.insert(pair<char,int>('*',24));//25*/
	return map;
}

