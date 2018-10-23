//============================================================================
// Name        : FlatAutomaton.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iomanip>

#include "GrmOverApprox.h"
#include "GrmUnderApprox.h"
#include "StringTheory.h"
#include "Config.h"
std::map<std::string, int> variables;
std::vector<std::vector<int>> graph;

Config config;
ConstraintSet constraintSet;

/*
 *
 */
void buildDependenceGraph(
		std::vector<std::pair<std::string, int>> cmdTokens,
		int &cnt,
		std::map<std::string, int> &variables,
		std::vector<std::vector<int>> &graph) {
	std::string constStr = "";
	for (const auto&  token : cmdTokens)
		if (token.first[0] == '"')
			constStr += token.first.substr(1, token.first.length() - 2);

	if (constStr.length() > 0) {
		constStr = "\"" + constStr + "\"";
		if (variables.find(constStr) == variables.end()) {
			variables[constStr] = cnt;
			cnt ++;
		}
	}


	if (cmdTokens.size() > 0) {
		if (cmdTokens[1].second >= antlrcpptest::SMTLIB26Lexer::TOKEN_CMD_DECLARE_SORT &&
				cmdTokens[1].second <= antlrcpptest::SMTLIB26Lexer::TOKEN_CMD_DEFINE_FUN &&
				variables.find(cmdTokens[2].first) == variables.end()) {

			variables[cmdTokens[2].first] = cnt;

			std::vector<int> newVector;
			graph.push_back(newVector);
			cnt ++;
		}
		else {
			// collect all variables in a line
			std::vector<int> lineVars;
			for (const auto& token : cmdTokens) {
				if (variables.find(token.first) != variables.end() &&
						token.second == antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM) {
					lineVars.push_back(variables[token.first]);
				}
			}

			// create graph
			if (lineVars.size() > 0) {
				for (unsigned int i = 0; i < lineVars.size(); ++i) {
					for (unsigned int j = i + 1; j < lineVars.size(); ++j) {
						graph[lineVars[i]].push_back(lineVars[j]);
						graph[lineVars[j]].push_back(lineVars[i]);
					}
				}

			}

			if (constStr.length() > 0) {
				for (unsigned int i = 0; i < lineVars.size(); ++i) {
					graph[lineVars[i]].push_back(variables[constStr]);
				}
			}

		}
	}
}

/*
 *
 */
void initGraph(std::string inputFile){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	int cnt = 0;
	std::vector<std::vector<std::pair<std::string, int>>> fileTokens;
	switch (config.languageVersion) {
	case 20:
	case 25:
		fileTokens = parseFile20(inputFile);
		break;

	case 26:
		fileTokens = parseFile26(inputFile);
		break;
	default:
		assert(false);
		break;
	}
	for (const auto& tokens : fileTokens) {
		buildDependenceGraph(tokens, cnt, variables, graph);
	}
}

/**
 * convert to
 */
std::string convertFileToReplaceConst(std::string fileDir) {
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	/*get fileName from fileDir */
	std::string fileName = "";
	for (int i = fileDir.length() - 1; i >= 0; --i)
		if (fileDir[i] != '/')
			fileName = fileDir[i] + fileName;
		else
			break;

	/* create dir */

	bool success = makePath(TMPDIR);
	__debugPrint(logFile, "%d creating %s: %s\n", __LINE__, TMPDIR, success ? "OK" : "failed");

	/* create file */
	std::string outFile = std::string(TMPDIR) + "/" + CONVERTED + fileName ;
	encodeHex(fileDir, outFile);
	return outFile;
}

/**
 *
 */
std::string convertToRemoveSpecialConstCharacters(std::string fileDir){
	/*get fileName from fileDir */
	std::string fileName = getFileNameFromFileDir(fileDir);

	/* create dir */
	std::string outFile = std::string(TMPDIR) + std::string("/");
	bool success = makePath(outFile);


	/* create file */
	outFile = outFile + fileName;

	bool completed = prepareEncoderDecoderMap(fileDir);
	if (completed == false)
		config.skipOverapprox = true;
	else
		config.skipOverapprox = false;

	__debugPrint(logFile, "%d creating %s: %s\n", __LINE__, outFile.c_str(), success ? "OK" : "failed");
	encodeSpecialChars(fileDir, outFile);
	return outFile;
}

/*
 *
 */
void getAllConstraints(){
	constraintSet = getConstraints(config.inputFile);
}

/*
 * parse user's command line
 */
void parseUserInput(int argc, char* argv[]){
	config.parse(argc, argv);
}

/**
 *
 */

int main(int argc, char* argv[])
{
	logFile = NULL;
	logAxiom = NULL;
	parseUserInput(argc, argv);
	if (config.printingConstraints){
		getAllConstraints();
	}

	if (config.inputFile.length() > 0) {
		config.inputFile = convertToRemoveSpecialConstCharacters(config.inputFile);
		initGraph(config.inputFile);
		config.inputFile_converted = convertFileToReplaceConst(config.inputFile);
		overApproxController();

		if (config.cleanLog == true)
			removeFiles(config.inputFile);
	}

#ifdef DEBUGLOG
	fclose(logFile);
	fclose(logAxiom);
#endif
	if (config.cleanLog == true)
		removeLog();
	return 0;
}
