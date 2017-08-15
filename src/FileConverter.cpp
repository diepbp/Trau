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
 * (not (= a b))
 */
std::string refine_not_equality(std::string str){
	assert(str.find("(not (= ") == 0);
	int num = findCorrespondRightParentheses(5, str);

	std::string tmpStr = str.substr(5, num - 5 + 1);

	std::string retTmp = "";
	unsigned int pos = 0;
	for (pos = 0; pos < tmpStr.length(); ++pos)
		if (tmpStr[pos] == ' ')
			pos++;
		else
			break;

	/* remove all two spaces */
	for (; pos < tmpStr.length(); ++pos) {
		if (tmpStr[pos] == ' ' && tmpStr[pos + 1] == ' ')
			continue;
		else
			retTmp = retTmp + tmpStr[pos];
	}

	std::string ret = "(";
	for (unsigned int i = 1; i < retTmp.length(); ++i){
		if (	i + 1 < ret.length() &&
				(retTmp[i - 1] == ')' 		|| retTmp[i - 1] == '(') &&
				retTmp[i] == ' ' &&
				(retTmp[i + 1] == ')'  || retTmp[i + 1] == '(')){
			continue;
		}
		else
			ret = ret + retTmp[i];
	}
	__debugPrint(logFile, "%d *** %s ***: %s --> %s --> %s\n", __LINE__, __FUNCTION__, str.c_str(), retTmp.c_str(), ret.c_str());
	return ret;
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
 * (implies x) --> (implies false x)
 */
void updateImplies(std::string &s){
	std::size_t found = s.find("(implies ");
	while (found != std::string::npos) {
		unsigned int endPos = findCorrespondRightParentheses(found, s);
		unsigned int pos = found + 9;
		__debugPrint(logFile, "%d init 0: \"%s\"\n", __LINE__, s.substr(found, endPos - found + 1).c_str());
		while (s[pos] == ' ')
			pos++;

		if (s[pos] == '(')
			pos = findCorrespondRightParentheses(pos, s) + 1;
		else while (s[pos] != ' ')
			pos++;

		__debugPrint(logFile, "%d after reach a0: \"%s\"\n", __LINE__, s.substr(0, pos).c_str());

		while (s[pos] == ' ')
			pos++;

		if (s[pos] == '(')
			pos = findCorrespondRightParentheses(pos, s) + 1;
		else while (s[pos] != ' ' && pos < endPos);
			pos++;

		if (pos >= endPos) {
			/* (implies x) --> (implies false x) */
			s = s.substr(0, found) + "(implies false " + s.substr(found + 9);
			__debugPrint(logFile, "%d ** %s **: %s\n", __LINE__, __FUNCTION__, s.c_str());
			return;
		}
		return;
	}
}

/*
 * (RegexIn ...) --> TRUE
 */
void updateRegexIn(std::string &s){
	std::size_t found = s.find("(RegexIn ");
	while (found != std::string::npos) {
		unsigned int pos = findCorrespondRightParentheses(found, s);
		__debugPrint(logFile, "%d *** %s ***: s = %s\n", __LINE__, __FUNCTION__, s.c_str());

		std::string substr = s.substr(found, pos - found + 1);
		s = s.replace(found, substr.length(), "true");
		__debugPrint(logFile, "--> s = %s (substr = %s) \n", s.c_str(), substr.c_str());
		found = s.find("(RegexIn ");
	}
}

/*
 * (Contains v1 v2) --> TRUE || FALSE
 */
void updateContain(std::string &s, std::map<std::string, bool> containStrMap){
	std::size_t found = s.find("(Contains ");
	while (found != std::string::npos) {
		unsigned int pos = findCorrespondRightParentheses(found, s);
		__debugPrint(logFile, "%d *** %s ***: s = %s\n", __LINE__, __FUNCTION__, s.c_str());

		std::string substr = s.substr(found, pos - found + 1);
		if (containStrMap[substr] == true)
			s = s.replace(found, substr.length(), "true");
		else
			s = s.replace(found, substr.length(), "false");
		__debugPrint(logFile, "--> s = %s (substr = %s) \n", s.c_str(), substr.c_str());
		found = s.find("(Contains ");
	}
}

/*
 * (Indexof v1 v2) --> ....
 */
void updateIndexOf(std::string &s,
		std::map<std::string, std::string> rewriterStrMap){
	std::size_t found = s.find("(Indexof ");
	while (found != std::string::npos) {
		unsigned int pos = findCorrespondRightParentheses(found, s);
		__debugPrint(logFile, "%d *** %s ***: s = %s\n", __LINE__, __FUNCTION__, s.c_str());

		std::string substr = s.substr(found, pos - found + 1);
		s = s.replace(found, substr.length(), rewriterStrMap[substr]);

		__debugPrint(logFile, "--> s = %s (substr = %s) \n", s.c_str(), substr.c_str());
		found = s.find("(Indexof ");
	}
}

/*
 * (LastIndexof v1 v2) --> ....
 */
void updateLastIndexOf(std::string &s,
		std::map<std::string, std::string> rewriterStrMap){
	std::size_t found = s.find("(LastIndexof ");
	while (found != std::string::npos) {
		unsigned int pos = findCorrespondRightParentheses(found, s);
		__debugPrint(logFile, "%d *** %s ***: s = %s\n", __LINE__, __FUNCTION__, s.c_str());

		std::string substr = s.substr(found, pos - found + 1);
		s = s.replace(found, substr.length(), rewriterStrMap[substr]);

		__debugPrint(logFile, "--> s = %s (substr = %s) \n", s.c_str(), substr.c_str());
		found = s.find("(LastIndexof ");
	}
}

/*
 * (EndsWith v1 v2) --> ....
 */
void updateEndsWith(std::string &s,
		std::map<std::string, std::string> rewriterStrMap){
	std::size_t found = s.find("(EndsWith ");
	while (found != std::string::npos) {
		unsigned int pos = findCorrespondRightParentheses(found, s);
		__debugPrint(logFile, "%d *** %s ***: s = %s\n", __LINE__, __FUNCTION__, s.c_str());

		std::string substr = s.substr(found, pos - found + 1);
		s = s.replace(found, substr.length(), rewriterStrMap[substr]);

		__debugPrint(logFile, "--> s = %s (substr = %s) \n", s.c_str(), substr.c_str());
		found = s.find("(EndsWith ");
	}
}

/*
 * (Substring a b c) --> c
 */
void updateSubstring(std::string &s) {

	std::size_t found = s.find("(Substring ");

	while (found != std::string::npos) {
		/* reach "a" */
		unsigned int endPos = findCorrespondRightParentheses(found, s);
		unsigned int pos = found + 10;
		__debugPrint(logFile, "%d init 0: \"%s\"\n", __LINE__, s.substr(found, endPos - found + 1).c_str());
		while (s[pos] == ' ')
			pos++;
		if (s[pos] == '(')
			pos = findCorrespondRightParentheses(pos, s) + 1;
		else while (s[pos] != ' ')
			pos++;
		__debugPrint(logFile, "%d after reach a0: \"%s\"\n", __LINE__, s.substr(0, pos).c_str());
		while (s[pos] == ' ')
			pos++;

		__debugPrint(logFile, "%d after reach a: \"%s\"\n", __LINE__, s.substr(0, pos).c_str());

		/* reach "b"*/
		if (s[pos] == '(')
			pos = findCorrespondRightParentheses(pos, s) + 1;
		else while (s[pos] != ' ')
			pos++;
		__debugPrint(logFile, "%d after reach b0: \"%s\"\n", __LINE__, s.substr(0, pos).c_str());
		while (s[pos] == ' ')
			pos++;

		__debugPrint(logFile, "%d after reach b: \"%s\"\n", __LINE__, s.substr(0, pos).c_str());

		/* reach c */
		unsigned int start = pos;
		if (s[pos] == '(')
			pos = findCorrespondRightParentheses(pos, s) + 1;
		else while (s[pos] != ')' && pos < s.length()) {
			pos++;
		}

		std::string c = s.substr(start, pos - start);



		__debugPrint(logFile, "%d s = %s, c = %s, substr = %s\n", __LINE__, s.c_str(), c.c_str(), s.substr(found, endPos - found + 1).c_str());
		s.replace(found, endPos - found + 1, c);
		__debugPrint(logFile, "%d updateSubstring: c = %s --> s = %s\n", __LINE__, c.c_str(), s.c_str());

		found = s.find("(Substring ");
	}
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
	/* replace const --> its length */

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
 * (Str2Reg x)--> x
 */
void updateStr2Regex(std::string &str){
	std::size_t found = str.find("Str2Reg ");
	while (found != std::string::npos) {
		/* go back to find ( */
		unsigned int leftParentheses = found;
		while (str[leftParentheses] != '(' && leftParentheses >= 0)
			leftParentheses--;
		assert(leftParentheses >= 0);

		/* go forward to find ) */
		unsigned int rightParentheses = found;
		while (str[rightParentheses] != ')' && rightParentheses < str.length())
			rightParentheses++;

		assert(rightParentheses < str.length());

		std::string content = "";
		for (unsigned int i = found + 7; i < rightParentheses; ++i)
			if (str[i] >= '0' && str[i] <= '9') {
				content = content + str[i];
			}

		str.replace(leftParentheses , rightParentheses - leftParentheses + 1, content);
		found = str.find("Str2Reg ");
	}

}

/*
 *
 */
void updateRegexStar(std::string &str, int &regexCnt){
	std::string regexPrefix = "__regex_";
	std::size_t found = str.find("RegexStar ");
	while (found != std::string::npos) {
		/* go back to find ( */
		unsigned int leftParentheses = found;
		while (str[leftParentheses] != '(' && leftParentheses >= 0)
			leftParentheses--;
		assert(leftParentheses >= 0);

		/* go forward to find ) */
		unsigned int rightParentheses = found;
		while (str[rightParentheses] != ')' && rightParentheses < str.length())
			rightParentheses++;

		assert(rightParentheses < str.length());
		std::string content = "";
		for (unsigned int i = found + 9; i < rightParentheses; ++i)
			if (str[i] >= '0' && str[i] <= '9') {
				content = content + str[i];
			}
		str.replace(leftParentheses , rightParentheses - leftParentheses + 1, "(* " + content + " " + regexPrefix + std::to_string(regexCnt++) + ")");
		found = str.find("RegexStar ");
	}
}

/*
 *
 */
void updateRegexPlus(std::string &str, int &regexCnt){
	std::size_t found = str.find("RegexPlus ");
	while (found != std::string::npos) {
		/* go back to find ( */
		unsigned int leftParentheses = found;
		while (str[leftParentheses] != '(' && leftParentheses >= 0)
			leftParentheses--;
		assert(leftParentheses >= 0);

		/* go forward to find ) */
		unsigned int rightParentheses = found;
		while (str[rightParentheses] != ')' && rightParentheses < str.length())
			rightParentheses++;

		assert(rightParentheses < str.length());
		std::string content = "";
		for (unsigned int i = found + 9; i < rightParentheses; ++i)
			if (str[i] >= '0' && str[i] <= '9') {
				content = content + str[i];
			}
		str.replace(leftParentheses , rightParentheses - leftParentheses + 1, "(* " + content + " __regex_" + std::to_string(regexCnt++) + ")");
		found = str.find("RegexPlus ");
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
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, s.c_str());
	while (true) {
		bool change = false;
		for (unsigned int i = 0; i < s.length(); ++i)
			if (s[i] == '=')
				if (s[i-1] == '(') { /* start by (= */
					int parentheses = 1;
					int tokens = 0;

					int j = i;
					for (j = i; j < (int)s.length(); ++j) {
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
					if (tokens <= 2) {
//						  printf("%d Before s: %s\n", __LINE__, s.c_str());
						s.replace(i - 1, j - i + 2, "");
//						  printf("%d After s: %s\n", __LINE__, s.c_str());

						change = true;
						break;
					}
				}
		if (change == false)
			break;
	}
}

/*
 *
 */
std::vector<std::string> _collectAlternativeComponents(std::string str){
	std::vector<std::string> result;
	int counter = 0;
	unsigned int startPos = 0;
	for (unsigned int j = 0; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
		}
		else if (str[j] == '('){
			counter++;
		}
		else if ((str[j] == '|' || str[j] == '~') && counter == 0) {
			result.push_back(str.substr(startPos, j - startPos));
			startPos = j + 1;
		}
	}
	if (startPos != 0)
		result.push_back(str.substr(startPos, str.length() - startPos));
	return result;
}

/*
 *
 */
int _findCorrespondRightParentheses(int leftParentheses, std::string str){
	assert (str[leftParentheses] == '(');
	int counter = 1;
	for (unsigned int j = leftParentheses + 1; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
			if (counter == 0){
				return j;
			}
		}
		else if (str[j] == '('){
			counter++;
		}
	}
	return -1;
}

/*
 *
 */
std::vector<std::vector<std::string>> _parseRegexComponents(std::string str){
//	printf("%d parsing: \"%s\"\n", __LINE__, str.c_str());
	if (str.length() == 0)
		return {};

	std::vector<std::vector<std::string>> result;

	std::vector<std::string> alternativeRegex = _collectAlternativeComponents(str);
	if (alternativeRegex.size() != 0){
		for (unsigned int i = 0; i < alternativeRegex.size(); ++i) {
			std::vector<std::vector<std::string>> tmp = _parseRegexComponents(alternativeRegex[i]);
			assert(tmp.size() <= 1);
			if (tmp.size() == 1)
				result.push_back(tmp[0]);
		}
		return result;
	}

	size_t leftParentheses = str.find('(');
//	if (leftParentheses == std::string::npos || str[str.length() - 1] == '*' || str[str.length() - 1] == '+')
	if (leftParentheses == std::string::npos)
		return {{str}};

	/* abc(def)* */
	if (leftParentheses != 0) {
		std::string header = str.substr(0, leftParentheses);
		std::vector<std::vector<std::string>> rightComponents = _parseRegexComponents(str.substr(leftParentheses));
		for (unsigned int i = 0; i < rightComponents.size(); ++i) {
			std::vector<std::string> tmp = {header};
			tmp.insert(tmp.end(), rightComponents[i].begin(), rightComponents[i].end());
			result.push_back(tmp);
		}
		return result;
	}

	int rightParentheses = _findCorrespondRightParentheses(leftParentheses, str);
	if (rightParentheses < 0) {
		assert (false);
	}
	else if (rightParentheses == (int)str.length() - 1){
		/* (a) */
		return _parseRegexComponents(str.substr(1, str.length() - 2));
	}
	else if (rightParentheses == (int)str.length() - 2 && (str[str.length() - 1] == '*' || str[str.length() - 1] == '+')){
		/* (a)* */
		return {{str}};
	}

	else {
		int pos = rightParentheses;
		std::string left, right;
		if (str[rightParentheses + 1] == '*' || str[rightParentheses + 1] == '+'){
			pos++;
			left = str.substr(leftParentheses, pos - leftParentheses + 1);
			right = str.substr(pos + 1);
		}
		else if (str[pos] != '|' || str[pos] != '~') {
			left = str.substr(leftParentheses + 1, pos - leftParentheses - 1);
			right = str.substr(pos + 1);
		}
		else {
			assert (false);
			/* several options ab | cd | ef */
		}

		if (str[pos] != '|' || str[pos] != '~') {
			std::vector<std::vector<std::string>> leftComponents = _parseRegexComponents(left);
			std::vector<std::vector<std::string>> rightComponents = _parseRegexComponents(right);
			if (leftComponents.size() > 0) {
				if (rightComponents.size() > 0) {
					for (unsigned int i = 0; i < leftComponents.size(); ++i)
						for (unsigned int j = 0; j < rightComponents.size(); ++j) {
							std::vector<std::string> tmp;
							tmp.insert(tmp.end(), leftComponents[i].begin(), leftComponents[i].end());
							tmp.insert(tmp.end(), rightComponents[j].begin(), rightComponents[j].end());
							result.push_back(tmp);
						}
				}
				else {
					result.insert(result.end(), leftComponents.begin(), leftComponents.end());
				}
			}
			else {
				if (rightComponents.size() > 0) {
					result.insert(result.end(), rightComponents.begin(), rightComponents.end());
				}
			}

			return result;
		}
	}
	return {};
}

/*
 * AutomataDef to const
 */
std::string extractConst(std::string str) {
	if (str[0] == '(' && str[str.length() - 1] == ')') { /*(..)*/
		str = str.substr(1, str.length() - 2);
		/* find space */
		std::size_t found = str.find(' ');
		assert (found != std::string::npos);
		found = found + 1;
		/* find $$ */
		if (found >= str.length())
			return "";
		if (str[found] == '$') {
			if (str[found + 1] == '$') {
				/* find !! */
				found = str.find("!!");
				assert (found != std::string::npos);
				found = found + 2;
				str = "\"" + str.substr(found) + "\"";
			}
		}
		else {
			str = str.substr(found);
			if (str.length() > 2)
				if (str[0] == '|') {
					str = str.substr(1, str.length() - 2);
					if (str[0] == '\"')
						str = str.substr(1, str.length() - 2);
				}

			str = "\"" + str + "\"";
		}
	}
	else {
		assert (str[0] == '\"');
		if (str[str.length() - 1] == '\"')
			str = str.substr(1, str.length() - 2);
		else {
			/* "abc"_number */
			for (unsigned int i = str.length() - 1; i >= 0; --i)
				if (str[i] == '_') {
					assert (str[i - 1] == '\"');
					str = str.substr(1, i - 2);
					break;
				}
		}
		if (str[0] == '$') {
			if (str[1] == '$') {
				/* find !! */
				std::size_t found = str.find("!!");
				assert (found != std::string::npos);
				found = found + 2;
				str = str.substr(found);
			}
		}
		str = "\"" + str + "\"";
	}
	__debugPrint(logFile, "%d extractConst: --%s--\n", __LINE__, str.c_str());
	return str;
}

/*
 * check whether the list does not have variables
 */
bool hasNoVar(std::vector<std::string> list){
	for (unsigned int i = 0; i < list.size(); ++i)
		if (list[i][0] != '\"')
			return false;
	return true;
}

/*
 * "GrammarIn" -->
 * it is the rewriteGRM callee
 */
void rewriteGRM(std::string s,
		std::map<std::string, std::vector<std::vector<std::string>>> equalitiesMap,
		std::map<std::string, std::string> constMap,
		std::vector<std::string> &definitions,
		std::vector<std::string> &constraints) {

	__debugPrint(logFile, "%d CFG constraint: %s\n", __LINE__, s.c_str());
	/* step 1: collect var that is the next token after GrammarIn */
	unsigned int pos = s.find("GrammarIn");
	assert(pos != std::string::npos);

	assert(s[pos + 9] == ' ');
	pos = pos + 9;
	while (s[pos] == ' ' && pos < s.length())
		pos++;

	std::string varName = "";
	while (s[pos] != ' ' && pos < s.length()) {
		varName = varName + s[pos];
		pos++;
	}

	__debugPrint(logFile, "%d CFG var: %s\n", __LINE__, varName.c_str());

	//assert(equalitiesMap[varName].size() > 0);

	/* step 2: collect the regex value of varName*/
	std::string result = "";
	for (unsigned int i = 0; i < equalitiesMap[varName].size(); ++i) {
		if (hasNoVar(equalitiesMap[varName][i])) {

			std::vector<std::string> components = equalitiesMap[varName][i];

			displayListString(components, "zxxxxxxxxx");

			/* create concat for each pair */
			for (unsigned int j = 0; j < components.size(); ++j) {
				std::string content = components[j].substr(1, components[j].length() - 2);
				if (components[j].find('*') != std::string::npos) {
					unsigned int leftParentheses = components[j].find('(');
					unsigned int rightParentheses = components[j].find(')');

					std::string tmp = components[j].substr(leftParentheses + 1, rightParentheses - leftParentheses - 1);
					__debugPrint(logFile, "%d: lhs = %d, rhs = %d, str = %s --> %s (%s) \n", __LINE__, leftParentheses, rightParentheses, components[j].c_str(), tmp.c_str(), constMap[content].c_str());

					definitions.push_back("(declare-fun " + constMap[content] + "_100 () String)\n");
					constraints.push_back("(assert (RegexIn " + constMap[content] + "_100 (RegexStar (Str2Reg \"" + tmp + "\"))))\n");

					if (result.length() > 0)
						result = "(Concat " + result + " " + constMap[content]+ "_100)";
					else
						result = constMap[content] + "_100";
				}
				else if (components[j].find('+') != std::string::npos) {
					unsigned int leftParentheses = components[j].find('(');
					unsigned int rightParentheses = components[j].find(')');
					std::string tmp = components[j].substr(leftParentheses + 1, rightParentheses - leftParentheses - 1);

					definitions.push_back("(declare-fun " + constMap[content] + "_100 () String)\n");
					constraints.push_back("(assert (RegexIn " + constMap[content] + "_100 (RegexPlus (Str2Reg \"" + tmp + "\"))))\n");
					if (result.length() > 0)
						result = "(Concat " + result + " " + constMap[content]+ "_100)";
					else
						result = constMap[content] + "_100";
				}
				else {
					if (result.length() > 0)
						result = "(Concat " + result + " " + components[j] + ")";
					else
						result = components[j];
				}
			}
		}
		else {
			__debugPrint(logFile, "%d rewriteGRM something here: equalMap size = %ld\n", __LINE__, equalitiesMap[varName][i].size());
			// displayListString(_equalMap[varName][i], "\t>> ");
		}
	}

	//assert(result.length() > 0);

	result = "(assert (= " + varName + " " + result + "))\n";
	constraints.push_back(result);
	__debugPrint(logFile, "%d >> %s\n", __LINE__, result.c_str());
}

/*
 * replace the CFG constraint by the regex constraints
 * it is the rewriteGRM caller
 */
void rewriteGRM_toNewFile(
		std::string inputFile,
		std::string outFile,
		std::map<std::string, std::vector<std::vector<std::string>>> equalitiesMap,
		std::map<std::string, std::string> constMap) {
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	FILE* in = fopen(inputFile.c_str(), "r");
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	if (!in){
		printf("%d %s", __LINE__, inputFile.c_str());
		throw std::runtime_error("Cannot open input file!");
	}

	std::vector<std::string> definitions;
	std::vector<std::string> constraints;

	char buffer[5000];
	std::vector<std::string> strVars;

	while (!feof(in)){
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL){

			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				break;
			}
			else {
				std::string tmp = buffer;
				if (tmp.find("GrammarIn") != std::string::npos) {
					rewriteGRM(tmp, equalitiesMap, constMap, definitions, constraints);
				}
				else
					constraints.push_back(tmp);
			}
		}
	}

	/* write everything to the file */
	for (unsigned int i = 0; i < definitions.size(); ++i) {
		out << definitions[i];
	}

	for (unsigned int i = 0; i < constraints.size(); ++i) {
		out << constraints[i];
	}

	out << "(check-sat)\n(get-model)\n";
	out.close();
	pclose(in);
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
		std::map<std::string, bool> containStrMap,
		std::map<std::string, std::string> rewriterStrMap,
		int &regexCnt,
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

			if (tokens[1].find("const_") != 0)
				str = redefineStringVar(tokens[1]);
			else
				str = "";
		}
		else {
			str = redefineOtherVar(tokens[1], tokens[tokens.size() - 1]);
		}

		if (str.length() > 0)
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
		bool lastParentheses = false;

		for (unsigned int i = 0; i < strTmp.length(); ++i) {
			bool reduceSize = false;
			if (strTmp[i] == '"') {
				if (textState == 1){
					textState = 2;
					if (constStr.length() > 0) {
						constStr = "\"" + constStr + "\"";
						constList.insert(constStr);
						constStr = "";
					}
					else {
						constStr = "\"" + constStr + "\"";
						constList.insert(constStr);
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
				if (strTmp[i] == '?') {
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
				else if (strTmp[i] == '~') {
					strTmp[i] = 'M';
				}
				else if (strTmp[i] == '!') {
					strTmp[i] = 'N';
				}
				else if (strTmp[i] == '@') {
					strTmp[i] = 'O';
				}
				else if (strTmp[i] == '#') {
					strTmp[i] = 'P';
				}
				else if (strTmp[i] == '$') {
					strTmp[i] = 'Q';
				}
				else if (strTmp[i] == '%') {
					strTmp[i] = 'R';
				}
				else if (strTmp[i] == '^') {
					strTmp[i] = 'S';
				}
				else if (strTmp[i] == '&') {
					strTmp[i] = 'T';
				}
				else if (strTmp[i] == '*') {
					strTmp[i] = 'U';
				}
				else if (strTmp[i] == '+') {
					strTmp[i] = 'V';
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
						notBool = abs(bracketCnt + 1);
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
					if (!reduceSize)
						notStr = notStr + strTmp[i];
					if (handleNotOp || !strContaintStringVar(notStr, strVars)) {
						/* not (= x "abc")*/
						newStr = newStr + notStr;
					}
					else {
						notStr = refine_not_equality(notStr);
						__debugPrint(logFile, "%d not constraint: %s\n", __LINE__, notStr.c_str());
						if (rewriterStrMap.find(notStr) != rewriterStrMap.end()) {
							if (rewriterStrMap[notStr] == "true")
								newStr = newStr + "false";
							else
								newStr = newStr + "true";
						}
						else {
							notConstraints.push_back(notStr);
							// remove this constraint
							changeByNotOp = true;
							newStr = newStr + "";
						}
					}
					lastParentheses = true;
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
				if (!reduceSize && lastParentheses == false)
					newStr = newStr + strTmp[i];
			}
			else {
				if (!reduceSize) {
					notStr = notStr + strTmp[i];
				}
			}
			lastParentheses = false;
		}
		__debugPrint(logFile, "%d step 00 %s\n", __LINE__, newStr.c_str());
		if (changeByNotOp) {
			checkAssignWellForm(newStr);
			changeByNotOp = false;
		}
		/* skip this assertion because of NotOp*/
		if (newStr.find("(assert )") != std::string::npos || newStr.find("(assert  )") != std::string::npos)
			return;

		updateImplies(newStr);
		updateRegexIn(newStr);
		updateContain(newStr, containStrMap);
		updateLastIndexOf(newStr, rewriterStrMap);
		updateIndexOf(newStr, rewriterStrMap);
		updateEndsWith(newStr, rewriterStrMap);


		updateConst(newStr, constList); /* "abcdef" --> 6 */
//		printf("%d step 02 %s\n", __LINE__, newStr.c_str());
		updateStr2Regex(newStr);
//		printf("%d step 03 %s\n", __LINE__, newStr.c_str());
		updateRegexStar(newStr, regexCnt);
//		printf("%d step 04 %s\n", __LINE__, newStr.c_str());
		updateRegexPlus(newStr, regexCnt);
//		printf("%d step 05 %s\n", __LINE__, newStr.c_str());
//		updateRegexIn(newStr);
//		 printf("%d step 06 %s\n", __LINE__, newStr.c_str());
		updateSubstring(newStr);


		updateConcat(newStr); /* Concat --> + */
		updateLength(newStr); /* Length --> "" */
		updateVariables(newStr, strVars); /* xyz --> len_xyz */

		__debugPrint(logFile, "%d newStr: %s\n",__LINE__, newStr.c_str());
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
			if (strTmp[i] == '?') {
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
			else if (strTmp[i] == '~') {
				strTmp[i] = 'M';
			}
			else if (strTmp[i] == '!') {
				strTmp[i] = 'N';
			}
			else if (strTmp[i] == '@') {
				strTmp[i] = 'O';
			}
			else if (strTmp[i] == '#') {
				strTmp[i] = 'P';
			}
			else if (strTmp[i] == '$') {
				strTmp[i] = 'Q';
			}
			else if (strTmp[i] == '%') {
				strTmp[i] = 'R';
			}
			else if (strTmp[i] == '^') {
				strTmp[i] = 'S';
			}
			else if (strTmp[i] == '&') {
				strTmp[i] = 'T';
			}
			else if (strTmp[i] == '*') {
				strTmp[i] = 'U';
			}
			else if (strTmp[i] == '+') {
				strTmp[i] = 'V';
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
				constStr.insert("__cOnStStR_" + constString);
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
	if (!in)
	{
		printf("%d %s", __LINE__, inputFile.c_str());
		throw std::runtime_error("Cannot open input file!");
	}
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
	if (!in)
		throw std::runtime_error("Cannot open input file!");
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
		std::map<std::string, bool> containStrMap,
		std::map<std::string, std::string> rewriterStrMap,
		int &regexCnt,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints,
		std::vector<std::string> &notConstraints){
	smtVarDefinition.clear();
	smtLenConstraints.clear();
	notConstraints.clear();
	FILE* in = fopen(inputFile.c_str(), "r");
	if (!in){
		printf("%d %s", __LINE__, inputFile.c_str());
		throw std::runtime_error("Cannot open input file!");
	}

	char buffer[5000];
	std::vector<std::string> strVars;

	while (!feof(in)){
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL){
			/* convert that line to length constraints */
			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				break;
			}
			customizeLine_ToCreateLengthLine(buffer, strVars, handleNotOp, containStrMap, rewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints, notConstraints);
		}
	}

	__debugPrint(logFile, "Print smtLength: %d \n", __LINE__);
	displayListString(smtLenConstraints, "");
	pclose(in);
}

/*
 * read SMT file
 * add length constraints and write it
 * rewrite CFG
 */
void addLengthConstraintsToSMTFile(std::string inputFile, /* nongrm file */
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::vector<std::string> lengthConstraints,
		std::string outFile){
	FILE* in = fopen(inputFile.c_str(), "r");
	if (!in) {
		printf("%d %s", __LINE__, inputFile.c_str());
		throw std::runtime_error("Cannot open input file!");
	}
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	std::vector<std::string> constraints;

	char buffer[5000];

	while (!feof(in)) {
		/* read a line */
		if (fgets(buffer, 5000, in) != NULL){
			if (strcmp("(check-sat)", buffer) == 0 || strcmp("(check-sat)\n", buffer) == 0) {
				break;
			}
			else {
				std::string tmp = buffer;
				/* rewrite CFG */
				if (tmp.find("GrammarIn") != std::string::npos) {
					assert(false);
					// rewriteGRM(tmp, _equalMap, newVars, definitions, constraints);
				}
				else {
					constraints.push_back(tmp);
				}
			}
		}
	}

	/* write everything to the file */
	for (unsigned int i = 0; i < constraints.size(); ++i)
		out << constraints[i];

	for (unsigned int i = 0 ; i < lengthConstraints.size(); ++i) {
		/* add length constraints */
		out << lengthConstraints[i];
		out.flush();
	}

	out << "(check-sat)\n(get-model)\n";

	pclose(in);

	out.flush();
	out.close();
}


