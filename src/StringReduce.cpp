#include "StringTheory.h"

extern int nondeterministicCounter;
extern bool havingGrmConstraints;
extern std::map<Z3_ast, Z3_ast> grm_astNode_map;
extern std::map<std::pair<Z3_ast, Z3_ast>, Z3_ast> containPairBoolMap;

extern std::map<std::string, std::pair<std::string, std::string>> indexOfStrMap;
extern std::map<std::string, std::pair<std::string, std::string>> lastIndexOfStrMap;
extern std::map<std::string, std::string> endsWithStrMap;
extern std::map<std::string, std::string> startsWithStrMap;
extern std::map<std::string, std::string> replaceStrMap;

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
		node02 = "\"" + customizeString(customizeString(Z3_ast_to_string(ctx, tmp))) + "\"";
	}
	else if (isConstStr(t, args[1])){
		node02 = "\"" + customizeString(Z3_ast_to_string(ctx, args[1])) + "\"";
	}
	else
		node02 = Z3_ast_to_string(ctx, args[1]);

	if (name == td->Replace) {
		if (isDetAutomatonFunc(t, args[2])) {
			Z3_ast tmp = Z3_get_app_arg(ctx, Z3_to_app(ctx, args[2]), 0);
			node03 = "\"" + customizeString(customizeString(Z3_ast_to_string(ctx, tmp))) + "\"";
		}
		else if (isConstStr(t, args[2])){
			node03 = "\"" + customizeString(Z3_ast_to_string(ctx, args[2])) + "\"";
		}
		else
			node03 = Z3_ast_to_string(ctx, args[2]);
	}

	if (name == td->LastIndexof)
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
	else
		return NULL;
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
		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);
		Z3_ast indexAst = mk_internal_int_var(t);

		// condAst = Contains(args[0], args[1])
		Z3_ast condAst = registerContain(t, args[0], args[1]);

		std::string boolVar = Z3_ast_to_string(ctx, condAst);

		// -----------------------
		bool update;
		// true branch
		std::vector<Z3_ast> thenItems;
		//  args[0] = x1 . args[1] . x2
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update)));
		//  indexAst = |x1|
		thenItems.push_back(Z3_mk_eq(ctx, indexAst, mk_length(t, x1)));

		indexOfStrMap[nodeName] = std::make_pair(boolVar, "len_" + std::string(Z3_ast_to_string(ctx, x1)));

		//     args[0]  = x3 . x4
		//  /\ |x3| = |x1| + |args[1]| - 1
		//  /\ ! contains(x3, args[1])
		Z3_ast x3 = mk_internal_string_var(t);
		Z3_ast x4 = mk_internal_string_var(t);
		Z3_ast tmpLenItems[3] = { indexAst, mk_length(t, args[1]), mk_int(ctx, -1) };
		Z3_ast tmpLen = Z3_mk_add(ctx, 3, tmpLenItems);
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
		thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
		thenItems.push_back(Z3_mk_not(ctx, mk_contains(t, x3, args[1])));

		// -----------------------
		// false branch
		Z3_ast elseBranch = Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1));

		breakdownAssert = Z3_mk_ite(ctx, condAst, mk_and_fromVector(t, thenItems), elseBranch);
		return indexAst;
	}
}


///*
// *
// */
//Z3_ast reduce_indexof2(Z3_theory t, Z3_ast const args[], Z3_ast & breakdownAssert) {
//  Z3_context ctx = Z3_theory_get_context(t);
//  if (getNodeType(t, args[0]) == my_Z3_ConstStr && getNodeType(t, args[1]) == my_Z3_ConstStr && getNodeType(t, args[2]) == my_Z3_Num) {
//    std::string arg0 = getConstStrValue(t, args[0]);
//    std::string arg1 = getConstStrValue(t, args[1]);
//    int arg2Int = getConstIntValue(t, args[2]);
//    if (arg2Int >= (int)arg0.length()) {
//      return mk_int(ctx, -1);
//    } else if (arg2Int < 0) {
//      int index = arg0.find(arg1);
//      return mk_int(ctx, index);
//    } else {
//      std::string suffixStr = arg0.substr(arg2Int, arg0.length() - arg2Int);
//      if (suffixStr.find(arg1) != std::string::npos) {
//        int index = suffixStr.find(arg1) + arg2Int;
//        return mk_int(ctx, index);
//      } else {
//        return mk_int(ctx, -1);
//      }
//    }
//  } else {
//    // -------------------------------------------------------------------------------
//    //   if (arg[2] >= length(arg[0]))                          // ite2
//    //     resAst = -1
//    //   else
//    //     args[0] = prefix . suffix
//    //     /\ indexAst = indexof(suffix, arg[1])
//    //     /\ args[2] = len(prefix)
//    //     /\ if (indexAst == -1)  resAst = indexAst            // ite3
//    //        else   resAst = args[2] + indexAst
//    // -------------------------------------------------------------------------------
//    PATheoryData * td = (PATheoryData*) Z3_theory_get_ext_data(t);
//    Z3_ast resAst = my_mk_internal_int_var(t);
//    Z3_ast indexAst = my_mk_internal_int_var(t);
//    Z3_ast prefix = my_mk_internal_string_var(t);
//    Z3_ast suffix = my_mk_internal_string_var(t);
//    Z3_ast prefixLen = mk_length(t, prefix);
//    Z3_ast zeroAst = mk_int(ctx, 0);
//    Z3_ast negOneAst = mk_int(ctx, -1);
//
//    Z3_ast ite3 = Z3_mk_ite(ctx, Z3_mk_eq(ctx, indexAst, negOneAst),
//                                 Z3_mk_eq(ctx, resAst, negOneAst),
//                                 Z3_mk_eq(ctx, resAst, mk_2_add(t, args[2], indexAst))
//                           );
//    Z3_ast ite2ElseItems[4];
//    ite2ElseItems[0] = Z3_mk_eq(ctx, args[0], mk_concat(t, prefix, suffix));
//    ite2ElseItems[1] = Z3_mk_eq(ctx, indexAst, mk_2_arg_app(ctx, td->Indexof, suffix, args[1]));
//    ite2ElseItems[2] = Z3_mk_eq(ctx, args[2], prefixLen);
//    ite2ElseItems[3] = ite3;
//    Z3_ast ite2Else = Z3_mk_and(ctx, 4, ite2ElseItems);
//
//    Z3_ast ite2 = Z3_mk_ite(ctx, Z3_mk_ge(ctx, args[2], mk_length(t, args[0])),
//                                 Z3_mk_eq(ctx, resAst, negOneAst),
//                                 ite2Else
//                           );
//
//    Z3_ast ite1 = Z3_mk_ite(ctx, Z3_mk_lt(ctx, args[2], zeroAst),
//                                 Z3_mk_eq(ctx, resAst, mk_2_arg_app(ctx, td->Indexof, args[0], args[1])),
//                                 ite2
//                            );
//    breakdownAssert = ite1;
//    return resAst;
//  }
//}

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
		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);
		Z3_ast indexAst = mk_internal_int_var(t);
		std::vector<Z3_ast> items;

		bool update;

		// args[0] = x1 . args[1] . x2
		Z3_ast eq1 = Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update));
		Z3_ast arg0HasArg1 = registerContain(t, args[0], args[1]);  // arg0HasArg1 = Contains(args[0], args[1])
		items.push_back(Z3_mk_eq(ctx, arg0HasArg1, eq1));

		Z3_ast condAst = arg0HasArg1;
		std::string boolVar = Z3_ast_to_string(ctx, condAst);
		//----------------------------
		// true branch
		std::vector<Z3_ast> thenItems;
		thenItems.push_back(Z3_mk_ge(ctx, indexAst, mk_int(ctx, 0)));
		//  args[0] = x1 . args[1] . x2
		//  x1 doesn't contain args[1]
		thenItems.push_back(Z3_mk_not(ctx, mk_contains(t, x2, args[1])));
		thenItems.push_back(Z3_mk_eq(ctx, indexAst, mk_length(t, x1)));

		if (isDetAutomatonFunc(t, args[1]) || isConstStr(t, args[1]))
			lastIndexOfStrMap[nodeName] = std::make_pair(boolVar, "len_" + std::string(Z3_ast_to_string(ctx, x1)));
		else
			lastIndexOfStrMap[nodeName] = std::make_pair(boolVar, "len_" + std::string(Z3_ast_to_string(ctx, x1)));
		bool canSkip = false;
		if (getNodeType(t, args[1]) == my_Z3_ConstStr) {
			std::string arg1Str = getConstStrValue(t, args[1]);
			if (arg1Str.length() == 1) {
				canSkip = true;
			}
		}

		if (!canSkip) {
			// args[0]  = x3 . x4 /\ |x3| = |x1| + 1 /\ ! contains(x4, args[1])
			Z3_ast x3 = mk_internal_string_var(t);
			Z3_ast x4 = mk_internal_string_var(t);
			Z3_ast tmpLenItems[2] = { indexAst, mk_int(ctx, 1) };
			Z3_ast tmpLen = Z3_mk_add(ctx, 2, tmpLenItems);
			thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
			thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
			thenItems.push_back(Z3_mk_not(ctx, mk_contains(t, x4, args[1])));
		}
		//----------------------------
		// else branch
		std::vector<Z3_ast> elseItems;
		elseItems.push_back(Z3_mk_eq(ctx, indexAst, mk_int(ctx, -1)));

		items.push_back(Z3_mk_ite(ctx, condAst, mk_and_fromVector(t, thenItems), mk_and_fromVector(t, elseItems)));

		breakdownAssert = mk_and_fromVector(t, items);

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
		Z3_ast x1 = mk_internal_string_var(t);
		Z3_ast x2 = mk_internal_string_var(t);
		Z3_ast i1 = mk_internal_int_var(t);
		Z3_ast result = mk_internal_string_var(t);

		// condAst = Contains(args[0], args[1])
		Z3_ast condAst = registerContain(t, args[0], args[1]);
		std::string boolName = Z3_ast_to_string(ctx, condAst);
		replaceStrMap[nodeName] = boolName;

		// -----------------------
		// true branch
		std::vector<Z3_ast> thenItems;
		//  args[0] = x1 . args[1] . x2
		bool update = true;
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x1, mk_concat(t, args[1], x2, update), update)));
		//  i1 = |x1|
		thenItems.push_back(Z3_mk_eq(ctx, i1, mk_length(t, x1)));
		//  args[0]  = x3 . x4 /\ |x3| = |x1| + |args[1]| - 1 /\ ! contains(x3, args[1])
		Z3_ast x3 = mk_internal_string_var(t);
		Z3_ast x4 = mk_internal_string_var(t);
		Z3_ast tmpLenItems[3] = {i1, mk_length(t, args[1]), mk_int(ctx, -1) };
		Z3_ast tmpLen = Z3_mk_add(ctx, 3, tmpLenItems);
		thenItems.push_back(Z3_mk_eq(ctx, args[0], mk_concat(t, x3, x4, update)));
		thenItems.push_back(Z3_mk_eq(ctx, mk_length(t, x3), tmpLen));
		thenItems.push_back(Z3_mk_not(ctx, mk_contains(t, x3, args[1])));
		thenItems.push_back(Z3_mk_eq(ctx, result, mk_concat(t, x1, mk_concat(t, args[2], x2, update), update)));
		// -----------------------
		// false branch
		Z3_ast elseBranch = Z3_mk_eq(ctx, result, args[0]);

		breakdownAssert = Z3_mk_ite(ctx, condAst, mk_and_fromVector(t, thenItems), elseBranch);
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

	Z3_ast ts0ContainsTs1 = registerContain(t, args[0], ts1);

	bool update;

	int value_prefix = getConstIntValue(t, args[1]);

	if (value_prefix != 0 ) {
		Z3_ast and_item[4];
		and_item[0] = ts0ContainsTs1;
		and_item[1] = Z3_mk_eq(ctx, args[0], mk_concat(t, ts0, mk_concat(t, ts1, ts2, update), update));
		and_item[2] = Z3_mk_eq(ctx, args[1], mk_length(t, ts0));
		and_item[3] = Z3_mk_eq(ctx, args[2], mk_length(t, ts1));

		breakdownAssert = Z3_mk_and(ctx, 4, and_item);
	}
	else {
		// substring from 0
		Z3_ast and_item[3];
		and_item[0] = ts0ContainsTs1;
		and_item[1] = Z3_mk_eq(ctx, args[0], mk_concat(t, ts1, ts2, update));
		and_item[2] = Z3_mk_eq(ctx, args[2], mk_length(t, ts1));

		breakdownAssert = Z3_mk_and(ctx, 3, and_item);
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
		list00.push_back(Z3_mk_eq(ctx, mk_length(t, s2_new), mk_int(ctx, len01)));

	if (len02 >= 0)
		list00.push_back(Z3_mk_eq(ctx, mk_length(t, s1_new), mk_int(ctx, len02)));

	if (!(len01 >= 0 && len02 >= 0)) {
		std::vector<Z3_ast> tmpVector =	basicArithConstraints_forEqual(t, s1_new, s2_new);
		list00.insert(list00.end(), tmpVector.begin(), tmpVector.end());
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


