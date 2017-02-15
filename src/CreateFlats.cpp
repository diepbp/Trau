//============================================================================
// Name        : CreateFlats.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <stdio.h>      /* printf */
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <assert.h>

#define MAX_BASE62_LENGTH 62

const char lookUpTable[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
  'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

std::string ConvertToBase( int integer, int base )
{
   char res[MAX_BASE62_LENGTH];
   char* pWritePos = res;
   int leftOver = integer;
   while( leftOver )
      {
         const int newLeftOver = leftOver / base;
         int digit62     = leftOver - (base * newLeftOver);
         *pWritePos      = lookUpTable[digit62];
         pWritePos++;

         leftOver        = newLeftOver;
      }
   *pWritePos = 0;
   return std::string( res );
}

std::map<char, int> createMapLookUpTable(){
	std::map<char, int> ret;
	for (int i = 0; i < MAX_BASE62_LENGTH; i++){
		ret[lookUpTable[i]] = i;
	}
	return ret;
}

std::string fillUp(std::string s, int len){
	bool same = true;
	for(int i = (int)s.length(); i < len; ++i)
		s = s + '0';
	for(unsigned int i = 1; i < s.length(); ++i)
		if (s[i] != s[0])
			same = false;

	if (same)
		s = std::string(1, s[0]);

	return s;
}

std::string fillWord(std::string s, int len){

	for(int i = (int)s.length(); i < len; ++i)
		s = s + '0';

	for(unsigned int i = 1; i < s.length(); ++i)
			if (s[i] == s[i-1])
				return "";
	return s;
}

std::set<std::string> createFlat(int p, std::map<int, char> charSet) {
	std::set<std::string> ret;

	unsigned int size = charSet.size();
	for (int i = 1; i <= p; ++i) {
		int num = pow(size, i);
		for (int j = 0; j < num; ++j){
			std::string s = ConvertToBase(j, size);
			s = fillUp(s, i);
			std::string ss;

			for(unsigned k = 0; k < s.size(); ++k)
				ss = ss + charSet[s[k] - '0'];

			ret.insert(ss);
		}
	}
	return ret;
}

std::set<std::string> createWord(int q, std::map<int, std::string> wordMap, std::map<char, int> mapLookUpTable) {
	std::cout << "wordMap: " << wordMap.size() << " vs " << q << std::endl;
	std::set<std::string> ret;
	unsigned int size = wordMap.size();

	int num = pow(size, q);
	for (int j = 0; j < num; ++j){
		std::string s = ConvertToBase(j, size);
		s = fillWord(s, q);

		if (s.size() == 0)
			continue;

//		std::cout << s << std::endl;
		std::string ss;

		for(unsigned k = 0; k < s.size(); ++k)
			ss = ss + "(" + wordMap[mapLookUpTable[s[k]]] + ")*";

		ret.insert(ss);
	}
	return ret;
}

void printTest(std::set<std::string> s){
	for(std::set<std::string>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << "Size: " << s.size() << std::endl;
}

std::set<std::string> createFlats(int p, int q, std::set<char> charSet){
	std::map<char, int> mapLookUpTable = createMapLookUpTable();
	int cnt = 0;
	std::map<int, char> charMap;
	for(std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it)
		charMap[cnt++] = *it;

	std::set<std::string> aFlat = createFlat(p, charMap);
//	printTest(aFlat);

	assert(aFlat.size() < 62);

	cnt = 0;
	std::map<int, std::string> wordMap;
	for(std::set<std::string>::iterator it = aFlat.begin(); it != aFlat.end(); ++it)
		wordMap[cnt++] = *it;

	return createWord(q, wordMap, mapLookUpTable);
}
