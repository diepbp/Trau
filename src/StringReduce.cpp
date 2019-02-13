#include "StringTheory.h"

extern int nondeterministicCounter;
extern bool havingGrmConstraints;
extern std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> concat_astNode_map;
extern std::map<Z3_ast, Z3_ast> grm_astNode_map;
extern std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> containPairBoolMap;

extern std::map<StringOP, std::pair<std::string, std::string>> subStrStrMap;
extern std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> subStrNodeMap;
extern std::map<StringOP, std::pair<std::string, std::string>> charAtStrMap;
extern std::map<StringOP, std::pair<std::string, std::pair<std::string, std::string>>> indexOfStrMap;
extern std::map<StringOP, std::pair<std::string, std::pair<std::string, std::string>>> indexOf2StrMap;
extern std::map<StringOP, std::pair<std::string, std::pair<std::string, std::string>>> lastIndexOfStrMap;
extern std::map<StringOP, std::string> endsWithStrMap;
extern std::map<StringOP, std::string> startsWithStrMap;

extern std::map<std::pair<std::pair<Z3_ast, Z3_ast>, Z3_ast>, std::vector<Z3_ast>> indexOf2_toAstMap;
extern std::map<std::pair<Z3_ast, Z3_ast>, std::vector<Z3_ast>> indexOf_toAstMap;
extern std::map<std::pair<Z3_ast, Z3_ast>, std::vector<Z3_ast>> lastIndexOf_toAstMap;

extern std::map<StringOP, std::string> replaceStrMap;
extern std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> replaceNodeMap;

extern std::map<StringOP, std::string> replaceAllStrMap;
extern std::map<std::pair<Z3_ast, std::pair<Z3_ast, Z3_ast>>, Z3_ast> replaceAllNodeMap;

extern std::map<Z3_ast, Z3_ast> toUpperMap;
extern std::map<Z3_ast, Z3_ast> toLowerMap;

extern std::map<Z3_ast, Z3_ast> carryOn;

extern int nondeterministicCounter;
extern bool lengthEnable;
extern ConstraintSet constraintSet;
extern std::map<StringOP, StringOP> internalVarFunctionMap;

static std::map<Z3_ast, Z3_ast> concatMapping;
std::set<std::string> setOfEqualities;

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
//void setAlphabet() {
//  if (defaultCharSet) {
//    // a string in C notion cannot contain a char '\0'
//    charSetSize = 255;
//    charSet = new char[charSetSize];
//    int idx = 0;
//    // small letters
//    for (int i = 97; i < 123; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // caps
//    for (int i = 65; i < 91; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // numbers
//    for (int i = 48; i < 58; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // printable marks - 1
//    for (int i = 32; i < 48; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // printable marks - 2
//    for (int i = 58; i < 65; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // printable marks - 3
//    for (int i = 91; i < 97; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // printable marks - 4
//    for (int i = 123; i < 127; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // non-printable - 1
//    for (int i = 1; i < 32; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//    // non-printable - 2
//    for (int i = 127; i < 256; i++) {
//      charSet[idx] = (char) i;
//      charSetLookupTable[charSet[idx]] = idx;
//      idx++;
//    }
//  } else {
//    const char setset[] = { 'a', 'b', 'c' };
//    int fSize = sizeof(setset) / sizeof(char);
//
//    charSet = new char[fSize];
//    charSetSize = fSize;
//    for (int i = 0; i < charSetSize; i++) {
//      charSet[i] = setset[i];
//      charSetLookupTable[setset[i]] = i;
//    }
//  }
//}
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
 * check if leng = 1 --> skip generating new constraints in indexof, indexof2, lastindexof...
 */
bool canSkipExt(Z3_theory t, Z3_ast node) {
	if (getNodeType(t, node) == my_Z3_ConstStr) {
		std::string nodeStr = getConstStrValue(t, node);
		if (nodeStr.length() == 1) {
			return true;
		}
	}
	return false;
}

/*
 *
 */
void appendToFile(std::string s) {
	/* write to file */
	FILE* eqFile = fopen("eqFile.txt", "a");
	fprintf(eqFile, "%s\n", s.c_str());
	fclose(eqFile);
}

/*
 *
 */
std::string exportNodeName(Z3_theory t, Z3_ast node) {
	Z3_context ctx = Z3_theory_get_context(t);

	if (isDetAutomatonFunc(t, node) || isConstStr(t, node)
			|| isNonDetAutomatonFunc(t, node)) {
		return "\"" + getConstString(t, node) + "\"";
	} else if (isConcatFunc(t, node)) {
		return "(" + std::string(config.languageMap[CONCAT]) + " "
				+ exportNodeName(t,
						Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 0)) + " "
				+ exportNodeName(t,
						Z3_get_app_arg(ctx, Z3_to_app(ctx, node), 1)) + ")";
	} else
		return Z3_ast_to_string(ctx, node);
}

/*
 *
 */
void pushVectors(Z3_ast node, std::vector<Z3_ast> &v0, std::vector<Z3_ast> &v1,
		std::vector<Z3_ast> &v2) {
	v0.push_back(node);
	v1.push_back(node);
	v2.push_back(node);
}

/*
 *
 */
StringOP convertStrOPToArithmeticOP(StringOP op){
	if (op.args.size() == 0)
		return op;
	else {
		if (op.name.compare(config.languageMap[LENGTH]) == 0){
			if (op.args[0].name.compare(config.languageMap[CONCAT]) == 0){
				std::vector<StringOP> args;
				std::vector<StringOP> q;
				q.emplace_back(op.args[0]);
				int pos = 0;
				while (pos < (int)q.size()){
					StringOP curr = q[pos];
					pos ++;

					for (unsigned i = 0; i < curr.args.size(); ++i)
						if (curr.args[i].args.size() == 0){
							args.push_back(StringOP(generateVarLength(curr.args[i].name)));
						}
						else {
							assert (curr.args[i].name.compare(config.languageMap[CONCAT]) == 0);
							q.emplace_back(curr.args[i]);
						}
				}
				return StringOP("+", args);
			}
			else
				return StringOP(generateVarLength(op.args[0].name));
		}
		else {
			std::vector<StringOP> args;
			for (unsigned i = 0; i < op.args.size(); ++i){
				args.push_back(convertStrOPToArithmeticOP(op.args[i]));
			}

			return StringOP(op.name, args);
		}

	}
}
/*
 *
 */
std::string convertStrNodeToArithmeticNode(Z3_theory t, Z3_ast node){
	StringOP op = node_to_stringOP(t, node);
	return convertStrOPToArithmeticOP(op).toString();
}

/*
 *
 */
void pushVectors(Z3_ast node, std::vector<Z3_ast> &v0,
		std::vector<Z3_ast> &v1) {
	v0.push_back(node);
	v1.push_back(node);
}

/*
 *
 */
void pushVectors(Z3_ast node, std::vector<Z3_ast> &v0) {
	v0.push_back(node);
}

/*
 *
 */
Z3_ast reduce_replaceAll(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	if (args[0] == args[1])
		return args[2];
	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr
			&& getNodeType(t, args[2]) == my_Z3_ConstStr) {
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
			replaceAllStrMap[StringOP(config.languageMap[REPLACEALL],
					{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]),	node_to_stringOP(t, args[2])})] = std::to_string(arg0Str.length());
			return mk_str_value(t, arg0Str.c_str());
		} else {
			replaceAllStrMap[StringOP(config.languageMap[REPLACEALL],
					{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]),	node_to_stringOP(t, args[2])})] = std::to_string(arg0Str.length());
			return args[0];
		}
	} else {
		AutomatonStringData * td =
				(AutomatonStringData*) Z3_theory_get_ext_data(t);

		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars00;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1]))
				!= indexOf_toAstMap.end())
			tmpInternalVars00 = indexOf_toAstMap[std::make_pair(args[0],
					args[1])];

		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);

		if (tmpInternalVars00.size() > 0) {
			x1 = tmpInternalVars00[0];
			x2 = tmpInternalVars00[1];
		}

		Z3_ast result = mk_internal_string_var(t);

		printZ3Node(t, args[1]);
		std::string arg01Plus = "(" + getConstString(t, args[1]) + ")+";
		std::string arg02Plus = "(" + getConstString(t, args[2]) + ")+";

		// condAst = Contains(args[0], args[1])
		Z3_ast condAst_arg00 = registerContain(t, args[0], args[1]);
		std::string boolName = Z3_ast_to_string(ctx, condAst_arg00);
		replaceAllStrMap[StringOP(config.languageMap[REPLACEALL],
				{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]),	node_to_stringOP(t, args[2])})] = boolName;

		bool update = true;
		bool canSkip = canSkipExt(t, args[1]);

		// -----------------------
		// case 01

		std::vector<Z3_ast> thenItems00;
		std::vector<Z3_ast> thenItems01;
		std::vector<Z3_ast> thenItems02;
		std::vector<Z3_ast> generalConstraints;

		//  args[0] = x1 . args[1] . x2
		Z3_ast arg0_tmp = Z3_mk_eq(ctx, args[0],
				mk_concat(t, x1,
						mk_concat(t,
								mk_binary_app(ctx, td->NonDet_AutomataDef,
										mk_str_value(t, arg01Plus.c_str()),
										mk_int(ctx, nondeterministicCounter++)),
								x2, update), update));
		pushVectors(arg0_tmp, thenItems00, thenItems01, thenItems02);

		Z3_ast condAst_x1 = registerContain(t, x1, args[1]);
		pushVectors(Z3_mk_not(ctx, condAst_x1), thenItems00, thenItems01,
				thenItems02);

		Z3_ast condAst_x2 = registerContain(t, x2, args[1]);
		generalConstraints.push_back(
				Z3_mk_implies(ctx, condAst_x2, condAst_arg00));

		if (!canSkip) {
			//  args[0]  = x_n1 . x_m1 /\ |x_n1| = |x1| + |args[1]| - 1 /\ ! contains(x_n1, args[1])
			Z3_ast tmpLenItems01[3] = { mk_length(t, x1), mk_length(t, args[1]),
					mk_int(ctx, -1) };
			Z3_ast tmpLen01 = Z3_mk_add(ctx, 3, tmpLenItems01);

			Z3_ast x_n1 = mk_internal_string_var(t);
			Z3_ast x_m1 = mk_internal_string_var(t);
			if (tmpInternalVars00.size() > 0) {
				assert(tmpInternalVars00.size() == 4);
				x_n1 = tmpInternalVars00[2];
				x_m1 = tmpInternalVars00[3];
			}

			pushVectors(
					Z3_mk_eq(ctx, args[0], mk_concat(t, x_n1, x_m1, update)),
					thenItems00, thenItems01, thenItems02);
			pushVectors(Z3_mk_eq(ctx, mk_length(t, x_n1), tmpLen01),
					thenItems00, thenItems01, thenItems02);

			Z3_ast condAst00n = registerContain(t, x_n1, args[1]);
			pushVectors(Z3_mk_not(ctx, condAst00n), thenItems00, thenItems01,
					thenItems02);

			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst_x1, condAst00n));
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst00n, condAst_arg00));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x_n1, x_m1};
			carryOn[condAst_arg00] = Z3_mk_eq(ctx, mk_length(t, x_n1),
					tmpLen01);
		} else {
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst_x1, condAst_arg00));
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		pushVectors(Z3_mk_not(ctx, condAst_x2), thenItems00);
		pushVectors(
				Z3_mk_eq(ctx, result,
						mk_concat(t, x1,
								mk_concat(t,
										mk_binary_app(ctx,
												td->NonDet_AutomataDef,
												mk_str_value(t,
														arg02Plus.c_str()),
												mk_int(ctx,
														nondeterministicCounter++)),
										x2, update), update)), thenItems00);

		// -----------------------
		// case 2
		// condAst_x2 = registerContain(t, x2, args[1]);
		//  x2 = x3 . args[1] . x4

		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars01;
		if (indexOf_toAstMap.find(std::make_pair(x2, args[1]))
				!= indexOf_toAstMap.end())
			tmpInternalVars01 = indexOf_toAstMap[std::make_pair(x2, args[1])];

		Z3_ast x3 = mk_internal_string_var(t);
		Z3_ast x4 = mk_internal_string_var(t);

		if (tmpInternalVars00.size() > 0) {
			x3 = tmpInternalVars01[0];
			x4 = tmpInternalVars01[1];
		}

		Z3_ast x2_tmp = Z3_mk_eq(ctx, x2,
				mk_concat(t, x3,
						mk_concat(t,
								mk_binary_app(ctx, td->NonDet_AutomataDef,
										mk_str_value(t, arg01Plus.c_str()),
										mk_int(ctx, nondeterministicCounter++)),
								x4, update), update));
		pushVectors(x2_tmp, thenItems01, thenItems02);

		Z3_ast condAst_x3 = registerContain(t, x3, args[1]);
		pushVectors(Z3_mk_not(ctx, condAst_x3), thenItems01, thenItems02);

		Z3_ast condAst_x4 = registerContain(t, x4, args[1]);
		generalConstraints.push_back(
				Z3_mk_implies(ctx, condAst_x4, condAst_x2));

		if (!canSkip) {
			Z3_ast x_n2 = mk_internal_string_var(t);
			Z3_ast x_m2 = mk_internal_string_var(t);
			if (tmpInternalVars01.size() > 0) {
				assert(tmpInternalVars01.size() == 4);
				x_n2 = tmpInternalVars01[2];
				x_m2 = tmpInternalVars01[3];
			}

			Z3_ast tmpLenItems02[3] = { mk_length(t, x3), mk_length(t, args[1]),
					mk_int(ctx, -1) };
			Z3_ast tmpLen02 = Z3_mk_add(ctx, 3, tmpLenItems02);
			pushVectors(Z3_mk_eq(ctx, x2, mk_concat(t, x_n2, x_m2, update)),
					thenItems01, thenItems02);
			pushVectors(Z3_mk_eq(ctx, mk_length(t, x_n2), tmpLen02),
					thenItems01, thenItems02);

			Z3_ast condAst02n = registerContain(t, x_n2, args[1]);
			pushVectors(Z3_mk_not(ctx, condAst02n), thenItems01, thenItems02);
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst02n, condAst_x2));
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst_x3, condAst02n));

			indexOf_toAstMap[std::make_pair(x2, args[1])] = {x3, x4, x_n2, x_m2};
			carryOn[condAst_x2] = Z3_mk_eq(ctx, mk_length(t, x_n2), tmpLen02);
		} else {
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst_x3, condAst_x2));

			indexOf_toAstMap[std::make_pair(x2, args[1])] = {x3, x4};
		}

		Z3_ast nonDet01 = mk_binary_app(ctx, td->NonDet_AutomataDef,
				mk_str_value(t, arg02Plus.c_str()),
				mk_int(ctx, nondeterministicCounter++));
		Z3_ast nonDet02 = mk_binary_app(ctx, td->NonDet_AutomataDef,
				mk_str_value(t, arg02Plus.c_str()),
					mk_int(ctx, nondeterministicCounter++));
		thenItems01.push_back( Z3_mk_eq(ctx, result, mk_concat(t, x1,
														mk_concat(t, nonDet01,
																	mk_concat(t, x3, mk_concat(t, nonDet02, x4, update), update),
										update), update)));
		thenItems01.push_back(Z3_mk_not(ctx, condAst_x4));

		// -----------------------
		// case 3
		// condAst04 = registerContain(t, x4, args[1]);

		//  x4 = x5 . args[1] . x6

		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars02;
		if (indexOf_toAstMap.find(std::make_pair(x4, args[1]))
				!= indexOf_toAstMap.end())
			tmpInternalVars02 = indexOf_toAstMap[std::make_pair(x4, args[1])];

		Z3_ast x5 = mk_internal_string_var(t);
		Z3_ast x6 = mk_internal_string_var(t);

		if (tmpInternalVars00.size() > 0) {
			x5 = tmpInternalVars02[0];
			x6 = tmpInternalVars02[1];
		}

		thenItems02.push_back(Z3_mk_eq(ctx, x4, mk_concat(t, x5,
															 mk_concat(t, mk_binary_app(ctx, td->NonDet_AutomataDef, mk_str_value(t, arg01Plus.c_str()), mk_int(ctx,
																nondeterministicCounter++)),
																x6, update), update)));
		Z3_ast condAst_x5 = registerContain(t, x5, args[1]);
		thenItems02.push_back(Z3_mk_not(ctx, condAst_x5));

		Z3_ast condAst_x6 = registerContain(t, x6, args[1]);
		thenItems02.push_back(Z3_mk_not(ctx, condAst_x6));
		generalConstraints.push_back(
				Z3_mk_implies(ctx, condAst_x6, condAst_x4));

		if (!canSkip) {
			Z3_ast tmpLenItems04[3] = { mk_length(t, x4), mk_length(t, args[1]),
					mk_int(ctx, -1) };
			Z3_ast tmpLen04 = Z3_mk_add(ctx, 3, tmpLenItems04);

			Z3_ast x_n4 = mk_internal_string_var(t);
			Z3_ast x_m4 = mk_internal_string_var(t);
			if (tmpInternalVars02.size() > 0) {
				assert(tmpInternalVars02.size() == 4);
				x_n4 = tmpInternalVars02[2];
				x_m4 = tmpInternalVars02[3];
			}

			thenItems02.push_back(
					Z3_mk_eq(ctx, x4, mk_concat(t, x_n4, x_m4, update)));
			thenItems02.push_back(Z3_mk_eq(ctx, mk_length(t, x_n4), tmpLen04));

			Z3_ast condAst04n = registerContain(t, x_n4, args[1]);
			thenItems02.push_back(Z3_mk_not(ctx, condAst04n));

//			thenItems02.push_back(Z3_mk_implies(ctx, condAst_x5, condAst04n));
//			thenItems02.push_back(Z3_mk_implies(ctx, condAst04n, condAst_x4));
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst_x5, condAst04n));
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst04n, condAst_x4));

			indexOf_toAstMap[std::make_pair(x4, args[1])] = {x5, x6, x_n4, x_m4};
			carryOn[condAst_x4] = Z3_mk_eq(ctx, mk_length(t, x_n4), tmpLen04);
		} else {
//			thenItems02.push_back(Z3_mk_implies(ctx, condAst_x5, condAst_x4));
//			thenItems02.push_back(Z3_mk_implies(ctx, condAst_x6, condAst_x4));
			generalConstraints.push_back(
					Z3_mk_implies(ctx, condAst_x5, condAst_x4));

			indexOf_toAstMap[std::make_pair(x4, args[1])] = {x5, x6};
		}

		Z3_ast nondet03 = mk_binary_app(ctx,
				td->NonDet_AutomataDef,
				mk_str_value(t, arg02Plus.c_str()),
				mk_int(ctx, nondeterministicCounter++));
		Z3_ast nondet04 = mk_binary_app(ctx,
				td->NonDet_AutomataDef,
				mk_str_value(t, arg02Plus.c_str()),
				mk_int(ctx, nondeterministicCounter++));
		Z3_ast nondet05 = mk_binary_app(ctx,
				td->NonDet_AutomataDef,
				mk_str_value(t, arg02Plus.c_str()),
				mk_int(ctx, nondeterministicCounter++));
		thenItems02.push_back(
				Z3_mk_eq(ctx, result,
						mk_concat(t, x1,
								mk_concat(t, nondet03,
										mk_concat(t, x3,
												mk_concat(t, nondet04,
														mk_concat(t, x5,
																mk_concat(t,
																		nondet05,
																		x6,
																		update),
																update),
														update), update),
										update), update)));

		Z3_ast elseBranch = Z3_mk_eq(ctx, result, args[0]);

		Z3_ast ite04 = Z3_mk_ite(ctx, condAst_x4,
				mk_and_fromVector(t, thenItems02),
				mk_and_fromVector(t, thenItems01));
		Z3_ast ite02 = Z3_mk_ite(ctx, condAst_x2, ite04,
				mk_and_fromVector(t, thenItems00));

		Z3_ast breakdown[2] = { mk_and_fromVector(t, generalConstraints),
				Z3_mk_ite(ctx, condAst_arg00, ite02, elseBranch) };
		breakdownAssert = Z3_mk_and(ctx, 2, breakdown);
		replaceAllNodeMap[std::make_pair(args[0],
				std::make_pair(args[1], args[2]))] = result;
		return result;
	}
}

/*
 *
 */
Z3_ast reduce_replace(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	if (args[0] == args[1])
		return args[2];

	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr
			&& getNodeType(t, args[2]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		std::string arg2Str = getConstStrValue(t, args[2]);
		if (arg0Str.find(arg1Str) != std::string::npos) {
			int index1 = arg0Str.find(arg1Str);
			int index2 = index1 + arg1Str.length();
			std::string substr0 = arg0Str.substr(0, index1);
			std::string substr2 = arg0Str.substr(index2);
			std::string replaced = substr0 + arg2Str + substr2;
			replaceStrMap[StringOP(config.languageMap[REPLACE],
					{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]), node_to_stringOP(t, args[2])})] = TRUESTR;
			return mk_str_value(t, replaced.c_str());
		} else {
			replaceStrMap[StringOP(config.languageMap[REPLACE],
					{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]),	node_to_stringOP(t, args[2])})] = FALSETR;
			return args[0];
		}
	} else {
		std::vector<Z3_ast> tmpInternalVars;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1]))
				!= indexOf_toAstMap.end())
			tmpInternalVars = indexOf_toAstMap[std::make_pair(args[0], args[1])];
		else if (indexOf2_toAstMap.find(std::make_pair(std::make_pair(args[0], args[1]), mk_int(ctx, 0)))
				!= indexOf2_toAstMap.end())
			tmpInternalVars =
					indexOf2_toAstMap[std::make_pair(std::make_pair(args[0], args[1]), mk_int(ctx, 0))];
		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);

		if (tmpInternalVars.size() > 0) {
			x1 = tmpInternalVars[0];
			x2 = tmpInternalVars[1];
		}
		else {
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		Z3_ast result = mk_internal_string_var(t);

		Z3_ast condAst_arg0 = registerContain(t, args[0], args[1]);
		std::string boolName = Z3_ast_to_string(ctx, condAst_arg0);
		replaceStrMap[StringOP(config.languageMap[REPLACE], node_to_stringOP(t, args[0]),
				node_to_stringOP(t, args[1]), node_to_stringOP(t, args[2]))] =
				boolName;

		// -----------------------
		// true branch
		std::vector<Z3_ast> thenItems;
		//  args[0] = x1 . args[1] . x2
		bool update = true;
		thenItems.push_back(
				Z3_mk_eq(ctx, args[0],
						mk_concat(t, x1, mk_concat(t, args[1], x2, update),
								update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		Z3_ast condAst_x1 = registerContain(t, x1, args[1]);
		thenItems.push_back(Z3_mk_not(ctx, condAst_x1));
		if (config.printingConstraints)
			constraintSet.otherConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		if (!canSkipExt(t, args[1])) {
			//  args[0]  = x3 . x4 /\ |x3| = |x1| + |args[1]| - 1 /\ ! contains(x3, args[1])
			Z3_ast x3 = mk_internal_string_var(t);
			Z3_ast x4 = mk_internal_string_var(t);
			if (tmpInternalVars.size() > 0) {
				if (tmpInternalVars.size() == 4) {
					x3 = tmpInternalVars[2];
					x4 = tmpInternalVars[3];
				}
			}
			Z3_ast tmpLenItems[3] = { mk_length(t, x1), mk_length(t, args[1]),
					mk_int(ctx, -1) };
			Z3_ast tmpLen = Z3_mk_add(ctx, 3, tmpLenItems);

			thenItems.push_back(
					Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			if (config.printingConstraints)
				constraintSet.stringConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
			if (config.printingConstraints)
				constraintSet.arithmeticConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			Z3_ast condAst_x3 = registerContain(t, x3, args[1]);
			thenItems.push_back(Z3_mk_not(ctx, condAst_x3));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_x3));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x3, condAst_arg0));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x3, x4};

			carryOn[condAst_arg0] = Z3_mk_eq(ctx, mk_length(t, x3), tmpLen);
		} else {
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_arg0));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		thenItems.push_back(
				Z3_mk_eq(ctx, result,
						mk_concat(t, x1, mk_concat(t, args[2], x2, update),
								update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		// -----------------------
		// false branch
		Z3_ast ands[2] = {Z3_mk_eq(ctx, result, args[0]), Z3_mk_not(ctx, condAst_x1)};
		Z3_ast elseBranch = Z3_mk_and(ctx, 2, ands);

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg0,
				mk_and_fromVector(t, thenItems), elseBranch);
		if (config.printingConstraints) {
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, elseBranch));
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
		}

		replaceNodeMap[std::make_pair(args[0], std::make_pair(args[1], args[2]))] =
				result;
		return result;
	}
}

/*
 *
 */
Z3_ast reduce_toUpper(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	if (getNodeType(t, args[0]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string tmp = "";
		for (unsigned int i = 0; i < arg0Str.length(); ++i) {
			if (arg0Str[i] >= 97 && arg0Str[i] <= 122)
				tmp = tmp + (char) (arg0Str[i] - 32);
			else
				tmp = tmp + arg0Str[i];
		}
		return mk_str_value(t, tmp.c_str());
	} else {
		Z3_ast ts0 = mk_internal_string_var(t);
		breakdownAssert = Z3_mk_eq(ctx, mk_length(t, ts0),
				mk_length(t, args[0]));
		toUpperMap[ts0] = args[0];
		return ts0;
	}
}

/*
 *
 */
Z3_ast reduce_toLower(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	if (getNodeType(t, args[0]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string tmp = "";
		for (unsigned int i = 0; i < arg0Str.length(); ++i) {
			if (arg0Str[i] >= 65 && arg0Str[i] <= 90)
				tmp = tmp + (char) (arg0Str[i] + 32);
			else
				tmp = tmp + arg0Str[i];
		}
		return mk_str_value(t, tmp.c_str());
	} else {
		Z3_ast ts0 = mk_internal_string_var(t);
		breakdownAssert = Z3_mk_eq(ctx, mk_length(t, ts0),
				mk_length(t, args[0]));
		toLowerMap[ts0] = args[0];
		return ts0;
	}
}

/*
 *
 */
Z3_ast reduce_contains(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast reduceAst = NULL;

	if (args[0] == args[1]) {
		return Z3_mk_true(ctx);
	}

	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.find(arg1Str) != std::string::npos)
			reduceAst = Z3_mk_true(ctx);
		else
			reduceAst = Z3_mk_false(ctx);
	}
	else if (args[0] == args[1]){
		reduceAst = Z3_mk_true(ctx);
	}
	else {
		std::vector<Z3_ast> tmpInternalVars;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1]))
				!= indexOf_toAstMap.end())
			tmpInternalVars =
					indexOf_toAstMap[std::make_pair(args[0], args[1])];
//		else if (indexOf2_toAstMap.find(std::make_pair(std::make_pair(args[0], args[1]), mk_int(ctx, 0)))
//				!= indexOf2_toAstMap.end())
//			tmpInternalVars =
//					indexOf2_toAstMap[std::make_pair(std::make_pair(args[0], args[1]), mk_int(ctx, 0))];
		Z3_ast ts0;
		Z3_ast ts1;

		if (tmpInternalVars.size() > 0) {
			ts0 = tmpInternalVars[0];
			ts1 = tmpInternalVars[1];
			__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, Z3_ast_to_string(ctx, ts0));
		}
		else {
			ts0 = mk_internal_string_var(t);
			ts1 = mk_internal_string_var(t);
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {ts0, ts1};
		}

		reduceAst = registerContain(t, args[0], args[1]); // reduceAst = Contains(args[0], args[1])

		bool update = true;
		Z3_ast breakdown = Z3_mk_eq(ctx, args[0],
				mk_concat(t, ts0, mk_concat(t, args[1], ts1, update), update));
		breakdownAssert = Z3_mk_eq(ctx, reduceAst, breakdown);
		if (config.printingConstraints) {
			constraintSet.stringConstraints.emplace(
					node_to_string(t, breakdown));
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
		}
	}

	/* transitive property */
	for (std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast>::iterator it =
			containPairBoolMap.begin(); it != containPairBoolMap.end(); ++it) {
		if (it->first.first == args[1]) {
			Z3_ast tmp = registerContain(t, args[0], it->first.second);
			Z3_ast tmp01 = Z3_mk_eq(ctx, tmp, Z3_mk_true(ctx));

			std::vector<Z3_ast> ands;
			ands.push_back(it->second);
			ands.push_back(reduceAst);
			Z3_ast tmp02 = Z3_mk_implies(ctx, mk_and_fromVector(t, ands),
					tmp01);
			addAxiom(t, tmp02, __LINE__, true);
		}
	}
	return reduceAst;
}

/*
 *
 */
Z3_ast reduce_startswith(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	Z3_ast reduceAst = NULL;
	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.length() < arg1Str.length()) {
			reduceAst = Z3_mk_false(ctx);
		} else {
			if (arg0Str.substr(0, arg1Str.length()) == arg1Str) {
				startsWithStrMap[StringOP(config.languageMap[STARTSWITH],
						node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
						TRUESTR;
				reduceAst = Z3_mk_true(ctx);
			} else {
				startsWithStrMap[StringOP(config.languageMap[STARTSWITH],
						node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
						FALSETR;
				reduceAst = Z3_mk_false(ctx);
			}
		}
	}
	else if (args[0] == args[1])
			reduceAst = Z3_mk_true(ctx);
	else {
		Z3_ast resBoolVar = registerStartsWith(t, args[0], args[1]);
		Z3_ast ts0 = mk_internal_string_var(t);
		Z3_ast ts1 = mk_internal_string_var(t);

		std::string boolVar = Z3_ast_to_string(ctx, resBoolVar);
		startsWithStrMap[StringOP(config.languageMap[STARTSWITH],
				node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
						boolVar;
		// boolVar = startswith(arg[0], arg[1])
		// --------------------------------------------
		std::vector<Z3_ast> ands;
		bool update;
		ands.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, ts1, update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, ands[ands.size() - 1]));

		ands.push_back(Z3_mk_eq(ctx, mk_length(t, ts0), mk_length(t, args[1])));
		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, ands[ands.size() - 1]));

		ands.push_back(
				Z3_mk_ite(ctx, Z3_mk_eq(ctx, ts0, args[1]),
						Z3_mk_eq(ctx, resBoolVar, Z3_mk_true(ctx)),
						Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx))));
		if (config.printingConstraints) {
			constraintSet.otherConstraints.emplace(
					node_to_string(t, ands[ands.size() - 1]));
			constraintSet.stringConstraints.emplace(
					node_to_string(t, Z3_mk_eq(ctx, ts0, args[1])));
			constraintSet.otherConstraints.emplace(
					node_to_string(t,
							Z3_mk_eq(ctx, resBoolVar, Z3_mk_true(ctx))));
			constraintSet.otherConstraints.emplace(
					node_to_string(t,
							Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx))));
		}

		Z3_ast then1 = mk_and_fromVector(t, ands);
		breakdownAssert = Z3_mk_ite(ctx,
				Z3_mk_ge(ctx, mk_length(t, args[0]), mk_length(t, args[1])),
				then1, Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx)));
		if (config.printingConstraints) {
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t,
							Z3_mk_ge(ctx, mk_length(t, args[0]),
									mk_length(t, args[1]))));
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
		}
		reduceAst = resBoolVar;
	}

	return reduceAst;
}

/*
 *
 */
Z3_ast reduce_endswith(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast reduceAst = NULL;

	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.length() < arg1Str.length()) {
			reduceAst = Z3_mk_false(ctx);
		} else {
			if (arg0Str.substr(arg0Str.length() - arg1Str.length(),
					arg1Str.length()) == arg1Str) {
				endsWithStrMap[StringOP(config.languageMap[ENDSWITH],
						node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
						TRUESTR;
				reduceAst = Z3_mk_true(ctx);
			} else {
				endsWithStrMap[StringOP(config.languageMap[ENDSWITH],
						node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
						FALSETR;
				reduceAst = Z3_mk_false(ctx);
			}
		}
	}
	else if (args[0] == args[1])
			reduceAst = Z3_mk_true(ctx);
	else {
		Z3_ast resBoolVar = registerEndsWith(t, args[0], args[1]);
		Z3_ast ts0 = mk_internal_string_var(t);
		Z3_ast ts1 = mk_internal_string_var(t);
		std::string boolVar = Z3_ast_to_string(ctx, resBoolVar);
		endsWithStrMap[StringOP(config.languageMap[ENDSWITH],
				node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
						boolVar;
		// boolVar = endswith(arg[0], arg[1])
		// --------------------------------------------
		std::vector<Z3_ast> ands01;
		bool update;

		ands01.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, ts1, update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, ands01[ands01.size() - 1]));

		ands01.push_back(Z3_mk_eq(ctx, mk_length(t, ts1), mk_length(t, args[1])));
		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, ands01[ands01.size() - 1]));

		ands01.push_back(
				Z3_mk_ite(ctx, Z3_mk_eq(ctx, ts1, args[1]),
						Z3_mk_eq(ctx, resBoolVar, Z3_mk_true(ctx)),
						Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx))));
		if (config.printingConstraints) {
			constraintSet.otherConstraints.emplace(
					node_to_string(t, ands01[ands01.size() - 1]));
			constraintSet.stringConstraints.emplace(
					node_to_string(t, Z3_mk_eq(ctx, ts1, args[1])));
			constraintSet.otherConstraints.emplace(
					node_to_string(t,
							Z3_mk_eq(ctx, resBoolVar, Z3_mk_true(ctx))));
			constraintSet.otherConstraints.emplace(
					node_to_string(t,
							Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx))));
		}

		breakdownAssert = Z3_mk_ite(ctx,
				Z3_mk_ge(ctx, mk_length(t, args[0]), mk_length(t, args[1])),
				mk_and_fromVector(t, ands01), Z3_mk_eq(ctx, resBoolVar, Z3_mk_false(ctx)));
		if (config.printingConstraints) {
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t,
							Z3_mk_ge(ctx, mk_length(t, args[0]),
									mk_length(t, args[1]))));
		}
		reduceAst = resBoolVar;
	}

	return reduceAst;
}

/*
 *
 */
Z3_ast reduce_indexof(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	/* doing the real work */
	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.find(arg1Str) != std::string::npos) {
			int index = arg0Str.find(arg1Str);
			indexOfStrMap[StringOP(config.languageMap[INDEXOF],
					node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
					std::make_pair("", std::make_pair(std::to_string(index), std::to_string(index)));
			return mk_int(ctx, index);
		} else {
			indexOfStrMap[StringOP(config.languageMap[INDEXOF],
					node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
					std::make_pair("", std::make_pair("-1", "-1"));
			return mk_int(ctx, -1);
		}
	}
	else if (args[0] == args[1]){
		return mk_int(ctx, 0);
	}
	else {
		/* check if the constrain is handled */
		std::vector<Z3_ast> tmpInternalVars;
		if (indexOf_toAstMap.find(std::make_pair(args[0], args[1])) != indexOf_toAstMap.end())
			tmpInternalVars = indexOf_toAstMap[std::make_pair(args[0], args[1])];
		else if (indexOf2_toAstMap.find(std::make_pair(std::make_pair(args[0], args[1]), mk_int(ctx, 0)))
				!= indexOf2_toAstMap.end())
			tmpInternalVars = indexOf2_toAstMap[std::make_pair(std::make_pair(args[0], args[1]), mk_int(ctx, 0))];
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
		thenItems.push_back(
				Z3_mk_eq(ctx, args[0],
						mk_concat(t, x1, mk_concat(t, args[1], x2, update),
								update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		Z3_ast condAst_x1 = registerContain(t, x1, args[1]);
		thenItems.push_back(Z3_mk_not(ctx, condAst_x1));
		if (config.printingConstraints)
			constraintSet.otherConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		//  indexAst = |x1|
		thenItems.push_back(Z3_mk_eq(ctx, indexAst, mk_length(t, x1)));
		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		StringOP tmpOp = StringOP(config.languageMap[INDEXOF], node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]));
		indexOfStrMap[tmpOp] =
				std::make_pair(boolVar,
						std::make_pair(generateVarLength(node_to_string(t, x1)),
								node_to_string(t, indexAst)));
		__debugPrint(logFile, "%d %s : = %s %s %s",  __LINE__, __FUNCTION__, indexOfStrMap[tmpOp].first.c_str(), indexOfStrMap[tmpOp].second.first.c_str(),
																						indexOfStrMap[tmpOp].second.second.c_str());
		if (!canSkipExt(t, args[1])) {
			//     args[0]  = x3 . x4
			//  /\ |x3| = |x1| + |args[1]| - 1
			//  /\ ! contains(x3, args[1])
			Z3_ast x3 = mk_internal_string_var(t);
			Z3_ast x4 = mk_internal_string_var(t);
			if (tmpInternalVars.size() > 0) {
				if (tmpInternalVars.size() >= 4){
					x3 = tmpInternalVars[2];
					x4 = tmpInternalVars[3];
				}
			}
			Z3_ast adds[3] = {mk_length(t, x1), mk_length(t, args[1]), mk_int(ctx, -1)};
			Z3_ast tmpLen = Z3_mk_add(ctx, 3, adds);

			thenItems.push_back(
					Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			if (config.printingConstraints)
				constraintSet.stringConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
			if (config.printingConstraints)
				constraintSet.arithmeticConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			Z3_ast condAst_x3 = registerContain(t, x3, args[1]);
			thenItems.push_back(Z3_mk_not(ctx, condAst_x3));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_x3));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x3, condAst_arg0));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x3, x4};

			carryOn[condAst_arg0] = Z3_mk_eq(ctx, mk_length(t, x3), tmpLen);
		} else {
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x1, condAst_arg0));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		// -----------------------
		// false branch
		Z3_ast ands[2] = {Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1)), Z3_mk_not(ctx, condAst_x1)};
		Z3_ast elseBranch = Z3_mk_and(ctx, 2, ands);

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg0,
				mk_and_fromVector(t, thenItems), elseBranch);
		if (config.printingConstraints) {
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, elseBranch));
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
		}
		return indexAst;
	}
}

/*
 *
 */
/*
 *
 */
Z3_ast reduce_indexof2(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	/* doing the real work */
	std::string tmp = node_to_string(t, args[2]);
	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr && tmp[0] >= '0'
			&& tmp[0] <= '9') {
		std::string arg0Str = getConstStrValue(t, args[0]);
		int pos = std::atoi(tmp.c_str());
		arg0Str = arg0Str.substr(pos);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.find(arg1Str) != std::string::npos) {
			int index = arg0Str.find(arg1Str);
			index += pos;
			indexOf2StrMap[StringOP(config.languageMap[INDEXOF2],
					{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]), node_to_stringOP(t, args[2])})] =
					std::make_pair("", std::make_pair(std::to_string(index), std::to_string(index)));
			return mk_int(ctx, index);
		} else {
			indexOf2StrMap[StringOP(config.languageMap[INDEXOF2],
					{node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]), node_to_stringOP(t, args[2])})] =
					std::make_pair("", std::make_pair("-1", "-1"));
			return mk_int(ctx, -1);
		}
	}
	else if (args[0] == args[1] && node_to_string(t, args[2])[0] >= '0' && node_to_string(t, args[2])[0] <= '9' ) {
		std::string tmp =  node_to_string(t, args[2]);
		if (tmp.compare("0") == 0)
			return mk_int(ctx, 0);
		else
			return mk_int(ctx, -1);
	}
	else {
		/* check if the contraint is handled */
		std::vector<Z3_ast> tmpInternalVars;
		if (indexOf2_toAstMap.find(std::make_pair(std::make_pair(args[0], args[1]), args[2])) != indexOf2_toAstMap.end())
			tmpInternalVars = indexOf2_toAstMap[std::make_pair(std::make_pair(args[0], args[1]), args[2])];
		else {
			std::string tmp = Z3_ast_to_string(ctx, args[2]);
			if (tmp.compare("0") == 0)
				if (indexOf_toAstMap.find(std::make_pair(args[0], args[1])) != indexOf_toAstMap.end())
					tmpInternalVars = indexOf_toAstMap[std::make_pair(args[0], args[1])];
		}
		Z3_ast x0 = mk_internal_string_var(t);
		Z3_ast x1 = mk_internal_string_var(t);
		if (tmpInternalVars.size() > 0) {
			x0 = tmpInternalVars[0];
			x1 = tmpInternalVars[1];
		}
		else {

		}

		Z3_ast indexAst = mk_internal_int_var(t);

		// condAst = |arg0| >= arg2
		Z3_ast condAst_arg0 = Z3_mk_gt(ctx, mk_length(t, args[0]), args[2]);
		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, condAst_arg0));

		// -----------------------
		bool update;
		// true branch
		std::vector<Z3_ast> thenItems;
		Z3_ast argsTmp[2] = {x1, args[1]};
		Z3_ast tmpAst = reduce_indexof(t, argsTmp, breakdownAssert);

		std::string arg02Str = Z3_ast_to_string(ctx, args[2]);
		if (arg02Str.compare("0") == 0){
			indexOf_toAstMap[std::make_pair(args[0], args[1])] = indexOf_toAstMap[std::make_pair(x1, args[1])];
			StringOP tmpOp = StringOP(config.languageMap[INDEXOF], node_to_stringOP(t, x1),
					node_to_stringOP(t, args[1]));
			indexOf2StrMap[StringOP(config.languageMap[INDEXOF2], {node_to_stringOP(t, args[0]),
					node_to_stringOP(t, args[1]),
					node_to_stringOP(t, args[2])})] = indexOfStrMap[tmpOp];
			__debugPrint(logFile, "%d %s : = %s %s",  __LINE__, __FUNCTION__, indexOfStrMap[tmpOp].second.first.c_str(),
					indexOfStrMap[tmpOp].second.second.c_str());
			indexOfStrMap.erase(StringOP(config.languageMap[INDEXOF], node_to_stringOP(t, x1),
					node_to_stringOP(t, args[1])));
			std::vector<Z3_ast> tmpVector = {Z3_mk_eq(ctx, args[0], x1), breakdownAssert};
			breakdownAssert = mk_and_fromVector(t, tmpVector);
			return tmpAst;
		}

		//  args[0] =  x0 . x1
		thenItems.push_back(
				Z3_mk_eq(ctx, args[0],
						mk_concat(t, x0, x1, update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		//  |x0| =  arg2
		thenItems.push_back(
				Z3_mk_eq(ctx, mk_length(t, x0), args[2]));
		__debugPrint(logFile, "%d zzzzzz: %s\n", __LINE__,  Z3_ast_to_string(ctx, thenItems[thenItems.size() - 1]) );

		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		/* edit breakdown assert */
		Z3_ast cond = Z3_get_app_arg(ctx, Z3_to_app(ctx, breakdownAssert), 0);
		Z3_ast correctCase = Z3_get_app_arg(ctx, Z3_to_app(ctx, breakdownAssert), 1);
		Z3_ast incorrectCase = Z3_get_app_arg(ctx, Z3_to_app(ctx, breakdownAssert), 2);

		//  indexAst = tmpAst + args[2]
		Z3_ast addResult[2] = {tmpAst, args[2]};
		Z3_ast addNode = Z3_mk_add(ctx, 2, addResult);
		std::vector<Z3_ast> tmpVector01 = {correctCase, Z3_mk_eq(ctx, indexAst, addNode)};

		std::vector<Z3_ast> tmpVector02 = {incorrectCase, Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1)) };
		thenItems.push_back(
				Z3_mk_ite(ctx, cond,
						mk_and_fromVector(t, tmpVector01),
						mk_and_fromVector(t, tmpVector02)));

		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		Z3_ast boolAst = mk_internal_bool_var(t);

		std::string boolVar = Z3_ast_to_string(ctx, boolAst);

		indexOf2_toAstMap[std::make_pair(std::make_pair(args[0], args[1]), args[2])] = {x0, x1};

		indexOf2StrMap[StringOP(config.languageMap[INDEXOF2], {node_to_stringOP(t, args[0]),
				node_to_stringOP(t, args[1]),
				node_to_stringOP(t, args[2])})] = std::make_pair(boolVar,
						std::make_pair(node_to_string(t, addNode),
								node_to_string(t, indexAst)));

		// -----------------------
		// false branch
		Z3_ast elseBranch = Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1));
		std::vector<Z3_ast> tmpVector03 = {cond, condAst_arg0};
		std::vector<Z3_ast> tmpVector04 = {Z3_mk_eq(ctx, boolAst, mk_and_fromVector(t, tmpVector03)),
				Z3_mk_ite(ctx, condAst_arg0, mk_and_fromVector(t, thenItems), elseBranch)};
		breakdownAssert = mk_and_fromVector(t, tmpVector04);
		carryOn[boolAst] = Z3_mk_ite(ctx, Z3_mk_gt(ctx, mk_length(t, args[0]), args[2]),
				Z3_mk_eq(ctx, mk_length(t, x0), args[2]),
				Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1)));
		if (config.printingConstraints) {
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, elseBranch));
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
		}
		return indexAst;
	}
}

/*
 *
 */
Z3_ast reduce_lastindexof(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	/* doing the real work */
	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_ConstStr) {
		std::string arg0Str = getConstStrValue(t, args[0]);
		std::string arg1Str = getConstStrValue(t, args[1]);
		if (arg0Str.rfind(arg1Str) != std::string::npos) {
			int index = arg0Str.rfind(arg1Str);
			lastIndexOfStrMap[StringOP(config.languageMap[LASTINDEXOF],
					node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
					std::make_pair("", std::make_pair(std::to_string(index), std::to_string(index)));
			return mk_int(ctx, index);
		} else {
			lastIndexOfStrMap[StringOP(config.languageMap[LASTINDEXOF],
					node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
					std::make_pair("", std::make_pair("-1", "-1"));
			return mk_int(ctx, -1);
		}
	}
	else if (args[0] == args[1]) {
		return mk_int(ctx, 0);
	}
	else {
		std::vector<Z3_ast> tmpInternalVars;
		if (lastIndexOf_toAstMap.find(std::make_pair(args[0], args[1]))
				!= lastIndexOf_toAstMap.end())
			tmpInternalVars = lastIndexOf_toAstMap[std::make_pair(args[0],
					args[1])];

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
		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		//  args[0] = x1 . args[1] . x2
		thenItems.push_back(
				Z3_mk_eq(ctx, args[0],
						mk_concat(t, x1, mk_concat(t, args[1], x2, update),
								update)));
		if (config.printingConstraints)
			constraintSet.stringConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		thenItems.push_back(Z3_mk_eq(ctx, indexAst, mk_length(t, x1)));
		if (config.printingConstraints)
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		//  x2 doesn't contain args[1]
		Z3_ast condAst_x2 = registerContain(t, x2, args[1]);
		thenItems.push_back(Z3_mk_not(ctx, condAst_x2));
		if (config.printingConstraints)
			constraintSet.otherConstraints.emplace(
					node_to_string(t, thenItems[thenItems.size() - 1]));

		lastIndexOfStrMap[StringOP(config.languageMap[LASTINDEXOF],
				node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]))] =
				std::make_pair(boolVar,
						std::make_pair(generateVarLength(node_to_string(t, x1)),
								node_to_string(t, indexAst)));

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
			thenItems.push_back(
					Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			if (config.printingConstraints)
				constraintSet.stringConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
			if (config.printingConstraints)
				constraintSet.arithmeticConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			Z3_ast condAst_x4 = registerContain(t, x4, args[1]);
			thenItems.push_back(Z3_mk_not(ctx, condAst_x4));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x2, condAst_x4));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			thenItems.push_back(Z3_mk_implies(ctx, condAst_x4, condAst_arg0));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			lastIndexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2, x3, x4};

			carryOn[condAst_arg0] = Z3_mk_eq(ctx, mk_length(t, x3), tmpLen);
		} else {
			thenItems.push_back(Z3_mk_implies(ctx, condAst_x2, condAst_arg0));
			if (config.printingConstraints)
				constraintSet.otherConstraints.emplace(
						node_to_string(t, thenItems[thenItems.size() - 1]));

			lastIndexOf_toAstMap[std::make_pair(args[0], args[1])] = {x1, x2};
		}

		//----------------------------
		// else branch
		Z3_ast elseItems = Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1));

		breakdownAssert = Z3_mk_ite(ctx, condAst_arg0,
				mk_and_fromVector(t, thenItems), elseItems);
		if (config.printingConstraints) {
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, elseItems));
			constraintSet.otherConstraints.emplace(
					node_to_string(t, breakdownAssert));
		}
		return indexAst;
	}
}

/*
 *
 */
Z3_ast reduce_charAt(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	__debugPrint(logFile, "%d, %d | %d", getNodeType(t, args[0]),
			getNodeType(t, args[1]), my_Z3_Num);
	if (getNodeType(t, args[0]) == my_Z3_ConstStr
			&& getNodeType(t, args[1]) == my_Z3_Num) {
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
		std::vector<Z3_ast> varSet = registerCharAt(t, args[0], args[1]);
		Z3_ast ts0 = varSet[0];
		Z3_ast ts1 = varSet[1];
		Z3_ast ts2 = varSet[2];

		std::vector<Z3_ast> tmp = {
				Z3_mk_ge(ctx, args[1], mk_int(ctx, 0)),
				Z3_mk_lt(ctx, args[1], mk_length(t, args[0])) };
		Z3_ast cond = mk_and_fromVector(t, tmp);
		Z3_ast astBool = mk_internal_bool_var(t);
		std::string boolVar = Z3_ast_to_string(ctx, astBool);

		bool update;
		Z3_ast ands[3];
		ands[0] = Z3_mk_eq(ctx, args[0],
				mk_concat(t, ts0, mk_concat(t, ts1, ts2, update), update));
		ands[1] = Z3_mk_eq(ctx, args[1], mk_length(t, ts0));
		ands[2] = Z3_mk_eq(ctx, mk_length(t, ts1), mk_int(ctx, 1));

		Z3_ast thenBranch = Z3_mk_and(ctx, 3, ands);
		std::vector<Z3_ast> elseVector = {Z3_mk_eq(ctx, mk_length(t, ts1), mk_int(ctx, 0)),
				Z3_mk_eq(ctx, mk_length(t, ts2), mk_int(ctx, 0))
		};
		Z3_ast elseBranch = mk_and_fromVector(t, elseVector);
		std::vector<Z3_ast> tmp01 = {
				Z3_mk_eq(ctx, astBool, cond),
				Z3_mk_ite(ctx, astBool, thenBranch, elseBranch) };
		breakdownAssert = mk_and_fromVector(t, tmp01);

		std::vector<Z3_ast> carryOnArgs = {
				Z3_mk_eq(ctx, args[1], mk_length(t, ts0)),
				Z3_mk_eq(ctx, mk_int(ctx, 1), mk_length(t, ts1))
		};
		carryOn[astBool] = mk_and_fromVector(t, carryOnArgs);
		charAtStrMap[StringOP(config.languageMap[CHARAT], node_to_stringOP(t, args[0]),
				node_to_stringOP(t, args[1]))] = std::make_pair(boolVar,
												node_to_string(t, ts1));

		if (config.printingConstraints) {
			constraintSet.stringConstraints.emplace(node_to_string(t, ands[0]));
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, ands[1]));
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, ands[2]));
			constraintSet.stringConstraints.emplace(
					node_to_string(t, elseBranch));
			constraintSet.otherConstraints.emplace(node_to_string(t, tmp01[0]));
			constraintSet.otherConstraints.emplace(node_to_string(t, tmp01[1]));
		}
		return ts1;
	}
}

/*
 *
 */
Z3_ast reduce_subStr(Z3_theory t, Z3_ast const args[],
		Z3_ast & breakdownAssert) {
	Z3_context ctx = Z3_theory_get_context(t);

	Z3_ast ts0 = mk_internal_string_var(t);
	Z3_ast ts1 = mk_internal_string_var(t);
	Z3_ast ts2 = mk_internal_string_var(t);

	bool update;

	int value_prefix = getConstIntValue(t, args[1]);
	std::string arg01Str = convertStrNodeToArithmeticNode(t, args[1]);
	std::string arg02Str = convertStrNodeToArithmeticNode(t, args[2]);

	if (value_prefix != 0) {
		Z3_ast and_item[3];
		and_item[0] = Z3_mk_eq(ctx, args[0],
				mk_concat(t, ts0, mk_concat(t, ts1, ts2, update), update));
		and_item[1] = Z3_mk_ite(ctx,
							Z3_mk_ge(ctx, args[1], mk_int(ctx, 0)),
							Z3_mk_ite(ctx,
								Z3_mk_le(ctx, args[1], mk_length(t, args[0])),
								Z3_mk_eq(ctx, args[1], mk_length(t, ts0)),
								Z3_mk_eq(ctx, mk_length(t, ts0), mk_length(t, args[0]))),
							Z3_mk_eq(ctx, mk_length(t, ts1), mk_int(ctx, 0)));

		std::string str01 = createITEOperator(
								createLessEqualConstraint("0", node_to_string(t, args[1])),
								createITEOperator(
									createLessEqualConstraint(node_to_string(t, args[1]), generateVarLength(node_to_string(t, args[0]))),
									createEqualConstraint(node_to_string(t, args[1]), generateVarLength(node_to_string(t, ts0))),
									createEqualConstraint(generateVarLength(node_to_string(t, ts1)), generateVarLength(node_to_string(t, ts0)))),
								createEqualConstraint(generateVarLength(node_to_string(t, ts0)), "0"));
		Z3_ast * items = new Z3_ast[2];
		items[0] = args[1];
		items[1] = args[2];

		Z3_ast * otherItems = new Z3_ast[2];
		otherItems[0] = args[1];
		otherItems[1] = mk_length(t, ts1);
		and_item[2] = Z3_mk_ite(ctx,
				Z3_mk_ge(ctx, args[1], mk_int(ctx, 0)),
				Z3_mk_ite(ctx,
						Z3_mk_ge(ctx,
							mk_length(t, args[0]),
							Z3_mk_add(ctx, 2, items)),
						Z3_mk_eq(ctx, args[2], mk_length(t, ts1)),
						Z3_mk_eq(ctx, Z3_mk_add(ctx, 2, otherItems), mk_length(t, args[0]))),
				Z3_mk_eq(ctx, mk_length(t, ts1), mk_int(ctx, 0)));
		std::string str02 = createITEOperator(
								createLessEqualConstraint("0", node_to_string(t, args[1])),
								createITEOperator(
									createLessEqualConstraint(
										createPlusOperator(node_to_string(t, args[1]), node_to_string(t, args[2])),
										generateVarLength(node_to_string(t, args[0]))),
									createEqualConstraint(node_to_string(t, args[2]), generateVarLength(node_to_string(t, ts1))),
									createEqualConstraint(
										createPlusOperator(node_to_string(t, args[1]), generateVarLength(node_to_string(t, ts1))),
										generateVarLength(node_to_string(t, args[0])))),
								createEqualConstraint(generateVarLength(node_to_string(t, ts1)), "0"));
		/* convert to string, prepare for replaceStrMap */
		std::string tmp = "(and " + str01 + " " + str02 + ")";

		subStrStrMap[StringOP(config.languageMap[SUBSTRING],
				node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]),
				node_to_stringOP(t, args[2]))] = std::make_pair(node_to_string(t, ts1), tmp);

		breakdownAssert = Z3_mk_and(ctx, 3, and_item);
	} else {
		// substring from 0
		Z3_ast ands[2];
		ands[0] = Z3_mk_eq(ctx, args[0], mk_concat(t, ts1, ts2, update));

		Z3_ast * items = new Z3_ast[2];
		items[0] = args[1];
		items[1] = args[2];

		Z3_ast * otherItems = new Z3_ast[2];
		otherItems[0] = args[1];
		otherItems[1] = mk_length(t, ts1);
		ands[1] = Z3_mk_ite(ctx,
				Z3_mk_ge(ctx, args[1], mk_int(ctx, 0)),
				Z3_mk_ite(ctx,
						Z3_mk_ge(ctx,
							mk_length(t, args[0]),
							Z3_mk_add(ctx, 2, items)),
						Z3_mk_eq(ctx, args[2], mk_length(t, ts1)),
						Z3_mk_eq(ctx, Z3_mk_add(ctx, 2, otherItems), mk_length(t, args[0]))),
				Z3_mk_eq(ctx, mk_length(t, ts1), mk_int(ctx, 0)));

		std::string str02 = createITEOperator(
										createLessEqualConstraint("0", node_to_string(t, args[1])),
										createITEOperator(
											createLessEqualConstraint(
												createPlusOperator(node_to_string(t, args[1]), node_to_string(t, args[2])),
												generateVarLength(node_to_string(t, args[0]))),
											createEqualConstraint(node_to_string(t, args[2]), generateVarLength(node_to_string(t, ts1))),
											createEqualConstraint(
												createPlusOperator(node_to_string(t, args[1]), generateVarLength(node_to_string(t, ts1))),
												generateVarLength(node_to_string(t, args[0])))),
										createEqualConstraint(generateVarLength(node_to_string(t, ts1)), "0"));

		subStrStrMap[StringOP(config.languageMap[SUBSTRING],
				node_to_stringOP(t, args[0]), node_to_stringOP(t, args[1]),
				node_to_stringOP(t, args[2]))] = std::make_pair(node_to_string(t, ts1), str02);
		breakdownAssert = Z3_mk_and(ctx, 2, ands);

		if (config.printingConstraints) {
			constraintSet.stringConstraints.emplace(node_to_string(t, ands[0]));
			constraintSet.arithmeticConstraints.emplace(
					node_to_string(t, ands[1]));
		}
	}
	subStrNodeMap[std::make_pair(args[0], std::make_pair(args[1], args[2]))] =
			ts1;
	return ts1;
}

/*
 *
 */
Z3_ast reduce_str2regex(Z3_theory t, Z3_func_decl d, Z3_ast const args[],
		Z3_ast & extraAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	Z3_ast converted = mk_unary_app(ctx, d, args[0]);

	return converted;
}

/*
 *
 */
Z3_ast reduce_regexStar(Z3_theory t, Z3_ast const args[],
		Z3_ast & extraAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_app arg1_func_app = Z3_to_app(ctx, args[0]);
	Z3_func_decl funcDecl = Z3_get_app_decl(ctx, arg1_func_app);
	if (funcDecl == td->RegexStar) {
		return args[0];
	}
	else if (funcDecl == td->RegexAllChar){
		return Z3_mk_app(ctx, td->RegexAll, 0, NULL);
	}
	else
		return NULL;
}

/*
 *
 */
Z3_ast reduce_regexPlus(Z3_theory t, Z3_ast const args[],
		Z3_ast & extraAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	Z3_app childFuncApp = Z3_to_app(ctx, args[0]);
	Z3_func_decl childFuncDecl = Z3_get_app_decl(ctx, childFuncApp);
	if (childFuncDecl == td->RegexPlus) {
		// (r+)+ --> r+
		return args[0];
	} else if (childFuncDecl == td->RegexStar) {
		// (r*)+ --> r*
		Z3_ast childArg0 = Z3_get_app_arg(ctx, childFuncApp, 0);
		return mk_unary_app(ctx, td->RegexStar, childArg0);
	} else {
		// r+ --> RegexConcat(r, r*)
		return mk_binary_app(ctx, td->RegexConcat, args[0],
				mk_unary_app(ctx, td->RegexStar, args[0]));
	}
}

/*
 *
 */
Z3_ast reduce_regexConcat(Z3_theory t, Z3_ast const args[],
		Z3_ast & extraAssert) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	Z3_app arg0_func_app = Z3_to_app(ctx, args[0]);
	Z3_app arg1_func_app = Z3_to_app(ctx, args[1]);

	Z3_func_decl arg0_funcDecl = Z3_get_app_decl(ctx, arg0_func_app);
	Z3_func_decl arg1_funcDecl = Z3_get_app_decl(ctx, arg1_func_app);

	// TODO what happens if they are not constant string
	if (arg0_funcDecl == td->Str2Reg && arg1_funcDecl == td->Str2Reg) {
		Z3_ast arg0Str = Z3_get_app_arg(ctx, arg0_func_app, 0);
		Z3_ast arg1Str = Z3_get_app_arg(ctx, arg1_func_app, 0);
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
	appendToFile(
			"(RegexIn " + exportNodeName(t, args[0]) + " "
					+ exportNodeName(t, args[1]) + ")");

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
		return Z3_mk_eq(ctx, args[0],
				mk_unary_app(ctx, td->AutomataDef,
						Z3_get_app_arg(ctx, arg1_func_app, 0)));
	} else if (funcDecl == td->RegexAll) {
		return Z3_mk_eq(ctx, args[0], mk_internal_string_var(t));
	} else if (funcDecl == td->RegexAllChar) {
		std::vector<Z3_ast> constraints;
		constraints.emplace_back(
				Z3_mk_eq(ctx, args[0], mk_internal_string_var(t)));
		constraints.emplace_back(
				Z3_mk_eq(ctx, mk_length(t, args[0]), mk_int(ctx, 1)));
		return mk_and_fromVector(t, constraints);
	}
	if (funcDecl == td->RegexNone) {
		return Z3_mk_eq(ctx, mk_length(t, args[0]), mk_int(ctx, 0));
	}
	// ----------------------------------------------------
	else {
		if (regexStr.find("__NotConstStr__") == std::string::npos
				&& regexStr.find("__Contain_Vars__") == std::string::npos) {
			if (regexStr.find('*') != std::string::npos
					|| regexStr.find('+') != std::string::npos) {
				Z3_ast newapp = mk_binary_app(ctx, td->NonDet_AutomataDef,
						mk_str_value(t, regexStr.c_str()),
						mk_int(ctx, nondeterministicCounter++));
				return Z3_mk_eq(ctx, args[0], newapp);
			} else {
				Z3_ast newapp = mk_unary_app(ctx, td->AutomataDef,
						mk_str_value(t, regexStr.c_str()));
				return Z3_mk_eq(ctx, args[0], newapp);
			}
		}
	}
	return NULL;
}

/*
 *
 */
Z3_ast reduce_grammarIn(Z3_theory t, Z3_ast const args[],
		Z3_ast & extraAssert) {
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

	if (grmStr.size() == 0) {
		std::cerr << "Grammar is not defined!\n\n\n";
		return NULL;
	}

	Z3_ast* or_items = new Z3_ast[grmStr.size()];
	for (unsigned int i = 0; i < grmStr.size(); ++i) {
		if (grmStr[i].length() > 0) {
			Z3_ast rhs;
			if (grmStr[i].find('*') != std::string::npos
					|| grmStr[i].find('+') != std::string::npos) {
				rhs = mk_binary_app(ctx, td->NonDet_AutomataDef,
						mk_str_value(t, grmStr[i].c_str()),
						mk_int(ctx, nondeterministicCounter++));
			} else {
				rhs = mk_unary_app(ctx, td->AutomataDef,
						mk_str_value(t, grmStr[i].c_str()));
			}

			if (isConstStr(t, args[0])) {
				std::string constStr = Z3_ast_to_string(ctx, args[0]);
				Z3_ast lhs = mk_unary_app(ctx, td->AutomataDef,
						mk_str_value(t, constStr.c_str()));
				or_items[i] = Z3_mk_eq(ctx, lhs, rhs);
			} else {
				or_items[i] = Z3_mk_eq(ctx, args[0], rhs);
			}
		} else {
			std::cerr << "Grammar is not defined!\n\n\n";
			return NULL;
		}
	}
	return Z3_mk_or(ctx, grmStr.size(), or_items);
}

/*
 *Z3_bool Th_reduce_app(Z3_theory t, Z3_func_decl d, unsigned n, Z3_ast const args[], Z3_ast * result);
 */
int Th_reduce_app(Z3_theory t, Z3_func_decl d, unsigned n, Z3_ast const args[],
		Z3_ast * result) {
	Z3_context ctx = Z3_theory_get_context(t);
	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);

	__debugPrint(logFile, "\n*** %s ***:", __FUNCTION__);
	std::vector<Z3_ast> encodedConstraints;
	std::vector<Z3_ast> rewrittenConstraints;
	// Convert the tricky "string" representation to string constant
	int convertedFlag = 0;
	Z3_ast * convertedArgs = new Z3_ast[n];
	for (int i = 0; i < (int) n; i++) {
		std::string symbolStr = std::string(Z3_ast_to_string(ctx, args[i]));
		if (symbolStr.length() >= 11
				&& symbolStr.substr(0, 11) == "__cOnStStR_") {
			convertedFlag = 1;
			convertedArgs[i] = mk_str_value(t,
					convertInputTrickyConstStr(symbolStr).c_str());
		} else if (isConcatFunc(t, args[i]) &&
						(d == td->SubString ||
						d == td->Indexof ||
						d == td->Indexof2 ||
						d == td->LastIndexof ||
						d == td->StartsWith ||
						d == td->EndsWith ||
						d == td->ToLower ||
						d == td->ToUpper ||
						d == td->Replace ||
						d == td->ReplaceAll ||
						d == td->Contains ||
						d == td->CharAt ||
						d == td->RegexIn)) {
			Z3_ast tmpVar;
			if (concatMapping.find(args[i]) != concatMapping.end())
				tmpVar = concatMapping[args[i]];
			else {
				tmpVar = mk_internal_string_var(t);
				concatMapping[args[i]] = tmpVar;
				internalVarFunctionMap[node_to_stringOP(t, tmpVar)] = node_to_stringOP(t, args[i]);
			}
			rewrittenConstraints.emplace_back(Z3_mk_eq(ctx, tmpVar, args[i]));
			convertedArgs[i] = tmpVar;
			__debugPrint(logFile, "%d converted %s to %s\n", __LINE__, node_to_string(t, args[i]).c_str(), node_to_string(t, tmpVar).c_str());
		} else
			convertedArgs[i] = args[i];
	}

	for (int i = 0; i < (int)n; ++i)
		if (isConcatFunc(t, convertedArgs[i])){
			Z3_ast n1 = Z3_get_app_arg(ctx, Z3_to_app(ctx, convertedArgs[i]), 0);
			Z3_ast n2 = Z3_get_app_arg(ctx, Z3_to_app(ctx, convertedArgs[i]), 1);
			std::pair<Z3_ast, Z3_ast> concatArgs(n1, n2);
			if (concat_astNode_map.find(concatArgs) == concat_astNode_map.end()){
				Z3_ast tmp = mk_internal_string_var(t);
				encodedConstraints.push_back(Z3_mk_eq(ctx, tmp, convertedArgs[i]));
			}
			else {
				convertedArgs[i] = concat_astNode_map[concatArgs];
			}
		}

	//---------------------------------
	// reduce app: Concat
	//---------------------------------
	if (d == td->Concat) {
		__debugPrint(logFile, "%d Input: Concat(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());

		bool updated = false;
		Z3_ast tmp = mk_concat(t, convertedArgs[0], convertedArgs[1], updated);

		// update children map

		if (updated == false) {
			__debugPrint(logFile, "\nFalse update \n");
			delete[] convertedArgs;
			return Z3_FALSE;
		}

		children_Map[tmp].push_back(convertedArgs[0]);
		children_Map[tmp].push_back(convertedArgs[1]);
		encodedConstraints.emplace_back(tmp);
		*result = mk_and_fromVector(t, encodedConstraints);
		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t,
				tmp);
		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		return Z3_TRUE;
	}

	//---------------------------------
	// reduce app: Length
	//---------------------------------
	else if (d == td->Length) {
		__debugPrint(logFile, "%d Input: Length(%s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str());
		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		if (getNodeType(t, convertedArgs[0]) == my_Z3_ConstStr) {
			int size = getConstStrValue(t, convertedArgs[0]).size();
			*result = mk_int(ctx, size);
			delete[] convertedArgs;
			return Z3_TRUE;
		} else {
			lengthEnable = true;
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
		__debugPrint(logFile, "%d Input: Str2Reg(%s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str());

		if (!isConstStr(t, convertedArgs[0])) {
			printf(
					"> Error: the argument of Str2Reg function should be a constant string.\n");
			printf("         (Str2Reg %s)\n",
					Z3_ast_to_string(ctx, convertedArgs[0]));
			exit(0);
		}

		Z3_ast otherAssert = NULL;
		*result = reduce_str2regex(t, d, convertedArgs, otherAssert);
		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (otherAssert != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, otherAssert).c_str());
			Z3_assert_cnstr(ctx, otherAssert);
		}

		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: RegexConcat
	//------------------------------------------
	else if (d == td->RegexConcat) {
		__debugPrint(logFile, "%d Input: RegexConcat(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());
		Z3_ast otherAssert = NULL;
		Z3_ast tmpRes = reduce_regexConcat(t, convertedArgs, otherAssert);
		delete[] convertedArgs;

		if (tmpRes != NULL)
			__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, tmpRes).c_str());

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
		__debugPrint(logFile, "%d Input: RegexIn(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());
		Z3_ast otherAssert = NULL;
		Z3_ast tmpRes = NULL;
		tmpRes = reduce_regexIn(t, convertedArgs, otherAssert);

		delete[] convertedArgs;

		if (tmpRes != NULL) {
			if (otherAssert != NULL) {
				rewrittenConstraints.emplace_back(otherAssert);
			}
			if (rewrittenConstraints.size() > 0)
				Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
			*result = tmpRes;

			__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, tmpRes).c_str());
			printZ3Node(t, tmpRes);
			if (otherAssert != NULL) {
				__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, otherAssert).c_str());
			}
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}

	//------------------------------------------
	// Reduce app: RegexStar
	//------------------------------------------
	else if (d == td->RegexStar) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: RegexStar(%s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str());

		*result = reduce_regexStar(t, convertedArgs, breakDownAst);
		delete[] convertedArgs;

		if (*result != NULL) {
			__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
			if (breakDownAst != NULL) {
				__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
				Z3_assert_cnstr(ctx, breakDownAst);
			}
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}
	//------------------------------------------
	// Reduce app: RegexPlus
	//------------------------------------------
	else if (d == td->RegexPlus) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: RegexPlus(%s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str());

		*result = reduce_regexPlus(t, convertedArgs, breakDownAst);
		delete[] convertedArgs;

		if (*result != NULL) {
			__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
			if (breakDownAst != NULL) {
				__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
				Z3_assert_cnstr(ctx, breakDownAst);
			}
			return Z3_TRUE;
		}
		return Z3_FALSE;
	}

	//------------------------------------------
	// Reduce app: GrammarIn
	//------------------------------------------
	else if (d == td->GrammarIn) {
		Z3_ast breakDownAst = NULL;
		Z3_ast tmpRes = NULL;
		tmpRes = reduce_grammarIn(t, convertedArgs, breakDownAst);
		__debugPrint(logFile, "%d Input: GrammarIn(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());
		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
		}

		delete[] convertedArgs;

		if (tmpRes != NULL) {
			if (breakDownAst != NULL) {
				Z3_assert_cnstr(ctx, breakDownAst);
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
		__debugPrint(logFile, "%d Input: SubString(%s, %s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str(), node_to_string(t, convertedArgs[2]).c_str());
		encodedConstraints.emplace_back(reduce_subStr(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);
		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t,
				mk_ternary_app(ctx, td->SubString, convertedArgs[0],
						convertedArgs[1], convertedArgs[2]));

		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Contains
	//------------------------------------------
	else if (d == td->Contains) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: Contains(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());

		encodedConstraints.emplace_back(reduce_contains(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);
		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_binary_app(ctx, td->Contains, convertedArgs[0], convertedArgs[1]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}
		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: CharAt
	//------------------------------------------
	else if (d == td->CharAt) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: convertedArgs(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());

		encodedConstraints.emplace_back(reduce_charAt(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_binary_app(ctx, td->CharAt, convertedArgs[0], convertedArgs[1]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Indexof
	//------------------------------------------
	else if (d == td->Indexof) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: Indexof(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());

		encodedConstraints.emplace_back(reduce_indexof(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_binary_app(ctx, td->Indexof, convertedArgs[0], convertedArgs[1]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Indexof
	//------------------------------------------
	else if (d == td->Indexof2) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: Indexof2(%s, %s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str(), node_to_string(t, convertedArgs[2]).c_str());

		encodedConstraints.emplace_back(reduce_indexof2(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_ternary_app(ctx, td->Indexof2, convertedArgs[0],	convertedArgs[1], convertedArgs[2]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: LastIndexof
	//------------------------------------------
	else if (d == td->LastIndexof) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: LastIndexof(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());

		encodedConstraints.emplace_back(reduce_lastindexof(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_binary_app(ctx, td->LastIndexof, convertedArgs[0], convertedArgs[1]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: EndsWith
	//------------------------------------------
	else if (d == td->EndsWith) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: EndsWith(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());
		Z3_ast tmp;
		switch (config.languageVersion) {
		case 20:
			break;
		case 25:
		case 26:
			/* swap args */
			tmp = convertedArgs[0];
			convertedArgs[0] = convertedArgs[1];
			convertedArgs[1] = tmp;
			break;
		default:
			assert(false);
			break;
		}

		encodedConstraints.emplace_back(reduce_endswith(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_binary_app(ctx, td->EndsWith, convertedArgs[0], convertedArgs[1]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: StartsWith
	//------------------------------------------
	else if (d == td->StartsWith) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: StartsWith(%s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str());

		Z3_ast tmp;
		switch (config.languageVersion) {
		case 20:
			break;
		case 25:
		case 26:
			/* swap args */
			tmp = convertedArgs[0];
			convertedArgs[0] = convertedArgs[1];
			convertedArgs[1] = tmp;
			break;
		default:
			assert(false);
			break;
		}

		encodedConstraints.emplace_back(reduce_startswith(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);
		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_binary_app(ctx, td->StartsWith, convertedArgs[0],	convertedArgs[1]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}
		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;
		return Z3_TRUE;
	}

	//------------------------------------------
	// Reduce app: Replace
	//------------------------------------------
	else if (d == td->Replace) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: Replace(%s, %s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str(), node_to_string(t, convertedArgs[2]).c_str());

		encodedConstraints.emplace_back(reduce_replace(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);
		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_ternary_app(ctx, td->Replace, convertedArgs[0], convertedArgs[1], convertedArgs[2]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;

		return Z3_TRUE;
	}
	//------------------------------------------
	// Reduce app: ReplaceAll
	//------------------------------------------
	else if (d == td->ReplaceAll) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: ReplaceAll(%s, %s, %s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str(), node_to_string(t, convertedArgs[1]).c_str(), node_to_string(t, convertedArgs[2]).c_str());

		encodedConstraints.emplace_back(reduce_replaceAll(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_ternary_app(ctx, td->ReplaceAll, convertedArgs[0], convertedArgs[1], convertedArgs[2]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;

		return Z3_TRUE;
	} else if (d == td->ToLower) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: ToLower(%s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str());

		encodedConstraints.emplace_back(reduce_toLower(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t, mk_unary_app(ctx, td->ToLower, convertedArgs[0]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		if (rewrittenConstraints.size() > 0)
			Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;

		return Z3_TRUE;
	} else if (d == td->ToUpper) {
		Z3_ast breakDownAst = NULL;
		__debugPrint(logFile, "%d Input: ToUpper(%s)\n", __LINE__, node_to_string(t, convertedArgs[0]).c_str());

		encodedConstraints.emplace_back(reduce_toUpper(t, convertedArgs, breakDownAst));
		*result = mk_and_fromVector(t, encodedConstraints);

		internalVarFunctionMap[node_to_stringOP(t, *result)] = node_to_stringOP(t,	mk_unary_app(ctx, td->ToUpper, convertedArgs[0]));

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());
		if (breakDownAst != NULL) {
			__debugPrint(logFile, ">> %d Add %s\n", __LINE__, node_to_string(t, breakDownAst).c_str());
			rewrittenConstraints.emplace_back(breakDownAst);
		}

		Z3_assert_cnstr(ctx, mk_and_fromVector(t, rewrittenConstraints));
		delete[] convertedArgs;

		return Z3_TRUE;
	} else if (d == td->RegexAll) {

	} else if (d == td->RegexAllChar) {

	} else if (d == td->RegexNone) {

	} else if (d == td->AutomataDef) {
	}

	if (convertedFlag == 1) {
		*result = Z3_mk_app(ctx, d, n, convertedArgs);

		__debugPrint(logFile, ">> %d %s\n", __LINE__, node_to_string(t, *result).c_str());

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
	/* write to file */
	std::string tmp = createEqualConstraint(node_to_string(t, s1),
			node_to_string(t, s2));
	if (config.printingConstraints)
		if (tmp.find("__cOnStStR_") == std::string::npos
				&& !isNonDetAutomatonFunc(t, s1)
				&& !isNonDetAutomatonFunc(t, s2)
				&& tmp.find("$$") != std::string::npos)
			constraintSet.stringConstraints.emplace(tmp);

	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__,
			tmp.c_str());

	if (tmp.find("__cOnStStR_") == std::string::npos
			&& setOfEqualities.find(tmp) == setOfEqualities.end()
			&& !isNonDetAutomatonFunc(t, s1) && !isNonDetAutomatonFunc(t, s2)) {
		appendToFile(tmp);
		setOfEqualities.emplace(tmp);
	}

	if (!(isStrVariable(t, s1)) && !isStrVariable(t, s2)) {
		std::string tmp01 = Z3_ast_to_string(ctx, s1);
		std::string tmp02 = Z3_ast_to_string(ctx, s2);
		if (tmp01.find(config.languageMap[CHARAT]) != std::string::npos
				|| tmp02.find(config.languageMap[CHARAT]) != std::string::npos) {
			if (!isConstStr(t, s1) && isConstStr(t, s2)) {
				throw std::runtime_error(
						"CharAt function accepts a const letter only!");
			}
		} else if (isConcatFunc(t, s1) && isConcatFunc(t, s2)) {
			std::vector<Z3_ast> list;
			Z3_ast tmp = mk_internal_string_var(t);
			list.emplace_back(Z3_mk_eq(ctx, tmp, s1));
			list.emplace_back(Z3_mk_eq(ctx, tmp, s2));
			*r = mk_and_fromVector(t, list);
			return Z3_TRUE;
			throw std::runtime_error(
								"One side of equality must be a string variable! The error is at:"
										+ tmp01 + " = " + tmp02);
		}

	}

	AutomatonStringData * td = (AutomatonStringData*) Z3_theory_get_ext_data(t);
	std::string s1_str = customizeString(node_to_string(t, s1));
	std::string s2_str = customizeString(node_to_string(t, s2));

	__debugPrint(logFile, "\n%d *** %s ***: %s = %s\n", __LINE__, __FUNCTION__, s1_str.c_str(), s2_str.c_str());
	Z3_ast s1_new = s1;
	Z3_ast s2_new = s2;

	int len01 = -1, len02 = -1;
	// Convert the tricky "string" representation to string constant
	if (s1_str.length() >= 11 && s1_str.substr(0, 11) == "__cOnStStR_") {
		std::string s = convertInputTrickyConstStr(s1_str);
		s1_new = mk_str_value(t, s.c_str());
		len01 = s.length();

		s1_new = mk_unary_app(ctx, td->AutomataDef, s1_new);
		addAxiom(t,
				Z3_mk_eq(ctx, mk_length(t, s1_new), mk_int(ctx, s.length())),
				__LINE__, true);
	} else if (isConstStr(t, s1)) {
		s1_new = mk_str_value(t, s1_str.c_str());
		len01 = s1_str.length();

		s1_new = mk_unary_app(ctx, td->AutomataDef, s1_new);
		addAxiom(t,
				Z3_mk_eq(ctx, mk_length(t, s1_new),
						mk_int(ctx, s1_str.length())), __LINE__, true);
	}

	if (s2_str.length() >= 11 && s2_str.substr(0, 11) == "__cOnStStR_") {
		std::string s = convertInputTrickyConstStr(s2_str);
		s2_new = mk_str_value(t, s.c_str());
		len02 = s.length();

		s2_new = mk_unary_app(ctx, td->AutomataDef, s2_new);
		addAxiom(t,
				Z3_mk_eq(ctx, mk_length(t, s2_new), mk_int(ctx, s.length())),
				__LINE__, true);
	} else if (isConstStr(t, s2)) {
		s2_new = mk_str_value(t, s2_str.c_str());
		len02 = s2_str.length();

		s2_new = mk_unary_app(ctx, td->AutomataDef, s2_new);
		addAxiom(t,
				Z3_mk_eq(ctx, mk_length(t, s2_new),
						mk_int(ctx, s2_str.length())), __LINE__, true);
	}
	// parikh and length constraints
	std::vector<Z3_ast> list00;

#ifdef ARITH
	// do not need to insert axiom for concat because concat does itself
	if (!isConcatFunc(t, s1)) {
		std::vector<Z3_ast> list01 = basicArithConstraints_forNode_simple(t,
				s1);
		list00.insert(list00.end(), list01.begin(), list01.end());
	}
	if (!isConcatFunc(t, s2)) {
		std::vector<Z3_ast> list01 = basicArithConstraints_forNode_simple(t,
				s2);
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
		list00.push_back(
				Z3_mk_implies(ctx, eqNode,
						Z3_mk_eq(ctx, mk_length(t, s2_new),
								mk_int(ctx, len01))));

	if (len02 >= 0)
		list00.push_back(
				Z3_mk_implies(ctx, eqNode,
						Z3_mk_eq(ctx, mk_length(t, s1_new),
								mk_int(ctx, len02))));

	if (!(len01 >= 0 && len02 >= 0)) {
		Z3_ast lengConstraint = Z3_mk_eq(ctx, mk_length(t, s1_new),
				mk_length(t, s2_new));
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

