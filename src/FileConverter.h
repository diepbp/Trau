/*
 * FileConverter.h
 *
 *  Created on: Dec 15, 2016
 *      Author: diepbp
 */

#ifndef FILECONVERTER_H_
#define FILECONVERTER_H_

#include "utils.h"
#include <regex>


static std::map<char, int> ENCODEMAP{
	{'"', 'A'},
	{'\\', 'B'},
	{'?', 'D'},
	{'|', 'E'},
	{'[', 'F'},
	{']', 'G'},
	{'(', 'H'},
	{')', 'J'},
	{';', 'K'},
	{'_', 'L'},
	{'~', 'M'},
	{'!', 'N'},
	{'@', 'P'},
	{'#', 'Q'},
	{'%', 'R'},
	{'^', 'S'},
	{'&', 'T'},
	{'*', 'U'},
	{'+', 'V'},
	{'\t', 'X'}
};

static std::map<int, int> DECODEMAP{
	{'A', '"'},
	{'B', '\\'},
	{'D', '?'},
	{'E', '|'},
	{'F', '['},
	{'G', ']'},
	{'H', '('},
	{'J', ')'},
	{'K', ';'},
	{'L', '_'},
	{'M', '~'},
	{'N', '!'},
	{'P', '@'},
	{'Q', '#'},
	{'R', '%'},
	{'S', '^'},
	{'T', '&'},
	{'U', '*'},
	{'V', '+'},
	{'X', '\t'}
};

template< typename T >
std::string int_to_hex( T i );

/*
 * Create a new string from tokens
 */
std::string concatTokens(std::vector<std::string> tokens);

/*
 * For all string variables
 * Change var name: xyz --> len_xyz
 * and change var type: string -> int
 */
std::string redefineStringVar(std::string var);

std::string redefineOtherVar(std::string var, std::string type);

/*
 * (Indexof v1 v2) --> ....
 */
void updateIndexOf(std::string &s,
		std::map<std::string, std::string> rewriterStrMap);

/*
 * (LastIndexof v1 v2) --> ....
 */
void updateLastIndexOf(std::string &s,
		std::map<std::string, std::string> rewriterStrMap);

/*
 * (EndsWith v1 v2) --> ....
 */
void updateEndsWith(std::string &s,
		std::map<std::string, std::string> rewriterStrMap);

/*
 * (StartsWith v1 v2) --> ....
 */
void updateStartsWith(std::string &s,
		std::map<std::string, std::string> rewriterStrMap);

/*
 * = x (Replace ...) --> true
 */
void updateReplace(std::string &s,
		std::map<std::string, std::string> rewriterStrMap);

/*
 * = x (ReplaceAll ...) --> true
 */
void updateReplaceAll(std::string &s,
		std::map<std::string, std::string> rewriterStrMap);

/*
 * (implies x) --> (implies false x)
 */
void updateImplies(std::string &s);

/*
 * (RegexIn ...) --> TRUE
 */
void updateRegexIn(std::string &s);

/*
 * (Contain v1 v2) --> TRUE || FALSE
 */
void updateContain(std::string &s, std::map<std::string, bool> containStrMap);

/*
 * (Substring a b c) --> c
 */
void updateSubstring(std::string &s);

/*
 * ToUpper --> len = len
 */
void updateToUpper(std::string &s);

/*
 * ToLower --> len = len
 */
void updateToLower(std::string &s);

/*
 * Concat --> +
 */
void updateConcat(std::string &s);

/*
 * Length --> ""
 */
void updateLength(std::string &s);

/*
 * "abcdef" --> 6
 */
void updateConst(std::string &s, std::set<std::string> constList);

/*
 * (Str2Regex x)--> = | x |
 */
void updateStr2Regex(std::string &str);

/*
 *
 */
void updateRegexStar(std::string &str, int &regexCnt);

/*
 *
 */
void updateRegexPlus(std::string &str, int &regexCnt);

/*
 * xyz --> len_xyz
 */
void updateVariables(std::string &s, std::vector<std::string> strVars);

/*
 * contain a string variable
 */
bool strContaintStringVar(std::string notStr, std::vector<std::string> strVars);

/*
 *
 */
void checkAssignWellForm(std::string &s);

/*
 * "abc123" 			--> 6
 * Concat abc def --> + len_abc len_def
 * Length abc 		--> len_abc
 */
void customizeLine_ToCreateLengthLine(
		std::string str,
		std::vector<std::string> &strVars,
		bool handleNotOp,
		std::map<std::string, std::string> rewriterStrMap,
		int &regexCnt,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints,
		std::vector<std::string> &notConstraints);

/*
 * Replace special const in constraints
 */
std::string customizeLine_removeSpecialChars(std::string str);

/*
 * Replace special const in constraints
 */
std::string customizeLine_replaceConst(std::string str, std::set<std::string> &constStr);

/*
 * read SMT file
 */
void rewriteFileSMTToRemoveSpecialChar(std::string inputFile, std::string outFile);

/*
 * read SMT file
 */
void rewriteFileSMTToReplaceConst(std::string inputFile, std::string outFile);

/*
 * "GrammarIn" --> some new vars, some new constraints
 */
void rewriteGRM(std::string s,
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		int &newVars,
		std::vector<std::string> &definitions,
		std::vector<std::string> &constraints);
/*
 * replace the CFG constraint by the regex constraints
 */
void rewriteGRM_toNewFile(
		std::string inputFile,
		std::string outFile,
		std::map<std::string, std::vector<std::vector<std::string>>> equalitiesMap,
		std::map<std::string, std::string> constMap);

/*
 * read SMT file
 * convert the file to length file & store it
 */
void convertSMTFileToLengthFile(std::string inputFile, bool handleNotOp,
		std::map<std::string, std::string> rewriterStrMap,
		int &regexCnt,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints,
		std::vector<std::string> &notConstraints);

/*
 * read SMT file
 * add length constraints and write it
 */
void addConstraintsToSMTFile(
		std::string inputFile,
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::vector<std::string> lengthConstraints,
		std::string outFile);

#endif /* FILECONVERTER_H_ */
