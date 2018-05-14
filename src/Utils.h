/*
 * utils.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef UTILS_H_
#define UTILS_H_

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

#include "FileUtils.h"
#include "TimeLapse.h"
#include "antlr4-runtime.h"
#include "antlrParser/SMTLIB2Lexer.h"
#include "antlrParser/SMTLIB2Parser.h"
#include "antlrParser/SMTLIB2ParserBaseVisitor.h"
#include "antlrParser/SMTLIB2ParserBaseListener.h"
#include "antlrParser/SMTLIB2ScriptListener.h"
#include "antlrParser/SMTLIB2TermListener.h"
#include "antlrParser/SMTLIB26Lexer.h"
#include "antlrParser/SMTLIB26Parser.h"
#include "antlrParser/SMTLIB26ParserBaseVisitor.h"
#include "antlrParser/SMTLIB26ParserBaseListener.h"
#include "antlrParser/SMTLIB26ScriptListener.h"
#include "antlrParser/SMTLIB26TermListener.h"

#define DEBUGLOG 1
#define REMOVINGLOG 1
#define NUM_THREADS	1
#define FLATMAX 100;
#define PMAX 50 // size of a flat
#define QMAX 2 // number of flats
#define QCONSTMAX 2 // number of flats for const
#define SPLIT_LOWER_BOUND 3
#define CONNECTSIZE 300

#define Z3_PATH "z3 "
#define VERIFIER "verifier/run.py "

#ifdef DEBUGLOG
#define __debugPrint(_fp, _format, ...) { fprintf( (_fp), (_format), ##__VA_ARGS__); fflush( (_fp) ); }
#define __print(_format, ...) { fprintf( logfile, (_format), ##__VA_ARGS__); fflush( (_fp) ); }
#define __debugPrintAxiom(_fp, _format, ...) { fprintf( (_fp), (_format), ##__VA_ARGS__); fflush( (_fp) ); }
#define printZ3Node(t, n) {__printNode( (t), (n));}
#define printZ3NodeAxiom(t, n) {__printNodeAxiom( (t), (n));}
#else
#define __debugPrint(_fp, _format, ...) {}
#define __print(_format, ...) {}
#define printZ3Node(t, n) {}
#endif

#define LENGTH 1
#define CONCAT 2
#define SUBSTRING 3
#define INDEXOF 4
#define LASTINDEXOF 5
#define STARTSWITH 6
#define ENDSWITH 7
#define TOUPPER 8
#define TOLOWER 9
#define REPLACE 10
#define REPLACEALL 11
#define CONTAINS 12
#define CHARAT 13
#define STR2REG 14
#define REGEXSTAR 15
#define REGEXPLUS 16
#define REGEXCHARRANGE 17
#define REGEXIN 18
#define REGEXUNION 19
#define REGEXCONCAT 20
#define REGEXALL 21
#define REGEXALLCHAR 22
#define REGEXNONE 23

const static std::map<int, std::string> languageMap20 = {
	{LENGTH, "Length"},
	{CONCAT, "Concat"},
	{SUBSTRING, "Substring"},
	{INDEXOF, "Indexof"},
	{LASTINDEXOF, "LastIndexof"},
	{STARTSWITH, "StartsWith"},
	{ENDSWITH, "EndsWith"},
	{TOUPPER, "ToUpper"},
	{TOLOWER, "ToLower"},
	{REPLACE, "Replace"},
	{REPLACEALL, "ReplaceAll"},
	{CONTAINS, "Contains"},
	{CHARAT, "CharAt"},
	{STR2REG, "Str2Reg"},
	{REGEXSTAR, "RegexStar"},
	{REGEXPLUS, "RegexPlus"},
	{REGEXCHARRANGE, "RegexCharRange"},
	{REGEXIN, "RegexIn"},
	{REGEXUNION, "RegexUnion"},
	{REGEXCONCAT, "RegexConcat"},
	{REGEXALL, "re.all"},
	{REGEXALLCHAR, "re.allchar"},
	{REGEXNONE, "re.none"}
};

const static std::map<int, std::string> languageMap25 = {
	{LENGTH, "str.len"},
	{CONCAT, "str.++"},
	{SUBSTRING, "str.substr"},
	{INDEXOF, "str.indexof"},
	{LASTINDEXOF, "LastIndexof"},
	{STARTSWITH, "str.prefixof"},
	{ENDSWITH, "str.suffixof"},
	{TOUPPER, "ToUpper"},
	{TOLOWER, "ToLower"},
	{REPLACE, "str.replace"},
	{REPLACEALL, "ReplaceAll"},
	{CONTAINS, "str.contains"},
	{CHARAT, "str.at"},
	{STR2REG, "str.to.re"},
	{REGEXSTAR, "re.*"},
	{REGEXPLUS, "re.+"},
	{REGEXCHARRANGE, "re.range"},
	{REGEXIN, "str.in.re"},
	{REGEXUNION, "re.union"},
	{REGEXCONCAT, "re.++"},
	{REGEXALL, "re.all"},
	{REGEXALLCHAR, "re.allchar"},
	{REGEXNONE, "re.none"}
};

const static char ESCAPECHAR20 = '\\';
const static char ESCAPECHAR25 = '"';

#define TRUESTR "true"
#define FALSETR "false"
#define LENPREFIX "len_"
#define ARRPREFIX "arr_"
#define ZERO "0"
#define REGEXSUFFIX "_100"

struct TokenElement{
    TokenElement(int _lineNo, std::string _content, std::string _type) : lineNo(_lineNo), content(_content), type(_type){}

    int lineNo;
    std::string content;
    std::string type;
};

struct StringOP{
	std::string name = "";
	std::string arg01 = "";
	std::string arg02 = "";
	std::string arg03 = "";

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

	bool operator()(const StringOP& a) const{
		if (name.length() > 0)
			if (name.compare(a.name) != 0)
				return false;

		if (arg01.length() > 0)
			if (arg01.compare(a.arg01) != 0)
				return false;

		if (arg02.length() > 0)
			if (arg02.compare(a.arg02) != 0)
				return false;

//		if (arg03.length() > 0)
//			if (arg03.compare(a.arg03) != 0)
//				return false;

		return true;
	}

	bool operator ==(const StringOP& a) const{
		if (name.length() > 0)
			if (name.compare(a.name) != 0)
				return false;

		if (arg01.length() > 0)
			if (arg01.compare(a.arg01) != 0)
				return false;

		if (arg02.length() > 0)
			if (arg02.compare(a.arg02) != 0)
				return false;

//		if (arg03.length() > 0)
//			if (arg03.compare(a.arg03) != 0)
//				return false;

		return true;
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

inline bool operator <(StringOP const& x, StringOP const& y) {
	int b0 = x.name.compare(y.name);

	if (b0 != 0)
		return b0 < 0;

	int b1 = x.arg01.compare(y.arg01);

	if (b1 != 0)
		return b1 < 0;

	int b2 = x.arg02.compare(y.arg02);

	if (b2 != 0)
		return b2 < 0;

//	int b3 = x.arg03.compare(y.arg03);
//
//	if (b3 != 0)
//		return b3 < 0;

    return false;
}

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
std::vector<std::pair<std::string, int>> parseTerm20(std::string term);

/*
 *
 */
std::vector<std::vector<std::pair<std::string, int>>> parseFile20(std::string file);

/*
 *
 */
std::vector<std::pair<std::string, int>> parseTerm26(std::string term);

/*
 *
 */
std::vector<std::vector<std::pair<std::string, int>>> parseFile26(std::string file);

/*
 *
 */
std::vector<unsigned> sort_indexes(const std::vector<std::pair<std::string, int>> &v);

/*
 * (a)|(b) --> a|b
 */
std::set<std::string> extendComponent(std::string s);

/*
 * (a) --> a
 */
void removeExtraParentheses(std::string &s);

/*
 *
 */
bool isRegexStr(std::string str);


/*
 *
 */
bool isUnionStr(std::string str);

/*
 *
 */
bool isConstStr(std::string str);

/*
 *
 */
std::string createEqualConstraint(std::string x, std::string y);

/*
 *
 */
std::string createLessEqualConstraint(std::string x, std::string y);

/*
 *
 */
std::string createLessConstraint(std::string x, std::string y);

/*
 *
 */
std::string createPlusOperator(std::string x, std::string y);

/*
 *
 */
std::string createPlusOperator(std::vector<std::string> list);

/*
 *
 */
std::string createSelectConstraint(std::string arr, std::string at);

/*
 *
 */
std::string createModOperator(std::string x, std::string y);

/*
 *
 */
std::string createNotOperator(std::string x);

/*
 *
 */
std::string createAssert(std::string x);

/*
 *
 */
std::string createArrayDefinition(std::string x);

/*
 *
 */
std::string createIntDefinition(std::string x);

#endif /* UTILS_H_ */
