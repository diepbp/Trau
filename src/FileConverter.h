/*
 * FileConverter.h
 *
 *  Created on: Dec 15, 2016
 *      Author: diepbp
 */

#ifndef FILECONVERTER_H_
#define FILECONVERTER_H_

#include "utils.h"

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
 * read SMT file
 * convert the file to length file & store it
 */
void convertSMTFileToLengthFile(std::string inputFile, bool handleNotOp,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints,
		std::vector<std::string> &notConstraints);

/*
 * read SMT file
 * add length constraints and write it
 */
void addLengthConstraintsToSMTFile(std::string inputFile, std::vector<std::string> lengthConstraints, std::string outFile);

void displayListString(std::vector<std::string> l, std::string msg);

void displayListString(std::set<std::string> l, std::string msg);

void displayListNumber(std::set<int> l, std::string msg);

void displayListNumber(std::vector<int> l, std::string msg);
#endif /* FILECONVERTER_H_ */
