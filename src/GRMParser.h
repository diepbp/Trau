/*
 * CParser.h
 *
 *  Created on: Sep 3, 2015
 *      Author: diepbp
 */

#ifndef GRMPARSER_H_
#define GRMPARSER_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>

#define NMAX 100

struct TokenElement{
    TokenElement(int _lineNo, std::string _content, std::string _type) : lineNo(_lineNo), content(_content), type(_type){}

    int lineNo;
    std::string content;
    std::string type;
};


class GRMParser{
public:
    std::vector<TokenElement> tokenList;
    std::string pmlFile, automataFile;

    GRMParser(std::string _automataFile, std::string _pmlFile) :
        pmlFile(_pmlFile), automataFile(_automataFile){

            readAutomata(automataFile);
            readCFile(pmlFile);
        };

    GRMParser(std::string _automataFile){
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
#endif /* GRMPARSER_H_ */
