//============================================================================
// Name        : FlatAutomaton.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iomanip>

#include "fileutils.h"
#include "GrmOverApprox.h"
#include "GrmUnderApprox.h"
#include "StringTheory.h"
#include "FileConverter.h"

std::string orgInput;
std::string inputFile;
std::string inputFile_converted;
bool getModel = false;
bool beReviewed = false;
bool cleanLog = true;
int cnt = 0;
std::map<std::string, int> variables;
std::vector<std::vector<int>> graph;
std::map<std::string, std::vector<std::string>> ourGrm;

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
		if (cmdTokens[1].second >= 64 &&
				cmdTokens[1].second <= 67 &&
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
						token.second == 88) {
					lineVars.push_back(variables[token.first]);
					__debugPrint(logFile, " %s \n", token.first.c_str());
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
#ifdef DEBUGLOG
  __debugPrint(logFile, "***********************************************\n");
  __debugPrint(logFile, "*              initGraph             			*\n");
  __debugPrint(logFile, "-----------------------------------------------\n");
#endif

  std::vector<std::vector<std::pair<std::string, int>>> fileTokens = parseFile(inputFile);
  for (const auto& tokens : fileTokens) {
	  buildDependenceGraph(tokens, cnt, variables, graph);
  }
}

void loadGrammar(std::string grammarFile) {
#ifdef DEBUGLOG
  __debugPrint(logFile, "***********************************************\n");
  __debugPrint(logFile, "*                 initGrammar                 *\n");
  __debugPrint(logFile, "-----------------------------------------------\n");
#endif

#if 0
  ourGrm = OverApproxCFG::overapprox_CFG(grammarFile);
#else
  ourGrm = UnderApproxCFG::underapprox_CFG(grammarFile);
#endif
#ifdef DEBUGLOG
  for (std::map<std::string, std::vector<std::string>>::iterator it = ourGrm.begin(); it != ourGrm.end(); ++it) {
	  __debugPrint(logFile, "%d %s: \n", __LINE__, it->first.c_str());
	  for (unsigned int i = 0; i < it->second.size(); ++i)
		  __debugPrint(logFile, "%d\t%s\n", __LINE__, it->second[i].c_str());
  }
#endif
}

/**
 * convert to
 */
std::string convertFileToReplaceConst(std::string fileDir) {
#ifdef DEBUGLOG
  __debugPrint(logFile, "***********************************************\n");
  __debugPrint(logFile, "*              convertFile             *\n");
  __debugPrint(logFile, "-----------------------------------------------\n");
#endif

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
	std::string outFile = std::string(TMPDIR) + "converted_" + fileName ;
	rewriteFileSMTToReplaceConst(fileDir, outFile);
	return outFile;
}

/**
 *
 */
std::string convertToRemoveSpecialConstCharacters(std::string fileDir){
	/*get fileName from fileDir */
	std::string fileName = getFileNameFromFileDir(fileDir);

	/* create dir */
	std::string outFile = "/tmp/fat_str_convert/";
	bool success = makePath(outFile);
	__debugPrint(logFile, "%d creating %s: %s\n", __LINE__, outFile.c_str(), success ? "OK" : "failed");

	/* create file */
	outFile = outFile + fileName;

	prepareEncoderDecoderMap(fileDir);
	rewriteFileSMTToRemoveSpecialChar(fileDir, outFile);

	return outFile;
}
/**
 *
 */
void printHelp(){
	printf("Trau string solver [version 0.9]\n");
	printf("Usage ./Trau [option] file.smt2\n\n");

	printf("Input format:\n");
	printf("\t -model 	\t\t print satisfying assignments if the result is SAT.\n");
	printf("\t -grm [..]\t\t\t specify the grammar file.\n");
	printf("\t -doublecheck 	\t\t use the S3P string solver to double-check satisfying assignments.\n");

	printf("\n");
}

/*
 * parse user's command line
 */
void parseUserInput(int argc, char* argv[]){
	std::string grammarFile = "";

#ifdef DEBUGLOG
	logFile = fopen(LOGFILE, "w");
	logAxiom = fopen(LOGAXIOMFILE, "w");
#endif

	bool foundGrm = false;
	for (int i = 1; i < argc; ++i) {
		std::string tmp = std::string(argv[i]);
		if (tmp.compare("-grm") == 0){
			i++;
			grammarFile = argv[i];
			foundGrm = true;
		}
		else if (tmp.compare("-doublecheck") == 0){
			beReviewed = true;
		}
		else if (tmp.compare("-model") == 0){
			getModel = true;
		}
		else if (tmp.compare("-noCleanLog") == 0){
			cleanLog = false;
		}
		else if (tmp.compare("-help") == 0){
			printHelp();
			return;
		}
		else if (tmp[0] == '-') {
			printf("Arguments Errors.\n");
			printHelp();
			inputFile = "";
			orgInput = "";
			return;
		}
		else {
			inputFile = argv[i];
			orgInput = inputFile;
		}
	}

	if (foundGrm == true){
		loadGrammar(grammarFile);
	}

	if (inputFile.length() == 0)
		std::cerr << "Specify the input file!\n";

#ifdef DEBUGLOG
	__debugPrint(logFile, "Input file: %s\n\n", inputFile.c_str());
	if (foundGrm)
		__debugPrint(logFile, "Grammar file: %s\n\n", grammarFile.c_str());
#endif
}

/**
 *
 */

int main(int argc, char* argv[])
{
	logFile = NULL;
	logAxiom = NULL;

	parseUserInput(argc, argv);
	if (inputFile.length() > 0) {
		inputFile = convertToRemoveSpecialConstCharacters(inputFile);
		initGraph(inputFile);
		inputFile_converted = convertFileToReplaceConst(inputFile);
		overApproxController();

		if (cleanLog == true)
			removeFile(inputFile);
	}

#ifdef DEBUGLOG
	fclose(logFile);
	fclose(logAxiom);
#endif
	if (cleanLog == true)
		removeLog();
	return 0;
}
