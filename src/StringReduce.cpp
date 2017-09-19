#include "StringTheory.h"

extern int nondeterministicCounter;
extern bool havingGrmConstraints;
extern std::map<Z3_ast, Z3_ast> grm_astNode_map;
extern std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> containPairBoolMap;

extern std::map<std::string, std::string> subStrStrMap;

extern std::map<std::string, std::pair<std::string, std::string>> indexOfStrMap;
extern std::map<std::string, std::pair<std::string, std::string>> lastIndexOfStrMap;
extern std::map<std::string, std::string> endsWithStrMap;
extern std::map<std::string, std::string> startsWithStrMap;

extern std::map<std::pair<Z3_ast, Z3_ast>, std::vector<Z3_ast>> indexOf_toAstMap;
extern std::map<std::pair<Z3_ast, Z3_ast>, std::vector<Z3_ast>> lastIndexOf_toAstMap;

extern std::map<std::string, std::string> replaceStrMap;
extern std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> replaceNodeMap;

extern std::map<std::string, std::string> replaceAllStrMap;
extern std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> replaceAllNodeMap;

extern std::map<Z3_ast, Z3_ast> toUpperMap;
extern std::map<Z3_ast, Z3_ast> toLowerMap;

extern std::map<Z3_ast, Z3_ast> carryOn;

//std::map<std::string, std::set<char>> charSet;
//
//std::map<Z3_ast, std::vector<std::string>> eqMap;
//std::map<std::pair<Z3_ast, Z3_ast>, int> eqList;

//bool defaultCharSet = true;
//
//
///*
// *
// */
//std::string encodeToEscape(char c) {
//  int idx = (unsigned char) c;
//  if (0 <= idx && idx <= 255) {
//    return escapeDict[idx];
//  } else {
//    printf("> Error: should not get here @ %d.\n", __LINE__);
//    exit(0);
//  }
//}
//
///*
// *
// */
//
////void setAlphabet() {
////  if (defaultCharSet) {
////    // a string in C notion cannot contain a char '\0'
////    charSetSize = 255;
////    charSet = new char[charSetSize];
////    int idx = 0;
////    // small letters
////    for (int i = 97; i < 123; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // caps
////    for (int i = 65; i < 91; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // numbers
////    for (int i = 48; i < 58; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // printable marks - 1
////    for (int i = 32; i < 48; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // printable marks - 2
////    for (int i = 58; i < 65; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // printable marks - 3
////    for (int i = 91; i < 97; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // printable marks - 4
////    for (int i = 123; i < 127; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // non-printable - 1
////    for (int i = 1; i < 32; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////    // non-printable - 2
////    for (int i = 127; i < 256; i++) {
////      charSet[idx] = (char) i;
////      charSetLookupTable[charSet[idx]] = idx;
////      idx++;
////    }
////  } else {
////    const char setset[] = { 'a', 'b', 'c' };
////    int fSize = sizeof(setset) / sizeof(char);
////
////    charSet = new char[fSize];
////    charSetSize = fSize;
////    for (int i = 0; i < charSetSize; i++) {
////      charSet[i] = setset[i];
////      charSetLookupTable[setset[i]] = i;
////    }
////  }
////}
//
//
//
///****************************************
// *  Z3 input parser doesn't understand constant string
// *  So, we pass const string by adding a special mark "$",
// * --------------------------------------
// * "__cOnStStR__x23_x5c_x6e_x5c_x22_x53"
// ****************************************/
//inline bool isValidHexDigit(char c) {
//  if (('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) {
//    return true;
//  }
//  return false;
//}
//
///*
// *
// */
//inline int hexDigitToInt(char a) {
//  if ('0' <= a && a <= '9')
//    return a - '0';
//  else if ('a' <= a && a <= 'f')
//    return 10 + a - 'a';
//  else if ('A' <= a && a <= 'F')
//    return 10 + a - 'A';
//  else
//    return 0;
//}
//
///*
// *
// */
//inline int twoHexDigitToChar(char a, char b) {
//  return (hexDigitToInt(a) * 16 + hexDigitToInt(b));
//}
//
//void printTest(Z3_theory t, Z3_ast node, int line) {
//	__debugPrint(logFile, "\n%d Print Test: \n", line);
//	printZ3Node(t, node);
//	__debugPrint(logFile, ":\n");
//	for (std::vector<std::string>::iterator it = eqMap[node].begin(); it != eqMap[node].end(); it++){
//		__debugPrint(logFile, "@%d\t %s \n", line, it->c_str());
//	}
//}
//
///*
// *
// */
//std::string convertInputTrickyConstStr(std::string inputStr) {
//  std::string outputStr = "";
//  std::string innerStr = inputStr.substr(11, inputStr.length() - 11);
//  int innerStrLen = innerStr.length();
//  if (innerStrLen % 4 != 0) {
//    fprintf(stdout, "> Error: Constant string conversion error. Exit.\n");
//    fprintf(stdout, "         Input encoding: %s\n", inputStr.c_str());
//    fflush(stdout);
//    exit(0);
//  }
//  for (int i = 0; i < (innerStrLen / 4); i++) {
//    std::string cc = innerStr.substr(i * 4, 4);
//    if (cc[0] == '_' && cc[1] == 'x' && isValidHexDigit(cc[2]) && isValidHexDigit(cc[3])) {
//      char dc = twoHexDigitToChar(cc[2], cc[3]);
////      fprintf(stdout, "> Error: Character in a constant string is not in the system alphabet. %s\n", cc.c_str());
////      fprintf(stdout, "         Please set the character set accordingly.\n");
////      fflush(stdout);
////      exit(0);
//      // Check whether the input character in the charSet
////      if (charSetLookupTable.find(dc) == charSetLookupTable.end()) {
////        fprintf(stdout, "> Error: Character '%s' in a constant string is not in the system alphabet.\n", encodeToEscape(dc).c_str());
////        fprintf(stdout, "         Please set the character set accordingly.\n");
////        fflush(stdout);
////        exit(0);
////      }
//      outputStr = outputStr + std::string(1, dc);
//    }
//  }
//  return outputStr;
//}
////

/*
 * check if leng = 1 --> skip generate new constraints in indexof, lastindexof...
 */
bool canSkipExt(Z3_theory t, Z3_ast node){
	bool canSkip = false;
	if (getNodeType(t, node) == my_Z3_ConstStr) {
		std::string nodeStr = getConstStrValue(t, node);
		if (nodeStr.length() == 1) {
			return true;
		}
	}
	return false;
}
/*
 * convert a node to string
 */
std::string exportNodeName(Z3_theory t,  Z3_ast const args[], Z3_func_decl name) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	std::string node01 = "";
	std::string node02 = "";
	std::string node03 = "";

	if (isDetAutomatonFunc(t, args[0])) {
		Z3_ast tmp = Z3_get_app_arg(ctx, Z3_to_app(ctx, args[0]), 0);
		node01 = "\"" + customizeString(Z3_ast_to_string(ctx, tmp)) + "\"";
	}
	else if (isConstStr(t, args[0])){
		node01 = "\"" + customizeString(Z3_ast_to_string(ctx, args[0])) + "\"";
	}
	else
		node01 = Z3_ast_to_string(ctx, args[0]);

	if (isDetAutomatonFunc(t, args[1])) {
		Z3_ast tmp = Z3_get_app_arg(ctx, Z3_to_app(ctx, args[1]), 0);
		node02 = "\"" + customizeString(Z3_ast_to_string(ctx, tmp)) + "\"";
	}
	else if (isConstStr(t, args[1])){
		node02 = "\"" + customizeString(Z3_ast_to_string(ctx, args[1])) + "\"";
	}
	else
		node02 = Z3_ast_to_string(ctx, args[1]);

	if (name == td->Replace) {
		if (isDetAutomatonFunc(t, args[2])) {
			Z3_ast tmp = Z3_get_app_arg(ctx, Z3_to_app(ctx, args[2]), 0);
			node03 = "\"" + customizeString(Z3_ast_to_string(ctx, tmp)) + "\"";
		}
		else if (isConstStr(t, args[2])){
			node03 = "\"" + customizeString(Z3_ast_to_string(ctx, args[2])) + "\"";
		}
		else
			node03 = Z3_ast_to_string(ctx, args[2]);
	}
	else if (name == td->ReplaceAll){
		if (isDetAutomatonFunc(t, args[2])) {
			Z3_ast tmp = Z3_get_app_arg(ctx, Z3_to_app(ctx, args[2]), 0);
			node03 = "\"" + customizeString(Z3_ast_to_string(ctx, tmp)) + "\"";
		}
		else if (isConstStr(t, args[2])){
			node03 = "\"" + customizeString(Z3_ast_to_string(ctx, args[2])) + "\"";
		}
		else
			node03 = Z3_ast_to_string(ctx, args[2]);
	}
	else if (name == td->SubString){
		node03 = Z3_ast_to_string(ctx, args[2]);
	}

	if (name == td->Contains)
		return "(Contains " + node01 + " " + node02 + ")";
	else if (name == td->LastIndexof)
		return "(LastIndexof " + node01 + " " + node02 + ")";
	else if (name == td->Indexof)
		return "(Indexof " + node01 + " " + node02 + ")";
	else if (name == td->StartsWith)
		return "(StartsWith " + node01 + " " + node02 + ")";
	else if (name == td->EndsWith)
		return "(EndsWith " + node01 + " " + node02 + ")";
	else if (name == td->Replace) {
		return "(Replace " + node01 + " " + node02 + " " + node03 + ")";
	}
	else if (name == td->ReplaceAll)
		return "(ReplaceAll " + node01 + " " + node02 + " " + node03 + ")";
	else if (name == td->SubString)
		return "(Substring " + node01 + " " + node02 + " " + node03 + ")";
	else
		return NULL;
}

/*
 *
 */
void pushVectors(Z3_ast node, std::vector<Z3_ast> &v0, std::vector<Z3_ast> &v1, std::vector<Z3_ast> &v2){
	v0.push_back(node);
	v1.push_back(node);
	v2.push_back(node);
}

/*
 *
 */
void pushVectors(Z3_ast node, std::vector<Z3_ast> &v0, std::vector<Z3_ast> &v1){
	v0.push_back(node);
	v1.push_back(node);
}

/*
 *
 */
void pushVectors(Z3_ast node, std::vector<Z3_ast> &v0){
	v0.push_back(node);
}

/*
 *
 */
Z3_ast reduce_replaceAll(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	/* convert to string, prepare for replaceStrMap */
	std::string nodeName = exportNodeName(t, args, td->ReplaceAll);

	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr && getNodeType(t, args[2]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		std::string arg2Str = getConstStrValue(t, args[2]);
		if (arg0Str.find(arg1Str) != std::string::npos) {
			while (arg0Str.find(arg1Str) != std::string::npos) {
				int index1 = arg0Str.find(arg1Str);
				int index2 = index1 + arg1Str.length();
				std::string substr0 = arg0Str.substr(0, index1);
				std::string substr2 = arg0Str.substr(index2);
				arg0Str = substr0 + arg2Str + substr2;
			}
			replaceAllStrMap[nodeName] = "true";
			return mk_str_value(t, arg0Str.c_str());
		} else {
			replaceAllStrMap[nodeName] = "false";
			return args[0];
		}
	} else {
		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars00;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1])) != indexOf_toAstMap.end())
			tmpInternalVars00 = indexOf_toAstMap[std::make_pair(args[0], args[1])];

		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);

		if (tmpInternalVars00.size() > 0) {
			x1 = tmpInternalVars00[0];
			x2 = tmpInternalVars00[1];
		}

		Z3_ast result = mk_internal_string_var(t);


		// condAst = Contains(args[0], args[1])
		Z3_ast condAst_arg00 = registerContain(t, args[0], args[1]);
		std::string boolName = Z3_ast_to_string(ctx, condAst_arg00);
		replaceAllStrMap[nodeName] = boolName;

		bool update = true;
		bool canSkip = canSkipExt(t, args[1]);

		// -----------------------
		// case 01

		std::vector<Z3_ast> thenItems00;
		std::vector<Z3_ast> thenItems01;
		std::vector<Z3_ast> thenItems02;

		//  args[0] = x1 . args[1] . x2
		Z3_ast arg0_tmp = Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update));
		pushVectors(arg0_tmp, thenItems00, thenItems01, thenItems02);

		Z3_ast condAst_x1 = registerContain(t, x1, args[1]);
		pushVectors(Z3_mk_not(ctx, condAst_x1), thenItems00, thenItems01, thenItems02);

		Z3_ast condAst_x2 = registerContain(t, x2, args[1]);
		pushVectors(Z3_mk_implies(ctx, condAst_x2, condAst_arg00), thenItems00, thenItems01, thenItems02);

		if (!canSkip) {
			//  args[0]  = x_n1 . x_m1 /\ |x_n1| = |x1| + |args[1]| - 1 /\ ! contains(x_n1, args[1])
			Z3_ast tmpLenItems01[3] = {mk_length(t, x1), mk_length(t, args[1]), mk_int(ctx, -1) };
			Z3_ast tmpLen01 = Z3_mk_add(ctx, 3, tmpLenItems01);

			Z3_ast x_n1 = mk_internal_string_var(t);
			Z3_ast x_m1 = mk_internal_string_var(t);
			if (tmpInternalVars00.size() > 0) {
				assert(tmpInternalVars00.size() == 4);
				x_n1 = tmpInternalVars00[2];
				x_m1 = tmpInternalVars00[3];
			}

			pushVectors(Z3_mk_eq(ctx, args[0], mk_concat(t, x_n1, x_m1, update)), thenItems00, thenItems01, thenItems02);
			pushVectors(Z3_mk_eq(ctx, mk_length(t, x_n1), tmpLen01), thenItems00, thenItems01, thenItems02);

			Z3_ast condAst00n = registerContain(t, x_n1, args[1]);
			pushVectors(Z3_mk_not(ctx, condAst00n), thenItems00, thenItems01, thenItems02);

			pushVectors(Z3_mk_implies(ctx, condAst_x1, condAst00n), thenItems00, thenItems01, thenItems02);
			pushVectors(Z3_mk_implies(ctx, condAst00n, condAst_arg00), thenItems00, thenItems01, thenItems02);

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x_n1, x_m1};
			carryOn[condAst_arg00] = Z3_mk_eq(ctx, mk_length(t, x_n1), tmpLen01);
		}
		else {
			pushVectors(Z3_mk_implies(ctx, condAst_x1, condAst_arg00), thenItems00, thenItems01, thenItems02);
			pushVectors(Z3_mk_implies(ctx, condAst_x2, condAst_arg00), thenItems00, thenItems01, thenItems02);
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		pushVectors(Z3_mk_not(ctx, condAst_x2), thenItems00);
		pushVectors(Z3_mk_eq(ctx, result, mk_concat(t, x1, mk_concat(t, args[2], x2, update), update)), thenItems00);

		// -----------------------
		// case 2
		// condAst_x2 = registerContain(t, x2, args[1]);
		//  x2 = x3 . args[1] . x4

		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars01;
		if (indexOf_toAstMap.find(std::make_pair(x2, args[1])) != indexOf_toAstMap.end())
			tmpInternalVars01 = indexOf_toAstMap[std::make_pair(x2, args[1])];

		Z3_ast x3 = mk_internal_string_var(t);
		Z3_ast x4 = mk_internal_string_var(t);

		if (tmpInternalVars00.size() > 0) {
			x3 = tmpInternalVars01[0];
			x4 = tmpInternalVars01[1];
		}

		Z3_ast x2_tmp = Z3_mk_eq(ctx, x2, mk_concat(t, x3, mk_concat(t, args[1], x4, update), update));
		pushVectors(x2_tmp, thenItems01, thenItems02);

		Z3_ast condAst_x3 = registerContain(t, x3, args[1]);
		pushVectors(Z3_mk_not(ctx, condAst_x3), thenItems01, thenItems02);

		Z3_ast condAst_x4 = registerContain(t, x4, args[1]);

		if (! canSkip) {
			Z3_ast x_n2 = mk_internal_string_var(t);
			Z3_ast x_m2 = mk_internal_string_var(t);
			if (tmpInternalVars01.size() > 0) {
				assert(tmpInternalVars01.size() == 4);
				x_n2 = tmpInternalVars01[2];
				x_m2 = tmpInternalVars01[3];
			}


			Z3_ast tmpLenItems02[3] = {mk_length(t, x3), mk_length(t, args[1]), mk_int(ctx, -1) };
			Z3_ast tmpLen02 = Z3_mk_add(ctx, 3, tmpLenItems02);
			pushVectors(Z3_mk_eq(ctx, x2, mk_concat(t, x_n2, x_m2, update)), thenItems01, thenItems02);
			pushVectors(Z3_mk_eq(ctx, mk_length(t, x_n2), tmpLen02), thenItems01, thenItems02);

			Z3_ast condAst02n = registerContain(t, x_n2, args[1]);
			pushVectors(Z3_mk_not(ctx, condAst02n), thenItems01, thenItems02);

			pushVectors(Z3_mk_implies(ctx, condAst02n, condAst_x2), thenItems01, thenItems02);
			pushVectors(Z3_mk_implies(ctx, condAst_x3, condAst02n), thenItems01, thenItems02);

			indexOf_toAstMap[std::make_pair(x2, args[1])] = {x3, x4, x_n2, x_m2};
			carryOn[condAst_x2] = Z3_mk_eq(ctx, mk_length(t, x_n2), tmpLen02);
		}
		else {
			pushVectors(Z3_mk_implies(ctx, condAst_x3, condAst_x2), thenItems01, thenItems02);
			pushVectors(Z3_mk_implies(ctx, condAst_x4, condAst_x2), thenItems01, thenItems02);

			indexOf_toAstMap[std::make_pair(x2, args[1])] = {x3, x4};
		}

		thenItems01.push_back(Z3_mk_eq(ctx, result, mk_concat(t, x1, mk_concat(t, args[2], mk_concat(t, x3, mk_concat(t, args[2], x4, update), update), update), update)));
		thenItems01.push_back(Z3_mk_not(ctx, condAst_x4));



		// -----------------------
		// case 3
		// condAst04 = registerContain(t, x4, args[1]);

		//  x4 = x5 . args[1] . x6

		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars02;
		if (indexOf_toAstMap.find(std::make_pair(x4, args[1])) != indexOf_toAstMap.end())
			tmpInternalVars02 = indexOf_toAstMap[std::make_pair(x4, args[1])];

		Z3_ast x5 = mk_internal_string_var(t);
		Z3_ast x6 = mk_internal_string_var(t);

		if (tmpInternalVars00.size() > 0) {
			x5 = tmpInternalVars02[0];
			x6 = tmpInternalVars02[1];
		}

		thenItems02.push_back(Z3_mk_eq(ctx, x4, mk_concat(t, x5, mk_concat(t, args[1], x6, update), update)));
		Z3_ast condAst_x5 = registerContain(t, x5, args[1]);
		thenItems02.push_back(Z3_mk_not(ctx, condAst_x5));

		Z3_ast condAst_x6 = registerContain(t, x6, args[1]);
		thenItems02.push_back(Z3_mk_not(ctx, condAst_x6));

		if (!canSkip) {
			Z3_ast tmpLenItems04[3] = {mk_length(t, x4), mk_length(t, args[1]), mk_int(ctx, -1) };
			Z3_ast tmpLen04 = Z3_mk_add(ctx, 3, tmpLenItems04);

			Z3_ast x_n4 = mk_internal_string_var(t);
			Z3_ast x_m4 = mk_internal_string_var(t);
			if (tmpInternalVars02.size() > 0) {
				assert(tmpInternalVars02.size() == 4);
				x_n4 = tmpInternalVars02[2];
				x_m4 = tmpInternalVars02[3];
			}

			thenItems02.push_back(Z3_mk_eq(ctx, x4, mk_concat(t, x_n4, x_m4, update)));
			thenItems02.push_back(Z3_mk_eq(ctx, mk_length(t, x_n4), tmpLen04));

			Z3_ast condAst04n = registerContain(t, x_n4, args[1]);
			thenItems02.push_back(Z3_mk_not(ctx, condAst04n));

			thenItems02.push_back(Z3_mk_implies(ctx, condAst_x5, condAst04n));
			thenItems02.push_back(Z3_mk_implies(ctx, condAst04n, condAst_x4));

			indexOf_toAstMap[std::make_pair(x4, args[1])] = {x5, x6, x_n4, x_m4};
			carryOn[condAst_x4] = Z3_mk_eq(ctx, mk_length(t, x_n4), tmpLen04);
		}
		else {
			thenItems02.push_back(Z3_mk_implies(ctx, condAst_x5, condAst_x4));
			thenItems02.push_back(Z3_mk_implies(ctx, condAst_x6, condAst_x4));

			indexOf_toAstMap[std::make_pair(x4, args[1])] = {x5, x6};
		}

		thenItems02.push_back(Z3_mk_eq(ctx, result, mk_concat(t, x1, mk_concat(t, args[2], mk_concat(t, x3, mk_concat(t, args[2], mk_concat(t, x5, mk_concat(t, args[2], x6, update), update), update), update), update), update)));

		Z3_ast elseBranch = Z3_mk_eq(ctx, result, args[0]);

		Z3_ast ite04 = Z3_mk_ite(ctx, condAst_x4, mk_and_fromVector(t, thenItems02), mk_and_fromVector(t, thenItems01));
		Z3_ast ite02 = Z3_mk_ite(ctx, condAst_x2, ite04, mk_and_fromVector(t, thenItems00));

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg00, ite02, elseBranch);
		replaceAllNodeMap[std::make_pair(args[0], std::make_pair(args[1], args[2]))] = result;
		return result;
	}
}

/*
 *
 */
Z3_ast reduce_toUpper(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	if (getNodeType(t, args[0]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string tmp = "";
		for (unsigned int i = 0 ; i < arg0Str.length(); ++i) {
			if (arg0Str[i] >= 97 && arg0Str[i] <= 122)
				tmp = tmp + (char)(arg0Str[i] - 32);
			else
				tmp = tmp + arg0Str[i];
		}
		return mk_str_value(t, tmp.c_str());
	}
	else {
		Z3_ast ts0 = mk_internal_string_var(t);
		breakdownAssert = Z3_mk_eq(ctx, mk_length(t, ts0), mk_length(t, args[0]));
		toUpperMap[ts0] = args[0];
		return ts0;
	}
}

/*
 *
 */
Z3_ast reduce_toLower(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	if (getNodeType(t, args[0]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string tmp = "";
		for (unsigned int i = 0 ; i < arg0Str.length(); ++i) {
			if (arg0Str[i] >= 65 && arg0Str[i] <= 90)
				tmp = tmp + (char)(arg0Str[i] + 32);
			else
				tmp = tmp + arg0Str[i];
		}
		return mk_str_value(t, tmp.c_str());
	}
	else {
		Z3_ast ts0 = mk_internal_string_var(t);
		breakdownAssert = Z3_mk_eq(ctx, mk_length(t, ts0), mk_length(t, args[0]));
		toLowerMap[ts0] = args[0];
		return ts0;
	}
}

/*
 *
 */
Z3_ast reduce_contains(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast reduceAst = NULL;

	if (args[0] == args[1]) {
		return Z3_mk_true(ctx);
	}

	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.find(arg1Str) != std::string::npos)
			reduceAst = Z3_mk_true(ctx);
		else
			reduceAst = Z3_mk_false(ctx);
	} else {
		Z3_ast ts0 = mk_internal_string_var(t);
		Z3_ast ts1 = mk_internal_string_var(t);

		reduceAst = registerContain(t, args[0], args[1]);  // reduceAst = Contains(args[0], args[1])

		bool update = true;
		breakdownAssert = Z3_mk_eq(ctx, reduceAst, Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, mk_concat(t, args[1], ts1, update), update)));
	}

	/* transitive property */
	for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it = containPairBoolMap.begin(); it != containPairBoolMap.end(); ++it) {
		if (it->first.first == args[1]) {
			Z3_ast tmp = registerContain(t, args[0], it->first.second);
			Z3_ast tmp01 = Z3_mk_eq(ctx, tmp, Z3_mk_true(ctx));

			std::vector<Z3_ast> ands;
			ands.push_back(it->second);
			ands.push_back(reduceAst);
			Z3_ast tmp02 = Z3_mk_implies(ctx, mk_and_fromVector(t, ands), tmp01);
			addAxiom(t, tmp02, __LINE__, true);
		}
	}
	return reduceAst;
}

/*
 *
 */
Z3_ast reduce_startswith(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	/* convert to string, prepare for startsWithStrMap */
	std::string nodeName = exportNodeName(t, args, td->StartsWith);

	Z3_ast reduceAst = NULL;
	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.length() < arg1Str.length()) {
			reduceAst = Z3_mk_false(ctx);
		} else {
			if (arg0Str.substr(0, arg1Str.length()) == arg1Str) {
				startsWithStrMap[nodeName] = "true";
				reduceAst = Z3_mk_true(ctx);
			} else {
				startsWithStrMap[nodeName] = "false";
				reduceAst = Z3_mk_false(ctx);
			}
		}
	} else {
		Z3_ast resBoolVar = registerStartsWith(t, args[0], args[1]);
		Z3_ast ts0 = mk_internal_string_var(t);
		Z3_ast ts1 = mk_internal_string_var(t);

		std::string boolVar = Z3_ast_to_string(ctx, resBoolVar);
		startsWithStrMap[nodeName] = boolVar;
		// boolVar = startswith(arg[0], arg[1])
		// --------------------------------------------
		std::vector<Z3_ast> innerItems;
		bool update;
		innerItems.push_back( Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, ts1, update)) );
		innerItems.push_back( Z3_mk_eq(ctx, mk_length(t, ts0), mk_length(t, args[1])) );
		innerItems.push_back( Z3_mk_ite(ctx, Z3_mk_eq(ctx, ts0, args[1]), Z3_mk_eq(ctx, resBoolVar, Z3_mk_true(ctx)), Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx) ) ) );
		Z3_ast then1 = mk_and_fromVector(t, innerItems);
		breakdownAssert = Z3_mk_ite(ctx, Z3_mk_ge(ctx, mk_length(t, args[0]), mk_length(t, args[1])), then1, Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx) ) );
		reduceAst = resBoolVar;
	}
	return reduceAst;
}

/*
 *
 */
Z3_ast reduce_endswith(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast reduceAst = NULL;
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	/* convert to string, prepare for endsWithStrMap */
	std::string nodeName = exportNodeName(t, args, td->EndsWith);

	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, nodeName.c_str());

	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.length() < arg1Str.length()) {
			reduceAst = Z3_mk_false(ctx);
		} else {
			if (arg0Str.substr(arg0Str.length() - arg1Str.length(), arg1Str.length()) == arg1Str) {
				endsWithStrMap[nodeName] = "true";
				reduceAst = Z3_mk_true(ctx);
			} else {
				endsWithStrMap[nodeName] = "false";
				reduceAst = Z3_mk_false(ctx);
			}
		}
	} else {
		Z3_ast resBoolVar = registerEndsWith(t, args[0], args[1]);
		Z3_ast ts0 = mk_internal_string_var(t);
		Z3_ast ts1 = mk_internal_string_var(t);
		std::string boolVar = Z3_ast_to_string(ctx, resBoolVar);
		endsWithStrMap[nodeName] = boolVar;
		// boolVar = endswith(arg[0], arg[1])
		// --------------------------------------------
		std::vector<Z3_ast> innerItems;
		bool update;
		innerItems.push_back( Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, ts1, update)) );
		innerItems.push_back( Z3_mk_eq(ctx, mk_length(t, ts1), mk_length(t, args[1])) );
		innerItems.push_back( Z3_mk_ite(ctx, Z3_mk_eq(ctx, ts1, args[1]), Z3_mk_eq(ctx, resBoolVar, Z3_mk_true(ctx)), Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx) ) ) );
		Z3_ast then1 = mk_and_fromVector(t, innerItems);
		breakdownAssert = Z3_mk_ite(ctx, Z3_mk_ge(ctx, mk_length(t, args[0]), mk_length(t, args[1])), then1, Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx) ) );
		reduceAst = resBoolVar;
	}
	return reduceAst;
}

/*
 *
 */
Z3_ast reduce_indexof(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	/* convert to string, prepare for indexOfStrMap */
	std::string nodeName = exportNodeName(t, args, td->Indexof);

	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, nodeName.c_str());

	/* doing the real work */
	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.find(arg1Str) != std::string::npos) {
			int index = arg0Str.find(arg1Str);
			indexOfStrMap[nodeName] = std::make_pair("", std::to_string(index));
			return mk_int(ctx, index);
		} else {
			indexOfStrMap[nodeName] = std::make_pair("", "-1");
			return mk_int(ctx, -1);
		}
	} else {
		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1])) != indexOf_toAstMap.end())
			tmpInternalVars = indexOf_toAstMap[std::make_pair(args[0], args[1])];

		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);

		if (tmpInternalVars.size() > 0) {
			x1 = tmpInternalVars[0];
			x2 = tmpInternalVars[1];
		}

		Z3_ast indexAst = mk_internal_int_var(t);

		// condAst = Contains(args[0], args[1])
		Z3_ast condAst_arg0 = registerContain(t, args[0], args[1]);

		std::string boolVar = Z3_ast_to_string(ctx, condAst_arg0);

		// -----------------------
		bool update;
		// true branch
		std::vector<Z3_ast> thenItems;
		//  args[0] = x1 . args[1] . x2
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update)));
		Z3_ast condAst_x1 = registerContain(t, x1, args[1]);
		thenItems.push_back(Z3_mk_not(ctx, condAst_x1));


		//  indexAst = |x1|
		thenItems.push_back(Z3_mk_eq(ctx, indexAst, mk_length(t, x1)));

		indexOfStrMap[nodeName] = std::make_pair(boolVar, "len_" + std::string(Z3_ast_to_string(ctx, x1)));

		if (!canSkipExt(t, args[1])) {
			//     args[0]  = x3 . x4
			//  /\ |x3| = |x1| + |args[1]| - 1
			//  /\ ! contains(x3, args[1])
			Z3_ast x3 = mk_internal_string_var(t);
			Z3_ast x4 = mk_internal_string_var(t);
			if (tmpInternalVars.size() > 0) {
				assert(tmpInternalVars.size() == 4);
				x3 = tmpInternalVars[2];
				x4 = tmpInternalVars[3];
			}
			Z3_ast tmpLenItems[3] = { mk_length(t, x1), mk_length(t, args[1]), mk_int(ctx, -1) };
			Z3_ast tmpLen = Z3_mk_add(ctx, 3, tmpLenItems);

			thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
			Z3_ast condAst_x3 = registerContain(t, x3, args[1]);
			thenItems.push_back(Z3_mk_not(ctx, condAst_x3));
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_x3));
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x3, condAst_arg0));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x3, x4};

			carryOn[condAst_arg0] = Z3_mk_eq(ctx, mk_length(t, x3), tmpLen);
		}
		else {
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_arg0));
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		// -----------------------
		// false branch
		Z3_ast elseBranch = Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1));

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg0, mk_and_fromVector(t, thenItems), elseBranch);
		return indexAst;
	}
}


/*
 *
 */
Z3_ast reduce_lastindexof(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	/* convert to string, prepare for lastIndexOfStrMap */
	std::string nodeName = exportNodeName(t, args, td->LastIndexof);

	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, nodeName.c_str());

	/* doing the real work */
	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.rfind(arg1Str) != std::string::npos) {
			int index = arg0Str.rfind(arg1Str);
			lastIndexOfStrMap[nodeName] = std::make_pair("", std::to_string(index));
			return mk_int(ctx, index);
		} else {
			lastIndexOfStrMap[nodeName] = std::make_pair("", "-1");
			return mk_int(ctx, -1);
		}
	} else {
		std::vector<Z3_ast> tmpInternalVars;
		if (lastIndexOf_toAstMap.find(std::make_pair(args[0], args[1])) != lastIndexOf_toAstMap.end())
			tmpInternalVars = lastIndexOf_toAstMap[std::make_pair(args[0], args[1])];

		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);

		if (tmpInternalVars.size() > 0) {
			x1 = tmpInternalVars[0];
			x2 = tmpInternalVars[1];
		}
		Z3_ast indexAst = mk_internal_int_var(t);

		bool update;

		Z3_ast condAst_arg0 = registerContain(t, args[0], args[1]);

		std::string boolVar = Z3_ast_to_string(ctx, condAst_arg0);
		//----------------------------
		// true branch
		std::vector<Z3_ast> thenItems;
		thenItems.push_back(Z3_mk_ge(ctx, indexAst, mk_int(ctx, 0)));
		//  args[0] = x1 . args[1] . x2
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update)));
		thenItems.push_back(Z3_mk_eq(ctx, indexAst, mk_length(t, x1)));

		//  x2 doesn't contain args[1]
		Z3_ast condAst_x2 = registerContain(t, x2, args[1]);
		thenItems.push_back(Z3_mk_not(ctx, condAst_x2));


		if (isDetAutomatonFunc(t, args[1]) || isConstStr(t, args[1]))
			lastIndexOfStrMap[nodeName] = std::make_pair(boolVar, "len_" + std::string(Z3_ast_to_string(ctx, x1)));
		else
			lastIndexOfStrMap[nodeName] = std::make_pair(boolVar, "len_" + std::string(Z3_ast_to_string(ctx, x1)));

		if (!canSkipExt(t, args[1])) {
			// args[0]  = x3 . x4 /\ |x3| = |x1| + 1 /\ ! contains(x4, args[1])
			Z3_ast x3 = mk_internal_string_var(t);
			Z3_ast x4 = mk_internal_string_var(t);
			if (tmpInternalVars.size() > 0) {
				assert(tmpInternalVars.size() == 4);
				x3 = tmpInternalVars[2];
				x4 = tmpInternalVars[3];
			}
			Z3_ast tmpLenItems[2] = { mk_length(t, x1), mk_int(ctx, 1) };
			Z3_ast tmpLen = Z3_mk_add(ctx, 2, tmpLenItems);
			thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
			Z3_ast condAst_x4 = registerContain(t, x4, args[1]);
			thenItems.push_back(Z3_mk_not(ctx, condAst_x4));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x2, condAst_x4));
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x4, condAst_arg0));

			lastIndexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x3, x4};

			carryOn[condAst_arg0] = Z3_mk_eq(ctx, mk_length(t, x3), tmpLen);
		}
		else {
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x2, condAst_arg0));

			lastIndexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		//----------------------------
		// else branch
		std::vector<Z3_ast> elseItems;
		elseItems.push_back(Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1)));

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg0, mk_and_fromVector(t, thenItems), mk_and_fromVector(t, elseItems));

		return indexAst;
	}
}


/*
 *
 */
Z3_ast reduce_charAt(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d, %d | %d", getNodeType(t, args[0]), getNodeType(t, args[1]), my_Z3_Num);
	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_Num) {
		__debugPrint(logFile, "quick path\n");
		std::string arg0Str = getConstStrValue(t, args[0]);
		int arg1Int = getConstIntValue(t, args[1]);
		std::string resStr;
		if (0 <= arg1Int && arg1Int <= (int) arg0Str.length()) {
			resStr.push_back(arg0Str.c_str()[arg1Int]);
		} else {
			resStr = "";
		}
		return mk_str_value(t, resStr.c_str());
	} else {

		Z3_ast ts0 = mk_internal_string_var(t);
		Z3_ast ts1 = mk_internal_string_var(t);
		Z3_ast ts2 = mk_internal_string_var(t);

		std::vector<Z3_ast> tmp = {Z3_mk_ge(ctx, args[1], mk_int(ctx, 0)), Z3_mk_lt(ctx, args[1], mk_length(t, args[0]))};
		Z3_ast cond = mk_and_fromVector(t, tmp);

		bool update;
		Z3_ast and_item[3];
		and_item[0] = Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, mk_concat(t, ts1, ts2, update), update));
		and_item[1] = Z3_mk_eq(ctx, args[1], mk_length(t, ts0));
		and_item[2] = Z3_mk_eq(ctx, mk_length(t, ts1), mk_int(ctx, 1));
		Z3_ast thenBranch = Z3_mk_and(ctx, 3, and_item);
		Z3_ast elseBranch = Z3_mk_eq(ctx, ts1, mk_str_value(t, ""));
		breakdownAssert = Z3_mk_ite(ctx, cond, thenBranch, elseBranch);
		return ts1;
	}
}


/*
 *
 */
Z3_ast reduce_replace(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	/* convert to string, prepare for replaceStrMap */
	std::string nodeName = exportNodeName(t, args, td->Replace);

	if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr && getNodeType(t, args[2]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		std::string arg2Str = getConstStrValue(t, args[2]);
		if (arg0Str.find(arg1Str) != std::string::npos) {
			int index1 = arg0Str.find(arg1Str);
			int index2 = index1 + arg1Str.length();
			std::string substr0 = arg0Str.substr(0, index1);
			std::string substr2 = arg0Str.substr(index2);
			std::string replaced = substr0 + arg2Str + substr2;
			replaceStrMap[nodeName] = "true";
			return mk_str_value(t, replaced.c_str());
		} else {
			replaceStrMap[nodeName] = "false";
			return args[0];
		}
	} else {
		std::vector<Z3_ast> tmpInternalVars;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1])) != indexOf_toAstMap.end())
			tmpInternalVars = indexOf_toAstMap[std::make_pair(args[0], args[1])];

		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);

		if (tmpInternalVars.size() > 0) {
			x1 = tmpInternalVars[0];
			x2 = tmpInternalVars[1];
		}

		Z3_ast result = mk_internal_string_var(t);

		Z3_ast condAst_arg0 = registerContain(t, args[0], args[1]);
		std::string boolName = Z3_ast_to_string(ctx, condAst_arg0);
		replaceStrMap[nodeName] = boolName;

		// -----------------------
		// true branch
		std::vector<Z3_ast> thenItems;
		//  args[0] = x1 . args[1] . x2
		bool update = true;
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update)));
		Z3_ast condAst_x1 = registerContain(t, x1, args[1]);
		thenItems.push_back(Z3_mk_not(ctx, condAst_x1));

		if (!canSkipExt(t, args[1])) {
			//  args[0]  = x3 . x4 /\ |x3| = |x1| + |args[1]| - 1 /\ ! contains(x3, args[1])
			Z3_ast x3 = mk_internal_string_var(t);
			Z3_ast x4 = mk_internal_string_var(t);
			if (tmpInternalVars.size() > 0) {
				assert(tmpInternalVars.size() == 4);
				x3 = tmpInternalVars[2];
				x4 = tmpInternalVars[3];
			}
			Z3_ast tmpLenItems[3] = {mk_length(t, x1), mk_length(t, args[1]), mk_int(ctx, -1) };
			Z3_ast tmpLen = Z3_mk_add(ctx, 3, tmpLenItems);
			thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));

			Z3_ast condAst_x3 = registerContain(t, x3, args[1]);
			thenItems.push_back(Z3_mk_not(ctx, condAst_x3));
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_x3));
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x3, condAst_arg0));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x3, x4};

			carryOn[condAst_arg0] = Z3_mk_eq(ctx, mk_length(t, x3), tmpLen);
		}
		else {
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_arg0));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		thenItems.push_back(Z3_mk_eq(ctx, result, mk_concat(t, x1, mk_concat(t, args[2], x2, update), update)));

		// -----------------------
		// false branch
		Z3_ast elseBranch = Z3_mk_eq(ctx, result, args[0]);

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg0, mk_and_fromVector(t, thenItems), elseBranch);

		replaceNodeMap[std::make_pair(args[0], std::make_pair(args[1], args[2]))] = result;
		return result;
	}
}


/*
 *
 */
Z3_ast reduce_subStr(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	Z3_ast ts0 = mk_internal_string_var(t);
	Z3_ast ts1 = mk_internal_string_var(t);
	Z3_ast ts2 = mk_internal_string_var(t);

	bool update;

	int value_prefix = getConstIntValue(t, args[1]);

	if (value_prefix != 0 ) {
		Z3_ast and_item[3];
		and_item[0] = Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, mk_concat(t, ts1, ts2, update), update));
		and_item[1] = Z3_mk_eq(ctx, args[1], mk_length(t, ts0));
		and_item[2] = Z3_mk_eq(ctx, args[2], mk_length(t, ts1));

		AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

		/* convert to string, prepare for replaceStrMap */
		std::string nodeName = exportNodeName(t, args, td->SubString);
		std::string tmp = "(= len_" + (string)Z3_ast_to_string(ctx, ts0) + " ";
		tmp = tmp + Z3_ast_to_string(ctx, args[1]) + ")";

		subStrStrMap[nodeName] = tmp;
		breakdownAssert = Z3_mk_and(ctx, 3, and_item);
	}
	else {
		// substring from 0
		Z3_ast and_item[2];
		and_item[0] = Z3_mk_eq(ctx, args[0], mk_concat(t, ts1, ts2, update));
		and_item[1] = Z3_mk_eq(ctx, args[2], mk_length(t, ts1));

		breakdownAssert = Z3_mk_and(ctx, 2, and_item);
	}
	return ts1;
}

/*
 *
 */
Z3_ast reduce_str2regex(Z3_theory t, Z3_func_decl d, Z3_ast const args[], Z3_ast & extraAssert) {
  Z3_context ctx = Z3_theory_get_context(t);
  Z3_ast converted = mk_unary_app(ctx, d, args[0]);

  return converted;
}


/*
 *
 */
Z3_ast reduce_regexStar(Z3_theory t, Z3_ast const args[], Z3_ast & extraAssert) {
  Z3_context ctx = Z3_theory_get_context(t);
  AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
  Z3_app arg1_func_app = Z3_to_app(ctx, args[0]);
  Z3_func_decl funcDecl = Z3_get_app_decl(ctx, arg1_func_app);
  if (funcDecl == td->RegexStar) {
    return args[0];
  }
  else
    return NULL;
}


/*
 *
 */
Z3_ast reduce_regexPlus(Z3_theory t, Z3_ast const args[], Z3_ast & extraAssert) {
  Z3_context ctx = Z3_theory_get_context(t);
  AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
  Z3_app childFuncApp = Z3_to_app(ctx, args[0]);
  Z3_func_decl childFuncDecl = Z3_get_app_decl(ctx, childFuncApp);
  if (childFuncDecl == td->RegexPlus) {
    // (r+)+ --> r+
    return args[0];
  } else if (childFuncDecl == td->RegexStar) {
    // (r*)+ --> r*
    Z3_ast childArg0  = Z3_get_app_arg(ctx, childFuncApp, 0);
    return mk_unary_app(ctx, td->RegexStar, childArg0);
  } else {
    // r+ --> RegexConcat(r, r*)
    return mk_binary_app(ctx, td->RegexConcat, args[0],  mk_unary_app(ctx, td->RegexStar, args[0]));
  }
}

/*
 *
 */
Z3_ast reduce_regexConcat(Z3_theory t, Z3_ast const args[], Z3_ast & extraAssert) {
  Z3_context ctx = Z3_theory_get_context(t);
  AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

  Z3_app arg0_func_app = Z3_to_app(ctx, args[0]);
  Z3_app arg1_func_app = Z3_to_app(ctx, args[1]);

  Z3_func_decl arg0_funcDecl = Z3_get_app_decl(ctx, arg0_func_app);
  Z3_func_decl arg1_funcDecl = Z3_get_app_decl(ctx, arg1_func_app);

  // TODO what happens if they are not constant string
  if (arg0_funcDecl == td->Str2Reg && arg1_funcDecl == td->Str2Reg) {
    Z3_ast arg0Str  = Z3_get_app_arg(ctx, arg0_func_app, 0);
    Z3_ast arg1Str  = Z3_get_app_arg(ctx, arg1_func_app, 0);
    bool updated;
    Z3_ast comb = mk_concat(t, arg0Str, arg1Str, updated);
    return mk_unary_app(ctx, td->Str2Reg, comb);
  }
  return NULL;
}

/*
 *
 */
Z3_ast reduce_regexIn(Z3_theory t, Z3_ast const args[], Z3_ast & extraAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_app arg1_func_app = Z3_to_app(ctx, args[1]);
	Z3_func_decl funcDecl = Z3_get_app_decl(ctx, arg1_func_app);

	std::string regexStr = getStdRegexStr(t, args[1]);

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n %d >> RegexIn(", __LINE__);
	printZ3Node(t, args[0]);
	__debugPrint(logFile, ", ");
	printZ3Node(t, args[1]);
	__debugPrint(logFile, ")\n --> \n");
	printZ3Node(t, args[0]);
	__debugPrint(logFile, "  \\in  %s\n\n", regexStr.c_str());
#endif

	// quick path:
	// >> if RegexIn(T4_4, (Str2Reg #)) --> "T4_4 = #" is enough
	if (funcDecl == td->Str2Reg) {
		return Z3_mk_eq(ctx, args[0], Z3_get_app_arg(ctx, arg1_func_app, 0));
	}
	// ----------------------------------------------------
	else {
		if (regexStr.find("__NotConstStr__") == std::string::npos && regexStr.find("__Contain_Vars__") == std::string::npos) {
			if (regexStr.find('*') != std::string::npos || regexStr.find('+') != std::string::npos) {
				Z3_ast newapp = mk_binary_app(ctx, td->NonDet_AutomataDef, mk_str_value(t, regexStr.c_str()), mk_int(ctx, nondeterministicCounter++));
				return Z3_mk_eq(ctx, args[0], newapp);
			}
			else {
				Z3_ast newapp = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, regexStr.c_str()));
				return Z3_mk_eq(ctx, args[0], newapp);
			}
		}
	}
	return NULL;
}

/*
 *
 */
Z3_ast reduce_grammarIn(Z3_theory t, Z3_ast const args[], Z3_ast & extraAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	std::vector<std::string> grmStr = getStdGrmStr(t, args[1]);

	havingGrmConstraints = true;

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n>> GrammarIn(");
	printZ3Node(t, args[0]);
	__debugPrint(logFile, ", ");
	printZ3Node(t, args[1]);
	__debugPrint(logFile, ")\n");
#endif

	grm_astNode_map[args[0]] = args[0];

	if (grmStr.size() == 0){
		std::cerr << "Grammar is not defined!\n\n\n";
		return NULL;
	}

	Z3_ast* or_items = new Z3_ast[grmStr.size()];
	for (unsigned int i = 0; i < grmStr.size(); ++i) {
		if (grmStr[i].length() > 0) {
			Z3_ast rhs;
			if (grmStr[i].find('*') != std::string::npos || grmStr[i].find('+') != std::string::npos) {
				rhs = mk_binary_app(ctx, td->NonDet_AutomataDef, mk_str_value(t, grmStr[i].c_str()), mk_int(ctx, nondeterministicCounter++));
			}
			else {
				rhs = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, grmStr[i].c_str()));
			}

			if (isConstStr(t, args[0])){
				std::string constStr = Z3_ast_to_string(ctx, args[0]);
				Z3_ast lhs = mk_unary_app(ctx, td->AutomataDef, mk_str_value(t, constStr.c_str()));
				or_items[i] = Z3_mk_eq(ctx, lhs, rhs);
			}
			else {
				or_items[i] = Z3_mk_eq(ctx, args[0], rhs);
			}
		}
		else {
			std::cerr << "Grammar is not defined!\n\n\n";
			return NULL;
		}
	}
	return Z3_mk_or(ctx, grmStr.size(), or_items);
}

/*
 *Z3_bool Th_reduce_app(Z3_theory t, Z3_func_decl d, unsigned n, Z3_ast const args[], Z3_ast * result);
 */
int Th_reduce_app(Z3_theory t, Z3_func_decl d, unsigned n, Z3_ast const args[], Z3_ast * result) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

#ifdef DEBUGLOG
		__debugPrint(logFile, "\n*** %s ***:", __FUNCTION__);
#endif

	// Convert the tricky "string" representation to string constant
	int convertedFlag = 0;
	Z3_ast * convertedArgs = new Z3_ast[n];
	for (int i = 0; i < (int) n; i++) {
		std::string symbolStr = std::string(Z3_ast_to_string(ctx, args[i]));
		if (symbolStr.length() >= 11 && symbolStr.substr(0, 11) == "__cOnStStR_") {
			convertedFlag = 1;
			convertedArgs[i] = mk_str_value(t, convertInputTrickyConstStr(symbolStr).c_str());
		} else {
			convertedArgs[i] = args[i];
		}
	}

	//---------------------------------
	// reduce app: Concat
	//---------------------------------
	if (d == td->Concat) {

#ifdef DEBUGLOG
		__debugPrint(logFile, "Concat(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")");
#endif
		bool updated = false;
		Z3_ast tmp = mk_concat(t, convertedArgs[0], convertedArgs[1], updated);

		// update children map

		if (updated == false) {
#ifdef DEBUGLOG
			__debugPrint(logFile, "\nFalse update \n");
#endif
			delete[] convertedArgs;
			return Z3_FALSE;
		}

		children_Map[tmp].push_back(convertedArgs[0]);
		children_Map[tmp].push_back(convertedArgs[1]);

		*result = tmp;
#ifdef DEBUGLOG
		__debugPrint(logFile, "\n convert to: ");
		printZ3Node(t, *result);
		__debugPrint(logFile, "\n\n");
#endif
		return Z3_TRUE;
	}

	//---------------------------------
	// reduce app: Length
	//---------------------------------
	else if (d == td->Length) {

#ifdef DEBUGLOG
		__debugPrint(logFile, "Length( ");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, " ) = ");
#endif
		if (getNodeType(t, convertedArgs[0]) == my_Z3_ConstStr) {
			int size = getConstStrValue(t, convertedArgs[0]).size();
			*result = mk_int(ctx, size);
			__debugPrint(logFile, "%d\n\n", size);
			delete[] convertedArgs;
			return Z3_TRUE;
		}
		else {
			__debugPrint(logFile, "%d not const\n\n", __LINE__);
			if (convertedFlag == 1) {
				*result = mk_length(t, convertedArgs[0]);

				delete[] convertedArgs;
				return Z3_TRUE;
			} else {
				delete[] convertedArgs;
				return Z3_FALSE;
			}
		}
	}

	//------------------------------------------
	// Reduce app: Str2Reg
	//------------------------------------------
	else if (d == td->Str2Reg) {
#ifdef DEBUGLOG
		__debugPrint(logFile, "Str2Reg(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ")\n");
#endif

		if (!isConstStr(t, convertedArgs[0])) {
			printf("> Error: the argument of Str2Reg function should be a constant string.\n");
			printf("         (Str2Reg %s)\n", Z3_ast_to_string(ctx, convertedArgs[0]));
			exit(0);
		}

		Z3_ast otherAssert = NULL;
		*result = reduce_str2regex(t, d, convertedArgs, otherAssert);

#ifdef DEBUGLOG
		if( otherAssert != NULL )
		{
			__debugPrint(logFile, "-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, otherAssert);
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
#endif

		if (otherAssert != NULL) {
			Z3_assert_cnstr(ctx, otherAssert);
		}
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: RegexConcat
	//------------------------------------------
	else if (d == td->RegexConcat) {
#ifdef DEBUGLOG
		__debugPrint(logFile, "RegexConcat(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")\n");
#endif

		Z3_ast otherAssert = NULL;
		Z3_ast tmpRes = reduce_regexConcat(t, convertedArgs, otherAssert);
		delete[] convertedArgs;

#ifdef DEBUGLOG
		if (tmpRes != NULL) {
			__debugPrint(logFile, "   --------------> ");
			printZ3Node(t, tmpRes);
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
#endif

		if (tmpRes == NULL) {
			return Z3_FALSE;
		} else {
			*result = tmpRes;
			return Z3_TRUE;
		}
	}


	//------------------------------------------
	// Reduce app: RegexIn
	//------------------------------------------
	else if (d == td->RegexIn) {
#ifdef DEBUGLOG
		__debugPrint(logFile, "RegexIn(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ") ==> ");
#endif
		Z3_ast otherAssert = NULL;
		Z3_ast tmpRes = NULL;
		tmpRes = reduce_regexIn(t, convertedArgs, otherAssert);

#ifdef DEBUGLOG
		printZ3Node(t, tmpRes);
		__debugPrint(logFile, "\n");
		if( otherAssert != NULL )
		{
			__debugPrint(logFile, "-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, otherAssert);
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
#endif

		delete[] convertedArgs;

		if (tmpRes != NULL) {
			if (otherAssert != NULL) {
				Z3_assert_cnstr(ctx, otherAssert);
			}
			*result = tmpRes;
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}

	//------------------------------------------
	// Reduce app: RegexStar
	//------------------------------------------
	else if (d == td->RegexStar) {
		Z3_ast otherAssert = NULL;
#ifdef DEBUGLOG
		__debugPrint(logFile, "RegexStar(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ") --> ");
#endif
		*result = reduce_regexStar(t, convertedArgs, otherAssert);
		delete[] convertedArgs;

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if( otherAssert != NULL )
		{
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, otherAssert);
		}
		__debugPrint(logFile, "\n\n");
#endif

		if (*result != NULL) {
			if (otherAssert != NULL) {
				Z3_assert_cnstr(ctx, otherAssert);
			}
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}
	//------------------------------------------
	// Reduce app: RegexPlus
	//------------------------------------------
	else if (d == td->RegexPlus) {
		Z3_ast otherAssert = NULL;
#ifdef DEBUGLOG
		__debugPrint(logFile, "RegexPlus(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ") --> ");
#endif
		*result = reduce_regexPlus(t, convertedArgs, otherAssert);
		delete[] convertedArgs;

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if( otherAssert != NULL )
		{
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, otherAssert);
		}
		__debugPrint(logFile, "\n\n");
#endif

		if (*result != NULL) {
			if (otherAssert != NULL) {
				Z3_assert_cnstr(ctx, otherAssert);
			}
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}

	//------------------------------------------
	// Reduce app: GrammarIn
	//------------------------------------------
	else if (d ==td->GrammarIn) {
		Z3_ast otherAssert = NULL;
		Z3_ast tmpRes = NULL;
		tmpRes = reduce_grammarIn(t, convertedArgs, otherAssert);

#ifdef DEBUGLOG
		__debugPrint(logFile, "GrammarIn(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ") ==> ");
		printZ3Node(t, tmpRes);
		__debugPrint(logFile, "\n");
		if( otherAssert != NULL ){
			__debugPrint(logFile, "-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, otherAssert);
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
#endif

		delete[] convertedArgs;

		if (tmpRes != NULL) {
			if (otherAssert != NULL) {
				Z3_assert_cnstr(ctx, otherAssert);
			}
			*result = tmpRes;
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}

	//---------------------------------
	// reduce app: SubString
	//---------------------------------
	else if (d == td->SubString) {
		Z3_ast breakDownAst = NULL;

#ifdef DEBUGLOG
		__debugPrint(logFile, "SubString( ");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[2]);
		__debugPrint(logFile, ")  =>  ");
#endif

		*result = reduce_subStr(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		__debugPrint(logFile, "\n-- ADD(@%d, Level %d):\n", __LINE__, sLevel);
		printZ3Node(t, breakDownAst);
		__debugPrint(logFile, "\n\n");
#endif
		Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Contains
	//------------------------------------------
	else if (d == td->Contains) {
		Z3_ast breakDownAst = NULL;

#ifdef DEBUGLOG
		__debugPrint(logFile, "Contains(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif
		*result = reduce_contains(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if( breakDownAst != NULL )
		{
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Indexof
	//------------------------------------------
	else if (d == td->Indexof) {
		Z3_ast breakDownAst = NULL;

#ifdef DEBUGLOG
		__debugPrint(logFile, "Indexof(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif

		*result = reduce_indexof(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if( breakDownAst != NULL )
		{
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: LastIndexof
	//------------------------------------------
	else if (d == td->LastIndexof) {
		Z3_ast breakDownAst = NULL;

#ifdef DEBUGLOG
		__debugPrint(logFile, "LastIndexof(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif

		*result = reduce_lastindexof(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if( breakDownAst != NULL )
		{
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: EndsWith
	//------------------------------------------
	else if (d == td->EndsWith) {
		Z3_ast breakDownAst = NULL;

#ifdef DEBUGLOG
		__debugPrint(logFile, "EndsWith(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif

		*result = reduce_endswith(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if (breakDownAst != NULL) {
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: StartsWith
	//------------------------------------------
	else if (d == td->StartsWith) {
		Z3_ast breakDownAst = NULL;

#ifdef DEBUGLOG
		__debugPrint(logFile, "StartsWith(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif

		*result = reduce_startswith(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if ( breakDownAst != NULL ){
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Replace
	//------------------------------------------
	else if (d == td->Replace){
		Z3_ast breakDownAst = NULL;
#ifdef DEBUGLOG
		__debugPrint(logFile, "Replace(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[2]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif

		*result = reduce_replace(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if ( breakDownAst != NULL ){
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;

		return Z3_TRUE;
	}
	//------------------------------------------
	// Reduce app: ReplaceAll
	//------------------------------------------
	else if (d == td->ReplaceAll){
		Z3_ast breakDownAst = NULL;
#ifdef DEBUGLOG
		__debugPrint(logFile, "ReplaceAll(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[1]);
		__debugPrint(logFile, ", ");
		printZ3Node(t, convertedArgs[2]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif

		*result = reduce_replaceAll(t, convertedArgs, breakDownAst);

#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if ( breakDownAst != NULL ){
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		// when quick path is taken, breakDownAst == NULL;
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;

		return Z3_TRUE;
	}
	else if (d == td->ToLower) {
		Z3_ast breakDownAst = NULL;
#ifdef DEBUGLOG
		__debugPrint(logFile, "ToLower(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif
		*result = reduce_toLower(t, convertedArgs, breakDownAst);
#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if ( breakDownAst != NULL ){
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;

		return Z3_TRUE;
	}
	else if (d == td->ToUpper){
		Z3_ast breakDownAst = NULL;
#ifdef DEBUGLOG
		__debugPrint(logFile, "ToUpper(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ")");
		__debugPrint(logFile, "  =>  ");
#endif
		*result = reduce_toUpper(t, convertedArgs, breakDownAst);
#ifdef DEBUGLOG
		printZ3Node(t, *result);
		if ( breakDownAst != NULL ){
			__debugPrint(logFile, "\n-- ADD(@%d): \n", __LINE__);
			printZ3Node(t, breakDownAst);
		}
		__debugPrint(logFile, "\n\n");
#endif
		if (breakDownAst != NULL)
			Z3_assert_cnstr(ctx, breakDownAst);
		delete[] convertedArgs;

		return Z3_TRUE;
	}
	else if (d == td->AutomataDef){
#ifdef DEBUGLOG
		__debugPrint(logFile, "AutomataDef(");
		printZ3Node(t, convertedArgs[0]);
		__debugPrint(logFile, ", ");
		__debugPrint(logFile, "  =>  nothing");
#endif

	}

	if (convertedFlag == 1) {
		*result = Z3_mk_app(ctx, d, n, convertedArgs);
#ifdef DEBUGLOG
		__debugPrint(logFile, "%d Others --> ", __LINE__);
		printZ3Node(t, *result);
		__debugPrint(logFile, "\n\n");
#endif
		delete[] convertedArgs;
		return Z3_TRUE;
	}


	delete[] convertedArgs;
	return Z3_FALSE; // failed to simplify
}

/*
 *
 */
Z3_bool cb_reduce_eq(Z3_theory t, Z3_ast s1, Z3_ast s2, Z3_ast * r) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	std::string s1_str = customizeString(Z3_ast_to_string(ctx, s1));
	std::string s2_str = customizeString(Z3_ast_to_string(ctx, s2));
	__debugPrint(logFile, "\n*** %s ***: %s = %s", __FUNCTION__, s1_str.c_str(), s2_str.c_str());
	__debugPrint(logFile, "\n\n");
	Z3_ast s1_new = s1;
	Z3_ast s2_new = s2;

	int len01 = -1, len02 = -1;
	// Convert the tricky "string" representation to string constant
	if (s1_str.length() >= 11 && s1_str.substr(0, 11) == "__cOnStStR_") {
		std::string s = convertInputTrickyConstStr(s1_str);
		s1_new = mk_str_value(t, s.c_str());
		len01 = s.length();

		s1_new = mk_unary_app(ctx, td->AutomataDef, s1_new);
		addAxiom(t, Z3_mk_eq(ctx, mk_length(t, s1_new), mk_int(ctx, s.length())), __LINE__, true);
	}
	else if (isConstStr(t, s1)){
		s1_new = mk_str_value(t, s1_str.c_str());
		len01 = s1_str.length();

		s1_new = mk_unary_app(ctx, td->AutomataDef, s1_new);
		addAxiom(t, Z3_mk_eq(ctx, mk_length(t, s1_new), mk_int(ctx, s1_str.length())), __LINE__, true);
	}

	if (s2_str.length() >= 11 && s2_str.substr(0, 11) == "__cOnStStR_") {
		std::string s = convertInputTrickyConstStr(s2_str);
		s2_new = mk_str_value(t, s.c_str());
		len02 = s.length();

		s2_new = mk_unary_app(ctx, td->AutomataDef, s2_new);
		addAxiom(t, Z3_mk_eq(ctx, mk_length(t, s2_new), mk_int(ctx, s.length())), __LINE__, true);
	}
	else if (isConstStr(t, s2)){
		s2_new = mk_str_value(t, s2_str.c_str());
		len02 = s2_str.length();

		s2_new = mk_unary_app(ctx, td->AutomataDef, s2_new);
		addAxiom(t, Z3_mk_eq(ctx, mk_length(t, s2_new), mk_int(ctx, s2_str.length())), __LINE__, true);
	}
	// parikh and length constraints
	std::vector<Z3_ast> list00;

#ifdef ARITH
	// do not need to insert axiom for concat because concat does itself
	if (!isConcatFunc(t, s1)) {
		std::vector<Z3_ast> list01 = basicArithConstraints_forNode_simple(t, s1);
		list00.insert(list00.end(), list01.begin(), list01.end());
	}
	if (!isConcatFunc(t, s2)) {
		std::vector<Z3_ast> list01 = basicArithConstraints_forNode_simple(t, s2);
		list00.insert(list00.end(), list01.begin(), list01.end());
	}
#endif

	if (s2_new != s2 || s1_new != s1) {
		*r = Z3_mk_eq(ctx, s1_new, s2_new);
	}


	// do not handle twice
	if (eqList.find(std::make_pair(s1_new, s2_new)) != eqList.end())
		return Z3_FALSE;

	Z3_ast eqNode = Z3_mk_eq(ctx, s1_new, s2_new);

	if (len01 >= 0)
		list00.push_back(Z3_mk_implies(ctx, eqNode, Z3_mk_eq(ctx, mk_length(t, s2_new), mk_int(ctx, len01))));

	if (len02 >= 0)
		list00.push_back(Z3_mk_implies(ctx, eqNode, Z3_mk_eq(ctx, mk_length(t, s1_new), mk_int(ctx, len02))));

	if (!(len01 >= 0 && len02 >= 0)) {
		Z3_ast lengConstraint = Z3_mk_eq(ctx, mk_length(t, s1_new), mk_length(t, s2_new));
		list00.push_back(Z3_mk_implies(ctx, eqNode, lengConstraint));
	}

	eqList[std::make_pair(s1_new, s2_new)] = 1;


	list00.push_back(eqNode);
	*r = mk_and_fromVector(t, list00);

#ifdef DEBUGLOG
	__debugPrint(logFile, "\n converted to : ");
	printZ3Node(t, *r);
	__debugPrint(logFile, "\n");
#endif
	return Z3_TRUE;
}

///*
// *
// */
//Z3_ast reduce_regexCharRange(Z3_theory t, Z3_ast const args[], Z3_ast & extraAssert) {
//  Z3_context ctx = Z3_theory_get_context(t);
//  PATheoryData * td = (PATheoryData*) Z3_theory_get_ext_data(t);
//  if (isConstStr(t, args[0]) && isConstStr(t, args[1])) {
//    std::string arg0Value = getConstStrValue(t, args[0]);
//    std::string arg1Value = getConstStrValue(t, args[1]);
//    if (arg0Value.size() == 1 && arg1Value.size() == 1) {
//      char low = arg0Value[0];
//      char high = arg1Value[0];
//      if (low > high) {
//        char t = low;
//        low = high;
//        high = t;
//      }
//
//#ifdef DEBUGLOG
//      __debugPrint(logFile, ">> reduce_regexCharRange: arg0 = \"%s\", arg1 = \"%s\"\n", arg0Value.c_str(), arg1Value.c_str());
//      __debugPrint(logFile, "                          low = '%c', high = '%c'\n", low, high);
//#endif
//
//      char c = low;
//      std::string cStr;
//      cStr.push_back(c);
//      Z3_ast res = mk_1_arg_app(ctx, td->Str2Reg, my_mk_str_value(t, cStr.c_str()));
//      c++;
//      for (; c <= high; c++) {
//        cStr.clear();
//        cStr.push_back(c);
//        res = mk_2_arg_app(ctx, td->RegexUnion, mk_1_arg_app(ctx, td->Str2Reg, my_mk_str_value(t, cStr.c_str())), res);
//      }
//      return res;
//    } else {
//      printf("> Error: The argument of RegexCharRange should be constant strings of size 1.\n");
//      printf("         Found (RegexCharRange %s %s)\n", arg0Value.c_str(), arg1Value.c_str());
//    }
//
//  } else {
//    printf("> Error: The argument of RegexCharRange should be constant strings.\n");
//    printf("         Found (RegexCharRange %s %s)\n", Z3_ast_to_string(ctx, args[0]), Z3_ast_to_string(ctx, args[1]));
//  }
//  exit(0);
//}


