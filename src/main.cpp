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
#include "FileConverter.h"
#include "Utils.h"

std::string orgInput;
std::string inputFile;
std::string inputFile_converted;
bool getModel = false;
bool beReviewed = false;
bool cleanLog = true;
bool printingConstraints = false;
int cnt = 0;
bool skipOverapprox;
std::map<std::string, int> variables;
std::vector<std::vector<int>> graph;
std::map<std::string, std::vector<std::string>> ourGrm;
std::map<int, std::string> languageMap;
char escapeChar = ESCAPECHAR20;
int languageVersion = 20;
bool aggressiveRefineBool = false;
std::string verifyingSolver = "";
std::string trauVersion = "1.2";


ConstraintSet constraintSet;

const std::vector<std::string> supportedLanguage = {"SMT2.0", "SMT2.5", "SMT2.6"};
const std::vector<std::string> availableSolvers = {"cvc4", "z3str3", "s3"};

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
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	std::vector<std::vector<std::pair<std::string, int>>> fileTokens;
	switch (languageVersion) {
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

void loadGrammar(std::string grammarFile) {
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

#if 0
	ourGrm = OverApproxCFG::overapprox_CFG(grammarFile);
#else
	ourGrm = UnderApproxCFG::underapprox_CFG(grammarFile);
#endif
	for (const auto& s : ourGrm) {
		__debugPrint(logFile, "%d %s: \n", __LINE__, s.first.c_str());
		for (const auto& ss : s.second)
			__debugPrint(logFile, "%d\t%s\n", __LINE__, ss.c_str());
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
		skipOverapprox = true;
	else
		skipOverapprox = false;

	__debugPrint(logFile, "%d creating %s: %s\n", __LINE__, outFile.c_str(), success ? "OK" : "failed");
	encodeSpecialChars(fileDir, outFile);
	return outFile;
}
/**
 *
 */
void printHelp(){
	printf("Trau string solver [version %s]\n", trauVersion.c_str());
	printf("Usage ./Trau [option] file.smt2\n\n");

	printf("Input format:\n");
	printf("\t -model 	\t\t print satisfying assignments if the result is SAT.\n");
	printf("\t -language [..]	\t\t define the input language. Trau supports ");
	for (const auto& s: supportedLanguage)
		printf("%s ", s.c_str());
	printf("!\n");
	printf("\t -grm [..]\t\t\t specify the grammar file.\n");
	printf("\t -doublecheck 	\t\t use the S3P string solver to double-check satisfying assignments.\n");

	printf("\n");
}

/*
 *
 */
void getAllConstraints(){
	constraintSet = getConstraints(inputFile);
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
		else if (tmp.compare("-language") == 0){
			i++;
			std::string language = "";
			if (std::find(supportedLanguage.begin(), supportedLanguage.end(), std::string(argv[i])) != supportedLanguage.end()) {
				language = argv[i];
			}
			if (language.length() == 0) {
				printf("Input language is not supported.\nTrau supports ");
				for (const auto& s: supportedLanguage)
					printf("%s ", s.c_str());
				printf("!\n");
				throw std::runtime_error("Cannot recognize the input language!");
			}
			else if (language.compare("SMT2.6") == 0) {
				languageMap = languageMap26;
				languageVersion = 26;
				escapeChar = ESCAPECHAR26;
				if (verifyingSolver.length() == 0)
					verifyingSolver = "cvc4";
			}
			else if (language.compare("SMT2.5") == 0) {
				languageMap = languageMap25;
				languageVersion = 25;
				escapeChar = ESCAPECHAR25;
				if (verifyingSolver.length() == 0)
					verifyingSolver = "z3str3";
			}
			else if (language.compare("SMT2.0") == 0) {
				languageMap = languageMap20;
				languageVersion = 20;
				escapeChar = ESCAPECHAR20;
				if (verifyingSolver.length() == 0)
					verifyingSolver = "s3";
			}
		}
		else if (tmp.compare("-doublecheck") == 0){
			getModel = true;
			beReviewed = true;

			if (i + 1 < argc){
				std::string checker = std::string(argv[i + 1]);
				if (checker[0] != '-') {
					if (std::find(availableSolvers.begin(), availableSolvers.end(), checker) != availableSolvers.end()) {
						verifyingSolver = argv[i + 1];
						i++;
					}
					else {
						printf("%s is not supported\n", argv[i + 1]);
					}
				}
			}
		}
		else if (tmp.compare("-model") == 0){
			getModel = true;
		}
		else if (tmp.compare("-agressiveRefineBool") == 0){
			aggressiveRefineBool = true;
		}
		else if (tmp.compare("-noCleanLog") == 0){
			cleanLog = false;
		}
		else if (tmp.compare("-help") == 0){
			printHelp();
			return;
		}
		else if (tmp.compare("-printConstraints") == 0){
			printingConstraints = true;
		}
		else if (tmp[0] == '-') {
			printHelp();
			inputFile = "";
			orgInput = "";
			throw std::runtime_error("Arguments Errors.\n");
			return;
		}
		else {
			inputFile = argv[i];
			orgInput = inputFile;
		}
	}

	if (verifyingSolver.length() == 0)
		verifyingSolver = "s3";

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
	languageMap = languageMap20;
	parseUserInput(argc, argv);
	if (printingConstraints){
		getAllConstraints();
	}

	if (inputFile.length() > 0) {
		inputFile = convertToRemoveSpecialConstCharacters(inputFile);
		initGraph(inputFile);
		inputFile_converted = convertFileToReplaceConst(inputFile);
		overApproxController();

		if (cleanLog == true)
			removeFiles(inputFile);
	}

#ifdef DEBUGLOG
	fclose(logFile);
	fclose(logAxiom);
#endif
	if (cleanLog == true)
		removeLog();
	return 0;
}
