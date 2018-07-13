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
#define CONNECTINGSIZE 300

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
#define INDEXOF2 24

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
	{REGEXNONE, "re.none"},
	{INDEXOF2, "Indexof2"}
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
	{REGEXNONE, "re.none"},
	{INDEXOF2, "str.indexof2"},
};

const static char ESCAPECHAR20 = '\\';
const static char ESCAPECHAR25 = '"';

#define TRUESTR "true"
#define FALSETR "false"
#define LENPREFIX "len_"
#define ARRPREFIX "arr_"
#define ITERSUFFIX "__iter"
#define ZERO "0"
#define REGEXSUFFIX "_10000"

struct ConstraintSet{
	std::set<std::string> arithmeticConstraints;
	std::set<std::string> stringConstraints;
	std::set<std::string> regularConstraints;
	std::set<std::string> otherConstraints;
};

struct TokenElement{
    TokenElement(int _lineNo, std::string _content, std::string _type) : lineNo(_lineNo), content(_content), type(_type){}

    int lineNo;
    std::string content;
    std::string type;
};

struct StringOP{
	std::string name = "";
	std::vector<StringOP> args;

	StringOP(const StringOP& a){
		name = a.name;
		args = a.args;
	};

	StringOP(){

	};

	StringOP(std::string _name): name(_name){

	};

	StringOP(std::string _name, StringOP arg01): name(_name){
		args.emplace_back(arg01);
	};

	StringOP(std::string _name, StringOP arg01, StringOP arg02): name(_name){
		args.emplace_back(arg01);
		args.emplace_back(arg02);
	};

	StringOP(std::string _name, StringOP arg01, StringOP arg02, StringOP arg03): name(_name){
		args.emplace_back(arg01);
		args.emplace_back(arg02);
		args.emplace_back(arg03);
	};

	StringOP(std::string _name, std::vector<StringOP> _args): name(_name), args(_args) {

	}

	void setName(std::string _name){
		name = _name;
	}

	void addArg(StringOP _arg){
		args.emplace_back(_arg);
	}

	void setArgs(std::vector<StringOP> _args){
		args = _args;
	}

	void setArg(int pos, StringOP _arg){
		assert((int)args.size() > pos);
		args[pos] = _arg;
	}

	bool operator()(const StringOP& a) const{
		if (name.length() > 0)
			if (name.compare(a.name) != 0)
				return false;

		if (args.size() != a.args.size())
			return false;

		for (unsigned i = 0 ; i < args.size(); ++i)
			if (args[i].toString().compare(a.args[i].toString()) != 0)
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

		if (args.size() != a.args.size())
			return false;

		for (unsigned i = 0 ; i < args.size(); ++i)
			if (args[i].toString().compare(a.args[i].toString()) != 0)
				return false;

//		if (arg03.length() > 0)
//			if (arg03.compare(a.arg03) != 0)
//				return false;

		return true;
	}

	/*
	 *
	 */
	StringOP& operator=(StringOP const& copy){
		name = copy.name;
		args = copy.args;
		return *this;
	}

	/*
	 *
	 */
	std::string toString() const{
		if (args.size() == 0)
			return name;
		else if (name.length() > 0){
			std::string tmp = "(" + name;
			for (unsigned i = 0 ; i < args.size(); ++i)
				tmp = tmp + " " + args[i].toString();
			tmp = tmp + ")";
			return tmp;
		}
		else
			return "";
	}

//	friend bool operator <(const StringOP& x, const StringOP& y);
};

inline bool operator <(StringOP const& x, StringOP const& y) {
	int b0 = x.name.compare(y.name);

	if (b0 != 0)
		return b0 < 0;
	if (x.args.size() > 0) {
		std::string tmp01 = x.args[0].toString();
		int b1 = x.args[0].toString().compare(y.args[0].toString());

		if (b1 != 0)
			return b1 < 0;

		if (x.args.size() > 1) {
			int b2 = x.args[1].toString().compare(y.args[1].toString());

			if (b2 != 0)
				return b2 < 0;
		}
	}

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
std::string createMultiplyOperator(std::string x, std::string y);

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

/*
 *
 */
std::string createContainConstraint(std::string x, std::string y);

/*
 *
 */
std::string createStartsWithConstraint(std::string x, std::string y);

/*
 *
 */
std::string createEndsWithConstraint(std::string x, std::string y);

/*
 *
 */
void formatOP(StringOP &opx);

/*
 *
 */
void formatMinusOP(StringOP &opx);

/*
 *
 */
void formatPlusOP(StringOP &opx);

/*
 *
 */
void formatMultiplyOP(StringOP &opx);


#endif /* UTILS_H_ */
