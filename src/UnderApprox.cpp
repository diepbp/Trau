/*
 * UnderApprox.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */

/*
 * UnderApprox.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#include "UnderApprox.h"

bool trivialUnsat = false;

void updatePossibleArrangements(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		std::vector<Arrangment> tmp,
		std::vector<Arrangment> &possibleCases) {
	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (tmp[i].isPossibleArrangement(lhs_elements, rhs_elements))
			possibleCases.push_back(tmp[i]);
}

void updatePossibleArrangements(
		std::vector<Arrangment> tmp,
		std::vector<Arrangment> &possibleCases) {
	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (tmp[i].isPossibleArrangement())
			possibleCases.push_back(tmp[i]);
}

/*
 *
 */
bool isRegexStr(std::string str){
	return str.find('*') != std::string::npos || str.find('+') != std::string::npos;
}

/*
 * First base case
 */
void handleCase_0_0(
		std::map<std::pair<int, int>, std::vector<Arrangment>> &arrangements,
		bool usingFilter){
	std::vector<int> tmpLeft;
	std::vector<int> tmpRight;

	/* left = right */
	tmpLeft.push_back(0);
	tmpRight.push_back(0);
	arrangements[std::make_pair(0, 0)].push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
}

/*
 * First base case
 */
void handleCase_0_0_general(){
	std::vector<int> tmpLeft;
	std::vector<int> tmpRight;

	if (arrangements[std::make_pair(0, 0)].size() == 0) {
		/* left = right */
		tmpLeft.push_back(0);
		tmpRight.push_back(0);
		arrangements[std::make_pair(0, 0)].push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
	}
}

/*
 * 2nd base case (sum lhs...) = [0]
 */
void handleCase_n_0(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		bool usingFilter){

	/* right always has SUMFLAT */
	std::vector<int> tmpRight;
	tmpRight.push_back(SUMFLAT);

	/* left has i number of 0 */
	std::vector<int> tmpLeft;
	tmpLeft.push_back(0);

	for (unsigned int i = 1; i < lhs_elements.size(); ++i) {
		tmpLeft.push_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

		/* update */
		if (usingFilter == true) {
			std::vector<Arrangment> possibleCases;
			updatePossibleArrangements(lhs_elements, rhs_elements, tmp04, possibleCases);

			arrangements[std::make_pair(i, 0)] = possibleCases;
		}
		else {
			/* add directly without checking */
			arrangements[std::make_pair(i, 0)] = tmp04;
		}
	}
}

/*
 * 2nd base case (sum lhs...) = [0]
 */
void handleCase_n_0_general(
		int lhs,
		int rhs){

	/* right always has SUMFLAT */
	std::vector<int> tmpRight;
	tmpRight.push_back(SUMFLAT);

	/* left has i number of 0 */
	std::vector<int> tmpLeft;
	tmpLeft.push_back(0);

	for (int i = 1; i < lhs; ++i) {
		tmpLeft.push_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

		/* add directly without checking */
		if (arrangements[std::make_pair(i, 0)].size() == 0) {
			arrangements[std::make_pair(i, 0)] = tmp04;
		}
	}
}

/*
 * 2nd base case [0] = (sum rhs...)
 */
void handleCase_0_n(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		bool usingFilter){

	/* left always has SUMFLAT */
	std::vector<int> tmpLeft;
	tmpLeft.push_back(SUMFLAT);

	/* right has i number of 0 */
	std::vector<int> tmpRight;
	tmpRight.push_back(0);

	for (unsigned int i = 1 ; i < rhs_elements.size(); ++i) {
		tmpRight.push_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

		/* update */
		if (usingFilter == true) {
			std::vector<Arrangment> possibleCases;
			updatePossibleArrangements(lhs_elements, rhs_elements, tmp04, possibleCases);

			arrangements[std::make_pair(0, i)] = possibleCases;
		}
		else {
			arrangements[std::make_pair(0, i)] = tmp04;
		}
	}
}

/*
 * 2nd base case [0] = (sum rhs...)
 */
void handleCase_0_n_general(
		int lhs,
		int rhs){

	/* left always has SUMFLAT */
	std::vector<int> tmpLeft;
	tmpLeft.push_back(SUMFLAT);

	/* right has i number of 0 */
	std::vector<int> tmpRight;
	tmpRight.push_back(0);

	for (int i = 1 ; i < rhs; ++i){
			tmpRight.push_back(0);

			std::vector<Arrangment> tmp04;
			tmp04.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

			/* update */
			/* add directly without checking */
			if (arrangements[std::make_pair(0, i)].size() == 0) {
				arrangements[std::make_pair(0, i)] = tmp04;
			}
		}
}

/*
 * general case
 */
void handleCase_n_n(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		bool usingFilter){
	for (unsigned int i = 0 ; i < lhs_elements.size(); ++i)
		for (unsigned int j = 0; j < rhs_elements.size(); ++j)
			if (i != 0 && j != 0){

				/* 3.1 [i] = sum(k...j) */
				std::vector<Arrangment> tmp03;

				{
					/* [i] = sum (0..j) */
					std::vector<int> tmpLeft;
					for (unsigned int k = 0; k < i; ++k)
						tmpLeft.push_back(EMPTYFLAT);
					tmpLeft.push_back(SUMFLAT);

					std::vector<int> tmpRight;
					for (unsigned int k = 0 ; k <= j; ++k)
						tmpRight.push_back(i);
					tmp03.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
				}

				/* [i] = sum (k..j) */
				for (unsigned int k = 1; k < j; ++k) {
					std::vector<Arrangment> tmp03_ext = arrangements[std::make_pair(i - 1, k - 1)];
					for (unsigned int t = 0; t < tmp03_ext.size(); ++t) {
						tmp03_ext[t].addLeft(SUMFLAT);
						for (unsigned int tt = k; tt <= j; ++tt)
							tmp03_ext[t].addRight(i);
					}

					tmp03.insert(tmp03.end(), tmp03_ext.begin(), tmp03_ext.end());
				}

				/* 3.2 right = sum(...left) */
				std::vector<Arrangment> tmp04;

				/* sum (k..i)  = [j] */
				for (unsigned int k = 1; k < i; ++k) {
					std::vector<Arrangment> tmp04_ext = arrangements[std::make_pair(k - 1, j - 1)];
					for (unsigned int t = 0; t < tmp04_ext.size(); ++t) {
						tmp04_ext[t].addRight(SUMFLAT);
						for (unsigned int tt = k; tt <= i; ++tt)
							tmp04_ext[t].addLeft(j);
					}

					tmp04.insert(tmp04.end(), tmp04_ext.begin(), tmp04_ext.end());
				}

				{
					/* sum (0..i)  = [j] */
					std::vector<int> tmpLeft;
					for (unsigned int k = 0 ; k <= i; ++k)
						tmpLeft.push_back(j);

					std::vector<int> tmpRight;
					for (unsigned int k = 0; k < j; ++k)
						tmpRight.push_back(EMPTYFLAT);
					tmpRight.push_back(SUMFLAT);
					tmp04.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
				}

				/* fourth case: left = right */
				std::vector<Arrangment> tmp05 = arrangements[std::make_pair(i - 1, j - 1)];
				for (unsigned int k = 0; k < tmp05.size(); ++k) {
					tmp05[k].addRight(i);
					tmp05[k].addLeft(j);
				}

				/* update */
				if (usingFilter == true) {
					std::vector<Arrangment> possibleCases;
					updatePossibleArrangements(lhs_elements, rhs_elements, tmp03, possibleCases);
					updatePossibleArrangements(lhs_elements, rhs_elements, tmp04, possibleCases);
					updatePossibleArrangements(lhs_elements, rhs_elements, tmp05, possibleCases);

					arrangements[std::make_pair(i, j)] = possibleCases;
				}
				else {
					/* add directly */
					std::vector<Arrangment> possibleCases;
					possibleCases.insert(possibleCases.end(), tmp03.begin(), tmp03.end());
					possibleCases.insert(possibleCases.end(), tmp04.begin(), tmp04.end());
					possibleCases.insert(possibleCases.end(), tmp05.begin(), tmp05.end());
					arrangements[std::make_pair(i, j)] = possibleCases;
				}
			}
}

/*
 * general case
 */
void handleCase_n_n_general(
		int lhs,
		int rhs){

	for (int i = 0 ; i < lhs; ++i)
		for (int j = 0; j < rhs; ++j)
			if (arrangements.find(std::make_pair(i,j)) == arrangements.end()){
				// printf("%d ..>>> calculate (%d, %d)\n", __LINE__, i, j);
				/* 2.0 [i] = empty */
				std::vector<Arrangment> tmp01_ext = arrangements[std::make_pair(i - 1, j)];
				for (unsigned int t = 0 ; t < tmp01_ext.size(); ++t) {
					tmp01_ext[t].addLeft(EMPTYFLAT);
				}

				/* 2.1 [j] = empty */
				std::vector<Arrangment> tmp02_ext = arrangements[std::make_pair(i, j - 1)];
				for (unsigned int t = 0 ; t < tmp02_ext.size(); ++t) {
					tmp02_ext[t].addRight(EMPTYFLAT);
				}

				/* 3.1 [i] = sum(k...j) */
				std::vector<Arrangment> tmp03;

				{
					/* [i] = sum (0..j) */
					std::vector<int> tmpLeft;
					for (int k = 0; k < i; ++k)
						tmpLeft.push_back(EMPTYFLAT);
					tmpLeft.push_back(SUMFLAT);

					std::vector<int> tmpRight;
					for (int k = 0 ; k <= j; ++k)
						tmpRight.push_back(i);

					assert ((int)tmpLeft.size() == i + 1);
					assert ((int)tmpRight.size() == j + 1);
					tmp03.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
				}

				/* [i] = sum (k..j) */
				for (int k = 1; k < j; ++k) {
					std::vector<Arrangment> tmp03_ext = arrangements[std::make_pair(i - 1, k - 1)];
					for (unsigned int t = 0; t < tmp03_ext.size(); ++t) {

						tmp03_ext[t].addLeft(SUMFLAT);
						for (int tt = k; tt <= j; ++tt)
							tmp03_ext[t].addRight(i);


						assert ((int)tmp03_ext[t].left_arr.size() == i + 1);
						assert ((int)tmp03_ext[t].right_arr.size() == j + 1);
					}

					tmp03.insert(tmp03.end(), tmp03_ext.begin(), tmp03_ext.end());
				}

				/* 3.2 right = sum(...left) */
				std::vector<Arrangment> tmp04;

				/* sum (k..i)  = [j] */
				for (int k = 1; k < i; ++k) {
					std::vector<Arrangment> tmp04_ext = arrangements[std::make_pair(k - 1, j - 1)];
					for (unsigned int t = 0; t < tmp04_ext.size(); ++t) {
						tmp04_ext[t].addRight(SUMFLAT);
						for (int tt = k; tt <= i; ++tt)
							tmp04_ext[t].addLeft(j);

						assert ((int)tmp04_ext[t].left_arr.size() == i + 1);
						assert ((int)tmp04_ext[t].right_arr.size() == j + 1);
					}

					tmp04.insert(tmp04.end(), tmp04_ext.begin(), tmp04_ext.end());
				}

				{
					/* sum (0..i)  = [j] */
					std::vector<int> tmpLeft;
					for (int k = 0 ; k <= i; ++k)
						tmpLeft.push_back(j);

					std::vector<int> tmpRight;
					for (int k = 0; k < j; ++k)
						tmpRight.push_back(EMPTYFLAT);
					tmpRight.push_back(SUMFLAT);

					assert ((int)tmpLeft.size() == i + 1);
					assert ((int)tmpRight.size() == j + 1);
					tmp04.push_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
				}

				/* fourth case: left = right */
				std::vector<Arrangment> tmp05 = arrangements[std::make_pair(i - 1, j - 1)];
				for (unsigned int k = 0; k < tmp05.size(); ++k) {
					tmp05[k].addRight(i);
					tmp05[k].addLeft(j);
				}

				/* update */
				/* add directly */
				std::vector<Arrangment> possibleCases;
//				possibleCases.insert(possibleCases.end(), tmp01_ext.begin(), tmp01_ext.end());
//				possibleCases.insert(possibleCases.end(), tmp02_ext.begin(), tmp02_ext.end());
				possibleCases.insert(possibleCases.end(), tmp03.begin(), tmp03.end());
				possibleCases.insert(possibleCases.end(), tmp04.begin(), tmp04.end());
				possibleCases.insert(possibleCases.end(), tmp05.begin(), tmp05.end());

//				std::vector<Arrangment> possibleCases_filtered;
//				updatePossibleArrangements(possibleCases, possibleCases_filtered);
//				arrangements[std::make_pair(i, j)] = possibleCases_filtered;
				arrangements[std::make_pair(i, j)] = possibleCases;
			}
}

/*
 * lhs: size of the lhs
 * rhs: size of the rhs
 * lhs_elements: elements of lhs
 * rhs_elements: elements of rhs
 *
 * Pre-Condition: x_i == 0 --> x_i+1 == 0
 *
 */
std::vector<std::string> collectAllPossibleArrangements(
		std::string lhs_str, std::string rhs_str,
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		std::map<std::string, int> &newVars){
	/* first base case */
	clock_t t;
	t = clock();

#if 1
	/* because arrangements are reusable, we use "general" functions */
	handleCase_0_0_general();

	/* second base case : first row and first column */
	handleCase_0_n_general(lhs_elements.size(), rhs_elements.size());
	handleCase_n_0_general(lhs_elements.size(), rhs_elements.size());

	/* general cases */
	handleCase_n_n_general(lhs_elements.size(), rhs_elements.size());

	/* because of "general" functions, we need to refine arrangements */
	std::vector<Arrangment> possibleCases;
	updatePossibleArrangements(lhs_elements, rhs_elements, arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)], possibleCases);
#else
	arrangements.clear();
	handleCase_0_0(arrangements);

	/* second base case : first row and first column */
	handleCase_0_n(lhs_elements, rhs_elements);
	handleCase_n_0(lhs_elements, rhs_elements);

	/* general cases */
	handleCase_n_n(lhs_elements, rhs_elements);
#endif
	t = clock() - t;

#ifdef PRINTTEST_UNDERAPPROX
	__debugPrint(logFile, "\n%d Calculating all possible cases: %.3f seconds, %ld cases.\n", __LINE__, ((float)t)/CLOCKS_PER_SEC, possibleCases.size());
#endif

	std::vector<std::string> cases;
#if 0
	/* 1 vs n, 1 vs 1, n vs 1 */
	for (int i = 0; i < arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)].size(); ++i) {
		std::string tmp = arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)][i].
				generateSMT(PMAX, lhs_str, rhs_str, lhs_elements, rhs_elements, connectedVariables, newVars);
		if (tmp.length() > 0) {
			cases.push_back(tmp);
		}
		else {
		}
	}
#else

	/* 1 vs n, 1 vs 1, n vs 1 */
	for (unsigned int i = 0; i < possibleCases.size(); ++i) {
		arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)][i].printArrangement("Checking case");
		possibleCases[i].constMap.clear();
		possibleCases[i].constMap.insert(constMap.begin(), constMap.end());
		std::string tmp = possibleCases[i].
				generateSMT(PMAX, lhs_str, rhs_str, lhs_elements, rhs_elements, connectedVariables, newVars);

		if (tmp.length() > 0) {
			cases.push_back(tmp);
			arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)][i].printArrangement("Correct case");
			__debugPrint(logFile, "%d %s\n", __LINE__, tmp.c_str());
		}
		else {
		}
	}
#endif
	return cases;

}

/*
 * define array for connected variable
 */
void create_constraints_array(std::vector<std::string> &defines, std::vector<std::string> &constraints){

	for (std::set<std::string>::iterator it = connectedVariables.begin(); it != connectedVariables.end(); ++it){
		defines.push_back("(declare-const arr_" + *it + " (Array Int Int))");
	}
}

/*
 * define array for connected variable
 */
void create_const_array(
		std::vector<std::string> &defines,
		std::vector<std::string> &constraints){

//	for (std::map<std::pair<std::string, std::string>, std::string>::iterator it = constMap.begin(); it != constMap.end(); ++it){
	for (std::map<std::string, std::string>::iterator it = constMap.begin(); it != constMap.end(); ++it){
		defines.push_back("(declare-const arr_" + it->second + " (Array Int Int))");
		if (!isRegexStr(it->first))
			for (unsigned int i = 0 ; i < it->first.length(); ++i) {
				constraints.push_back("(assert (= (select arr_" + it->second + " " + std::to_string(i) + ") " + std::to_string(it->first[i]) + "))");
			}
		else {
			std::string regexContent = parse_regex_content(it->first);
			for (unsigned int i = 0 ; i < regexContent.length(); ++i) {
				constraints.push_back("(assert (= (select arr_" + it->second + " " + std::to_string(i) + ") " + std::to_string(regexContent[i]) + "))");
			}
		}
	}
}

/*
 *
 */
/*
 *
 * (declare-const __regex_x Int)
 *
 * __regex_x >= 0
 *
 */
void create_constraints_RegexCnt(std::vector<std::string> &defines, std::vector<std::string> &constraints){
	for (int i = 0 ; i < regexCnt; ++i) {
		defines.push_back("(declare-const __regex_" + std::to_string(i) + " Int)");
		constraints.push_back("(assert (>= __regex_" + std::to_string(i) + " 0))");
	}
}

/*
 * var name -> define var
 * (declare-const len_const_0_0 Int)
 * (declare-const len_const_1_0 Int)
 *
 * const = sum(len_const_0_0)
 * len_const_0_0 >= 0
 *
 */
void create_constraints_const(std::vector<std::string> &defines, std::vector<std::string> &constraints){

	for (std::map<std::string, std::string>::iterator it = constMap.begin(); it != constMap.end(); ++it)
		if (!isRegexStr(it->first)){

			/* len_x = sum(len_x_i)*/
			std::string lenX = "";
			std::string varName = "len_" + it->second + "_";
			if ( it->first.length() <= SPLIT_UNDER_BOUND - 2) { /* -2 because of "xxxx" */
				defines.push_back("(declare-const len_" + it->second + "_" + "1 Int)");
				constraints.push_back("(assert (>= len_" + it->second + "_" + "1 0))");
				lenX = varName + "1 0";
			}
			else for (int i = 1; i <= QCONSTMAX; ++i) {
				defines.push_back("(declare-const len_" + it->second + "_" + std::to_string(i) + " Int)");
				constraints.push_back("(assert (>= len_" + it->second + "_" + std::to_string(i) + " 0))");
				lenX = lenX + varName + std::to_string(i) + " ";
			}

			/* (+ sum(len_x_i) */
			if (QCONSTMAX > 1)
				lenX = "(+ " + lenX + ")";

			std::string lenName = std::to_string(it->first.length());
			/*(assert (= const (+ sum(len_x_i)))) */
			lenX = "(assert (= " + lenName + " " + lenX  + "))";

			constraints.push_back(lenX);
		}
		else {
			defines.push_back("(declare-const len_" + it->second + "_" + std::to_string(std::abs(REGEX_CODE)) + " Int)");
			constraints.push_back("(assert (>= len_" + it->second + "_" + std::to_string(std::abs(REGEX_CODE)) + " 0))");

			std::string regexContent = parse_regex_content(it->first);

			constraints.push_back("(assert (= (mod len_" + it->second + "_" + std::to_string(std::abs(REGEX_CODE)) +  " " + std::to_string(regexContent.length()) + ") 0))");
		}
}

/*
 * var name -> define var
 * (declare-const len_var_0 Int)
 * (declare-const len_var_0 Int)
 *
 * len_var = sum(len_var_0)
 * len_var_0 >= 0
 *
 */
void create_constraints_strVar(std::vector<std::string> &defines, std::vector<std::string> &constraints){
	for (std::set<std::string>::iterator it = allVariables.begin(); it != allVariables.end(); ++it){

		/* len_x = sum(len_x_i)*/
		std::string lenX = "";
		std::string varName = "len_" + *it + "_";
		for (int i = 0; i < QMAX; ++i) {
			defines.push_back("(declare-const len_" + *it + "_" + std::to_string(i) + " Int)");
			constraints.push_back("(assert (>= len_" + *it + "_" + std::to_string(i) + " 0))");
			constraints.push_back("(assert (< len_" + *it + "_" + std::to_string(i) + " 100))");
			lenX = lenX + varName + std::to_string(i) + " ";
		}

		if (it->find("__flat_") != std::string::npos || it->substr(0, 6).compare("$$_str") == 0) {
			/* they are internal variables */
			defines.push_back("(declare-const len_" + *it + " Int)");
		}

		/* (+ sum(len_x_i) */
		if (QMAX > 1)
			lenX = "(+ " + lenX + ")";

		std::string lenName = "len_" + *it;
		/*(assert (= const (+ sum(len_x_i)))) */
		// constraints.push_back("(assert (< " + lenName + " 200))");
		constraints.push_back("(assert (= " + lenName + " " + lenX  + "))");
	}
}

/*
 * len_x = sum(len_y)
 */
std::string createLengthConstraintForAssignment(std::string x, std::vector<std::string> components){
	std::string lenX = "";
	int cnt = 0;
	for (unsigned int i = 0 ; i < components.size(); ++i){
		if (components[i][0] != '\"'){ /* not a const */
			lenX = lenX + " len_" + components[i];
			cnt ++;
		}
		else if (components[i].length() > 2) { /* const is not an empty string */
			if(!isRegexStr(components[i])) {
				lenX = lenX + " " + std::to_string(components[i].length() - 2);
				cnt ++;
			}
			else {
				/* regex */
				lenX = lenX + " " + std::to_string(parse_regex_content(components[i].substr(1, components[i].length() - 2)).length());
				cnt ++;
			}
		}
	}

	/* (+ sum(len_y)) */
	if (cnt > 1)
		lenX = "(+ " + lenX + ")";

	/*(= len_X (+ sum(len_y)) */
	if (x[0] != '\"')
		lenX = "(= len_" + x + " " + lenX  + ")";
	else {
		if(!isRegexStr(x))
			lenX = "(= " + std::to_string(x.length() - 2) + " " + lenX  + ")";
		else
			lenX = "(= " + std::to_string(parse_regex_content(x.substr(1, x.length() - 2)).length()) + " " + lenX  + ")";
	}
	printf("%d createLengthConstraintForAssignment: %s\n", __LINE__, lenX.c_str());

	return lenX;
}


/*
 * print to screen
 */
void printSMT(){
	std::vector<std::string> varDefines;//  = define_Size_It_Variables(global_smtVars);

	//	for (int i = 0 ; i < varDefines.size(); ++i)
	//		printf("%s\n", varDefines[i].c_str());


	for (unsigned int i = 0 ; i < global_smtStatements.size(); ++i){
		if (global_smtStatements[i].size() == 1) {
			printf("(assert ( %s )\n", global_smtStatements[i][0].c_str());
		}
		else {
			printf("(assert (or \n");
			for (unsigned int j = 0; j < global_smtStatements[i].size(); ++j)
				printf("%s\n", global_smtStatements[i][j].c_str());
			printf("))\n");
		}
	}


	printf("(check-sat)\n");
	printf("(get-model)\n");
}


/*
 * write to file output
 */
void writeOutput02(std::string outFile){
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);

	/* (declare-const X_i_sz Int) */
	/* (declare-const X_i_it Int) */
	/* (declare-const len_X_i Int) */
	std::vector<std::string> defines;
	std::vector<std::string> constraints;

	create_constraints_RegexCnt(defines, constraints);
	create_constraints_const(defines, constraints);
	create_constraints_strVar(defines, constraints);
	create_constraints_array(defines, constraints);
	create_const_array(defines, constraints);

	for (unsigned int i = 0 ; i < defines.size(); ++i) {
		out << defines[i] << std::endl;
		out.flush();
	}

	/* copy declare-const from smt file */
	for (unsigned int i = 0 ; i < smtVarDefinition.size(); ++i) {
		out << smtVarDefinition[i] << std::endl;
		out.flush();
	}

	for (unsigned int i = 0 ; i < constraints.size(); ++i) {
		out << constraints[i] << std::endl;
		out.flush();
	}

	/* repeated variables */
	for (unsigned int i = 0; i < repeatedVariableConstraints.size(); ++i) {
		out << repeatedVariableConstraints[i] << std::endl;
		out.flush();
	}

	/* assertions for flat automata*/
	for (unsigned int i = 0 ; i < global_smtStatements.size(); ++i){
		if (global_smtStatements[i].size() == 1) {
			out << "(assert " << global_smtStatements[i][0] << " )\n";
		}
		else {
			out << "(assert (or \n";
			for (unsigned int j = 0; j < global_smtStatements[i].size(); ++j)
				out << global_smtStatements[i][j] << std::endl;
			out<< ")) \n";

		}
		out.flush();
	}

	/* copy assertions from smt file */
	for (unsigned int i = 0 ; i < smtLenConstraints.size(); ++i) {
		out << smtLenConstraints[i];
		out.flush();
	}

	out << "(check-sat)\n(get-model)\n";
	out.flush();
	out.close();
}

/*
 * write to file output
 */
void writeOutput_basic(std::string outFile){
	std::ofstream out;
	out.open(outFile.c_str(), std::ios::out);


	std::vector<std::string> defines;
	std::vector<std::string> constraints;

	create_constraints_RegexCnt(defines, constraints);
	for (unsigned int i = 0 ; i < defines.size(); ++i) {
		out << defines[i] << std::endl;
		out.flush();
	}



	/* copy declare-const from smt file */
	for (unsigned int i = 0 ; i < smtVarDefinition.size(); ++i) {
		out << smtVarDefinition[i] << std::endl;
		out.flush();
	}

	for (unsigned int i = 0 ; i < constraints.size(); ++i) {
		out << constraints[i] << std::endl;
		out.flush();
	}

	/* copy assertions from smt file */
	for (unsigned int i = 0 ; i < smtLenConstraints.size(); ++i) {
		out << smtLenConstraints[i];
		out.flush();
	}

	out << "(check-sat)\n(get-model)\n";
	out.flush();
	out.close();
}

/*
 * write to file output
 */
void writeLengthOutput(std::string outFile,
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<std::string, std::string> lengthResultMap){
	assert(lengthResultMap.size() > 0);
	std::vector<std::string> lengthValues;

	__debugPrint(logFile, " *** writeLengthOutput *** \n");
	/* length assertions */
	for (std::vector<std::string>::iterator it = smtVarDefinition.begin(); it != smtVarDefinition.end(); ++it){
		std::vector<std::string> tokens = parse_string_language(*it, " ");

		std::string value = lengthResultMap[tokens[1]];

		printf("%d %s %s\n", __LINE__, it->c_str(), value.c_str());

		if (tokens[1].substr(0, 4).compare("len_") == 0) {
			std::string tmp = it->substr(4);
			lengthValues.push_back("(assert (= (Length " + tokens[1].substr(4) +") " + value + "))\n");
		}
		else {
			lengthValues.push_back("(assert (= " + tokens[1] + " " + value + "))\n");
		}
	}

	/* read & copy the input file */
	addLengthConstraintsToSMTFile(NONGRM, _equalMap, lengthValues, outFile);
}



/*
 * convert lhs == rhs to SMT formula
 */
std::pair<std::vector<std::string>, std::map<std::string, int>> equalityToSMT(
		std::string lhs, std::string rhs,
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements){
#ifdef DEBUGLOG
	__debugPrint(logFile, ">> equalities to SMT \n");
	for (unsigned int i = 0; i < lhs_elements.size(); ++i)
		__debugPrint(logFile, "%s.%d ", lhs_elements[i].first.c_str(), lhs_elements[i].second);
	__debugPrint(logFile, "= ");
	for (unsigned int i = 0; i < rhs_elements.size(); ++i)
		__debugPrint(logFile, "%s.%d ", rhs_elements[i].first.c_str(), rhs_elements[i].second);
	__debugPrint(logFile, "\nNumber of flats: %ld flats = %ld flats\n", lhs_elements.size(), rhs_elements.size());
#endif



	std::map<std::string, int> newVars;

	std::vector<std::string> cases = collectAllPossibleArrangements(
			lhs, rhs,
			lhs_elements, rhs_elements,
			newVars);
	displayListString(cases, " print cases");
	std::pair<std::vector<std::string>, std::map<std::string, int>> result = std::make_pair(cases, newVars);
	if (cases.size() == 0)
		newVars.clear();
	return result;
}

/*
 * print input
 */
void printEqualMap(std::map<std::string, std::vector<std::vector<std::string>>> equalMap) {
	__debugPrint(logFile, "%d Equal Map\n", __LINE__);
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalMap.begin();
			it != equalMap.end(); ++it) {
		__debugPrint(logFile, "%s =\n", it->first.c_str());
		for (unsigned int i = 0; i < it->second.size(); ++i) {
			for (unsigned int j = 0; j < it->second[i].size(); ++j) {
				__debugPrint(logFile, "\t%s ",  it->second[i][j].c_str());
			}
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
	}
}



/*
 * AutomataDef to const
 */
std::string collectConst(std::string str) {
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
		std::string extra = "";
		if (str[str.length() - 1] == '\"')
			str = str.substr(1, str.length() - 2);
		else {
			/* "abc"_number */

			for (unsigned int i = str.length() - 1; i >= 0; --i)
				if (str[i] == '_') {
					assert (str[i - 1] == '\"');
					extra = str.substr(i);
					str = str.substr(1, i - 2);
					__debugPrint(logFile, "%d extra: %s %s\n", __LINE__, str.c_str(), extra.c_str());
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
		str = "\"" + str + "\"" + extra;
	}
	__debugPrint(logFile, "%d collectConst: %s\n", __LINE__, str.c_str());
	return str;
}

std::string generate_simple_constraint(std::vector<std::vector<std::string>> eqVector){
	/* find a const*/
	for (unsigned int i = 0; i < eqVector.size(); ++i) {
		if (eqVector[i].size() == 1) {
			if (eqVector[i][0][0] == '\"') /* const */ {
				return std::to_string(eqVector[i][0].length() - 2);
			}
		}
	}

	/* pick the first option */
	std::string result = "";
	for (unsigned int i = 0 ; i < eqVector[0].size(); ++i)
		if (eqVector[0][i][0] == '\"') /* const */
			result = result + " " + std::to_string(eqVector[0][i].length() - 2);
		else
			result = result + " len_" + eqVector[0][i];
	if (eqVector[0].size() == 1)
		return result;
	else
		return "(+" + result + ")";
}

/*
 * read equality file
 * save data to equalMap
 * save all variables to allVariables
 */
void readFileEquality(std::string inputFile){
	FILE* in = fopen(inputFile.c_str(), "r");
	if (!in) {
		printf("%d %s", __LINE__, inputFile.c_str());
		throw std::runtime_error("Cannot open input file!");
	}
	std::map<std::string, std::vector<std::vector<std::string>>> equalMapTmp;
	char buffer[1000];

	/* read lengths of variables */
	while (1) {
		if (!fgets(buffer, sizeof buffer, in)) break;
		std::string tmp = buffer;

		if (tmp.length() > 0 && (tmp[tmp.length() - 1] == '\n' || tmp[tmp.length() - 1] == 10))
			tmp = tmp.substr(0, tmp.length() - 1);

		if (tmp.length() == 0) { /* break when get an empty line */
			break;
		}
		else {
			std::vector<std::string> tokens = parse_string_language(tmp, " ");
			assert(tokens.size() == 2);
			varLength[tokens[0]] = atoi(tokens[1].c_str());
		}
	}

	while (1) {
		if (!fgets(buffer, sizeof buffer, in)) break;
		std::string line = buffer;
		if (line.length() > 0 && line[line.length() - 1] == '\n')
			line = line.substr(0, line.length() - 1);

		if (line.compare("00") == 0)
			break;

		if (line.length() != 0) {
			if (line[0] == '=') { /* start of an equalities */
				/* read until get empty line */
				std::vector<std::string> components;
				while (1) {
					if (!fgets(buffer, sizeof buffer, in)) break;
					std::string tmp = buffer;

					if (tmp.length() > 0 && (tmp[tmp.length() - 1] == '\n' || tmp[tmp.length() - 1] == 10))
						tmp = tmp.substr(0, tmp.length() - 1);

					if (tmp.length() == 0) { /* break when get an empty line */
						break;
					}
					else {
						if (tmp[0] == '(') {
							tmp = collectConst(tmp);
							components.push_back(tmp);
						}
						else {
							std::vector<std::string> tokens = parse_string_language(tmp, " ");
							assert(tokens.size() == 1);
							if (varLength.find(tokens[0]) == varLength.end() || /* does not know its length */
									(varLength.find(tokens[0]) != varLength.end() && varLength[tokens[0]] > 0)) /* or length > 0 */
								components.push_back(tokens[0]);
						}
					}
				}

#ifdef ALLVAR
				for (unsigned int i = 0; i < components.size(); ++i)
					if (components[i][0] != '\"') { /* a new variables */
						allVariables.insert(components[i]);
					}
#endif

				line = line.substr(2); // skip "= "

#ifdef ALLVAR
				if (line[0] != '\"')  /* a new variables */
					allVariables.insert(line);
#endif

				if (equalMapTmp.find(line) == equalMapTmp.end()) {
					std::vector<std::vector<std::string>> tmp;
					tmp.push_back(components);
					equalMapTmp[line] = tmp;
				}
				else
					equalMapTmp[line].push_back(components);
			}
		}
	}

	/* read repeated variables*/
	std::vector<std::string> repeatedVariables;
	while (1) {
		if (!fgets(buffer, sizeof buffer, in)) break;
		std::string line = buffer;
		if (line.length() > 0 && line[line.length() - 1] == '\n')
			line = line.substr(0, line.length() - 1);

		repeatedVariables.push_back(line.substr(0, line.length() - 9)); /* " repeated" */
		// printf("%s\n", line.substr(0, line.length() - 9).c_str());
	}

	/* refine equal map*/
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalMapTmp.begin(); it != equalMapTmp.end(); ++it)
		if (std::find(repeatedVariables.begin(), repeatedVariables.end(), it->first) == repeatedVariables.end())
			equalitiesMap[it->first] = it->second;
		else {
			/* create length constraint for this variable*/
			std::string result = "(assert (= len_" + it->first + " " + generate_simple_constraint(it->second) + "))";
			// printf("%s \n", result.c_str());
			repeatedVariableConstraints.push_back(result);
		}

	pclose(in);
}

/**
 * collect all variables we need to handle
 */
void parseEqualityMap(std::map<std::string, std::vector<std::vector<std::string>>> _equalMap){
	equalitiesMap.clear();

	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = _equalMap.begin(); it != _equalMap.end(); ++it) {
		if (it->first[0] != '\"')
			allVariables.insert(it->first);
		std::vector<std::vector<std::string>> setOfEQ;
		for (unsigned int i = 0 ; i < it->second.size(); ++i) {
			std::vector<std::string> anEq;
			for (unsigned int j = 0; j < it->second[i].size(); ++j) {
				if (it->second[i][j][0] == '\"') { /* AutomataDef */
					std::string constStr = collectConst(it->second[i][j]);
					if (constStr.length() > 0)
						anEq.push_back(collectConst(it->second[i][j]));
				}
				else {/* skip const */
					if (varLength.find(it->second[i][j]) == varLength.end() || /* does not know its length */
							(varLength.find(it->second[i][j]) != varLength.end() && varLength[it->second[i][j]] > 0)) /* or length > 0 */ {

						anEq.push_back(it->second[i][j]);
						allVariables.insert(it->second[i][j]);
					}
				}
			}
			setOfEQ.push_back(anEq);
		}
		equalitiesMap[it->first] = setOfEQ;
	}

#ifdef PRINTTEST_UNDERAPPROX
	/* print test the equal map*/
	 printEqualMap(equalitiesMap);
#endif
}
/*
 * Create a general value that the component belongs to
 */
std::string sumStringVector(std::vector<std::string> list){
	std::string value = "";
	/* create a general value that the component belongs to */
	for (unsigned int k = 0; k < list.size(); ++k)
		value = value + list[k] + " ";
	return value;
}

/*
 * sum & split const strings
 * "a" . "b" = "ab"
 *
 * and update regex to make it to be deterministic
 */
void sumConstString(){
	std::map<std::string, std::vector<std::string>> parserMap;

	std::map<std::string, std::vector<std::vector<std::string>>> new_eqMap;
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin(); it != equalitiesMap.end(); ++it) {
		std::vector<std::vector<std::string>> tmp_vector;
		for (unsigned int j = 0; j < it->second.size(); ++j){
//			displayListString(it->second[j], "equalitiesMap to handle");
			std::vector<std::string> elements;
			std::string tmpStr = "";
			/* push to map */
			for (unsigned int k = 0; k < it->second[j].size(); ++k) {
				if (it->second[j][k][0] == '\"') {
					/* prevent the case: (abc)*  + def */
					if (isRegexStr(it->second[j][k])) {
						std::vector<std::string> localElements;
						/* reuse the parse result */
						if (parserMap.find(it->second[j][k]) != parserMap.end()) {
							localElements = parserMap[it->second[j][k]];
						}
						else {
							/* update regex */
							unsigned int tmpPos = it->second[j][k].length() - 1;
							for (tmpPos = it->second[j][k].length() - 1; tmpPos >= 0; --tmpPos)
								if (it->second[j][k][tmpPos] == '\"') {
									break;
								}

							std::string content = it->second[j][k].substr(1, tmpPos - 1);

							__debugPrint(logFile, "%d content = %s\n", __LINE__, content.c_str());
							/* parse this regex */
							std::vector<std::vector<std::string>> regexElements = refineVectors(parseRegexComponents(underApproxRegex(content)));

							/* assume that regexElements size is 1 */
							assert(regexElements.size() >= 1);

							if (regexElements.size() > 1)
								__debugPrint(logFile, "%d IMPORTANT NOTE: regexElements size = %ld\n", __LINE__, regexElements.size());

							unsigned int pos = 0;

							/* add to vector */
							while (pos < regexElements[0].size()){
								if (isRegexStr(regexElements[0][pos])) {
									localElements.push_back("\"" + regexElements[0][pos] + "__" + std::to_string(regexCnt++) + "\"");
								}
								else {
									localElements.push_back(regexElements[0][pos]);
								}
								pos++;
							}

							parserMap[it->second[j][k]] = localElements;
						}

						displayListString(localElements, " localElements list ");
						displayListString(elements, " elements list ");

						/*push to elements list */
						/* 1. handle the connecter point: tmpStr and first of local elements are const, sum them */
						bool constConnector = false;
						std::string firstOfLocalElements = localElements[0];
						if (firstOfLocalElements[0] == '\"' && !isRegexStr(firstOfLocalElements)){
							tmpStr =  tmpStr + firstOfLocalElements.substr(0, firstOfLocalElements.length() - 2);
							constConnector = true;
						}

						/* 2. add tmp the list */
						if (tmpStr.length() > 0) {
							elements.push_back("\"" + tmpStr + "\"");
							tmpStr = "";
						}

						if (constConnector == false)
							elements.insert(elements.end(), localElements.begin(), localElements.end());
						else {
							for (unsigned int kk = 1; kk < localElements.size(); ++kk)
								elements.push_back(localElements[kk]);
						}
					}
					else /* meet const str */
						tmpStr = tmpStr + it->second[j][k].substr(1, it->second[j][k].length() - 2);
				}
				else { /* meet variable */
					if (tmpStr.length() > 0) {
						elements.push_back("\"" + tmpStr + "\"");
						tmpStr = "";
					}
					elements.push_back(it->second[j][k]);
				}
			}
			if (tmpStr.length() > 0) {
				elements.push_back("\"" + tmpStr + "\"");
				tmpStr = "";
			}
			tmp_vector.push_back(elements);
		}
		new_eqMap[it->first] = tmp_vector;
	}

	equalitiesMap.clear();
	equalitiesMap = new_eqMap;

#ifdef PRINTTEST_UNDERAPPROX
	if (equalitiesMap.size() > 0) {
		printEqualMap(equalitiesMap);
	}
#endif
}


/*
 * Assign a name for each const string,
 * We need that name when we split const
 */
void createConstMap(){
	int constCnt = 0;
	constMap.clear();

	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin(); it != equalitiesMap.end(); ++it) {
		for (unsigned int j = 0; j < it->second.size(); ++j){

			/* create a general value that the component belongs to */
			std::string value = sumStringVector(it->second[j]);

			/* push to map */
			for (unsigned int k = 0; k < it->second[j].size(); ++k)
				if (it->second[j][k][0] == '\"'){
					std::string content = it->second[j][k].substr(1, it->second[j][k].length() - 2);
					/* string is regex ? */
					if (content[content.length() - 1] == '*' || content[content.length() - 1] == '+') {
						content = content + "__" + std::to_string(constCnt);
					}
					constMap[content] = "const_" + std::to_string(constCnt++);
				}
		}
	}

#ifdef PRINTTEST_UNDERAPPROX
	if (constMap.size() > 0) {
		/* print test const map */
		__debugPrint(logFile, "%d Const map:\n", __LINE__);
		for (std::map<std::string, std::string>::iterator it = constMap.begin(); it != constMap.end(); ++it) {
			__debugPrint(logFile, "%s: %s\n", it->first.c_str(), it->second.c_str());
		}
		__debugPrint(logFile, "\n");
	}
#endif
}

/*
 *
 */
void extractNotConstraints(){
	for (unsigned int i = 0; i < notConstraints.size(); ++i) {
		std::vector<std::string> tokens = parse_string_language(notConstraints[i], " ()");
		notMap[tokens[2]].insert(tokens[3].substr(1, tokens[3].length() - 2));
	}
}

/*
 * Find connected variables
 * They are variables that are used by more than one variables
 */

void collectConnectedVariables(){
	std::map<std::string, std::string> usedComponents;
	std::set<std::string> connectedVarSet;
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin(); it != equalitiesMap.end(); ++it) {
		if (it->second.size() <= 1)
			continue;

		for (unsigned int j = 0; j < it->second.size(); ++j){
			/* create a general value that the component belongs to */
			std::string value = sumStringVector(it->second[j]);

			/* push to map */
			for (unsigned int k = 0; k < it->second[j].size(); ++k)
				if (it->second[j][k][0] != '\"') {

					/* check if component is already in the map*/
					if (usedComponents.find(it->second[j][k]) != usedComponents.end()) {
						if (usedComponents[it->second[j][k]].compare(value) != 0) {
							connectedVarSet.insert(it->second[j][k]);
							// printf("at \n\t%s\n\t%s\n", usedComponents[it->second[j][k]].c_str(), value.c_str());
						}
					}
					else /* update map */
						usedComponents[it->second[j][k]] = value;
				}
		}

	}

	connectedVariables.insert(connectedVarSet.begin(), connectedVarSet.end());
#ifdef PRINTTEST_UNDERAPPROX
	/* print test connected var */
	if (connectedVariables.size() > 0) {
		__debugPrint(logFile, "%d Connected Variables:\n", __LINE__);

		for (std::set<std::string>::iterator it = connectedVariables.begin(); it != connectedVariables.end(); ++it){
			__debugPrint(logFile, "%s at %s\n", it->c_str(), usedComponents[*it].c_str());
		}
		__debugPrint(logFile, "\n");
	}
#endif
}

/*
 * Remove all equalities without connected variables and consts
 */

void refineEqualMap(){
	std::map<std::string, std::vector<std::vector<std::string>>> new_eqMap;
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin(); it != equalitiesMap.end(); ++it) {

		std::vector<std::vector<std::string>> tmp_vector;
		for (unsigned int j = 0; j < it->second.size(); ++j){

			/* push to map */
			for (unsigned int k = 0; k < it->second[j].size(); ++k) {
				if (it->second[j][k][0] == '\"' /* const */ ||
						connectedVariables.find(it->second[j][k]) != connectedVariables.end()) {
					tmp_vector.push_back(it->second[j]);
					break;
				}
			}
		}

		new_eqMap[it->first] = tmp_vector;
	}

	equalitiesMap.clear();
	equalitiesMap = new_eqMap;
}

/*
 *
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
	return result;
}

/*
 *
 */
std::string underApproxRegex(std::string str){
	/* remove all star-in-star */
	for (unsigned int i = 0 ; i < str.length(); ++i) {
		if (str[i] == '('){
			int counter = 1;
			bool hasStar = false;
			for (unsigned int j = i + 1; j < str.length(); ++j) {
				if (str[j] == ')'){
					counter--;
					if (counter == 0 && str[j + 1] == '*' && hasStar == true) {
						// str.replace(i, j - i + 2, str.substr(i + 1, j - i - 1));
						str.replace(j + 1, 1, "");
						return underApproxRegex(str);
					}
					else if (counter == 0){
						break;
					}
				}
				else if (str[j] == '('){
					counter++;
				}
				else if (str[j] == '*')
					hasStar = true;
			}
		}
	}
	return str;
}

/*
 *
 */
std::vector<std::vector<std::string>> parseRegexComponents(std::string str){
//	printf("%d parsing: \"%s\"\n", __LINE__, str.c_str());
	if (str.length() == 0)
		return {};

	std::vector<std::vector<std::string>> result;

	std::vector<std::string> alternativeRegex = collectAlternativeComponents(str);
	if (alternativeRegex.size() != 0){
		for (unsigned int i = 0; i < alternativeRegex.size(); ++i) {
			std::vector<std::vector<std::string>> tmp = parseRegexComponents(alternativeRegex[i]);
			assert(tmp.size() <= 1);
			if (tmp.size() == 1)
				result.push_back(tmp[0]);
		}
		return result;
	}

	size_t leftParenthesis = str.find('(');
//	if (leftParenthesis == std::string::npos || str[str.length() - 1] == '*' || str[str.length() - 1] == '+')
	if (leftParenthesis == std::string::npos)
		return {{str}};

	/* abc(def)* */
	if (leftParenthesis != 0) {
		std::string header = str.substr(0, leftParenthesis);
		std::vector<std::vector<std::string>> rightComponents = parseRegexComponents(str.substr(leftParenthesis));
		for (unsigned int i = 0; i < rightComponents.size(); ++i) {
			std::vector<std::string> tmp = {header};
			tmp.insert(tmp.end(), rightComponents[i].begin(), rightComponents[i].end());
			result.push_back(tmp);
		}
		return result;
	}

	int rightParenthesis = findCorrespondRightParenthesis(leftParenthesis, str);
	if (rightParenthesis < 0) {
		assert (false);
	}
	else if (rightParenthesis == (int)str.length() - 1){
		/* (a) */
		return parseRegexComponents(str.substr(1, str.length() - 2));
	}
	else if (rightParenthesis == (int)str.length() - 2 && (str[str.length() - 1] == '*' || str[str.length() - 1] == '+')){
		/* (a)* */
		return {{str}};
	}

	else {
		int pos = rightParenthesis;
		std::string left, right;
		if (str[rightParenthesis + 1] == '*' || str[rightParenthesis + 1] == '+'){
			pos++;
			left = str.substr(leftParenthesis, pos - leftParenthesis + 1);
			right = str.substr(pos + 1);
		}
		else if (str[pos] != '|' || str[pos] != '~') {
			left = str.substr(leftParenthesis + 1, pos - leftParenthesis - 1);
			right = str.substr(pos + 1);
		}
		else {
			assert (false);
			/* several options ab | cd | ef */
		}

		if (str[pos] != '|' || str[pos] != '~') {
			std::vector<std::vector<std::string>> leftComponents = parseRegexComponents(left);
			std::vector<std::vector<std::string>> rightComponents = parseRegexComponents(right);
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
 *
 */
bool equalVector(std::vector<std::string> a, std::vector<std::string> b){
	if (a.size() != b.size()) {
		return false;
	}
	for (unsigned int i = 0; i < a.size(); ++i)
		if (a[i].compare(b[i]) != 0) {
			return false;
		}
	return true;
}

/*
 * remove duplication
 */
std::vector<std::vector<std::string>> refineVectors(std::vector<std::vector<std::string>> list){

	bool duplicated[1000];
	memset(duplicated, false, sizeof duplicated);
	for (unsigned int i = 0; i < list.size(); ++i)
		if (!duplicated[i])
			for (unsigned int j = i + 1; j < list.size(); ++j)
				if (!duplicated[j]) {
					if (equalVector(list[i], list[j])) {
						duplicated[j] = true;
					}
				}

	std::vector<std::vector<std::string>> result;
	for (unsigned int i = 0 ; i < list.size(); ++i)
		if (!duplicated[i])
			result.push_back(list[i]);

	for (unsigned int i = 0; i < result.size(); ++i)
		for (unsigned int j = 0; j < result[i].size(); ++j)
			if (result[i][j][0] != '(')
				result[i][j] = "\"" + result[i][j] + "\"";
	return result;
}
/*
 * Input: x . y
 * Output: flat . flat . flat . flat . flat . flat
 */
std::vector<std::pair<std::string, int>> createEquality(std::vector<std::string> list){
	std::vector<std::pair<std::string, int>> elements;

	for (unsigned int k = 0; k < list.size(); ++k)
		if (list[k][0] == '\"') {
			size_t starPos = list[k].find('*');
			if (starPos == std::string::npos)
				starPos = list[k].find('+');

			if (starPos == std::string::npos) {
				if (list[k].length() > SPLIT_UNDER_BOUND) /* const string */ {
					for (int j = 0; j < QCONSTMAX; ++j) { /* split variables into QMAX parts */
						elements.push_back(std::make_pair(list[k].substr(1, list[k].length() - 2), -(j + 1)));
					}
				}
				else {
					/* length < SPLIT_UNDER_BOUND */
					elements.push_back(std::make_pair(list[k].substr(1, list[k].length() - 2), -1));
				}
			}
			else {
				/* regex */
				std::string content = list[k].substr(1, list[k].length() - 2);

				elements.push_back(std::make_pair(content, REGEX_CODE));
			}
		}
		else {
			for (int j = 0; j < QMAX; ++j) { /* split variables into QMAX parts */
				elements.push_back(std::make_pair(list[k], j));
			}
		}

//	for (unsigned int i = 0; i < elements.size(); ++i)
//		printf("%s.%d ---- ", elements[i].first.c_str(), elements[i].second);
//	printf("%d\n",__LINE__);

	return elements;
}

/**
 * extra variables
 */
std::vector<std::string> createSetOfFlatVariables(int flatP) {
	pthread_mutex_lock (&smt_mutex);
	std::vector<std::string> result;
	for (int i = 0 ; i < flatP; ++i) {
		std::string varName = "__flat_" + std::to_string(noFlatVariables + i);
		result.push_back(varName);
		connectedVariables.insert(varName);
		allVariables.insert(varName);
	}
	noFlatVariables += flatP;
	pthread_mutex_unlock (&smt_mutex);
	return result;
}

/*
 * Pthread
 * Each thread handles a part in the global map from start -> end
 */
void *convertEqualities(void *tid){
	int start, *mytid, end;
	mytid = (int *) tid;

	/* define elements that will be handled by this thread*/
	start = (*mytid * (equalitiesMap.size() / NUM_THREADS));
	if (*mytid != NUM_THREADS - 1)
		end = start + (equalitiesMap.size() / NUM_THREADS);
	else
		end = equalitiesMap.size();

#ifdef DEBUGLOG
	// printf("Thread %d starting...\n", *mytid);
	// printf ("Thread %d doing iterations %d to %d\n", *mytid, start, end-1);
#endif

	/* return a number of results*/
	auto startIt = std::next(equalitiesMap.begin(), start);
	auto endIt = std::next(equalitiesMap.begin(), end);
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = startIt;
			it != endIt;
			++it) {
#ifdef DEBUGLOG
		// printf ("Thread %d doing: %s, size = %ld\n", *mytid, it->first.c_str(), it->second.size());
#endif

		std::vector<std::string> lenConstraint;
		std::string tmp = " ";
		bool lengthRecord = false;
		clock_t t;

		/* different tactic for size of it->second */
		const int flatP = 1;
		const int maxPConsidered = 6;
		unsigned int maxLocal = 0;
		for (unsigned int i = 0; i < it->second.size(); ++i) {
			maxLocal = it->second[i].size() > maxLocal ? it->second[i].size() : maxLocal;
		}
#ifdef PRINTTEST_UNDERAPPROX
		__debugPrint(logFile, "%d Max list size: %d\n", __LINE__, maxLocal);
#endif
		if (maxLocal >= maxPConsidered) {
			/* add an eq = flat . flat . flat, then other equalities will compare will it*/
			std::vector<std::string> genericFlat = createSetOfFlatVariables(flatP);
			std::vector<std::pair<std::string, int>> lhs_elements = createEquality(genericFlat);

			/* compare with others */
			for (unsigned int i = 0; i < it->second.size(); ++i) {
				std::vector<std::pair<std::string, int>> rhs_elements = createEquality(it->second[i]);
				t = clock();
				std::pair<std::vector<std::string>, std::map<std::string, int>> result = equalityToSMT(	sumStringVector(genericFlat),
						sumStringVector(it->second[i]),
						lhs_elements,
						rhs_elements
				);
				t = clock() - t;

#ifdef PRINTTEST_UNDERAPPROX
				__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
				if (result.first.size() != 0) {
					if (lengthRecord == false) {
						/* (= len_X (+ sum(len_y)) */
						 lenConstraint.push_back(createLengthConstraintForAssignment(it->first, it->second[0]));
						lengthRecord = true;
					}
					/* sync result*/
					pthread_mutex_lock (&smt_mutex);
					for (std::map<std::string, int>::iterator iter = result.second.begin(); iter != result.second.end(); ++iter) {
						global_smtVars[iter->first] = 'd';
					}
					global_smtStatements.push_back(result.first);

					if (lenConstraint.size() > 0) {
						global_smtStatements.push_back(lenConstraint);
						lenConstraint.clear();
					}
					pthread_mutex_unlock (&smt_mutex);
				}
				else {
					/* trivial unsat */
					trivialUnsat = true;
				}
			}
		}
		else {

			/* work as usual */
			for (unsigned int i = 0; i < it->second.size(); ++i)
				for (unsigned int j = i + 1; j < it->second.size(); ++j) {
					/* [i] = [j] */

					std::vector<std::pair<std::string, int>> lhs_elements = createEquality(it->second[i]);
					std::vector<std::pair<std::string, int>> rhs_elements = createEquality(it->second[j]);
					t = clock();
					std::pair<std::vector<std::string>, std::map<std::string, int>> result = equalityToSMT(	sumStringVector(it->second[i]),
																											sumStringVector(it->second[j]),
																											lhs_elements,
																											rhs_elements
																										);
					t = clock() - t;
#ifdef PRINTTEST_UNDERAPPROX
					__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
					if (result.first.size() != 0) {
						if (lengthRecord == false) {
							/* (= len_X (+ sum(len_y)) */
							lenConstraint.push_back(createLengthConstraintForAssignment(it->first, it->second[0]));
							lengthRecord = true;
						}
						/* sync result*/
						pthread_mutex_lock (&smt_mutex);
						for (std::map<std::string, int>::iterator iter = result.second.begin(); iter != result.second.end(); ++iter) {
							global_smtVars[iter->first] = 'd';
						}
						global_smtStatements.push_back(result.first);

						if (lenConstraint.size() > 0) {
							global_smtStatements.push_back(lenConstraint);
							lenConstraint.clear();
						}
						pthread_mutex_unlock (&smt_mutex);
					}
					else {
						/* trivial unsat */
						trivialUnsat = true;
					}
				}
		}
		/**/

	}

#ifdef DEBUGLOG
	// printf("Thread %d done.\n", *mytid);
#endif
	pthread_exit(NULL);
}

/*
 * Just do sequential to compare performance
 */
void testSequential(){
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin();
			it != equalitiesMap.end();
			++it) {

		for (unsigned int i = 1; i < it->second.size(); ++i) {
			/* [i] = [i - 1] */

			std::vector<std::pair<std::string, int>> lhs_elements = createEquality(it->second[i - 1]);
			std::vector<std::pair<std::string, int>> rhs_elements = createEquality(it->second[i]);

			std::pair<std::vector<std::string>, std::map<std::string, int>> result = equalityToSMT(	sumStringVector(it->second[i]),
					sumStringVector(it->second[i]),
					lhs_elements,
					rhs_elements
			);
		}

	}
}

/*
 *
 */
void testEqualityToSMT(){
	std::string frame = "LLutmbC169413169LLutmcC169413169LLutmaC169413169.K";

	std::vector<std::pair<std::string, int>> lhs_elements;
	std::vector<std::pair<std::string, int>> rhs_elements;

	int variables = 5;
	for (int i = 0; i < variables; ++i)
		for (int j = 0; j < QMAX; ++j) {
			lhs_elements.push_back(std::make_pair("varX" + std::to_string(i), j));
			rhs_elements.push_back(std::make_pair("varY" + std::to_string(i), j));
		}

	lhs_elements.push_back(std::make_pair(frame, -1));
	// std::cout << tim::measure<>::execution(equalityToSMT, lhs_elements, rhs_elements) << std::endl;
}

/*
 *
 */
bool Z3_run(
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		bool finalCall = true) {
	std::string cmd = std::string(Z3_PATH) + "-smt2 " + OUTPUT;
	printf(">> Running Z3...\n");

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("Z3 failed!");

	std::map<std::string, std::string> results;
	char buffer[5000];
	std::string result = "";
	bool sat = false;
	try {
		/* the first line */
		fgets(buffer, 4000, in);
		std::string getSat = buffer;
		getSat = getSat.substr(0, 3);

		if (getSat.compare("sat") == 0) {
			printf(">> SAT\n\n");
			sat = true;
		}
		else {
			if (finalCall == true)
				printf(">> UNSAT\n\n");
			printf("%d here\n", __LINE__);
			return sat;
		}
		/* the concrete values */
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 4000, in) != NULL) {
				line = buffer;
				if (line.find("(define") != std::string::npos) {
					/* collect variable */
					std::vector<std::string> tokens = parse_string_language(buffer, " (),.");

					std::string name = tokens[1];

					/* read the value in the next line */
					fgets(buffer, 4000, in);
					tokens = parse_string_language(buffer, " (),.");
					if (tokens[0][0] == '-')
						results[name] = "(" + tokens[0] + " " + tokens[1] + ")";
					else
						results[name] = tokens[0];

					printf("%d result of %s: %s\n", __LINE__, name.c_str(), results[name].c_str());
				}
			}

		}

	} catch (...) {
		pclose(in);
		throw;
	}
	pclose(in);

	/* collect length of all string variables*/
	std::string lengthFile = std::string(TMPDIR) + "w_l_" + getFileNameFromFileDir(orgInput);
#ifdef PRINTTEST_UNDERAPPROX
	__debugPrint(logFile, "%d output with length: %s\n", __LINE__, lengthFile.c_str());
#endif

	writeLengthOutput(lengthFile, _equalMap, results);
	if (sat && getModel)
		sat = S3_assist(lengthFile);
	return sat;
}

/*
 *
 */
bool S3_assist(std::string fileName){
	std::string cmd = std::string(S3_PATH) + " -f " + fileName;
	printf("Collecting concrete values...\n");

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("S3 failed!");

	std::map<std::string, std::string> results;
	char buffer[5000];
	std::string result = "";
	bool sat = false;
	try {
		/* the concrete values */
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 5000, in) != NULL) {
				//				printf("%s\n", buffer);
				line = buffer;
				if (line.length() > 0 && line[0] == '*')
					printf("================================================\n");
				else if (line.length() > 0 && line[0] == '-')
					printf("------------------------------------------------\n");
				else {
					if (line.substr(0, 6).compare(">> SAT") == 0)
						sat = true;
					if (line.find("String!val!") == std::string::npos)
						printf("%s", buffer);
				}
			}

		}

	} catch (...) {
		pclose(in);
		throw;
	}
	pclose(in);
	return sat;
}

/*
 * Pthread Caller
 */
void pthreadController(){
	pthread_t thread[NUM_THREADS];
	int  tids[NUM_THREADS];
	pthread_attr_t attr;
	int rc;

	/* Initialize and set thread detached attribute */
	pthread_mutex_init(&smt_mutex, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/* create threads */
	for(int t = 0; t < NUM_THREADS; t++) {
		tids[t] = t;
#ifdef DEBUGLOG
		// printf("Controller: creating thread %d\n", t);
#endif
		rc = pthread_create(&thread[t], &attr, convertEqualities, (void *) &tids[t]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	/* Free attribute and wait for the other threads */
	pthread_attr_destroy(&attr);

	/* join threads */
	void *result;
	for(int t = 0; t < NUM_THREADS; t++) {
		rc = pthread_join(thread[t], &result);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
		}
#ifdef DEBUGLOG
		// printf("Controller: completed join with thread %d.\n", t);
#endif
	}

	pthread_mutex_destroy(&smt_mutex);

	//	pthread_exit(NULL);
}

void init(){
	// extractNotConstraints(); //it will do nothing
	collectConnectedVariables();
	refineEqualMap();
	sumConstString();
	createConstMap();
}

bool underapproxController(
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<std::string, bool> containStrMap,
		std::map<std::string, std::string> indexOfStrMap,
		std::map<std::string, std::string> lastIndexOfStrMap,
		std::map<std::string, int> _currentLength,
		std::string fileDir ) {
	std::vector<std::vector<std::string>> test = refineVectors(parseRegexComponents(underApproxRegex("( not )*a > 1a1 or ( not )*1a1 > a")));
	for (unsigned int i = 0; i < test.size(); ++i)
		displayListString(test[i], " parse regex ");

	printf("Running Under Approximation...\n");


	/* init varLength */
	varLength.clear();
	varLength.insert(_currentLength.begin(), _currentLength.end());


	/* init equalMap */
	parseEqualityMap(_equalMap);

	notConstraints.clear();
	smtLenConstraints.clear();
	smtVarDefinition.clear();
	global_smtStatements.clear();

	init();

	/* rewrite the CFG constraint */
	printEqualMap(equalitiesMap);
#ifdef PRINTTEST_UNDERAPPROX
	if (constMap.size() > 0) {
		/* print test const map */
		__debugPrint(logFile, "%d Const map:\n", __LINE__);
		for (std::map<std::string, std::string>::iterator it = constMap.begin(); it != constMap.end(); ++it) {
			__debugPrint(logFile, "%s: %s\n", it->first.c_str(), it->second.c_str());
		}
		__debugPrint(logFile, "\n");
	}
#endif
	rewriteGRM_toNewFile(fileDir, NONGRM, equalitiesMap, constMap);

	/* init regexCnt */
	regexCnt = 0;

	bool result = false;

	if (connectedVariables.size() == 0 && equalitiesMap.size() == 0) {
		convertSMTFileToLengthFile(NONGRM, true, containStrMap, indexOfStrMap, lastIndexOfStrMap, regexCnt, smtVarDefinition, smtLenConstraints, notConstraints);
		if (trivialUnsat) {
			printf("%d false \n", __LINE__);
			return false;
		}

		writeOutput_basic(OUTPUT);

		bool val = Z3_run(_equalMap, false);
		if (val == false){
			regexCnt = 0;
			convertSMTFileToLengthFile(NONGRM, false, containStrMap, indexOfStrMap, lastIndexOfStrMap, regexCnt, smtVarDefinition, smtLenConstraints, notConstraints);
			if (trivialUnsat) {
				printf("%d false \n", __LINE__);
				return false;
			}
			writeOutput_basic(OUTPUT);
			result = Z3_run(_equalMap);
		}
	}
	else {
		convertSMTFileToLengthFile(NONGRM, false, containStrMap, indexOfStrMap, lastIndexOfStrMap, regexCnt, smtVarDefinition, smtLenConstraints, notConstraints);
		pthreadController();
		if (trivialUnsat) {
			printf("%d false \n", __LINE__);
			return false;
		}
		else {
			std::cout << ">> Generated SMT\n\n";
			writeOutput02(OUTPUT);

			result =  Z3_run(_equalMap);
		}
	}

	if (result == false) {
		/* skip */
	}

	printf("%d %s\n", __LINE__, result == true ? "true" : "false");
	return result;
}


