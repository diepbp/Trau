/*
 * CParser.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: diepbp
 */

#include "GRMParser.h"

#include <assert.h>

std::vector<char*> GRMParser::stringTokens(char* line){
	std::vector<char*> result;
    char * pch;
    pch = strtok (line," \t\r\n\b\f");
    while (pch != NULL)
    {
        result.push_back(pch);
        pch = strtok (NULL, " \t\r\n\b\f");
    }
    return result;
}

/*
 * Read data file and put them to transition table
 */
bool GRMParser::readAutomata(std::string fileName){
    FILE* fp;
    fp = fopen(fileName.c_str(), "r");

    const int SIZEBUF = 2048;
    char buf [SIZEBUF];
    std::vector<char*> tmp;

    int countFinalStates = 0;
    for (int i = 0; i < NMAX; ++i) {
        finalStates[i] = 0;
        putbackStates[i] = 0;
    }

    fgets(buf, sizeof (buf), fp); // <start-state>
    fgets(buf, sizeof (buf), fp); // 0
    fgets(buf, sizeof (buf), fp); // <final-states>

    fgets(buf, sizeof (buf), fp);
    tmp = stringTokens(buf);
    for (std::vector<char*>::iterator i = tmp.begin(); i != tmp.end(); ++i) {
        finalStates[atoi((char*)*i)] = true;
        countFinalStates++;
    }

    fgets(buf, sizeof (buf), fp); // <row-labels>
    fgets(buf, sizeof (buf), fp);
    tmp = stringTokens(buf);
    for (std::vector<char*>::iterator i = tmp.begin(); i != tmp.end(); ++i) {
        rowLabels.insert(std::pair<int, int>(atoi((char*)*i), rowLabels.size()));
    }

    fgets(buf, sizeof (buf), fp); // <column-labels>
    fgets(buf, sizeof (buf), fp);
    tmp = stringTokens(buf);

    for (std::vector<char*>::iterator i = tmp.begin(); i != tmp.end(); ++i) {
        std::string ss(*i);
        colLabels.insert(std::pair<std::string, int>(ss, colLabels.size()));
    }

    fgets(buf, sizeof (buf), fp);
    for (unsigned int i = 0; i < rowLabels.size(); ++i) {
        for (unsigned int j = 0; j < colLabels.size(); ++j) {
            fscanf(fp, "%i", &transitionTable[i][j]);
        }
    }

    fgets(buf, sizeof (buf), fp);
    fgets(buf, sizeof (buf), fp); // <finalstate-token-map>

    for (int i = 0; i < countFinalStates; ++i) {
        fgets(buf, sizeof (buf), fp);
        tmp = stringTokens(buf);
        std::string s(tmp[1]);
        tokenMap[atoi(tmp[0])] = s;
    }

    fgets(buf, sizeof (buf), fp);
    fgets(buf, sizeof (buf), fp); // <put-back-state>
    tmp = stringTokens(buf);

    for (std::vector<char*>::iterator i = tmp.begin(); i != tmp.end(); ++i) {
        putbackStates[atoi((char*)*i)] = true;
    }
    pclose(fp);
    return true;
}

std::string GRMParser::findType(char ch){ //-------------------------CHANGE-----------------
	std::string tmp = "";
    tmp.insert(tmp.end(), ch);

    if (ch == 'E' || ch == 'e')
        return "E|e";
    else if (ch == 'b' || ch == 'f' ||ch == 'n' ||ch == 'r' || ch == 't')
        return "b|f|n|r|t";
    else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_')
        return "char";
    else if (ch >= '0' && ch <= '9')
        return "num";
    else if (ch == ' ' || ch == '\t')
        return "space";
    return tmp;
}

/*
 * error handling
 * 		string error
 * 		neu gap loi la string : tim den dau " tiep theo
 * 		neu gap loi con lai, tim den ky tu phan cach, hoac dau ngoac tiep theo
 *
 * 		start : vi tri loi hien tai
 * 		error : string dang loi hien tai
 * 		line : string dang xet
 *
 * 		ket qua tra ve la vi tri xuat phat ma` o do' khong gap loi~
 */
int GRMParser::processError(int start, std::string error, std::string line){
	unsigned int i = start;
    if (error[0] == '"' && error[error.length() - 2] != '"'){
        while (i < line.length() && line[i] != '"')
            ++i;
        if (i < line.length())
            ++i;
        error = error + line.substr(start, i);
        tokenList.push_back(TokenElement(-1, error, "error"));
        start = i;
    }
    else {
        for (i = start; i < line.length(); ++i){
        	error = error + line[i];
        }
        tokenList.push_back(TokenElement(-1, error, "error"));

    }
    return i - 1;
}

std::vector<TokenElement> GRMParser::tokenHandler(std::string s, int lineNo){
    std::vector<TokenElement> tmpResult;
    if (s.length() == 0)
        return tmpResult;
    unsigned int start = 0;
    if (s[s.length() - 1] == '\n')
        s = s.substr(0, s.length() - 1);
    s = s + " ";
    while(start < s.length()){
        temp = temp + s[start];
        if ((temp[0] == ' ' || temp[0] == '\t' || temp[0] == '\n' || temp[0] == '\r') && temp.length() == 1){
            temp = "";
        }
        state = transitionTable[rowLabels[state]][(int)colLabels[findType(s[start])]];
//        printf("%d state after = %d\n", __LINE__, state);
        // state 20 : skip if "//"
        if (state == 20){
            state = 0;
            temp = "";
            break;
        }

        if (state != -1){
            // not error
            if (finalStates[state] == true){
                if (putbackStates[state] == true){
                    temp = temp.substr(0, temp.length()- 1);
                    --start;
                }
                // state 20 : comment
                if (state != 20)
                    tmpResult.push_back(TokenElement(lineNo, temp, tokenMap[state]));
                temp = "";

                state = 0;
            }
        }
        else {

            if (s[start] != ' ' && s[start] != '\t')
                ++ start;
            start = processError(start, temp, s);
            state = 0;
            temp = "";
        }
        ++start;
    }

    //xu ly loi~ khi het dong : luu y state 46: trang thai /*
    if (state != 0 && state != 46)
        tmpResult.push_back(TokenElement(-1, temp, "error"));
    return tmpResult;
}

void GRMParser::readCFile(std::string fileName){
	FILE* fp;
	const int SIZEBUF = 2048;
	char buf [SIZEBUF];

	fp = fopen(fileName.c_str(), "r");
	int lineNo = 0;
	while (fgets(buf, sizeof (buf), fp)) {
		std::string s(buf);
		std::vector<TokenElement> t = tokenHandler(s, ++lineNo);
		printf("%d Line: ++%s++\n", __LINE__, s.c_str());
		for (unsigned int i = 0; i < t.size(); ++i)
			printf("\t--%s--:%s\n", t[i].content.c_str(), t[i].type.c_str());
		printf("\n");
	}

	printf("%d Size: %ld\n", __LINE__, tokenList.size());
	for (unsigned int i = 0; i < tokenList.size(); ++i) {
		printf("\t line: %d, \t %s -- %s\n", tokenList[i].lineNo, tokenList[i].content.c_str(), tokenList[i].type.c_str());
	}

	fclose(fp);
}
