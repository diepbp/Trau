/*
 * StringTheory.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: diepbp
 */

#include "StringTheory.h"

FILE * logFile = NULL;
FILE * logAxiom = NULL;
int sLevel = 0;
int searchStart = 0;
int tmpStringVarCount = 0;
int tmpIntVarCount = 0;
int tmpBoolVarCount = 0;

int numOfFlats;
bool lengthDefined = false;
bool languageDefined = false;
bool done = false;
bool assignedConcrete = false;
bool skipUnderApprox;

int varCnt = 0;
int value_count = 0;
Z3_ast emptyConstStr;

int nondeterministicCounter = 0;
bool lengthEnable = false;

bool havingGrmConstraints = false;
bool unknownResult = false;

clock_t timer;

std::map<Z3_ast, Z3_ast> toUpperMap;
std::map<Z3_ast, Z3_ast> toLowerMap;

std::map<StringOP, std::string> subStrStrMap;
std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> subStrNodeMap;

std::map<std::pair<Z3_ast, Z3_ast>, std::vector<Z3_ast>> indexOf_toAstMap;
std::map<std::pair<std::pair<Z3_ast, Z3_ast>, Z3_ast>, std::vector<Z3_ast>> indexOf2_toAstMap;
std::map<std::pair<Z3_ast, Z3_ast>, std::vector<Z3_ast>> lastIndexOf_toAstMap;

std::map<StringOP, std::pair<std::string, std::string>> charAtStrMap;
std::map<StringOP, std::pair<std::string, std::pair<std::string, std::string>>> indexOfStrMap;
std::map<StringOP, std::pair<std::string, std::pair<std::string, std::string>>> indexOf2StrMap;

std::map<StringOP, std::pair<std::string, std::pair<std::string, std::string>>> lastIndexOfStrMap;
std::map<StringOP, std::string> endsWithStrMap;
std::map<StringOP, std::string> startsWithStrMap;

std::map<StringOP, std::string> replaceStrMap;
std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> replaceNodeMap;

std::map<StringOP, std::string> replaceAllStrMap;
std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> replaceAllNodeMap;

std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> endsWithPairBoolMap;
std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> startsWithPairBoolMap;

std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> containNodeMap;
std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> containPairBoolMap;
std::map<Z3_ast, std::set<std::pair<Z3_ast, Z3_ast> > > containPairIdxMap;

std::map<Z3_ast, Z3_ast> carryOn;

//std::set<char> charSet;
std::vector<Z3_ast> consideredVars;
std::map<std::pair<Z3_ast, int>, Z3_ast> parikh_Node_map;
std::map<Z3_ast, Z3_ast> length_astNode_map;
std::map<Z3_ast, int> inputVarMap;
std::map<Z3_ast, int> intInputVarMap;
std::set<Z3_ast> inputVarInLen;
std::set<Z3_ast> internalStrVars;

std::map<std::string, int> initLength;

std::map<Z3_ast, std::vector<Z3_ast>> children_Map;
int leavePos = 0;

std::map<std::string, Automaton> string_automaton_Map;
std::map<Z3_ast, std::vector<Z3_ast>> language_Map;
std::map<Z3_ast, std::vector<Z3_ast>> concrete_value_Map;
std::map<Z3_ast, int> lang_value_Map;
std::map<Z3_ast, Z3_ast> final_value_Map;
std::map<std::vector<Z3_ast>, int> lang_value_Map1;
std::map<std::vector<std::pair<Z3_ast, int>>, Z3_ast> lang_value_Map2;

std::map<std::pair<Z3_ast, int>, std::string> tmpInternalVarMap;
std::map<std::pair<Z3_ast, int>, Automaton> internalVarMap;
std::map<std::pair<Z3_ast, int>, Automaton> internalVarMap_withoutCombination;
std::map<std::pair<Z3_ast, int>, std::vector<Z3_ast>> equalMap;
std::map<std::pair<Z3_ast, int>, std::pair<int, int>> length_LanguageMap;
std::map<Z3_ast, std::string> finalValues;


std::map<std::pair<Z3_ast, std::string>, Z3_ast> regexInBoolMap;
std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> concat_astNode_map;
std::map<Z3_ast, Z3_ast> grm_astNode_map;
std::map<std::string, Z3_ast> constStr_astNode_map;
std::map<Z3_ast, int> basicStrVarAxiom_added;

std::map<StringOP, StringOP> internalVarFunctionMap;

std::vector<std::pair<std::pair<Z3_ast, Z3_ast>, int>> disequalityList;
extern ConstraintSet constraintSet;
extern bool printingConstraints;

const std::string escapeDict[] = { "\\x00", "\\x01", "\\x02", "\\x03", "\\x04", "\\x05", "\\x06", "\\x07", "\\x08", "\\t", "\\n", "\\x0b", "\\x0c",
		"\\r", "\\x0e", "\\x0f", "\\x10", "\\x11", "\\x12", "\\x13", "\\x14", "\\x15", "\\x16", "\\x17", "\\x18", "\\x19", "\\x1a", "\\x1b", "\\x1c",
		"\\x1d", "\\x1e", "\\x1f", " ", "!", "\\\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6",
		"7", "8", "9", ":", ";", "<", "=", ">", "?", "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
		"T", "U", "V", "W", "X", "Y", "Z", "[", "\\\\", "]", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
		"p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~", "\\x7f", "\\x80", "\\x81", "\\x82", "\\x83", "\\x84", "\\x85", "\\x86",
		"\\x87", "\\x88", "\\x89", "\\x8a", "\\x8b", "\\x8c", "\\x8d", "\\x8e", "\\x8f", "\\x90", "\\x91", "\\x92", "\\x93", "\\x94", "\\x95", "\\x96",
		"\\x97", "\\x98", "\\x99", "\\x9a", "\\x9b", "\\x9c", "\\x9d", "\\x9e", "\\x9f", "\\xa0", "\\xa1", "\\xa2", "\\xa3", "\\xa4", "\\xa5", "\\xa6",
		"\\xa7", "\\xa8", "\\xa9", "\\xaa", "\\xab", "\\xac", "\\xad", "\\xae", "\\xaf", "\\xb0", "\\xb1", "\\xb2", "\\xb3", "\\xb4", "\\xb5", "\\xb6",
		"\\xb7", "\\xb8", "\\xb9", "\\xba", "\\xbb", "\\xbc", "\\xbd", "\\xbe", "\\xbf", "\\xc0", "\\xc1", "\\xc2", "\\xc3", "\\xc4", "\\xc5", "\\xc6",
		"\\xc7", "\\xc8", "\\xc9", "\\xca", "\\xcb", "\\xcc", "\\xcd", "\\xce", "\\xcf", "\\xd0", "\\xd1", "\\xd2", "\\xd3", "\\xd4", "\\xd5", "\\xd6",
		"\\xd7", "\\xd8", "\\xd9", "\\xda", "\\xdb", "\\xdc", "\\xdd", "\\xde", "\\xdf", "\\xe0", "\\xe1", "\\xe2", "\\xe3", "\\xe4", "\\xe5", "\\xe6",
		"\\xe7", "\\xe8", "\\xe9", "\\xea", "\\xeb", "\\xec", "\\xed", "\\xee", "\\xef", "\\xf0", "\\xf1", "\\xf2", "\\xf3", "\\xf4", "\\xf5", "\\xf6",
		"\\xf7", "\\xf8", "\\xf9", "\\xfa", "\\xfb", "\\xfc", "\\xfd", "\\xfe", "\\xff" };

void string_theory()
{
	Z3_ast t1, t2, t3;
	Z3_context ctx;
	Z3_theory Th;
	printf("\nsimple_example4\n");
	ctx = mk_context();
	Th = mk_theory(ctx);
	//    AutomatonStringData * td;
	//    td = (AutomatonStringData*)Z3_theory_get_ext_data(Th);

	t1  = mk_int_var(ctx, "t1");
	t2  = mk_int_var(ctx, "t2");
	t3  = mk_int_var(ctx, "t3");

	Z3_assert_cnstr(ctx, Z3_mk_ge(ctx, t1, mk_int(ctx, 0)));
	Z3_assert_cnstr(ctx, Z3_mk_ge(ctx, t2, mk_int(ctx, 0)));
	Z3_assert_cnstr(ctx, Z3_mk_ge(ctx, t3, mk_int(ctx, 0)));
	// 1 = t1
	Z3_assert_cnstr(ctx, Z3_mk_eq(ctx, t1, mk_int(ctx, 1)));

	// t1 = t2
	Z3_assert_cnstr(ctx, Z3_mk_eq(ctx, t2, t1));


	// t2 + t3 = t3 + 1
	Z3_ast t21[2] = {t3, t2};
	Z3_ast t22[2] = {t3, mk_int(ctx, 1)};
	Z3_assert_cnstr(ctx, Z3_mk_eq(ctx, Z3_mk_add(ctx, 2, t21), Z3_mk_add(ctx, 2, t22)));

	// printf("Context:\n%s\n", Z3_context_to_string(ctx));
	check(Th);
	Z3_del_context(ctx);
}

/**
   \brief exit gracefully in case of error.
 */
void exitf(const char* message)
{
	fprintf(stderr,"BUG: %s.\n", message);
	exit(1);
}

/**
   \brief Simpler error handler.
 */
void error_handler(Z3_context ctx, Z3_error_code e)
{
	printf("Error code: %d\n", e);
	exitf("incorrect use of Z3");
}


/**
   \brief Create a logical context.

   Enable model construction. Other configuration parameters can be passed in the cfg variable.

   Also enable tracing to stderr and register custom error handler.
 */
Z3_context mk_context_custom(Z3_config cfg)
{
	Z3_context ctx;

	Z3_set_param_value(cfg, "MODEL", TRUESTR);
	ctx = Z3_mk_context(cfg);
	Z3_set_error_handler(ctx, error_handler);

	//    Z3_set_error_handler(ctx, error_handler);

	return ctx;
}

/**
   \brief Create a logical context.

   Enable model construction only.

   Also enable tracing to stderr and register standard error handler.
 */
Z3_context mk_context(){
	Z3_config  cfg;
	Z3_context ctx;
	cfg = Z3_mk_config();
	ctx = mk_context_custom(cfg);
	Z3_del_config(cfg);
	return ctx;
}



/*
 *
 */
Z3_ast mk_str_value(Z3_theory t, char const * str) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData *) Z3_theory_get_ext_data(t);

	// if the empty string is not created, create one
	if (constStr_astNode_map.find("") == constStr_astNode_map.end()) {
		Z3_symbol empty_str_sym = Z3_mk_string_symbol(ctx, "\"\"");
		constStr_astNode_map[""] = Z3_theory_mk_value(ctx, t, empty_str_sym, td->String);
	}

	std::string keyStr = std::string(str);

	// if the str is not created, create one
	if (constStr_astNode_map.find(keyStr) == constStr_astNode_map.end()) {
		Z3_symbol str_sym = Z3_mk_string_symbol(ctx, str);
		Z3_ast strNode = Z3_theory_mk_value(ctx, t, str_sym, td->String);
		constStr_astNode_map[keyStr] = strNode;
	}
	return constStr_astNode_map[keyStr];
}

/*
 *
 */
Z3_ast mk_internal_string_var(Z3_theory t){
	std::stringstream ss;
	ss << tmpStringVarCount++;
	std::string name = "$$_str" + ss.str();
	Z3_ast strVar = mk_str_var(t, name.c_str());
	internalStrVars.emplace(strVar);

//	std::string language = createGenericLanguage(t, strVar, charSet);
//	Z3_ast langAxiom = createLanguageAxiom(t, strVar, language);
//	addAxiom(t, langAxiom, __LINE__,true);

	return strVar;
}

/*
 *
 */
Z3_ast mk_internal_int_var(Z3_theory t){
	Z3_context ctx = Z3_theory_get_context(t);
	std::stringstream ss;
	ss << tmpIntVarCount++;
	std::string name = "$$_int" + ss.str();
	return mk_int_var(ctx, name.c_str());
}

/*
 *
 */
Z3_ast mk_internal_bool_var(Z3_theory t){
	Z3_context ctx = Z3_theory_get_context(t);
	std::stringstream ss;
	ss << tmpBoolVarCount++;
	std::string name = "$$_bool" + ss.str();
	return mk_bool_var(ctx, name.c_str());
}

/*
 *
 */
Z3_ast get_internal_bool_var(Z3_theory t, unsigned int index){
	Z3_context ctx = Z3_theory_get_context(t);
	std::stringstream ss;
	ss << index;
	std::string name = "$$_bool" + ss.str();
	return mk_bool_var(ctx, name.c_str());
}



/*
 *
 */
Z3_ast mk_str_var(Z3_theory t, char const * name) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData *) Z3_theory_get_ext_data(t);
	Z3_ast varAst = mk_var(ctx, name, td->String);
	return varAst;
}


/*
 *
 */
Z3_ast mk_length(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);

	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	if (length_astNode_map.find(n) == length_astNode_map.end()) {
		if (isConstStr(t, n)) {
			length_astNode_map[n] = mk_int(ctx, getConstStrValue(t, n).length());
		} else {
			length_astNode_map[n] = mk_unary_app(ctx, td->Length, n);
		}
	}
	return length_astNode_map[n];
}

/*
 *
 */
Z3_ast mk_contains(Z3_theory t, Z3_ast n1, Z3_ast n2) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	std::pair<Z3_ast, Z3_ast> containsKey(n1, n2);
	if (containNodeMap.find(containsKey) == containNodeMap.end()) {
		if (isConstStr(t, n1) && isConstStr(t, n2)) {
			std::string n1Str = getConstStrValue(t, n1);
			std::string n2Str = getConstStrValue(t, n2);
			if (n1Str.find(n2Str) != std::string::npos)
				containNodeMap[containsKey] = Z3_mk_true(ctx);
			else
				containNodeMap[containsKey] = Z3_mk_false(ctx);
		} else {
			containNodeMap[containsKey] = mk_binary_app(ctx, td->Contains, n1, n2);
		}
	}
	return containNodeMap[containsKey];
}

/*
 *
 */
Z3_ast mk_concat(Z3_theory t, Z3_ast n1, Z3_ast n2, bool &updated) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	if (n1 == NULL || n2 == NULL) {
		fprintf(stdout, "> Error: the strings to be concat cannot be NULL (@ %d).\n", __LINE__);
		exit(0);
	} else {
		bool n1HasEqcValue = false;
		bool n2HasEqcValue = false;
		n1 = get_eqc_value(t, n1, n1HasEqcValue);
		n2 = get_eqc_value(t, n2, n2HasEqcValue);

		updated = updated || false;
		// update charSet
		if (isConstStr(t, n1)) {
			updated = true;
		}
		if (isConstStr(t, n2)) {
			updated = true;
		}

		if (n1HasEqcValue && n2HasEqcValue) { // two const strings
			return Concat(t, n1, n2);
		} else if (n1HasEqcValue && !n2HasEqcValue) {
			if (getConstStrValue(t, n1).size() == 0) {
				return n2;
			}
			if (isConcatFunc(t, n2)) {
				Z3_ast n2_arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n2), 0);
				Z3_ast n2_arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n2), 1);
				if (isConstStr(t, n2_arg0)) {
					n1 = Concat(t, n1, n2_arg0); // n1 will be a constant
					n2 = n2_arg1;
				}
			}
		} else if (!n1HasEqcValue && n2HasEqcValue) {
			if (getConstStrValue(t, n2).size() == 0) {
				return n1;
			}

			if (isConcatFunc(t, n1)) {
				Z3_ast n1_arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n1), 0);
				Z3_ast n1_arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n1), 1);
				if (isConstStr(t, n1_arg1)) {
					n1 = n1_arg0;
					n2 = Concat(t, n1_arg1, n2); // n2 will be a constant
				}
			}
		} else {
			if (isConcatFunc(t, n1) && isConcatFunc(t, n2)) {
				Z3_ast n1_arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n1), 0);
				Z3_ast n1_arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n1), 1);
				Z3_ast n2_arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n2), 0);
				Z3_ast n2_arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n2), 1);
				if (isConstStr(t, n1_arg1) && isConstStr(t, n2_arg0)) {
					Z3_ast tmpN1 = n1_arg0;
					Z3_ast tmpN2 = Concat(t, n1_arg1, n2_arg0);
					n1 = mk_concat(t, tmpN1, tmpN2, updated);
					n2 = n2_arg1;
				}
			}
		}

		//------------------------------------------------------
		// * Z3_ast ast1 = mk_2_arg_app(ctx, td->Concat, n1, n2);
		// * Z3_ast ast2 = mk_2_arg_app(ctx, td->Concat, n1, n2);
		// Z3 treats (ast1) and (ast2) as two different nodes.
		//-------------------------------------------------------
		std::vector<Z3_ast> and_list;

		// handle string const
		bool hasEqcValue = false;
		Z3_ast node00 = get_eqc_value(t, n1, hasEqcValue);
		if (hasEqcValue) {
			std::string str = getConstString(t, node00);
			if (str.size() >= 0) {
				// create automata def for const string
				if (str.find('*') != std::string::npos || str.find('+') != std::string::npos)
					n1 = mk_binary_app(ctx, td->NonDet_AutomataDef, mk_str_value(t, str.c_str()), mk_int(ctx, nondeterministicCounter++));
				else
					n1 = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, str.c_str()));

#ifdef ARITH
				and_list.emplace_back(Z3_mk_eq(ctx, getLengthAST(t, n1), mk_int(ctx, str.size())));
				// create Parikh for const string
				std::vector<Z3_ast> list;
#ifdef PARIKH1
				list = createParikhConstraints_string(t, n1, str);
#endif
				and_list.insert(and_list.end(), list.begin(), list.end());
#endif
			}
		}

		Z3_ast node02 = get_eqc_value(t, n2, hasEqcValue);
		if (hasEqcValue) {

			std::string str = getConstString(t, node02);
			if (str.size() >= 0) {
				//create automata def for const string
				if (str.find('*') != std::string::npos || str.find('+') != std::string::npos)
					n2 = mk_binary_app(ctx, td->NonDet_AutomataDef, mk_str_value(t, str.c_str()), mk_int(ctx, nondeterministicCounter++));
				else
					n2 = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, str.c_str()));

#ifdef ARITH
				and_list.emplace_back(Z3_mk_eq(ctx, getLengthAST(t, n2), mk_int(ctx, str.size())));
				// create Parikh for const string
				std::vector<Z3_ast> list;
#ifdef PARIKH1
				list = createParikhConstraints_string(t, n2, str);
#endif
				and_list.insert(and_list.end(), list.begin(), list.end());
#endif
			}
		}

		std::pair<Z3_ast, Z3_ast> concatArgs(n1, n2);

		Z3_ast concatAst = NULL;

		// handle length constraints
		if (concat_astNode_map.find(concatArgs) == concat_astNode_map.end()) {
			concatAst = mk_binary_app(ctx, td->Concat, n1, n2);
			concat_astNode_map[concatArgs] = concatAst;

			//      getNodesInConcat(t, concatAst, childrenVector);
#ifdef ARITH
			std::vector<Z3_ast> basicN1 = basicArithConstraints_forNode_simple(t, n1);
			std::vector<Z3_ast> basicN2 = basicArithConstraints_forNode_simple(t, n2);
			std::vector<Z3_ast> basicTotal = basicArithConstraints_forNode_simple(t, mk_binary_app(ctx, td->Concat, n1, n2));
			std::vector<Z3_ast> basicConcat = basicArithConstraints_forConcat(t, n1, n2);

			and_list.insert(and_list.end(), basicN1.begin(), basicN1.end());
			and_list.insert(and_list.end(), basicN2.begin(), basicN2.end());
			and_list.insert(and_list.end(), basicTotal.begin(), basicTotal.end());
			and_list.insert(and_list.end(), basicConcat.begin(), basicConcat.end());
#endif
		} else {
			concatAst = concat_astNode_map[concatArgs];
		}

		// add basic length and parikh constraints

		if (and_list.size() > 0) {
			addAxiom(t, mk_and_fromVector(t, and_list), __LINE__, true);
			updated = true;
		}
		return concatAst;
	}
}

/*
 *
 */
//Z3_ast mk_add_fromVector(Z3_theory t, std::vector<Z3_ast> & vec) {
//  Z3_context ctx = Z3_theory_get_context(t);
//  if (vec.size() == 0) {
//    return mk_int(ctx, 0);
//  } else if (vec.size() == 1) {
//    return vec[0];
//  } else {
//    Z3_ast * items = new Z3_ast[vec.size()];
//    for (unsigned int i = 0; i < vec.size(); i++)
//      items[i] = vec[i];
//    Z3_ast toAssert = Z3_mk_add(ctx, vec.size(), items);
//    delete[] items;
//    return toAssert;
//  }
//}

/****************************************
 *  Z3 input parser doesn't understand constant string
 *  So, we pass const string by adding a special mark "$",
 * --------------------------------------
 * "__cOnStStR__x23_x5c_x6e_x5c_x22_x53"
 ****************************************/
inline bool isValidHexDigit(char c) {
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) {
		return true;
	}
	return false;
}

/*
 *
 */
inline int hexDigitToInt(char a) {
	if ('0' <= a && a <= '9')
		return a - '0';
	else if ('a' <= a && a <= 'f')
		return 10 + a - 'a';
	else if ('A' <= a && a <= 'F')
		return 10 + a - 'A';
	else
		return 0;
}

/*
 *
 */
inline int twoHexDigitToChar(char a, char b) {
	return (hexDigitToInt(a) * 16 + hexDigitToInt(b));
}

/*
 *
 */
std::string convertInputTrickyConstStr(std::string inputStr) {
	std::string outputStr = "";
	std::string innerStr = inputStr.substr(11, inputStr.length() - 11);
	int innerStrLen = innerStr.length();
	if (innerStrLen % 4 != 0) {
		fprintf(stdout, "> Error: Constant string conversion error. Exit.\n");
		fprintf(stdout, "         Input encoding: %s\n", inputStr.c_str());
		fflush(stdout);
		exit(0);
	}
	for (int i = 0; i < (innerStrLen / 4); i++) {
		std::string cc = innerStr.substr(i * 4, 4);
		if (cc[0] == '_' && cc[1] == 'x' && isValidHexDigit(cc[2]) && isValidHexDigit(cc[3])) {
			char dc = twoHexDigitToChar(cc[2], cc[3]);
			//      fprintf(stdout, "> Error: Character in a constant string is not in the system alphabet. %s\n", cc.c_str());
			//      fprintf(stdout, "         Please set the character set accordingly.\n");
			//      fflush(stdout);
			//      exit(0);
			// Check whether the input character in the charSet
			//      if (charSetLookupTable.find(dc) == charSetLookupTable.end()) {
			//        fprintf(stdout, "> Error: Character '%s' in a constant string is not in the system alphabet.\n", encodeToEscape(dc).c_str());
			//        fprintf(stdout, "         Please set the character set accordingly.\n");
			//        fflush(stdout);
			//        exit(0);
			//      }
			outputStr = outputStr + std::string(1, dc);
		}
	}
	return outputStr;
}

/*
  * return str if it is const or automatadet
  */
std::string getConstString(Z3_theory t, Z3_ast node){
	Z3_context ctx = Z3_theory_get_context(t);

	if (isConstStr(t, node)) {
		std::string tmp = getConstStrValue(t, node);
		std::string s = "";
		for (unsigned i = 0 ; i < tmp.size(); ++i) {
			s+= tmp[i];
			if (tmp[i] == '\\' && i != tmp.size() - 1 && tmp[i + 1] == '\\' && languageVersion == 20)
				++i;
		}
		return s;
	}
	else {
		std::string tmp = Z3_ast_to_string(ctx, Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0));
		std::string s = "";
		for (unsigned i = 0 ; i < tmp.size(); ++i) {
			s+= tmp[i];
			if (tmp[i] == '\\' && i != tmp.size() - 1 && tmp[i + 1] == '\\' && languageVersion == 20)
				++i;
		}
		return customizeString(s);
	}
	return NULL;
}

/*
 *
 */
Z3_ast convertToAutomtaNodeIfPossible(Z3_theory t, Z3_ast node){
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	if (isConstStr(t, node)) {
		std::string s = getConstString(t, node);
		__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, s.c_str());
		return mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, s.c_str()));
	}
	else
		return node;
}

/*
 * startswith A, "abc" --> contains A, "c"
 */
void addStartsWithRelation(Z3_theory t, Z3_ast str, Z3_ast subStr, Z3_ast boolNode){
	Z3_context ctx = Z3_theory_get_context(t);

#ifdef DEBUGLOG
	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, str);
	__debugPrint(logFile, " ");
	printZ3Node(t, subStr);
	__debugPrint(logFile, "\n");
#endif

	string ss = "";
	if (isDetAutomatonFunc(t, subStr) || isConstStr(t, subStr)) {
		if (isDetAutomatonFunc(t, subStr))
			ss = Z3_ast_to_string(ctx,  Z3_get_app_arg(ctx, Z3_to_app(ctx, subStr), 0));
		else
			ss = getConstStrValue(t, subStr);

		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = startsWithPairBoolMap.begin(); it != startsWithPairBoolMap.end(); ++it) {
			if (isDetAutomatonFunc(t, it->first.second) && it->first.first == str && it->second != boolNode) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->first.second), 0);
				std::string s = Z3_ast_to_string(ctx, arg00);

				__debugPrint(logFile, "%d checking startswith %s vs %s\n", __LINE__, ss.c_str(), s.c_str());

				/* startswith a "123" == bool00 && startswith a "1"  == bool01 --> bool00 => bool01 */
				std::size_t pos00 = ss.find(s);
				if (pos00 == 0)
					addAxiom(t, Z3_mk_implies(ctx, boolNode, it->second), __LINE__, true);
				std::size_t pos01 = s.find(ss);
				if (pos01 == 0)
					addAxiom(t, Z3_mk_implies(ctx, it->second, boolNode), __LINE__, true);

				/* startswith a "123" == bool00 && startswith a "456"  == bool01 --> not (bool00 && bool01) */
				if (pos00 != 0 && pos01 != 0){
					std::vector<Z3_ast> andComponents;
					andComponents.emplace_back(it->second);
					andComponents.emplace_back(boolNode);
					addAxiom(t, Z3_mk_not(ctx, mk_and_fromVector(t, andComponents)), __LINE__, true);
				}
			}
		}
	}

	if (isConstStr(t, str) || isDetAutomatonFunc(t, str)) {
		if (isDetAutomatonFunc(t, str))
			ss = Z3_ast_to_string(ctx,  Z3_get_app_arg(ctx, Z3_to_app(ctx, str), 0));
		else
			ss = getConstStrValue(t, str);

		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = startsWithPairBoolMap.begin(); it != startsWithPairBoolMap.end(); ++it) {
			if (isDetAutomatonFunc(t, it->first.first) && it->first.second == subStr && it->second != boolNode) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->first.first), 0);
				std::string s = Z3_ast_to_string(ctx, arg00);

				/* startswith "12345" a == bool00 && startswith "123" a  == bool01 --> bool00 => bool01 */
				std::size_t pos00 = ss.find(s);
				if (pos00 == 0)
					addAxiom(t, Z3_mk_implies(ctx, it->second, boolNode),__LINE__, true);

				std::size_t pos01 = s.find(ss);
				if (pos01 == 0)
					addAxiom(t, Z3_mk_implies(ctx, boolNode, it->second),__LINE__, true);

				/* startswith "12345" a == bool00 && startswith "456" a  == bool01 --> (bool00 && bool01) => length a <= 0 */
				if (pos00 != 0 && pos01 != 0) {
					std::vector<Z3_ast> andComponents;
					andComponents.emplace_back(it->second);
					andComponents.emplace_back(boolNode);
					addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andComponents), Z3_mk_le(ctx, mk_length(t, subStr), mk_int(ctx, longestCommonHead(s, ss).length()))), __LINE__, true);
				}
			}
		}
	}
}

/*
 *
 */
Z3_ast registerStartsWith(Z3_theory t, Z3_ast str, Z3_ast subStr){
	Z3_ast tmpStr = convertToAutomtaNodeIfPossible(t, str);
	Z3_ast tmpSubStr = convertToAutomtaNodeIfPossible(t, subStr);

#ifdef DEBUGLOG
	__debugPrint(logFile, "*** %s ***: StartsWith(", __FUNCTION__);
	printZ3Node(t, tmpStr);
	__debugPrint(logFile, ", ");
	printZ3Node(t, tmpSubStr);
#endif

	std::pair<Z3_ast, Z3_ast> key = std::make_pair(tmpStr, tmpSubStr);
	if (startsWithPairBoolMap.find(key) == startsWithPairBoolMap.end()) {
		startsWithPairBoolMap[key] = mk_internal_bool_var(t);
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, ") = ");
	printZ3Node(t, startsWithPairBoolMap[key]);
	__debugPrint(logFile, "\n");
#endif

	addStartsWithRelation(t, str, subStr, startsWithPairBoolMap[key]);
	constraintSet.otherConstraints.emplace(createEqualConstraint(node_to_string(t, startsWithPairBoolMap[key]),
																	createStartsWithConstraint(node_to_string(t, tmpStr), node_to_string(t, tmpSubStr))));
	return startsWithPairBoolMap[key];
}

/*
 * endswith A, "abc" --> contains A, "c"
 */
void addEndsWithRelation(Z3_theory t, Z3_ast str, Z3_ast subStr, Z3_ast boolNode){

	Z3_context ctx = Z3_theory_get_context(t);

#ifdef DEBUGLOG
	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, str);
	__debugPrint(logFile, " ");
	printZ3Node(t, subStr);
	__debugPrint(logFile, "\n");
#endif

	string ss = "";
	if (isDetAutomatonFunc(t, subStr) || isConstStr(t, subStr)) {
		if (isDetAutomatonFunc(t, subStr))
			ss = Z3_ast_to_string(ctx,  Z3_get_app_arg(ctx, Z3_to_app(ctx, subStr), 0));
		else
			ss = getConstStrValue(t, subStr);

		__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, ss.c_str());
		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = endsWithPairBoolMap.begin(); it != endsWithPairBoolMap.end(); ++it) {
			if (isDetAutomatonFunc(t, it->first.second) && it->first.first == str && it->second != boolNode) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->first.second), 0);
				std::string s = Z3_ast_to_string(ctx, arg00);

				__debugPrint(logFile, "%d checking endswith %s vs %s\n", __LINE__, ss.c_str(), s.c_str());
				/* endswith a "123" == bool00 && endswith a "1"  == bool01 --> bool00 => bool01 */
				std::size_t pos00 = ss.find(s);
				if (pos00 != std::string::npos && pos00 + s.length() == ss.length())
					addAxiom(t, Z3_mk_implies(ctx, boolNode, it->second), __LINE__, true);
				std::size_t pos01 = s.find(ss);
				if (pos01 != std::string::npos && pos01 + ss.length() == s.length())
					addAxiom(t, Z3_mk_implies(ctx, it->second, boolNode), __LINE__, true);

				/* endswith a "123" == bool00 && endswith a "456"  == bool01 --> not(bool00 && bool01) */
				if (!(pos00 != std::string::npos && pos00 + s.length() == ss.length()) &&
						!(pos01 != std::string::npos && pos01 + ss.length() == s.length())) {
					std::vector<Z3_ast> andComponents;
					andComponents.emplace_back(it->second);
					andComponents.emplace_back(boolNode);
					addAxiom(t, Z3_mk_not(ctx, mk_and_fromVector(t, andComponents)), __LINE__, true);
				}
			}
		}
	}

	if (isConstStr(t, str) || isDetAutomatonFunc(t, str)) {
		if (isDetAutomatonFunc(t, str))
			ss = Z3_ast_to_string(ctx,  Z3_get_app_arg(ctx, Z3_to_app(ctx, str), 0));
		else
			ss = getConstStrValue(t, str);

		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = endsWithPairBoolMap.begin(); it != endsWithPairBoolMap.end(); ++it) {
			if (isDetAutomatonFunc(t, it->first.first) && it->first.second == subStr && it->second != boolNode) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->first.first), 0);
				std::string s = Z3_ast_to_string(ctx, arg00);

				/* endswith "123" a == bool00 && endswith "12345" a == bool01 --> bool00 => bool01 */
				std::size_t pos00 = ss.find(s);
				if (pos00 != std::string::npos && pos00 + s.length() == ss.length())
					addAxiom(t, Z3_mk_implies(ctx, it->second, boolNode),__LINE__, true);
				std::size_t pos01 = s.find(ss);
				if (pos01 != std::string::npos && pos01 + ss.length() == s.length())
					addAxiom(t, Z3_mk_implies(ctx, boolNode, it->second),__LINE__, true);

				/* endswith "123" a == bool00 && endswith "456" a  == bool01 --> (bool00 && bool01) => len a <= 0 */
				if (!(pos00 != std::string::npos && pos00 + s.length() == ss.length()) &&
					!(pos01 != std::string::npos && pos01 + ss.length() == s.length())	) {
					std::vector<Z3_ast> andComponents;
					andComponents.emplace_back(it->second);
					andComponents.emplace_back(boolNode);
					addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andComponents), Z3_mk_le(ctx, mk_length(t, subStr), mk_int(ctx, longestCommonTail(ss, s).length()))), __LINE__, true);
				}
			}
		}
	}
}

/*
 *
 */
Z3_ast registerEndsWith(Z3_theory t, Z3_ast str, Z3_ast subStr) {

	Z3_ast tmpStr = convertToAutomtaNodeIfPossible(t, str);
	Z3_ast tmpSubStr = convertToAutomtaNodeIfPossible(t, subStr);

#ifdef DEBUGLOG
	__debugPrint(logFile, "*** %s ***: EndsWith(", __FUNCTION__);
	printZ3Node(t, tmpStr);
	__debugPrint(logFile, ", ");
	printZ3Node(t, tmpSubStr);
#endif

	std::pair<Z3_ast, Z3_ast> key = std::make_pair(tmpStr, tmpSubStr);
	if (endsWithPairBoolMap.find(key) == endsWithPairBoolMap.end()) {
		endsWithPairBoolMap[key] = mk_internal_bool_var(t);
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, ") = ");
	printZ3Node(t, endsWithPairBoolMap[key]);
	__debugPrint(logFile, "\n");
#endif

	addEndsWithRelation(t, str, subStr, endsWithPairBoolMap[key]);
	constraintSet.otherConstraints.emplace(createEqualConstraint(
																		node_to_string(t, endsWithPairBoolMap[key]),
																		createEndsWithConstraint(node_to_string(t, tmpStr), node_to_string(t, tmpSubStr))));
	return endsWithPairBoolMap[key];
}

/*
 * contains A, "abc" --> contains A, "a"
 */
void addContainRelation(Z3_theory t, Z3_ast str, Z3_ast subStr, Z3_ast boolNode){
	Z3_context ctx = Z3_theory_get_context(t);

#ifdef DEBUGLOG
	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, str);
	__debugPrint(logFile, " ");
	printZ3Node(t, subStr);
	__debugPrint(logFile, "\n");
#endif

	string ss = "";
	if (isDetAutomatonFunc(t, subStr) || isConstStr(t, subStr)) {
		if (isDetAutomatonFunc(t, subStr))
			ss = Z3_ast_to_string(ctx,  Z3_get_app_arg(ctx, Z3_to_app(ctx, subStr), 0));
		else
			ss = getConstStrValue(t, subStr);

		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = containPairBoolMap.begin(); it != containPairBoolMap.end(); ++it) {
			if (isDetAutomatonFunc(t, it->first.second) && it->first.first == str && it->second != boolNode) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->first.second), 0);
				std::string s = Z3_ast_to_string(ctx, arg00);

				__debugPrint(logFile, "%d * %s * %s vs %s\n", __LINE__, __FUNCTION__, ss.c_str(), s.c_str());
				if (ss.find(s) != std::string::npos)
					addAxiom(t, Z3_mk_implies(ctx, boolNode, it->second), __LINE__, true);
				else if (s.find(ss) != std::string::npos)
					addAxiom(t, Z3_mk_implies(ctx, it->second, boolNode), __LINE__, true);
			}
		}
	}

	if (isConstStr(t, str) || isDetAutomatonFunc(t, str)) {
		if (isDetAutomatonFunc(t, str))
			ss = Z3_ast_to_string(ctx,  Z3_get_app_arg(ctx, Z3_to_app(ctx, str), 0));
		else
			ss = getConstStrValue(t, str);

		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = containPairBoolMap.begin(); it != containPairBoolMap.end(); ++it) {
			if (isDetAutomatonFunc(t, it->first.first) && it->first.second == subStr && it->second != boolNode) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->first.first), 0);
				std::string s = Z3_ast_to_string(ctx, arg00);
				if (ss.find(s) != std::string::npos)
					addAxiom(t, Z3_mk_implies(ctx, it->second, boolNode),__LINE__, true);
				else if (s.find(ss) != std::string::npos)
					addAxiom(t, Z3_mk_implies(ctx, boolNode, it->second),__LINE__, true);
			}
		}
	}
}

/*
 *
 */
Z3_ast registerContain(Z3_theory t, Z3_ast str, Z3_ast subStr) {

	Z3_ast tmpStr = convertToAutomtaNodeIfPossible(t, str);
	Z3_ast tmpSubStr = convertToAutomtaNodeIfPossible(t, subStr);

#ifdef DEBUGLOG
	__debugPrint(logFile, "*** %s ***: Contains(", __FUNCTION__);
	printZ3Node(t, tmpStr);
	__debugPrint(logFile, ", ");
	printZ3Node(t, tmpSubStr);
#endif

	std::pair<Z3_ast, Z3_ast> key = std::make_pair(tmpStr, tmpSubStr);
	if (containPairBoolMap.find(key) == containPairBoolMap.end()) {
		containPairBoolMap[key] = mk_internal_bool_var(t);
		containPairIdxMap[str].insert(key);
		containPairIdxMap[subStr].insert(key);
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, ") = ");
	printZ3Node(t, containPairBoolMap[key]);
	__debugPrint(logFile, "\n");
#endif

	addContainRelation(t, str, subStr, containPairBoolMap[key]);
	if (printingConstraints)
		constraintSet.otherConstraints.emplace(createEqualConstraint(node_to_string(t, containPairBoolMap[key]), createContainConstraint(node_to_string(t, tmpStr), node_to_string(t, tmpSubStr))));
	return containPairBoolMap[key];
}

/*
 *
 */
Z3_ast registerInternalContain(Z3_theory t, Z3_ast str, Z3_ast subStr) {
	Z3_ast tmpStr;
	Z3_ast tmpSubStr;
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	if (isConstStr(t, subStr)) {
		std::string s = customizeString(getConstStrValue(t, subStr));
		tmpSubStr = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, s.c_str()));
	}
	else
		tmpSubStr = subStr;

	if (isConstStr(t, str)){
		std::string s = customizeString(getConstStrValue(t, str));
		tmpStr = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, s.c_str()));
	}
	else
		tmpStr = str;

#ifdef DEBUGLOG
	__debugPrint(logFile, ">> [containRegister]xxx Contains(");
	printZ3Node(t, tmpStr);
	__debugPrint(logFile, ", ");
	printZ3Node(t, tmpSubStr);
#endif

	std::pair<Z3_ast, Z3_ast> key = std::make_pair(tmpStr, tmpSubStr);
	if (containPairBoolMap.find(key) == containPairBoolMap.end()) {
		containPairBoolMap[key] = mk_internal_bool_var(t);
		addAxiom(t, Z3_mk_eq(ctx, containPairBoolMap[key], mk_contains(t, tmpStr, tmpSubStr)), __LINE__, true);
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, ") = ");
	printZ3Node(t, containPairBoolMap[key]);
	__debugPrint(logFile, "\n");
#endif

	addContainRelation(t, str, subStr, containPairBoolMap[key]);
	return containPairBoolMap[key];
}

/*
 * Handle concat when note is constant
 */
Z3_ast Concat(Z3_theory t, Z3_ast n1, Z3_ast n2) {
	bool n1HasEqcValue = false;
	bool n2HasEqcValue = false;
	Z3_ast v1 = get_eqc_value(t, n1, n1HasEqcValue);
	Z3_ast v2 = get_eqc_value(t, n2, n2HasEqcValue);
	if (n1HasEqcValue && n2HasEqcValue) {
		std::string n1_str = getConstStrValue(t, v1);
		std::string n2_str = getConstStrValue(t, v2);
		std::string result = n1_str + n2_str;
		return mk_str_value(t, result.c_str());
	} else if (n1HasEqcValue && !n2HasEqcValue) {
		if (getConstStrValue(t, v1) == "") {
			return n2;
		}
	} else if (!n1HasEqcValue && n2HasEqcValue) {
		if (getConstStrValue(t, v2) == "") {
			return n1;
		}
	}
	return NULL;
}

/*
 * only collect leaf, z3_Ast format
 */
void getNodesInConcat(Z3_theory t, Z3_ast node, std::vector<Z3_ast> & nodeList) {
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_context ctx = Z3_theory_get_context(t);
	if (getNodeType(t, node) != my_Z3_Func || (getNodeType(t, node) == my_Z3_Func && Z3_get_app_decl(ctx, Z3_to_app(ctx, node)) != td->Concat)) {
		nodeList.emplace_back(node);
		return;
	} else {
		Z3_ast leftArg = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0);
		Z3_ast rightArg = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 1);
		getNodesInConcat(t, leftArg, nodeList);
		getNodesInConcat(t, rightArg, nodeList);
	}
}

/*
 * only collect leaf, string format
 */
StringOP node_to_stringOP(Z3_theory t, Z3_ast node) {
	Z3_context ctx = Z3_theory_get_context(t);
	if (isAutomatonFunc(t, node)) {
		return StringOP("\"" + getConstString(t, node) + "\"");
	}
	else if (isConstStr(t, node)){
		std::string tmp = Z3_ast_to_string(ctx, node);
		if (tmp.length() > 0 && tmp[0] == '|' && tmp[tmp.length() - 1] == '|' ) {
			tmp = tmp.substr(1, tmp.length() - 2);
		}
		return StringOP("\"" + tmp + "\"");
	}
	else if (isVariable(t, node))
		return StringOP(Z3_ast_to_string(ctx, node));
	else {
//		__debugPrint(logFile, "%d node: %s\n", __LINE__, Z3_ast_to_string(ctx, node));
		Z3_ast funcType = Z3_func_decl_to_ast(ctx, Z3_get_app_decl(ctx, Z3_to_app(ctx, node)));
		std::string typeStr = Z3_ast_to_string(ctx, funcType);
		int args = Z3_get_app_num_args(ctx, Z3_to_app(ctx, node));
		std::vector<StringOP> elements;
		for (int i = 0; i < args; ++i) {
			Z3_ast n = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), i);
			elements.emplace_back(node_to_stringOP(t, n));
		}
		StringOP ret;
		ret.setArgs(elements);


		if (typeStr.find("declare-fun +") != std::string::npos){
			ret.setName("+");
			formatPlusOP(ret);
			return ret;
		}
		else if (typeStr.find("declare-fun -") != std::string::npos){
			ret.setName("-");
			formatMinusOP(ret);
			return ret;
		}
		else if (typeStr.find("declare-fun *") != std::string::npos){
			ret.setName("*");
			formatMultiplyOP(ret);
			return ret;
		}
		else if (typeStr.find("declare-fun =") != std::string::npos){
			ret.setName("=");
			return ret;
		}
		else if (typeStr.find("declare-fun >=") != std::string::npos){
			ret.setName(">=");
			return ret;
		}
		else if (typeStr.find("declare-fun <=") != std::string::npos){
			ret.setName("<=");
			return ret;
		}
		else if (typeStr.find("declare-fun >") != std::string::npos){
			ret.setName(">");
			return ret;
		}
		else if (typeStr.find("declare-fun <") != std::string::npos){
			ret.setName("<");
			return ret;
		}
		else if (typeStr.find("declare-fun ite") != std::string::npos){
			ret.setName("ite");
			return ret;
		}
		else if (typeStr.find("declare-fun and") != std::string::npos){
			ret.setName("and");
			return ret;
		}
		else if (typeStr.find("declare-fun or") != std::string::npos){
			ret.setName("or");
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[CONCAT]) != std::string::npos) {
			ret.setName(languageMap[CONCAT]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[INDEXOF2]) != std::string::npos) {
			ret.setName(languageMap[INDEXOF2]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[INDEXOF]) != std::string::npos) {
			ret.setName(languageMap[INDEXOF]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[CONTAINS]) != std::string::npos) {
			ret.setName(languageMap[CONTAINS]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[SUBSTRING]) != std::string::npos) {
			ret.setName(languageMap[SUBSTRING]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[LASTINDEXOF]) != std::string::npos) {
			ret.setName(languageMap[LASTINDEXOF]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[STARTSWITH]) != std::string::npos) {
			ret.setName(languageMap[STARTSWITH]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[ENDSWITH]) != std::string::npos) {
			ret.setName(languageMap[ENDSWITH]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[REPLACEALL]) != std::string::npos) {
			ret.setName(languageMap[REPLACEALL]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[REPLACE]) != std::string::npos) {
			ret.setName(languageMap[REPLACE]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[TOLOWER]) != std::string::npos) {
			ret.setName(languageMap[TOLOWER]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[TOUPPER]) != std::string::npos) {
			ret.setName(languageMap[TOUPPER]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[CHARAT]) != std::string::npos) {
			ret.setName(languageMap[CHARAT]);
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[LENGTH]) != std::string::npos) {
			ret.setName(languageMap[LENGTH]);
			return ret;
		}


		else {
			std::string tmp = Z3_ast_to_string(ctx, node);
			if (tmp.length() > 0 && tmp[0] == '|' && tmp[tmp.length() - 1] == '|' ) {
				tmp = tmp.substr(1, tmp.length() - 2);
				tmp = "\"" + tmp + "\"";
			}
			return StringOP(tmp);
		}
	}
}

/*
 * only collect leaf, string format
 */
std::string node_to_string(Z3_theory t, Z3_ast node) {
	Z3_context ctx = Z3_theory_get_context(t);
	if (isAutomatonFunc(t, node)) {
		return "\"" + getConstString(t, node) + "\"";
	}
	else if (isConstStr(t, node)){
		std::string tmp = Z3_ast_to_string(ctx, node);
		if (tmp.length() > 0 && tmp[0] == '|' && tmp[tmp.length() - 1] == '|' ) {
			tmp = tmp.substr(1, tmp.length() - 2);
		}
		tmp = "\"" + tmp + "\"";
		return tmp;
	}
	else if (isVariable(t, node))
		return Z3_ast_to_string(ctx, node);
	else {
//		__debugPrint(logFile, "%d node: %s\n", __LINE__, Z3_ast_to_string(ctx, node));
		Z3_ast funcType = Z3_func_decl_to_ast(ctx, Z3_get_app_decl(ctx, Z3_to_app(ctx, node)));
		std::string typeStr = Z3_ast_to_string(ctx, funcType);
		int args = Z3_get_app_num_args(ctx, Z3_to_app(ctx, node));
		std::vector<std::string> elements;
		for (int i = 0; i < args; ++i) {
			Z3_ast n = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), i);
			elements.emplace_back(node_to_string(t, n));
		}
		std::string ret = "";
		for (const auto& s : elements)
			ret = ret + " " + s;


		if (typeStr.find("declare-fun +") != std::string::npos){
			ret = "(+" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun *") != std::string::npos){
			ret = "(*" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun =") != std::string::npos){
			ret = "(=" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun >=") != std::string::npos){
			ret = "(>=" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun <=") != std::string::npos){
			ret = "(<=" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun >") != std::string::npos){
			ret = "(>" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun <") != std::string::npos){
			ret = "(<" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun ite") != std::string::npos){
			ret = "(ite" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun and") != std::string::npos){
			ret = "(and" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun or") != std::string::npos){
			ret = "(or" + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[CONCAT]) != std::string::npos) {
			ret = "(" + languageMap[CONCAT] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[INDEXOF2]) != std::string::npos) {
			ret = "(" + languageMap[INDEXOF2] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[INDEXOF]) != std::string::npos) {
			ret = "(" + languageMap[INDEXOF] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[CONTAINS]) != std::string::npos) {
			ret = "(" + languageMap[CONTAINS] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[SUBSTRING]) != std::string::npos) {
			ret = "(" + languageMap[SUBSTRING] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[LASTINDEXOF]) != std::string::npos) {
			ret = "(" + languageMap[LASTINDEXOF] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[STARTSWITH]) != std::string::npos) {
			ret = "(" + languageMap[STARTSWITH] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[ENDSWITH]) != std::string::npos) {
			ret = "(" + languageMap[ENDSWITH] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[REPLACEALL]) != std::string::npos) {
			ret = "(" + languageMap[REPLACEALL] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[REPLACE]) != std::string::npos) {
			ret = "(" + languageMap[REPLACE] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[TOLOWER]) != std::string::npos) {
			ret = "(" + languageMap[TOLOWER] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[TOUPPER]) != std::string::npos) {
			ret = "(" + languageMap[TOUPPER] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[CHARAT]) != std::string::npos) {
			ret = "(" + languageMap[CHARAT] + ret + ")";
			return ret;
		}
		else if (typeStr.find("declare-fun " + languageMap[LENGTH]) != std::string::npos) {
			ret = "(" + languageMap[LENGTH] + ret + ")";
			return ret;
		}


		else {
			std::string tmp = Z3_ast_to_string(ctx, node);
			if (tmp.length() > 0 && tmp[0] == '|' && tmp[tmp.length() - 1] == '|' ) {
				tmp = tmp.substr(1, tmp.length() - 2);
				tmp = "\"" + tmp + "\"";
			}
			return tmp;
		}
	}
}

/*
 * collect all nodes, including concat inside concat
 */
void getAllNodesInConcat(Z3_theory t, Z3_ast node, std::vector<Z3_ast> & nodeList) {
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_context ctx = Z3_theory_get_context(t);
	if (getNodeType(t, node) != my_Z3_Func || (getNodeType(t, node) == my_Z3_Func && Z3_get_app_decl(ctx, Z3_to_app(ctx, node)) != td->Concat)) {
		nodeList.emplace_back(node);
		return;
	} else {
		nodeList.emplace_back(node);
		Z3_ast leftArg = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0);
		Z3_ast rightArg = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 1);
		getAllNodesInConcat(t, leftArg, nodeList);
		getAllNodesInConcat(t, rightArg, nodeList);
	}
}

/*
 * collect subnodes of a node, and subnodes of nodes that are equal to it.
 */
void getNodesInConcat_extended(Z3_theory t, Z3_ast node, std::set<Z3_ast> & nodeList){
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> tmpEq = collect_eqc(t, node);
	for (const auto& n : tmpEq) {
		if (getNodeType(t, n) != my_Z3_Func ||
				(getNodeType(t, n) == my_Z3_Func && !isConcatFunc(t, n))) {
			nodeList.emplace(n);
			continue;
		} else {
			Z3_ast leftArg = Z3_get_app_arg(ctx, Z3_to_app(ctx, n), 0);
			Z3_ast rightArg = Z3_get_app_arg(ctx, Z3_to_app(ctx, n), 1);
			if (nodeList.find(leftArg) == nodeList.end())
				getNodesInConcat_extended(t, leftArg, nodeList);
			if (nodeList.find(rightArg) == nodeList.end())
				getNodesInConcat_extended(t, rightArg, nodeList);
		}
	}
}
/*
 * There are some exceptions when finding domain for a string variable
 *
 * Break the connection between arg0 and arg1
 * Break the connection between child and parent if parent doesnt have connections
 */
void reduceVariableDomain(Z3_theory t) {
#ifdef DEBUGLOG

	__debugPrint(logFile, "***********************************************\n");
	__debugPrint(logFile, "*               Reduce Domain Var             *\n");
	__debugPrint(logFile, "-----------------------------------------------\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);

	for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = concat_astNode_map.begin(); it != concat_astNode_map.end(); ++it) {

		std::set<Z3_ast> parents = collectAllParents(t, it->second);
		int cntParent = 0;
		for (std::set<Z3_ast>::iterator func = parents.begin(); func != parents.end(); ++func)
			if (!isLengthFunc(t, *func))
				++cntParent;

		//		printZ3Node(t, it->second);
		//		displayListNode(t, parents, " Parents:\n");

		// must have some concat
		if (cntParent > 0)
			continue;

		std::vector<Z3_ast> eq_toNode = collect_eqc(t, it->second);
		bool hasConnection = true;
		for (unsigned int i = 0; i < eq_toNode.size(); ++i) {
			if ((isConcatFunc(t, eq_toNode[i]) && eq_toNode[i] != it->second) || isAutomatonFunc(t, eq_toNode[i])) {
				hasConnection = false;
				break;
			}
		}

		// this concat is not equal to other concats and automaton
		if (hasConnection == true) {

			Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->second), 0);
			Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, it->second), 1);
			std::vector<Z3_ast> eq_toArg0 = collect_eqc(t, arg0);
			std::vector<Z3_ast> eq_toArg1 = collect_eqc(t, arg1);

			// remove edge between children
			std::string arg0_name = Z3_ast_to_string(ctx, arg0);
			std::string arg1_name = Z3_ast_to_string(ctx, arg1);

			std::vector<int>::iterator pos_arg1 = std::find(graph[variables[arg0_name]].begin(), graph[variables[arg0_name]].end(), variables[arg1_name]);
			std::vector<int>::iterator pos_arg0 = std::find(graph[variables[arg1_name]].begin(), graph[variables[arg1_name]].end(), variables[arg0_name]);
			if (pos_arg1 != graph[variables[arg0_name]].end())
				graph[variables[arg0_name]].erase(pos_arg1);
			if (pos_arg0 != graph[variables[arg1_name]].end())
				graph[variables[arg1_name]].erase(pos_arg0);

			bool arg0Defined = false;
			bool arg1Defined = false;

			for (unsigned int i = 0 ; i < eq_toArg0.size(); ++i)
				if (isAutomatonFunc(t, eq_toArg0[i]))
					arg0Defined = true;

			for (unsigned int i = 0 ; i < eq_toArg1.size(); ++i)
				if (isAutomatonFunc(t, eq_toArg1[i]))
					arg1Defined = true;

			__debugPrint(logFile, "%d Exceptional Concat: %d %d", __LINE__, arg0Defined, arg1Defined);
			printZ3Node(t, it->second);
			__debugPrint(logFile, "\n");

			if (isAutomatonFunc(t, arg0) || isAutomatonFunc(t, arg1))
				continue;

			if (arg0Defined == true && arg1Defined == false) {
				std::string tmpChild = Z3_ast_to_string(ctx, arg1);
				//    		__debugPrint(logFile, "%s - %d, %d ", tmpChild.c_str(), variables[tmpChild], variables[Z3_ast_to_string(ctx, arg0)]);
				//    		displayListNumber(graph[variables[tmpChild]]);
				//    		displayListNumber(graph[variables[Z3_ast_to_string(ctx, arg0)]]);

				for (unsigned int i = 0; i < eq_toNode.size(); ++i) {
					if (isStrVariable(t, eq_toNode[i])) {
						std::string tmpName = Z3_ast_to_string(ctx, eq_toNode[i]);
						//    				__debugPrint(logFile, "%s - %d ", tmpName.c_str(), variables[tmpName]);
						//    				displayListNumber(graph[variables[tmpName]]);
						std::vector<int>::iterator pos01 = std::find( graph[variables[tmpChild]].begin(),  graph[variables[tmpChild]].end(), variables[tmpName]);
						if (pos01 != graph[variables[tmpChild]].end())
							graph[variables[tmpChild]].erase(pos01);
						else
							__debugPrint(logFile, "%d something goes wrong\n", __LINE__);

						std::vector<int>::iterator pos02 = std::find(graph[variables[tmpName]].begin(), graph[variables[tmpName]].end(), variables[tmpChild]);
						if (pos02 != graph[variables[tmpName]].end())
							graph[variables[tmpName]].erase(pos02);
						else
							__debugPrint(logFile, "%d something goes wrong\n", __LINE__);
					}
				}



			}
			else if (arg0Defined == false && arg1Defined == true) {
				std::string tmpChild = Z3_ast_to_string(ctx, arg0);
				//    		__debugPrint(logFile, "%s - %d, %d ", tmpChild.c_str(), variables[tmpChild], variables[Z3_ast_to_string(ctx, arg0)]);
				//    		displayListNumber(graph[variables[tmpChild]]);
				//    		displayListNumber(graph[variables[Z3_ast_to_string(ctx, arg0)]]);

				for (unsigned int i = 0; i < eq_toNode.size(); ++i) {
					if (isStrVariable(t, eq_toNode[i])) {
						std::string tmpName = Z3_ast_to_string(ctx, eq_toNode[i]);
						//    				__debugPrint(logFile, "%s - %d ", tmpName.c_str(), variables[tmpName]);
						//    				displayListNumber(graph[variables[tmpName]]);
						std::vector<int>::iterator pos01 = std::find( graph[variables[tmpChild]].begin(),  graph[variables[tmpChild]].end(), variables[tmpName]);
						if (pos01 != graph[variables[tmpChild]].end())
							graph[variables[tmpChild]].erase(pos01);
						else
							__debugPrint(logFile, "%d something goes wrong\n", __LINE__);

						std::vector<int>::iterator pos02 = std::find(graph[variables[tmpName]].begin(), graph[variables[tmpName]].end(), variables[tmpChild]);
						if (pos02 != graph[variables[tmpName]].end())
							graph[variables[tmpName]].erase(pos02);
						else
							__debugPrint(logFile, "%d something goes wrong\n", __LINE__);
					}
				}
			}

		}
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, "*               Finish Reducing Domain Var             *\n");
	__debugPrint(logFile, "-----------------------------------------------\n");
#endif
}

/*
 *
 */
void findVariableDomain(){
	bool* visited = new bool[10000];
	int cnt = 0;
#ifdef DEBUGLOG
	__debugPrint(logFile, "***********************************************\n");
	__debugPrint(logFile, "*              findVariableDomain             *\n");
	__debugPrint(logFile, "-----------------------------------------------\n");
#endif
	for (int i = 0; i < 10000; ++i)
		visited[i] = false;

	std::map<std::string, std::set<char>> ret;

	for(unsigned int start = 0; start < graph.size(); ++start) {
		if (visited[start] == false) {
			std::vector<int> queue;

			visited[start] = true;
			queue.emplace_back(start);
			unsigned int pos = 0;
			while (pos < queue.size()) {
				int value = queue[pos];
				if (value < (int)graph.size())
					for (unsigned int i = 0; i < graph[value].size(); ++i) {
						if (visited[graph[value][i]] == false) {
							visited[graph[value][i]] = true;
							queue.emplace_back(graph[value][i]);
						}
					}
				pos++;
			}

			// collect string and variables
			std::vector<std::string> constStrs;
			std::vector<std::string> vars;
			classifyStrings_Variables(queue, constStrs, vars, variables);

			// collect all characters
			std::set<char> componentChars = collectChars(constStrs);

			// pair variables with charSet
			for (unsigned i = 0; i < vars.size(); ++i)
				ret[vars[i]] = componentChars;

#ifdef DEBUGLOG
			__debugPrint(logFile, "%d New Component: ", __LINE__);
			for (std::set<char>::iterator it = componentChars.begin(); it != componentChars.end(); ++it)
				__debugPrint(logFile, "%c ", *it);
			__debugPrint(logFile, "\n");
			for (unsigned int i = 0; i < vars.size(); ++i)
				__debugPrint(logFile, "%s ", vars[i].c_str());
			__debugPrint(logFile, "\n");
#endif
			cnt ++;
		}
	}

	__debugPrint(logFile, "Number of connected components: %d\n", cnt);

	__debugPrint(logFile, "%d charset size: %ld\n", __LINE__, charSet.size());
	charSet = ret;
	__debugPrint(logFile, "%d ret size: %ld\n", __LINE__, ret.size());
	__debugPrint(logFile, "%d charset size: %ld\n", __LINE__, charSet.size());
}

/*
 *
 */
std::set<char> collectChars(std::vector<std::string> constStrs) {
	std::set<char> componentChars;
	int state = 0; // 1: normal, 2: "\\"
	for (unsigned int i = 0; i < constStrs.size(); ++i) {
		for (unsigned int j = 1 ; j < constStrs[i].length() - 1; ++j)
			if (state == 2){
				componentChars.insert(constStrs[i][j]);
				state = 1;
			}
			else if (constStrs[i][j] == escapeChar && state == 1)  {
				state = 2;
			}
			else {
				componentChars.insert(constStrs[i][j]);
			}
	}
	return componentChars;
}

/*
 *
 */
void classifyStrings_Variables(std::vector<int> queue, std::vector<std::string> &constStrs, std::vector<std::string> &vars, std::map<std::string, int> variables){
	for (unsigned int i = 0; i < queue.size(); ++i) {
		for (std::map<std::string, int>::iterator it = variables.begin(); it != variables.end(); ++it) {
			if (it->second == queue[i] && it->first[0] != '"') {
				vars.emplace_back(it->first);
				break;
			}
			else if (it->second == queue[i] && it->first[0] == '"') {
				constStrs.emplace_back(it->first);
				break;
			}
		}
	}
}

/**
   \brief Simple theory example.
   The theory has a binary function f, and a unit element u.

   The theory axioms are:
   - <tt>forall X. f(X, u) = X</tt>
   - <tt>forall X. f(u, X) = X</tt>
 */
Z3_theory mk_theory(Z3_context ctx) {
	AutomatonStringData * td = (AutomatonStringData*)malloc(sizeof(AutomatonStringData));
	Z3_theory Th = Z3_mk_theory(ctx, "Automata String", td);
	Z3_sort BoolSort = Z3_mk_bool_sort(ctx);
	Z3_sort IntSort = Z3_mk_int_sort(ctx);
	Z3_symbol string_name = Z3_mk_string_symbol(ctx, "String");
	td->String = Z3_theory_mk_sort(ctx, Th, string_name);

	Z3_symbol regexSort_name = Z3_mk_string_symbol(ctx, "Regex");
	td->Regex = Z3_theory_mk_sort(ctx, Th, regexSort_name);

	Z3_symbol grammarSort_name = Z3_mk_string_symbol(ctx, "Grammar");
	td->Grammar = Z3_theory_mk_sort(ctx, Th, grammarSort_name);

	Z3_symbol concat_name = Z3_mk_string_symbol(ctx, languageMap[CONCAT].c_str());
	Z3_sort concat_domain[2];
	concat_domain[0] = td->String;
	concat_domain[1] = td->String;
	td->Concat = Z3_theory_mk_func_decl(ctx, Th, concat_name, 2, concat_domain, td->String);
	//---------------------------
	Z3_symbol length_name = Z3_mk_string_symbol(ctx, languageMap[LENGTH].c_str());
	Z3_sort length_domain[1];
	length_domain[0] = td->String;
	td->Length = Z3_theory_mk_func_decl(ctx, Th, length_name, 1, length_domain, IntSort);
	//---------------------------
	Z3_symbol substring_name = Z3_mk_string_symbol(ctx, languageMap[SUBSTRING].c_str());
	Z3_sort substring_domain[3];
	substring_domain[0] = td->String;
	substring_domain[1] = IntSort;
	substring_domain[2] = IntSort;
	td->SubString = Z3_theory_mk_func_decl(ctx, Th, substring_name, 3, substring_domain, td->String);
	//---------------------------
	Z3_symbol indexof_name = Z3_mk_string_symbol(ctx, languageMap[INDEXOF].c_str());
	Z3_sort indexof_domain[2];
	indexof_domain[0] = td->String;
	indexof_domain[1] = td->String;
	td->Indexof = Z3_theory_mk_func_decl(ctx, Th, indexof_name, 2, indexof_domain, IntSort);
	//---------------------------
	Z3_symbol indexof2_name = Z3_mk_string_symbol(ctx, languageMap[INDEXOF2].c_str());
	Z3_sort indexof2_domain[3];
	indexof2_domain[0] = td->String;
	indexof2_domain[1] = td->String;
	indexof2_domain[2] = IntSort;
	td->Indexof2 = Z3_theory_mk_func_decl(ctx, Th, indexof2_name, 3, indexof2_domain, IntSort);
	//---------------------------
	Z3_symbol contains_name = Z3_mk_string_symbol(ctx, languageMap[CONTAINS].c_str());
	Z3_sort contains_domain[2];
	contains_domain[0] = td->String;
	contains_domain[1] = td->String;
	td->Contains = Z3_theory_mk_func_decl(ctx, Th, contains_name, 2, contains_domain, BoolSort);
	//---------------------------
	Z3_symbol startsWith_name = Z3_mk_string_symbol(ctx, languageMap[STARTSWITH].c_str());
	Z3_sort startsWith_domain[2];
	startsWith_domain[0] = td->String;
	startsWith_domain[1] = td->String;
	td->StartsWith = Z3_theory_mk_func_decl(ctx, Th, startsWith_name, 2, startsWith_domain, BoolSort);
	//---------------------------
	Z3_symbol endsWith_name = Z3_mk_string_symbol(ctx, languageMap[ENDSWITH].c_str());
	Z3_sort endsWith_domain[2];
	endsWith_domain[0] = td->String;
	endsWith_domain[1] = td->String;
	td->EndsWith = Z3_theory_mk_func_decl(ctx, Th, endsWith_name, 2, endsWith_domain, BoolSort);
	//---------------------------
	Z3_symbol replace_name = Z3_mk_string_symbol(ctx, languageMap[REPLACE].c_str());
	Z3_sort replace_domain[3];
	replace_domain[0] = td->String;
	replace_domain[1] = td->String;
	replace_domain[2] = td->String;
	td->Replace = Z3_theory_mk_func_decl(ctx, Th, replace_name, 3, replace_domain, td->String);
	//---------------------------
	Z3_symbol replaceAll_name = Z3_mk_string_symbol(ctx, languageMap[REPLACEALL].c_str());
	Z3_sort replaceAll_domain[3];
	replaceAll_domain[0] = td->String;
	replaceAll_domain[1] = td->String;
	replaceAll_domain[2] = td->String;
	td->ReplaceAll = Z3_theory_mk_func_decl(ctx, Th, replaceAll_name, 3, replaceAll_domain, td->String);

	//---------------------------
	Z3_symbol lastIndexof_name = Z3_mk_string_symbol(ctx, languageMap[LASTINDEXOF].c_str());
	Z3_sort lastIndexof_domain[2];
	lastIndexof_domain[0] = td->String;
	lastIndexof_domain[1] = td->String;
	td->LastIndexof = Z3_theory_mk_func_decl(ctx, Th, lastIndexof_name, 2, lastIndexof_domain, IntSort);
	//---------------------------
	Z3_symbol charAt_name = Z3_mk_string_symbol(ctx, languageMap[CHARAT].c_str());
	Z3_sort charAt_domain[2];
	charAt_domain[0] = td->String;
	charAt_domain[1] = IntSort;
	td->CharAt = Z3_theory_mk_func_decl(ctx, Th, charAt_name, 2, charAt_domain, td->String);

	//---------------------------
	Z3_symbol toUpper_name = Z3_mk_string_symbol(ctx, languageMap[TOUPPER].c_str());
	Z3_sort toUpper_domain[1];
	toUpper_domain[0] = td->String;
	td->ToUpper = Z3_theory_mk_func_decl(ctx, Th, toUpper_name, 1, toUpper_domain, td->String);

	//---------------------------
	Z3_symbol toLower_name = Z3_mk_string_symbol(ctx, languageMap[TOLOWER].c_str());
	Z3_sort toLower_domain[1];
	toLower_domain[0] = td->String;
	td->ToLower = Z3_theory_mk_func_decl(ctx, Th, toLower_name, 1, toLower_domain, td->String);

	//===========================
	// Str2Reg := String --> Regex
	Z3_symbol str2Reg_name = Z3_mk_string_symbol(ctx, languageMap[STR2REG].c_str());
	Z3_sort str2Reg_domain[1];
	str2Reg_domain[0] = td->String;
	td->Str2Reg = Z3_theory_mk_func_decl(ctx, Th, str2Reg_name, 1, str2Reg_domain, td->Regex);
	//---------------------------
	// RegexStar := Regex --> Regex
	Z3_symbol regexStar_name = Z3_mk_string_symbol(ctx, languageMap[REGEXSTAR].c_str());
	Z3_sort regexStar_domain[1];
	regexStar_domain[0] = td->Regex;
	td->RegexStar = Z3_theory_mk_func_decl(ctx, Th, regexStar_name, 1, regexStar_domain, td->Regex);
	//---------------------------
	// RegexIn := String x Regex --> Bool
	Z3_symbol regexIn_name = Z3_mk_string_symbol(ctx, languageMap[REGEXIN].c_str());
	Z3_sort regexIn_domain[2];
	regexIn_domain[0] = td->String;
	regexIn_domain[1] = td->Regex;
	td->RegexIn = Z3_theory_mk_func_decl(ctx, Th, regexIn_name, 2, regexIn_domain, BoolSort);
	//---------------------------
	// RegexUnion := Regex x Regex --> Regex
	Z3_symbol regexUnion_name = Z3_mk_string_symbol(ctx, languageMap[REGEXUNION].c_str());
	Z3_sort regexUnion_domain[2];
	regexUnion_domain[0] = td->Regex;
	regexUnion_domain[1] = td->Regex;
	td->RegexUnion = Z3_theory_mk_func_decl(ctx, Th, regexUnion_name, 2, regexUnion_domain, td->Regex);
	//---------------------------
	// RegexConcat := Regex x Regex --> Regex
	Z3_symbol regexConcat_name = Z3_mk_string_symbol(ctx, languageMap[REGEXCONCAT].c_str());
	Z3_sort regexConcat_domain[2];
	regexConcat_domain[0] = td->Regex;
	regexConcat_domain[1] = td->Regex;
	td->RegexConcat = Z3_theory_mk_func_decl(ctx, Th, regexConcat_name, 2, regexConcat_domain, td->Regex);
	//---------------------------
	// Unroll := String x Int --> String
	Z3_symbol unrollFunc_name = Z3_mk_string_symbol(ctx, "Unroll");
	Z3_sort unrollFunc_domain[2];
	unrollFunc_domain[0] = td->Regex;
	unrollFunc_domain[1] = IntSort;
	td->Unroll = Z3_theory_mk_func_decl(ctx, Th, unrollFunc_name, 2, unrollFunc_domain, td->String);
	//---------------------------
	// RegexPlus := Regex --> Regex
	Z3_symbol regexPlus_name = Z3_mk_string_symbol(ctx, languageMap[REGEXPLUS].c_str());
	Z3_sort regexPlus_domain[1];
	regexPlus_domain[0] = td->Regex;
	td->RegexPlus = Z3_theory_mk_func_decl(ctx, Th, regexPlus_name, 1, regexPlus_domain, td->Regex);
	//---------------------------
	// RegexCharRange := String x String --> Regex
	Z3_symbol regexCharRange_name = Z3_mk_string_symbol(ctx, languageMap[REGEXCHARRANGE].c_str());
	Z3_sort regexCharRange_domain[2];
	regexCharRange_domain[0] = td->String;
	regexCharRange_domain[1] = td->String;
	td->RegexCharRange = Z3_theory_mk_func_decl(ctx, Th, regexCharRange_name, 2, regexCharRange_domain, td->Regex);
	//---------------------------
	// RegexAll--> Regex
	Z3_symbol regexAll_name = Z3_mk_string_symbol(ctx, languageMap[REGEXALL].c_str());
	Z3_sort regexAll_domain[0];
	td->RegexAll = Z3_theory_mk_func_decl(ctx, Th, regexAll_name, 0, regexAll_domain, td->Regex);
	//---------------------------
	// RegexAll--> Regex
	Z3_symbol regexAllChar_name = Z3_mk_string_symbol(ctx, languageMap[REGEXALLCHAR].c_str());
	Z3_sort regexAllChar_domain[0];
	td->RegexAllChar = Z3_theory_mk_func_decl(ctx, Th, regexAllChar_name, 0, regexAllChar_domain, td->Regex);
	//---------------------------
	// RegexAll--> Regex
	Z3_symbol regexNone_name = Z3_mk_string_symbol(ctx, languageMap[REGEXNONE].c_str());
	Z3_sort regexNone_domain[0];
	td->RegexNone = Z3_theory_mk_func_decl(ctx, Th, regexNone_name, 0, regexNone_domain, td->Regex);

	//---------------------------
	// AutomataDef := String --> String
	Z3_symbol automata_name = Z3_mk_string_symbol(ctx, "AutomataDef");
	Z3_sort automata_domain[1];
	automata_domain[0] = td->String;
	td->AutomataDef = Z3_theory_mk_func_decl(ctx, Th, automata_name, 1, automata_domain, td->String);

	// NonDetAutomatDef := String x Int --> String
	Z3_symbol nondetautomata_name = Z3_mk_string_symbol(ctx, "NonDet_AutomataDef");
	Z3_sort nondetautomata_domain[2];
	nondetautomata_domain[0] = td->String;
	nondetautomata_domain[1] = IntSort;
	td->NonDet_AutomataDef = Z3_theory_mk_func_decl(ctx, Th, nondetautomata_name, 2, nondetautomata_domain, td->String);

	// GrammarIn :=  String x Grammar --> Bool
	Z3_symbol grammarIn_name = Z3_mk_string_symbol(ctx, "GrammarIn");
	Z3_sort grammarIn_domain[2];
	grammarIn_domain[0] = td->String;
	grammarIn_domain[1] = td->Grammar;
	td->GrammarIn = Z3_theory_mk_func_decl(ctx, Th, grammarIn_name, 2, grammarIn_domain, BoolSort);

	// Str2Grm := String --> Grammar
	Z3_symbol str2Grm_name = Z3_mk_string_symbol(ctx, "Str2Grm");
	Z3_sort str2Grm_domain[1];
	str2Grm_domain[0] = td->String;
	td->Str2Grm = Z3_theory_mk_func_decl(ctx, Th, str2Grm_name, 1, str2Grm_domain, td->Grammar);

	// Parikh := String x Int --> Int
	Z3_symbol parikh_name = Z3_mk_string_symbol(ctx, "ParikhImg");
	Z3_sort parikh_domain[2];
	parikh_domain[0] = td->String;
	parikh_domain[1] = IntSort;
	td->Parikh = Z3_theory_mk_func_decl(ctx, Th, parikh_name, 2, parikh_domain, IntSort);

	Z3_set_delete_callback(Th, Th_delete);
	Z3_set_reduce_eq_callback(Th, cb_reduce_eq);
	Z3_set_reduce_app_callback(Th, Th_reduce_app);
	Z3_set_new_app_callback(Th, Th_new_app);
	Z3_set_new_elem_callback(Th, Th_new_elem);
	Z3_set_init_search_callback(Th, Th_init_search);
	Z3_set_push_callback(Th, Th_push);
	Z3_set_pop_callback(Th, Th_pop);
	Z3_set_reset_callback(Th, Th_reset);
	Z3_set_restart_callback(Th, Th_restart);
	Z3_set_new_eq_callback(Th, Th_new_eq);
	Z3_set_new_diseq_callback(Th, Th_new_diseq);
	Z3_set_new_relevant_callback(Th, Th_new_relevant);
	Z3_set_new_assignment_callback(Th, Th_new_assignment);
	Z3_set_final_check_callback(Th, Th_final_check);
	return Th;
}

/**
   \brief Callback: invoked when \c t is deleted.
   This callback can be used to free theory specific data-structures.
 */
void Th_delete(Z3_theory t) {
	AutomatonStringData * td = (AutomatonStringData *)Z3_theory_get_ext_data(t);
	__debugPrint(logFile, "\n** Delete()\n");
	free(td);
}

/**
   \brief Callback: invoked when \c n is finally added to the logical context.
   \c n is an application of the form <tt>g(...)</tt> where \c g is an
   interpreted function symbol of \c t.
 */
void Th_new_app(Z3_theory t, Z3_ast n) {
}

/**
   \brief Callback: invoked when \c n is finally added to the logical context.
   \c n is an expression of sort \c s, where \c s is an interpreted sort of \c t.
 */
void Th_new_elem(Z3_theory t, Z3_ast n) {
}

void cb_arith_new_eq(Z3_theory t, Z3_ast n1, Z3_ast n2) {
	__debugPrint(logFile, "%d *** %s@%d ***: = ", __LINE__, __FUNCTION__, sLevel);
	printZ3Node(t, n1);
	__debugPrint(logFile, " ");
	printZ3Node(t, n2);
	__debugPrint(logFile, " \n");

	if (sLevel == 0){
		constraintSet.arithmeticConstraints.emplace(createEqualConstraint(node_to_string(t, n1), node_to_string(t, n2)));
	}
}

/**
   \brief Callback: invoked when Z3 starts the search for a satisfying assignment.
 */
void Th_init_search(Z3_theory t) {
	Z3_context ctx = Z3_theory_get_context(t);
	timer = clock();

#ifdef DEBUGLOG
	Z3_ast ctxAssign = Z3_get_context_assignment(ctx);
	__debugPrint(logFile, "\n\n");

	for (const auto& var : inputVarInLen) {
		printZ3Node(t, var);
		__debugPrint(logFile, ", ");
	}

	__debugPrint(logFile, "***********************************************\n");
	__debugPrint(logFile, "*               Starting Search               *\n");
	__debugPrint(logFile, "-----------------------------------------------\n");
	printZ3Node(t, ctxAssign);
	__debugPrint(logFile, "\n");
#endif

	searchStart = 1;
	Z3_theory_set_arith_new_eq_cb(t, cb_arith_new_eq);

}

/**
   \brief Callback: invoked when Z3 creates a case-split (aka backtracking point).
 */
void Th_push(Z3_theory t) {
	sLevel++;
	__debugPrint(logFile, "\n*******************************************\n");
	__debugPrint(logFile, "[PUSH]: Level = %d\n", sLevel);
	__debugPrint(logFile, "\n*******************************************\n");
	if (sLevel == 1) {
		initLength = collectCurrentLength(t);
	}
}

/**
   \brief Callback: invoked when Z3 backtracks a case-split.

   \see Th_push
 */
void Th_pop(Z3_theory t) {
	__debugPrint(logFile, "\n*******************************************\n");
	__debugPrint(logFile, "[POP]: Level = %d\n", sLevel - 1);
	__debugPrint(logFile, "\n*******************************************\n");

	for (std::map<std::pair<Z3_ast, int>, Automaton>::iterator it = internalVarMap.begin(); it != internalVarMap.end(); ++it) {
		if (it->first.second == sLevel && it->second.name.compare(UNKNOWN_AUTOMATON) != 0) {
			it->second.name = UNKNOWN_AUTOMATON;
		}
	}

	for (std::map<std::pair<Z3_ast, int>, Automaton>::iterator it = internalVarMap_withoutCombination.begin(); it != internalVarMap_withoutCombination.end(); ++it)  {
		if (it->first.second == sLevel && it->second.name.compare(UNKNOWN_AUTOMATON) != 0) {
			it->second.name = UNKNOWN_AUTOMATON;
		}
	}

	for (std::map<std::pair<Z3_ast, int>, std::vector<Z3_ast>>::iterator it = equalMap.begin(); it != equalMap.end(); ++it) {
		if (it->first.second >= sLevel && it->second.size() > 0) {
			it->second.clear();
		}
	}

	for (std::map<std::pair<Z3_ast, int>, std::pair<int, int>>::iterator it = length_LanguageMap.begin(); it != length_LanguageMap.end(); ) {
		if (it->first.second >= sLevel) {
			it = length_LanguageMap.erase(it);
		}
		else
			++it;
	}

	std::vector<std::pair<std::pair<Z3_ast, Z3_ast>, int>> _disequalityList;
	for (const auto& dEq : disequalityList) {
		if (dEq.second < sLevel){
			_disequalityList.emplace_back(dEq);
		}
	}
	disequalityList = _disequalityList;

	sLevel--;
	leavePos = 0;
	done = false;

	lengthDefined = false;
	languageDefined = false;
	finalValues.clear();
}

/**
   \brief Callback: invoked when the logical context containing \c t is reset.
 */
void Th_reset(Z3_theory t) {
	__debugPrint(logFile, "\n** Reset():\n");
}

/**
   \brief Callback: invoked when Z3 restarts the search for a satisfying assignment.
 */
void Th_restart(Z3_theory t) {
	__debugPrint(logFile, "\n** Restart():\n");
}

/**
   \brief Callback: invoked when <tt>n1 = n2</tt> is true in the logical context.

   Z3 will only invoke this callback using expressions \c n1 and \c n2 s.t.
   #Th_new_app or #Th_new_elem was invoked for them.
 */
void Th_new_eq(Z3_theory t, Z3_ast nn1, Z3_ast nn2) {

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n\n\n\n");
	__debugPrint(logFile, "=================================================================================\n");
	__debugPrint(logFile, "** %s ***: @%d\n", __FUNCTION__, sLevel);
	printZ3Node(t, nn1);
	__debugPrint(logFile, "  = ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, "\n");

	__debugPrint(logAxiom, "\n\n\n\n");
	__debugPrint(logAxiom, "=================================================================================\n");
	__debugPrint(logAxiom, "** %s ***: @%d\n", __FUNCTION__, sLevel);
	printZ3NodeAxiom(t, nn1);
	__debugPrint(logAxiom, "  = ");
	printZ3NodeAxiom(t, nn2);
	__debugPrint(logAxiom, "\n");
#endif

	Z3_context ctx = Z3_theory_get_context(t);

	std::vector<Z3_ast> eq_nn1 = collect_eqc(t, nn1);
	std::vector<Z3_ast> eq_nn2 = collect_eqc(t, nn2);

	if (isVariable(t, nn1)) {
		if (isConcatFunc(t, nn2)){
			std::vector<Z3_ast> list;
			collect_node_in_concat(t, nn2, list);
			for (const auto& node : list){
				std::vector<Z3_ast> eq_node = collect_eqc(t, node);
				for (const auto& _node : eq_node)
					if (_node == nn1)
						return;
			}
		}
	}

	if (isVariable(t, nn2)) {
		if (isConcatFunc(t, nn1)){
			std::vector<Z3_ast> list;
			collect_node_in_concat(t, nn1, list);
			displayListNode(t, list, "xxxxxx");
			for (const auto& node : list){
				std::vector<Z3_ast> eq_node = collect_eqc(t, node);
				for (const auto& _node : eq_node)
					if (_node == nn2)
						return;
			}
		}
	}
	if (done == true || skipOverapprox == true) {
		if (done)
			__debugPrint(logFile, "%d Completed!\n", __LINE__);
		return;
	}


	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	if (isConstStr(t, nn1) || isConstStr(t, nn2)) {
		return;
	}

	addLengthConstraint(t, nn1, nn2);

//	initLengthPropagation(t, nn1, nn2);

	if (!checkEqualConsistency(t, nn1, nn2)) {
		Z3_ast toAssert = negatedConstraint(t);

		__debugPrint(logFile, "@%d >> Negate of:", __LINE__);
		printZ3Node(t, toAssert);
		if (toAssert == NULL)
			addAxiom(t, negateEquality(t, nn1, nn2), __LINE__, true);
		return;
	}

//	if (!checkContainConsistency(t, nn1, nn2)){
//		Z3_ast toAssert = negatedConstraint(t);
//
//		__debugPrint(logFile, "@%d >> Negate of:", __LINE__);
//		printZ3Node(t, toAssert);
//		if (toAssert == NULL)
//			addAxiom(t, negateEquality(t, nn1, nn2), __LINE__, true);
//		return;
//	}

//	add_prefix_relation(t, nn1, nn2);
//	add_posfix_relation(t, nn1, nn2);

//	implyEqualityForConcatMember(t, nn1, nn2);

	add_endsWith_consistency(t, nn1, nn2);

	add_replace_consistency(t, nn1, nn2);

	if (consideredVars.size() > 0) {
		std::vector<std::pair<Z3_ast, int>> langVal;

		// collect language values index
		for (unsigned int i = 0; i < consideredVars.size(); ++i) {
			int index = collectSingleLanguage_index(t, consideredVars[i]);
			if (index <= 0)
				return;
			langVal.emplace_back(std::make_pair(consideredVars[i], index));
		}

		// have enough indices
		if ((isVariable(t, nn1) && isAutomatonFunc(t, nn2)) || (isVariable(t, nn2) && isAutomatonFunc(t, nn1))) {
			Automaton ton01 = getPreCalculatedValue(t, nn1);
			if (ton01.isConst()) {
				__debugPrint(logFile, "@%d Update value at cb_new_eq \n", __LINE__);
				if (isVariable(t, nn1))
					final_value_Map[nn1] = nn2;
				else
					final_value_Map[nn2] = nn1;
				return;
			}

			Z3_ast toAssert;

			//prevent to repeat extension
			// TODO bring to the beginning
			if (lang_value_Map2.find(langVal) != lang_value_Map2.end()) {
				toAssert = lang_value_Map2[langVal];
			}
			else {
				toAssert = extendEqualVars_Automata(t, langVal);
				lang_value_Map2[langVal] = toAssert;
			}

			if (toAssert != NULL)
				addAxiom_Theory(t, toAssert, __LINE__, true);
			return;
		}
	}

	if (Z3_get_sort(ctx, nn1) != td->String || Z3_get_sort(ctx, nn2) != td->String) {
		__debugPrint(logFile, "-----------------\n");
		__debugPrint(logFile, ">> [cb_new_eq] SKIP: NOT String Sort @ %d\n\n", __LINE__);
		__debugPrint(logFile, "=================================================================================\n");
		return;
	}
}

/*
 * nn1 = nn2 => |nn1| = |nn2|
 * |nn1| = 0 => nn1 = ""
 * |nn2| = 0 => nn2 = ""
 */
void addLengthConstraint(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	Z3_context ctx = Z3_theory_get_context(t);
//	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	Z3_ast leng_nn1 = mk_length(t, nn1);
	Z3_ast leng_nn2 = mk_length(t, nn2);
	addAxiom(t, Z3_mk_eq(ctx, leng_nn1, leng_nn2), __LINE__, true);
//	addAxiom(t, Z3_mk_implies(ctx,
//			Z3_mk_eq(ctx, leng_nn1, mk_int(ctx, 0)),
//			Z3_mk_eq(ctx, nn1, mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, "")))), __LINE__, true);
//	addAxiom(t, Z3_mk_implies(ctx,
//			Z3_mk_eq(ctx, leng_nn2, mk_int(ctx, 0)),
//			Z3_mk_eq(ctx, nn2, mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, "")))), __LINE__, true);
}

/*
 *
 */
void implyEqualityForConcatMember(Z3_theory t, Z3_ast lhs, Z3_ast rhs){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n");
	__debugPrint(logFile, "=================================================================================\n");
	__debugPrint(logFile, "** implyEqualityForConcatMember(): @%d\n", sLevel);
	__debugPrint(logFile, "\n");
#endif
	/* lhs . a = rhs . b --> a = b */
	Z3_context ctx = Z3_theory_get_context(t);
	std::set<Z3_ast> concatOfLhs = findAllConcatContainingNode(t, lhs, 0);
	std::set<Z3_ast> concatOfRhs = findAllConcatContainingNode(t, rhs, 0);

	for (std::set<Z3_ast>::iterator it = concatOfLhs.begin(); it != concatOfLhs.end(); ++it){
		std::vector<Z3_ast> eq01 = collect_eqc(t, *it);
		for (unsigned int i = 0; i < eq01.size(); ++i)
			if (std::find(concatOfRhs.begin(), concatOfRhs.end(), eq01[i]) != concatOfRhs.end()) {
				assert(isConcatFunc(t, eq01[i]));
				Z3_ast node01 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq01[i]), 1);
				Z3_ast node02 = Z3_get_app_arg(ctx, Z3_to_app(ctx, *it), 1);

				/* rhs . a = lhs. b --> a = b */

				std::vector<Z3_ast> eqNode01 = collect_eqc(t, node01);
				if (std::find(eqNode01.begin(), eqNode01.end(), node02) == eqNode01.end()) {
					addAxiom(t, Z3_mk_implies(ctx, Z3_mk_eq(ctx, lhs, rhs), Z3_mk_eq(ctx, node01, node02)), __LINE__, true);
				}
			}
	}

	concatOfLhs.clear();
	concatOfRhs.clear();

	/* a . lhs = b . rhs --> a = b */

	concatOfLhs = findAllConcatContainingNode(t, lhs, 1);
	concatOfRhs = findAllConcatContainingNode(t, rhs, 1);

	for (std::set<Z3_ast>::iterator it = concatOfLhs.begin(); it != concatOfLhs.end(); ++it){
		std::vector<Z3_ast> eq01 = collect_eqc(t, *it);
		for (unsigned int i = 0; i < eq01.size(); ++i) {
			if (std::find(concatOfRhs.begin(), concatOfRhs.end(), eq01[i]) != concatOfRhs.end()) {
				assert(isConcatFunc(t, eq01[i]));
				Z3_ast node01 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq01[i]), 0);
				Z3_ast node02 = Z3_get_app_arg(ctx, Z3_to_app(ctx, *it), 0);
				/* rhs . a = lhs. b --> a = b */
				std::vector<Z3_ast> eqNode01 = collect_eqc(t, node01);
				if (std::find(eqNode01.begin(), eqNode01.end(), node02) == eqNode01.end()) {
					addAxiom(t, Z3_mk_implies(ctx, Z3_mk_eq(ctx, lhs, rhs), Z3_mk_eq(ctx, node01, node02)), __LINE__, true);
				}
			}
		}
	}

	/* lhs = a. x && rhs = b . x --> a = b */
	std::vector<Z3_ast> eqLhs = collect_eqc(t, lhs);
	std::vector<Z3_ast> eqRhs = collect_eqc(t, rhs);
	for (unsigned int i = 0; i < eqLhs.size(); ++i)
		if (isConcatFunc(t, eqLhs[i])) {
			Z3_ast arg01 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eqLhs[i]), 0);
			Z3_ast arg02 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eqLhs[i]), 1);
			std::vector<Z3_ast> eqArg01 = collect_eqc(t, arg01);
			std::vector<Z3_ast> eqArg02 = collect_eqc(t, arg02);
			for (unsigned int j = 0; j < eqRhs.size(); ++j)
				if (isConcatFunc(t, eqRhs[j])) {
					Z3_ast arg03 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eqRhs[j]), 0);
					Z3_ast arg04 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eqRhs[j]), 1);
					if (std::find(eqArg01.begin(), eqArg01.end(), arg03) !=  eqArg01.end() &&
							std::find(eqArg02.begin(), eqArg02.end(), arg04) ==  eqArg02.end()) {
						std::vector<Z3_ast> andNode;
						andNode.emplace_back(Z3_mk_eq(ctx, lhs, rhs));
						andNode.emplace_back(Z3_mk_eq(ctx, lhs, eqLhs[i]));
						andNode.emplace_back(Z3_mk_eq(ctx, arg01, arg03));

						addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andNode), Z3_mk_eq(ctx, arg02, arg04)), __LINE__, true);
					}
					else
						if (std::find(eqArg01.begin(), eqArg01.end(), arg03) ==  eqArg01.end() &&
								std::find(eqArg02.begin(), eqArg02.end(), arg04) !=  eqArg02.end()) {
							std::vector<Z3_ast> andNode;
							andNode.emplace_back(Z3_mk_eq(ctx, lhs, rhs));
							andNode.emplace_back(Z3_mk_eq(ctx, lhs, eqLhs[i]));
							andNode.emplace_back(Z3_mk_eq(ctx, arg02, arg04));

							addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andNode), Z3_mk_eq(ctx, arg01, arg03)), __LINE__, true);
						}
				}
		}
}

/*
 *
 */
std::set<Z3_ast> findAllConcatContainingNode(Z3_theory t, Z3_ast node, int pos){
	std::set<Z3_ast> results;
	for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = concat_astNode_map.begin(); it != concat_astNode_map.end(); ++it) {
		if (pos == 0) {
			if (it->first.first == node) {
				results.insert(it->second);
			}
		}
		else if (pos == 1){
			if (it->first.second == node)
				results.insert(it->second);
		}
	}
	return results;
}
/*
 *
 */
std::vector<Z3_ast> initLengthPropagation(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> lengthPropagation;

	if (isConcatFunc(t, nn1)) {
		Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, nn1), 0);
		Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, nn1), 1);

		int leng00 = getLenValue(t, arg0);
		int leng01 = getLenValue(t, arg1);

		if (leng00 != -1) {
			lengthPropagation.emplace_back(arg0);
		}
		if (leng01 != -1) {
			lengthPropagation.emplace_back(arg1);
		}
	}
	else if (isStrVariable(t, nn1) || isAutomatonFunc(t, nn2)) {

		int leng01 = getLenValue(t, nn1);

		if (leng01 != -1) {
			lengthPropagation.emplace_back(nn1);
			printZ3Node(t, nn1);
			__debugPrint(logFile, ": length = %d \n", leng01);
		}
	}


	if (isConcatFunc(t, nn2)) {
		Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, nn2), 0);
		Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, nn2), 1);

		int leng00 = getLenValue(t, arg0);
		int leng01 = getLenValue(t, arg1);

		if (leng00 != -1) {
			lengthPropagation.emplace_back(arg0);
			printZ3Node(t, arg0);
			__debugPrint(logFile, ": length = %d \n", leng00);
		}
		if (leng01 != -1) {
			lengthPropagation.emplace_back(arg1);
			printZ3Node(t, arg1);
			__debugPrint(logFile, ": length = %d \n", leng01);
		}
	}
	else if (isStrVariable(t, nn2) || isAutomatonFunc(t, nn2)) {

		int leng01 = getLenValue(t, nn2);

		if (leng01 != -1) {
			lengthPropagation.emplace_back(nn2);
			printZ3Node(t, nn2);
			__debugPrint(logFile, ": length = %d \n", leng01);
		}
	}
	return lengthPropagation;
}
/*
 *
 */
bool updateConcatLength(Z3_theory t, Z3_ast node, bool alwaysAdd = true) {
	Z3_context ctx = Z3_theory_get_context(t);
	std::pair<int, int> oldValue = getLengthDomain(node);

	Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0);
	Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 1);

	std::pair<int, int> domain00 = getLengthDomain(arg0);
	if (domain00.first == -1)
		domain00.first = 0;

	std::pair<int, int> domain01 = getLengthDomain(arg1);
	if (domain01.first == -1)
		domain01.first = 0;

	std::pair<int, int> newValue;

	newValue.first = domain00.first + domain01.first;
	newValue.second = domain00.second >= 0 && domain01.second >= 0 ? domain00.second + domain01.second : -1;

	printZ3Node(t, node);
	__debugPrint(logFile, "\n%d\t\t updateConcatLength (%d, %d) -- (%d, %d) --> (%d, %d)\n", __LINE__, domain00.first, domain00.second, domain01.first, domain01.second, newValue.first, newValue.second);
	length_LanguageMap[std::make_pair(node, sLevel)] = newValue;

	if (alwaysAdd || !(oldValue.first == newValue.first && oldValue.second == newValue.second)) {
		__debugPrint(logFile, "\t\t");
		printZ3Node(t, node);
		__debugPrint(logFile, "\t\tComponent size (%d, %d) -- (%d, %d) --> (%d, %d)\n", domain00.first, domain00.second, domain01.first, domain01.second, newValue.first, newValue.second);
	}
	return !(oldValue.first == newValue.first && oldValue.second == newValue.second);
}

/*
 *
 */
bool updateLengthNode_withValue(Z3_theory t, Z3_ast node, int minn, int maxx) {
	bool change = false;
	std::pair<int, int> value = getLengthDomain(node);
	if (value.first < minn) {
		value.first = minn;
		change = true;
	}
	if ((value.second > maxx && maxx != -1) || value.second == -1) {
		value.second = maxx;
		change = true;
	}
	length_LanguageMap[std::make_pair(node, sLevel)] = value;
	return change;
}

/*
 * Update the parent
 */
void doLengthPropagation(Z3_theory t, std::vector<Z3_ast> nodeList){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n");
	__debugPrint(logFile, "=================================================================================\n");
	__debugPrint(logFile, "** doLengthPropagation: @%d\n", sLevel);
	__debugPrint(logFile, "=================================================================================\n");
#endif
	std::vector<Z3_ast> checkingNode;
	std::map<Z3_ast, bool>  visited;

	// update from solver
	for (unsigned i = 0; i < nodeList.size(); ++i) {
		checkingNode.emplace_back(nodeList[i]);
	}

	for (unsigned i = 0; i < checkingNode.size(); ++i)
		visited[checkingNode[i]] = true;

	unsigned int pos = 0;
	while (pos < checkingNode.size()) {
		Z3_ast currentNode = checkingNode[pos];
		std::pair<int, int> domain = getLengthDomain(currentNode);

		printZ3Node(t, currentNode);
		__debugPrint(logFile, " (line %d) (%d -- %d)", __LINE__, domain.first, domain.second);

		if (isStrVariable(t, currentNode) || isConcatFunc(t, currentNode) || isAutomatonFunc(t, currentNode)) {
			std::vector<Z3_ast> eq_nodes = collect_eqc(t, currentNode);

			// edit domain --> collect the best guy
			collectBestDomain(eq_nodes, domain);

			// update domain
			__debugPrint(logFile, "\t\t ---> (%d -- %d)\n", domain.first, domain.second);

			updateLengthNode_withValue(t, currentNode, domain.first, domain.second);
			for (unsigned int i = 0; i < eq_nodes.size(); ++i)
				updateLengthNode_withValue(t, eq_nodes[i], domain.first, domain.second);

			// propagate the value to parents
			std::set<Z3_ast> parents = collectAllParents(t, currentNode);
			for (std::set<Z3_ast>::iterator it = parents.begin(); it != parents.end(); ++it) {
				if (!isLengthFunc(t, *it)) {
					if (visited.find(*it) == visited.end()) {
						checkingNode.emplace_back(*it);
						visited[*it] = true;

						// edit domain
						if (isConcatFunc(t, *it)) {
							updateConcatLength(t, *it);
						}
						else {
							__debugPrint(logFile, "%d Do not care about other function: ", __LINE__);
							printZ3Node(t, *it);
							__debugPrint(logFile, "\n");
						}
					}
					else {
						if (isConcatFunc(t, *it)) {
							bool changed = updateConcatLength(t, *it, false);
							if (changed) {
								checkingNode.emplace_back(*it);
								__debugPrint(logFile, "\t\t\t\t re-update domain\n");
							}
						}
						else {
							__debugPrint(logFile, "%d Do not care about other function: ", __LINE__);
							printZ3Node(t, *it);
							__debugPrint(logFile, "\n");
						}
					}
				}
			}

			__debugPrint(logFile, "%d %s xxx\n", __LINE__, __FUNCTION__);

			if (domain.second >= 0) {
#if 0
				// propagate concat to children
				for (unsigned int i = 0; i < eq_nodes.size(); ++i) {
					if (isConcatFunc(t, eq_nodes[i])) {
						Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq_nodes[i]), 0);
						Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq_nodes[i]), 1);

						//						bool childChanged = false;
						std::pair<int, int> tmpDomain = getLengthDomain(arg0);

						if (tmpDomain.second > domain.second || tmpDomain.second == -1) {
							//							childChanged = true;
							tmpDomain.second = domain.second;
							length_LanguageMap[std::make_pair(arg0, sLevel)] = tmpDomain;
							checkingNode.emplace_back(arg0);
							printZ3Node(t, arg0);
							__debugPrint(logFile, ": Left Child update domain: %d -- %d\n", tmpDomain.first, tmpDomain.second);
						}

						tmpDomain = getLengthDomain(arg1);
						if (tmpDomain.second > domain.second || tmpDomain.second == -1) {
							//							childChanged = true;
							tmpDomain.second = domain.second;
							length_LanguageMap[std::make_pair(arg1, sLevel)] = tmpDomain;
							checkingNode.emplace_back(arg1);

							printZ3Node(t, arg1);
							__debugPrint(logFile, ": Right Child update domain: %d -- %d\n", tmpDomain.first, tmpDomain.second);
						}
					}
				}
#endif
			}
		}
		pos++;
	}
	__debugPrint(logFile, "%d %s leaving\n", __LINE__, __FUNCTION__);
}

/*
 * edit domain --> collect the best guy
 */
bool collectBestDomain(std::vector<Z3_ast> eq_nodes, std::pair<int, int> &domain){
	bool changed = false;
	for (unsigned int i = 0; i < eq_nodes.size(); ++i) {
		std::pair<int, int> lengthDomain = getLengthDomain(eq_nodes[i]);
		if (domain.first < lengthDomain.first) {
			domain.first = lengthDomain.first;
			changed = true;
		}
		if (domain.second > lengthDomain.second && lengthDomain.second != -1) {
			domain.second = lengthDomain.second;
			changed = true;
		}
	}
	return changed;
}

/*
 * count length of string
 */
int calculateAutomatonSize(Z3_theory t, Z3_ast node){
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_app func_app = Z3_to_app(ctx, node);
	Z3_func_decl funcDecl = Z3_get_app_decl(ctx, func_app);
	if (funcDecl == td->AutomataDef){
		Z3_ast arg = Z3_get_app_arg(ctx, func_app, 0);
		std::string str = Z3_ast_to_string(ctx, arg);
		str = customizeString(str);
		if (str.find("*") == std::string::npos  && str.find("|") == std::string::npos) {
			int cnt = 0;
			for (unsigned int i = 0; i < str.size(); ++i){
				if ((str[i] >= 'a' && str[i] <= 'z') ||
						(str[i] >= 'A' && str[i] <= 'Z') ||
						(str[i] >= '0' && str[i] <= '9'))
					cnt++;
			}
			return cnt;
		}
	}
	return -1;
}

/*
 * a contains "xyz" == false && b = x . "123xyz" . y && a == b --> false
 */
void add_impliable_contains(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	__debugPrint(logFile, "%d *** %s *** (", __LINE__, __FUNCTION__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, ",");
	printZ3Node(t, nn2);
	__debugPrint(logFile, ")\n");
	Z3_context ctx = Z3_theory_get_context(t);

	std::set<Z3_ast> children01; getNodesInConcat_extended(t, nn1, children01);
	std::set<Z3_ast> children02; getNodesInConcat_extended(t, nn2, children02);

	std::vector<Z3_ast> eq_nn1 = collect_eqc(t, nn1);
	std::vector<Z3_ast> eq_nn2 = collect_eqc(t, nn2);

	/* a contains "xyz" == false && b = x . "123xyz" . y && a == b --> false */
	for (const auto& containsNode : containPairBoolMap) {
		if (std::find(eq_nn1.begin(), eq_nn1.end(), containsNode.first.first) != eq_nn1.end() &&
				(isDetAutomatonFunc(t, containsNode.first.second) || isConstStr(t, containsNode.first.second))) {

			/* get const string */
			std::string tmpStr = getConstString(t, containsNode.first.second);

			for (const auto& itor : children02)
				if (isDetAutomatonFunc(t, itor) || isRegexPlusFunc(t, itor)){
					std::string wholeStr = getConstString(t, itor);
					if (wholeStr.find(tmpStr) != std::string::npos){
						addAxiom(t, Z3_mk_implies(ctx, Z3_mk_not(ctx, containsNode.second), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1 ,nn2))), __LINE__, true);
					}
				}
		}

		if (std::find(eq_nn2.begin(), eq_nn2.end(), containsNode.first.first) != eq_nn2.end() &&
				(isDetAutomatonFunc(t, containsNode.first.second) || isConstStr(t, containsNode.first.second))) {

			/* get const string */
			std::string tmpStr = getConstString(t, containsNode.first.second);

			for (const auto& itor : children01)
				if (isDetAutomatonFunc(t, itor) || isRegexPlusFunc(t, itor)){
					std::string wholeStr = getConstString(t, itor);
					if (wholeStr.find(tmpStr) != std::string::npos){
						addAxiom(t, Z3_mk_implies(ctx, Z3_mk_not(ctx, containsNode.second), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1 ,nn2))), __LINE__, true);
					}
				}
		}

	}

	/*
	 * a contains "xyz" == false && b = x . y && a == b && y does not contains "xyz" --> false
	 */
	if (isConcatFunc(t, nn1)){
		std::vector<Z3_ast> nodeList;
		getNodesInConcat(t, nn1, nodeList);
		for (const auto& n : nodeList){
			for (const auto& containsNode : containPairBoolMap){
				if (containsNode.first.first == n){
					std::pair<Z3_ast, Z3_ast> p = std::make_pair(nn2, containsNode.first.second);
					if (containPairBoolMap.find(p) != containPairBoolMap.end()){
						Z3_ast tmp = Z3_mk_implies(ctx, containsNode.second, containPairBoolMap[p]);
						addAxiom(t, tmp, __LINE__, true);
					}
				}
			}
		}
	}

	if (isConcatFunc(t, nn2)){
		std::vector<Z3_ast> nodeList;
		getNodesInConcat(t, nn2, nodeList);
		for (const auto& n : nodeList){
			for (const auto& containsNode : containPairBoolMap){
				if (containsNode.first.first == n){
					std::pair<Z3_ast, Z3_ast> p = std::make_pair(nn1, containsNode.first.second);
					if (containPairBoolMap.find(p) != containPairBoolMap.end()){
						Z3_ast tmp = Z3_mk_implies(ctx, containsNode.second, containPairBoolMap[p]);
						addAxiom(t, tmp, __LINE__, true);
					}
				}
			}
		}
	}
}

/*
 *  a contains b && b contains c --> a contains c
 */
void add_transitive_contains(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	Z3_context ctx = Z3_theory_get_context(t);

	/* add transitive constraint*/
	std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> considerContain01;
	std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> considerContain02;
	for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = containPairBoolMap.begin(); it != containPairBoolMap.end(); ++it) {
		if (it->first.first == nn1 || it->first.first == nn2) {
			considerContain01[it->first] = it->second;
		}

		if (it->first.second == nn1 || it->first.second == nn2) {
			considerContain02[it->first] = it->second;
		}
	}

	for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = considerContain01.begin(); it != considerContain01.end(); ++it) {
		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator itor = considerContain02.begin(); itor != considerContain02.end(); ++itor) {

			/* compare all possible combinations */
			std::vector<Z3_ast> eqFirst = collect_eqc(t, itor->first.first);
			std::vector<Z3_ast> eqSecond = collect_eqc(t, it->first.second);
			for (unsigned int i = 0; i < eqFirst.size(); ++i)
				for (unsigned int j = 0; j < eqSecond.size(); ++j){
					std::pair<Z3_ast, Z3_ast> aPair(eqFirst[i], eqSecond[j]);
					if (containPairBoolMap.find(aPair) != containPairBoolMap.end()) {
						std::vector<Z3_ast> constraints;
						constraints.emplace_back(it->second);
						constraints.emplace_back(itor->second);
						Z3_ast implies = Z3_mk_implies(ctx, mk_and_fromVector(t, constraints), containPairBoolMap[aPair]);
						addAxiom(t, implies, __LINE__, true);
					}
				}
		}
	}
}

/*
 *  a contains c && a = b --> b contains c
 *  a contains b && b contains c --> a contains c
 *  a contains "xyz" && a = "123xyz" --> true
 */
bool checkContainConsistency(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	__debugPrint(logFile, "** %d *** %s ***: \n", __LINE__, __FUNCTION__);

	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> eq01 = collect_eqc(t, nn1);
	std::vector<Z3_ast> eq02 = collect_eqc(t, nn2);
	__debugPrint(logFile, "** %d *** %s *** 1 : \n", __LINE__, __FUNCTION__);

	std::set<Z3_ast> children01; getNodesInConcat_extended(t, nn1, children01);
	std::set<Z3_ast> children02; getNodesInConcat_extended(t, nn2, children02);

	/* a contains c && a = b --> b contains c */
	for (const auto& it : children01) {
		for (unsigned int i = 0; i < eq02.size(); ++ i){
			std::pair<Z3_ast, Z3_ast> tmpPair(eq02[i], it);
			if (containPairBoolMap.find(tmpPair) != containPairBoolMap.end()) {
				/* not bool -> not equal*/
				Z3_ast notTmp = Z3_mk_not(ctx, containPairBoolMap[tmpPair]);
				Z3_ast impliesTmp = Z3_mk_implies(ctx, notTmp, Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2)));
				addAxiom(t, impliesTmp, __LINE__, true);
			}

			/* check conflict if b and c are automatadet */
			if (isDetAutomatonFunc(t, eq02[i]) && isDetAutomatonFunc(t, it)){
				std::string tmp00 = getConstString(t, eq02[i]);
				std::string tmp01 = getConstString(t, it);
				if (tmp00.find(tmp01) == std::string::npos)
					return false;
			}
		}
	}

	/* b contains c && a = b --> a contains c */
	for (const auto& it : children02) {
		for (unsigned int i = 0; i < eq01.size(); ++ i){
			std::pair<Z3_ast, Z3_ast> tmpPair(eq01[i], it);
			if (containPairBoolMap.find(tmpPair) != containPairBoolMap.end()) {
				/* not bool -> not equal*/
				Z3_ast notTmp = Z3_mk_not(ctx, containPairBoolMap[tmpPair]);
				Z3_ast impliesTmp = Z3_mk_implies(ctx, notTmp, Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2)));
				addAxiom(t, impliesTmp, __LINE__, true);
			}

			/* check conflict if b and c are automatadet */
			if (isDetAutomatonFunc(t, eq01[i]) && isDetAutomatonFunc(t, it)){
				std::string tmp00 = getConstString(t, eq01[i]);
				std::string tmp01 = getConstString(t, it);
				if (tmp00.find(tmp01) == std::string::npos)
					return false;
			}
		}
	}

//	add_impliable_contains(t, nn1, nn2);
	add_transitive_contains(t, nn1, nn2);
	__debugPrint(logFile, "%d %s: back\n", __LINE__, __FUNCTION__);
	return true;
}

/*
 *	x = replace a b c
 *	--> contain x y = contain a y if ...
 */
void add_replace_consistency(Z3_theory t, Z3_ast nn1, Z3_ast nn2){

#ifdef DEBUGLOG
	__debugPrint(logFile, "%d *** %s ***: (", __LINE__, __FUNCTION__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, ", ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, ")\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);

	for (const auto& replaceNode: replaceNodeMap){
		if (replaceNode.second == nn1 || replaceNode.second == nn2){
			__debugPrint(logFile, "%d replaceNode: %s\n", __LINE__, Z3_ast_to_string(ctx, replaceNode.second));
			for (const auto& containNode : containPairBoolMap)
				if (containNode.first.first == nn1 || containNode.first.first == nn2) {

					__debugPrint(logFile, "%d containNode .... : %s\n", __LINE__, Z3_ast_to_string(ctx, containNode.first.first));
					printZ3Node(t, replaceNode.first.second.first);
					__debugPrint(logFile, ", ");
					printZ3Node(t, containNode.first.second);
					__debugPrint(logFile, "\n");

					if ((isAutomatonFunc(t, replaceNode.first.second.first) || isConstStr(t, replaceNode.first.second.first)) &&
						 isAutomatonFunc(t, containNode.first.second)){

						__debugPrint(logFile, "%d containNode: %s\n", __LINE__, Z3_ast_to_string(ctx, containNode.first.first));

						std::string str00 = getConstString(t, replaceNode.first.second.first);
						std::string str01 = getConstString(t, containNode.first.second);

						if (str00.find(str01) == std::string::npos &&
							str01.find(str00) == std::string::npos){
							Z3_ast tmp = registerInternalContain(t, replaceNode.first.first, containNode.first.second);
							if (tmp != containNode.second)
								addAxiom(t, Z3_mk_eq(ctx, containNode.second, tmp), __LINE__, true);
						}
					}
				}
		}

		if (replaceNode.first.first == nn1 || replaceNode.second == nn2){

		}
	}

}
/*
 *
 */
void add_startsWith_consistency(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	// TODO add_startsWith_consistency
#ifdef DEBUGLOG
	__debugPrint(logFile, "%d *** %s ***: (", __LINE__, __FUNCTION__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, ", ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, ")\n");
#endif

}

/*
 * a = b && endwith a "abc" && endwith b "abce"  --> false
 * "abc" \in postfix(a) -> endwith a "c" = true *
 */
void add_endsWith_consistency(Z3_theory t, Z3_ast nn1, Z3_ast nn2){

#ifdef DEBUGLOG
	__debugPrint(logFile, "%d *** %s ***: (", __LINE__, __FUNCTION__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, ", ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, ")\n");
#endif

	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> eq01 = collect_eqc(t, nn1);
	std::vector<Z3_ast> eq02 = collect_eqc(t, nn2);

	/* a = b && endswith a "abc" && endswith b "abce"  --> false */
	for (const auto& endswith1 : endsWithPairBoolMap){
		if ((isConstStr(t, endswith1.first.second) || isAutomatonFunc(t, endswith1.first.second)) &&
				std::find(eq01.begin(), eq01.end(), endswith1.first.first) != eq01.end()){

			std::string firstEndsWith = getConstString(t, endswith1.first.second);

			__debugPrint(logFile, "%d endswith 1st: %s -> %s\n", __LINE__, Z3_ast_to_string(ctx, endswith1.first.second), firstEndsWith.c_str());

			for (const auto& endswith2 : endsWithPairBoolMap){
				if ((isConstStr(t, endswith2.first.second) || isAutomatonFunc(t, endswith2.first.second)) &&
						std::find(eq02.begin(), eq02.end(), endswith2.first.first) != eq02.end()){

					std::string secondEndsWith = getConstString(t, endswith2.first.second);

					__debugPrint(logFile, "%d endswith 2nd: %s -> %s\n", __LINE__, Z3_ast_to_string(ctx, endswith2.first.second), secondEndsWith.c_str());

					/* checking consistency */
					if (firstEndsWith.length() >= secondEndsWith.length()){
						std::string tmp = firstEndsWith.substr(firstEndsWith.length() - secondEndsWith.length());
						if (tmp.compare(secondEndsWith) != 0) {
							/* at least one of them cannot happen */
#ifdef DEBUGLOG
							__debugPrint(logFile, "\n");
							printZ3Node(t, endswith1.second);
							__debugPrint(logFile, "\n");
							printZ3Node(t, endswith2.second);
							__debugPrint(logFile, "\n");
#endif
							Z3_ast arr[2] = {endswith1.second, endswith2.second};

							addAxiom(t, Z3_mk_implies(ctx, Z3_mk_and(ctx, 2, arr), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
						}
						else {
							if (firstEndsWith.length() > secondEndsWith.length())
								addAxiom(t, Z3_mk_implies(ctx, endswith1.second, endswith2.second), __LINE__, true);
							else
								addAxiom(t, Z3_mk_eq(ctx, endswith1.second, endswith2.second), __LINE__, true);
						}
					}
					else {
						std::string tmp = secondEndsWith.substr(secondEndsWith.length() - firstEndsWith.length());
						if (tmp.compare(firstEndsWith) != 0) {
							/* at least one of them cannot happen */
#ifdef DEBUGLOG
							__debugPrint(logFile, "\n");
							printZ3Node(t, endswith1.second);
							__debugPrint(logFile, "\n");
							printZ3Node(t, endswith2.second);
							__debugPrint(logFile, "\n");
#endif
							Z3_ast arr[2] = {endswith1.second, endswith2.second};

							addAxiom(t, Z3_mk_implies(ctx, Z3_mk_and(ctx, 2, arr), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
						}
						else {
							addAxiom(t, Z3_mk_implies(ctx, endswith2.second, endswith1.second), __LINE__, true);
						}
					}
				}
			}
		}
	}
}

/**
 * find all nodes that accept "node" as the prefix
 */
std::set<Z3_ast> find_all_nodes_from_prefix(Z3_theory t, Z3_ast node){
	std::vector<Z3_ast> queue;
	queue.emplace_back(node);
	unsigned int pos = 0;
	while (pos < queue.size()) {
		Z3_ast nodeTmp = queue[pos];
		pos++;

		for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = concat_astNode_map.begin(); it != concat_astNode_map.end(); ++it){
			if (it->first.first == nodeTmp && std::find(queue.begin(), queue.end(), it->second) == queue.end()) {
				std::vector<Z3_ast> eq_nodeSecond = collect_eqc(t, it->second);
				for (const auto& n : eq_nodeSecond)
					if (std::find(queue.begin(), queue.end(), n) == queue.end())
						queue.emplace_back(n);
			}
		}
	}
	std::set<Z3_ast> result;
	for (unsigned int i = 1; i < queue.size(); ++i) /* skip itself */
		if (isVariable(t, queue[i]))
			result.insert(queue[i]);

	return result;
}

/*
 * find prefix of a node
 */
std::set<Z3_ast> find_all_prefix_of_node(Z3_theory t, Z3_ast node){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	Z3_context ctx = Z3_theory_get_context(t);

	std::vector<Z3_ast> queue;
	queue.emplace_back(node);
	unsigned int pos = 0;
	while (pos < queue.size()) {
		Z3_ast nodeTmp = queue[pos];
		pos++;

		std::vector<Z3_ast> eq_nodeTmp = collect_eqc(t, nodeTmp);
		for (unsigned int i = 0; i < eq_nodeTmp.size(); ++i){
			if (isConcatFunc(t, eq_nodeTmp[i])){
				Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq_nodeTmp[i]), 0);
				if (std::find(queue.begin(), queue.end(), arg00) == queue.end())
					queue.emplace_back(arg00);
			}
			else if (isVariable(t, eq_nodeTmp[i]) && std::find(queue.begin(), queue.end(), eq_nodeTmp[i]) == queue.end())
				queue.emplace_back(eq_nodeTmp[i]);
		}
	}
//	__debugPrint(logFile, "%d *** %s ***: before refine\n", __LINE__, __FUNCTION__);
//	displayListNode(t, queue, "");
	std::set<Z3_ast> result;
	for (unsigned int i = 1; i < queue.size(); ++i) /* skip itself */
		if (isVariable(t, queue[i])) {
			result.insert(queue[i]);
		}
	return result;
}

/*
 * find posfix of a node
 */
std::set<Z3_ast> find_all_posfix_of_node(Z3_theory t, Z3_ast node){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	Z3_context ctx = Z3_theory_get_context(t);

	std::vector<Z3_ast> queue;
	queue.emplace_back(node);
	unsigned int pos = 0;
	while (pos < queue.size()) {
		Z3_ast nodeTmp = queue[pos];
		pos++;

		std::vector<Z3_ast> eq_nodeTmp = collect_eqc(t, nodeTmp);
		for (const auto& n : eq_nodeTmp){
			if (isConcatFunc(t, n)){
				Z3_ast arg01 = Z3_get_app_arg(ctx, Z3_to_app(ctx, n), 1);
				if (std::find(queue.begin(), queue.end(), arg01) == queue.end())
					queue.emplace_back(arg01);
			}

			if (std::find(queue.begin(), queue.end(), n) == queue.end())
				queue.emplace_back(n);
		}
	}

	std::set<Z3_ast> result;
	for (unsigned int i = 1; i < queue.size(); ++i) /* skip itself */
		result.insert(queue[i]);
	return result;
}

/*
 * |prefix_01| > |prefix_02|
 * prefix_01 not contain "s"
 * --> prefix_02 not contain "s"
 */
void add_posfix_relation(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	Z3_context ctx = Z3_theory_get_context(t);

	std::set<Z3_ast> all_posfix_nn1 = find_all_posfix_of_node(t, nn1);
	std::set<Z3_ast> all_posfix_nn2 = find_all_posfix_of_node(t, nn2);

	printZ3Node(t, nn1);
	displayListNode(t, all_posfix_nn1, ">> all_posfix_nn1 ");
	printZ3Node(t, nn2);
	displayListNode(t, all_posfix_nn2, ">> all_posfix_nn2 ");

	for (const auto& posfix01 : all_posfix_nn1){
		for (const auto& containNode : containPairBoolMap){
			if (containNode.first.first == posfix01 &&
					(isConstStr(t, containNode.first.second) || isDetAutomatonFunc(t, containNode.first.second))) {

				std::string tmpStr00 = getConstString(t, containNode.first.second);
				Z3_ast len_posfix01 = mk_length(t, posfix01);
				for (const auto& posfix02 : all_posfix_nn2){
					for (const auto& containNode02 : containPairBoolMap){
						if (containNode02.first.first == posfix02 && (isConstStr(t, containNode02.first.second) || isDetAutomatonFunc(t, containNode02.first.second))) {
							Z3_ast len_posfix02 = mk_length(t, posfix02);
							assert(isDetAutomatonFunc(t, containNode02.first.second));
							assert(isDetAutomatonFunc(t, containNode.first.second));


							std::string tmpStr01 = getConstString(t, containNode02.first.second);

							if (tmpStr01.find(tmpStr00) != std::string::npos) {
								/* a does not contains "x"; b contains "yx", |a| >= |b| --> false */
								std::vector<Z3_ast> andElements;
								andElements.emplace_back(Z3_mk_ge(ctx, len_posfix01, len_posfix02));
								andElements.emplace_back(Z3_mk_not(ctx, containNode.second));
								andElements.emplace_back(containNode02.second);
								addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andElements), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
							}

							if (tmpStr00.find(tmpStr01) != std::string::npos){
								/* a does not contains "x"; b contains "yx", |a| >= |b| --> false */
								std::vector<Z3_ast> andElements;
								andElements.emplace_back(Z3_mk_ge(ctx, len_posfix02, len_posfix01));
								andElements.emplace_back(Z3_mk_not(ctx, containNode02.second));
								andElements.emplace_back(containNode.second);
								addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andElements), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
							}
						}
					}
				}
			}
		}
	}

	/* a does not contains "x"; b = c. "yx" . d, |a| >= |b| --> false */
	for (const auto& posfix01 : all_posfix_nn1){
			for (const auto& containNode : containPairBoolMap){
				if (containNode.first.first == posfix01 &&
						(isConstStr(t, containNode.first.second) || isDetAutomatonFunc(t, containNode.first.second))) {

					std::string tmpStr00 = getConstString(t, containNode.first.second);
					Z3_ast len_posfix01 = mk_length(t, posfix01);
					for (const auto& posfix02 : all_posfix_nn2){
						if (isConcatFunc(t, posfix02)){
							Z3_ast len_posfix02 = mk_length(t, posfix02);
							std::vector<Z3_ast> v;
							getNodesInConcat(t, posfix02, v);
							/* a does not contains "x"; b = c. "yx" . d, |a| >= |b| --> false */
							for (const auto& n : v)
								if (isConstStr(t, n) || isDetAutomatonFunc(t, n)){
									std::string str = getConstString(t, n);
									if (str.find(tmpStr00) != std::string::npos) {
										std::vector<Z3_ast> andElements;
										andElements.emplace_back(Z3_mk_ge(ctx, len_posfix01, len_posfix02));
										andElements.emplace_back(Z3_mk_not(ctx, containNode.second));
										addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andElements), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
										break;
									}
								}
						}
					}
				}
			}
	}

	/* a does not contains "x"; b = c. "yx" . d, |a| >= |b| --> false */
	for (const auto& posfix01 : all_posfix_nn2){
		for (const auto& containNode : containPairBoolMap){
			if (containNode.first.first == posfix01 &&
					(isConstStr(t, containNode.first.second) || isDetAutomatonFunc(t, containNode.first.second))) {

				std::string tmpStr00 = getConstString(t, containNode.first.second);
				Z3_ast len_posfix01 = mk_length(t, posfix01);
				for (const auto& posfix02 : all_posfix_nn1){
					if (isConcatFunc(t, posfix02)){
						Z3_ast len_posfix02 = mk_length(t, posfix02);
						std::vector<Z3_ast> v;
						getNodesInConcat(t, posfix02, v);
						/* a does not contains "x"; b = c. "yx" . d, |a| >= |b| --> false */
						for (const auto& n : v)
							if (isConstStr(t, n) || isDetAutomatonFunc(t, n)){
								std::string str = getConstString(t, n);
								if (str.find(tmpStr00) != std::string::npos) {
									std::vector<Z3_ast> andElements;
									andElements.emplace_back(Z3_mk_ge(ctx, len_posfix01, len_posfix02));
									andElements.emplace_back(Z3_mk_not(ctx, containNode.second));
									addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andElements), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
									break;
								}
							}
					}
				}
			}
		}
	}
}

/*
 * |posfix_01| > |posfix_02|
 * posfix_01 not contain "s"
 * --> posfix_02 not contain "s"
 */
void add_prefix_relation(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	Z3_context ctx = Z3_theory_get_context(t);

	std::set<Z3_ast> all_prefix_nn1 = find_all_prefix_of_node(t, nn1);
	std::set<Z3_ast> all_prefix_nn2 = find_all_prefix_of_node(t, nn2);

	printZ3Node(t, nn1);
	displayListNode(t, all_prefix_nn1, ">> all_prefix_nn1 ");
	printZ3Node(t, nn2);
	displayListNode(t, all_prefix_nn2, ">> all_prefix_nn2 ");

	for (const auto& prefix01 : all_prefix_nn1){
		for (const auto& containNode : containPairBoolMap){
			if (containNode.first.first == prefix01 && (isConstStr(t, containNode.first.second) || isDetAutomatonFunc(t, containNode.first.second))) {
				Z3_ast len_prefix01 = mk_length(t, prefix01);
				for (const auto& prefix02 : all_prefix_nn2){
					for (const auto& containNode02 : containPairBoolMap){
						if (containNode02.first.first == prefix02 && (isConstStr(t, containNode02.first.second) || isDetAutomatonFunc(t, containNode02.first.second))) {
							Z3_ast len_prefix02 = mk_length(t, prefix02);
							assert(isDetAutomatonFunc(t, containNode02.first.second));
							assert(isDetAutomatonFunc(t, containNode.first.second));

							std::string tmpStr00 = getConstString(t, containNode.first.second);
							std::string tmpStr01 = getConstString(t, containNode02.first.second);

							if (tmpStr01.find(tmpStr00) != std::string::npos) {
								/* a does not contains "x"; b contains "yx", |a| >= |b| --> false */
								std::vector<Z3_ast> andElements;
								andElements.emplace_back(Z3_mk_ge(ctx, len_prefix01, len_prefix02));
								andElements.emplace_back(Z3_mk_not(ctx, containNode.second));
								andElements.emplace_back(containNode02.second);
								addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andElements), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
							}

							if (tmpStr00.find(tmpStr01) != std::string::npos){
								/* a does not contains "x"; b contains "yx", |a| >= |b| --> false */
								std::vector<Z3_ast> andElements;
								andElements.emplace_back(Z3_mk_ge(ctx, len_prefix02, len_prefix01));
								andElements.emplace_back(Z3_mk_not(ctx, containNode02.second));
								andElements.emplace_back(containNode.second);
								addAxiom(t, Z3_mk_implies(ctx, mk_and_fromVector(t, andElements), Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))), __LINE__, true);
							}
						}
					}
				}
			}
		}
	}
}

/*
 * check satisfiable of 'nn1 = nn2'
 */
bool checkEqualConsistency(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n** %d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, " = ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);

	std::vector<Z3_ast> eq01;
	std::vector<Z3_ast> eq01_parent;
	std::vector<Z3_ast> eq02;
	std::vector<Z3_ast> eq02_parent;

	collect_from_new_eq(t, nn1, nn2, eq01, eq01_parent, eq02, eq02_parent);

	std::set<Z3_ast> eqList;
	std::string str_nn1 = Z3_ast_to_string(ctx, nn1);
	std::string str_nn2 = Z3_ast_to_string(ctx, nn2);
	if (str_nn1.find("$$") != 0 && str_nn2.find("$$") != 0) {
		if (!crossCheck_Update(t, eq01, eq02, nn1, nn2)) {
			// UNSAT
			return false;
		}
	}

	updateEqualMap(t, nn1, nn2);

	// select node to propagate
	if (str_nn1.find("~") == std::string::npos &&
			str_nn1.find("*") == std::string::npos)
	{
		if (!propagate(t, nn1)) {
			return false;
		}
	}
	else
	{
		if (!propagate(t, nn2)) {
			return false;
		}
	}
	__debugPrint(logFile, "%d %s: back\n", __LINE__, __FUNCTION__);
	return true;
}

/*
 *
 */
bool propagate(Z3_theory t, Z3_ast node){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n** %d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);

	// collect all parents
	std::set<Z3_ast> parents = collectAllParents(t, node);
	std::vector<Z3_ast> parents_filtered;
	for (const auto& n : parents)
		if (!isLengthFunc(t, n)){
			std::vector<Z3_ast> listNodes;
			if (isConcatFunc(t, node)) {
				collect_node_in_concat(t, node, listNodes);

				for (const auto& _node : listNodes) {
					std::vector<Z3_ast> eq_node = collect_eqc(t, _node);
					for (const auto& __node : eq_node)
						if (__node == n)
							return true;
				}
			}
			bool add = true;
			for (unsigned int i = 0 ; i < parents_filtered.size(); ++i) {
				std::vector<Z3_ast> eq_parent = getEqualValues(parents_filtered[i]);
				if (std::find(eq_parent.begin(), eq_parent.end(), n) != eq_parent.end()) {
					add = false;
					break;
				}
			}
			if (add == true)
				parents_filtered.emplace_back(n);
		}

#ifdef DEBUGLOG
	displayListNode(t, parents_filtered, " parents_filtered ");
#endif

	// for all parents nodes
	for (const auto& n : parents_filtered) {
		if (isConcatFunc(t, n)) {
			bool success;
			Automaton tonton = updateNode(t, n, success);
			if (!success) {
#ifdef DEBUGLOG
				__debugPrint(logFile, "\n\n>> @%d at __%s: Update failed: ", __LINE__, __FILE__);
				printZ3Node(t, n);
				__debugPrint(logFile, "\n\n");
#endif
				return false;
			}

			/* do not need to check anymore */
			if (tonton.isUnknown())
				continue;

			std::vector<Z3_ast> it_eqValues = getEqualValues(n);
			if (crossCheck(t, it_eqValues, n)){
				if (!tonton.isUnknown()) {
					bool ret = propagate(t, n);
					if (ret == false)
						return false;
				}
			}
			else {
#ifdef DEBUGLOG
				__debugPrint(logFile, "@%d UNSAT: ", __LINE__);
				printZ3Node(t, n);
				__debugPrint(logFile, "\n");
#endif
				__debugPrint(logFile, "%d negating eq: ", __LINE__);
				printZ3Node(t, n);
				printZ3Node(t, it_eqValues[0]);
				__debugPrint(logFile, "\n");
				addAxiom(t, Z3_mk_not(ctx, Z3_mk_eq(ctx, it_eqValues[0], n)), __LINE__, true);
				return false;
			}
		}
	}
	__debugPrint(logFile, "%d %s : back\n", __LINE__, __FUNCTION__);
	return true;
}

/*
 *
 */
void updateEqualMap(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n>> @%d *** %s ***\n", __LINE__, __FUNCTION__);
#endif

	std::vector<Z3_ast> leftEq = getEqualValues(nn1);
	std::vector<Z3_ast> rightEq = getEqualValues(nn2);

	Z3_context c = Z3_theory_get_context(t);
	std::string name01 = Z3_ast_to_string(c, nn1);
	if (name01.find("~") != std::string::npos || name01.find("*") != std::string::npos) {
		leftEq.clear();
		leftEq.emplace_back(nn1);
	}

	std::string name02 = Z3_ast_to_string(c, nn2);
	if (name02.find("~") != std::string::npos || name02.find("*") != std::string::npos) {
		rightEq.clear();
		rightEq.emplace_back(nn2);
	}

	// combine
	for (unsigned int j = 0; j < leftEq.size(); ++j) {
		if (std::find(rightEq.begin(), rightEq.end(), leftEq[j]) == rightEq.end())
			rightEq.emplace_back(leftEq[j]);
	}

//	displayListNode(t, rightEq);

	for (unsigned int i = 0; i < rightEq.size(); ++i) {
		equalMap[std::make_pair(rightEq[i], sLevel)] = rightEq;
	}
}

bool checkSingleAutomaton(Automaton ton){
	if (ton.isUnknown())
		return true;
	else if (ton.isError())
		return false;
	return true;
}


Automaton updateNode(Z3_theory t, Z3_ast node, bool &success) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n\n>>%d *** %s *** @%d ", __LINE__, __FUNCTION__, sLevel);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif
	success = false;
	Automaton oldVal = getPreCalculatedValue(t, node);
	if (oldVal.isUnknown())
		success = true;

	if (isVariable(t, node)) {
		Automaton ton = evalVariable(t, node, false);

		if (!oldVal.isUnknown())
			ton = ton.Intersect(ton.name, oldVal);
		if (ton.isUnknown() || ton.isError()) {
			success = success || false;
			return Automaton(UNKNOWN_AUTOMATON);
		}

		updateInternalVarMap(node, ton);
		updateInternalVarMap_independence(node, ton);
		success = true;
		return ton;
	}

	else if (isConstStr(t, node)){
		std::string str = getConstStrValue(t, node);
		str = customizeString(str);
		RegEx re;

		re.Compile(str);
		Automaton ton = re.CreateAutomaton("known");
		success = true;
		return ton;
	}

	else {
		Z3_context ctx = Z3_theory_get_context(t);
		Z3_app func_app = Z3_to_app(ctx, node);

		if (isAutomatonFunc(t, node)) {
#ifdef DEBUGLOG
			__debugPrint(logFile, "\n\n>> @%d at __%s: Eval AutomataDef \n", __LINE__, __FILE__);
#endif
			Z3_ast arg = Z3_get_app_arg(ctx, func_app, 0);
			Automaton ton = evalAutomataDef(t, arg);
			updateInternalVarMap(node, ton);
			updateInternalVarMap_independence(node, ton);
			success = true;
			return ton;
		}

		else if (isConcatFunc(t, node)) {
			Z3_ast arg00 = Z3_get_app_arg(ctx, func_app, 0);
			Z3_ast arg01 = Z3_get_app_arg(ctx, func_app, 1);
			Automaton ton = evalConcat(t, arg00, arg01, false);
#ifdef DEBUGLOG
			printZ3Node(t, node);
			if (ton.isUnknown()) {
				__debugPrint(logFile, "\n>> @%d at __%s: updated Concat value\n %s\n", __LINE__, __FILE__, UNKNOWN_AUTOMATON);
			}
			else
				__debugPrint(logFile, "\n>> @%d at __%s: updated Concat value\n %s\n", __LINE__, __FILE__, ton.toString().c_str());
#endif

			if (!oldVal.isUnknown()) {
				if (!ton.isUnknown()) {

				}
				else {
					success = true;
					updateInternalVarMap(node, ton);
					updateInternalVarMap_independence(node, ton);
					return oldVal;
				}
			}

			if (ton.isUnknown() || ton.isError()) {
				success = success || false;
				return Automaton(UNKNOWN_AUTOMATON);
			}
			success = true;
			updateInternalVarMap(node, ton);
			updateInternalVarMap_independence(node, ton);
			return ton;
		}
		else {
#ifdef DEBUGLOG
			__debugPrint(logFile, "\n\n>> @%d at __%s: Eval UNKNOWN \n", __LINE__, __FILE__);
#endif
			success = true;
			Automaton ton(UNKNOWN_AUTOMATON);
			return ton;
		}
	}

}


void updateForAllEqualNodes(Z3_ast node, Automaton value){
	std::vector<Z3_ast> equal = getEqualValues(node);
	updateInternalVarMap(equal, value);
}

Automaton evalNode(Z3_theory t, Z3_ast node, bool isIndependence) {
	Automaton ret;
	if (!isIndependence) {
		ret = getPreCalculatedValue(t, node);
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n %d ", __LINE__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif

	if (ret.isUnknown()) {
		if (isVariable(t, node)) {
			Automaton ton = evalVariable(t, node, false);

#ifdef DEBUGLOG
//			__debugPrint(logFile, "\n>> @%d Value of variable: @%d: %s \n", __LINE__, sLevel, ton.name.c_str());
#endif
			if (ton.isUnknown())
				return ton;

			if (ton.isError()) {
				//				ret.name = UNKNOWN_AUTOMATON;
				return ton;
			}

			updateInternalVarMap(node, ton);
			updateInternalVarMap_independence(node, ton);
			return ton;
		}
		else {
			Z3_context ctx = Z3_theory_get_context(t);
			Z3_app func_app = Z3_to_app(ctx, node);

			if (isAutomatonFunc(t, node)) {
				Z3_ast arg = Z3_get_app_arg(ctx, func_app, 0);

				Automaton ton = evalAutomataDef(t, arg);
				updateInternalVarMap(node, ton);
				updateInternalVarMap_independence(node, ton);

				return ton;
			}
			else if (isConcatFunc(t, node)) {
				Z3_ast arg00 = Z3_get_app_arg(ctx, func_app, 0);
				Z3_ast arg01 = Z3_get_app_arg(ctx, func_app, 1);
				Automaton ton = evalConcat(t, arg00, arg01, false);

				if (ton.isUnknown())
					return ton;
				updateInternalVarMap(node, ton);
				updateInternalVarMap_independence(node, ton);
				return ton;
			}
			else {
#ifdef DEBUGLOG
//				__debugPrint(logFile, "\n\n>> @%d at __%s: Eval UNKNOWN \n", __LINE__, __FILE__);
#endif
				Automaton ton(UNKNOWN_AUTOMATON);
				return ton;
			}
		}
	}
	else {
#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n\n>> @%d at __%s:known node value %s\n", __LINE__, __FILE__, ret.toString().c_str());
#endif
		//		ret.name = UNKNOWN_AUTOMATON;
		return ret;
	}

}

//Automaton evalNode_Lazy(Z3_theory t, Z3_ast node, bool isIndependence) {
//	Automaton ret;
//	if (isIndependence) {
//		ret = getPreCalculatedValue_independence(t, node);
//	}
//	else {
//		ret = getPreCalculatedValue(t, node);
//	}
//
//#ifdef DEBUGLOG
//	__debugPrint(logFile, "\n\n>> @%d at __%s: Eval Node Lazy: @%d ", __LINE__, __FILE__, sLevel);
//	printZ3Node(t, node);
//	__debugPrint(logFile, "\n");
//#endif
//
//	if (ret.isUnknown()) {
//#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n\n>> @%d at __%s: Eval UNKNOWN \n", __LINE__, __FILE__);
//#endif
//		Automaton ton(UNKNOWN_AUTOMATON);
//		return ton;
//	}
//	else {
//#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n\n>> @%d at __%s:known node value %s\n", __LINE__, __FILE__, ret.toString().c_str());
//#endif
//		return ret;
//	}
//}

/*
 *
 */
Automaton evalAutomataDef(Z3_theory t, Z3_ast arg) {
	Z3_context ctx = Z3_theory_get_context(t);
	std::string regex = std::string(Z3_ast_to_string(ctx, arg));
	regex = customizeString(regex);
	if (regex.size() > 0) {
		RegEx re;
		re.Compile(regex);
		Automaton ton = re.CreateAutomaton("known");
		return ton;
	}
	else {
		std::vector<int> acceptStates;
		std::vector<int> states;
		std::vector<int> labels;
		std::vector<int> initStates; initStates.emplace_back(0);
		std::vector<Transition> transitions;
		acceptStates.emplace_back(0);
		states.emplace_back(0);
		__debugPrint(logFile, "%d empty string %s\n", __LINE__, regex.c_str());
		Automaton ton("known", states, transitions, labels, initStates, acceptStates);
		return ton;
	}
}


/*
 *
 */
Automaton evalConcat(Z3_theory t, Z3_ast arg00, Z3_ast arg01, bool isIndependence) {

#ifdef DEBUGLOG
//	__debugPrint(logFile, "\n>> @%d Eval Concat: ", __LINE__);
//	printZ3Node(t, arg00);
//	__debugPrint(logFile, " *concat* ");
//	printZ3Node(t, arg01);
//	__debugPrint(logFile, "\n");
#endif
	std::string known = "known";
	Automaton ret(known);

	Automaton ton00 = evalNode(t, arg00, isIndependence);
	if (ton00.isUnknown())
		return ton00;
	if (ton00.isError()) {
		return ret;
	}

	Automaton ton01 = evalNode(t, arg01, isIndependence);
	if (ton01.isUnknown())
		return ton01;
	if (ton01.isError())
		return ret;

#ifdef DEBUGLOG
//	__debugPrint(logFile, "\n>> @%d at __%s: Finish Concat\n", __LINE__, __FILE__);
#endif

	return ton00.Concat(known, ton01);
}

/*
 *
 */
Automaton evalVariable(Z3_theory t, Z3_ast node, bool isIndependence){
	assert(isVariable(t, node));
	if (checkCylicity(t, node) == true)
		return Automaton(UNKNOWN_AUTOMATON);
	return evalIntersection(t, getEqualValues(node), isIndependence);
}

/*
 *
 */
void sortingElements(std::vector<Automaton> &list) {
	for (unsigned int i = 0; i < list.size(); ++i) {
		unsigned int minPos = i;
		unsigned int minVal = list[i].transitions.size();
		for (unsigned int j = i + 1; j < list.size(); ++j) {
			if (minVal > list[j].transitions.size()) {
				minPos = j;
				minVal = list[j].transitions.size();
			}
		}

		Automaton t = list[i];
		list[i] = list[minPos];
		list[minPos] = t;
	}
}

bool checkCylicity(Z3_theory t, Z3_ast node){
	Z3_context ctx = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, Z3_ast_to_string(ctx, node));
	std::vector<Z3_ast> eq_n = collect_eqc(t, node);
	unsigned pos = 0;
	std::map<Z3_ast, int> repeated;
	std::vector<Z3_ast> queue;
	queue.emplace_back(node);
	repeated[node] = 1;
	while (pos < queue.size()) {
		std::vector<Z3_ast> eq_n = collect_eqc(t, queue[pos]);
		pos++;
		for (const auto& n : eq_n)
			if (isConcatFunc(t, n)) {
				std::vector<Z3_ast> list;
				collect_node_in_concat(t, n, list);
				for (const auto& __n: list) {
					__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, Z3_ast_to_string(ctx, __n));
					if (repeated[__n] == 1)
						return true;
					__debugPrint(logFile, "%d %s: passed\n", __LINE__, __FUNCTION__);
					queue.emplace_back(__n);
					repeated[__n] = 1;
				}
			}
	}
	return false;
}

Automaton evalIntersection(Z3_theory t, std::vector<Z3_ast> list, bool isIndependence) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n>> @%d Eval Intersection size = %d\n", __LINE__, (int)list.size());
#endif

	Z3_context ctx = Z3_theory_get_context(t);
	Automaton ret(UNKNOWN_AUTOMATON);

	if (list.size() == 0) {
		return ret;
	}

	/* step 1: collect all elements to be evaluated */
	std::vector<Z3_ast> elements_filtered;
	for (std::vector<Z3_ast>::iterator it = list.begin(); it != list.end(); ++it) {
		if (isStrVariable(t, *it)) {
			// skip
		}
		else if (isConcatFunc(t, *it)) {
			// prevent duplicate concat: e.g. concat (a, b) and concat(a, c) where b == c
			Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, *it), 0);
			Z3_ast arg11 = Z3_get_app_arg(ctx, Z3_to_app(ctx, *it), 1);


			bool add = true;
			for (unsigned int i = 0; i < elements_filtered.size(); ++i)
				if (isConcatFunc(t, elements_filtered[i])) {
					Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, elements_filtered[i]), 0);
					Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, elements_filtered[i]), 1);

					std::vector<Z3_ast> eq_Arg0 = collect_eqc(t, arg0);
					std::vector<Z3_ast> eq_Arg1 = collect_eqc(t, arg1);
					if ((std::find(eq_Arg0.begin(), eq_Arg0.end(), arg00) != eq_Arg0.end() &&
							std::find(eq_Arg1.begin(), eq_Arg1.end(), arg11) != eq_Arg1.end())) { // the same concat
						add = false;
						break;
					}
				}

			if (add == true)
				elements_filtered.emplace_back(*it);
		}
		else {
			elements_filtered.emplace_back(*it);
		}
	}

#ifdef DEBUGLOG
	__debugPrint(logFile, ">> @%d at Number of elements: %ld \n", __LINE__, elements_filtered.size());
#endif

//	/* skip the case y vs x y x*/
//	for (unsigned i = 0; i < elements_filtered.size(); ++i)
//		if (isStrVariable(t, elements_filtered[i])) {
//			std::vector<Z3_ast> eq_n = collect_eqc(t, elements_filtered[i]);
//
//			for (unsigned j = i + 1; j < elements_filtered.size(); ++j)
//				if (isConcatFunc(t, elements_filtered[j])) {
//					std::vector<Z3_ast> list;
//					collect_node_in_concat(t, elements_filtered[j], list);
//					for (const auto& _n : eq_n)
//						for (const auto& __n: list)
//							if (_n == __n)
//								return ret;
//				}
//		}

	/* evaluate all elements */
	std::vector<Automaton> elements;
	for (unsigned int i = 0; i < elements_filtered.size(); ++i) {
		Automaton ton = evalNode(t, elements_filtered[i], isIndependence);
		if (ton.isError() && !ton.isUnknown())
			return ton;
		else if (!ton.isUnknown()) {
			elements.emplace_back(ton);
		}
	}

	if (elements.size() == 0) {
#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n>> @%d at __%s: UNKNOWN (%ld elements)\n", __LINE__, __FILE__, elements_filtered.size());
#endif
		return ret;
	}
	else {
#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n\n>> @%d at __%s:Update interstion list = %d --> ", __LINE__, __FILE__, (int)elements.size());
#endif
		elements = removeEqualAutomata(elements);
		elements = removeGenericAutomata(elements);
#ifdef DEBUGLOG
//		__debugPrint(logFile, " %d\n", (int)elements.size());
#endif
		std::string known = "known";

		// sorting elements
		//		sortingElements(elements);

		// intersect with concats
		Automaton tonton = elements[0];
#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n\n>> @%d  Element %d: \n %s", __LINE__, 0, elements[0].toString(false).c_str());
#endif

		for (unsigned int i = 1; i < elements.size(); ++i) {
#ifdef DEBUGLOG
//			__debugPrint(logFile, "\n\n>> @%d  Element %d: \n %s", __LINE__, i, elements[i].toString(false).c_str());
#endif
			tonton = tonton.Intersect(known, elements[i]);
			if (tonton.isError())
				return tonton;
		}
		tonton.name = known;
#ifdef DEBUGLOG
//		__debugPrint(logFile, "\n\n>> @%d at __%s: Result intersection: %s ", __LINE__, __FILE__, tonton.toString(false).c_str());
#endif
		return tonton;

	}
	return ret;
}

/*
 *
 */
std::vector<Automaton> removeEqualAutomata(std::vector<Automaton> list) {
	std::vector<Automaton> ret;
	// remove all equal ones
	for (unsigned int i = 0; i < list.size(); ++i) {
		bool add = true;
		for (unsigned int j = i + 1; j < list.size(); ++j) {
			if (list[i].isEqual(list[j])) {
				add = false;
				break;
			}
		}
		if (add == true)
			ret.emplace_back(list[i]);
	}
	return ret;
}

/*
 *
 */
std::vector<Automaton> removeGenericAutomata(std::vector<Automaton> list) {
	std::vector<Automaton> ret;
	for (unsigned int i = 0; i < list.size(); ++i) {
		if (list[i].isGeneric == false)
			ret.emplace_back(list[i]);
	}

	if (ret.size() == 0 && list.size() > 0) {
		ret.emplace_back(list[0]);
	}
	return ret;
}

/*
 *
 */
bool isCheckedNode(Z3_theory t, Z3_ast node, std::vector<Z3_ast> checkedNode){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string name = Z3_ast_to_string(ctx, node);
	for (unsigned int i = 0; i < checkedNode.size(); ++i) {
		std::string s = Z3_ast_to_string(ctx, checkedNode[i]);
		if (s.compare(name) == 0)
			return true;
	}
	return false;
}

/*
 *
 */
bool crossCheck_Update(Z3_theory t, std::vector<Z3_ast> v1, std::vector<Z3_ast> v2, Z3_ast nn1, Z3_ast nn2) {
	Z3_context ctx = Z3_theory_get_context(t);

	// checker if one of nodes is a generic automaton
	bool genericNode = false;
	std::string genericString;
	if (isStrVariable(t, nn1))
		genericString = createGenericLanguage(t, nn1);
	else if (isStrVariable(t, nn2))
		genericString = createGenericLanguage(t, nn2);
	else if (isConcatFunc(t, nn1))
		genericString = createGenericLanguage(t, nn1);
	else
		genericString =  createGenericLanguage(t, nn2);

	std::string tmpStr = std::string(Z3_ast_to_string(ctx, nn1)) + std::string(Z3_ast_to_string(ctx, nn2));
	if (tmpStr.find(genericString) != std::string::npos)
		genericNode = true;

	v1.insert(v1.end(), v2.begin(), v2.end());

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n** @%d Cross Check and Update: ", __LINE__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, " == ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, "\n");
#endif

	Automaton tonton = evalIntersection(t, v1, false);
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at After all: \n", __LINE__);
	if (!tonton.isUnknown()) {
		__debugPrint(logFile, "%s\n", tonton.toString().c_str());
	}
	else {
		__debugPrint(logFile, "uNkNoWn\n");
	}
#endif

	if (tonton.isUnknown())
		return true;
	if (tonton.isError())
		return false;

	if (genericNode == true) {
		tonton.isGeneric = true;
	}

	updateInternalVarMap(v1, tonton);
	updateInternalVarMap_independence(v1, tonton);

	return true;
}

/*
 *
 */
bool crossCheck(Z3_theory t, std::vector<Z3_ast> v1, Z3_ast node) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at %s Cross Check: ", __LINE__, __FILE__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif

	std::vector<Z3_ast> checkedNode;

	Automaton value = evalIntersection(t, v1, true);
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at __%s: After all: \n", __LINE__, __FILE__);
	if (!value.isUnknown()) {
		__debugPrint(logFile, "%s\n", value.toString().c_str());
	}
	else {
		__debugPrint(logFile, "uNkNoWn\n");
	}
#endif

	if (value.isUnknown())
		return true;
	if (value.isError())
		return false;

	updateInternalVarMap(v1, value);
	return true;
}

/*
 *
 */
void updateInternalVarMap(std::vector<Z3_ast> list, Automaton value) {
	for (unsigned int i = 0; i < list.size(); ++i)
		internalVarMap[std::make_pair(list[i], sLevel)] = value;
}

/*
 *
 */
void updateInternalVarMap(Z3_ast node, Automaton value) {
	internalVarMap[std::make_pair(node, sLevel)] = value;
}

/*
 *
 */
void updateInternalVarMap_independence(std::vector<Z3_ast> list, Automaton value) {
	for (unsigned int i = 0; i < list.size(); ++i)
		internalVarMap_withoutCombination[std::make_pair(list[i], sLevel)] = value;
}
/*
 *
 */
void updateInternalVarMap_independence(Z3_ast node, Automaton value) {
	internalVarMap_withoutCombination[std::make_pair(node, sLevel)] = value;
}
/*
 *
 */
Automaton getPreCalculatedValue(Z3_theory t, Z3_ast node) {
	for (int i = sLevel; i >= 0; --i) {
		Automaton ton = internalVarMap[std::make_pair(node, i)];
		if (!ton.isUnknown()) {
			return ton;
		}
	}

	return internalVarMap[std::make_pair(node, sLevel)];
}

/*
 *
 */
Automaton getPreCalculatedValue_independence(Z3_theory t, Z3_ast node) {
	for (int i = sLevel; i >= 0; --i) {
		Automaton ton = internalVarMap_withoutCombination[std::make_pair(node, i)];
		if (!ton.isUnknown()) {
			return ton;
		}
	}

	return internalVarMap_withoutCombination[std::make_pair(node, sLevel)];
}

/*
 *
 */
std::vector<Z3_ast> getEqualValues(Z3_ast node) {
	std::vector<Z3_ast> ret;

	for (int i = sLevel; i >= 0; --i) {
		std::vector<Z3_ast> tmp = equalMap[std::make_pair(node, i)];
		if (tmp.size() > 0)
			return tmp;
	}

	ret.emplace_back(node);
	return ret;
}

/*
 * Because of no constraints over variable, only need one char to create the language
 */
Z3_ast handleAutomaton_VarKnownLength_lazy(Z3_theory t, int len, Z3_ast node){
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at %s: handleAutomaton_VarKnownLength_lazy: ", __LINE__, __FILE__);
	__debugPrint(logFile, " ----- ");
	printZ3Node(t, node);
	__debugPrint(logFile, " \n\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	int nnLen = getLenValue(t, node);

	assert(nnLen >= 0);

	std::string prefix_var = "$$" + std::string(Z3_ast_to_string(ctx, node)) + "_" + std::to_string(sLevel) + "!!";
	std::string s = prefix_var + createStringWithLength_lazy(t, node, nnLen, charSet);
	Z3_ast result = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, s.c_str()));

	return Z3_mk_eq(ctx, node, result);
}

/*
 *
 */
Z3_ast handleAutomaton_VarKnownLength(Z3_theory t, int len, Z3_ast node){
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at %s: handleAutomaton_VarKnownLength: ", __LINE__, __FILE__);
	__debugPrint(logFile, " ----- ");
	printZ3Node(t, node);
	__debugPrint(logFile, " \n\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	int nnLen = getLenValue(t, node);

	assert(nnLen >= 0);

	std::string prefix_var = "$$" + std::string(Z3_ast_to_string(ctx, node)) + "_" + std::to_string(sLevel) + "!!";
	std::string s = prefix_var + createStringWithLength(t, node, nnLen, charSet);
	Z3_ast result = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, s.c_str()));

	return Z3_mk_eq(ctx, node, result);
}

void handleAutomaton_Automaton(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
#ifdef DEBUGLOG
	__debugPrint(logFile, "%d at %s: handleAutomaton_Automaton: ", __LINE__, __FILE__);
	printZ3Node(t, nn1);
	__debugPrint(logFile, " ----- ");
	printZ3Node(t, nn2);
	__debugPrint(logFile, " \n\n");
#endif

	Z3_context ctx = Z3_theory_get_context(t);

	std::string regexStr01 = std::string(Z3_ast_to_string(ctx, nn1));
	std::string regexStr02 = std::string(Z3_ast_to_string(ctx, nn2));

	regexStr01 = customizeString(regexStr01);
	regexStr02 = customizeString(regexStr02);

	__debugPrint(logFile, "Check two regexs %s vs %s\n", regexStr01.c_str(), regexStr02.c_str());

	RegEx re;
	re.Compile(regexStr01);
	Automaton automaton01 = re.CreateAutomaton(Z3_ast_to_string(ctx, nn1));
	re.Compile(regexStr02);
	Automaton automaton02 = re.CreateAutomaton(Z3_ast_to_string(ctx, nn2));

	Automaton newOne = automaton01.Intersect(automaton02);
	__debugPrint(logFile, "%d at %s: resulted automaton\n%s\n", __LINE__, __FILE__, newOne.toString().c_str());

	if (newOne.isError()){
		__debugPrint(logFile, "%d at %s: size of new automaton: %d\n", __LINE__, __FILE__, (int)newOne.acceptStates.size());
		// UNSAT
		addAxiom(t, Z3_mk_eq(ctx, mk_int(ctx, 0), mk_int(ctx, 1)), __LINE__, true);
	}
	__debugPrint(logFile, "%d at %s: pass automaton = automaton: %d\n", __LINE__, __FILE__, (int)newOne.acceptStates.size());
	//TODO automaton = automaton
}

/*
 * Handle Var - automata
 */
Z3_ast extendEqualVar_Automata(Z3_theory t, Z3_ast n1, Z3_ast n2) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "** extendEqualVar_Automata(): @%d\n", sLevel);
	printZ3Node(t, n1);
	__debugPrint(logFile, "  = ");
	printZ3Node(t, n2);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	Automaton ton = getPreCalculatedValue(t, n2);
	if (!ton.isUnknown()) {
		if (!ton.isConst()) {
			std::vector<Z3_ast> values = createValueAxiom(t, n1);

			if (values.size() == 0) {
				values.emplace_back(negatedConstraint(t));
			}

			assert(values.size() > 0);
			return Z3_mk_eq(ctx, Z3_mk_eq(ctx, n1, n2), mk_and_fromVector(t, values));
		}
		else {
			// update final value
			__debugPrint(logFile, "@%d Update value: %s", __LINE__, ton.toString().c_str());
			printZ3Node(t, n2);
			__debugPrint(logFile, "\n");
		}
	}
	return NULL;
}

/*
 * Handle Vars - automata
 */
Z3_ast extendEqualVars_Automata(Z3_theory t, std::vector<std::pair<Z3_ast, int>> langVal) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "** extendEqualVars_Automata(): @%d %d\n", sLevel, (int)langVal.size());
	for (unsigned int i = 0; i < langVal.size(); ++i) {
		printZ3Node(t, langVal[i].first);
		__debugPrint(logFile, " = %d ", langVal[i].second);
		printZ3Node(t, language_Map[langVal[i].first][langVal[i].second - 1]);
		__debugPrint(logFile, "\n");
	}
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> ret;

	for (unsigned int i = 0; i < langVal.size(); ++i) {
		Z3_ast tmp = extendEqualVar_Automata(t, langVal[i].first, language_Map[langVal[i].first][langVal[i].second - 1]);
		if (tmp == NULL)
			return NULL;
		ret.emplace_back(tmp);
	}

	return mk_and_fromVector(t, ret);
	std::vector<Z3_ast> langSet = collectLanguageValue(t);
	assert(langSet.size() > 0);
	assert(ret.size() > 0);
	return Z3_mk_implies(ctx, mk_and_fromVector(t, langSet), mk_and_fromVector(t, ret));
}

/*
 *
 */
std::string customizeString(std::string s) {
	if (s[0] == '|') s = s.substr(1, s.length() - 2);
	if (s[0] == '"') s = s.substr(1, s.length() - 2);
	const size_t pos = s.find("!!");
	if (s.compare("!!") != 0 && s.find("$$") < 2)
		if (pos != std::string::npos)
			s = s.substr(pos + 2);

	for (unsigned int i = 0; i < s.size(); ++i)
		if (s[i] == '~')
			s[i] = '|';
	return s;
}

/**
   \brief Callback: invoked when <tt>n1 = n2</tt> is false in the logical context.

   Z3 will only invoke this callback using expressions \c n1 and \c n2 s.t.
   #Th_new_app or #Th_new_elem was invoked for them.
 */
void Th_new_diseq(Z3_theory t, Z3_ast n1, Z3_ast n2) {
	Z3_context c = Z3_theory_get_context(t);
	__debugPrint(logFile, "New disequality: %s ", Z3_ast_to_string(c, n1));
	__debugPrint(logFile, "!= %s\n", Z3_ast_to_string(c, n2));
	disequalityList.emplace_back(std::make_pair(std::make_pair(n1, n2), sLevel));
}

/**
   \brief Callback: invoked when \c n becomes relevant in the current search branch.
   Irrelevant expressions may be ignored by the theory solver.

   Z3 will only invoke this callback using a expression \c n s.t.
   #Th_new_app or #Th_new_elem was invoked for it.
 */
void Th_new_relevant(Z3_theory t, Z3_ast n) {
	//    Z3_context c = Z3_theory_get_context(t);
	//    __debugPrint(logFile, "Relevant: %s\n", Z3_ast_to_string(c, n));
}

/**
   \brief Callback: invoked when \c n is assigned to true/false.

   Z3 will only invoke this callback using a expression \c n s.t.
   #Th_new_app or #Th_new_elem was invoked for it.
 */
void Th_new_assignment(Z3_theory t, Z3_ast n, Z3_bool v) {
	Z3_context c = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d Assigned: %s --> %d\n", __LINE__, Z3_ast_to_string(c, n), v);
}

/*
 * Compare two vectors of AST
 */
bool isEqualVector(std::vector<Z3_ast> a, std::vector<Z3_ast> b) {

	if (a.size() != b.size())
		return false;
	for (unsigned int i = 0; i < a.size(); ++i) {
		if (a[i] == b[i]) {

		}
		else
			return false;
	}
	return true;
}

/**
 * Collect const in a list
 */
Z3_ast findConstInList(Z3_theory t, std::vector<Z3_ast> list){
	for (unsigned int i = 0 ; i < list.size(); ++i)
		if (isDetAutomatonFunc(t, list[i]))
			return list[i];
	return NULL;
}

/*
 * if
 * 		it is Concat -->
 * 		it is equal to AutomataDef -->
 */
void extendVariableToFindAllPossibleEqualities(
		Z3_theory t,
		Z3_ast node,
		std::set<Z3_ast> connectedVariables,
		std::set<std::string> &non_root,
		std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> &allEqPossibilities,
		std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> &fullEqPossibilities,
		std::map<Z3_ast, int> &levelMap) {
	Z3_context ctx = Z3_theory_get_context(t);

	__debugPrint(logFile, "%d *** %s *** %s\n", __LINE__, Z3_ast_to_string(ctx, node), __FUNCTION__);

	std::vector<std::vector<Z3_ast>> result;
	std::vector<Z3_ast> eqNode = collect_eqc(t, node);
	displayListNode(t, eqNode, " eq  to node");
	std::string nodeName = "";
	Z3_ast orgNode = node;
	for (const auto& n : eqNode) {
		if (isVariable(t, n)){
			std::string tmp = Z3_ast_to_string(ctx, n);
			if (levelMap[node] > 0)
				non_root.emplace(tmp);
			if (nodeName.compare(tmp) < 0){
				node = n;
				nodeName = tmp;
			}
		}
	}

	Z3_ast constNode = findConstInList(t, eqNode);

	if (constNode != NULL) {
		if (allEqPossibilities.find(constNode) != allEqPossibilities.end()) {
			/* const has been evaluated */
			/* --> update: he = const */
			allEqPossibilities[node].push_back({constNode});
			for (const auto& _node : eqNode)
				if (_node != node){
					if (isStrVariable(t, _node) || isAutomatonFunc(t, _node))
						fullEqPossibilities[node].push_back({_node});
					else if (isConcatFunc(t, _node)) {
						std::vector<Z3_ast> nodes;
						collect_node_in_concat(t, _node, nodes);
						fullEqPossibilities[node].push_back(nodes);
					}
				}
			return;
		}
	}

	/* refine eqNode to remove some concat */
	std::vector<Z3_ast> refined_eqNode;
	for (const auto& _node : eqNode)
		if (isConcatFunc(t, _node)) {

			/* check y = x y z*/
			std::vector<Z3_ast> list;
			collect_node_in_concat(t, _node, list);
			for (const auto& __node : list){
				std::vector<Z3_ast> eq_node = collect_eqc(t, __node);
				for (const auto& _n : eq_node) {
					if (_n == node){
						continue;
					}
				}
			}

			Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, _node), 0);
			Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, _node), 1);

			if (std::find(eqNode.begin(), eqNode.end(), arg0) != eqNode.end() ||
					std::find(eqNode.begin(), eqNode.end(), arg1) != eqNode.end())
				/* a = concat a x | a = concat b x && b = a*/
				continue;

			if (isStrVariable(t, arg0))
				/* mark non-root variable --> dont care about him */
				non_root.insert(std::string(Z3_ast_to_string(ctx, arg0)));


			if (isStrVariable(t, arg1))
				/* mark non-root variable --> dont care about him */
				non_root.insert(std::string(Z3_ast_to_string(ctx, arg1)));


			std::vector<Z3_ast> eqNodeArg0 = collect_eqc(t, arg0);
			std::vector<Z3_ast> eqNodeArg1 = collect_eqc(t, arg1);
			bool duplicateConcat = false;
			for (const auto& refined_node : refined_eqNode)
				if (std::find(eqNodeArg0.begin(), eqNodeArg0.end(), refined_node) != eqNodeArg0.end() ||
						std::find(eqNodeArg1.begin(), eqNodeArg1.end(), refined_node) != eqNodeArg1.end()) {
					duplicateConcat = true;
					break;
				}
				else if (isConcatFunc(t, refined_node)){
					Z3_ast arg00 = Z3_get_app_arg(ctx, Z3_to_app(ctx, refined_node), 0);
					Z3_ast arg11 = Z3_get_app_arg(ctx, Z3_to_app(ctx, refined_node), 1);
					if (std::find(eqNodeArg0.begin(), eqNodeArg0.end(), arg00) != eqNodeArg0.end() &&
							std::find(eqNodeArg1.begin(), eqNodeArg1.end(), arg11) != eqNodeArg1.end()) {
						duplicateConcat = true;
						break;
					}
				}

			if (duplicateConcat == false) {
				refined_eqNode.emplace_back(_node);
			}
		}


		else if (_node != node) {
			/* mark non-root variable */
			if (isStrVariable(t, _node)) {
				non_root.insert(std::string(Z3_ast_to_string(ctx, _node)));
			}

			/* do not need to add itself */
			if (isAutomatonFunc(t, _node)) {
				refined_eqNode.emplace_back(_node);
			}
		}


	/* if none of them is const --> continue with Concat */
	for (const auto& _node : refined_eqNode)
		if (isConcatFunc(t, _node)) {
			std::vector<std::vector<Z3_ast>> arg0_eq;
			std::vector<std::vector<Z3_ast>> arg1_eq;
			Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, _node), 0);
			Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, _node), 1);

			if (!isAutomatonFunc(t, arg0)) { /* variable or Concat ... */
				if (allEqPossibilities.find(arg0) == allEqPossibilities.end()) {
					/* break cycle */
					if (levelMap.find(arg0) == levelMap.end()) {
						levelMap[arg0] = levelMap[node] + 1;
						extendVariableToFindAllPossibleEqualities(t,
								arg0,
								connectedVariables,
								non_root,
								allEqPossibilities,
								fullEqPossibilities,
								levelMap);
					}
					else
						allEqPossibilities[arg0].push_back({arg0});

				}
				arg0_eq = allEqPossibilities[arg0];
			}
			else { /* automaton */
				arg0_eq.push_back({arg0});
			}

			if (!isAutomatonFunc(t, arg1)) {
				if (allEqPossibilities.find(arg1) == allEqPossibilities.end()) {
					if (levelMap.find(arg1) == levelMap.end()) {
						levelMap[arg1] = levelMap[node] + 1;
						extendVariableToFindAllPossibleEqualities(t,
								arg1,
								connectedVariables,
								non_root,
								allEqPossibilities,
								fullEqPossibilities,
								levelMap);
					}
					else
						allEqPossibilities[arg1].push_back({arg1});
				}
				arg1_eq = allEqPossibilities[arg1];
			}
			else { /* automaton */
				arg1_eq.push_back({arg1});
			}

			assert(arg0_eq.size() > 0);
			assert(arg1_eq.size() > 0);

			/* combine */
			__debugPrint(logFile, "%d combine lhs + rhs: ", __LINE__);
			printZ3Node(t, node);
			__debugPrint(logFile, " = (");
			printZ3Node(t, arg0);
			__debugPrint(logFile, ", ");
			printZ3Node(t, arg1);
			__debugPrint(logFile, "): size = %ld * %ld\n", arg0_eq.size(), arg1_eq.size());
			for (unsigned j = 0; j < arg0_eq.size(); ++j) {
				for (unsigned k = 0; k < arg1_eq.size(); ++k) {
					std::vector<Z3_ast> tmp;
					tmp.insert(tmp.end(), arg0_eq[j].begin(), arg0_eq[j].end());
					tmp.insert(tmp.end(), arg1_eq[k].begin(), arg1_eq[k].end());
					result.emplace_back(tmp);
				}
			}
		}
		else {
			__debugPrint(logFile, "%d current checking node: %s \n", __LINE__, Z3_ast_to_string(ctx, _node));

			/* must be automata */
			if ((constNode != NULL && constNode != _node) ||
					constNode == NULL){
				/* skip the generic automata */
				std::string automaton2str = Z3_ast_to_string(ctx, Z3_get_app_arg(ctx, Z3_to_app(ctx, _node), 0));
				__debugPrint(logFile, "%d should not check %s\n", __LINE__, automaton2str.c_str());
				if (automaton2str.find("$$") > 2 || automaton2str.find("!!") == std::string::npos) {
					__debugPrint(logFile, "%d add const \"%s\" to node: %s\n", __LINE__, automaton2str.c_str(), Z3_ast_to_string(ctx, node));
					result.push_back({_node});
				}
			}
			else
				__debugPrint(logFile, "%d skipped\n", __LINE__);
		}

	fullEqPossibilities[node] = result;
	std::vector<std::vector<Z3_ast>> refined_result;
	/* check
	 * 1. contain const or not
	 * 2. contain connected variables or not
	 *
	 * if both are false, keep original, print length
	 */
	__debugPrint(logFile, ">> %d before refine node %s: size = %ld\n", __LINE__, Z3_ast_to_string(ctx, node), result.size());
	for (const auto& _eq: result){
		bool added = false;
		for (const auto _node : _eq) {
			if (isAutomatonFunc(t, _node) ||
					connectedVariables.find(_node) != connectedVariables.end()) {
				__debugPrint(logFile, "%d add because of %s\n", __LINE__, Z3_ast_to_string(ctx, _node));
				displayListNode(t, _eq, "_Eq ");
				refined_result.emplace_back(_eq);
				added = true;
				break;
			}

		}

		/* do not need to print this case because it can be implied from SMT file */
		if (added == false) {
			__debugPrint(logFile, "%d not added\n", __LINE__);
			displayListNode(t, _eq, "_Eq ");
		}
	}

	__debugPrint(logFile, ">> %d node %s: size = %ld\n", __LINE__, Z3_ast_to_string(ctx, node), refined_result.size());

	if (constNode != NULL) /* found a const at the beginning */ {
		__debugPrint(logFile, "%d found const\n", __LINE__);
		/* create a new combination for const */
		/* update: const = lhs . rhs | automaton */
		if (refined_result.size() > 0) {
			refined_result.push_back({constNode});
			allEqPossibilities[constNode] = refined_result;
			fullEqPossibilities[constNode] = result;
		}

		/* --> update: he = const */
		fullEqPossibilities[node].push_back({constNode});
		allEqPossibilities[node].push_back({constNode});
	}
	else {
		/* he = himself */
		if (refined_result.size() == 0) {
			if (!isConcatFunc(t, node))
				refined_result.push_back({node});
			else {
				std::vector<Z3_ast> tmpVector;
				collect_node_in_concat(t, node, tmpVector);
				refined_result.push_back(tmpVector);
			}
			__debugPrint(logFile, "\t %d add itself: %s\n", __LINE__, Z3_ast_to_string(ctx, node));
		}

		/* update */
		allEqPossibilities[node] = refined_result;
	}

	if (orgNode != node){
		fullEqPossibilities[orgNode] = fullEqPossibilities[node];
		allEqPossibilities[orgNode] = allEqPossibilities[node];
	}

	__debugPrint(logFile, ">> %d node %s: size = %ld\n", __LINE__, Z3_ast_to_string(ctx, node), allEqPossibilities[node].size());
}

/*
 * rewrite a vector of ast node to a vector of string
 */
std::vector<std::string> vectorAst_to_vectorString(Z3_theory t, std::vector<Z3_ast> eqPossibility){
	std::vector<std::string> tmp;
	Z3_context ctx = Z3_theory_get_context(t);
	for (unsigned int j = 0; j < eqPossibility.size(); ++j) {
		if (isAutomatonFunc(t, eqPossibility[j])) {
			std::string regex = getConstString(t, eqPossibility[j]);
			if (isNonDetAutomatonFunc(t, eqPossibility[j])) {
				Z3_ast arg01 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eqPossibility[j]), 1);
				std::string index = std::string(Z3_ast_to_string(ctx, arg01));
				regex = "\"" + regex + "\"_" + index;
			}
			else
				regex = "\"" + regex + "\"";
			tmp.emplace_back(regex);
		}
		else
			tmp.emplace_back(std::string(Z3_ast_to_string(ctx, eqPossibility[j])));
	}
	return tmp;
}

void collect_node_in_concat(Z3_theory t, Z3_ast node, std::vector<Z3_ast> &list){
	Z3_context ctx = Z3_theory_get_context(t);
	assert(isConcatFunc(t, node));

	Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0);
	Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 1);

	if (isStrVariable(t, arg0) || isAutomatonFunc(t, arg0))
		list.emplace_back(arg0);
	else {
		if (isConcatFunc(t, arg0))
			collect_node_in_concat(t, arg0, list);
	}

	if (isStrVariable(t, arg1) || isAutomatonFunc(t, arg1))
		list.emplace_back(arg1);
	else {
		if (isConcatFunc(t, arg1))
			collect_node_in_concat(t, arg1, list);
	}
}

/*
 *
 */
std::set<Z3_ast> collectConnectedVars(Z3_theory t){
	/* detect connected variables */
	std::map<Z3_ast, Z3_ast> inConcat;
	std::set<Z3_ast> ret;

	for (const auto& concatNode : concat_astNode_map) {

		 std::vector<Z3_ast> list;
		 collect_node_in_concat(t, concatNode.second, list);
		 for (unsigned i = 0; i < list.size(); ++i){
			 std::vector<Z3_ast> eq_node = collect_eqc(t, list[i]);
			 for (unsigned j = i + 1; j < list.size(); ++j)
				 for (unsigned k = 0; k < eq_node.size(); ++k)
					 if (eq_node[k] == list[j])
						 ret.emplace(list[i]);
		 }
		/* check connected for 1st variable */
		if (inConcat.find(concatNode.first.first) != inConcat.end() &&
				inConcat[concatNode.first.first] != concatNode.second)
			ret.insert(concatNode.first.first);

		else if (!isAutomatonFunc(t, concatNode.first.first))
			inConcat[concatNode.first.first] = concatNode.second;

		/* check connected for 2nd variable */
		if (inConcat.find(concatNode.first.second) != inConcat.end() &&
				inConcat[concatNode.first.second] != concatNode.second)
			ret.insert(concatNode.first.second);
		else if (!isAutomatonFunc(t, concatNode.first.second))
			inConcat[concatNode.first.second] = concatNode.second;
	}

	for (const auto& node : disequalityList){
		if (isVariable(t, node.first.first))
			ret.emplace(node.first.first);
		else if (isConcatFunc(t, node.first.first)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.first.first);
			collect_node_in_concat(t, node.first.first, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}
		if (isVariable(t, node.first.second))
			ret.emplace(node.first.second);
		else if (isConcatFunc(t, node.first.second)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.first.second);
			collect_node_in_concat(t, node.first.second, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}
	}

	for (const auto& node : containNodeMap){
		if (isVariable(t, node.first.first))
			ret.emplace(node.first.first);
		else if (isConcatFunc(t, node.first.first)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.first.first);
			collect_node_in_concat(t, node.first.first, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}
	}

	for (const auto& node : replaceNodeMap)
		if (isVariable(t, node.second))
			ret.emplace(node.second);
		else if (isConcatFunc(t, node.second)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.second);
			collect_node_in_concat(t, node.second, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}

	for (const auto& node : replaceAllNodeMap)
		if (isVariable(t, node.second))
			ret.emplace(node.second);
		else if (isConcatFunc(t, node.second)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.second);
			collect_node_in_concat(t, node.second, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}

	for (const auto& node : subStrNodeMap)
		if (isVariable(t, node.second))
			ret.emplace(node.second);
		else if (isConcatFunc(t, node.second)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.second);
			collect_node_in_concat(t, node.second, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}

	for (const auto& node : indexOf_toAstMap){
		if (isVariable(t, node.first.first))
			ret.emplace(node.first.first);
		else if (isConcatFunc(t, node.first.first)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.first.first);
			collect_node_in_concat(t, node.first.first, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}
	}

	for (const auto& node : indexOf2_toAstMap)
		if (isVariable(t, node.first.first.first))
			ret.emplace(node.first.first.first);
		else if (isConcatFunc(t, node.first.first.first)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.first.first.first);
			collect_node_in_concat(t, node.first.first.first, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}

	for (const auto& node : lastIndexOf_toAstMap)
		if (isVariable(t, node.first.first))
			ret.emplace(node.first.first);
		else if (isConcatFunc(t, node.first.first)){
			std::vector<Z3_ast> tmp;
			ret.emplace(node.first.first);
			collect_node_in_concat(t, node.first.first, tmp);
			for (const auto& n : tmp)
				if (isVariable(t, n))
					ret.emplace(n);
		}

	displayListNode(t, ret,  "list of connectedVar");
	return ret;
}

/*
 * all vars do not contain some letters
 */
std::set<char> getNotContainLetters(
		Z3_theory t,
		std::vector<Z3_ast> list,
		std::map<Z3_ast, bool> boolValues){
	/* init map */
	std::set<char> initSet;
	for (unsigned i = 32; i < 128; ++i)
		initSet.emplace(i);
	for (const auto& node : list) {
		if (isStrVariable(t, node)) {
			std::set<char> tmp;
			for (const auto& contain : containPairBoolMap)
				if (contain.first.first == node &&
						(isConstStr(t, contain.first.second) || isDetAutomatonFunc(t, contain.first.second)) &&
						boolValues[contain.second] == false){
					std::string str = getConstString(t, contain.first.second);
					if (str.size() == 1) {
						tmp.emplace(str[0]);
					}
				}

			/* intersection*/
			std::set<char> newSet;
			for (const auto& ch : initSet)
				if (tmp.find(ch) != tmp.end())
					newSet.emplace(ch);
			initSet = newSet;
		}
	}
	return initSet;
}

/*
 * all vars do not contain some letters
 */
std::set<char> getNotContainLetters(
		Z3_theory t,
		std::vector<std::vector<Z3_ast>> list,
		std::map<Z3_ast, bool> boolValues){
	std::set<char> ret;
	for (const auto& v : list) {
		std::set<char> tmp = getNotContainLetters(t, v, boolValues);
		ret.insert(tmp.begin(), tmp.end());
	}
	return ret;
}

/*
 *
 */
std::map<char, int> eval_parikh_fixedbound(
		Z3_theory t,
		std::vector<Z3_ast> list,
		std::map<Z3_ast, bool> boolValues){
	std::map<char, int> m;
	/* init map */
	std::set<char> initSet = getNotContainLetters(t, list, boolValues);
	for (const auto& node : list) {
		if (isNonDetAutomatonFunc(t, node)) {
			/* not contain chars */
			std::string tmpStr = getConstString(t, node);
			/* intersection*/
			std::set<char> newSet;
			for (const auto& ch : initSet)
				if (tmpStr.find(ch) == std::string::npos)
					newSet.emplace(ch);
			initSet = newSet;
		}
	}
	for (const auto& node: list)
		if (isConstStr(t, node) || isDetAutomatonFunc(t, node)) {
			std::string str = getConstString(t, node);
			for (unsigned i = 0; i < str.length(); ++i)
				if (initSet.find(str[i]) != initSet.end())
					m[str[i]] = m[str[i]] + 1;
		}
	return m;
}

/*
 * the string has at least some chars
 */
std::map<char, int> eval_parikh_lowerbound(
		Z3_theory t,
		std::vector<Z3_ast> list,
		std::map<Z3_ast, bool> boolValues){
	std::map<char, int> m;
	/* init map */
	std::set<char> initSet;
	for (unsigned i = 0; i < 255; ++i)
		m[i]= 0;

	for (const auto& node: list)
		if (isConstStr(t, node) || isDetAutomatonFunc(t, node)) {
			std::string str = getConstString(t, node);
			for (unsigned i = 0; i < str.length(); ++i)
				m[str[i]] = m[str[i]] + 1;
		}
		else if (isRegexPlusFunc(t, node)) {
			std::string str = parse_regex_content(getConstString(t, node));
			for (unsigned i = 0; i < str.length(); ++i)
				m[str[i]] = m[str[i]] + 1;
		}
	std::map<char, int> ret;
	for (const auto& n : m)
		if (n.second > 0)
			ret[n.first] = n.second;
	return ret;
}

/*
 *
 */
std::map<std::string, int> getMaxParikhMap(
		std::map<std::string, int> data,
		std::map<std::string, int> tmp){
	/* get max of two maps */
	for (const auto& ch : tmp)
		if (data.find(ch.first) == data.end() || data[ch.first] < ch.second)
			data[ch.first] = ch.second;
	return data;
}

/*
 *
 */
void addToParikhMap(
		std::string ch,
		std::map<std::string, int> &m){
	if (m.find(ch) == m.end())
		m[ch] = 1;
	else
		m[ch] = m[ch] + 1;
}

/*
 *
 */
std::map<std::string, int> computeParikhFromConst(
		Z3_theory t,
		Z3_ast node){
	std::map<std::string, int> data;
	std::string s = getConstString(t, node);

	if (s.length() > 1)
		addToParikhMap(s, data);

	for (unsigned i = 1; i < s.size(); ++i)
		if (s[i] != s[i - 1])
			addToParikhMap(std::string(1, s[i - 1]), data);

	/* last char */
	addToParikhMap(std::string(1, s[s.length() - 1]), data);
	return data;
}

/*
 *
 */
std::vector<std::string> computeParikhFromConst_complement(
		Z3_theory t,
		Z3_ast node){
	std::vector<std::string> data;
	std::string s = getConstString(t, node);
	for (unsigned i = 32; i < 128; ++i)
		if (s.find((char)i) == std::string::npos)
			data.emplace_back(std::string(1, i));

	return data;
}

/*
 *
 */
std::map<std::string, int> computeParikhFromVector(
		Z3_theory t,
		std::vector<Z3_ast> list){
	std::map<std::string, int> tmp;
	for (const auto& n : list)
		if (isConstStr(t, n) || isDetAutomatonFunc(t, n) || isRegexPlusFunc(t, n)){
			std::string s = getConstString(t, n);
			if (isRegexPlusFunc(t, n))
				s = parse_regex_content(s);

			/* add the whole string */
			if (s.length() > 1)
				addToParikhMap(s, tmp);

			/* add all the letter */
			/* compare to the first char */
			unsigned i = 1;
			for (; i < s.size(); ++i)
				if (s[i] != s[0]){
					if (tmp.find(std::string(1, s[0])) == tmp.end())
						tmp[std::string(1, s[0])] = 1;
					break;
				}
			i++;
			/* continue */
			for (;i < s.size(); ++i)
				if (s[i] != s[i - 1])
					addToParikhMap(std::string(1, s[i - 1]), tmp);

			/* last char */
			addToParikhMap(std::string(1, s[s.length() - 1]), tmp);
		}
	return tmp;
}

/*
 *
 */
std::map<std::string, int> computeParikhFromVectorOfVector(
		Z3_theory t,
		std::vector<std::vector<Z3_ast>> list){
	std::map<std::string, int> data;
	for (const auto& v : list){
		std::map<std::string, int> tmp = computeParikhFromVector(t, v);

		/* get max of two maps */
		data = getMaxParikhMap(data, tmp);
	}
	return data;
}

/*
 *
 */
std::map<std::string, int> computeMinParikh(
		Z3_theory t,
		Z3_ast node,
		std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> combinationOverVariables){
	std::map<std::string, int> data;
	std::vector<Z3_ast> eq = collect_eqc(t, node);
	for (const auto& n : eq) {
		data = getMaxParikhMap(data, computeParikhFromVectorOfVector(t, combinationOverVariables[n]));
	}
	return data;
}

/*
 *
 */
void compute_parikh(
		Z3_theory t,
		Z3_ast node,
		std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> combinationOverVariables,
		std::map<Z3_ast, bool> boolMapValues,
		std::map<Z3_ast, std::map<std::string, int>> &minimum_parikhImg,
		std::map<Z3_ast, std::map<std::string, int>> &fixed_parikhImg){

	if (minimum_parikhImg.find(node) != minimum_parikhImg.end())
		return;

	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");

	std::map<std::string, int> data_fix;
	std::vector<std::string> data_complement;
	std::vector<Z3_ast> eq = collect_eqc(t, node);

	/* check itself and its friends */
	for (const auto& n : eq) {
		if (isConstStr(t, n) || isDetAutomatonFunc(t, n)){
			data_fix = computeParikhFromConst(t, n);
			data_complement = computeParikhFromConst_complement(t, n);
			break;
		}
	}

	if (data_fix.size() > 0){
		for (const auto& n : eq)
			minimum_parikhImg[n] = data_fix;

		for (const auto& ch : data_complement)
			data_fix[ch] = 0;

		for (const auto& n : eq)
			fixed_parikhImg[n] = data_fix;
		return;
	}

	/* check sub-elements */
	std::map<std::string, int> data_min = computeMinParikh(t, node, combinationOverVariables);
	data_fix = fixed_parikhImg[node];

	for (const auto& n : eq) {
		/* check if they do not contain some letters */
		for (const auto c : containPairBoolMap) {
			if (boolMapValues[c.second] == false) {
				if (c.first.first == n && (isConstStr(t, c.first.second) || isDetAutomatonFunc(t, c.first.second))) {
					std::string s = getConstString(t, c.first.second);
					if (s.length() == 1)
						data_fix[s] = 0;
				}
			}
		}
	}

	/* check = replace */
	for (const auto& n : eq) {
		for (const auto& repAll : replaceAllNodeMap)
			if (n == repAll.second && std::find(eq.begin(), eq.end(), repAll.first.first) == eq.end()) {
				__debugPrint(logFile, "%d going to check: ", __LINE__);
				printZ3Node(t, repAll.first.first);
				__debugPrint(logFile, "\n");

//				std::set<char> notContainLetters = getNotContainLetters(t, combinationOverVariables[repAll.first.first], boolMapValues);
				compute_parikh(t, repAll.first.first, combinationOverVariables, boolMapValues, minimum_parikhImg, fixed_parikhImg);

				std::map<std::string, int> tmp_min = minimum_parikhImg[repAll.first.first];
				std::map<std::string, int> tmp_fix = fixed_parikhImg[repAll.first.first];

				__debugPrint(logFile, "%d tmp result\n", __LINE__);
				for (const auto& ch : tmp_min)
					__debugPrint(logFile, "%s:%d\t", ch.first.c_str(), ch.second);
				__debugPrint(logFile, "\n");

				Z3_ast tobeReplaced = repAll.first.second.first;
				if (isConstStr(t, tobeReplaced) || isDetAutomatonFunc(t, tobeReplaced)){
					std::string s0 = getConstString(t, tobeReplaced);

					Z3_ast replacing = repAll.first.second.second;
					if (isConstStr(t, replacing) || isDetAutomatonFunc(t, replacing)){
						std::string s1 = getConstString(t, replacing);
						__debugPrint(logFile, "%d %s %s\n", __LINE__, s0.c_str(), s1.c_str());

						if (s0.length() == 1) {
							if (s1.find(s0) == std::string::npos){
								/* other letters, if they are not in s0, will stay the same */
								for (const auto& ch : tmp_min)
									if (ch.first.find(s0) == std::string::npos) {
										data_min.emplace(ch);
									}
							}
							else {
								/* get max of two sets */
								data_min = getMaxParikhMap(data_min, tmp_min);
							}

							/* because all s0 were replaced --> none of them in the replaced string */
							if (s1.find(s0) == std::string::npos) {
								__debugPrint(logFile, "%d fix parikh cannot have %s\n", __LINE__, s0.c_str());
								data_fix[std::string(1, s0[0])] = 0;
							}
						}

						/* other letters, if they are not in s0 and s1, will stay the same */
						for (const auto& ch : tmp_fix)
							if (ch.first.find(s0) == std::string::npos && s1.find(ch.first) == std::string::npos)
								data_fix.emplace(ch);
					}
				}
			}

		/* replace */
		for (const auto& rep : replaceNodeMap)
			if (n == rep.second && std::find(eq.begin(), eq.end(), rep.first.first) == eq.end()) {
				__debugPrint(logFile, "%d going to check: ", __LINE__);
				printZ3Node(t, rep.first.first);
				__debugPrint(logFile, "\n");

				//				std::set<char> notContainLetters = getNotContainLetters(t, combinationOverVariables[repAll.first.first], boolMapValues);
				compute_parikh(t, rep.first.first, combinationOverVariables, boolMapValues, minimum_parikhImg, fixed_parikhImg);

				std::map<std::string, int> tmp_min = minimum_parikhImg[rep.first.first];
				std::map<std::string, int> tmp_fix = fixed_parikhImg[rep.first.first];

				__debugPrint(logFile, "%d tmp result\n", __LINE__);
				for (const auto& ch : tmp_min)
					__debugPrint(logFile, "%s:%d\t", ch.first.c_str(), ch.second);
				__debugPrint(logFile, "\n");

				Z3_ast tobeReplaced = rep.first.second.first;
				if (isConstStr(t, tobeReplaced) || isDetAutomatonFunc(t, tobeReplaced)){
					std::string s0 = getConstString(t, tobeReplaced);

					Z3_ast replacing = rep.first.second.second;
					if (isConstStr(t, replacing) || isDetAutomatonFunc(t, replacing)){
						std::string s1 = getConstString(t, replacing);
						__debugPrint(logFile, "%d %s %s\n", __LINE__, s0.c_str(), s1.c_str());

						if (s0.length() == 1) {
							if (s1.find(s0) == std::string::npos){
								/* other letters, if they are not in s0, will stay the same */
								for (const auto& ch : tmp_min)
									if (ch.first.find(s0) == std::string::npos) {
										data_min.emplace(ch);
									}
							}
							else {
								/* get max of two sets */
								data_min = getMaxParikhMap(data_min, tmp_min);
							}
						}

						/* other letters, if they are not in s0 and s1, will stay the same */
						for (const auto& ch : tmp_fix)
							if (ch.first.find(s0) == std::string::npos && s1.find(ch.first) == std::string::npos)
								data_fix.emplace(ch);
					}
				}
			}
	}

	for (const auto& n : eq) {
		minimum_parikhImg[n] = data_min;
		fixed_parikhImg[n] = data_fix;
	}
}

/*
 * x = replace y a b --> parikh image of x is almost the same as parikh image of y
 */
void compute_parikh(
		Z3_theory t,
		std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> combinationOverVariables,
		std::map<Z3_ast, bool> boolMapValues,
		std::map<Z3_ast, std::map<std::string, int>> &min_parikhMap,
		std::map<Z3_ast, std::map<std::string, int>> &fix_parikhMap){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	for (const auto& node : replaceAllNodeMap)
		compute_parikh(t, node.second, combinationOverVariables, boolMapValues, min_parikhMap, fix_parikhMap);

	for (const auto& node: replaceNodeMap)
		compute_parikh(t, node.second, combinationOverVariables, boolMapValues, min_parikhMap, fix_parikhMap);

	/* test */
	for (const auto& node : min_parikhMap) {
		__debugPrint(logFile, "%d * %s *: min image of ", __LINE__, __FUNCTION__);
		printZ3Node(t, node.first);
		__debugPrint(logFile, ": \n");
		for (const auto& ch : node.second)
			__debugPrint(logFile, "%s:%d\t\t", ch.first.c_str(), ch.second);
		__debugPrint(logFile, "\n");
	}

	for (const auto& node : fix_parikhMap) {
		__debugPrint(logFile, "%d * %s *: fixed image of ", __LINE__, __FUNCTION__);
		printZ3Node(t, node.first);
		__debugPrint(logFile, ": \n");
		for (const auto& ch : node.second)
			__debugPrint(logFile, "%s:%d\t\t", ch.first.c_str(), ch.second);
		__debugPrint(logFile, "\n");
	}
}

/*
 *
 */
bool parikh_check_substr_basic(
		Z3_theory t,
		Z3_ast node,
		std::vector<std::vector<Z3_ast>> list){
	Z3_context ctx = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d *** %s ***: %s \n", __LINE__, __FUNCTION__, Z3_ast_to_string(ctx, node));

	if (isConstStr(t, node) || isDetAutomatonFunc(t, node))
		list.push_back({node});

	if (list.size() <= 1)
		return true;

	for (unsigned i = 1; i < list.size(); ++i) {
		/* cut common prefix and suffix */
		std::vector<Z3_ast> l00;
		std::vector<Z3_ast> l01;
		int start = 0, finish = list[0].size() - 1;
		while (start < (int)list[0].size() && start < (int)list[i].size())
			if (list[0][start] == list[i][start])
				++start;
			else
				break;
		while (finish >= 0 && (list[i].size() - list[0].size() + finish) >= 0) {
			if (list[0][finish] == list[i][list[i].size() - list[0].size() + finish])
				--finish;
			else
				break;
		}
		__debugPrint(logFile, "%d going to trim: %d -> %d\n", __LINE__, start, finish);
		/* --> cut */
		for (int j = start; j <= finish; ++j)
			l00.emplace_back(list[0][j]);
		for (int j = start; j <= (int)list[i].size() - ((int)list[0].size() - finish); ++j)
			l01.emplace_back(list[i][j]);

		__debugPrint(logFile, "%d after trimming\n", __LINE__)
		if (l00.size() == 1) {
			if (isConstStr(t, l00[0]) || isDetAutomatonFunc(t, l00[0])){
				std::string s0 = getConstString(t, l00[0]);
				for (unsigned j = 0; j < l01.size(); ++j)
					if (isConstStr(t, l01[j]) || isDetAutomatonFunc(t, l01[j])){
						std::string s1 = getConstString(t, l01[j]);
						if (s0.find(s1) == std::string::npos) {
							return false;
						}
					}
			}
		}
		else {
			if (l01.size() == 1) {
				if (isConstStr(t, l01[0]) || isDetAutomatonFunc(t, l01[0])){
					std::string s0 = getConstString(t, l01[0]);
					for (unsigned j = 0; j < l00.size(); ++j)
						if (isConstStr(t, l00[j]) || isDetAutomatonFunc(t, l00[j])){
							std::string s1 = getConstString(t, l00[j]);
							if (s0.find(s1) == std::string::npos) {
								return false;
							}
						}
				}
			}
		}
	}
	__debugPrint(logFile, ">> %d done %s \n", __LINE__, __FUNCTION__);
	return true;

}

/*
 *
 */
bool parikh_check_contain(
		Z3_theory t,
		Z3_ast node,
		std::vector<std::vector<Z3_ast>> list,
		std::map<Z3_ast, bool> boolValues,
		std::map<Z3_ast, std::map<std::string, int>> min_parikhMap,
		std::map<Z3_ast, std::map<std::string, int>> fix_parikhMap,
		Z3_ast& conflict){

	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");

//	for (const auto& l : list)
//		displayListNode(t, l, "Quick check list: ");

	std::vector<std::string> constList;

	/* check the node */
	std::map<std::string, int> data_min = min_parikhMap[node];
	if (isConstStr(t, node) || isDetAutomatonFunc(t, node)){
		constList.emplace_back(getConstString(t, node));
	}
	else
		for (const auto& v : list)
			for (const auto n : v)
				if (isConstStr(t, n) || isDetAutomatonFunc(t, n))
					constList.emplace_back(getConstString(t, n));

	for (const auto& ch : data_min)
		__debugPrint(logFile, " --- %s %d\t", ch.first.c_str(), ch.second);

	std::map<std::string, int> data_fix = fix_parikhMap[node];
	for (const auto& ch : data_fix)
		__debugPrint(logFile, " +++ %s %d\t", ch.first.c_str(), ch.second);
	__debugPrint(logFile, "\n");

	std::vector<Z3_ast> eq = collect_eqc(t, node);

	for (const auto& contain : containPairBoolMap)
		if (std::find(eq.begin(), eq.end(), contain.first.first) != eq.end() &&
				(isConstStr(t, contain.first.second) || isDetAutomatonFunc(t, contain.first.second))){
			std::string str = getConstString(t, contain.first.second);
			assert(boolValues.find(contain.second) != boolValues.end());

			if (boolValues[contain.second] == false) {
				__debugPrint(logFile, "%d not contain: %s\n", __LINE__, str.c_str());

				if (data_min.find(str) != data_min.end()){
					conflict = contain.second;
					return false;
				}

				if (str.length() == 1) {
					for (unsigned j = 0; j < str.length(); ++j)
						if (data_min[std::string(1, str[j])] > 0) {
							conflict = contain.second;
							return false;
						}
				}

				for (const auto& s : constList)
					if (s.find(str) != std::string::npos){
						conflict = contain.second;
						return false;
					}
			}
			else {
				__debugPrint(logFile, "%d contain: %s\n", __LINE__, str.c_str());
				/* contain = true */
				for (unsigned i = 0 ; i < str.length(); ++i)
					if (data_fix.find(std::string(1, str[i])) != data_fix.end() && data_fix[std::string(1, str[i])] == 0) {
						conflict = contain.second;
						__debugPrint(logFile, "%d does not work because of fix_parikhImg: %s, at %c\n", __LINE__, str.c_str(), str[i]);
						return false;
					}
			}
		}

	return true;
}

/*
 *
 */
bool parikh_check_regex(
		Z3_theory t,
		Z3_ast node,
		std::vector<std::vector<Z3_ast>> list,
		std::map<Z3_ast, bool> boolValues,
		std::map<Z3_ast, std::map<std::string, int>> parikhMap){

	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");

//	for (const auto& v : list)
//		displayListNode(t, v, "Quick check list: ");

	std::map<std::string, int> data = parikhMap[node];
	for (const auto& ch : data)
		__debugPrint(logFile, " --- %s %d\t", ch.first.c_str(), ch.second);

	std::vector<Z3_ast> eq = collect_eqc(t, node);
	if (data.size() > 0) {
		for (const auto& v : list){
			std::set<char> notContain00 = getNotContainLetters(t, v, boolValues);
			/* check two replace all funcs */
			for (const auto& ch : notContain00) {
				int cnt00 = 0;
				/* count list 0 */
				for (const auto& p : v)
					if (isConstStr(t, p) || isDetAutomatonFunc(t, p)) {
						cnt00 = -1;
						break;
					}
					else if (isRegexPlusFunc(t, p)) {
						std::string s = parse_regex_content(getConstString(t, p));
						if (s.length() > 1) {
							cnt00 = -1;
							break;
						}

						if (s.find(ch) != std::string::npos)
							++cnt00;
					}
				if (cnt00 == -1)
					continue;

				if (cnt00 < data[std::string(1, ch)]) {
					__debugPrint(logFile, "%d char: %c --> cnt00 = %d, data = %d\n", __LINE__, ch, cnt00, data[std::string(1, ch)]);
					return false;
				}
			}
		}
	}
	return true;
}

/*
 * x = a . b . c = d . e . f --> possible or not
 */
bool parikh_check_replaceall(
		Z3_theory t,
		std::vector<std::vector<Z3_ast>> list,
		std::map<Z3_ast, bool> boolValues){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	if (list.size() <= 1)
		return true;

//	for (const auto& l : list)
//		displayListNode(t, l, "Quick check list: ");

	for (unsigned i = 1; i < list.size(); ++i) {
		/* cut common prefix and suffix */
		std::vector<Z3_ast> l00;
		std::vector<Z3_ast> l01;
		unsigned start = 0, removeItems = 0;
		while (start < list[0].size() && start < list[i].size())
			if (list[0][start] == list[i][start])
				++start;
			else
				break;
		while (list[0].size() - removeItems > start && list[i].size() - removeItems - 1 >= 0)
			if (list[0][list[0].size() - removeItems - 1] == list[i][list[i].size() - removeItems - 1])
				removeItems++;
			else
				break;

		/* --> cut */
		for (unsigned j = start; j < list[0].size() - removeItems; ++j)
			l00.emplace_back(list[0][j]);

		for (unsigned j = start; j < list[i].size() - removeItems; ++j)
			l01.emplace_back(list[i][j]);

		std::vector<Z3_ast> l10;
		std::vector<Z3_ast> l11;
		/* remove common vars */
		for (const auto& v : l00)
			if (isStrVariable(t, v)){
				if (std::find(l01.begin(), l01.end(), v) == l01.end())
					l10.emplace_back(v);
			}
			else
				l10.emplace_back(v);

		for (const auto& v : l01)
			if (isStrVariable(t, v)){
				if (std::find(l00.begin(), l00.end(), v) == l00.end())
					l11.emplace_back(v);
			}
			else
				l11.emplace_back(v);

		/* compare */
		std::map<char, int> fixed00 = eval_parikh_fixedbound(t, l10, boolValues);
		std::map<char, int> lower00 = eval_parikh_lowerbound(t, l10, boolValues);
		std::map<char, int> fixed01 = eval_parikh_fixedbound(t, l11, boolValues);
		std::map<char, int> lower01 = eval_parikh_lowerbound(t, l11, boolValues);

		__debugPrint(logFile, "%d fixed00 bound size %ld\n", __LINE__, fixed00.size());
		for (const auto& p : fixed00)
			__debugPrint(logFile, "%c: %d\t\t ", p.first, p.second);

		__debugPrint(logFile, "\n%d fixed01 bound size %ld\n", __LINE__, fixed01.size());
		for (const auto& p : fixed01)
			__debugPrint(logFile, "%c: %d\t\t ", p.first, p.second);

		__debugPrint(logFile, "\n%d lower00 bound: of size %ld\n", __LINE__, lower00.size());
		for (const auto& p : lower00)
			if (p.second > 0)
				__debugPrint(logFile, "%c: %d\t\t ", p.first, p.second);

		__debugPrint(logFile, "\n%d lower01 bound: of size %ld\n", __LINE__, lower01.size());
		for (const auto& p : lower01)
			if (p.second > 0)
				__debugPrint(logFile, "%c: %d\t\t ", p.first, p.second);
		bool constOnly00 = (lower00.size() == fixed00.size()) && fixed00.size() > 0;
		bool constOnly01 = (lower01.size() == fixed01.size()) && fixed01.size() > 0;
		for (const auto& ch : fixed00)
			if (lower01.find(ch.first) != lower01.end())
				if (lower01[ch.first] > ch.second)
					return false;

		for (const auto& ch : fixed01)
			if (lower00.find(ch.first) != lower01.end())
				if (lower00[ch.first] > ch.second)
					return false;


		for (const auto& ch : fixed00)
			if (lower00[ch.first] != ch.second) {
				__debugPrint(logFile, "%d not constOnly00 because %d != %d at %c\n", __LINE__, lower00[ch.first], ch.second, ch.first);
				constOnly00 = false;
				break;
			}
		for (const auto& ch : fixed01)
			if (lower01[ch.first] != ch.second) {
				__debugPrint(logFile, "%d not constOnly01 because %d != %d at %c\n", __LINE__, lower01[ch.first], ch.second, ch.first);
				constOnly01 = false;
				break;
			}
		__debugPrint(logFile, "\n%d const ? %d ---  const ? %d\n", __LINE__, constOnly00? 1 : 0, constOnly01? 1 : 0);
		if (constOnly00 && constOnly01){
			__debugPrint(logFile, "%d both  sides are const\n", __LINE__);
			for (const auto& ch : fixed00)
				if (fixed01[ch.first] != ch.second)
					return false;
			for (const auto& ch : fixed01)
				if (fixed00[ch.first] != ch.second)
					return false;
		}
		else if (constOnly00){
			__debugPrint(logFile, "%d LHS is const\n", __LINE__);
			if (constOnly00)
				for (const auto& ch : fixed00)
					if (fixed01.find(ch.first) != fixed01.end() && fixed01[ch.first] > ch.second)
						return false;
		}
		else if (constOnly01){
			__debugPrint(logFile, "%d RHS is const\n", __LINE__);
				for (const auto& ch : fixed01)
					if (fixed00.find(ch.first) != fixed00.end() && fixed00[ch.first] > ch.second)
						return false;
		}

		__debugPrint(logFile, "%d *** step 3 ***\n", __LINE__);
		/* check regex plus for replaceall */
		__debugPrint(logFile, "%d checking regex plus\n", __LINE__);
		std::set<char> notContain00 = getNotContainLetters(t, list[0], boolValues);
		std::set<char> notContain01 = getNotContainLetters(t, list[i], boolValues);
		std::set<char> intersection;
		for (const auto& ch : notContain00) {
			__debugPrint(logFile, "%d letter: %c\n", __LINE__, ch);
			if (notContain01.find(ch) != notContain01.end())
				intersection.emplace(ch);
		}

		/* check two replace all funcs */
		for (const auto& ch : intersection){
			__debugPrint(logFile, "%d not include letter: %c\n", __LINE__, ch);
			int cnt00 = 0, cnt01 = 0;
			/* count list 0 */
			for (const auto& p : list[0])
				if (isConstStr(t, p) || isDetAutomatonFunc(t, p)) {
					cnt00 = -1;
					break;
				}
				else if (isRegexPlusFunc(t, p)) {
					std::string s = parse_regex_content(getConstString(t, p));
					if (s.find(ch) != std::string::npos)
						++cnt00;
				}
			if (cnt00 == -1)
				continue;

			/* count list i */
			for (const auto& p : list[i])
				if (isConstStr(t, p) || isDetAutomatonFunc(t, p)) {
					cnt01 = -1;
					break;
				}
				else if (isRegexPlusFunc(t, p)) {
					std::string s = parse_regex_content(getConstString(t, p));
					if (s.find(ch) != std::string::npos)
						++cnt01;
				}
			if (cnt01 == -1)
				continue;

			if (cnt00 != cnt01) {
				__debugPrint(logFile, "%d compare regex plus: char = %c: %d %d\n", __LINE__, ch, cnt00, cnt01);
				return false;
			}
		}
	}

	__debugPrint(logFile, "%d %s: done\n", __LINE__, __FUNCTION__);
	return true;
}

/**
 *
 */
void collectCombinationOverVariables(Z3_theory t,
		std::map<std::string, std::vector<std::vector<std::string>>> &combinationOverVariables,
		std::map<std::string, std::vector<std::vector<std::string>>> &fullCombinationOverVariables){
	Z3_context ctx = Z3_theory_get_context(t);
	std::set<std::string> non_root;

	std::set<Z3_ast> connectedVariables = collectConnectedVars(t);



	/* find all equal possibilities*/
	std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> allEqPossibilities;
	std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> fullEqPossibilities;
	std::map<Z3_ast, int> levelMap;
	for (const auto& var: inputVarMap) {
		std::string currentVarName = Z3_ast_to_string(ctx, var.first);
		if (non_root.find(currentVarName) == non_root.end()){
			levelMap[var.first] = 0;
			extendVariableToFindAllPossibleEqualities(	t,
					var.first,
					connectedVariables,
					non_root,
					allEqPossibilities,
					fullEqPossibilities,
					levelMap);
		}
	}

	for (const auto& var: replaceNodeMap) {
		std::string currentVarName = Z3_ast_to_string(ctx, var.second);
		if (non_root.find(currentVarName) == non_root.end()){
			levelMap[var.second] = 0;
			extendVariableToFindAllPossibleEqualities(t,
					var.second,
					connectedVariables,
					non_root,
					allEqPossibilities,
					fullEqPossibilities,
					levelMap);
		}
	}

	for (const auto& var: replaceAllNodeMap) {
		std::string currentVarName = Z3_ast_to_string(ctx, var.second);
		if (non_root.find(currentVarName) == non_root.end()){
			levelMap[var.second] = 0;
			extendVariableToFindAllPossibleEqualities(t,
					var.second,
					connectedVariables,
					non_root,
					allEqPossibilities,
					fullEqPossibilities,
					levelMap);
		}
	}

//	for (const auto& var: indexOf2_toAstMap) {
//		std::string currentVarName = Z3_ast_to_string(ctx, var.first.first.first);
//		if (non_root.find(currentVarName) == non_root.end()){
//			levelMap[var.first.first.first] = 0;
//			extendVariableToFindAllPossibleEqualities(t,
//					var.first.first.first,
//					connectedVariables,
//					non_root,
//					allEqPossibilities,
//					fullEqPossibilities,
//					levelMap);
//		}
//	}

//	for (const auto& var: indexOf_toAstMap) {
//		std::string currentVarName = Z3_ast_to_string(ctx, var.first.first);
//		if (non_root.find(currentVarName) == non_root.end()){
//			levelMap[var.first.first] = 0;
//			extendVariableToFindAllPossibleEqualities(t,
//					var.first.first,
//					connectedVariables,
//					non_root,
//					allEqPossibilities,
//					fullEqPossibilities,
//					levelMap);
//		}
//	}

	for (const auto& var: concat_astNode_map) {
			std::string currentVarName = Z3_ast_to_string(ctx, var.second);
			if (non_root.find(currentVarName) == non_root.end()){
				levelMap[var.second] = 0;
				extendVariableToFindAllPossibleEqualities(t,
						var.second,
						connectedVariables,
						non_root,
						allEqPossibilities,
						fullEqPossibilities,
						levelMap);
			}
		}

	for (const auto& var : levelMap)
		if (var.second > 0)
			if (isVariable(t, var.first))
				non_root.emplace(Z3_ast_to_string(ctx, var.first));

	__debugPrint(logFile, "%d Finish calculating\n", __LINE__);

	std::vector<Z3_ast> boolValues = collectBoolValueInPositiveContext(t);
	std::map<Z3_ast, bool> boolMapValues;
	for (const auto& b : boolValues){
		std::string tmp = Z3_ast_to_string(ctx, b);
		if (isVariable(t, b))
			boolMapValues[b] = true;
		else {
			Z3_ast v =  Z3_get_app_arg(ctx, Z3_to_app(ctx, b), 0);
			assert(isVariable(t, v));
			boolMapValues[v] = false;
		}
	}

	/* collect all equal possibilities of root variables */
	for (const auto& eqVar : allEqPossibilities) {
		std::string varName = std::string(Z3_ast_to_string(ctx, eqVar.first));
		__debugPrint(logFile, "%d before parikh_check_replaceall: var = %s\n", __LINE__, varName.c_str());
		bool fine_replace = parikh_check_replaceall(t, eqVar.second, boolMapValues);
		bool substr_basic = parikh_check_substr_basic(t, eqVar.first, eqVar.second);

		if (!fine_replace || !substr_basic) {
			__debugPrint(logFile, "%d * %s * replaceall does not work\n", __LINE__, __FUNCTION__);
			Z3_ast assertion = negatePositiveEquality(t, eqVar.first, eqVar.second, boolMapValues);
			if (assertion != NULL)
				addAxiom(t, assertion, __LINE__, true);
			else {
				assert(false);
				addAxiom(t, negatePositiveContext(t), __LINE__, true);
			}

			combinationOverVariables.clear();
			fullCombinationOverVariables.clear();
			return;
		}

		if (isAutomatonFunc(t, eqVar.first) || isStrVariable(t, eqVar.first))
			varName = node_to_string(t, eqVar.first);
		else if (isConcatFunc(t, eqVar.first))
			continue;

		/* update eq for itself */
		if (non_root.find(varName) == non_root.end() ||
				grm_astNode_map.find(eqVar.first) != grm_astNode_map.end()){
			/* add them to the result set */

			for (const auto& _eq : eqVar.second)
				combinationOverVariables[varName].emplace_back(vectorAst_to_vectorString(t, _eq));

			/* add all equal nodes of itor->first to repeated list */
			std::vector<Z3_ast> eqNode = collect_eqc(t, eqVar.first);
			for (const auto& _node : eqNode)
				if (isStrVariable(t, _node) && _node != eqVar.first) {
					non_root.insert(std::string(Z3_ast_to_string(ctx, _node)));
				}
		}
		else if (non_root.find(varName) != non_root.end()){
			combinationOverVariables[varName].clear();
			/* keep one eq to export length constraint */
			assert(eqVar.second.size() > 0);
			bool found = false;

			/* prefer to add a combination with const string */
			for (const auto& v : eqVar.second) {
				for (const auto& s : v)
					if (isAutomatonFunc(t, s)) {
						found = true;
						combinationOverVariables[varName].emplace_back(vectorAst_to_vectorString(t, v));
						break;
					}
				if (found)
					break;
			}
			/* then prefer to add a combination with connected var */
			if (!found)
				for (const auto& v : eqVar.second) {
					for (const auto& s : v)
						if (connectedVariables.find(s) != connectedVariables.end()) {
							found = true;
							combinationOverVariables[varName].emplace_back(vectorAst_to_vectorString(t, v));
							break;
						}
					if (found)
						break;
				}
			/* then add the first constraints */
			if (!found)
				combinationOverVariables[varName].emplace_back(vectorAst_to_vectorString(t, eqVar.second[0]));
		}

		/* update eq for its friends */
		std::vector<Z3_ast> eqNode = collect_eqc(t, eqVar.first);
		for (const auto& n : eqNode)
			if (isStrVariable(t, n) && n != eqVar.first) {
				std::string name = std::string(Z3_ast_to_string(ctx, n));
				assert(combinationOverVariables[varName].size() > 0);
				combinationOverVariables[name].emplace_back(combinationOverVariables[varName][0]);
			}
	}

	/* update fullCombinationOverVariables */
	for (const auto& eqVar : fullEqPossibilities) {
		std::string varName = "";
		if (isAutomatonFunc(t, eqVar.first) || isStrVariable(t, eqVar.first))
			varName = node_to_string(t, eqVar.first);
		else if (isConcatFunc(t, eqVar.first))
			continue;

		for (const auto& _eq : eqVar.second)
			fullCombinationOverVariables[varName].emplace_back(vectorAst_to_vectorString(t, _eq));

		/* update eq for its friends */
		std::vector<Z3_ast> eqNode = collect_eqc(t, eqVar.first);
		for (const auto& n : eqNode)
			if (isStrVariable(t, n) && n != eqVar.first) {
				std::string name = node_to_string(t, n);
				assert(combinationOverVariables[varName].size() > 0);
				fullCombinationOverVariables[name] = fullCombinationOverVariables[varName];
			}
	}

	/* check parikh satisfiability based on relation between replaceall */
	std::map<Z3_ast, std::map<std::string, int>> min_parikhMap;
	std::map<Z3_ast, std::map<std::string, int>> fix_parikhMap;
	compute_parikh(t, allEqPossibilities, boolMapValues, min_parikhMap, fix_parikhMap);
	for (const auto& n : allEqPossibilities) {
		Z3_ast conflict = NULL;
		bool fine_contain = parikh_check_contain(t, n.first, n.second, boolMapValues, min_parikhMap, fix_parikhMap, conflict);
		if (!fine_contain) {
			assert(conflict != NULL);
			__debugPrint(logFile, "%d * %s * contain does not work\n", __LINE__, __FUNCTION__);
			addAxiom(t, negatePositiveEquality(t, n.first, n.second, boolMapValues), __LINE__, true);
			combinationOverVariables.clear();
			fullCombinationOverVariables.clear();
			return;
		}
	}

	for (const auto& n : allEqPossibilities) {
		bool fine_regex = parikh_check_regex(t, n.first, n.second, boolMapValues, min_parikhMap);
		if (!fine_regex) {
			__debugPrint(logFile, "%d * %s * regex does not work\n", __LINE__, __FUNCTION__);
			addAxiom(t, negatePositiveEquality(t, n.first, n.second, boolMapValues), __LINE__, true);
			combinationOverVariables.clear();
			fullCombinationOverVariables.clear();
			return;
		}
	}
}

/**
 * collect lengths of string variables
 */
std::map<std::string, int> collectCurrentLength(Z3_theory t){
	Z3_context ctx = Z3_theory_get_context(t);
	std::map<std::string, int> results;

	/* original variables */
	for (const auto& var : inputVarMap) {
		int length = getLenValue(t, var.first);
		if (length != -1) {
			results[std::string(Z3_ast_to_string(ctx, var.first))] = length;
		}
	}

	/* tmp variables */
	for (int i = 0; i < tmpStringVarCount; ++i) {
		std::string name = "$$_str" + std::to_string(i);
		Z3_ast varName = mk_str_var(t, name.c_str());
		int length = getLenValue(t, varName);
		if (length != -1) {
			results[name] = length;
		}
	}
	return results;
}

/*
 *
 */
bool formatOPInternal(StringOP &op){
	bool print = false;
//	if (op.toString().find("Indexof2 $$_str1") != std::string::npos) {
//		__debugPrint(logFile, "%d *** %s ***: %s; name = %s, args %ld\n", __LINE__, __FUNCTION__, op.toString().c_str(), op.name.c_str(), op.args.size());
//		for (unsigned i = 0; i < op.args.size(); ++i) {
//			__debugPrint(logFile, "%d name = %s, args = %ld\n", __LINE__, op.args[i].name.c_str(), op.args[i].args.size());
//		}
//		print = true;
//	}
	bool update = false;
	if (op.args.size() == 0){
		if (op.name.find("$$_") == 0) {
			if (internalVarFunctionMap.find(op) != internalVarFunctionMap.end()){
				op = internalVarFunctionMap[op];
				update = true;
			}
		}
	}
	else {
		for (unsigned i = 0; i < op.args.size(); ++i) {
			if (op.args[i].name.find("$$_") == 0){
				if (internalVarFunctionMap.find(op.args[i]) != internalVarFunctionMap.end()){
					op.args[i] = internalVarFunctionMap[op.args[i]];
					update = true;
				}
			}
			else if (op.args[i].args.size() > 0) {
				bool tmpUpdate = formatOPInternal(op.args[i]);
				update = update || tmpUpdate;
			}
		}
		formatOP(op);
	}

	if (print)
		__debugPrint(logFile, "%d %s \n", __LINE__, op.toString().c_str());
	return update;

}

/*
 * change each internal variable by corresponding function
 */
void reformatInternalVarFunctionMap(){
//	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	bool found = true;
	while (found){
		found = false;
		std::map<StringOP, StringOP> tmp = internalVarFunctionMap;
		for (const auto& var: tmp){
			StringOP tmpVar = var.second;
			found = found || formatOPInternal(tmpVar);
			internalVarFunctionMap[var.first] = tmpVar;
		}
		if (!found)
			break;
	}
}

/*
 * change each internal variable by corresponding function
 */
void reformatRewriterMap(std::map<StringOP, std::string> &rewriterMap){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	reformatInternalVarFunctionMap();
	std::map<StringOP, std::string> ret;
	for (const auto& op : rewriterMap){
		StringOP tmp = op.first;
		std::vector<StringOP> args = tmp.args;
		for (unsigned i = 0; i < args.size(); ++i) {
			formatOPInternal(args[i]);
		}
		tmp = StringOP(op.first.name, args);
		ret[tmp] = op.second;

	}
	for (const auto& s : ret) {
		__debugPrint(logFile, "%d >> %s\n", __LINE__, s.first.toString().c_str());
		rewriterMap[s.first] = s.second;
	}
}

/**
   \brief Callback: invoked before Z3 starts building a model.
   This callback can be used to perform expensive operations lazily.
 */
Z3_bool Th_final_check(Z3_theory t) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n\n\n");
	__debugPrint(logFile, "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
	__debugPrint(logFile, "                cb_final_check @ Level [%d] \n", sLevel);
	__debugPrint(logFile, "=============================================================\n");
#endif

	if (printingConstraints)
		done = true;

	calculateConcatLength(t);

	if (done) {
		__debugPrint(logFile, "%d Completed!\n", __LINE__);
		return Z3_TRUE;
	}

	if (checkDone(t))
		return Z3_TRUE;

	printf(".");
	//----------------------------------------------------------------------------------
	//run dependence analysis, find free string vars
	std::map<Z3_ast, int> varAppearInAssign;
	std::map<Z3_ast, int> freeVar_map;
	std::map<Z3_ast, std::set<Z3_ast> > membership;
	//  ctxDepAnalysis(t, varAppearInAssign, freeVar_map, membership);

	if (lengthDefined == false) {
		findVariableDomain();
		lengthDefined = true;
	}

	//**************************************************************
	// Create language for all variables that do not have a language
	//**************************************************************

	bool hasLanguage = true;
	if (languageDefined == false) {
		assignLanguage(t, hasLanguage);
		languageDefined = true;
	}

	Z3_context ctx = Z3_theory_get_context(t);
	if (hasLanguage == true) {
		/* doing under approximation */
		for (const auto& it : containPairBoolMap){
			__debugPrint(logFile, "\n %d containPairBoolMap: ", __LINE__);
			printZ3Node(t, it.second);
			__debugPrint(logFile, ": ");
			printZ3Node(t, it.first.first);
			__debugPrint(logFile, " contains ");
			printZ3Node(t, it.first.second);
			__debugPrint(logFile, "\n");
		}

		std::map<std::string, std::vector<std::vector<std::string>>> combinationOverVariables;
		std::map<std::string, std::vector<std::vector<std::string>>> fullCombinationOverVariables;
		collectCombinationOverVariables(t, combinationOverVariables, fullCombinationOverVariables);

		if (combinationOverVariables.size() == 0)
			return Z3_TRUE;

		std::map<StringOP, std::string> rewriterStrMap;
		std::set<std::string> carryOnConstraints;
		std::vector<Z3_ast> boolVars;

		collectDataInPositiveContext(t, boolVars, rewriterStrMap, carryOnConstraints);
		reformatRewriterMap(rewriterStrMap);

		for (const auto& elem : internalVarFunctionMap){
			__debugPrint(logFile, "%d internalVarFunctionMap \t%s: %s\n", __LINE__, elem.first.toString().c_str(), elem.second.toString().c_str());
		}

		for (const auto& elem : rewriterStrMap){
			StringOP op = elem.first;
			__debugPrint(logFile, "%d rewriterStrMap \t%s: %s\n", __LINE__, op.toString().c_str(), elem.second.c_str());
		}

		for (const auto& s : carryOnConstraints){
			__debugPrint(logFile, "%d carryOnConstraints: \t%s\n", __LINE__, s.c_str());
		}

		for (const auto& s : initLength){
			__debugPrint(logFile, "%d currentLength: \t%s : %d\n", __LINE__, s.first.c_str(), s.second);
		}

		skipUnderApprox = false;
		__debugPrint(logFile, "%d lengthEnable: %d\n", __LINE__, lengthEnable? 1: 0);
		if (containPairBoolMap.size() == 0 &&
			indexOfStrMap.size() == 0 &&
			indexOf2StrMap.size() == 0 &&
			lastIndexOfStrMap.size() == 0 &&
			endsWithStrMap.size() == 0 &&
			startsWithStrMap.size() == 0 &&
			replaceAllStrMap.size() == 0 &&
			replaceStrMap.size() == 0 &&
			lengthEnable == false &&
			skipOverapprox == false) {
			bool skipQuickSolver = false;
			for (const auto& n : rewriterStrMap)
				if (n.first.name.compare("=") == 0 && n.second.compare(TRUESTR) != 0)
					skipQuickSolver = true;
			__debugPrint(logFile, "%d skipQuickSolver: %d\n", __LINE__, skipQuickSolver? 1: 0);
			if (!skipQuickSolver) {
				updateLength(t);

				if (!assignedConcrete && assignConcreteValue(t)){
					__debugPrint(logFile, "%d Completed!\n", __LINE__);
					done = true;
					return Z3_TRUE;
				}
			}
		}


		if (!underapproxController(combinationOverVariables,
				fullCombinationOverVariables,
				rewriterStrMap,
				carryOnConstraints,
				initLength,
				inputFile)) {
			__debugPrint(logFile, "%d >> do not sat\n", __LINE__);
			/* create negation */
			std::vector<Z3_ast> orConstraints;
			for (std::map<Z3_ast, Z3_ast>::iterator it = grm_astNode_map.begin(); it != grm_astNode_map.end(); ++it) {
				std::string grm2str = Z3_ast_to_string(ctx, it->first);
				assert (combinationOverVariables.find(grm2str) != combinationOverVariables.end());
				std::vector<Z3_ast> eq_grm = getEqualValues(it->first);
				displayListNode(t, eq_grm, " ccc ");
				for (unsigned int i = 0; i < eq_grm.size(); ++i)
					if (isAutomatonFunc(t, eq_grm[i]))
						orConstraints.emplace_back(Z3_mk_not(ctx, Z3_mk_eq(ctx, it->first, eq_grm[i])));
			}

			__debugPrint(logFile, "%d boolVars: %ld, orConstraints: %ld, unknownResult: %d\n", __LINE__, boolVars.size(), orConstraints.size(), unknownResult == true ? 1 : 0);
			if (boolVars.size() == 0 && orConstraints.size() == 0 && unknownResult) {
				/* give up*/
				__debugPrint(logFile, "%d %s gives up\n", __LINE__, __FUNCTION__);
				return Z3_FALSE;
			}
			else {
				Z3_ast negation = negatePositiveContext(t, boolVars);
				orConstraints.emplace_back(negation);
				addAxiom(t, mk_or_fromVector(t, orConstraints), __LINE__, true);
			}
		}
		else {
			done = true;
			__debugPrint(logFile, "%d >> DONE!!!\n", __LINE__);
		}

#if 0
		/* find concreate values */
		if (!assignConcreteValue(t)) {
			addAxiom(t, Z3_mk_eq(ctx, mk_int(ctx, 0), mk_int(ctx, 1)), __LINE__, true);
		}
#endif
	}

	__debugPrint(logFile, "%d Finish\n", __LINE__);

	return Z3_TRUE;
}

/**
 * Done if
 * - Know lengths of all variables
 * - Know values  of all variables
 */
bool checkDone(Z3_theory t) {
	for (const auto& var : inputVarMap) {
		int length = getLenValue(t, var.first);
		if (length == -1) {
			__debugPrint(logFile, "Not done because of %d = ", length);
			printZ3Node(t, var.first);
			__debugPrint(logFile, "\n");
			return false;
		}
	}

	for (const auto& var : inputVarMap) {
		std::string value = getConstStrValue(t, var.first);
		std::vector<Z3_ast> eq = collect_eqc(t, var.first);
		bool haveConst = false;
		for (unsigned i = 0 ; i < eq.size(); ++i)
			if (isConstStr(t, eq[i])) {
				haveConst = true;
				break;
			}
		if (haveConst == false)
			return false;
	}
	return true;
}

/*
 * First, add all nodes to a set
 * Then convert set to a vector
 */
void updateLength(Z3_theory t) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n Update Length @ Level [%d]", sLevel);
	__debugPrint(logFile, "\n------------------------------------\n");
#endif
	std::vector<Z3_ast> updateNodes;
	std::set<Z3_ast> tmpSet;
	Z3_context ctx = Z3_theory_get_context(t);

	// update length for concat node
	for (const auto& node : concat_astNode_map){
		int len = getLenValue(t, node.second);
		if (len != -1) {
			tmpSet.insert(node.second);
			length_LanguageMap[std::make_pair(node.second, sLevel)] = std::make_pair(len, len);
		}

		// check their components
		Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node.second), 0);
		Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node.second), 1);
		len = getLenValue(t, arg0);
		if (len != -1) {
			tmpSet.insert(arg0);
			length_LanguageMap[std::make_pair(arg0, sLevel)] = std::make_pair(len, len);
		}

		len = getLenValue(t, arg1);
		if (len != -1) {
			tmpSet.insert(arg1);
			length_LanguageMap[std::make_pair(arg1, sLevel)] = std::make_pair(len, len);
		}
	}

	updateNodes.assign(tmpSet.begin(), tmpSet.end());

	doLengthPropagation(t, updateNodes);
	__debugPrint(logFile, "%d %s leaving\n", __LINE__, __FUNCTION__);
}

/*
 *
 */
void calculateConcatLength(Z3_theory t){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n\n\n");
	__debugPrint(logFile, "                calculateConcatLength @ Level [%d] \n", sLevel);
	__debugPrint(logFile, "=============================================================\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
#ifdef ARITH
	for (const auto& node : concat_astNode_map){
		int len01 = getLenValue(t, node.first.first);
		int len02 = getLenValue(t, node.first.second);
		int len = getLenValue(t, node.second);

		/*
		 * known values of components -> value of contat
		 */
		if (len01 != -1 && len02 != -1 && len == -1) {
			Z3_ast* and_items = new Z3_ast[2];
			and_items[0] = Z3_mk_eq(ctx, getLengthAST(t, node.first.first), mk_int(ctx, len01));
			and_items[1] = Z3_mk_eq(ctx, getLengthAST(t, node.first.second), mk_int(ctx, len02));
			addAxiom(t, Z3_mk_implies(ctx, Z3_mk_and(ctx, 2, and_items), Z3_mk_eq(ctx, getLengthAST(t, node.second), mk_int(ctx, len01 + len02))), __LINE__, true);
		}

		/*
		 * known ONE value of component and value of contat --> value of other
		 */
		if (len01 == -1 && len02 != -1 && len != -1) {
			Z3_ast* and_items = new Z3_ast[2];
			and_items[0] = Z3_mk_eq(ctx, getLengthAST(t, node.first.second), mk_int(ctx, len02));
			and_items[1] = Z3_mk_eq(ctx, getLengthAST(t, node.second), mk_int(ctx, len));
			addAxiom(t, Z3_mk_implies(ctx, Z3_mk_and(ctx, 2, and_items), Z3_mk_eq(ctx, getLengthAST(t, node.first.first), mk_int(ctx, len - len02))), __LINE__, true);
		}


		if (len01 != -1 && len02 == -1 && len != -1) {
			Z3_ast* and_items = new Z3_ast[2];
			and_items[0] = Z3_mk_eq(ctx, getLengthAST(t, node.first.first), mk_int(ctx, len01));
			and_items[1] = Z3_mk_eq(ctx, getLengthAST(t, node.second), mk_int(ctx, len));
			addAxiom(t, Z3_mk_implies(ctx, Z3_mk_and(ctx, 2, and_items), Z3_mk_eq(ctx, getLengthAST(t, node.first.second), mk_int(ctx, len - len01))), __LINE__, true);
		}
	}
#endif
}

/*
 *
 */
bool hasLanguageConstraints(Z3_theory t, Z3_ast node) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n Collecting parents @ Level [%d]: ", sLevel);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n------------------------------------\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);

	// BFS
	std::set<Z3_ast> parents = collectAllParents(t, node);
	parents.insert(node);
	std::vector<Z3_ast> checkingNode;
	for (const auto& node : parents)
		if (!isLengthFunc(t, node))
			checkingNode.emplace_back(node);

	std::map<Z3_ast, bool>  visited;
	for (unsigned int i = 0; i < checkingNode.size(); ++i)
		visited[checkingNode[i]] = false;

	unsigned int pos = 0;
	while(pos < checkingNode.size()) {
		Z3_ast currentNode = checkingNode[pos];
		printZ3Node(t, currentNode);
		__debugPrint(logFile, "\n");

		if (isStrVariable(t, currentNode) || isConcatFunc(t, currentNode)) {
			std::vector<Z3_ast> eq_nodes = getEqualValues(currentNode);
			for (unsigned int i = 0; i < eq_nodes.size(); ++i)
				if (visited.find(eq_nodes[i]) == visited.end() || visited[eq_nodes[i]] == true){

					if (isConcatFunc(t, eq_nodes[i])) {
						if (visited.find(eq_nodes[i]) == visited.end()) {
							checkingNode.emplace_back(eq_nodes[i]);
							visited[eq_nodes[i]] = true;
						}
						// collect lower levels
						Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq_nodes[i]), 0);
						if (visited.find(arg0) == visited.end()) {
							checkingNode.emplace_back(arg0);
							visited[arg0] = true;
						}

						// collect lower levels
						Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, eq_nodes[i]), 1);
						if (visited.find(arg1) == visited.end()) {
							checkingNode.emplace_back(arg1);
							visited[arg1] = true;
						}

					}
					else if (isAutomatonFunc(t, eq_nodes[i])) {
						return true;
					}
					else if (isStrVariable(t, eq_nodes[i]) && visited.find(eq_nodes[i]) == visited.end()) {
						// for visiting parents
						checkingNode.emplace_back(eq_nodes[i]);
						visited[eq_nodes[i]] = true;
					}
				}

			// collect higher levels
			if (eq_nodes.size() > 0)
				parents = collectAllParents(t, eq_nodes[0]);
			for (std::set<Z3_ast>::iterator it = parents.begin(); it != parents.end(); ++it)
				if (visited.find(*it) == visited.end() && !isLengthFunc(t, *it)) {
					checkingNode.emplace_back(*it);
					visited[*it] = false;
				}
		}
		else if (isAutomatonFunc(t, currentNode))
			return true;
		pos++;
	}
	__debugPrint(logFile, "NO CONSTRAINT FOR LENGTH\n");
	return false;
}

/*
 * get length domain of a variable
 */
std::pair<int, int> getLengthDomain(Z3_ast node) {
	for (int i = sLevel; i >= 0; --i) {
		std::pair<Z3_ast, int> tmp = std::make_pair(node, i);
		if (length_LanguageMap.find(tmp) != length_LanguageMap.end())
			return length_LanguageMap[tmp];
	}

	return std::make_pair(-1, -1);
}

/*
 *
 */
void assignLanguage(Z3_theory t, bool &hasLanguage){
	Z3_context ctx = Z3_theory_get_context(t);
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n------------------------------------\n");
	__debugPrint(logFile, "\n assignLanguage @ Level [%d]: ", sLevel);
	__debugPrint(logFile, "\n------------------------------------\n");
	__debugPrint(logFile, "%d charset size: %ld\n", __LINE__, charSet.size());
#endif

	std::vector<Z3_ast> tmpVector;

	// step 1: collect set of all variables without constraints
	for (const auto& var: inputVarMap)
		if (!hasConstraintOverVar(t, var.first)) {
			if (isStrVariable(t, var.first)) {
				tmpVector.emplace_back(var.first);
			}
		}

//	for (const auto& var: internalStrVars){
//		if (!hasConstraintOverVar(t, var)) {
//			if (isStrVariable(t, var)) {
//				tmpVector.emplace_back(var);
//			}
//		}
//	}

	displayListNode(t, tmpVector, "List of variables to assign language");

	if (tmpVector.size() > 50)
		return;

	// step 2: if (A == B) then only create language for variable A
	std::map<Z3_ast, bool> tmpMap;
	for (const auto& node : tmpVector)
		if (tmpMap.find(node) == tmpMap.end()){
			std::vector<Z3_ast> equalToNode = getEqualValues(node);
			for (unsigned int j = 0; j < equalToNode.size(); ++j)
				tmpMap[equalToNode[j]] = true;

			hasLanguage = false;
			std::string varName = std::string(Z3_ast_to_string(ctx, node));

			std::string language = createGenericLanguage(t, node);
			Z3_ast langAxiom = createLanguageAxiom(t, node, language);
			addAxiom(t, langAxiom, __LINE__,true);

			consideredVars.emplace_back(node);
		}
}

/*
 *
 */
bool assignConcreteValue(Z3_theory t){
	//**************************************************************
	// Select leaves
	// only taking care of concat --> get their values first
	// the dependence between nodes are flexible because of conditional statements, we cannot do this step at the beginning
	//**************************************************************
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	assignedConcrete = true;
	std::set<Z3_ast> rootConcat;

	// 1. Collect all children
	std::set<Z3_ast> allChildren;
	for (const auto& node : concat_astNode_map)
		if (allChildren.find(node.second) == allChildren.end()){
			std::set<Z3_ast> list;

			getNodesInConcat_extended(t, node.second, list);
			for (const auto& n : list)
				if (n != node.second)
					allChildren.insert(n);

			assert(allChildren.find(node.second) == allChildren.end());
		}

	for (const auto& n : concat_astNode_map) {
		if (allChildren.find(n.second) == allChildren.end()){
			rootConcat.emplace(n.second);
		}
	}

	__debugPrint(logFile, "\n\n%d Roots list\n", __LINE__);
	displayListNode(t, rootConcat);

	//**************************************************************
	// Create concrete values for all leaves
	//**************************************************************
	std::map<Z3_ast, std::string> str_values;
	std::map<Z3_ast, int> len_values;

	__debugPrint(logFile,
			"/**************************************************************/\n"
			"Leave num %d of %ld\n"
			"/**************************************************************/"
			"\n", leavePos, rootConcat.size());

	if (rootConcat.size() > 0)
		initialize(t, str_values, len_values);

	Z3_context ctx = Z3_theory_get_context(t);
	for (const auto& n : len_values)
		__debugPrint(logFile, "%d %s: %d\n", __LINE__, Z3_ast_to_string(ctx, n.first), n.second);

	if (determindConcat(t, rootConcat, str_values, len_values)){
		if (assignOtherValue(t, str_values, len_values)){
			std::vector<Z3_ast> assertList;
			for (const auto& s : str_values){
				assertList.emplace_back(axiom_FinalValue(t, s.first, s.second));
			}
			addAxiom(t, mk_and_fromVector(t, assertList), __LINE__, true);
		}
		else
			return false;
		skipUnderApprox = true;
	}
	else {
		return false;
	}
	return true;
}

/*
 * Get value for variables that do not have relation with others
 */
bool assignOtherValue(
		Z3_theory t,
		std::map<Z3_ast, std::string> &str_values,
		std::map<Z3_ast, int> &len_values){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n------------------------------------\n");
	__debugPrint(logFile, "\n assignOtherValue @ Level [%d]: ", sLevel);
	__debugPrint(logFile, "\n------------------------------------\n");
#endif
	const int MAXRANGE = 30;
	for (std::map<Z3_ast, int>::iterator it = inputVarMap.begin(); it != inputVarMap.end(); ++it){
		if (!relatedToConcat(t, it->first)){
			Automaton ton = getPreCalculatedValue(t, it->first);
			int length = getLenValue(t, it->first);
			printZ3Node(t, it->first);
			__debugPrint(logFile, " (%d) %d\n", __LINE__, length);

			if (length < 0)
				length = 0;

			std::set<std::string> values = ton.createStringWithLengthRange(length, length + MAXRANGE);
			if (values.size() > 0) {
				str_values[it->first] = *values.begin();
			}
			else {
				__debugPrint(logFile, "Cannot get value with length = (%d %d) of ", length, length + MAXRANGE);
				printZ3Node(t, it->first);
				__debugPrint(logFile, "\n");
				return false;
			}
		}
	}
	return true;
}
/*
 *
 */
bool guessLanguage(Z3_theory t, Z3_ast node) {
	Automaton ton = getPreCalculatedValue(t, node);
	std::string frame = ton.getFrame();

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n------------------------------------\n");
	__debugPrint(logFile, "\n Guess Language @ Level [%d]: ", sLevel);
	printZ3Node(t, node);
	__debugPrint(logFile, ": frame = \"%s\" \n------------------------------------\n", frame.c_str());
#endif

	std::vector<std::string> flats;
	if (frame.length() > 0)
		for (int i = 1; i <= QMAX; ++i) { // number of flats
			if (canSplit(i, PMAX, 0, frame, flats)){
				break;
			}
			flats.clear();
		}
	else {
		Z3_context ctx = Z3_theory_get_context(t);
		std::set<char> subCharSet = charSet[Z3_ast_to_string(ctx, node)];

		if (subCharSet.size() == 0)
			subCharSet.insert('a');
		std::string tmp("");
		for (std::set<char>::iterator it = subCharSet.begin(); it != subCharSet.end(); ++it) {
			tmp = tmp + *it;
			break;
		}

		__debugPrint(logFile, "TMP = %s\n", tmp.c_str());
		flats.emplace_back(tmp);
	}

	if (flats.size() > 0) {
		displayListString(flats, "Set of flats:");
		__debugPrint(logFile, "%d Set of flats\n", __LINE__)
		// add new language
		std::string newLanguage = "";
		for (unsigned int i = 0; i < flats.size(); ++i)
			newLanguage = newLanguage + "(" + flats[i] + ")*";

		Z3_ast langAxiom = createLanguageAxiom(t, node, newLanguage);
		addAxiom(t, langAxiom, __LINE__,true);
		return true;
	}
	else {
		__debugPrint(logFile, "Cannot guest language with bound = (%d, %d)\n", PMAX, QMAX);
		return false;
	}
}

/*
 *
 */
bool canSplit(int boundedFlat, int boundSize, int pos, std::string frame, std::vector<std::string> &flats) {
	if ((int)flats.size() == boundedFlat)
		return false;

	for (int size = 1; size <= boundSize; ++size) { // size of a flat
		std::string flat = frame.substr(pos, size);
		flats.emplace_back(flat); // add to stack
		int tmpPos = pos + size;

		while (true) {
			std::string nextIteration = frame.substr(tmpPos, size);
			if (nextIteration.compare(flat) != 0)
				break;
			else if (tmpPos < (int)frame.length() && tmpPos + size <= (int)frame.length()){
				tmpPos += size;
			}
			else
				break;
		}
		if (tmpPos < (int)frame.length()){
			if (canSplit(boundedFlat, boundSize, tmpPos, frame, flats))
				return true;
			else {
				// de-stack
				flats.pop_back();
			}
		}
		else {
			return true;
		}
	}
	return false;
}

/**
 *
 */
bool matchAutomaton(
		Z3_theory t,
		Z3_ast node,
		std::string value){
	Automaton ton = getPreCalculatedValue(t, node);
	return ton.match(value);
}

/*
 *
 */
void splitValueForConcat(
		Z3_theory t,
		std::vector<Z3_ast> list,
		std::string value,
		int pos,
		std::map<Z3_ast, std::string> str_values,
		std::map<Z3_ast, int> len_values,
		std::map<Z3_ast, std::string> &assignments,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***: at %d / %s, list size = %ld\n", __LINE__, __FUNCTION__, pos, value.c_str(), list.size());
	if (pos == (int) list.size()) {
		if (value.length() == 0) {
			completion = true;
		}
		return;
	}
	int leng = -1;

	/* know value */
	if (str_values.find(list[pos]) != str_values.end()){
		leng = str_values[list[pos]].length();
		if (leng > (int)value.length()) {
			return;
		}
		std::string tmp = value.substr(0, leng);
		if (tmp.compare(str_values[list[pos]]) != 0) {
			return;
		}
		else {
			if (assignments.find(list[pos]) != assignments.end() &&
					assignments[list[pos]].compare(str_values[list[pos]]) != 0)
				return;

			assignments[list[pos]] = str_values[list[pos]];
			splitValueForConcat(t, list, value.substr(leng), pos + 1, str_values, len_values, assignments, completion);
			if (completion)
				return;
			assignments.erase(list[pos]);
		}
	}

	/* know length */
	else if (len_values.find(list[pos]) != len_values.end()){
		leng = len_values[list[pos]];
		if (leng > (int)value.length())
			return;
		std::string tmp = value.substr(0, leng);

		if (assignments.find(list[pos]) != assignments.end() &&
						assignments[list[pos]].compare(tmp) != 0)
					return;

		if (matchAutomaton(t, list[pos], tmp)){
			assignments[list[pos]] = tmp;
			splitValueForConcat(t, list, value.substr(leng), pos + 1, str_values, len_values, assignments, completion);

			if (completion)
				return;
			assignments.erase(list[pos]);
		}
	}

	/* take all remaining string */
	else if (pos == (int)list.size() - 1) {
		__debugPrint(logFile, "%d matchAutomaton %s at %d\n", __LINE__, value.c_str(), pos);

		if (assignments.find(list[pos]) != assignments.end() &&
				assignments[list[pos]].compare(value) != 0)
			return;

		if (matchAutomaton(t, list[pos], value)){
			__debugPrint(logFile, "%d matched %s \n", __LINE__, value.c_str());
			assignments[list[pos]] = value;

			splitValueForConcat(t, list, "", pos + 1, str_values, len_values, assignments, completion);
			if (completion)
				return;
			assignments.erase(list[pos]);
		}
	}

	else for (unsigned i = 0; i <= value.size(); ++i){
		std::string tmp = value.substr(0, i);
		__debugPrint(logFile, "%d matchAutomaton %s at %d\n", __LINE__, tmp.c_str(), pos);

		if (assignments.find(list[pos]) != assignments.end() &&
				assignments[list[pos]].compare(tmp) != 0)
			continue;

		if (matchAutomaton(t, list[pos], tmp)){
			__debugPrint(logFile, "%d matched %s \n", __LINE__, tmp.c_str());
			assignments[list[pos]] = tmp;
			assert(tmp.length() + value.substr(i).length() == value.length());

			splitValueForConcat(t, list, value.substr(i), pos + 1, str_values, len_values, assignments, completion);
			if (completion)
				return;
			assignments.erase(list[pos]);
		}

	}
}

/*
 *
 */
bool splitValueForConcat(
		Z3_theory t,
		std::vector<Z3_ast> list,
		std::string value,
		std::map<Z3_ast, std::string> &str_values,
		std::map<Z3_ast, int> &len_values){
	std::map<Z3_ast, std::string> assignments;
	bool completion = false;
	splitValueForConcat(t, list, value, 0, str_values, len_values, assignments, completion);

	if (!completion)
		return false;
	else {
		/* check if they have been updated */
		bool updated = true;
		for (const auto& n : list) {
			assert(assignments.find(n) != assignments.end());
			if (str_values.find(n) !=str_values.end() && len_values.find(n) != len_values.end()) {
				if (str_values[n].compare(assignments[n]) != 0) {
					updated = false;
					break;
				}
			}
			else {
				updated = false;
				break;
			}

		}

		if (updated) {
			__debugPrint(logFile, "%d %s skip updating\n", __LINE__, __FUNCTION__);
			return true;
		}

		for (const auto& n : list) {
			update_constValue(t, n, assignments[n], str_values, len_values, __LINE__);
		}

		for (const auto& n : list){
			std::vector<Z3_ast> eq = collect_eqc(t, n);
			for (const auto& nn : eq)
				if (isConcatFunc(t, nn)){
					if (!splitValueForConcat(t, nn, assignments[n], str_values, len_values))
						return false;
				}
		}
	}
	return true;
}

/*
 *
 */
bool splitValueForConcat(
		Z3_theory t,
		Z3_ast node,
		std::string value,
		std::map<Z3_ast, std::string> &str_values,
		std::map<Z3_ast, int> &len_values){
	__debugPrint(logFile, "%d *** %s ***", __LINE__, __FUNCTION__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");

	std::vector<Z3_ast> list;
	collect_node_in_concat(t, node, list);
	return splitValueForConcat(t, list, value, str_values, len_values);
}

/*
 *
 */
bool determindConcat(
		Z3_theory t,
		std::set<Z3_ast> leaves_list,
		std::map<Z3_ast, std::string> &str_values,
		std::map<Z3_ast, int> &len_values){

	__debugPrint(logFile, "leavesList.size = %ld\n", leaves_list.size());

	for (const auto& node : leaves_list) {
		if (isConcatFunc(t, node)) {
			// 1. get args
			std::vector<Z3_ast> listNode;
			collect_node_in_concat(t, node, listNode);

#ifdef DEBUGLOG
			__debugPrint(logFile, "\n------------------------------------\n");
			__debugPrint(logFile, "\n DetermindConcat @ Level [%d]: ", sLevel);
			printZ3Node(t, node);
			__debugPrint(logFile, "\n------------------------------------\n");
#endif

			// 2. values is determined?
			std::vector<Z3_ast> list;
			collect_node_in_concat(t, node, list);
			std::string tmpValue = "";
			bool found = true;
			for (const auto& n : list) {
				if (str_values.find(n) != str_values.end()) {
					tmpValue = tmpValue + str_values[n];
				}
				else
					found = false;
			}
			if (found == true) {
				if (str_values.find(node) != str_values.end()) {
					if (str_values[node].compare(tmpValue) != 0)
						return false;
				}
				else
					str_values[node] = tmpValue;
				return true;
			}

			// 3. size is determined?
			std::pair<int, int> lengthRange = getLengthRange(t, node, len_values);
			if (len_values.find(node) != len_values.end())
				lengthRange = std::make_pair(len_values[node], len_values[node]);

			__debugPrint(logFile, "\n %d lengthRange: %d to %d \n",  __LINE__, lengthRange.first, lengthRange.second);
			if (lengthRange.first > lengthRange.second && lengthRange.second != -1)
				return false;

			// 4. get all possible values
			std::set<std::string> values_list;
			if (str_values.find(node) != str_values.end())
				values_list.insert(str_values[node]);
			else {
				Automaton ton = getPreCalculatedValue(t, node);

				values_list = ton.createStringWithLengthRange(lengthRange.first, lengthRange.second);
				__debugPrint(logFile, "%d Number of possible values (%d-%d): %d\n", __LINE__, lengthRange.first, lengthRange.second, (int)values_list.size());
				if (values_list.size() == 0) {
					__debugPrint(logFile, "%d %s\n", __LINE__, ton.toString(true).c_str());
					return false;
				}
			}

			displayListString(values_list, "List of values");
			assert(values_list.size() <= 2);

			// 5. split values
			for (std::set<std::string>::iterator it = values_list.begin(); it != values_list.end(); ++it) {
				// 5.0. update itself and his friends
				update_constValue(t, node, *it, str_values, len_values, __LINE__);

				// 5.0.1. update list of concat nodes to extend
				std::vector<Z3_ast> eqOfNode = collect_eqc(t, node);
				for (const auto _n : eqOfNode) {
					if (isConcatFunc(t, _n)) {
						bool completion = splitValueForConcat(t, _n, *it, str_values, len_values);
						if (!completion){
							__debugPrint(logFile, "%d Cannot splitValueForConcat: ", __LINE__);
							printZ3Node(t, _n);
							__debugPrint(logFile, "\n");
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

/*
 *
 */
bool initialize(Z3_theory t, std::map<Z3_ast, std::string> &str_values,  std::map<Z3_ast, int> &len_values) {
	std::map<Z3_ast, bool> handled;
	for (const auto& node : concat_astNode_map){
		initializeNode(t, node.second, str_values, len_values, handled);
		std::vector<Z3_ast> children;
		getAllNodesInConcat(t, node.second, children);


		for (unsigned i = 0; i < children.size(); ++i) {
			if (handled[children[i]] == false){
				initializeNode(t, children[i], str_values, len_values, handled);
			}
		}
	}
	return true;
}

/*
 *
 */
bool initializeNode(Z3_theory t, Z3_ast node, std::map<Z3_ast, std::string> &str_values,  std::map<Z3_ast, int> &len_values, std::map<Z3_ast, bool> &handled) {
	Z3_context ctx = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, Z3_ast_to_string(ctx, node));

	std::vector<Z3_ast> eq = collect_eqc(t, node);
	for (unsigned i = 0; i < eq.size(); ++i) {
		handled[eq[i]] = true;
	}

	Automaton ton = getPreCalculatedValue(t, node);
	if (ton.isConst()) {
		std::string tmp = ton.getConst();
		for (unsigned i = 0; i < eq.size(); ++i) {
			str_values[eq[i]] = tmp;
			len_values[eq[i]] = tmp.length();
		}
	}
	else {
		int len = -1;
		for (unsigned i = 0; i < eq.size(); ++i) {
			int tmpLen = getLenValue(t, eq[i]);
			if (tmpLen != -1) {
				if (tmpLen != len && len != -1)
					return false;
				else
					len = tmpLen;
			}
		}

		if (len != -1)
			for (unsigned i = 0; i < eq.size(); ++i) {
				len_values[eq[i]] = len;
			}
	}
	return true;
}

/*
 *
 */
void update_constValue(Z3_theory t,
		Z3_ast node,
		std::string value,
		std::map<Z3_ast, std::string> &str_values,
		std::map<Z3_ast, int> &len_values,
		int line){
	printZ3Node(t, node);
	__debugPrint(logFile, ": update value from %d: \"%s\"\n\n", line, value.c_str());
	std::vector<Z3_ast> eq = collect_eqc(t, node);
	// 1. update values for all equals nodes
	for (unsigned i = 0; i < eq.size(); ++i)
		str_values[eq[i]] = value;

	// 2. update length for all equals nodes
	for (unsigned i = 0; i < eq.size(); ++i)
		len_values[eq[i]] = value.length();
}

/*
 * if length is defined --> return it
 * if there are no equivalent values --> return max length
 *
 */
std::pair<int, int> getLengthRange(Z3_theory t, Z3_ast node, std::map<Z3_ast, int> len_values){
	Z3_context ctx = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d *** %s ***: %s", __LINE__, __FUNCTION__, Z3_ast_to_string(ctx, node));
	std::pair<int, int> domain = getLengthDomain(node);
	if (domain.first < 0)
		domain.first = 0;
	if (domain.second < 0)
		domain.second = domain.first + PMAX * QMAX;
	return domain;

	if (len_values.find(node) != len_values.end())
		return std::make_pair(len_values[node], len_values[node]);

	std::vector<Z3_ast> eq = collect_eqc(t, node);
	if (eq.size() == 0)
		return std::make_pair(0, PMAX * QMAX);

	// do not get the const result
	int minLen = -1, maxLen = -1;
	for (unsigned k = 0; k < eq.size(); ++k)
		if (isConcatFunc(t, eq[k])){
			int tmpMinLen = 0, tmpMaxLen = 0;

			std::vector<Z3_ast> concat_children;
			getNodesInConcat(t, eq[k], concat_children);
			for (unsigned j = 0; j < concat_children.size(); ++j)
				if (concat_children[j] != eq[k]) {
					std::pair<int, int> tmpLen = getLengthRange(t, concat_children[j], len_values);

					tmpMinLen += tmpLen.first;
					tmpMaxLen += tmpLen.second;
				}

			minLen = minLen > tmpMinLen ? minLen : tmpMinLen;
			maxLen = maxLen > tmpMaxLen ? maxLen : tmpMaxLen;
		}
	if (maxLen == -1)
		return std::make_pair(0, PMAX * QMAX);
	else
		return std::make_pair(minLen, maxLen);
}

/*
 *
 */
Z3_ast axiom_FinalValue(Z3_theory t, Z3_ast node, std::string value){
	Z3_context ctx = Z3_theory_get_context(t);
	finalValues[node] = value;
	Z3_ast constStr = mk_str_value(t, value.c_str());

	Z3_ast axiomToAdd01 = Z3_mk_eq(ctx, node, constStr);

	__debugPrint(logFile, "%d (assert (= %s \"%s\"))\n", __LINE__, Z3_ast_to_string(ctx, node), value.c_str());

	return axiomToAdd01;
}

/*
 *
 */
void assignFinalValues(Z3_theory t, std::map<Z3_ast, std::string> str_values, std::vector<Z3_ast> &axiomToAdd) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n------------------------------------\n");
	__debugPrint(logFile, "\n AssignFinalValues @ Level [%d]: ", sLevel);
	__debugPrint(logFile, "\n------------------------------------\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	int cnt = 0;
	std::vector<Z3_ast> andAxiomToAdd;
	for (const auto& node : inputVarMap){
		cnt++;
		if (str_values.find(node.first) != str_values.end()) {
			std::string prefix_var;// = std::string(Z3_ast_to_string(ctx, itor->first)) + "_FiNaL_";
			std::string value = prefix_var + str_values[node.first];

			Z3_ast axiomToAdd01 = axiom_FinalValue(t, node.first, value);
			andAxiomToAdd.emplace_back(axiomToAdd01);
			andAxiomToAdd.emplace_back(Z3_mk_eq(ctx, mk_length(t, node.first), mk_int(ctx, value.length())));
		}
	}
	if (andAxiomToAdd.size() > 0)
		axiomToAdd.emplace_back(mk_and_fromVector(t, andAxiomToAdd));
}

/*
 *
 */
void assignFinalValues(Z3_theory t) {
	Z3_context ctx = Z3_theory_get_context(t);
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d Assign final value: %s", __LINE__, __FILE__);
	__debugPrint(logFile, "\n");
#endif
	for (const auto& var : inputVarMap){
		if (final_value_Map.find(var.first) != final_value_Map.end()) {
			std::string prefix_var = "$$" + std::string(Z3_ast_to_string(ctx, var.first)) + "_" + std::to_string(sLevel) + "!!";
			std::string value = prefix_var + std::string(Z3_ast_to_string(ctx, final_value_Map[var.first]));
			value = customizeString(value);
			if (value[value.size() - 1] == ')')
				value = value.substr(0, value.length() - 1);
			addAxiom(t, Z3_mk_eq(ctx, var.first, mk_str_value(t, value.c_str())), __LINE__, true);
		}
	}
}

/*
 *
 */
Z3_ast createLanguageAxiom(Z3_theory t, Z3_ast node, std::set<std::string> list){
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at %s Create Language Axiom: ", __LINE__, __FILE__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	std::string prefix_var = "$$" + std::string(Z3_ast_to_string(ctx, node)) + "!!";

	int pos = 1;
	std::vector<Z3_ast> or_List;
	std::vector<Z3_ast> and_List;


	for (const auto& str : list) {
		Z3_ast langNode = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, (prefix_var + str).c_str()));

		if (string_automaton_Map.find(str) == string_automaton_Map.end()) {
			// create automata
			RegEx re;
			re.Compile(str);
			string_automaton_Map[str] = re.CreateAutomaton("known");
		}
		internalVarMap[std::make_pair(langNode, 0)] = string_automaton_Map[str];

		or_List.emplace_back(Z3_mk_eq(ctx, mk_int_var(ctx, (PRE_LANGUAGE + std::string(Z3_ast_to_string(ctx, node))).c_str()), mk_int(ctx, pos)));

		std::vector<Z3_ast> parikh;// = basicArithConstraints_forNode_simple(t, langNode);
		std::vector<Z3_ast> parikhSimpleLanguage;
		std::vector<Z3_ast> list01;// = basicArithConstraints_forEqual(t, node, langNode);

#ifdef ARITH
		parikh.insert(parikh.end(), list01.begin(), list01.end());
#ifdef PARIKH1
		// TODO do not understand

		//		if (std::string(Z3_ast_to_string(ctx, node)).compare("y1") != 0 || cnt++ < 3)
		{

			parikhSimpleLanguage = createParikhConstraints_evenSimplerLanguage(t, langNode, *it);
			if (parikhSimpleLanguage.size() > 0)
				and_List.emplace_back(mk_and_fromVector(t, parikhSimpleLanguage));
		}
#endif

#endif
		and_List.emplace_back(Z3_mk_eq(ctx, or_List[or_List.size() - 1], Z3_mk_eq(ctx, node, langNode)));

		language_Map[node].emplace_back(langNode);

		pos++;
	}

	// range for number of cases
	and_List.emplace_back(Z3_mk_ge(ctx, mk_int_var(ctx, (PRE_LANGUAGE + std::string(Z3_ast_to_string(ctx, node))).c_str()), mk_int(ctx, 1)));
	and_List.emplace_back(Z3_mk_le(ctx, mk_int_var(ctx, (PRE_LANGUAGE + std::string(Z3_ast_to_string(ctx, node))).c_str()), mk_int(ctx, list.size())));

	assert(and_List.size() > 0);

	return mk_and_fromVector(t, and_List);
}

/*
 *
 */
Z3_ast createLanguageAxiom(Z3_theory t, Z3_ast node, std::string language){
#ifdef DEBUGLOG
	__debugPrint(logFile, "\n>> @%d at %s *** %s ***: ", __LINE__, __FILE__, __FUNCTION__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	std::string prefix_var = "$$" + std::string(Z3_ast_to_string(ctx, node)) + "_" + std::to_string(sLevel) + "!!";

	Z3_ast langNode = mk_binary_app(ctx, td->NonDet_AutomataDef, mk_str_value(t, (prefix_var + language).c_str()), mk_int(ctx, nondeterministicCounter++));

	if (string_automaton_Map.find(language) == string_automaton_Map.end()) {
		// create automata
		RegEx re;
		re.Compile(language);
		string_automaton_Map[language] = re.CreateAutomaton("known");

#ifdef DEBUGLOG
		__debugPrint(logFile, "@%d Finish * %s *: %s\n", __LINE__, __FUNCTION__, language.c_str());
#endif
	}
	internalVarMap[std::make_pair(langNode, 0)] = string_automaton_Map[language];

	return Z3_mk_eq(ctx, node, langNode);
}

/*
 * Create concrete values
 */
std::vector<Z3_ast> createValueAxiom(Z3_theory t, Z3_ast node) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d at %s Create Value Axiom: ", __LINE__, __FILE__);
	printZ3Node(t, node);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	Automaton ton_var = getPreCalculatedValue(t, node);
	std::set<std::string> list;
	int nodeLen = getLenValue(t, node);

	if (nodeLen >= 0) {
		list = ton_var.createStringFixedLength(nodeLen);
	}
	else
		list = ton_var.createStringUpToLength(STR_LEN);

	std::vector<Z3_ast> and_List;
	if (list.size() > 0) {
		// prefix of automaton var
		std::string prefix_var = "$$" + std::string(Z3_ast_to_string(ctx, node)) + "!!";

		std::vector<Z3_ast> or_List;

		int pos = 1;
		for (std::set<std::string>::iterator it = list.begin(); it != list.end(); ++it) {
			Z3_ast valueNode = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, (prefix_var + *it).c_str()));
			pos = getConcreteValue_variable(t, node, valueNode);
			or_List.emplace_back(Z3_mk_eq(ctx, mk_int_var(ctx, (PRE_VALUE + std::string(Z3_ast_to_string(ctx, node))).c_str()), mk_int(ctx, pos)));

#ifdef ARITH
			std::vector<Z3_ast> parikh;
#ifdef PARIKH1
			parikh = createParikhConstraints_string(t, valueNode, *it);
#else
			parikh.emplace_back(Z3_mk_eq(ctx, getLengthAST(t, valueNode), mk_int(ctx, ((std::string)*(it)).size())));
#endif
			assert(parikh.size() > 0);
			//			and_List.emplace_back(Z3_mk_implies(ctx, or_List[or_List.size() - 1], mk_and_fromVector(t, parikh)));
			and_List.emplace_back(mk_and_fromVector(t, parikh));
#endif
			and_List.emplace_back(Z3_mk_eq(ctx, or_List[or_List.size() - 1], Z3_mk_eq(ctx, node, concrete_value_Map[node][pos - 1])));



			// TODO remove
			//			if (std::string(Z3_ast_to_string(ctx, node)).compare("y1") == 0)
			//				break;
		}

		assert(or_List.size() > 0);
		and_List.emplace_back(mk_or_fromVector(t, or_List));
	}
	return and_List;
}

/*
 *
 */
int getConcreteValue_variable(Z3_theory t, Z3_ast node, Z3_ast value){
	std::vector<Z3_ast> values = concrete_value_Map[node];
	for (unsigned i = 0; i < values.size(); ++i){
		if (values[i] == value)
			return i + 1;
	}
	values.emplace_back(value);
	concrete_value_Map[node] = values;
	return values.size();
}

/*
 *
 */
Z3_ast negatedConstraint(Z3_theory t) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d *** %s *** Negated Constraints: ", __LINE__, __FUNCTION__);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> str = collectStringValue(t);
	std::vector<Z3_ast> lang = collectLanguageValue(t);

	if (str.size() == 0) {
		if (lang.size() <= 0) {
			__debugPrint(logFile, "@%d at %s Something go wrong.\n ", __LINE__, __FUNCTION__);
			return Z3_FALSE;
		}
		assert(lang.size() > 0);
		return Z3_mk_not(ctx, mk_and_fromVector(t, lang));
	}
	else {
		std::vector<Z3_ast> langTmp;
		int preLanguage_size = std::string(PRE_LANGUAGE).size();

		for (unsigned i = 0; i < lang.size(); ++i) {
			std::string name = std::string(Z3_ast_to_string(ctx, lang[i]));
			std::string nameLang;
			int pos = name.find(PRE_LANGUAGE) + preLanguage_size;
			for (unsigned int cnt = pos; cnt < name.size(); ++cnt)
				if (name[cnt] != ' ')
					nameLang = nameLang + name[cnt];
				else {
					nameLang = nameLang + name[cnt];
					break;
				}

			bool found = false;
			for (unsigned j = 0; j < str.size(); ++j) {
				std::string nameVal = std::string(Z3_ast_to_string(ctx, str[j]));
				if (nameVal.find(nameLang) != std::string::npos) {
					found = true;
					break;
				}
			}

			if (!found)
				langTmp.emplace_back(lang[i]);

		}

		assert(str.size() > 0);
		Z3_ast tmp = Z3_mk_not(ctx, mk_and_fromVector(t, str));
		if (langTmp.size() > 0) {

			langTmp.insert(langTmp.end(), str.begin(), str.end());
			assert(langTmp.size() > 0);
			return Z3_mk_not(ctx, mk_and_fromVector(t, langTmp));
		}
		else
			return tmp;
	}
}

/**
  *
  */
Z3_ast negateEquality(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	Z3_context ctx = Z3_theory_get_context(t);

	Z3_ast orConstraints[2] = {negatePositiveContext(t),  Z3_mk_not(ctx, Z3_mk_eq(ctx, nn1, nn2))};
	return Z3_mk_or(ctx, 2, orConstraints);
}

/*
 *
 */
Z3_ast negatePositiveContext(Z3_theory t) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d *** %s ***: ", __LINE__, __FUNCTION__);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> tmp = collectBoolValueInPositiveContext(t);
	if (tmp.size() == 0)
		return Z3_mk_false(ctx);
	else
		return Z3_mk_not(ctx, mk_and_fromVector(t, tmp));
}

/*
 * negate all boolean variables
 */
Z3_ast negatePositiveContext(Z3_theory t, std::vector<Z3_ast> boolVars) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d *** %s ***: ", __LINE__, __FUNCTION__);
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	if (boolVars.size() == 0)
		return Z3_mk_false(ctx);
	else
		return Z3_mk_not(ctx, mk_and_fromVector(t, boolVars));
}

/*
 * not(all information related to NODE)
 */
Z3_ast negatePositiveEquality(
		Z3_theory t,
		Z3_ast node,
		std::vector<std::vector<Z3_ast>> list,
		std::map<Z3_ast, bool> boolValues) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "@%d *** %s ***: boolValues size = %ld", __LINE__, __FUNCTION__, boolValues.size());
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	std::set<Z3_ast> tmp01;
	getNodesInConcat_extended(t, node, tmp01);

	displayListNode(t, tmp01, " negatePositiveEqualityxxx ");
	std::vector<Z3_ast> collector;
	for (const auto& p : containPairBoolMap)
		if (tmp01.find(p.first.first) != tmp01.end()){
			if (boolValues.find(p.second) != boolValues.end()){
				if (boolValues[p.second] == false)
					collector.emplace_back(Z3_mk_eq(ctx, p.second, Z3_mk_false(ctx)));
				else
					collector.emplace_back(Z3_mk_eq(ctx, p.second, Z3_mk_true(ctx)));
			}
		}

	std::vector<Z3_ast> tmp02 = collect_eqc(t, node);
	for (const auto& n : tmp02) {
		if (isNonDetAutomatonFunc(t, n)){
			std::string astStr = Z3_ast_to_string(ctx, n);
			if (astStr.find("$$") == std::string::npos || astStr.find("!!") == std::string::npos)
				collector.push_back(Z3_mk_eq(ctx, node, n));
		}
		else
			collector.push_back(Z3_mk_eq(ctx, node, n));
	}

	if (collector.size() > 0)
		return Z3_mk_not(ctx, mk_and_fromVector(t, collector));
	else
		return NULL;
}

/*
 *
 */
std::vector<Z3_ast> collectLanguageValue(Z3_theory t){
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> ret;

	for (std::map<Z3_ast, int>::iterator it = inputVarMap.begin(); it != inputVarMap.end(); ++it) {
		std::string name = std::string(Z3_ast_to_string(ctx, it->first));
		name = PRE_LANGUAGE + name;
		Z3_ast cases = mk_int_var(ctx, name.c_str());
		Z3_ast value = Z3_theory_get_value_of_len(t, mk_int_var(ctx, name.c_str()));

		if (value != NULL) {
			char * str = (char *) Z3_ast_to_string(ctx, value);

			int value_int = atoi(str);
			if (value_int > 0) {
				ret.emplace_back(Z3_mk_eq(ctx, cases, mk_int(ctx, value_int)));
			}
		}
	}

	return ret;
}

/*
 *
 */
int collectSingleLanguage_index(Z3_theory t, Z3_ast node){
	Z3_context ctx = Z3_theory_get_context(t);

	std::string name = std::string(Z3_ast_to_string(ctx, node));
	name = PRE_LANGUAGE + name;
	//	Z3_ast cases = mk_int_var(ctx, name.c_str());
	Z3_ast value = Z3_theory_get_value_of_len(t, mk_int_var(ctx, name.c_str()));

	if (value != NULL) {
		char * str = (char *) Z3_ast_to_string(ctx, value);

		int value_int = atoi(str);
		return value_int;
	}

	//	return NULL;
	return -1;
}

/*
 *
 */
std::vector<Z3_ast> collectStringValue(Z3_theory t){
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> ret;

	for (std::map<Z3_ast, int>::iterator it = inputVarMap.begin(); it != inputVarMap.end(); ++it) {
		std::string name = std::string(Z3_ast_to_string(ctx, it->first));
		name = PRE_VALUE + name;
		Z3_ast cases = mk_int_var(ctx, name.c_str());
		Z3_ast value = Z3_theory_get_value_of_len(t, mk_int_var(ctx, name.c_str()));

		if (value != NULL) {
			char * str = (char *) Z3_ast_to_string(ctx, value);

			int value_int = atoi(str);
			if (value_int > 0) {
				ret.emplace_back(Z3_mk_eq(ctx, cases, mk_int(ctx, value_int)));
			}
		}
	}

	return ret;
}

/*
 * for each char in charset, create a variable
 */
std::vector<Z3_ast> createParikhConstraints_simpleLanguage(Z3_theory t, Z3_ast node, std::string language) {
	Z3_context ctx = Z3_theory_get_context(t);

	std::vector<Z3_ast> and_list;
	std::map<char, std::vector<Z3_ast>> add_items;

	std::vector<std::string> flats = parse_string_language(language);

	std::vector<Z3_ast> indexList;

	for (unsigned int i = 0; i < flats.size(); ++i){
		std::string name = "$$fLaT" + std::to_string(numOfFlats++);
		Z3_ast index = mk_int_var(ctx, name.c_str());
		indexList.emplace_back(index);
		for (unsigned int j = 0; j < flats[i].size(); ++j){
			add_items[flats[i][j]].emplace_back(index);
		}
	}

	//	for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it) {
	//		and_list.emplace_back(Z3_mk_eq(ctx, mk_binary_app(ctx, td->Parikh, node, mk_int(ctx, (int)*it)), mk_add_fromVector(t, add_items[*it])));
	//	}

	Z3_ast zero = mk_int(ctx, 0);
	for (unsigned int i = 0; i < indexList.size(); ++i)
		and_list.emplace_back(Z3_mk_ge(ctx, indexList[i], zero));
	return and_list;
}

/*
 * for each char in charset, create a variable
 */
std::vector<Z3_ast> createParikhConstraints_evenSimplerLanguage(Z3_theory t, Z3_ast node, std::string language) {
	//	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> and_list;

	//	Z3_ast zero = mk_int(ctx, 0);

	//	for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it)
	//		if (language.find(*it) == std::string::npos)
	//			and_list.emplace_back(Z3_mk_eq(ctx, mk_binary_app(ctx, td->Parikh, node, mk_int(ctx, (int)*it)), zero));

	return and_list;
}

/*
 * for each char in charset, create a variable
 */
std::vector<Z3_ast> createParikhConstraints_string(Z3_theory t, Z3_ast node, std::string value) {
	std::vector<Z3_ast> and_list;
	//	for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it) {
	//		int cnt = 0;
	//		for (unsigned int j = 0; j < value.size(); ++j)
	//			if (value[j] == *it)
	//				cnt++;
	//		Z3_ast parikhChar = getParikhChar(t, node, *it);
	//
	//		// breaking here
	//		and_list.emplace_back(Z3_mk_eq(ctx, parikhChar, mk_int(ctx, cnt)));
	//	}
	return and_list;
}

/*
 * parikh concat >= parikh elements  --> that makes the program VERY SLOW
 * parikh concat = sum of parikh elements
 *
 * len >= len elements
 * len = sum of len of elements
 */
std::vector<Z3_ast> basicArithConstraints_forConcat(Z3_theory t, Z3_ast nn1, Z3_ast nn2){
	std::vector<Z3_ast> ret;
	Z3_context ctx = Z3_theory_get_context(t);
	std::pair<Z3_ast, Z3_ast> concatArgs(nn1, nn2);
	Z3_ast concatNode = concat_astNode_map[concatArgs];
#ifdef PARIKH1
	for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it) {
		Z3_ast* add_items = new Z3_ast[2];
		add_items[0] = getParikhChar(t, nn1, *it);
		add_items[1] = getParikhChar(t, nn2, *it);

		// for parikh
		//		ret.emplace_back(Z3_mk_ge(ctx, getParikhChar(t, concatNode, *it), add_items[0]));
		//		ret.emplace_back(Z3_mk_ge(ctx, getParikhChar(t, concatNode, *it), add_items[1]));

		ret.emplace_back(Z3_mk_eq(ctx, getParikhChar(t, concatNode, *it), Z3_mk_add(ctx, 2, add_items)));
	}
#endif
	// for len
	Z3_ast * add_items = new Z3_ast[2];
	add_items[0] = getLengthAST(t, nn1);
	add_items[1] = getLengthAST(t, nn2);

	//	ret.emplace_back(Z3_mk_ge(ctx, getLengthAST(t, concatNode), add_items[0]));
	//	ret.emplace_back(Z3_mk_ge(ctx, getLengthAST(t, concatNode), add_items[1]));

	ret.emplace_back(Z3_mk_eq(ctx, getLengthAST(t, concatNode), Z3_mk_add(ctx, 2, add_items)));
	delete[] add_items;
	return ret;
}

/*
 * Len = sum of Parikh
 * len >= 0
 */
std::vector<Z3_ast> basicArithConstraints_forNode_simple(Z3_theory t, Z3_ast node) {
	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> ret;
	Z3_ast zero = mk_int(ctx, 0);
	ret.emplace_back(Z3_mk_ge(ctx, mk_length(t, node), zero));

#ifdef PARIKH1
	Z3_ast* add_items = new Z3_ast[charSet.size()];


	int cnt = 0;
	for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it) {
		add_items[cnt] = getParikhChar(t, node, *it);
		cnt++;
	}
	ret.emplace_back(Z3_mk_eq(ctx, getLengthAST(t, node), Z3_mk_add(ctx, charSet.size(), add_items)));

	delete[] add_items;
#endif

	return ret;
}

/*
 * Len = sum of Parikh
 * len > 0
 * parikh > 0
 */
std::vector<Z3_ast> basicArithConstraints_forNode(Z3_theory t, Z3_ast node) {

	std::vector<Z3_ast> ret;
	Z3_ast* add_items = new Z3_ast[charSet.size()];

#ifdef PARIKH1
	Z3_context ctx = Z3_theory_get_context(t);
	int cnt = 0;
	Z3_ast zero = mk_int(ctx, 0);
	// parikh > 0
	for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it) {
		add_items[cnt] = getParikhChar(t, node, *it);
		if (isVariable(t, node))
			ret.emplace_back(Z3_mk_ge(ctx, add_items[cnt], zero));
		cnt++;
	}
	//Len = sum of Parikh
	ret.emplace_back(Z3_mk_eq(ctx, getLengthAST(t, node), Z3_mk_add(ctx, charSet.size(), add_items)));
#endif
	delete[] add_items;
	return ret;
}

/*
 *
 */
Z3_ast getInternalValue(Z3_theory t, Z3_ast node){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string varName = Z3_ast_to_string(ctx, node);
	varName = PRE_VALUE + varName;
	Z3_ast valueNode = mk_int_var(ctx, varName.c_str());
	return valueNode;
}

Z3_ast createOrStr(Z3_theory t, std::set<std::string> strs, Z3_ast node){
	std::vector<Z3_ast> ret;
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	for(std::set<std::string>::iterator it = strs.begin(); it != strs.end(); ++it){
		std::string value = "!!" + *it ;

		Z3_ast tmpNode = mk_unary_app(ctx, td->AutomataDef, mk_str_var(t, value.c_str()));
		Z3_ast tmp = Z3_mk_eq(ctx, node, tmpNode);
		ret.emplace_back(tmp);

	}

	assert(ret.size() > 0);
	return mk_or_fromVector(t, ret);
}

/*
 * Generate value only when having language
 */
bool hasLanguageOverVar(Z3_theory t, Z3_ast node) {
	std::vector<Z3_ast> tmp = getEqualValues(node);
	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (isAutomatonFunc(t, tmp[i])) {
			return true;
		}
	return false;
}

/*
 * Generate language only for variables that are lack of information
 */
bool hasConstraintOverVar(Z3_theory t, Z3_ast node) {
	std::vector<Z3_ast> list = collect_eqc(t, node);

	for (const auto& n : list)
		if (!isVariable(t, n) && n != node){
			return true;
		}
	return false;
}

/*
 * Generate language only for variables that are lack of information
 */
bool relatedToConcat(Z3_theory t, Z3_ast node) {
	std::vector<Z3_ast> tmp = collect_eqc(t, node);

	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (isConcatFunc(t, tmp[i]))
			return true;

	tmp = collect_eqc_parents(t, node);
	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (isConcatFunc(t, tmp[i]))
			return true;

	return false;
}

/*
 * only use one char
 */
std::string createStringWithLength_lazy(Z3_theory t, Z3_ast node, int len, std::map<std::string, std::set<char>> charSet) {
	Z3_ast tmpVariableNode = findEqualVariable(t, node);
	Z3_context ctx = Z3_theory_get_context(t);
	std::set<char> subCharSet = charSet[Z3_ast_to_string(ctx, tmpVariableNode)];
	if (subCharSet.size() == 0)
		subCharSet.insert('a');

	std::string aChar = "";
	if (subCharSet.size() > 0)
		aChar = aChar + *(subCharSet.begin());
	else
		aChar = "a";
	std::string ret = "";
	for (int i = 0; i < len; ++i)
		ret = ret + aChar;
	return ret;
}

/*
 *  only use all characters in the set
 */
std::string createStringWithLength(Z3_theory t, Z3_ast node, int len, std::map<std::string, std::set<char>> charSet) {
	Z3_ast tmpVariableNode = findEqualVariable(t, node);
	Z3_context ctx = Z3_theory_get_context(t);
	std::set<char> subCharSet = charSet[Z3_ast_to_string(ctx, tmpVariableNode)];
	if (subCharSet.size() == 0)
		subCharSet.insert('a');

	std::string aChar = createChar(subCharSet);
	std::string ret = "";
	for (int i = 0; i < len; ++i)
		ret = ret + aChar;
	return ret;
}

/*
 *
 */
std::string createChar(std::set<char> charSet){
	if (charSet.size() == 0)
		return "(a)";
	else {
		std::string ret = "";
		for (std::set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it)
			if (*it == '"')
				ret = ret + "~\"";
			else if (*it == '\\')
				ret = ret + "~\\";
			else
				ret = ret + "~" + (char)*it;
		ret = ret.substr(1);
		ret = "(" + ret + ")";
		return ret;
	}
}

/*
 *
 */
Z3_ast findEqualVariable(Z3_theory t, Z3_ast node) {
	if (isVariable(t, node)) {
		return node;
	}
	else {
		std::vector<Z3_ast> eq_Node = getEqualValues(node);
		for (unsigned int i = 0 ; i < eq_Node.size(); ++i) {
			if (isVariable(t, eq_Node[i]))
				return eq_Node[i];
		}
	}

	// find char from elements
	Z3_context ctx = Z3_theory_get_context(t);
	if (isConcatFunc(t, node)) {
		Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0);
		Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 1);
		Z3_ast tmp01 = findEqualVariable(t, arg0);
		if (tmp01 != NULL)
			return tmp01;
		Z3_ast tmp02 = findEqualVariable(t, arg1);
		if (tmp02 != NULL)
			return tmp02;
	}
	return NULL;
}

/*
 *
 */
std::string createGenericLanguage(Z3_theory t, Z3_ast node) {
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	Z3_ast tmpVariableNode = findEqualVariable(t, node);
	assert(tmpVariableNode != NULL);

	Z3_context ctx = Z3_theory_get_context(t);
	std::set<char> subCharSet = charSet[Z3_ast_to_string(ctx, tmpVariableNode)];

	if (ourGrm.size() > 0) {
		for (int i = '0'; i <= '9'; ++i)
			subCharSet.insert(i);
		for (int i = 'A'; i <= 'Z'; ++i)
			subCharSet.insert(i);
		for (int i = 'a'; i <= 'z'; ++i)
			subCharSet.insert(i);
		subCharSet.insert('=');
		subCharSet.insert('<');
		subCharSet.insert('>');
		subCharSet.insert(';');
		subCharSet.insert(' ');
		subCharSet.insert('/');
	}

	for (const auto& ch: subCharSet){
		__debugPrint(logFile, "%c ", ch);
	}

	if (charSet.size() == 0)
		return "(a)*";
	else {
		return createChar(subCharSet) + "*";
	}
}

/*
 * Mark variable appeared in map "varAppearMap"
 */
void classifyAstByType(Z3_theory t, Z3_ast node, std::map<Z3_ast, int> & varMap, std::map<Z3_ast, int> & concatMap,
		std::map<Z3_ast, std::set<Z3_ast>> & membership) {
#ifdef DEBUGLOG
	//	__debugPrint(logFile, "%d at %s: ClassifyAstByType.\n", __LINE__, __FILE__);
#endif
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_context ctx = Z3_theory_get_context(t);
	T_TheoryType nodeType = getNodeType(t, node);

	//  printZ3Node(t, node);
	//  __debugPrint(logFile, "\n");

	if (nodeType == my_Z3_Str_Var) {
		std::string vName = std::string(Z3_ast_to_string(ctx, node));
		__debugPrint(logFile, "%d at %s string var name: %s\n", __LINE__, __FILE__, vName.c_str());
		if (!(vName.length() >= 6 && (vName.substr(0, 6) == "$$_len" || vName.substr(0, 6) == "$$_val" || vName.substr(0, 6) == "$$_uRt"))) {
			varMap[node] = 1;
		}
	} else if (getNodeType(t, node) == my_Z3_Func) {
		Z3_app func_app = Z3_to_app(ctx, node);
		Z3_func_decl funcDecl = Z3_get_app_decl(ctx, func_app);

		if (funcDecl == td->Length) {
			return;
		} else if (funcDecl == td->Concat) {
			Z3_ast arg0 = Z3_get_app_arg(ctx, func_app, 0);
			Z3_ast arg1 = Z3_get_app_arg(ctx, func_app, 1);
			bool arg0HasEq = false;
			bool arg1HasEq = false;
			Z3_ast arg0Val = get_eqc_value(t, arg0, arg0HasEq);
			Z3_ast arg1Val = get_eqc_value(t, arg1, arg1HasEq);

			int canskip = 0;

			if (arg0HasEq && arg0Val == emptyConstStr) {
				canskip = 1;
			}

			if (canskip == 0 && arg1HasEq && arg1Val == emptyConstStr) {
				canskip = 1;
			}

			if (concatMap.find(node) == concatMap.end()) {
				if (canskip == 0) {
					concatMap[node] = 1;
				}
			}
		} else if (funcDecl == td->RegexIn) {
			assert(Z3_get_app_num_args(ctx, func_app) == 2);
			Z3_ast argAst01 = Z3_get_app_arg(ctx, func_app, 0);
			assert(isVariable(t, argAst01));
			membership[argAst01].insert(Z3_get_app_arg(ctx, func_app, 1));

			printZ3Node(t, argAst01);
			__debugPrint(logFile, " belongs to \n");
			printZ3Node(t, node);
		}

		int argCount = Z3_get_app_num_args(ctx, func_app);
		for (int i = 0; i < argCount; i++) {
			Z3_ast argAst = Z3_get_app_arg(ctx, func_app, i);
			classifyAstByType(t, argAst, varMap, concatMap, membership);
		}
	} else {
		//  	std::string vName = std::string(Z3_ast_to_string(ctx, node));
		//  	__debugPrint(logFile, "%d at %s other var name: %s = %s\n", __LINE__, __FILE__, vName.c_str(), Z3_ast_to_string(ctx, node));
		//  	bool b;
	}
}

/*
 *
 */
bool isInterestingFuncKind(Z3_decl_kind func_decl) {
	bool result = true;
	switch (func_decl) {
	case Z3_OP_EQ:
		result = true;
		break;
	default:
		result = false;
		//        case Z3_OP_DISTINCT:
		//        case Z3_OP_ITE:
		//        case Z3_OP_AND:
		//        case Z3_OP_OR:
		//        case Z3_OP_IFF:
		//        case Z3_OP_XOR:
		//        case Z3_OP_NOT:
		//        case Z3_OP_IMPLIES:
		//            result = false;
		//            break;
		//        default:
		//            result = true;
	}
	return result;
}

/*
 *
 */
void classifyAstByTypeInPositiveContext(Z3_theory t, Z3_ast node, std::map<Z3_ast, int> & varMap, std::map<Z3_ast, int> & concatMap,
		std::map<Z3_ast, std::set<Z3_ast>> & membership) {
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast ctxAssign = Z3_get_context_assignment(ctx);

	if (Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, Z3_to_app(ctx, ctxAssign))) != Z3_OP_AND) {
		if (getNodeType(t, ctxAssign) == my_Z3_Func) {
			Z3_app func_app = Z3_to_app(ctx, ctxAssign);
			Z3_decl_kind func_decl = Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, func_app));
			if (isInterestingFuncKind(func_decl)) {
				classifyAstByType(t, ctxAssign, varMap, concatMap, membership);
			}
		}
	} else {
		int argCount = Z3_get_app_num_args(ctx, Z3_to_app(ctx, ctxAssign));
		for (int i = 0; i < argCount; i++) {
			Z3_ast argAst = Z3_get_app_arg(ctx, Z3_to_app(ctx, ctxAssign), i);
			if (getNodeType(t, argAst) == my_Z3_Func) {
				Z3_app func_app = Z3_to_app(ctx, argAst);
				Z3_decl_kind func_decl = Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, func_app));

				if (isInterestingFuncKind(func_decl)) {
					classifyAstByType(t, argAst, varMap, concatMap, membership);
				}
			}
		}
	}

}

/*
 *
 */
bool collectCharAtInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		bool boolValue,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	for (const auto& it : charAtStrMap) {
		if (boolStr.compare(it.second.first) == 0){
			if (boolValue) {
				rewriterStrMap[it.first] = it.second.second;
				if (carryOn.find(boolNode) != carryOn.end())
					carryOnConstraints.emplace(Z3_ast_to_string(ctx, carryOn[boolNode]));
			}
			else
				rewriterStrMap[it.first] = "-1";
			return true;
		}
	}
	return false;
}

/*
 *
 */
bool collectContainValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		std::string value,
		std::map<StringOP, std::string> &rewriterStrMap){
	for (const auto& it : containPairBoolMap) {
		if (it.second == boolNode) {
			rewriterStrMap[StringOP(languageMap[CONTAINS], node_to_stringOP(t, it.first.first), node_to_stringOP(t, it.first.second))] = value;
			return true;
		}
	}
	return false;
}

/*
 *
 */
void collectSubstrValueInPositiveContext(
		Z3_theory t,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){
	for (const auto& substrElement : subStrStrMap) {
		rewriterStrMap[substrElement.first] = substrElement.second;
		carryOnConstraints.emplace(substrElement.second);
	}
}

/*
 *
 */
bool collectIndexOfValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		bool boolValue,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	for (const auto& it : indexOfStrMap) {
		if (boolStr.compare(it.second.first) == 0){
			if (boolValue) {
				rewriterStrMap[it.first] = it.second.second.first;
				carryOnConstraints.emplace(createEqualConstraint(it.second.second.first, it.second.second.second));
				if (carryOn.find(boolNode) != carryOn.end())
					carryOnConstraints.emplace(Z3_ast_to_string(ctx, carryOn[boolNode]));
			}
			else {
				rewriterStrMap[it.first] = "(- 1)";
				carryOnConstraints.emplace(createEqualConstraint(it.second.second.first, "(- 1)"));
			}
			return true;
		}
	}
	return false;
}

/*
 *
 */
bool collectIndexOf2ValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		bool boolValue,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	for (const auto& it : indexOf2StrMap) {
		if (boolStr.compare(it.second.first) == 0) {
			if (boolValue) {
				rewriterStrMap[it.first] = it.second.second.first;
				carryOnConstraints.emplace(createEqualConstraint(it.second.second.first, it.second.second.second));
				if (carryOn.find(boolNode) != carryOn.end())
					carryOnConstraints.emplace(
							Z3_ast_to_string(ctx, carryOn[boolNode]));
			} else {
				rewriterStrMap[it.first] = "(- 1)";
				carryOnConstraints.emplace(createEqualConstraint(it.second.second.first, "(- 1)"));
			}
			return true;
		}
	}
	return false;
}

/*
 *
 */
bool collectLastIndexOfValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		bool boolValue,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
		printZ3Node(t, boolNode);
		__debugPrint(logFile, "\n");
	__debugPrint(logFile, "%d size of last indexof: %ld\n", __LINE__, lastIndexOfStrMap.size());

	for (const auto& it : lastIndexOfStrMap) {

		if (boolStr.compare(it.second.first) == 0){
			if (boolValue) {
				rewriterStrMap[it.first] = it.second.second.first;
				carryOnConstraints.emplace(createEqualConstraint(it.second.second.first, it.second.second.second));
				if (carryOn.find(boolNode) != carryOn.end())
					carryOnConstraints.emplace(Z3_ast_to_string(ctx, carryOn[boolNode]));
			}
			else {
				rewriterStrMap[it.first] = "(- 1)";
				carryOnConstraints.emplace(createEqualConstraint(it.second.second.first, "(- 1)"));
			}
			return true;
		}
	}
	return false;
}

/*
 *
 */
bool collectEndsWithValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		std::string boolValue,
		std::map<StringOP, std::string> &rewriterStrMap){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	for (const auto& s : endsWithStrMap) {
		if (boolStr.compare(s.second) == 0){
			rewriterStrMap[s.first] = boolValue;
			return true;
		}
	}
	return false;
}

/*
 *
 */
void collectEqualValueInPositiveContext(
		Z3_theory t,
		Z3_ast argAst,
		std::map<StringOP, std::string> &rewriterStrMap){
	Z3_context ctx = Z3_theory_get_context(t);

	std::string astToString = Z3_ast_to_string(ctx, argAst);
//	__debugPrint(logFile, "%d * %s *: %s\n", __LINE__, __FUNCTION__, astToString.c_str());

	if (//astToString.find("$$") == std::string::npos && /* not internal vars */
			astToString.find("a!") == std::string::npos && /* not internal vars */
			astToString.find("(" + std::string(languageMap[LENGTH]) + " ") == std::string::npos && /* not length constraints */
			astToString.find("(= ") != std::string::npos) { /* equality */
		/* add this constraint */
		if (astToString.find("(not ") == 0){
			Z3_ast boolNode = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 0);
			Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, boolNode), 0);
			Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, boolNode), 1);
			if (isStrVariable(t, arg0) || isStrVariable(t, arg1))
				rewriterStrMap[StringOP("=", node_to_stringOP(t, arg0), node_to_stringOP(t, arg1))] = FALSETR;
		}
		else {
//			__debugPrint(logFile, "%d * %s *: %s\n", __LINE__, __FUNCTION__, astToString.c_str());
//			Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 0);
//			Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 1);
//			if (isStrVariable(t, arg0) || isStrVariable(t, arg1))
//				rewriterStrMap[StringOP("=", node_to_stringOP(t, arg0), node_to_stringOP(t, arg1))] = TRUESTR;
		}
	}
	else if (astToString.find("(= ") != std::string::npos &&
			astToString.find("$$") != std::string::npos &&
			astToString.find("(not ") == std::string::npos){
		Z3_ast arg0 = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 0);
		Z3_ast arg1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 1);
		if (toUpperMap.find(arg0) != toUpperMap.end()) {
			rewriterStrMap[StringOP("=", node_to_stringOP(t, toUpperMap[arg0]), node_to_stringOP(t, arg1))] = TOUPPER;
		}
		else if (toUpperMap.find(arg1) != toUpperMap.end()){
			rewriterStrMap[StringOP("=", node_to_stringOP(t, toUpperMap[arg1]), node_to_stringOP(t, arg0))] = TOUPPER;
		}
		else if (toLowerMap.find(arg1) != toLowerMap.end()){
			rewriterStrMap[StringOP("=", node_to_stringOP(t, toLowerMap[arg1]), node_to_stringOP(t, arg0))] = TOLOWER;
		}
		else if (toLowerMap.find(arg0) != toLowerMap.end()) {
			rewriterStrMap[StringOP("=", node_to_stringOP(t, toLowerMap[arg0]), node_to_stringOP(t, arg1))] = TOLOWER;
		}
	}
}
/*
 *
 */
bool collectStartsWithValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		std::string boolValue,
		std::map<StringOP, std::string> &rewriterStrMap){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	for (const auto& s : startsWithStrMap) {
		if (boolStr.compare(s.second) == 0){
			rewriterStrMap[s.first] = boolValue;
			return true;
		}
	}
	return false;
}

/*
 *
 */
bool collectReplaceValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		bool boolValue,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){

	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	for (const auto& it : replaceStrMap) {
		if (boolStr.compare(it.second) == 0){
			if (boolValue) {
				for (const auto& opx : internalVarFunctionMap)
					if (opx.second == it.first) {
						rewriterStrMap[it.first] = opx.first.toString();
						break;
					}
				if (carryOn.find(boolNode) != carryOn.end())
					carryOnConstraints.emplace(Z3_ast_to_string(ctx, carryOn[boolNode]));
			}
			else
				for (const auto& opx : internalVarFunctionMap)
					if (opx.second == it.first) {
						rewriterStrMap[it.first] = opx.first.toString();
						break;
					}
			return true;
		}
	}

	return false;
}


/*
 *
 */
bool collectReplaceAllValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		bool boolValue,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){

	Z3_context ctx = Z3_theory_get_context(t);
	std::string boolStr = Z3_ast_to_string(ctx, boolNode);
	__debugPrint(logFile, "%d *** %s ***: ", __LINE__, __FUNCTION__);
	printZ3Node(t, boolNode);
	__debugPrint(logFile, "\n");
	for (const auto& it : replaceAllStrMap) {
		if (boolStr.compare(it.second) == 0){
			if (boolValue) {
				for (const auto& opx : internalVarFunctionMap)
					if (opx.second == it.first) {
						rewriterStrMap[it.first] = opx.first.toString();
						break;
					}
				if (carryOn.find(boolNode) != carryOn.end())
					carryOnConstraints.emplace(Z3_ast_to_string(ctx, carryOn[boolNode]));
			}
			else
				for (const auto& opx : internalVarFunctionMap)
					if (opx.second == it.first) {
						rewriterStrMap[it.first] = opx.first.toString();
						break;
					}
			return true;
		}
	}

	return false;
}

/*
 *
 */
std::vector<Z3_ast> collectBoolValueInPositiveContext(Z3_theory t) {
	__debugPrint(logFile, "@%d *** %s *** \n", __LINE__, __FUNCTION__);

	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast ctxAssign = Z3_get_context_assignment(ctx);
	std::vector<Z3_ast> ret;

	if (Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, Z3_to_app(ctx, ctxAssign))) == Z3_OP_AND) {
		int argCount = Z3_get_app_num_args(ctx, Z3_to_app(ctx, ctxAssign));

		for (int i = 0; i < argCount; i++) {
			Z3_ast argAst = Z3_get_app_arg(ctx, Z3_to_app(ctx, ctxAssign), i);
			if (isVariable(t, argAst)) {
				std::string astToString = Z3_ast_to_string(ctx, argAst);
				if (astToString.find("$$_bool") != std::string::npos)
					ret.emplace_back(argAst);
			}
			else if (Z3_get_app_num_args(ctx, Z3_to_app(ctx, argAst)) == 1){
				Z3_ast argAst_01 = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 0);
				if (isVariable(t, argAst_01)) {
					std::string astToString = Z3_ast_to_string(ctx, argAst_01);
					if (astToString.find("$$_bool") != std::string::npos)
						ret.emplace_back(argAst);
				}
			}
		}
	}

#ifdef DEBUGLOG
		displayListNode(t, ret, "");
		__debugPrint(logFile, "@%d >>  %s ***: finish\n", __LINE__, __FUNCTION__);
#endif
	return ret;
}

/*
 *
 */
void collectBoolValueInPositiveContext(
		Z3_theory t,
		Z3_ast boolNode,
		std::vector<Z3_ast> &boolVars,
		bool value) {
	Z3_context ctx = Z3_theory_get_context(t);
	std::string astToString = Z3_ast_to_string(ctx, boolNode);
	if (astToString.find("$$_bool") != std::string::npos &&
			astToString.find("(ite") == std::string::npos &&
			astToString.find("(let (") == std::string::npos &&
			astToString.find("(or (") == std::string::npos ) {
		if (value)
			boolVars.emplace_back(boolNode);
		else
			boolVars.emplace_back(Z3_mk_not(ctx, boolNode));
	}
	else if (isVariable(t, boolNode)) {
		if (value)
			boolVars.emplace_back(boolNode);
		else
			boolVars.emplace_back(Z3_mk_not(ctx, boolNode));
	}
}

/*
 *
 */
void collectDataInPositiveContext(
		Z3_theory t,
		std::vector<Z3_ast> &boolVars,
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> &carryOnConstraints){
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast ctxAssign = Z3_get_context_assignment(ctx);
	__debugPrint(logFile, "\n%d *** %s ***\n", __LINE__, __FUNCTION__);

	for (const auto& s: indexOfStrMap)
		if (s.second.first.length() == 0) /* evaluated */
			rewriterStrMap[s.first] = s.second.second.first;

	for (const auto& s : indexOf2StrMap)
		if (s.second.first.length() == 0) /* evaluated */
			rewriterStrMap[s.first] = s.second.second.first;

	for (const auto& s: lastIndexOfStrMap)
		if (s.second.first.length() == 0) /* evaluated */
			rewriterStrMap[s.first] = s.second.second.first;

	for (const auto& s : endsWithStrMap)
		rewriterStrMap[s.first] = s.second;

	for (const auto& it : startsWithStrMap)
		rewriterStrMap[it.first] = it.second;

	for (const auto& s : replaceStrMap)
		rewriterStrMap[s.first] = s.second;

	for (const auto& s : replaceAllStrMap)
		rewriterStrMap[s.first] = s.second;

	collectSubstrValueInPositiveContext(t, rewriterStrMap, carryOnConstraints);

	if (Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, Z3_to_app(ctx, ctxAssign))) == Z3_OP_AND) {
		int argCount = Z3_get_app_num_args(ctx, Z3_to_app(ctx, ctxAssign));
		__debugPrint(logFile, "%d * %s * arg count = : %d\n", __LINE__, __FUNCTION__, argCount);
		for (int i = 0; i < argCount; i++) {
			Z3_ast argAst = Z3_get_app_arg(ctx, Z3_to_app(ctx, ctxAssign), i);


			T_TheoryType type = getNodeType(t, argAst);

			bool found01 = false, found02 = false, found03 = false, found04 = false, found05 = false, found06 = false, found07 = false, found08 = false, found09 = false;
			if (type == my_Z3_Var) {
				std::string astToString = Z3_ast_to_string(ctx, argAst);
				if (astToString.find("$$_bool") != std::string::npos) {
					collectBoolValueInPositiveContext(t, argAst, boolVars, true);
					found01 = collectContainValueInPositiveContext(t, argAst, TRUESTR, rewriterStrMap);
					found02 = collectIndexOfValueInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
					found09 = collectIndexOf2ValueInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
					found03 = collectLastIndexOfValueInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
					found04 = collectEndsWithValueInPositiveContext(t, argAst, TRUESTR, rewriterStrMap);
					found05 = collectStartsWithValueInPositiveContext(t, argAst, TRUESTR, rewriterStrMap);
					found06 = collectReplaceValueInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
					found07 = collectReplaceAllValueInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
					found08 = collectCharAtInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
				}
				else {
					collectBoolValueInPositiveContext(t, argAst, boolVars, true);
				}
			}

			else if (type == my_Z3_Func && Z3_get_app_num_args(ctx, Z3_to_app(ctx, argAst)) == 1) {
				Z3_ast boolNode = Z3_get_app_arg(ctx, Z3_to_app(ctx, argAst), 0);
				if (isVariable(t, boolNode)){
					collectBoolValueInPositiveContext(t, boolNode, boolVars, false);
					std::string astToString = Z3_ast_to_string(ctx, boolNode);
					if (astToString.find("$$_bool") != std::string::npos) {
						found01 = collectContainValueInPositiveContext(t, boolNode, FALSETR, rewriterStrMap);
						found02 = collectIndexOfValueInPositiveContext(t, boolNode, false, rewriterStrMap, carryOnConstraints);
						found09 = collectIndexOf2ValueInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
						found03 = collectLastIndexOfValueInPositiveContext(t, boolNode, false, rewriterStrMap, carryOnConstraints);
						found04 = collectEndsWithValueInPositiveContext(t, boolNode, FALSETR, rewriterStrMap);
						found05 = collectStartsWithValueInPositiveContext(t, boolNode, FALSETR, rewriterStrMap);
						found06 = collectReplaceValueInPositiveContext(t, boolNode, false, rewriterStrMap, carryOnConstraints);
						found07 = collectReplaceAllValueInPositiveContext(t, boolNode, false, rewriterStrMap, carryOnConstraints);
						found08 = collectCharAtInPositiveContext(t, argAst, true, rewriterStrMap, carryOnConstraints);
					}
				}
			}

			if (!(found01 || found02 || found03 || found04 || found05 || found06 || found07 || found08 || found09)){
				collectEqualValueInPositiveContext(t, argAst, rewriterStrMap);
			}
		}
	}
	else
		assert(false);
}
/*
 * Decide whether two n1 and n2 are ALREADY in a same eq class
 * Or n1 and n2 are ALREADY treated equal by the core
 * BUT, they may or may not be really equal
 */
bool inSameEqc(Z3_theory t, Z3_ast n1, Z3_ast n2) {
	if (n1 == n2)
		return true;
	Z3_ast curr = Z3_theory_get_eqc_next(t, n1);
	while (curr != n1) {
		if (curr == n2)
			return true;
		curr = Z3_theory_get_eqc_next(t, curr);
	}
	return false;
}

/*
 * Dependence analysis from current context assignment
 * - "freeVarMap" contains a set of variables that doesn't constrained by Concats.
 *    But it's possible that it's bounded by unrolls
 *    For the case of
 *    (1) var1 = unroll(r1, t1)
 *        var1 is in the freeVarMap
 *        > should unroll r1 for var1
 *    (2) var1 = unroll(r1, t1) /\ var1 = Concat(var2, var3)
 *        var2, var3 are all in freeVar
 *        > should split the unroll function so that var2 and var3 are bounded by new unrolls
 */
void ctxDepAnalysis(Z3_theory t, std::map<Z3_ast, int> & strVarMap, std::map<Z3_ast, int> & freeVarMap,
		std::map<Z3_ast, std::set<Z3_ast> > & membership) {
	std::map<Z3_ast, int> concatMap;
	std::map<Z3_ast, Z3_ast> aliasIndexMap;
	std::map<Z3_ast, Z3_ast> var_eq_constStr_map;
	std::map<Z3_ast, Z3_ast> concat_eq_constStr_map;
	std::map<Z3_ast, std::map<Z3_ast, int> > var_eq_concat_map;
	std::map<Z3_ast, std::map<Z3_ast, int> > var_eq_unroll_map;
	std::map<Z3_ast, std::map<Z3_ast, int> > concat_eq_concat_map;
	std::map<Z3_ast, std::map<Z3_ast, int> > depMap;

	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast ctxAssign = Z3_get_context_assignment(ctx);

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n*********************************************************\n");
	__debugPrint(logFile, "       Dependence Analysis\n");
	__debugPrint(logFile, "---------------------------------------------------------\n\n");
#endif

	//--------------------------------------------
	// Step 1. get variables/Concat AST appeared in context
	//--------------------------------------------
	for (std::map<Z3_ast, int>::iterator it = inputVarMap.begin(); it != inputVarMap.end(); it++) {
		strVarMap[it->first] = 1;
	}
	classifyAstByTypeInPositiveContext(t, ctxAssign, strVarMap, concatMap, membership);


#ifdef DEBUGLOG
	{
		__debugPrint(logFile, "(0) alias: variables\n");
		std::map<Z3_ast, std::map<Z3_ast, int> > aliasSumMap;

		std::map<Z3_ast, Z3_ast>::iterator itor0 = aliasIndexMap.begin();
		for (; itor0 != aliasIndexMap.end(); itor0++)
			aliasSumMap[itor0->second][itor0->first] = 1;

		std::map<Z3_ast, std::map<Z3_ast, int> >::iterator keyItor = aliasSumMap.begin();
		for (; keyItor != aliasSumMap.end(); keyItor++) {
			__debugPrint(logFile, "    * ");
			printZ3Node(t, keyItor->first);
			__debugPrint(logFile, " : ");
			std::map<Z3_ast, int>::iterator innerItor = keyItor->second.begin();
			for (; innerItor != keyItor->second.end(); innerItor++) {
				printZ3Node(t, innerItor->first);
				__debugPrint(logFile, ", ");
			}
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
	}

	{
		__debugPrint(logFile, "(1) var = constStr:\n");
		std::map<Z3_ast, Z3_ast>::iterator itor1 = var_eq_constStr_map.begin();
		for (; itor1 != var_eq_constStr_map.end(); itor1++) {
			__debugPrint(logFile, "    * ");
			printZ3Node(t, itor1->first);
			__debugPrint(logFile, " = ");
			printZ3Node(t, itor1->second);
			if (!inSameEqc(t, itor1->first, itor1->second))
				__debugPrint(logFile, "  (notTrue in ctx)");
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
	}

	{
		__debugPrint(logFile, "(2) var = concat:\n");
		std::map<Z3_ast, std::map<Z3_ast, int> >::iterator itor2 = var_eq_concat_map.begin();
		for (; itor2 != var_eq_concat_map.end(); itor2++) {
			__debugPrint(logFile, "    * ");
			printZ3Node(t, itor2->first);
			__debugPrint(logFile, " = { ");
			std::map<Z3_ast, int>::iterator i_itor = itor2->second.begin();
			for (; i_itor != itor2->second.end(); i_itor++) {
				printZ3Node(t, i_itor->first);
				__debugPrint(logFile, ", ");
			}
			__debugPrint(logFile, " }\n");
		}
		__debugPrint(logFile, "\n");
	}

	{
		__debugPrint(logFile, "(4) concat = constStr:\n");
		std::map<Z3_ast, Z3_ast>::iterator itor3 = concat_eq_constStr_map.begin();
		for (; itor3 != concat_eq_constStr_map.end(); itor3++) {
			__debugPrint(logFile, "    * ");
			printZ3Node(t, itor3->first);
			__debugPrint(logFile, " = ");
			printZ3Node(t, itor3->second);
			__debugPrint(logFile, "\n");

		}
		__debugPrint(logFile, "\n");
	}

	{
		__debugPrint(logFile, "(5) eq concats:\n");
		std::map<Z3_ast, std::map<Z3_ast, int> >::iterator itor4 = concat_eq_concat_map.begin();
		for (; itor4 != concat_eq_concat_map.end(); itor4++) {
			if (itor4->second.size() > 1) {
				std::map<Z3_ast, int>::iterator i_itor = itor4->second.begin();
				__debugPrint(logFile, "    * ");
				for (; i_itor != itor4->second.end(); i_itor++) {
					printZ3Node(t, i_itor->first);
					__debugPrint(logFile, " , ");
				}
				__debugPrint(logFile, "\n");
			}
		}
		__debugPrint(logFile, "\n");
	}

#endif
}

/*
 *
 */
Z3_ast getLengthAST(Z3_theory t, Z3_ast n) {
	return mk_length(t, n);
}

/*
 *
 */
Z3_ast getParikhChar(Z3_theory t, Z3_ast n, char c) {
	Z3_context ctx = Z3_theory_get_context(t);
	std::pair<Z3_ast, int> p = std::make_pair(n, (int)c);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	if (parikh_Node_map.find(p) == parikh_Node_map.end()) {
		parikh_Node_map[p] = mk_binary_app(ctx, td->Parikh, n, mk_int(ctx, (int)c));
	}
	return parikh_Node_map[p];
}

/*
 * Query the integer theory.
 *   - If n has length value in integer theory, return the value.
 *   - Else, return -1.
 */
int getLenValue(Z3_theory t, Z3_ast node) {

	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast lenAst = getLengthAST(t, node);
	Z3_ast lenValueAst = Z3_theory_get_value_of_len(t, lenAst);

	if (lenValueAst == NULL) {
		return -1;
	}
	//  if (getNodeType(t, n) == my_Z3_ConstStr || lenAst != lenValueAst) {
	if (lenAst != lenValueAst) {
		char * str = (char *) Z3_ast_to_string(ctx, lenValueAst);

		int len = atoi(str);
		if (len < 0) {
			__debugPrint(logFile, "\n\n\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			__debugPrint(logFile, "ERROR: length of ");
			printZ3Node(t, node)
			__debugPrint(logFile, " < 0\n");
			exit(0);
		}
		return len;
	}
	return -1;
}

/*
 * Look for the equivalent constant for a node "n"
 * Iterate the equivalence class
 * If there is a constant,
 *    return the constant
 * Otherwise,
 *    return n
 */
Z3_ast get_eqc_value(Z3_theory t, Z3_ast n, bool & hasEqcValue) {
	Z3_ast curr = n;
	do {
		if (Z3_theory_is_value(t, curr)) {
			if (isConstStr(t, curr)) {
				hasEqcValue = true;
				return curr;
			}
		}
		curr = Z3_theory_get_eqc_next(t, curr);
	} while (curr != n);
	hasEqcValue = false;
	return n;
}

/**
   \brief Display equivalence class containing \c n.
 */
void display_eqc(Z3_theory t, Z3_ast n, std::vector<Z3_ast> equivalent) {
	Z3_context c = Z3_theory_get_context(t);

	__debugPrint(logFile,"  ----- begin eqc of %s: %d nodes\n", Z3_ast_to_string(c, n), (int) equivalent.size());
	//	__debugPrint(logFile,", root: %s\n", Z3_ast_to_string(c, Z3_theory_get_eqc_root(t, n)));
	displayListNode(t, equivalent);
	__debugPrint(logFile,"  ----- end of eqc\n");
}

/**
   \brief Display equivalence class containing \c n.
 */
std::vector<Z3_ast> collect_eqc(Z3_theory t, Z3_ast n) {
	std::vector<Z3_ast> ret;
	Z3_ast curr = n;
	do {
		ret.emplace_back(curr);
		curr = Z3_theory_get_eqc_next(t, curr);
	}
	while (curr != n);

	return ret;
}

/**
   \brief Display the parent theory operators of the equivalence class containing \c n.
 */
void display_eqc_parents(Z3_theory t, Z3_ast n, std::vector<Z3_ast> equivalent) {
	Z3_context c = Z3_theory_get_context(t);

	__debugPrint(logFile, "  ----- begin eqc (theory) parents of %s\n", Z3_ast_to_string(c, n));
	displayListNode(t, equivalent);
	__debugPrint(logFile,"  ----- end of eqc (theory) parents\n");
}

/*
 *
 */
std::vector<Z3_ast> collect_eqc_parents(Z3_theory t, Z3_ast n) {
	std::vector<Z3_ast> ret;
	Z3_ast curr = n;
	do {
		unsigned num_parents = Z3_theory_get_num_parents(t, curr);
		unsigned i;
		for (i = 0; i < num_parents; i++) {
			Z3_ast p = Z3_theory_get_parent(t, curr, i);
			ret.emplace_back(p);
		}
		curr = Z3_theory_get_eqc_next(t, curr);
	}
	while (curr != n);
	return ret;
}

/*
 *
 */
std::set<Z3_ast> collectAllParents(Z3_theory t, Z3_ast node){
	std::vector<Z3_ast> equal = getEqualValues(node);

	std::set<Z3_ast> parents;
	for (unsigned int i = 0; i < equal.size(); ++i) {
		std::vector<Z3_ast> list =  collect_eqc_parents(t, equal[i]);
		for (unsigned int j = 0; j < list.size(); ++j) {
			if (std::find(equal.begin(), equal.end(), list[j]) == equal.end())
				parents.insert(list[j]);
		}
	}
	//	std::set<Z3_ast> parents;
	//	std::vector<Z3_ast> list =  collect_eqc_parents(t, node);
	//	parents.insert(list.begin(), list.end());
	return parents;
}

/*
 *
 */
std::set<Z3_ast> collectAllFurtherParents(Z3_theory t, Z3_ast node) {
	std::set<Z3_ast> ret;
	collectAllFurtherParents(t, node, ret);
	return ret;
}

/*
 *
 */
void collectAllFurtherParents(Z3_theory t, Z3_ast node, std::set<Z3_ast> &list) {
	std::set<Z3_ast> tmp = collectAllParents(t, node);
	for (std::set<Z3_ast>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
		if (isConcatFunc(t, *it)) {
			list.insert(*it);
			collectAllFurtherParents(t, *it, list);
		}
	}
}

void displayListNode(Z3_theory t, std::vector<Z3_ast> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& n : l) {
		printZ3Node(t, n);
		__debugPrint(logFile, "\n");
	}
	__debugPrint(logFile, "\n");
}

void displayListNode(Z3_theory t, std::set<Z3_ast> l, std::string msg) {
	if (msg.length() > 0)
		__debugPrint(logFile, "%s\n", msg.c_str());
	for (const auto& n : l) {
		printZ3Node(t, n);
		__debugPrint(logFile, "\n");
	}
	__debugPrint(logFile, "\n");
}

void display_new_eq(Z3_theory t, Z3_ast n1, Z3_ast n2, std::vector<Z3_ast> eq01, std::vector<Z3_ast> eq01_parent, std::vector<Z3_ast> eq02, std::vector<Z3_ast> eq02_parent) {
	__debugPrint(logFile,"====== begin new equality\n");

	display_eqc(t, n1, eq01);
	display_eqc_parents(t, n1, eq01_parent);

	__debugPrint(logFile,"  ==\n");

	display_eqc(t, n2, eq02);
	display_eqc_parents(t, n2, eq02_parent);

	__debugPrint(logFile,"====== end new equality\n");
}

/*
 *
 */
void __printNode(Z3_theory t, Z3_ast node) {
#ifdef DEBUGLOG
	Z3_context ctx = Z3_theory_get_context(t);
	if (node == NULL) {
		__debugPrint(logFile, "NULL");
		return;
	}

	T_TheoryType nodeType = getNodeType(t, node);
	switch (nodeType) {
	case my_Z3_ConstStr: {
		std::string str = getConstStrValue(t, node);
		__debugPrint(logFile, "\"%s\"", str.c_str());
		break;
	}
	case my_Z3_Func: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Num: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Var: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Str_Var: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Quantifier: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Unknown: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	default: {
		__debugPrint(logFile, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	}
#endif
}

void __printNodeAxiom(Z3_theory t, Z3_ast node) {
#ifdef DEBUGLOG
	Z3_context ctx = Z3_theory_get_context(t);
	if (node == NULL) {
		__debugPrint(logAxiom, "NULL");
		return;
	}

	T_TheoryType nodeType = getNodeType(t, node);
	switch (nodeType) {
	case my_Z3_ConstStr: {
		std::string str = getConstStrValue(t, node);
		__debugPrint(logAxiom, "\"%s\"", str.c_str());
		break;
	}
	case my_Z3_Func: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Num: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Var: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Str_Var: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Quantifier: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	case my_Z3_Unknown: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	default: {
		__debugPrint(logAxiom, "%s", Z3_ast_to_string(ctx, node));
		break;
	}
	}
#endif
}

void collect_from_new_eq(Z3_theory t, Z3_ast n1, Z3_ast n2, std::vector<Z3_ast>& eq01, std::vector<Z3_ast>& eq01_parent, std::vector<Z3_ast>& eq02, std::vector<Z3_ast>& eq02_parent) {
	Z3_context c = Z3_theory_get_context(t);
	std::string name01 = Z3_ast_to_string(c, n1);
	if (name01.find("~") == std::string::npos && name01.find("*") == std::string::npos) {
		eq01 = collect_eqc(t, n1);
		eq01_parent = collect_eqc_parents(t, n1);
	}
	else
		eq01.emplace_back(n1);

	std::string name02 = Z3_ast_to_string(c, n2);
	if (name02.find("~") == std::string::npos && name02.find("*") == std::string::npos) {
		eq02 = collect_eqc(t, n2);
		eq02_parent = collect_eqc_parents(t, n2);
	}
	else
		eq01.emplace_back(n2);
}

/**
   \brief Instantiate the unit axiom for the parents of \c n because
   \c n is now equal to unit u in the logical context.
 */
void apply_unit_axiom_for_parents_of(Z3_theory t, Z3_ast n) {
	Z3_context c = Z3_theory_get_context(t);
	printf("At line %d %s:\n", __LINE__, Z3_ast_to_string(c, n));
	//	AutomatonStringData * td = (AutomatonStringData*)Z3_theory_get_ext_data(t);

	/*
      The following idiom is the standard approach for traversing
      applications of the form

      g(..., n', ...)
      where
      - g is an interpreted function symbol of \c t.
      - n' is in the same equivalence class of n.
	 */
	Z3_ast n_prime = n;
	do {
		unsigned num_parents = Z3_theory_get_num_parents(t, n_prime);
		unsigned i;
		for (i = 0; i < num_parents; i++) {
			//			Z3_app parent = Z3_to_app(c, Z3_theory_get_parent(t, n_prime, i));
			/* check whether current parent is of the form f(a, n_prime) */
			//			if (Z3_get_app_decl(c, parent) == td->f && Z3_get_app_arg(c, parent, 1) == n_prime) {
			//				/* assert f(a, u) = a */
			//				Z3_context c = Z3_theory_get_context(t);
			//				Z3_ast a = Z3_get_app_arg(c, parent, 0);
			//
			//				printf("At line %d: %s\n", __LINE__, Z3_ast_to_string(c, a));
			//				printf("At line %d: %s\n", __LINE__, Z3_ast_to_string(c, n_prime));
			//
			//				Z3_theory_assert_axiom(t, Z3_mk_eq(c, mk_binary_app(c, td->f, a, td->u), a));
			//				/* Instead of asserting f(a, u) = a, we could also have asserted
			//                   the clause:
			//                   (not (n_prime = u)) or (f(a, n_prime) = a)
			//
			//                   However, this solution is wasteful, because the axiom
			//                   assert f(a, u) = a is simpler and more general.
			//                   Note that n_prime is in the equivalence class of n,
			//                   and n is now equal to u. So, n_prime is also equal to u.
			//                   Then, using congruence, Z3 will also deduce that f(a, n_prime) = a
			//                   using the simpler axiom.
			//				 */
			//			}
			//			/* check whether current parent is of the form f(n_prime, a) */
			//			if (Z3_get_app_decl(c, parent) == td->f && Z3_get_app_arg(c, parent, 0) == n_prime) {
			//				/* assert f(u, a) = a */
			//				Z3_context c = Z3_theory_get_context(t);
			//				Z3_ast a = Z3_get_app_arg(c, parent, 1);
			//
			//				printf("At line %d: %s\n", __LINE__, Z3_ast_to_string(c, a));
			//				printf("At line %d: %s\n", __LINE__, Z3_ast_to_string(c, n_prime));
			//				Z3_theory_assert_axiom(t, Z3_mk_eq(c, mk_binary_app(c, td->f, td->u, a), a));
			//			}
		}
		n_prime = Z3_theory_get_eqc_next(t, n_prime);
	}
	while (n_prime != n);
}

/*
 *
 */
bool isVariable(Z3_theory t, Z3_ast n) {
	T_TheoryType nodeType = getNodeType(t, n);

	if (nodeType == my_Z3_Var || nodeType == my_Z3_Str_Var || nodeType == my_Z3_Regex_Var)
		return true;
	else
		return false;
}

bool isStrVariable(Z3_theory t, Z3_ast n) {
	T_TheoryType nodeType = getNodeType(t, n);

	if (nodeType == my_Z3_Str_Var)
		return true;
	else
		return false;
}

/*
 *
 */
bool isAutomatonFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->AutomataDef || d == td->NonDet_AutomataDef)
		return true;
	else
		return false;
}

/*
 *
 */
bool isNonDetAutomatonFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->NonDet_AutomataDef)
		return true;
	else
		return false;
}

/*
 *
 */
bool isDetAutomatonFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->AutomataDef)
		return true;
	else
		return false;
}

/*
 *
 */
bool isRegexPlusFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->NonDet_AutomataDef) {
		std::string str = getConstString(t, n);
		if (str.find('+') != std::string::npos)
			return true;
	}
	return false;
}

/*
 *
 */
bool isConcatFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->Concat)
		return true;
	else
		return false;
}

/*
 *
 */
bool isCharAtFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->CharAt)
		return true;
	else
		return false;
}

/*
 *
 */
bool isConstStr(Z3_theory t, Z3_ast node) {
	if (node == NULL)
		return false;
	if (getNodeType(t, node) == my_Z3_ConstStr) {
		return true;
	} else {
		return false;
	}
}

/*
 *
 */
bool isLengthFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->Length)
		return true;
	else
		return false;
}

/*
 *
 */
bool isUnrollFunc(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->Unroll)
		return true;
	else
		return false;
}


/*
 *
 */
bool isSelectRetString(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	Z3_decl_kind decl_kind = Z3_get_decl_kind(ctx, d);

	if (decl_kind == Z3_OP_SELECT && td->String == Z3_get_sort(ctx, n)) {
		return true;
	} else {
		return false;
	}
}

/*
 *
 */
bool isRegexStar(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->RegexStar)
		return true;
	else
		return false;
}

/*
 *
 */
bool isStr2Regex(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->Str2Reg)
		return true;
	else
		return false;
}

/*
 *
 */
bool isRegexUnion(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->RegexUnion)
		return true;
	else
		return false;
}

/*
 *
 */
bool isRegexConcat(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
	if (d == td->RegexConcat)
		return true;
	else
		return false;
}

/*
 *
 */
std::string getStdRegexStr(Z3_theory t, Z3_ast regex) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl regexFuncDecl = Z3_get_app_decl(ctx, Z3_to_app(ctx, regex));
	if (regexFuncDecl == td->Str2Reg) {
		Z3_ast regAst = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 0);
		std::string regStr = str2RegexStr(customizeString(getConstStrValue(t, regAst)));

		// string cannot containt "~"
		if (regStr.find('~') != std::string::npos) {
			printf("> Error: unexpected regex operation.\n");
			__debugPrint(logFile, ">> Error: unexpected regex operation.\n");
			__debugPrint(logFile, "   * [regex] %s: ", regStr.c_str());
			printZ3Node(t, regex);
			__debugPrint(logFile, "\n");
			exit(0);
		}

		return regStr;
	} else if (regexFuncDecl == td->RegexConcat) {
		Z3_ast reg1Ast = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 0);
		Z3_ast reg2Ast = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 1);
		std::string reg1Str = getStdRegexStr(t, reg1Ast);
		std::string reg2Str = getStdRegexStr(t, reg2Ast);
		return "(" + reg1Str + ")(" + reg2Str + ")";
	} else if (regexFuncDecl == td->RegexUnion) {
		Z3_ast reg1Ast = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 0);
		Z3_ast reg2Ast = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 1);
		std::string reg1Str = getStdRegexStr(t, reg1Ast);
		std::string reg2Str = getStdRegexStr(t, reg2Ast);
		return  "(" + reg1Str + ")~(" + reg2Str + ")";
	} else if (regexFuncDecl == td->RegexStar) {
		Z3_ast reg1Ast = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 0);
		std::string reg1Str = getStdRegexStr(t, reg1Ast);
		return  "(" + reg1Str + ")*";
	} else if (regexFuncDecl == td->RegexCharRange) {
		Z3_ast start = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 0);
		Z3_ast finish = Z3_get_app_arg(ctx, Z3_to_app(ctx, regex), 1);
		std::string arg00 = getConstString(t, start);
		std::string arg01 = getConstString(t, finish);

		assert(arg00.length() == 1);
		assert(arg01.length() == 1);
		std::string ret = "";
		for (unsigned i = arg00[0]; i <= (unsigned)arg01[0]; ++i)
			ret = ret + "~" + (char)i;
		return ret.substr(1);
	}
	else {
		return "__Contain_Vars__";
	}
}

/*
 * name -> regex(es) using under approximation
 */
std::vector<std::string> getStdGrmStr(Z3_theory t, Z3_ast grammar) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_func_decl grmFuncDecl = Z3_get_app_decl(ctx, Z3_to_app(ctx, grammar));
	if (grmFuncDecl == td->Str2Grm) {
		Z3_ast grmAst = Z3_get_app_arg(ctx, Z3_to_app(ctx, grammar), 0);
		std::vector<std::string> grmStr = lookUp_Grammar(Z3_ast_to_string(ctx, grmAst));

		return grmStr;
	} else {
		return {"__Contain_Vars__"};
	}
}


/*
 * Find over/under-approx of CFG
 */
std::vector<std::string> lookUp_Grammar(std::string name){
	/* replace the first char of name */
	std::string tmpName = name;
	if (tmpName[0] != '$'){
		printf("%d %s\n", __LINE__, tmpName.c_str());
		throw std::runtime_error("CFG variable is incorrect\n");
	}
	return ourGrm["$" + tmpName.substr(1)];
}

/*
 *
 */
std::string str2RegexStr(std::string str) {
	std::string res = "";
	int len = str.size();
	for (int i = 0; i < len; i++) {
		char nc = str[i];
		// 12 special chars
		if (nc == '\\' || nc == '^' || nc == '$' || nc == '.' || nc == '|' || nc == '?'
				|| nc == '*' || nc == '+' || nc == '(' || nc == ')' || nc == '[' || nc == '{') {
			res.append(1, '\\');
		}
		res.append(1, str[i]);
	}
	return res;
}

/* ---------------------------------
 * Return the node type in Enum
 * ---------------------------------
 */
T_TheoryType getNodeType(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_ast_kind z3Kind = Z3_get_ast_kind(ctx, n);

	switch (z3Kind) {
	case Z3_NUMERAL_AST: {
		return my_Z3_Num;
		break;
	}

	case Z3_APP_AST: {
		Z3_sort s = Z3_get_sort(ctx, n);
		Z3_sort_kind sk = Z3_get_sort_kind(ctx, s);
		Z3_func_decl d = Z3_get_app_decl(ctx, Z3_to_app(ctx, n));
		if (Z3_theory_is_value(t, n)) {
			if (sk == Z3_BOOL_SORT) {
				if (d == td->Contains ||
						d == td->StartsWith ||
						d == td->EndsWith ||
						d == td->RegexIn ||
						d == td->GrammarIn) {
					return my_Z3_Func;
				} else {
					return my_Z3_ConstBool;
				}
			} else if (sk == Z3_INT_SORT) {
				if (d == td->Length ||
						d == td->Indexof ||
						d == td->Indexof2 ||
						d == td->LastIndexof) {
					return my_Z3_Func;
				}
			} else if (sk == Z3_UNKNOWN_SORT) {
				if (s == td->String) {
					if (d == td->Concat ||
							d == td->SubString ||
							d == td->Replace ||
							d == td->ReplaceAll ||
							d == td->Unroll ||
							d == td->CharAt ||
							d == td->AutomataDef ||
							d == td->NonDet_AutomataDef ||
							d == td->ToLower ||
							d == td->ToUpper ) {
						return my_Z3_Func;
					} else {
						return my_Z3_ConstStr;
					}
				}

				if (s == td->Regex) {
					if (d == td->RegexConcat ||
							d == td->RegexStar ||
							d == td->RegexPlus ||
							d == td->RegexCharRange ||
							d == td->RegexUnion ||
							d == td->Str2Reg ||
							d == td->RegexAll ||
							d == td->RegexAllChar ||
							d == td->RegexNone) // TODO update list of functions
						return my_Z3_Func;
					else
						return my_Z3_Regex_Var;
				}

				if (s == td->Grammar) {
					if (d == td->Str2Grm ||
							d == td->GrammarIn)
						return my_Z3_Func;
					else
						return my_Z3_Grammar_Var;
				}


			} else if (sk == Z3_ARRAY_SORT) {
				std::string vName = std::string(Z3_ast_to_string(ctx, n));
				__debugPrint(logFile, "> [getNodeType] my_Z3_Func: %s\n\n", vName.c_str());
				return my_Z3_Func;
			}
		} else {
			//Z3 native functions fall into this category
			Z3_decl_kind dk = Z3_get_decl_kind(ctx, d);
			unsigned domainSize = Z3_get_domain_size(ctx, d);
			if (dk != Z3_OP_UNINTERPRETED) {
				// built-in function
				return my_Z3_Func;
			} else {
				if (domainSize != 0) {
					// "real" UNINTERPRETED function declared in the input
					return my_Z3_Func;
				} else {
					if (s == td->String) {
						return my_Z3_Str_Var;
					} else if (s == td->Regex) {
						return my_Z3_Regex_Var;
					} else {
						return my_Z3_Var;
					}
				}
			}
		}
		break;
	}

	case Z3_VAR_AST: {
		return my_Z3_Var;
		break;
	}

	default: {
		break;
	}
	}
	return my_Z3_Unknown;
}

/*
 *
 */
std::string getConstStrValue(Z3_theory t, Z3_ast n) {
	if (n == emptyConstStr) {
		return std::string("");
	}

	Z3_context ctx = Z3_theory_get_context(t);
	std::string strValue;
	if (isConstStr(t, n)) {
		char * str = (char *) Z3_ast_to_string(ctx, n);
		strValue = std::string(str);
	} else {
		strValue = std::string("__NotConstStr__");
	}

	return customizeString(strValue);
}

/*
 *
 */
int getConstIntValue(Z3_theory t, Z3_ast n) {
	Z3_context ctx = Z3_theory_get_context(t);
	if (getNodeType(t, n) == my_Z3_Num) {
		char * str = (char *) Z3_ast_to_string(ctx, n);
		int val = atoi(str);
		return val;
	} else {
		__debugPrint(logFile, "> Converting a non integer string to int @ %d. \n", __LINE__);
	}
	return -1;
}

/*
 * Add axioms that are true for any string var
 */
void basicStrVarAxiom(Z3_theory t, Z3_ast vNode, int line) {
	if (basicStrVarAxiom_added.find(vNode) == basicStrVarAxiom_added.end()) {
		Z3_context ctx = Z3_theory_get_context(t);
		Z3_ast lenTerm = mk_length(t, vNode);

		Z3_ast strlen_ge = Z3_mk_ge(ctx, lenTerm, mk_int(ctx, 0));
		addAxiom(t, strlen_ge, line, false);

		Z3_ast strLen_zero = Z3_mk_eq(ctx, lenTerm, mk_int(ctx, 0));
		Z3_ast str_empty = Z3_mk_eq(ctx, vNode, mk_str_value(t, ""));
		Z3_ast str_eq_ast2 = Z3_mk_eq(ctx, strLen_zero, str_empty);
		addAxiom(t, str_eq_ast2, line, false);

		basicStrVarAxiom_added[vNode] = 1;
	}
}

void addAxiom(Z3_theory t, Z3_ast toAssert, int line, bool display) {
	if (toAssert == NULL) {
		return;
	}

#ifdef DEBUGLOG
	if (display) {
		if (searchStart == 1) {
			__debugPrint(logFile, "\n---------------------\nAxiom Add(@%d, Level %d):\n", line, sLevel);
			printZ3Node(t, toAssert);
			__debugPrint(logFile, "\n---------------------\n\n");

			__debugPrint(logAxiom, "\n---------------------\nAxiom Add(@%d, Level %d):\n", line, sLevel);
			printZ3NodeAxiom(t, toAssert);
			__debugPrint(logAxiom, "\n---------------------\n\n");
		} else {
			__debugPrint(logFile, "\n---------------------\nAssertion Add(@%d, Level %d):\n", line, sLevel);
			printZ3Node(t, toAssert);
			__debugPrint(logFile, "\n---------------------\n\n");

			__debugPrint(logAxiom, "\n---------------------\nAssertion Add(@%d, Level %d):\n", line, sLevel);
			printZ3NodeAxiom(t, toAssert);
			__debugPrint(logAxiom, "\n---------------------\n\n");
		}
	}
#endif

	if (searchStart == 1) {
		Z3_theory_assert_axiom(t, toAssert);
	} else {
		Z3_context ctx = Z3_theory_get_context(t);
		Z3_assert_cnstr(ctx, toAssert);
	}


}

void addAxiom_Theory(Z3_theory t, Z3_ast toAssert, int line, bool display) {
	if (toAssert == NULL) {
		return;
	}

	Z3_theory_assert_axiom(t, toAssert);

#ifdef DEBUGLOG
	if (display) {
		if (searchStart == 1) {
			__debugPrint(logFile, "\n---------------------\nAxiom Add(@%d, Level %d):\n", line, 0);
			printZ3Node(t, toAssert);
			__debugPrint(logFile, "\n---------------------\n\n");

			__debugPrint(logAxiom, "\n---------------------\nAxiom Add(@%d, Level %d):\n", line, 0);
			printZ3NodeAxiom(t, toAssert);
			__debugPrint(logAxiom, "\n---------------------\n\n");
		} else {
			__debugPrint(logFile, "\n---------------------\nAssertion Add(@%d, Level %d):\n", line, 0);
			printZ3Node(t, toAssert);
			__debugPrint(logFile, "\n---------------------\n\n");

			__debugPrint(logAxiom, "\n---------------------\nAssertion Add(@%d, Level %d):\n", line, 0);
			printZ3NodeAxiom(t, toAssert);
			__debugPrint(logAxiom, "\n---------------------\n\n");
		}
	}
#endif
}

/*
 *
 */
void checkInputVar(Z3_theory t, Z3_ast node) {

	Z3_context ctx = Z3_theory_get_context(t);
	T_TheoryType nodeType = getNodeType(t, node);
	if (nodeType == my_Z3_Var) {
		intInputVarMap[node] = 1;
	}
	if (nodeType == my_Z3_Str_Var) {
		std::string vName = std::string(Z3_ast_to_string(ctx, node));
		if (vName.length() >= 11 && vName.substr(0, 11) == "__cOnStStR_") {
			return;
		}
		if (vName.length() >= 3 && vName.substr(0, 3) == "$$_") {
			printf("> Error: please don't define a variable with a prefix \"$$_\" (");
			printf("%s). Abort\n\n", Z3_ast_to_string(ctx, node));
			exit(0);
		}
		inputVarMap[node] = 1;
	} else if (getNodeType(t, node) == my_Z3_Func) {
		Z3_app func_app = Z3_to_app(ctx, node);
		int argCount = Z3_get_app_num_args(ctx, func_app);

		AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
		Z3_func_decl funcd = Z3_get_app_decl(ctx, Z3_to_app(ctx, node));

		for (int i = 0; i < argCount; i++) {
			Z3_ast argAst = Z3_get_app_arg(ctx, func_app, i);
			if (funcd == td->Length && getNodeType(t, argAst) == my_Z3_Str_Var) {
				inputVarInLen.insert(argAst);
			}
			checkInputVar(t, argAst);
		}
	} else if (nodeType == my_Z3_Regex_Var) {
		printf("> Error: please don't define a separate Regex variable (");
		printf("%s). Abort\n\n", Z3_ast_to_string(ctx, node));
		exit(0);
	} else {
		std::string vName = std::string(Z3_ast_to_string(ctx, node));
	}
}

/**
   \brief Check whether the logical context is satisfiable, and compare the result with the expected result.
   If the context is satisfiable, then display the model.
 */
void check(Z3_theory t)
{
	Z3_context ctx = Z3_theory_get_context(t);

	Z3_model m      = 0;
	Z3_lbool result = Z3_check_and_get_model(ctx, &m);
	if (unknownResult == true && result == Z3_L_FALSE)
		result = Z3_L_UNDEF;
	if (printingConstraints){
		printf(">> Arithmetic Constraints\n");
		for (const auto& s : constraintSet.arithmeticConstraints)
			printf("%s\n", s.c_str());
		printf(">> String Constraints\n");
		for (const auto& s : constraintSet.stringConstraints)
			printf("%s\n", s.c_str());
		printf(">> Regular Constraints\n");
		for (const auto& s : constraintSet.regularConstraints)
			printf("%s\n", s.c_str());
		printf(">> Other Constraints\n");
		for (const auto& s : constraintSet.otherConstraints)
			printf("%s\n", s.c_str());
	}

	else switch (result) {
	case Z3_L_FALSE:
		printf("================================================\n");
		printf(">> UNSAT\n");
		printf("================================================\n");
		break;
	case Z3_L_UNDEF:
		printf(">> UNKNOWN\n");
		break;
	case Z3_L_TRUE:

#if 0
		if (ourGrm.size() == 0) {
			printf("OverApprox: sat\n");
			std::map<std::string, std::vector<std::vector<std::string>>> combinationOverVariables = collectCombinationOverVariables(t);
			std::map<std::string, int> currentLength = collectCurrentLength(t);

			underapproxController(combinationOverVariables, currentLength, inputFile);
		}
		else {
			printf("================================================\n");
			printf(">> SAT\n");
			printf("------------------------------------------------\n");
			printf("%s\n", Z3_model_to_string(ctx, m));
			printf("================================================\n");
		}

		break;
#else
		if (skipUnderApprox){
			printf("================================================\n");
			printf("%s", Z3_model_to_string(ctx, m));
			printf("================================================\n");
			printf("\n>> SAT\n");
		}
		else {
			printf("\n>> SAT\n");
		}
		break;
#endif
	}
	if (m) {
		Z3_del_model(ctx, m);
	}
}

void overApproxController() {
	if (!printingConstraints)
		printf("Running Over Approximation\n");
#ifdef DEBUGLOG
	__debugPrint(logFile, "***********************************************\n");
	__debugPrint(logFile, "*              Trau_theory                     *\n");
	__debugPrint(logFile, "-----------------------------------------------\n");
#endif
	if (inputFile_converted == "") {
		printf("No input file is provided.\n");
		return;
	}
	Z3_context ctx = mk_context();
	Z3_theory Th = mk_theory(ctx);
	ctx = Z3_theory_get_context(Th);

	//  setAlphabet();

	// load cstr from inputFile
	Z3_ast fs = Z3_parse_smtlib2_file(ctx, inputFile_converted.c_str(), 0, 0, 0, 0, 0, 0);

	// check input variable. Stop if invalid stuffs are found
	checkInputVar(Th, fs);

	emptyConstStr = mk_str_value(Th, "");

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n***********************************************\nInput loaded:\n-----------------------------------------------\n");
	printZ3Node(Th, fs);
	__debugPrint(logFile, "\n-----------------------------------------------\n\n");
#endif

	Z3_assert_cnstr(ctx, fs);
	check(Th);

	// clean up

	Z3_del_context(ctx);
}
