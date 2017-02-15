/*
 * FileConverter.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */

#include "FileConverter.h"

template< typename T >
std::string int_to_hex( T i )
{
	std::stringstream stream;
	stream << "_x" << std::hex << i;
	return stream.str();
}

/*
 * Create a new string from tokens
 */
std::string concatTokens(std::vector<std::string> tokens) {
	std::string ret = "";
	for (unsigned int i = 0; i < tokens.size(); ++i)
		if (i == 0)
			ret = tokens[i];
		else
			ret = ret + " " + tokens[i];
	return ret;
}

/*
 * For all string variables
 * Change var name: xyz --> len_xyz
 * and change var type: string -> int
 */
std::string redefineStringVar(std::string var){
	return "(declare-const len_" + var + " Int)";
}

std::string redefineOtherVar(std::string var, std::string type){
	return "(declare-const " + var + " " + type;
}


/*
 * Concat --> +
 */
void updateConcat(std::string &s) {
	// replace concat --> +
	std::size_t found = s.find("(Concat ");
	while (found != std::string::npos) {
		s.replace(found + 1, 6, "+");
		found = s.find("(Concat ");
	}

	found = s.find("Concat ");
	while (found != std::string::npos) {
		s.replace(found, 6, "+");
		found = s.find("Concat ");
	}
}

/*
 * Length --> ""
 */
void updateLength(std::string &s) {
	// replace Length --> ""
	std::size_t found = s.find("(Length ");
	while (found != std::string::npos) {
		s.replace(found + 1, 6, "+ 0");
		found = s.find("(Length ");
	}

	found = s.find("Length ");
	while (found != std::string::npos) {
		s.replace(found, 6, "+ 0");
		found = s.find("Length ");
	}
}

/*
 * "abcdef" --> 6
 */
void updateConst(std::string &s, std::set<std::string> constList) {
	// replace const --> its length
	for (std::set<std::string>:: iterator it = constList.begin(); it != constList.end(); ++it) {
		while(true) {
			std::size_t found = s.find(*it);
			if (found != std::string::npos) {
				s.replace(found, it->length(), std::to_string(it->length() - 2));
			}
			else
				break;
		}
	}

}

/*
 * xyz --> len_xyz
 */
void updateVariables(std::string &s, std::vector<std::string> strVars) {
	std::vector<std::string> tmp = parse_string_language(s, " ");
	for (unsigned int i = 0; i < tmp.size(); ++i) {
		std::vector<std::string> anotherTmp = parse_string_language(tmp[i], " ()=");
		std::vector<std::string> vars;
		for (unsigned int j = 0; j < anotherTmp.size(); ++j) {
			if (std::find(strVars.begin(), strVars.end(), anotherTmp[j]) != strVars.end()){
				// there exists string variables
				vars.push_back(anotherTmp[j]);
			}
		}
		for (unsigned int j = 0 ; j < vars.size(); ++j) {
			std::size_t found = tmp[i].find(vars[j]);
			tmp[i].replace(found, vars[j].length(), "len_" + vars[j]);
		}
	}

	s = concatTokens(tmp);
}

/*
 * contain a string variable
 */
bool strContaintStringVar(std::string notStr, std::vector<std::string> strVars) {
	if (notStr.find("Length") != std::string::npos)
		return false;
	for (unsigned int i = 0; i < strVars.size(); ++i) {
		std::string tmp = strVars[i];
		if (notStr.find(tmp) != std::string::npos)
			return true;
	}
	return false;
}

/*
 *
 */
void checkAssignWellForm(std::string &s){
	while (true) {
		bool change = false;
		for (unsigned int i = 0; i < s.length(); ++i)
			if (s[i] == '=')
				if (s[i-1] == '(') { /* start by (= */
					int parentheses = 1;
					int tokens = 0;

					int j = i;
					for (unsigned j = i; j < s.length(); ++j) {
						if (s[j] == '('){
							parentheses++;
							tokens++;
						}
						else if (s[j] == ')') {
							parentheses--;
							if (s[j - 1] != ' ')
								tokens++;
							if (parentheses == 0) {
								break;
							}
							tokens++;
						}
						if (s[j] == ' ' && s[j - 1] != ' ')
							tokens++;
					}
					// check (= A)
//					printf("Tokens of %s : %d\n", newS.c_str(), tokens);
					if (tokens <= 2) {
						 // printf("%d Before s: %s\n", __LINE__, s.c_str());
						s.replace(i - 1, j - i + 2, "");
						 // printf("%d After s: %s\n", __LINE__, s.c_str());

						change = true;
						break;
					}
				}
		if (change == false)
			break;
	}
}

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
		std::vector<std::string> &notConstraints){
	std::set<std::string> constList;
	bool changeByNotOp = false;
	/* define a variable */
	if (str.find("(declare") != std::string::npos) {
		/* string var */
		std::vector<std::string> tokens = parse_string_language(str, " \n");
		if (str.find("String)") != std::string::npos || str.find("String )") != std::string::npos ) {
			/* length must be greater/equal than/to 0 */
			smtLenConstraints.push_back("(assert (>= len_" + tokens[1] + " 0))\n");

			strVars.push_back(tokens[1]); /* list of string variables */
			str = redefineStringVar(tokens[1]);
		}
		else {
			str = redefineOtherVar(tokens[1], tokens[tokens.size() - 1]);
		}
		smtVarDefinition.push_back(str);
	}

	/* assertion */
	else if ((str.find("(ite") == std::string::npos) ||
			(str.find("(and") == std::string::npos) ||
			(str.find("(or") == std::string::npos) ||
			(str.find("( ite") == std::string::npos) ||
			(str.find("( and") == std::string::npos) ||
			(str.find("( or") == std::string::npos)) {
		std::string strTmp = str;
		std::string newStr = "";
		int tabNum[1000];
		memset(tabNum, 0, sizeof tabNum);

		int notBool = -1;
		std::string notStr = "";

		int bracketCnt = 0;
		int textState = 0; /* 1 -> "; 2 -> ""; 3 -> \; */
		std::string constStr = "";

		for (unsigned int i = 0; i < strTmp.length(); ++i) {
			bool reduceSize = false;
			if (strTmp[i] == '"') {
				if (textState == 1){
					textState = 2;
					if (constStr.length() > 0) {
						constStr = "\"" + constStr + "\"";
						constList.emplace(constStr);
						constStr = "";
					}
					else {
						constStr = "\"" + constStr + "\"";
						constList.emplace(constStr);
						constStr = "";
					}

				}
				else if (textState == 3) {
					textState = 1;
					strTmp[i] = 'A';
					constStr = constStr + strTmp[i];

				}
				else {
					textState = 1;
				}
			}
			else if (strTmp[i] == '\\') {
				if (textState != 3) {
					textState = 3;
					strTmp.erase(i, 1);
					i--;
					reduceSize = true;
				}
				else if (textState == 3) {
					strTmp[i] = 'B';
					textState = 1;
					constStr = constStr + strTmp[i];
				}

			}
			else if (textState == 1 || textState == 3) {
				if (strTmp[i] == '~') {
					strTmp[i] = '0';
				}
				else if (strTmp[i] == '!') {
					strTmp[i] = '1';
				}
				else if (strTmp[i] == '@') {
					strTmp[i] = '2';
				}
				else if (strTmp[i] == '#') {
					strTmp[i] = '3';
				}
				else if (strTmp[i] == '$') {
					strTmp[i] = '4';
				}
				else if (strTmp[i] == '%') {
					strTmp[i] = '5';
				}
				else if (strTmp[i] == '^') {
					strTmp[i] = '6';
				}
				else if (strTmp[i] == '&') {
					strTmp[i] = '7';
				}
				else if (strTmp[i] == '*') {
					strTmp[i] = '8';
				}
				else if (strTmp[i] == '+') {
					strTmp[i] = '9';
				}
				else if (strTmp[i] == '=') {
					strTmp[i] = 'C';
				}
				else if (strTmp[i] == '?') {
					strTmp[i] = 'D';
				}
				else if (strTmp[i] == '|') {
					strTmp[i] = 'E';
				}
				else if (strTmp[i] == '[') {
					strTmp[i] = 'F';
				}
				else if (strTmp[i] == ']') {
					strTmp[i] = 'G';
				}
				else if (strTmp[i] == '(') {
					strTmp[i] = 'H';
				}
				else if (strTmp[i] == ')') {
					strTmp[i] = 'J';
				}
				else if (strTmp[i] == ';') {
					strTmp[i] = 'K';
				}
				else if (strTmp[i] == '_') {
					strTmp[i] = 'L';
				}
				constStr = constStr + strTmp[i];
			}

			else if (strTmp[i] == '(') {
				/* just want the file has a better look by adding some \n and \t */
				if (i + 3 < strTmp.length()) {
					std::string keyword01 = strTmp.substr(i + 1, 3);
					std::string keyword02 = strTmp.substr(i + 1, 2);
					if (keyword01.compare("ite") == 0 ||
							keyword01.compare("and") == 0 ||
							keyword02.compare("or") == 0) {
						tabNum[bracketCnt + 1] = abs(tabNum[bracketCnt]) + 1;
					}
					else if (keyword01.compare("not") == 0) {
						notBool = abs(bracketCnt);
					}
				}
				else
					tabNum[bracketCnt] = - abs(tabNum[bracketCnt - 1]);

				/* adding some \n and \t */
				if (tabNum[bracketCnt] > 0)
					newStr = newStr + "\n";
				for (int j = 0; j < tabNum[bracketCnt]; ++j)
					newStr = newStr + "\t";
				bracketCnt ++;
			}
			else if (strTmp[i] == ')') {
				if (notBool > 0 && bracketCnt == notBool) {
					if (handleNotOp || !strContaintStringVar(notStr, strVars)) {
						/* not (= x "abc")*/
						newStr = newStr + notStr;
					}
					else {
						// printf("%d remove this %s\n", __LINE__, notStr.c_str());
						 notConstraints.push_back(notStr);
						// remove this constraint
						changeByNotOp = true;
						newStr = newStr + "";
					}
					notBool = -1;
					notStr = "";
				}
				if (tabNum[bracketCnt] > 0)
					newStr = newStr + "\n";
				for (int j = 0; j < tabNum[bracketCnt]; ++j)
					newStr = newStr + "\t";
				bracketCnt--;
			}

			if (notBool < 0) {
				if (!reduceSize)
					newStr = newStr + strTmp[i];
			}
			else {
				if (!reduceSize)
					notStr = notStr + strTmp[i];
			}
		}

		// printf("%d before 00 %s\n", __LINE__, newStr.c_str());
		if (changeByNotOp) {
			checkAssignWellForm(newStr);
			changeByNotOp = false;
		}
		/* skip this assertion because of NotOp*/
		if (newStr.find("(assert )") != std::string::npos)
			return;

		// printf("%d before 01 %s\n", __LINE__, newStr.c_str());
		updateConst(newStr, constList); /* "abcdef" --> 6 */
		// printf("%d afterConst %s\n", __LINE__, newStr.c_str());
		updateConcat(newStr); /* Concat --> + */
		updateLength(newStr); /* Length --> "" */
		updateVariables(newStr, strVars); /* xyz --> len_xyz */

		smtLenConstraints.push_back(newStr);
	}
	else
		smtLenConstraints.push_back(str);
}

/*
 * Replace special const in constraints
 */
std::string customizeLine_removeSpecialChars(std::string str){

	std::string strTmp = str;
	std::string newStr = "";
	int tabNum[1000];
	memset(tabNum, 0, sizeof tabNum);


	int textState = 0; /* 1 -> "; 2 -> ""; 3 -> \; */

	for (unsigned int i = 0; i < strTmp.length(); ++i) {
		bool reduceSize = false;
		if (strTmp[i] == '"') {
			if (textState == 1){
				textState = 2;
			}
			else if (textState == 3) {
				textState = 1;
				strTmp[i] = 'A';
			}
			else {
				textState = 1;
			}
		}
		else if (strTmp[i] == '\\') {
			if (textState != 3) {
				textState = 3;
				strTmp.erase(i, 1);
				i--;
				reduceSize = true;
			}
			else if (textState == 3) {
				strTmp[i] = 'B';
				textState = 1;
			}

		}
		else if (textState == 1 || textState == 3) {
			if (strTmp[i] == '~') {
				strTmp[i] = '0';
			}
			else if (strTmp[i] == '!') {
				strTmp[i] = '1';
			}
			else if (strTmp[i] == '@') {
				strTmp[i] = '2';
			}
			else if (strTmp[i] == '#') {
				strTmp[i] = '3';
			}
			else if (strTmp[i] == '$') {
				strTmp[i] = '4';
			}
			else if (strTmp[i] == '%') {
				strTmp[i] = '5';
			}
			else if (strTmp[i] == '^') {
				strTmp[i] = '6';
			}
			else if (strTmp[i] == '&') {
				strTmp[i] = '7';
			}
			else if (strTmp[i] == '*') {
				strTmp[i] = '8';
			}
			else if (strTmp[i] == '+') {
				strTmp[i] = '9';
			}
			else if (strTmp[i] == '=') {
				strTmp[i] = 'C';
			}
			else if (strTmp[i] == '?') {
				strTmp[i] = 'D';
			}
			else if (strTmp[i] == '|') {
				strTmp[i] = 'E';
			}
			else if (strTmp[i] == '[') {
				strTmp[i] = 'F';
			}
			else if (strTmp[i] == ']') {
				strTmp[i] = 'G';
			}
			else if (strTmp[i] == '(') {
				strTmp[i] = 'H';
			}
			else if (strTmp[i] == ')') {
				strTmp[i] = 'J';
			}
			else if (strTmp[i] == ';') {
				strTmp[i] = 'K';
			}
			else if (strTmp[i] == '_') {
				strTmp[i] = 'L';
			}
		}

		if (!reduceSize)
			newStr = newStr + strTmp[i];
	}

	return newStr;
}

/*
 * Replace special const in constraints
 */
std::string customizeLine_replaceConst(std::string str, std::set<std::string> &constStr){

	std::string strTmp = str;
	std::string newStr = "";
	int tabNum[1000];
	memset(tabNum, 0, sizeof tabNum);

	std::string constString = "";

	int textState = 0; /* 1 -> "; 2 -> ""; 3 -> \; */

	for (unsigned int i = 0; i < strTmp.length(); ++i) {
		if (strTmp[i] == '"') {
			if (textState == 1){
				textState = 2;
				constStr.emplace("__cOnStStR_" + constString);
			}
			else {
				constString = "";
				newStr = newStr + "__cOnStStR_";
				textState = 1;
			}
		}
		else if (textState == 1) {
			std::string hex = int_to_hex((int)strTmp[i]);
			constString = constString + hex;
			newStr = newStr + hex;
		}
		else
			newStr = newStr + strTmp[i];
	}

	return newStr;
}

/*
 * read SMT file
 */
void rewriteFileSMTToRemoveSpecialChar(std::string inputFile, std::string outFile){
	FILE* in = fopen(inputFile.c_str(), "r");
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	char buffer[5000];
	while (!feof(in))
	{
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL)
		{
			out << customizeLine_removeSpecialChars(buffer);
			out.flush();

			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				break;
			}
		}
	}

	pclose(in);

	out.flush();
	out.close();
}

/*
 * read SMT file
 */
void rewriteFileSMTToReplaceConst(std::string inputFile, std::string outFile){
	FILE* in = fopen(inputFile.c_str(), "r");
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	char buffer[5000];
	std::set<std::string> constStr;
	std::vector<std::string> lines;
	while (!feof(in))
	{
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL)
		{
			lines.push_back(customizeLine_replaceConst(buffer, constStr));
			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				break;
			}
		}
	}

	pclose(in);

	for (std::set<std::string>::iterator it = constStr.begin(); it != constStr.end(); ++it) {
		out << "(declare-const " << *it << " String)\n";
		out.flush();
	}

	for (unsigned int i = 0; i < lines.size(); ++i) {
		out << lines[i];
		out.flush();
	}

	out.flush();
	out.close();
}

/*
 * read SMT file
 * convert the file to length file & store it
 */
void convertSMTFileToLengthFile(std::string inputFile, bool handleNotOp,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints,
		std::vector<std::string> &notConstraints){
	FILE* in = fopen(inputFile.c_str(), "r");

	char buffer[5000];
	std::vector<std::string> strVars;
	while (!feof(in))
	{
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL)
		{
			/* convert that line to length constraints */
			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				break;
			}
			customizeLine_ToCreateLengthLine(buffer, strVars, handleNotOp, smtVarDefinition, smtLenConstraints, notConstraints);
		}
	}
	pclose(in);
}

/*
 * read SMT file
 * add length constraints and write it
 */
void addLengthConstraintsToSMTFile(std::string inputFile, std::vector<std::string> lengthConstraints, std::string outFile){
	FILE* in = fopen(inputFile.c_str(), "r");
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	char buffer[5000];
	while (!feof(in))
	{
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL)
		{
			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				for (unsigned int i = 0 ; i < lengthConstraints.size(); ++i) {
					/* add length constraints */
					out << lengthConstraints[i];
					out.flush();
				}
				out << buffer;
				out.flush();
				break;
			}
			else {
				out << buffer;
				out.flush();
			}
		}
	}

	pclose(in);

	out.flush();
	out.close();
}


