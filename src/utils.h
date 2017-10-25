/*
 * utils.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <assert.h>

#include <stack>
#include <set>
#include <list>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

#include <fst/fstlib.h>

#include <fstream>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

#include "TimeLapse.h"
#include "antlr4-runtime.h"
#include "antlrParser/SMTLIB2Lexer.h"
#include "antlrParser/SMTLIB2Parser.h"
#include "antlrParser/SMTLIB2ParserBaseVisitor.h"
#include "antlrParser/SMTLIB2ParserBaseListener.h"
#include "antlrParser/SMTLIB2ScriptListener.h"
#include "antlrParser/SMTLIB2TermListener.h"

#define DEBUGLOG 1
#define REMOVINGLOG 1
#define NUM_THREADS	1
#define FLATMAX 100;
#define PMAX 50 // size of a flat
#define QMAX 2 // number of flats
#define QCONSTMAX 2 // number of flats for const
#define SPLIT_UNDER_BOUND 3
#define CONNECTSIZE 200

#define Z3_PATH "z3 "
#define VERIFIER "verifier/run.py "

#define TMPDIR "/tmp/fat_str_convert/"

#ifdef DEBUGLOG
#define __debugPrint(_fp, _format, ...) { fprintf( (_fp), (_format), ##__VA_ARGS__); fflush( (_fp) ); }
#define __debugPrintAxiom(_fp, _format, ...) { fprintf( (_fp), (_format), ##__VA_ARGS__); fflush( (_fp) ); }
#define printZ3Node(t, n) {__printNode( (t), (n));}
#define printZ3NodeAxiom(t, n) {__printNodeAxiom( (t), (n));}
#else
#define __debugPrint(_fp, _format, ...) {}
#define printZ3Node(t, n) {}
#endif

struct TokenElement{
    TokenElement(int _lineNo, std::string _content, std::string _type) : lineNo(_lineNo), content(_content), type(_type){}

    int lineNo;
    std::string content;
    std::string type;
};

struct StringOP{
	std::string name;
	std::string arg01;
	std::string arg02;
	std::string arg03;

	StringOP(){

	};

	StringOP(const StringOP& a){
		name = a.name;
		arg01 = a.arg01;
		arg02 = a.arg02;
		arg03 = a.arg03;
	};

	StringOP(std::string _name): name(_name){

	};

	StringOP(std::string _name, std::string _arg01): name(_name), arg01(_arg01) {

	};

	StringOP(std::string _name, std::string _arg01, std::string _arg02): name(_name), arg01(_arg01), arg02(_arg02){

	};

	StringOP(std::string _name, std::string _arg01, std::string _arg02, std::string _arg03): name(_name), arg01(_arg01), arg02(_arg02), arg03(_arg03){

	};

	void setName(std::string _name){
		name = _name;
	}

	void setArg01(std::string _arg01){
		arg01 = _arg01;
	}

	void setArg02(std::string _arg02){
		arg02 = _arg02;
	}

	void setArg03(std::string _arg03){
		arg03 = _arg03;
	}

	bool operator==(StringOP a) const{
		if (name.length() > 0)
			if (name.compare(a.name) != 0)
				return false;
		if (arg01.length() > 0)
			if (arg01.compare(a.arg01) != 0)
				return false;

		if (arg02.length() > 0)
			if (arg02.compare(a.arg02) != 0)
				return false;

		if (arg03.length() > 0)
			if (arg03.compare(a.arg03) != 0)
				return false;

		return true;
	}

	bool operator <(const StringOP& x) const{
	    if (x.name.compare(name) != 0)
	    	return x.name.compare(name) > 0;

	    if (x.arg01.compare(arg01) != 0)
	    	return x.arg01.compare(arg01) > 0;

	    if (x.arg02.compare(arg02) != 0)
	    	return x.arg02.compare(arg02) > 0;

	    if (x.arg03.compare(arg03) != 0)
	    	return x.arg03.compare(arg03) > 0;

	    return false;
	}

	/*
	 *
	 */
	std::string toString(){
		if (arg03.length() > 0)
			return "(" + name + " " + arg01 + " " + arg02 + " " + arg03 + ")";
		else if (arg02.length() > 0)
			return "(" + name + " " + arg01 + " " + arg02 + ")";
		else if (arg01.length() > 0)
			return "(" + name + " " + arg01 + ")";
		else
			return "(" + name + ")";
	}

//	friend bool operator <(const StringOP& x, const StringOP& y);
};

//bool operator <(const StringOP& x, const StringOP& y) {
//    if (x.name.compare(y.name) != 0)
//    	return x.name.compare(y.name) > 0;
//
//    if (x.arg01.compare(y.arg01) != 0)
//    	return x.arg01.compare(y.arg01) > 0;
//
//    if (x.arg02.compare(y.arg02) != 0)
//    	return x.arg02.compare(y.arg02) > 0;
//
//    if (x.arg03.compare(y.arg03) != 0)
//    	return x.arg03.compare(y.arg03) > 0;
//
//    return false;
//}

extern FILE * logFile;
extern FILE * logAxiom;

std::string longestCommonTail(std::string a, std::string b);

std::string longestCommonHead(std::string a, std::string b);

int lcd(int x, int y);

std::vector<std::string> parse_string_language(std::string s, std::string delimiters);

/*
 * (abc)*__XXX -> abc
 */
std::string parse_regex_content(std::string str);

/*
 * (abc)*__XXX -> (abc)*
 */
std::string parse_regex_full_content(std::string str);

std::string getFileNameFromFileDir(std::string fileDir);

void displayListString(std::vector<std::string> l, std::string msg);

void displayListString(std::set<std::string> l, std::string msg);

void displayListString(std::map<std::string, int> l, std::string msg);

void displayListNumber(std::set<int> l, std::string msg);

void displayListNumber(std::vector<int> l, std::string msg);

/*
 *
 */
int findCorrespondRightParentheses(int leftParentheses, std::string str);

/*
 *
 */
int findCorrespondRightParentheses(int leftParentheses, std::vector<std::pair<std::string, int>> tokens);

/*
 * (a) | (b) --> {a, b}
 */
std::vector<std::string> collectAlternativeComponents(std::string str);


/*
 *
 */
std::string orConstraint(std::set<std::string> possibleCases);

/*
 *
 */
std::string orConstraint(std::vector<std::string> possibleCases);

/*
 * create (and constraint01 constraint02 .. constraint0n)
 */
std::string andConstraint(std::vector<std::string> possibleCases);

/*
 *
 */
std::string andConstraint(std::set<std::string> possibleCases);

/*
 *
 */
std::vector<std::pair<std::string, int>> parseTerm(std::string term);

/*
 *
 */
std::vector<std::vector<std::pair<std::string, int>>> parseFile(std::string file);
#endif /* UTILS_H_ */
