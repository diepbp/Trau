/*
 * utils.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */
#include "utils.h"

std::string longestCommonTail(std::string a, std::string b){
	unsigned int posA = a.length() - 1;
	unsigned int posB = b.length() - 1;
	std::string ret = "";
	while(posA >= 0 && posB >= 0){
		if (a[posA] == b[posB]){
			ret = a[posA] + ret;
			posA--;
			posB--;
		}
		else break;
	}
	return ret;
}

std::string longestCommonHead(std::string a, std::string b){
	unsigned int posA = 0;
	unsigned int posB = 0;
	std::string ret = "";
	while(posA < a.length() && posB < b.length()){
		if (a[posA] == b[posB]){
			ret = ret + a[posA];
			posA++;
			posB++;
		}
		else break;
	}
	return ret;
}

int lcd(int x, int y) {
	int x1 = x;
	int y1 = y;
	if (x < y) {
		x1 = y;
		y1 = x;
	}

	int r = y1;
	while (r != 0) {
		r = x1 % y1;
		x1 = y1;
		y1 = r;
	}

	return x * y / x1;
}
/*
 * string to tokens
 */
std::vector<std::string> parse_string_language(std::string s, std::string delimiters)
{
	std::vector<std::string> result;
	char *str=new char[s.size()+1];
	str[s.size()]=0;
	memcpy(str, s.c_str(), s.size());

	char* pch;
	pch = strtok(str, delimiters.c_str());

	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok(NULL, delimiters.c_str());
	}

	return result;
}

/*
 * (abc)*__XXX -> abc
 */
std::string parse_regex_content(std::string str){
	size_t pos = str.find('*');
	if (pos == std::string::npos)
		pos = str.find('+');
	assert (pos != std::string::npos);

	return str.substr(1, pos - 2);
}

/*
 * (abc)*__XXX -> (abc)*
 */
std::string parse_regex_full_content(std::string str){
	size_t pos = str.find('*');
	if (pos == std::string::npos)
		pos = str.find('+');
	assert (pos != std::string::npos);

	return str.substr(0, pos + 1);
}

/*
 *
 */
std::string getFileNameFromFileDir(std::string fileDir){
	/*get fileName from fileDir */
	std::string fileName = "";
	for (int i = fileDir.length() - 1; i >= 0; --i)
		if (fileDir[i] != '/')
			fileName = fileDir[i] + fileName;
		else
			break;
	return fileName;
}

void displayListString(std::set<std::string> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& s : l){
		__debugPrint(logFile, "%s\n", s.c_str());
	}
	__debugPrint(logFile, "\n");
}

void displayListString(std::map<std::string, int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& s : l){
		__debugPrint(logFile, "%s\n", s.first.c_str());
	}
	__debugPrint(logFile, "\n");
}


void displayListString(std::vector<std::string> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& s : l){
		__debugPrint(logFile, "%s\n", s.c_str());
	}
	__debugPrint(logFile, "\n");
}

void displayListNumber(std::set<int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& num : l){
		__debugPrint(logFile, " %d,", num);
	}
	__debugPrint(logFile, "\n");
}

void displayListNumber(std::vector<int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& num : l){
		__debugPrint(logFile, " %d,", num);
	}
	__debugPrint(logFile, "\n");
}

/*
 *
 */
int findCorrespondRightParentheses(int leftParentheses, std::string str){
	assert (str[leftParentheses] == '(');
	int counter = 1;
	for (unsigned int j = leftParentheses + 1; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
			if (counter == 0){
				return j;
			}
		}
		else if (str[j] == '('){
			counter++;
		}
	}
	return -1;
}

/*
 * (a) | (b) --> {a, b}
 */
std::vector<std::string> collectAlternativeComponents(std::string str){
	std::vector<std::string> result;
	int counter = 0;
	unsigned int startPos = 0;
	for (unsigned int j = 0; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
		}
		else if (str[j] == '('){
			counter++;
		}
		else if ((str[j] == '|' || str[j] == '~') && counter == 0) {
			result.push_back(str.substr(startPos, j - startPos));
			startPos = j + 1;
		}
	}
	if (startPos != 0)
		result.push_back(str.substr(startPos, str.length() - startPos));
	else {
		assert (str.find('|') == std::string::npos && str.find('~') == std::string::npos);
		return {str};
	}

	return result;
}

/*
 *
 */
std::string orConstraint(std::set<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(or ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = *possibleCases.begin();
	}
	return result;
}

/*
 *
 */
std::string orConstraint(std::vector<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(or ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = *possibleCases.begin();
	}
	return result;
}


/*
 * create (and constraint01 constraint02 .. constraint0n)
 */
std::string andConstraint(std::vector<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(and ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = possibleCases[0];
	}
	return result;
}

/*
 *
 */
std::string andConstraint(std::set<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(and ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = *possibleCases.begin();
	}
	return result;
}
