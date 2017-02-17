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
#include "StringTheory.h"
#include "FileConverter.h"

std::string orgInput;
std::string inputFile;
std::string inputFile_converted;

int cnt = 0;
std::map<std::string, int> variables;
std::vector<std::vector<int>> graph;
std::map<std::string, std::string> ourGrm;

/*
 *
 */
void buildDependenceGraph(std::string line, int &cnt, std::map<std::string, int> &variables, std::vector<std::vector<int>> &graph) {
	std::string declare_fun = "declare-fun";
	std::string declare_const = "declare-const";
	std::string declare = "declare";
	std::vector<std::string> tokens = parse_string_language(line, " ()*+*/=><");

	int state = 2; // 1 -> "; 2 -> ""; 3 -> \;
	std::string constStr = "";
	for (unsigned int i = 0; i < line.length(); ++i)
		if (line[i] == '"') {
			if (state == 1){
				state = 2;
			}
			else if (state == 3) {
					state = 1;
					constStr = constStr + line[i];
			}
			else {
				state = 1;
			}
		}
		else if (line[i] == '\\' && state == 1) {
			if (state != 3)
				state = 3;
			constStr = constStr + line[i];
		}
		else if (state == 1 || state == 3)
			constStr = constStr + line[i];


	if (constStr.length() > 0) {
		constStr = "\"" + constStr + "\"";
		if (variables.find(constStr) == variables.end()) {
			variables[constStr] = cnt;
			cnt ++;
		}
	}


	if (tokens.size() > 0) {

		if ((tokens[0].compare(declare) == 0 || tokens[0].compare(declare_fun) == 0 || tokens[0].compare(declare_const) == 0) &&
				variables.find(tokens[1]) == variables.end()) {

			variables[tokens[1]] = cnt;

			std::vector<int> newVector;
			graph.push_back(newVector);
			cnt ++;
		}
		else if (tokens[0].compare(declare_const) == 0) {

		}
		else {
			// collect all variables in a line
			std::vector<int> lineVars;
			for (unsigned int i = 0; i < tokens.size(); ++i) {
				if (variables.find(tokens[i]) != variables.end() &&
						tokens[i][0] != '"') {
					lineVars.push_back(variables[tokens[i]]);
					__debugPrint(logFile, " %s,", tokens[i].c_str());
				}
			}
			__debugPrint(logFile, "\n%s\n", line.c_str());

			// create graph
			if (lineVars.size() > 0) {
				for (unsigned int i = 0; i < lineVars.size(); ++i) {
					for (unsigned int j = i + 1; j < lineVars.size(); ++j) {
						graph[lineVars[i]].push_back(lineVars[j]);
						graph[lineVars[j]].push_back(lineVars[i]);
					}
//					__debugPrint(logFile, " %d,", lineVars[i]);
				}
//				__debugPrint(logFile, "\n");

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
  __debugPrint(logFile, "*              initGraph             *\n");
  __debugPrint(logFile, "-----------------------------------------------\n");
#endif
	FILE* pipe = fopen(inputFile.c_str(), "r");
	char buffer[1000];

	std::string cmdLine = "";
	while (!feof(pipe))
	{
		if (fgets(buffer, 1000, pipe) != NULL)
		{
			std::string tmp = std::string(buffer);
			if (tmp.find("(assert ") != std::string::npos) {
				buildDependenceGraph(cmdLine, cnt, variables, graph);
				cmdLine = tmp;
			}
			else if (tmp.find("(declare") != std::string::npos) {
				buildDependenceGraph(cmdLine, cnt, variables, graph);
				cmdLine = tmp;
			}
			else {
				cmdLine = cmdLine + tmp;
			}

		}
	}
	if (cmdLine.length() > 0) {
		buildDependenceGraph(cmdLine, cnt, variables, graph);
	}
	pclose(pipe);
}

void loadGrammar(std::string grammarFile) {
#ifdef DEBUGLOG
  __debugPrint(logFile, "***********************************************\n");
  __debugPrint(logFile, "*                 initGrammar                 *\n");
  __debugPrint(logFile, "-----------------------------------------------\n");
#endif
  ourGrm = CFG_parser(grammarFile);

#ifdef DEBUGLOG
  for (std::map<std::string, std::string>::iterator it = ourGrm.begin(); it != ourGrm.end(); ++it)
  	__debugPrint(logFile, "%d %s: %s\n", __LINE__, it->first.c_str(), it->second.c_str());
#endif
//	FILE* pipe = fopen(grammarFile.c_str(), "r");
//	char buffer[2000];
//
//	std::string cmdLine = "";
//	while (!feof(pipe))
//	{
//		if (fgets(buffer, 2000, pipe) != NULL)
//		{
//			int pos = 0;
//			std::string line = buffer;
//			std::string name = "";
//			for (pos = 0; pos < line.length(); ++pos)
//				if (line[pos] == ':')
//					break;
//				else {
//					name = name + line[pos];
//				}
//
//			std::string reg = line.substr(pos + 2, line.length() - pos - 3);
//			__debugPrint(logFile, "%s --> %s\n", name.c_str(), reg.c_str());
//
//			ourGrm[name] = reg;
//		}
//	}
//	pclose(pipe);
}


/*
 *
 */
void *exec(void *args) {
	char* cmd = *((char* *) args);
	FILE* pipe = popen(cmd, "r");
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	char buffer[1000];
	std::string result = "";

	std::string cmdLine = "";
	try {

		while (!feof(pipe)) {
			if (fgets(buffer, 1000, pipe) != NULL) {
				result += buffer;
			}
		}

	} catch (...) {
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	pthread_exit(0);
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
	rewriteFileSMTToRemoveSpecialChar(fileDir, outFile);
	return outFile;
}

/**
 *
 */

int main(int argc, char* argv[])
{
	if (argc < 2)
		std::cerr << "Specify the input file!\n";

	logFile = NULL;
	logAxiom = NULL;
	std::string grammarFile = "";

#ifdef DEBUGLOG
	logFile = fopen("log.smt2", "w");
	logAxiom = fopen("logAxiom.smt2", "w");
#endif

	if (argc >= 3) {
		bool foundGrm = false;
		for (int i = 1; i < argc; ++i) {
			std::string tmp = std::string(argv[i]);
			if (tmp.compare("-grm") == 0){
				i++;
				grammarFile = argv[i];
				foundGrm = true;
			}
			else {
				inputFile = argv[i];
				orgInput = inputFile;
			}
		}
		if (argc > 4 || foundGrm == false)
			throw std::runtime_error("Incorrect arguments.\n ./FAT [-grm grammarFile] smtFile\n");
		grammarFile = argv[2];
		loadGrammar(grammarFile);
	}
	else {
		inputFile = argv[1];
		orgInput = inputFile;
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, "Input file: %s\n\n", inputFile.c_str());
	if (argc >= 3)
		__debugPrint(logFile, "Grammar file: %s\n\n", argv[2]);
#endif
	inputFile = convertToRemoveSpecialConstCharacters(inputFile);
	initGraph(inputFile);
	inputFile_converted = convertFileToReplaceConst(inputFile);
	overApproxController();

	removeFile(inputFile);
#ifdef DEBUGLOG
	fclose(logFile);
	fclose(logAxiom);
#endif
	return 0;
}
