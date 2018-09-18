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
	stream << "_x" << std::setfill('0') << std::setw(2) << std::hex << i;
	return stream.str();
}

/*
 * (not (= a b))
 */
std::string refine_not_equality(std::string str){
	assert(str.find("(not (") == 0);

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
		if (	i + 1 < retTmp.length() &&
				(retTmp[i - 1] == ')' 		|| retTmp[i - 1] == '(') &&
				retTmp[i] == ' ' &&
				(retTmp[i + 1] == ')'  || retTmp[i + 1] == '(') &&
				retTmp[i - 1] == retTmp[i + 1]){
			continue;
		}
		else if (retTmp[i - 1] == '(' && retTmp[i] == ' '){
			continue;
		}
		else if (i + 1 < retTmp.length() && retTmp[i + 1] == ')' && retTmp[i] == ' '){
			continue;
		}
		else
			ret = ret + retTmp[i];
	}
	__debugPrint(logFile, "%d *** %s ***: %s --> %s --> %s\n", __LINE__, __FUNCTION__, str.c_str(), retTmp.c_str(), ret.c_str());
	return ret;
}

/*
 *
 */
std::vector<std::pair<std::string, int>> replaceTokens(
		std::vector<std::pair<std::string, int>> tokens,
		int start, int finish, std::string tokenName, int tokenType){
	std::vector<std::pair<std::string, int>> tmp;
	for (int i = 0; i < start; ++i)
		tmp.emplace_back(tokens[i]);
	if (tokenName[0] == '('){
		__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, tokenName.c_str());
		std::vector<std::pair<std::string, int>> tokensTmp;
		switch (config.languageVersion) {
		case 20:
		case 25:
			tokensTmp = parseTerm20(tokenName);
			break;

		case 26:
			tokensTmp = parseTerm26(tokenName);
			break;
		default:
			assert(false);
			break;
		}
		for (unsigned i = 0; i < tokensTmp.size(); ++i) {
			__debugPrint(logFile, "%s --", tokensTmp[i].first.c_str());
			tmp.emplace_back(tokensTmp[i]);
		}
	}
	else
		tmp.push_back(std::make_pair(tokenName, tokenType));
	for (int i = finish + 1; i < (int)tokens.size(); ++i)
		tmp.emplace_back(tokens[i]);

	return tmp;
}

/*
 *
 */
std::vector<std::pair<std::string, int>> replaceTokens(std::vector<std::pair<std::string, int>> tokens,
		int start, int finish, std::vector<std::pair<std::string, int>> addTokens){
	std::vector<std::pair<std::string, int>> tmp;
	for (int i = 0; i < start; ++i)
		tmp.emplace_back(tokens[i]);
	tmp.insert(tmp.end(), addTokens.begin(), addTokens.end());
	for (int i = finish; i < (int)tokens.size(); ++i)
		tmp.emplace_back(tokens[i]);

	return tmp;
}

/*
 *
 */
std::string sumTokens(std::vector<std::pair<std::string, int>> tokens,
		int start, int finish){
	assert(start <= finish);
	std::string ret = tokens[start].first;

	for (int i = start + 1; i <= finish; ++i){
		if (tokens[i].first.compare(")") != 0 && tokens[i - 1].first.compare("(") != 0)
			ret += " ";
		ret += tokens[i].first;
	}

	return ret;
}

/*
 *
 */
int findTokens(std::vector<std::pair<std::string, int>> tokens, int startPos, std::string s, int type){
	for (int i = startPos; i < (int)tokens.size(); ++i)
		if (tokens[i].second == type && tokens[i].first.compare(s) == 0)
			return i;
	return -1;
}

/*
 *
 */
void formatOPByRewriter(StringOP &op,
		std::map<StringOP, std::string> rewriterStrMap){
	if (op.args.size() == 0){
		if (op.name.find("$$_") == 0 ||
				op.name.find(std::string(LENPREFIX) + "$$_") == 0) {
			for (const auto& opx : rewriterStrMap)
				if (opx.second.compare(op.name) == 0) {
					op = opx.first;
					return;
				}
		}
	}
	else {
		for (unsigned i = 0; i < op.args.size(); ++i) {
			if (op.args[i].name.find("$$_") == 0 ||
					op.args[i].name.find(std::string(LENPREFIX) + "$$_") == 0){
				for (const auto& opx : rewriterStrMap)
					if (opx.second.compare(op.args[i].name) == 0 &&
							opx.first.toString().find("$$_") == std::string::npos) {
						op.args[i] = opx.first;
						break;
					}
			}
			else if (op.args[i].args.size() > 0)
				formatOPByRewriter(op.args[i], rewriterStrMap);
		}
		formatOP(op);
	}
}

/*
 *
 */
StringOP findOpArg(
		std::vector<std::pair<std::string, int>> tokens,
				int &startPos){
//	__debugPrint(logFile, "\n%d *** %s ***: %s\n", __LINE__, __FUNCTION__, sumTokens(tokens, startPos, tokens.size() - 1).c_str());
	StringOP ret;
	if (tokens[startPos].second == antlrcpptest::SMTLIB26Lexer::OpenPar) {
		int tmp = findCorrespondRightParentheses(startPos, tokens);

		if  (tokens[startPos + 1].first.compare("-") == 0){
			ret = findStringOP(tokens, startPos + 1);
			formatMinusOP(ret);
		}
		else if  (tokens[startPos + 1].first.compare("+") == 0){
			ret = findStringOP(tokens, startPos + 1);
			formatPlusOP(ret);
		}
		else if  (tokens[startPos + 1].first.compare("*") == 0){
			StringOP ret = findStringOP(tokens, startPos + 1);
			formatMultiplyOP(ret);
		}
		else if (tokens[startPos + 1].first.compare("not") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare("ite") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare("implies") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare("=") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(">") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare("<") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(">=") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare("<=") == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[LENGTH]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[CONCAT]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[SUBSTRING]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[INDEXOF2]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[INDEXOF]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[LASTINDEXOF]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[TOUPPER]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[TOLOWER]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[REPLACE]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[REPLACEALL]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[STARTSWITH]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
			assert (ret.args.size() == 2);
			StringOP tmp;
			switch (config.languageVersion) {
				case 26:
				case 25:
					tmp = ret.args[0];
					ret.args[0] = ret.args[1];
					ret.args[1] = tmp;
					break;
				default:
					break;
			}
		}
		else if (tokens[startPos + 1].first.compare(config.languageMap[ENDSWITH]) == 0) {
			ret = findStringOP(tokens, startPos + 1);
			assert (ret.args.size() == 2);
			StringOP tmp;
			switch (config.languageVersion) {
			case 26:
			case 25:
				tmp = ret.args[0];
				ret.args[0] = ret.args[1];
				ret.args[1] = tmp;
				break;
			default:
				break;
			}
		}
		else {
			ret = findStringOP(tokens, startPos + 1);
		}
		startPos = tmp;
	}
	else {
		ret = StringOP(tokens[startPos].first);
	}
	return ret;
}

/*
 *
 */
StringOP findStringOP(
		std::vector<std::pair<std::string, int>> tokens,
		int startPos){
//	__debugPrint(logFile, "\n%d *** %s ***: %s\n", __LINE__, __FUNCTION__, sumTokens(tokens, startPos, tokens.size() - 1).c_str());
	StringOP op(tokens[startPos].first);

	while (true){
		startPos++;
		if (tokens[startPos].second == antlrcpptest::SMTLIB26Lexer::ClosePar){
			break;
		}
		op.addArg(findOpArg(tokens, startPos));
	}
	if (op.name.compare(config.languageMap[STARTSWITH]) == 0 ||
			op.name.compare(config.languageMap[ENDSWITH]) == 0) {
		assert (op.args.size() == 2);
		StringOP tmp;
		switch (config.languageVersion) {
		case 26:
		case 25:
			tmp = op.args[0];
			op.args[0] = op.args[1];
			op.args[1] = tmp;
			break;
		default:
			break;
		}
	}
	return op;
}

/*
 *
 */
void updateEquality(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap
		){
	int found = findTokens(tokens, 0, "=", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		assert(tokens[found - 1].second == antlrcpptest::SMTLIB26Lexer::OpenPar);
		StringOP op(findStringOP(tokens, found));
		bool foundOp = false;
		for (const auto& _op : rewriterStrMap) {
			if (_op.first == op && _op.second.compare(FALSETR) == 0) {
				tokens = replaceTokens(tokens, found - 1, findCorrespondRightParentheses(found - 1, tokens), _op.second, antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
				foundOp = true;
				break;
			}
		}

		if (foundOp)
			found = findTokens(tokens, 0, "=", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		else
			found = findTokens(tokens, found + 1, "=", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 *
 */
bool isArithmeticOP(StringOP opx, std::set<std::string> otherVars){
//	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, opx.toString().c_str());
	if (opx.name.compare(">") == 0 ||
			opx.name.compare("<") == 0 ||
			opx.name.compare(">=") == 0 ||
			opx.name.compare("<=") == 0 ||
			opx.name.compare("not") == 0 ||
			opx.name.compare("ite") == 0 ||
			opx.name.compare(config.languageMap[STARTSWITH]) == 0 ||
			opx.name.compare(config.languageMap[ENDSWITH]) == 0)
		return true;

	if (opx.name.compare("=") == 0){
		if (opx.args[0].name.compare("ite") == 0 ||
				opx.args[0].name.compare("not") == 0 ||
				opx.args[0].name.compare("+") == 0 ||
				opx.args[0].name.compare("-") == 0 ||
				opx.args[0].name.compare("*") == 0 ||
				opx.args[0].name.compare(config.languageMap[LENGTH]) == 0 ||
				opx.args[0].name.compare(config.languageMap[INDEXOF]) == 0 ||
				opx.args[0].name.compare(config.languageMap[INDEXOF2]) == 0 ||
				opx.args[0].name.compare(config.languageMap[LASTINDEXOF]) == 0 ||
				(opx.args[0].name[0] >= '0' && opx.args[0].name[0] <= '9'))
			return true;

		if (opx.args[1].name.compare("ite") == 0 ||
				opx.args[1].name.compare("not") == 0 ||
				opx.args[1].name.compare("+") == 0 ||
				opx.args[1].name.compare("-") == 0 ||
				opx.args[1].name.compare("*") == 0 ||
				opx.args[1].name.compare(config.languageMap[LENGTH]) == 0 ||
				opx.args[1].name.compare(config.languageMap[INDEXOF]) == 0 ||
				opx.args[1].name.compare(config.languageMap[INDEXOF2]) == 0 ||
				opx.args[1].name.compare(config.languageMap[LASTINDEXOF]) == 0 ||
				(opx.args[1].name[0] >= '0' && opx.args[1].name[0] <= '9'))
			return true;

		if (otherVars.find(opx.args[0].name) != otherVars.end())
			return true;

		if (otherVars.find(opx.args[1].name) != otherVars.end())
			return true;
	}
//	__debugPrint(logFile, ">> %d not ArithmeticOP\n", __LINE__);
	return false;
}

/*
 *
 */
std::string createNewIntVar(){
	intVar++;
	return "$$$___intVar" + std::to_string(intVar);
}

/*
 *
 */
std::string createNewBoolVar(){
	intVar++;
	return "$$$___boolVar" + std::to_string(intVar);
}
/*
 *
 */
std::string getStringFromRegexOP(StringOP op){

	std::string tmp = "";
	if (op.name.compare(config.languageMap[STR2REG]) == 0) {
		tmp = tmp + op.args[0].name.substr(1, op.args[0].name.length() - 2);
	}
	else if (op.name.compare(config.languageMap[REGEXALL]) == 0){
		tmp = "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|x|u|v|x|y|z)*";
	}
	else if (op.name.compare(config.languageMap[REGEXALLCHAR]) == 0){
		tmp = "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|x|u|v|x|y|z)";
	}
	else if (op.name.compare(config.languageMap[REGEXCHARRANGE]) == 0){
		tmp = "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|x|u|v|x|y|z)";
	}
	else if (op.name.compare(config.languageMap[REGEXNONE]) == 0){
		tmp = "";
	}
	else if (op.name.compare(config.languageMap[REGEXPLUS]) == 0){
		tmp = tmp + "(" + getStringFromRegexOP(op.args[0]) + ")+";
	}
	else if (op.name.compare(config.languageMap[REGEXSTAR]) == 0){
		tmp = tmp + "(" + getStringFromRegexOP(op.args[0]) + ")*";
	}
	else if (op.name.compare(config.languageMap[REGEXUNION]) == 0){
		if (op.args.size() == 1)
			tmp = tmp + getStringFromRegexOP(op.args[0]);
		else {
			std::string tmp01 = "";
			for (unsigned j = 0; j < op.args.size(); ++j)
				tmp01 = tmp01 + "(" + getStringFromRegexOP(op.args[j]) + ")|";
			tmp = tmp = tmp + tmp01.substr(0, tmp.length() - 1);
		}
	}
	else if (op.name.compare(config.languageMap[REGEXCONCAT]) == 0) {
		for (unsigned j = 0; j < op.args.size(); ++j)
			tmp = tmp + getStringFromRegexOP(op.args[j]);
	}
	return tmp;
}
/*
 *
 */
void updateNot(std::vector<std::pair<std::string, int>> &tokens,
		std::set<std::string> otherVars,
		std::vector<std::string> &smtVarDefinition){
	int found = findTokens(tokens, 0, "not", antlrcpptest::SMTLIB26Lexer::SYM_NOT);
	while (found != -1) {
		int endCond = -1;
		assert(tokens[found - 1].second == antlrcpptest::SMTLIB26Lexer::OpenPar);
		if (tokens[found + 1].second == antlrcpptest::SMTLIB26Lexer::OpenPar) {
			endCond = findCorrespondRightParentheses(found - 1, tokens);

			StringOP opx = findStringOP(tokens, found + 2);

			if (!isArithmeticOP(opx, otherVars)) {
				std::vector<std::pair<std::string, int>> addingTokens;
				addingTokens.push_back(std::make_pair("=", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
				std::string tmpVar = createNewIntVar();
				smtVarDefinition.push_back(createIntDefinition(tmpVar));
				addingTokens.push_back(std::make_pair(tmpVar, antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
				addingTokens.push_back(std::make_pair("0", antlrcpptest::SMTLIB26Lexer::NUMERAL));
				tokens = replaceTokens(tokens, found, endCond, addingTokens); /* found at ( */
				found = findTokens(tokens, found, "not", antlrcpptest::SMTLIB26Lexer::SYM_NOT);
			}
			else
				found = findTokens(tokens, found + 1, "not", antlrcpptest::SMTLIB26Lexer::SYM_NOT);
		}
		else {
			found = findTokens(tokens, found + 1, "not", antlrcpptest::SMTLIB26Lexer::SYM_NOT);
		}
	}
}

/*
 * (implies x) --> (implies bool x)
 */
void updateImplies(std::vector<std::pair<std::string, int>> &tokens,
		std::vector<std::string> &smtVarDefinition){
	int found = findTokens(tokens, 0, "implies", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int endCond = -1;
		if (tokens[found + 1].second == antlrcpptest::SMTLIB26Lexer::OpenPar) {
			endCond = findCorrespondRightParentheses(found + 1, tokens);
		}
		else {
			endCond = found + 1;
		}
		std::string tmpVar = createNewBoolVar();
		smtVarDefinition.push_back(createBoolDefinition(tmpVar));
		tokens = replaceTokens(tokens, found + 1, endCond, tmpVar, antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);

		found = findTokens(tokens, endCond, "implies", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
//	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, sumTokens(tokens, 0, tokens.size()).c_str());
}

/*
 * (RegexIn ...) --> random
 */
void updateRegexIn(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap,
		std::vector<std::string> &smtVarDefinition){
	int found = -1;
	for (unsigned i = 0; i < tokens.size(); ++i)
		if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM &&
				tokens[i].first.compare(config.languageMap[REGEXIN]) == 0) {
			found = (int)i;
			break;
		}
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op = findStringOP(tokens, found);
		/* check if it is a const string */
		std::string tmp = getStringFromRegexOP(op.args[1]);
		if (!isRegexStr(tmp)) {
			StringOP opx = StringOP("=", op.args[0], "\"" + tmp + "\"");
			__debugPrint(logFile, "%d %s\n", __LINE__, opx.toString().c_str());
			if (rewriterStrMap.find(opx) != rewriterStrMap.end()) {
				std::string tmpStr = rewriterStrMap[opx];
				if (tmpStr.compare(TRUESTR) == 0)
					tokens = replaceTokens(tokens, found - 1, pos, TRUESTR, antlrcpptest::SMTLIB26Lexer::SYM_TRUE);
				else if (tmpStr.compare(FALSETR) == 0)
					tokens = replaceTokens(tokens, found - 1, pos, FALSETR, antlrcpptest::SMTLIB26Lexer::SYM_FALSE);
				else
					assert (false);
			}
			else {
				std::vector<std::pair<std::string, int>> addingTokens;
				addingTokens.push_back(std::make_pair("=", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
				std::string tmpVar = createNewIntVar();
				smtVarDefinition.push_back(createIntDefinition(tmpVar));
				addingTokens.push_back(std::make_pair(tmpVar, antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
				addingTokens.push_back(std::make_pair("0", antlrcpptest::SMTLIB26Lexer::NUMERAL));
				tokens = replaceTokens(tokens, found, pos, addingTokens); /* found at ( */
			}
		}
		else {
			std::vector<std::pair<std::string, int>> addingTokens;
			addingTokens.push_back(std::make_pair("=", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
			std::string tmpVar = createNewIntVar();
			smtVarDefinition.push_back(createIntDefinition(tmpVar));
			addingTokens.push_back(std::make_pair(tmpVar, antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
			addingTokens.push_back(std::make_pair("0", antlrcpptest::SMTLIB26Lexer::NUMERAL));
			tokens = replaceTokens(tokens, found, pos, addingTokens); /* found at ( */
		}

		found = -1;
		for (unsigned i = found + 1; i < tokens.size(); ++i)
			if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM &&
					tokens[i].first.compare(config.languageMap[REGEXIN]) == 0) {
				found = (int)i;
				break;
			}
	}
}

/*
 * (Contains v1 v2) --> TRUE || FALSE
 */
void updateContain(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){

	int found = findTokens(tokens, 0, config.languageMap[CONTAINS], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());
		if (rewriterStrMap[op].compare(TRUESTR) == 0)
			tokens = replaceTokens(tokens, found - 1, pos, TRUESTR, antlrcpptest::SMTLIB26Lexer::SYM_TRUE);
		else
			tokens = replaceTokens(tokens, found - 1, pos, FALSETR, antlrcpptest::SMTLIB26Lexer::SYM_FALSE);

		found = findTokens(tokens, 0, config.languageMap[CONTAINS], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * (Indexof v1 v2) --> ....
 */
void updateIndexOf(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[INDEXOF], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());

		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, 0, config.languageMap[INDEXOF], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * (Indexof2 v1 v2 v3) --> ....
 */
void updateIndexOf2(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[INDEXOF2], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());

		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, 0, config.languageMap[INDEXOF2], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * (LastIndexof v1 v2) --> ....
 */
void updateLastIndexOf(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[LASTINDEXOF], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());

		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, 0, config.languageMap[LASTINDEXOF], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * (EndsWith v1 v2) --> ....
 */
void updateEndsWith(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[ENDSWITH], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());

		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, 0, config.languageMap[ENDSWITH], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * (StartsWith v1 v2) --> ....
 */
void updateStartsWith(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[STARTSWITH], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());

		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, 0, config.languageMap[STARTSWITH], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * = x (Replace ...) --> true
 */
void updateReplace(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[REPLACE], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1){
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, op.toString().c_str());
		formatOPByRewriter(op, rewriterStrMap);

		assert(rewriterStrMap.find(op) != rewriterStrMap.end());
		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, found, config.languageMap[REPLACE], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * = x (ReplaceAll ...) --> true
 */
void updateReplaceAll(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	int found = findTokens(tokens, 0, config.languageMap[REPLACEALL], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1){
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		formatOPByRewriter(op, rewriterStrMap);
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());
		tokens = replaceTokens(tokens, found - 1, pos, rewriterStrMap[op], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, found, config.languageMap[REPLACEALL], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * (Substring a b c) --> c && rewriter map
 */
void updateSubstring(
		std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap) {

	int found = findTokens(tokens, 0, config.languageMap[SUBSTRING], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	int indentCnt = 0;
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op = findStringOP(tokens, found);
		StringOP arg02 = op.args[2];
		formatOPByRewriter(op, rewriterStrMap);
		__debugPrint(logFile, "%d %s %s\n", __LINE__, indent(indentCnt).c_str(), op.toString().c_str());
		assert(rewriterStrMap.find(op) != rewriterStrMap.end());
		std::string replacement = rewriterStrMap[op];

		if (replacement[0] >= '0' && replacement[0] >= '9') {
			tokens = replaceTokens(tokens, found - 1, pos, replacement, antlrcpptest::SMTLIB26Lexer::NUMERAL);
		}
		else {
			tokens = replaceTokens(tokens, found - 1, pos, replacement, antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		}
		found = findTokens(tokens, 0, config.languageMap[SUBSTRING], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		indentCnt ++;
	}
}

/*
 * ToUpper --> len = len
 */
void updateToUpper(std::vector<std::pair<std::string, int>> &tokens) {
	int found = findTokens(tokens, 0, config.languageMap[TOUPPER], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));

		tokens = replaceTokens(tokens, found - 1, pos, op.args[0].toString(), antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, pos, config.languageMap[TOUPPER], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * ToLower --> len = len
 */
void updateToLower(std::vector<std::pair<std::string, int>> &tokens) {
	int found = findTokens(tokens, 0, config.languageMap[TOLOWER], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		tokens = replaceTokens(tokens, found - 1, pos, op.args[0].toString(), antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);

		found = findTokens(tokens, pos, config.languageMap[TOLOWER], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}


/*
 * Concat --> +
 */
void updateConcat(std::vector<std::pair<std::string, int>> &tokens) {
	// replace concat --> +
	int found = findTokens(tokens, 0, config.languageMap[CONCAT], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		tokens[found] = std::make_pair("+", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
		found = findTokens(tokens, found, config.languageMap[CONCAT], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * Length --> ""
 */
void updateLength(std::vector<std::pair<std::string, int>> &tokens) {
	// replace Length --> ""
	int found = findTokens(tokens, 0, config.languageMap[LENGTH], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		std::vector<std::pair<std::string, int>> tmp;
		for (int i = 0; i < found; ++i)
			tmp.emplace_back(tokens[i]);
		tmp.push_back(std::make_pair("+", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
		tmp.push_back(std::make_pair("0", antlrcpptest::SMTLIB26Lexer::NUMERAL));
		for (int i = found + 1; i < (int)tokens.size(); ++i)
			tmp.emplace_back(tokens[i]);
		tokens.clear();
		tokens = tmp;
		found = findTokens(tokens, found, config.languageMap[LENGTH], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 * "abcdef" --> 6
 */
void updateConst(std::vector<std::pair<std::string, int>> &tokens) {
	/* replace const --> its length */

	for (unsigned i = 0; i < tokens.size(); ++i){
		if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::STRING){
			assert(tokens[i].first.length() - 2 >= 0);
			tokens[i].first = std::to_string(tokens[i].first.length() - 2);
			tokens[i].second = antlrcpptest::SMTLIB26Lexer::NUMERAL;
		}
	}
}

/*
 * (Str2Reg x)--> x
 */
void updateStr2Regex(std::vector<std::pair<std::string, int>> &tokens){
	int found = findTokens(tokens, 0, config.languageMap[STR2REG], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));
		tokens = replaceTokens(tokens, found - 1, pos, op.args[0].toString(), antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);

		found = findTokens(tokens, pos, config.languageMap[STR2REG], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 *
 */
void updateRegexStar(std::vector<std::pair<std::string, int>> &tokens, int &regexCnt){
	std::string regexPrefix = "__regex_";

	int found = findTokens(tokens, 0, config.languageMap[REGEXSTAR], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));

		std::vector<std::pair<std::string, int>> addingTokens;
		addingTokens.push_back(std::make_pair("*", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
		for (int i = found + 1; i < pos; ++i)
			addingTokens.emplace_back(tokens[i]);
		addingTokens.push_back(std::make_pair(regexPrefix + std::to_string(regexCnt++), antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));

		tokens = replaceTokens(tokens, found, pos - 1, addingTokens);
		found = findTokens(tokens, pos, config.languageMap[REGEXSTAR], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 *
 */
void updateRegexPlus(
		std::vector<std::pair<std::string, int>> &tokens,
		int &regexCnt){
	std::string regexPrefix = "__regex_";

	int found = findTokens(tokens, 0, config.languageMap[REGEXPLUS], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		int pos = findCorrespondRightParentheses(found - 1, tokens);

		StringOP op(findStringOP(tokens, found));

		std::vector<std::pair<std::string, int>> addingTokens;
		addingTokens.push_back(std::make_pair("*", antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));
		for (int i = found + 1; i < pos; ++i)
			addingTokens.emplace_back(tokens[i]);
		addingTokens.push_back(std::make_pair(regexPrefix + std::to_string(regexCnt++), antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM));

		tokens = replaceTokens(tokens, found, pos - 1, addingTokens);
		found = findTokens(tokens, pos, config.languageMap[REGEXPLUS], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}
}

/*
 *
 */
void updateCharAt(std::vector<std::pair<std::string, int>> &tokens,
		std::map<StringOP, std::string> rewriterStrMap){
	// replace CharAt --> select
	int found = findTokens(tokens, 0, config.languageMap[CHARAT], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	while (found != -1) {
		StringOP opx = findStringOP(tokens, found);
		formatOPByRewriter(opx, rewriterStrMap);

		int tmp = findCorrespondRightParentheses(found - 1, tokens);
		std::vector<std::pair<std::string, int>> addingTokens;
		tokens = replaceTokens(tokens, found - 1, tmp, rewriterStrMap[opx], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);

		found = findTokens(tokens, found, config.languageMap[CHARAT], antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM);
	}

}

/*
 * xyz --> len_xyz
 */
void updateVariables(
		std::vector<std::pair<std::string, int>> &tokens,
		std::vector<std::string> strVars) {
	for (unsigned i = 0; i < tokens.size(); ++i) {
		if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM &&
				((std::find(strVars.begin(), strVars.end(), tokens[i].first) != strVars.end()) ||
				tokens[i].first.find("$$_str") == 0)) {
			tokens[i].first = LENPREFIX + tokens[i].first;
		}
	}
}

/*
 * contain a string variable
 */
bool strContaintStringVar(std::string notStr, std::vector<std::string> strVars) {
	if (notStr.find(LENGTH) != std::string::npos)
		return false;
	for (const auto& s : strVars) {
		if (notStr.find(s) != std::string::npos)
			return true;
	}
	return false;
}

/*
 *
 */
std::vector<std::string> _collectAlternativeComponents(std::string str){
	std::vector<std::string> result;
	int counter = 0;
	unsigned startPos = 0;
	for (unsigned j = 0; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
		}
		else if (str[j] == '('){
			counter++;
		}
		else if ((str[j] == '|' || str[j] == '~') && counter == 0) {
			result.emplace_back(str.substr(startPos, j - startPos));
			startPos = j + 1;
		}
	}
	if (startPos != 0)
		result.emplace_back(str.substr(startPos, str.length() - startPos));
	return result;
}

/*
 *
 */
int _findCorrespondRightParentheses(int leftParentheses, std::string str){
	assert (str[leftParentheses] == '(');
	int counter = 1;
	for (unsigned j = leftParentheses + 1; j < str.length(); ++j) {
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
				result.emplace_back(tmp[0]);
		}
		return result;
	}

	size_t leftParentheses = str.find('(');
	if (leftParentheses == std::string::npos)
		return {{str}};

	/* abc(def)* */
	if (leftParentheses != 0) {
		std::string header = str.substr(0, leftParentheses);
		std::vector<std::vector<std::string>> rightComponents = _parseRegexComponents(str.substr(leftParentheses));
		for (unsigned i = 0; i < rightComponents.size(); ++i) {
			std::vector<std::string> tmp = {header};
			tmp.insert(tmp.end(), rightComponents[i].begin(), rightComponents[i].end());
			result.emplace_back(tmp);
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
							result.emplace_back(tmp);
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
			for (int i = str.length() - 1; i >= 0; --i)
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
	for (unsigned i = 0; i < list.size(); ++i)
		if (list[i][0] != '\"')
			return false;
	return true;
}

/*
 * Get all chars in consts
 */
std::set<char> getUsedChars(std::string str){
	std::set<char> result;

	for (unsigned i = 1; i < str.length() - 1; ++i) {
		if (str[i] == config.escapeChar) {
			switch (config.languageVersion) {
				case 25:
				case 20:
					if (str[i + 1] == 'a')
						result.emplace('\a');
					else if (str[i + 1] == 'b')
						result.emplace('\b');
					else if (str[i + 1] == 'e')
						result.emplace('\e');
					else if (str[i + 1] == 'f')
						result.emplace('\f');
					else if (str[i + 1] == 'n')
						result.emplace('\n');
					else if (str[i + 1] == 'r')
						result.emplace('\r');
					else if (str[i + 1] == 't')
						result.emplace('\t');
					else if (str[i + 1] == 'v')
						result.emplace('\v');
					else
						result.emplace(str[i + 1]);
					i++;
					break;
				case 26:
					result.emplace(str[i + 1]);
					i++;
					break;
				default:
					assert (false);
					break;
			}
		}
		else
			result.emplace(str[i]);
	}

	return result;
}

/*
 *
 */
bool prepareEncoderDecoderMap(std::string fileName){
	FILE* in = fopen(fileName.c_str(), "r");
	if (!in) {
		printf("%d %s", __LINE__, fileName.c_str());
		throw std::runtime_error("Cannot open input file!");
	}

	std::set<char> tobeEncoded = {'?', '\\', '|', '"', '(', ')', '~', '&', '\'', '+', '%', '#', '*'};
	switch (config.languageVersion) {
		case 20:
			for (const auto& ch : escapeCharacter20)
				tobeEncoded.emplace(ch);
			break;
		case 25:
			for (const auto& ch : escapeCharacter25)
				tobeEncoded.emplace(ch);
			break;
		case 26:
			for (const auto& ch : escapeCharacter26)
				tobeEncoded.emplace(ch);
			break;
		default:
			break;
	}
	std::set<char> encoded;
	bool used[255];
	memset(used, sizeof used, false);
	std::vector<std::vector<std::pair<std::string, int>>> fileTokens;
	switch (config.languageVersion) {
	case 20:
	case 25:
		fileTokens = parseFile20(fileName);
		break;

	case 26:
		fileTokens = parseFile26(fileName);
		break;
	default:
		assert(false);
		break;
	}

	for (const auto& tokens : fileTokens) {
		for (const auto& token : tokens) {
			if (token.second == antlrcpptest::SMTLIB26Lexer::STRING) /* string */{
				std::set<char> tmp = getUsedChars(token.first);
				for (const auto& ch : tmp) {
					used[(int)ch] = true;
					if (tobeEncoded.find(ch) != tobeEncoded.end())
						encoded.emplace(ch);
				}
			}
		}
	}

	std::vector<char> unused;
	for (unsigned i = '0'; i <= '9'; ++i)
		if (used[i] == false)
			unused.emplace_back(i);

	for (unsigned i = 'a'; i <= 'z'; ++i)
		if (used[i] == false)
			unused.emplace_back(i);

	for (unsigned i = 'A'; i <= 'Z'; ++i)
			if (used[i] == false)
				unused.emplace_back(i);

	__debugPrint(logFile, "%d *** %s ***: unused = %ld, encoded = %ld\n", __LINE__, __FUNCTION__, unused.size(), encoded.size());

	if (unused.size() < encoded.size()) {
		unsigned cnt = 0;
		for (const char& ch : encoded) {
			__debugPrint(logFile, "%d *** %s ***: %c --> %c\n", __LINE__, __FUNCTION__, ch, 128 + cnt);
			ENCODEMAP[ch] = 20 + cnt;
			DECODEMAP[20 + cnt] = ch;
			cnt++;
		}
		return false;
	}
	unsigned cnt = 0;
	for (const char& ch : encoded) {
		__debugPrint(logFile, "%d *** %s ***: %c --> %c\n", __LINE__, __FUNCTION__, ch, unused[cnt]);
		ENCODEMAP[ch] = unused[cnt];
		DECODEMAP[unused[cnt]] = ch;
		cnt++;
	}
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
	int pos = s.find("GrammarIn");
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
			result = "";
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

					definitions.emplace_back("(declare-fun " + constMap[content] + std::string(REGEXSUFFIX) + " () String)\n");
					constraints.emplace_back("(assert (" + std::string(config.languageMap[REGEXIN]) + " " + constMap[content] + std::string(REGEXSUFFIX) + " (" +
													std::string(config.languageMap[REGEXSTAR]) + " (" + std::string(config.languageMap[STR2REG]) + " \"" + tmp + "\"))))\n");

					if (result.length() > 0)
						result = "("  + std::string(config.languageMap[CONCAT]) + " " + result + " " + constMap[content] + std::string(REGEXSUFFIX) + ")";
					else
						result = constMap[content] + std::string(REGEXSUFFIX);
				}
				else if (components[j].find('+') != std::string::npos) {
					unsigned int leftParentheses = components[j].find('(');
					unsigned int rightParentheses = components[j].find(')');
					std::string tmp = components[j].substr(leftParentheses + 1, rightParentheses - leftParentheses - 1);

					definitions.emplace_back("(declare-fun " + constMap[content] + std::string(REGEXSUFFIX) + " () String)\n");
					constraints.emplace_back("(assert (" + std::string(config.languageMap[REGEXIN]) + " " + constMap[content] + std::string(REGEXSUFFIX) + " (" +
													std::string(config.languageMap[REGEXSTAR]) + " (" + std::string(config.languageMap[STR2REG]) + " \"" + tmp + "\"))))\n");
					if (result.length() > 0)
						result = "("  + std::string(config.languageMap[CONCAT]) + " " + result + " " + constMap[content] + std::string(REGEXSUFFIX) + ")";
					else
						result = constMap[content] + std::string(REGEXSUFFIX);
				}
				else {
					if (result.length() > 0)
						result = "("  + std::string(config.languageMap[CONCAT]) + " " + result + " " + components[j] + ")";
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

	result = "(assert (= " + varName + " " + result + "))\n";
	constraints.emplace_back(result);
}

/*
 * replace the CFG constraint by the regex constraints
 * it is the rewriteGRM caller
 */
void toNonGRMFile(
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

			std::string tmp = buffer;
			if (tmp.find("GrammarIn") != std::string::npos) {
				rewriteGRM(tmp, equalitiesMap, constMap, definitions, constraints);
			}
			else
				constraints.emplace_back(tmp);
		}
		else
			break;
	}

	/* write everything to the file */
	for (unsigned i = 0; i < definitions.size(); ++i) {
		out << definitions[i];
	}

	for (unsigned i = 0; i < constraints.size(); ++i) {
		out << constraints[i];
	}

	if (constraints[constraints.size() - 1].find("get-model") == std::string::npos){
		out << "\n(get-model)";
	}

	out.close();
	pclose(in);
}

/*
 * "abc123" 			--> 6
 * Concat abc def --> + len_abc len_def
 * Length abc 		--> len_abc
 */
void toLengthLine(
		std::vector<std::pair<std::string, int>> tokens,
		std::vector<std::string> &strVars,
		bool handleNotOp,
		std::map<StringOP, std::string> rewriterStrMap,
		int &regexCnt,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints){

	std::set<std::string> constList;
	std::set<std::string> otherVar;

	bool declare = false;
	for (const auto& token : tokens)
		if (token.second == antlrcpptest::SMTLIB26Lexer::TOKEN_CMD_DECLARE_SORT  ||
				token.second == antlrcpptest::SMTLIB26Lexer::TOKEN_CMD_DECLARE_FUN) {
			declare = true;
			break;
		}

	if (declare == true) {
		bool stringVarDef = false;
		std::string newStr = "";
		for (const auto& token : tokens)
			if (token.second == antlrcpptest::SMTLIB26Lexer::SIMPLE_SYM && token.first.compare("String") == 0){
				stringVarDef = true;
				break;
			}

		if (stringVarDef == true) {
			smtLenConstraints.emplace_back("(assert (>= len_" + tokens[2].first + " 0))\n");
			strVars.emplace_back(tokens[2].first); /* list of string variables */

			if (tokens[2].first.find("const_") != 0)
				newStr = redefineStringVar(tokens[2].first);
			else
				newStr = "";
		}
		else {
			otherVar.emplace(tokens[2].first);
			newStr = redefineOtherVar(tokens[2].first, tokens[tokens.size() - 2].first);
		}

		if (newStr.length() > 0)
			smtVarDefinition.emplace_back(newStr);

		return;
	}

	for (unsigned i = 0; i < tokens.size(); ++i)
		if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::STRING){
			std::string s = "";
			for (unsigned j = 1; j < tokens[i].first.length() - 1; ++j) {
				if (tokens[i].first[j] == config.escapeChar){
					switch (config.languageVersion) {
					case 20:
					case 25:
						if (j + 2 < tokens[i].first.length() && tokens[i].first[j + 1] == 't') {
							s += '\t';
							++j;
						}
						else if (j + 2 < tokens[i].first.length()){
							s += tokens[i].first[j + 1];
							++j;
						}
						break;
					case 26:
						break;
					default:
						break;
					}
				}
				else
					s += tokens[i].first[j];
			}
			tokens[i].first = "\"" + s + "\"";
		}
	updateImplies(tokens, smtVarDefinition);
	updateRegexIn(tokens, rewriterStrMap, smtVarDefinition);
	updateContain(tokens, rewriterStrMap);
	updateCharAt(tokens, rewriterStrMap);
	updateLastIndexOf(tokens, rewriterStrMap);
	updateIndexOf2(tokens, rewriterStrMap);
	updateIndexOf(tokens, rewriterStrMap);
	updateEndsWith(tokens, rewriterStrMap);
	updateStartsWith(tokens, rewriterStrMap);
	updateReplace(tokens, rewriterStrMap);
	updateReplaceAll(tokens, rewriterStrMap);

	updateToUpper(tokens);
	updateToLower(tokens);
	updateSubstring(tokens, rewriterStrMap);
	updateEquality(tokens, rewriterStrMap);
	updateNot(tokens, otherVar, smtVarDefinition);
	updateConst(tokens); /* "abcdef" --> 6 */
	updateStr2Regex(tokens);
	updateRegexStar(tokens, regexCnt);
	updateRegexPlus(tokens, regexCnt);



	updateConcat(tokens); /* Concat --> + */
	updateLength(tokens); /* Length --> "" */
	updateVariables(tokens, strVars); /* xyz --> len_xyz */

//	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, sumTokens(tokens, 0, tokens.size() - 1).c_str());
	smtLenConstraints.emplace_back(sumTokens(tokens, 0, tokens.size() - 1) + "\n");
}

/*
 *
 */
std::string encodeSpecialChars(std::string constStr){
	std::string strTmp = "";

	for (unsigned i = 1 ; i < constStr.length() - 1; ++i){
		switch (config.languageVersion) {
			case 25:
			case 20:
				if (constStr[i] == config.escapeChar) {
					if (i < constStr.length() - 1) {
						if (constStr[i + 1] == 'a') {
							strTmp += ENCODEMAP['\a'];
							i++;
						} else if (constStr[i + 1] == 'b') {
							strTmp += ENCODEMAP['\b'];
							i++;
						} else if (constStr[i + 1] == 'e') {
							strTmp += ENCODEMAP['\e'];
							i++;
						} else if (constStr[i + 1] == 'f') {
							strTmp += ENCODEMAP['\f'];
							i++;
						} else if (constStr[i + 1] == 'n') {
							strTmp += ENCODEMAP['\n'];
							i++;
						} else if (constStr[i + 1] == 'r') {
							strTmp += ENCODEMAP['\r'];
							i++;
						} else if (constStr[i + 1] == 't') {
							strTmp += ENCODEMAP['\t'];
							i++;
						} else if (constStr[i + 1] == 'v') {
							strTmp += ENCODEMAP['\v'];
							i++;
						}
						else if (constStr[i + 1] == '"' ||
								constStr[i + 1] == '\'' ||
								constStr[i + 1] == '\\') {
							strTmp += ENCODEMAP[constStr[i + 1]];
							i++;
						}
						else {
							strTmp += constStr[i];
							strTmp += constStr[i];
						}
					}
					else {
						strTmp += constStr[i];
					}
				}
				else if (ENCODEMAP.find(constStr[i]) != ENCODEMAP.end())
					strTmp += ENCODEMAP[constStr[i]];
				else
					strTmp += constStr[i];
				break;
			case 26:
				if (constStr[i] == config.escapeChar) {
					if (i < constStr.length() - 1) {
						if (constStr[i + 1] == '"'){
							strTmp += ENCODEMAP['"'];
							i++;
						}
					}
					else {
						strTmp += constStr[i];
					}
				}
				else if (ENCODEMAP.find(constStr[i]) != ENCODEMAP.end())
					strTmp += ENCODEMAP[constStr[i]];
				else
					strTmp += constStr[i];
				break;
			default:
				assert (false);
				break;
		}
	}

	return '"' + strTmp + '"';
}

/*
 * replace declare-variable by declare-fun
 */
std::vector<std::string> replaceVariableDefinition(std::vector<std::pair<std::string, int>> tokens){
	std::vector<std::string> ret;
	bool found = false;
	int pos = 0;
	for (const auto& token : tokens) {
		pos++;
		if (pos == 2 && found == true)
			ret.emplace_back("()");

		if (token.first.compare("declare-variable") == 0) {
			found = true;
			ret.emplace_back("declare-fun");
			pos = 0;
		}
		else
			ret.emplace_back(token.first);
	}

	if (!found)
		return {};
	else
		return ret;
}

/*
 *
 */
bool isSetCommand(std::vector<std::pair<std::string, int>> tokens){
	if (tokens.size() > 2)
		if (tokens[1].first.find("set-") == 0){
			return true;
		}
	return false;
}

/*
 *
 */
std::vector<std::vector<std::string>> collectArgs(
		unsigned pos,
		unsigned &endPos,
		std::vector<std::string> tokens){
	std::vector<std::vector<std::string>> ret;
	assert(pos < tokens.size());
	assert(tokens[pos - 1][0] == '(');
	int cntLevel = 1;
	std::vector<std::string> arg;
	for (unsigned i = pos + 1; i < tokens.size(); ++i){
		if (tokens[i][0] == '(') {
			cntLevel++;
			arg.emplace_back(tokens[i]);
		}
		else if (tokens[i][0] == ')') {
			cntLevel--;
			if (cntLevel == 0) {
				endPos = i;
				return ret;
			}
			else {
				arg.emplace_back(tokens[i]);
				if (cntLevel == 1){
					ret.emplace_back(arg);
					arg.clear();
				}
			}
		}
		else {
			arg.emplace_back(tokens[i]);
			if (cntLevel == 1) {
				ret.emplace_back(arg);
				arg.clear();
			}
		}
	}
	assert(false);
	return ret;
}

/*
 * (concat a b c d) --> (concat a (concat b (concat c d)))
 * TODO: supporting intersection
 */
std::vector<std::string> rewriteLeftAssociationConstraints(std::vector<std::string> tokens){
	std::vector<std::string> ret;
	bool found = true;
	while (found) {
		ret.clear();
		found = false;
		unsigned i = 0;
		while (i < tokens.size()) {
			if (tokens[i].compare(config.languageMap[CONCAT]) == 0 ||
					tokens[i].compare(config.languageMap[REGEXCONCAT]) == 0 ||
					tokens[i].compare(config.languageMap[REGEXUNION]) == 0){
				/* count the number of str */
				unsigned endPos = 0;
				std::vector<std::vector<std::string>> args = collectArgs(
						i,
						endPos,
						tokens);

				if (args.size() > 2) {
					found = true;
				}
				else {
					ret.emplace_back(tokens[i++]);
					continue;
				}

				/* (concat a b c d) --> (concat a (concat b (concat c d))) */
				for (unsigned j = 0; j < args.size() - 1; ++j) {
					if (j > 0)
						ret.emplace_back("(");
					ret.emplace_back(tokens[i]);
					for (const auto& s : args[j])
						ret.emplace_back(s);
				}
				for (const auto& s : args[args.size() - 1])
					ret.emplace_back(s);
				for (unsigned j = 0; j < args.size() - 1; ++j) {
					ret.emplace_back(")");
				}
				i = endPos;
			}
			else
				ret.emplace_back(tokens[i]);
			++i;
		}
		tokens = ret;
	}
	return ret;
}


/*
 * read SMT file and get maxInt and sumInt
 */
std::pair<int, long> getAllInt(std::string inputFile){
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

	int maxInt = 0;
	long sumInt = 0;
	for (const auto& tokens : fileTokens) {
		for (const auto& token : tokens) {
			if (token.second == 82){
				int tmp = std::stoi(token.first.c_str());
				maxInt = std::max(maxInt, tmp);
				sumInt += tmp;
			}
		}
	}
	return std::make_pair(maxInt, sumInt);
}

/*
 *
 */
std::pair<std::string, std::string> getParameters(std::vector<std::pair<std::string, int>> tokens, unsigned pos){
	std::string first = "";
	std::string second = "";
	if (tokens[pos].second != antlrcpptest::SMTLIB26Lexer::OpenPar){
		first = tokens[pos++].first;
	}
	else {
		int cnt = 1;
		first = "(";
		pos++;
		while (cnt != 0){
			if (tokens[pos].second == antlrcpptest::SMTLIB26Lexer::OpenPar)
				cnt ++;
			else if (tokens[pos].second == antlrcpptest::SMTLIB26Lexer::ClosePar)
				cnt --;
			first = first + " " + tokens[pos].first;
			pos++;
		}
	}

	if (tokens[pos].second != antlrcpptest::SMTLIB26Lexer::OpenPar){
		second = tokens[pos++].first;
	}
	else {
		int cnt = 1;
		second = "(";
		pos++;
		while (cnt != 0){
			if (tokens[pos].second == antlrcpptest::SMTLIB26Lexer::OpenPar)
				cnt ++;
			else if (tokens[pos].second == antlrcpptest::SMTLIB26Lexer::ClosePar)
				cnt --;
			second = second + " " + tokens[pos].first;
			pos++;
		}
	}

	return std::make_pair(first, second);
}



/*
 *
 */
std::vector<std::string> getParameters(std::vector<std::vector<std::pair<std::string, int>>> fileTokens, unsigned pos, unsigned line){
	std::vector<std::string> ret;
	while (line < fileTokens.size()) {
		std::string str = "";
		if (fileTokens[line][pos].second != antlrcpptest::SMTLIB26Lexer::OpenPar){
			str = fileTokens[line][pos++].first;
			if (pos >= fileTokens[line].size()) {
				pos = 0;
				line++;
			}
		}
		else {
			int cnt = 1;
			str = "(";

			pos++;
			if (pos >= fileTokens[line].size()) {
				pos = 0;
				line++;
			}

			while (cnt != 0 && pos < fileTokens[line].size()){
				if (fileTokens[line][pos].second == antlrcpptest::SMTLIB26Lexer::OpenPar)
					cnt ++;
				else if (fileTokens[line][pos].second == antlrcpptest::SMTLIB26Lexer::ClosePar)
					cnt --;
				str = str + " " + fileTokens[line][pos].first;

				pos++;
				if (pos >= fileTokens[line].size()) {
					pos = 0;
					line++;
				}
			}
		}
		ret.emplace_back(str);
		if (fileTokens[line][pos].second == antlrcpptest::SMTLIB26Lexer::ClosePar)
			break;
	}

	return ret;
}


/*
 * get constraints
 */
ConstraintSet getConstraints(std::string inputFile){
	std::vector<std::vector<std::pair<std::string, int>>> fileTokens;
	ConstraintSet result;
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

	std::set<std::string> intVars;
	unsigned line = 0;
	for (const auto& tokens : fileTokens) {
		/* collect all int var */
		if (tokens.size() > 1 && tokens[1].second >= 64 && tokens[1].second <= 67) {
			if (tokens[tokens.size() - 2].first.compare("Int") == 0 ||
					tokens[tokens.size() - 2].first.compare("Bool") == 0)
				intVars.emplace(tokens[2].first);
		}
		else {
			for (unsigned i = 0; i < tokens.size(); ++i) {
				if (tokens[i].second == 92){
					if (tokens[i + 1].first.compare("=") == 0 ||
							tokens[i + 1].first.compare(">") == 0 ||
							tokens[i + 1].first.compare("<") == 0 ||
							tokens[i + 1].first.compare("<=") == 0 ||
							tokens[i + 1].first.compare(">=") == 0
							) {
						std::pair<std::string, std::string> eqArgs = getParameters(tokens, i + 2);

						if (intVars.find(eqArgs.first) != intVars.end() ||
								intVars.find(eqArgs.second) != intVars.end() ||
								eqArgs.first.find("( " + config.languageMap[LENGTH]) == 0 ||
								eqArgs.second.find("( " + config.languageMap[LENGTH]) == 0 ||
								(eqArgs.first[0] >= '1' && eqArgs.first[0] <= '9') ||
								(eqArgs.second[0] >= '1' && eqArgs.second[0] <= '9') ||
								eqArgs.first.find("( +") == 0 ||
								eqArgs.first.find("( *") == 0 ||
								eqArgs.first.find("( /") == 0 ||
								eqArgs.first.find("( -") == 0 ||
								eqArgs.second.find("( +") == 0 ||
								eqArgs.second.find("( *") == 0 ||
								eqArgs.second.find("( /") == 0 ||
								eqArgs.second.find("( -") == 0){
							result.arithmeticConstraints.emplace("(" + tokens[i + 1].first + " " + eqArgs.first + " " + eqArgs.second + ")");
						}
						else {
							result.stringConstraints.emplace("(" + tokens[i + 1].first + " " + eqArgs.first + " " + eqArgs.second + ")");
						}
					}
					else if (tokens[i + 1].first.compare("and") == 0 ||
							tokens[i + 1].first.compare("or") == 0){
						std::vector<std::string> logics = getParameters(fileTokens, i + 2, line);
						std::string tmp = "(" + tokens[i + 1].first + " ";
						for (const auto& s : logics)
							tmp = tmp + s + " ";
						tmp = tmp + ")";
						result.otherConstraints.emplace(tmp);
					}
					else {
						/* regex */
						if (i + 2 < tokens.size() && tokens[i + 1].first.compare(config.languageMap[REGEXIN]) == 0){
							std::pair<std::string, std::string> eqArgs = getParameters(tokens, i + 2);
							result.regularConstraints.emplace("(" + config.languageMap[REGEXIN] + " " + eqArgs.first + " " + eqArgs.second + ")");
						}
					}
				}
			}
		}
		line++;
	}

//	printf(">> Arithmetic Constraints\n");
//	for (const auto& s : arithmeticConstraints)
//		printf("%s\n", s.c_str());
//	printf(">> String Constraints\n");
//	for (const auto& s : stringConstraints)
//		printf("%s\n", s.c_str());
//	printf(">> Regular Constraints\n");
//	for (const auto& s : regularConstraints)
//		printf("%s\n", s.c_str());
	return result;
}

/*
 * read SMT file
 */
void encodeSpecialChars(std::string inputFile, std::string outFile){
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
	std::vector<std::vector<std::string>> newtokens;
	std::set<std::string> constStr;

	for (const auto& tokens : fileTokens) {
		for (const auto& s : tokens)
			__debugPrint(logFile, "%s ", s.first.c_str());
		__debugPrint(logFile, "\n");

		bool add = true;
		std::vector<std::string> listTokens = replaceVariableDefinition(tokens);
		if (listTokens.size() > 0) {
			/* declare-variable */
			newtokens.emplace_back(listTokens);
			continue;
		}
		else if (isSetCommand(tokens))
			continue;

		for (const auto& token : tokens) {
			if (token.second == antlrcpptest::SMTLIB26Lexer::TOKEN_CMD_GET_MODEL) { /* get model */
				config.getModel = true;
				add = false;
				break;
			}
			if (token.second == antlrcpptest::SMTLIB26Lexer::TOKEN_CMD_GET_VALUE) {
				config.getModel = true;
				add = false;
				break;
			}
			else if (token.second == antlrcpptest::SMTLIB26Lexer::STRING) /* string */{
				std::string tmp = encodeSpecialChars(token.first);
				constStr.emplace(tmp);
				listTokens.emplace_back(tmp);
			}
			else {
				listTokens.emplace_back(token.first);
			}
		}
		if (add == true) {
			listTokens = rewriteLeftAssociationConstraints(listTokens);
			newtokens.emplace_back(listTokens);
		}
	}

	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	for (const auto& tokens : newtokens) {
		for (const auto &token : tokens) {
			out << token << " ";
			out.flush();
		}
		out << "\n";
	}
	out.flush();
	out.close();
}



/*
 *
 */
std::string encodeHex(std::string constStr){
	std::string newStr = "__cOnStStR_";
	for (unsigned i = 1 ; i < constStr.length() - 1; ++i) {
		newStr = newStr + int_to_hex((int)constStr[i]);
		if (constStr[i] == '\\' && constStr[i + 1] == '\\')
			++i;
	}
	return newStr;
}

/*
 * read SMT file
 */
void encodeHex(std::string inputFile, std::string outFile){
	__debugPrint(logFile, "%d *** %s ***: %s -> %s\n", __LINE__, __FUNCTION__, inputFile.c_str(), outFile.c_str());
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
	std::vector<std::vector<std::string>> newtokens;
	std::set<std::string> constStr;
	for (const auto& tokens : fileTokens) {
		std::vector<std::string> listTokens;
		for (const auto &token : tokens) {
			if (token.second == antlrcpptest::SMTLIB26Lexer::STRING) /* string */{
				std::string tmp = encodeHex(token.first);
				constStr.emplace(tmp);
				listTokens.emplace_back(tmp);
			}
			else {
				listTokens.emplace_back(token.first);
			}
		}
		newtokens.emplace_back(listTokens);
	}

	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	for (const auto& s : constStr) {
		out << "(declare-const " << s << " String)\n";
		out.flush();
	}

	for (const auto& tokens : newtokens) {
		for (const auto &token : tokens) {
			out << token << " ";
			out.flush();
		}
		out << "\n";
	}

	out.flush();
	out.close();
}

/*
 *
 */
void defineIntVars(
		std::map<StringOP, std::string> rewriterStrMap,
		std::set<std::string> carryOnConstraints,
		std::vector<std::string> &smtVarDefinition){
	std::set<std::string> intVars;
	for (const auto& opx : rewriterStrMap){
		if (opx.second.find("$$_int") != std::string::npos){
			std::vector<std::string> tokens = parse_string_language(opx.second, " ()");
			for (const auto& token : tokens)
				if (token.find("$$_int") == 0) {
					intVars.emplace(token);
				}
		}
	}

	for (const auto& s : carryOnConstraints){
		if (s.find("$$_int") != std::string::npos){
			std::vector<std::string> tokens = parse_string_language(s, " ()");
			for (const auto& token : tokens)
				if (token.find("$$_int") == 0) {
					intVars.emplace(token);
				}
		}
	}

	for (const auto& s: intVars){
		smtVarDefinition.emplace_back(createIntDefinition(s));
		__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, smtVarDefinition[smtVarDefinition.size() - 1].c_str());
	}

}

/*
 * read SMT file
 * convert the file to length file & store it
 */
void toLengthFile(
		std::string inputFile, bool handleNotOp,
		std::set<std::string> carryOnConstraints,
		std::map<StringOP, std::string> rewriterStrMap,
		int &regexCnt,
		std::vector<std::string> &smtVarDefinition,
		std::vector<std::string> &smtLenConstraints){
	clock_t t;
	t = clock();

	smtVarDefinition.clear();
	smtLenConstraints.clear();

	defineIntVars(rewriterStrMap, carryOnConstraints, smtVarDefinition);
	std::vector<std::vector<std::string>> newtokens;
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
	std::vector<std::string> strVars;
	std::set<std::string> constStr;

	for (const auto& tokens : fileTokens) {
		toLengthLine(tokens, strVars, handleNotOp, rewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
	}
	t = clock() - t;
	__debugPrint(logFile, "%d %s: %.3f s\n", __LINE__, __FUNCTION__, ((float)t)/CLOCKS_PER_SEC);
}

/*
 *
 */
std::string decodeStr(std::string s){
	__debugPrint(logFile, "%d *** %s ***: %s: ", __LINE__, __FUNCTION__, s.c_str());
	std::string tmp = "";
	for (unsigned i = 0 ; i < s.size(); ++i) {
		tmp += s[i];
		switch (config.languageVersion) {
			case 20:
			case 25:
				if (s[i] == '\\' && i + 1 < s.size() && s[i + 1] == '\\')
					++i;
				break;
			case 26:
				break;
			default:
				break;
		}
	}
	s = tmp;
	tmp = "";

	for (unsigned i = 0; i < s.length(); ++i){
		if (DECODEMAP.find(s[i]) != DECODEMAP.end()){
			switch (config.languageVersion) {
			case 20:
			case 25:
				if ((char)DECODEMAP[s[i]] != '\t')
					tmp += (char)DECODEMAP[s[i]];
				else
					tmp += "\\t";
				break;
			case 26:
				break;
			default:
				break;
			}
		}
		else
			tmp += s[i];

	}
	__debugPrint(logFile, " %s\n", tmp.c_str());
	return tmp;
}


/*
 * read SMT file
 * add length constraints and write it
 * rewrite CFG
 */
void addConstraintsToSMTFile(
		std::string inputFile, /* nongrm file */
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
			std::string tmp = buffer;
			/* rewrite CFG */
			if (tmp.find("GrammarIn") != std::string::npos) {
				assert(false);
				// rewriteGRM(tmp, _equalMap, newVars, definitions, constraints);
			}
			else {
				constraints.emplace_back(tmp);
			}
		}
		else
			break;
	}

	/* write everything to the file */
	for (unsigned i = 0; i < constraints.size(); ++i)
		if (constraints[i].find("check-sat") == std::string::npos &&
					constraints[i].find("get-model") == std::string::npos)
		out << constraints[i];

	for (unsigned i = 0 ; i < lengthConstraints.size(); ++i) {
		/* add length constraints */
		out << lengthConstraints[i];
		out.flush();
	}
	out << "(check-sat)";
	pclose(in);

	out.flush();
	out.close();
}
