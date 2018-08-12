/*
 * utils.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */
#include "Utils.h"

std::string longestCommonTail(std::string a, std::string b){
	int posA = (int)a.length() - 1;
	int posB = (int)b.length() - 1;
	std::string ret = "";
	while(posA >= 0 && posB >= 0){
		if (a[posA] == b[posB]){
			ret = a[posA] + ret;
			posA--;
			posB--;
		}
		else break;
	}
	return ret;
}

std::string longestCommonHead(std::string a, std::string b){
	unsigned int posA = 0;
	unsigned int posB = 0;
	std::string ret = "";
	while(posA < a.length() && posB < b.length()){
		if (a[posA] == b[posB]){
			ret = ret + a[posA];
			posA++;
			posB++;
		}
		else break;
	}
	return ret;
}

int lcd(int x, int y) {
	int x1 = x;
	int y1 = y;
	if (x < y) {
		x1 = y;
		y1 = x;
	}

	int r = y1;
	while (r != 0) {
		r = x1 % y1;
		x1 = y1;
		y1 = r;
	}

	return x * y / x1;
}
/*
 * string to tokens
 */
std::vector<std::string> parse_string_language(std::string s, std::string delimiters)
{
	std::vector<std::string> result;
	char *str=new char[s.size()+1];
	str[s.size()]=0;
	memcpy(str, s.c_str(), s.size());

	char* pch;
	pch = strtok(str, delimiters.c_str());

	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok(NULL, delimiters.c_str());
	}

	return result;
}

/*
 * (abc)*__XXX -> abc
 */
std::string parse_regex_content(std::string str){
	size_t pos = str.find('*');
	if (pos == std::string::npos)
		pos = str.find('+');
	assert (pos != std::string::npos);

	return str.substr(1, pos - 2);
}

/*
 * (abc)*__XXX -> (abc)*
 */
std::string parse_regex_full_content(std::string str){
	size_t pos = str.find('*');
	if (pos == std::string::npos)
		pos = str.find('+');
	assert (pos != std::string::npos);

	return str.substr(0, pos + 1);
}

/*
 *
 */
std::string getFileNameFromFileDir(std::string fileDir){
	/*get fileName from fileDir */
	std::string fileName = "";
	for (int i = fileDir.length() - 1; i >= 0; --i)
		if (fileDir[i] != '/')
			fileName = fileDir[i] + fileName;
		else
			break;
	return fileName;
}

void displayListString(std::set<std::string> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& s : l){
		__debugPrint(logFile, "%s\n", s.c_str());
	}
	__debugPrint(logFile, "\n");
}

void displayListString(std::map<std::string, int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& s : l){
		__debugPrint(logFile, "%s\n", s.first.c_str());
	}
	__debugPrint(logFile, "\n");
}


void displayListString(std::vector<std::string> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& s : l){
		__debugPrint(logFile, "%s\n", s.c_str());
	}
	__debugPrint(logFile, "\n");
}

void displayListNumber(std::set<int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& num : l){
		__debugPrint(logFile, " %d,", num);
	}
	__debugPrint(logFile, "\n");
}

void displayListNumber(std::vector<int> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& num : l){
		__debugPrint(logFile, " %d,", num);
	}
	__debugPrint(logFile, "\n");
}

/*
 *
 */
int findCorrespondRightParentheses(int leftParentheses, std::string str){
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
int findCorrespondRightParentheses(int leftParentheses, std::vector<std::pair<std::string, int>> tokens){
	assert (tokens[leftParentheses].second == antlrcpptest::SMTLIB26Lexer::OpenPar);
	int cnt = 1;
	for (unsigned i = leftParentheses + 1 ; i < tokens.size(); ++i)
		if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::OpenPar)
			cnt++;
		else if (tokens[i].second == antlrcpptest::SMTLIB26Lexer::ClosePar) {
			cnt--;
			if (cnt == 0)
				return i;
		}
	return -1;
}

/*
 * (a) | (b) --> {a, b}
 */
std::vector<std::string> collectAlternativeComponents(std::string str){
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
	else {
		return {str};
	}

	return result;
}

/*
 *
 */
std::string orConstraint(std::set<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(or ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = *possibleCases.begin();
	}
	return result;
}

/*
 *
 */
std::string orConstraint(std::vector<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(or ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = *possibleCases.begin();
	}
	return result;
}


/*
 * create (and constraint01 constraint02 .. constraint0n)
 */
std::string andConstraint(std::vector<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(and ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = possibleCases[0];
	}
	return result;
}

/*
 *
 */
std::string andConstraint(std::set<std::string> possibleCases){
	std::string result = "";
	if (possibleCases.size() > 1) {
		result = "(and ";
		for (const auto& s : possibleCases)
			result = result + s + " ";
		result = result + ")";
	}
	else if (possibleCases.size() == 1){
		result = *possibleCases.begin();
	}
	return result;
}

/*
 *
 */
std::vector<std::pair<std::string, int>> parseTerm20(std::string term){
	ANTLRInputStream input(term);
	SMTLIB2Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	SMTLIB2Parser parser(&tokens);
	tree::ParseTree *tree = parser.term();
	SMTLIB2TermListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
	return listener.smtTokens[0];
}

/*
 *
 */
std::vector<std::vector<std::pair<std::string, int>>> parseFile20(std::string file){
	ANTLRFileStream input(file);
	SMTLIB2Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	SMTLIB2Parser parser(&tokens);
	tree::ParseTree *tree = parser.script();
	SMTLIB2ScriptListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	return listener.smtTokens;
}

/*
 *
 */
std::vector<std::pair<std::string, int>> parseTerm26(std::string term){
	ANTLRInputStream input(term);
	SMTLIB26Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	SMTLIB26Parser parser(&tokens);
	tree::ParseTree *tree = parser.term();
	SMTLIB26TermListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
	return listener.smtTokens[0];
}

/*
 *
 */
std::vector<std::vector<std::pair<std::string, int>>> parseFile26(std::string file){
	ANTLRFileStream input(file);
	SMTLIB26Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	SMTLIB26Parser parser(&tokens);
	tree::ParseTree *tree = parser.script();
	SMTLIB26ScriptListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	return listener.smtTokens;
}

/*
 *
 */
std::vector<unsigned> sort_indexes(const std::vector<std::pair<std::string, int>> &v) {

	// initialize original index locations
	std::vector<unsigned> idx(v.size());
	iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v[i1].second > v[i2].second;});

	return idx;
}

/*
 * (a)|(b | c) --> {a, b, c}
 */
std::set<std::string> extendComponent(std::string s){
	std::vector<std::string> components = collectAlternativeComponents(s);
	if (components.size() > 0) {
		if (components.size() == 1)
			return {components[0]};
		std::set<std::string> ret;
		for (unsigned int i = 0 ; i < components.size(); ++i) {
			removeExtraParentheses(components[i]);
			std::set<std::string> tmp = extendComponent(components[i]);
			ret.insert(tmp.begin(), tmp.end());
		}
		return ret;
	}
	else
		assert(false);
	return {};
}

/*
 * (a) --> a
 */
void removeExtraParentheses(std::string &s){
	while (s[0] == '(' && findCorrespondRightParentheses(0, s) == (int)s.length() - 1)
		s = s.substr(1, s.length() - 2);
}

/*
 *
 */
bool isRegexStr(std::string str){
	return str.find(")*") != std::string::npos || str.find(")+") != std::string::npos;
}

/*
 *
 */
bool isUnionStr(std::string str){
	return str.find("|") != std::string::npos;
}

/*
 *
 */
bool isConstStr(std::string str){
	if (str[0] == '"' && str.find(")*") == std::string::npos && str.find(")+") == std::string::npos)
		return true;
	else
		return false;
}

/*
 *
 */
std::string createEqualConstraint(std::string x, std::string y){
	return "(= " + x + " " + y + ")";
}

/*
 *
 */
std::string createLessEqualConstraint(std::string x, std::string y){
	return "(<= " + x + " " + y + ")";
}

/*
 *
 */
std::string createLessConstraint(std::string x, std::string y){
	return "(< " + x + " " + y + ")";
}

/*
 *
 */
std::string createPlusOperator(std::string x, std::string y){
	return "(+ " + x + " " + y + ")";
}

/*
 *
 */
std::string createPlusOperator(std::vector<std::string> list){
	if (list.size() == 0)
		return "0";
	else if (list.size() == 1)
		return list[0];

	std::string ret = "(+";
	for (const auto& s : list)
		ret = ret + " " + s;
	return ret + ")";
}


/*
 *
 */
std::string createSelectConstraint(std::string arr, std::string at){
	return "(select " + arr + " " + at + ")";
}

/*
 *
 */
std::string createModOperator(std::string x, std::string y){
	return "(mod " + x + " " + y + ")";
}

/*
 *
 */
std::string createMultiplyOperator(std::string x, std::string y){
	return "(* " + x + " " + y + ")";
}

/*
 *
 */
std::string createNotOperator(std::string x){
	return "(not " + x + ")";
}

/*
 *
 */
std::string createAssert(std::string x){
	return "(assert " + x + ")";
}

/*
 *
 */
std::string createArrayDefinition(std::string x){
	return "(declare-const " + x + " (Array Int Int))";
}

/*
 *
 */
std::string createIntDefinition(std::string x){
	return "(declare-const " + x + " Int)";
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
	return "(declare-const " + var + " " + type + ")";
}

/*
 *
 */
std::string createContainConstraint(std::string x, std::string y){
	return "(Contains " + x + " " + y + ")";
}

/*
 *
 */
std::string createStartsWithConstraint(std::string x, std::string y){
	return "(StartsWith " + x + " " + y + ")";
}

/*
 *
 */
std::string createEndsWithConstraint(std::string x, std::string y){
	return "(EndsWith " + x + " " + y + ")";
}

/*
 *
 */
void formatMinusOP(StringOP &opx){
//	__debugPrint(logFile, "%d %s: op minus: %s\n", __LINE__, __FUNCTION__, opx.toString().c_str());
	if (opx.args.size() == 2) {
		if (opx.args[0].name.compare("0") == 0) {
			if (opx.args[1].name.compare("+") == 0){
				std::vector<StringOP> tmp;
				for (unsigned i = 0; i < opx.args[1].args.size(); ++i)
					tmp.push_back(StringOP("-", opx.args[1].args[i]));
				opx = StringOP("+", tmp);
			}
			else {
				if (opx.args[1].name.compare("0") == 0)
					opx = StringOP("0");
				else
					opx = StringOP("-", opx.args[1]);
			}
		}
		else /* convert - --> + */ {
			std::vector<StringOP> tmp;
			if (opx.args[1].name.compare("+") == 0){
				for (unsigned i = 0; i < opx.args[1].args.size(); ++i) {
					if (opx.args[1].args[i].name.compare("0") == 0)
						tmp.push_back(StringOP("0"));
					else
						tmp.push_back(StringOP("-", opx.args[1].args[i]));
				}
			}
			else {
				if (opx.args[1].name.compare("0") == 0)
					tmp.push_back(StringOP("0"));
				else
					tmp.push_back(StringOP("-", opx.args[1]));
			}

			if (opx.args[0].name.compare("+") == 0)
				for (unsigned i = 0; i < opx.args[0].args.size(); ++i)
					tmp.emplace_back(opx.args[0].args[i]);
			else
				tmp.emplace_back(opx.args[0]);
			opx = StringOP("+", tmp);
			formatPlusOP(opx);
		}
	}
	else if (opx.args.size() == 1) {
		if (opx.args[0].name.compare("0") == 0)
			opx = StringOP("0");
		else {
			if (opx.args[0].name.compare("+") == 0){
				std::vector<StringOP> tmp;
				for (unsigned i = 0; i < opx.args[0].args.size(); ++i) {
					if (opx.args[0].args[i].name.compare("0") == 0)
						tmp.push_back(StringOP("0"));
					else
						tmp.push_back(StringOP("-", opx.args[0].args[i]));
				}
				opx = StringOP("+", tmp);
				formatPlusOP(opx);
			}
		}
	}
//	__debugPrint(logFile, "%d >> %s\n", __LINE__, opx.toString().c_str());
}


/*
 *
 */
void formatOP(StringOP &opx){
	if (opx.name.compare("-") == 0)
		formatMinusOP(opx);
	else if (opx.name.compare("+") == 0)
		formatPlusOP(opx);
	else if (opx.name.compare("*") == 0)
		formatMultiplyOP(opx);
}
/*
 *
 */
void formatPlusOP(StringOP &opx){
	/* remove 0 */
//	__debugPrint(logFile, "%d %s: op plus: %s\n", __LINE__, __FUNCTION__, opx.toString().c_str());
	std::vector<StringOP> elements = opx.args;
	std::vector<StringOP> args;
	unsigned pos = 0;
	while (pos < elements.size()) {
		StringOP curr = elements[pos];
		if (curr.name.compare("0") == 0){
		}
		else if (curr.name.compare("+") == 0){
			for (unsigned i = 0; i < curr.args.size(); ++i)
				elements.emplace_back(curr.args[i]);
		}
		else if (curr.name.compare("-") == 0){
			formatMinusOP(curr);
			if (curr.args.size() == 1)
				args.emplace_back(StringOP("-", curr.args[0]));
			else for (unsigned i = 0; i < curr.args.size(); ++i)
				elements.emplace_back(StringOP("-", curr.args[i]));
		}
		else
			args.emplace_back(curr);
		pos++;

	}

	opx.setArgs(args);

	/* reorder args */
	for (unsigned i = 0 ; i < opx.args.size(); ++i)
		for (unsigned j = i + 1 ; j < opx.args.size(); ++j)
			if (opx.args[i].toString().compare(opx.args[j].toString()) > 0) {
				StringOP tmp = opx.args[i];
				opx.args[i] = opx.args[j];
				opx.args[j] = tmp;
			}

	if (opx.args.size() == 1){
		opx.setName(opx.args[0].name);
		opx.setArgs(opx.args[0].args);
	}
//	__debugPrint(logFile, "%d >> %s\n", __LINE__, opx.toString().c_str());
}

/*
 *
 */
void formatMultiplyOP(StringOP &opx){
	/* remove 0 */
	std::vector<StringOP> tmpVector;
	bool remember = false;
	for (unsigned i = 0 ; i < opx.args.size(); ++i){
		std::string tmp = opx.args[i].toString();
		if (tmp.size() == 0 || tmp.compare("1") == 0){
		}
		else if (tmp.compare("(- 1)") == 0){
			remember = !remember;
		}
		else
			tmpVector.emplace_back(opx.args[i]);

	}
	if (remember && tmpVector.size() > 0)
		tmpVector[0] = StringOP("-", tmpVector[0]);
	else
		tmpVector.push_back(StringOP("-", StringOP("1")));

	if (tmpVector.size() == 0){
		opx = StringOP("1");
	}
	else if (tmpVector.size() == 1){
		opx = tmpVector[0];
	}
	else {
		opx.setArgs(tmpVector);

		/* reorder args */
		for (unsigned i = 0 ; i < opx.args.size(); ++i)
			for (unsigned j = i + 1 ; j < opx.args.size(); ++j)
				if (opx.args[i].toString().compare(opx.args[j].toString()) > 0) {
					StringOP tmp = opx.args[i];
					opx.args[i] = opx.args[j];
					opx.args[j] = tmp;
				}
	}
}


/*
 *
 */
int Z3_reviews(std::string fileName){
	std::string cmd = std::string(Z3VERIFIER) + fileName;

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("Z3 failed!");

	std::map<std::string, std::string> results;
	char buffer[5000];
	try {
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 5000, in) != NULL) {
				line = buffer;
				if (line.find("unsat") == 0) {
					return Trau_UNSAT;
				}
				if (line.find("sat") == 0) {
					return Trau_SAT;
				}
			}

		}

	} catch (...) {
		pclose(in);
		throw;
	}
	pclose(in);
	printf("Warning: Z3 returns unknown\n");
	return Trau_Unknown;
}

/*
 *
 */
int CVC4_reviews(std::string fileName){
	std::string cmd = std::string(CVC4VERIFIER) + fileName;

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("CVC4 failed!");

	std::map<std::string, std::string> results;
	char buffer[5000];
	try {
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 5000, in) != NULL) {
				line = buffer;
				if (line.find("unsat") == 0) {
					return Trau_UNSAT;
				}
				if (line.find("sat") == 0) {
					return Trau_SAT;
				}
			}

		}

	} catch (...) {
		pclose(in);
		throw;
	}
	pclose(in);
	printf("Warning: CVC4 returns unknown\n");
	return Trau_Unknown;
}

/*
 *
 */
int S3_reviews(std::string fileName){
	std::string cmd = std::string(S3VERIFIER) + " -f " + fileName;

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("S3 failed!");

	std::map<std::string, std::string> results;
	char buffer[5000];
	try {
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 5000, in) != NULL) {
				line = buffer;
				if (line.find(">> UNSAT") == 0){
					return Trau_UNSAT;
				}
				else if (line.find(">> SAT") == 0) {
					return Trau_SAT;
				}
				else if (line.find("unknown function/constant") != std::string::npos){
					unsigned pos = line.find("unknown function/constant") + std::string("unknown function/constant").length() + 1;
					std::string funcName = "";
					while (line[pos] != ' ' && line[pos] != '"' && pos < line.length())
						funcName += line[pos++];
					printf("Warning: S3P does not support some functions: %s\n", funcName.c_str());
					return Trau_Unknown;
				}
			}

		}

	} catch (...) {
		pclose(in);
		throw;
	}
	pclose(in);

	return Trau_Unknown;
}

/*
 *
 */
void verifyResult(
		int languageVersion,
		std::string fileName,
		std::string verifyingSolver,
		bool result){
	int sat;
	switch (languageVersion) {
	case 20:
		if (verifyingSolver.compare("s3") == 0) {
			sat = S3_reviews(fileName);
			if ((sat == Trau_SAT && result) || (sat == Trau_UNSAT && !result) || sat == Trau_Unknown) {
				printf("\nDouble-checked by S3P: successful.\n");
			}
			else
				assert(false);
		}
		else {
			printf("\n %s cannot check the test.\n", verifyingSolver.c_str());
		}
		break;
	case 25:

	case 26:
		if (verifyingSolver.compare("cvc4") == 0){
			sat = CVC4_reviews(fileName);
			if ((sat == Trau_SAT && result) || (sat == Trau_UNSAT && !result) || sat == Trau_Unknown) {
				printf("\nDouble-checked by %s: successful.\n", verifyingSolver.c_str());
			}
			else
				assert(false);
		}
		else if (verifyingSolver.compare("z3str3") == 0){
			sat = Z3_reviews(fileName);
			if ((sat == Trau_SAT && result) || (sat == Trau_UNSAT && !result) || sat == Trau_Unknown) {
				printf("\nDouble-checked by %s: successful.\n", verifyingSolver.c_str());
			}
			else
				assert(false);
		}
		else {
			printf("\n %s cannot check the test.\n", verifyingSolver.c_str());
		}
		break;
		break;
	default:
		break;
	}
}
