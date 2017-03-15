/*
 * utils.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */
#include "utils.h"

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
 *
 */
std::string parse_regex_content(std::string str){
	size_t pos = str.find('*');
	if (pos == std::string::npos)
		pos = str.find('+');
	assert (pos != std::string::npos);

	return str.substr(1, pos - 2);
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
	for (std::set<std::string>::iterator it = l.begin(); it != l.end(); ++it){
		__debugPrint(logFile, "%s\n", it->c_str());
	}
	__debugPrint(logFile, "\n");
}

void displayListString(std::map<std::string, int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (std::map<std::string, int>::iterator it = l.begin(); it != l.end(); ++it){
		__debugPrint(logFile, "%s\n", it->first.c_str());
	}
	__debugPrint(logFile, "\n");
}


void displayListString(std::vector<std::string> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (std::vector<std::string>::iterator it = l.begin(); it != l.end(); ++it){
		__debugPrint(logFile, "%s\n", it->c_str());
	}
	__debugPrint(logFile, "\n");
}

void displayListNumber(std::set<int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (std::set<int>::iterator it = l.begin(); it != l.end(); ++it) {
		__debugPrint(logFile, " %d,", *it);
	}
	__debugPrint(logFile, "\n");
}

void displayListNumber(std::vector<int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (std::vector<int>::iterator it = l.begin(); it != l.end(); ++it) {
		__debugPrint(logFile, " %d,", *it);
	}
	__debugPrint(logFile, "\n");
}
