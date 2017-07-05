/*
 * CParser.h
 *
 *  Created on: Sep 3, 2015
 *      Author: diepbp
 */

#ifndef TOKENPARSER_H_
#define TOKENPARSER_H_

#include "utils.h"

#define NMAX 1000

class TokenParser{
public:
    std::vector<TokenElement> tokenList;
    std::string pmlFile, automataFile;

    TokenParser(std::string _automataFile, std::string _pmlFile) :
        pmlFile(_pmlFile), automataFile(_automataFile){

            readAutomata(automataFile);
            readCFile(pmlFile);
        };

    TokenParser(std::string _automataFile){
    	automataFile = _automataFile;
        readAutomata(automataFile);
    };

    void readCFile(std::string fileName);
    bool readAutomata(std::string fileName);

    std::vector<TokenElement> tokenHandler(std::string s, int lineNo);
private:

    std::map<int, int> rowLabels;
    std::map<std::string, int> colLabels;
    std::string tokenMap[NMAX];
    int transitionTable[NMAX][NMAX];
    bool finalStates[NMAX], putbackStates[NMAX];
    std::string temp = "";
    int state = 0;

    int processError(int start, std::string error, std::string line);
    std::string findType(char ch);
    std::vector<char*> stringTokens(char* line);
};
#endif /* TOKENPARSER_H_ */
