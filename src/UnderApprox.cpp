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

/*
 * get value from eq map
 */
std::string getPossibleValue(std::string s){
	if (s[0] == '\"'){
		return s;
	}
	else {
		if (equalitiesMap.find(s) != equalitiesMap.end())
			for (const auto& value : equalitiesMap[s]){
				if (value.size() == 1)
					if (value[0][0] == '\"')
						return value[0];
			}
		else
			return "!FoUnD";
	}
	return "!FoUnD";
}

bool isEqualVector(std::vector<std::string> a, std::vector<std::string> b) {

	if (a.size() != b.size())
		return false;
	for (unsigned int i = 0; i < a.size(); ++i)
		if (a[i].compare(b[i]) != 0)
			return false;

	return true;
}

std::vector<std::string> find_eq_class(std::string var){
	std::vector<std::string> ret;
	for (const auto& v : equalitiesMap) {
		if (v.first.compare(var) == 0)
			ret.emplace_back(v.first);
		else {
			for (const auto& l00 : v.second) {
				bool found = false;
				for (const auto& l01 :equalitiesMap[var]){
					/* compare two vectors */
					if (isEqualVector(l00, l01)) {
						found = true;
						break;
					}
				}
				if (found) {
					ret.emplace_back(v.first);
					break;
				}
			}
		}
	}
	return ret;
}

void updatePossibleArrangements(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		std::vector<Arrangment> tmp,
		std::vector<Arrangment> &possibleCases) {
	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (tmp[i].isPossibleArrangement(lhs_elements, rhs_elements))
			possibleCases.emplace_back(tmp[i]);
}

void updatePossibleArrangements(
		std::vector<Arrangment> tmp,
		std::vector<Arrangment> &possibleCases) {
	for (unsigned int i = 0; i < tmp.size(); ++i)
		if (tmp[i].isPossibleArrangement())
			possibleCases.emplace_back(tmp[i]);
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
bool isConstStr(std::string str){
	if (str[0] == '"' && str.find(")*") == std::string::npos && str.find(")+") == std::string::npos)
		return true;
	else
		return false;
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
	tmpLeft.emplace_back(0);
	tmpRight.emplace_back(0);
	arrangements[std::make_pair(0, 0)].emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
}

/*
 * First base case
 */
void handleCase_0_0_general(){
	std::vector<int> tmpLeft;
	std::vector<int> tmpRight;

	if (arrangements[std::make_pair(0, 0)].size() == 0) {
		/* left = right */
		tmpLeft.emplace_back(0);
		tmpRight.emplace_back(0);
		arrangements[std::make_pair(0, 0)].emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
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
	tmpRight.emplace_back(SUMFLAT);

	/* left has i number of 0 */
	std::vector<int> tmpLeft;
	tmpLeft.emplace_back(0);

	for (unsigned int i = 1; i < lhs_elements.size(); ++i) {
		tmpLeft.emplace_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

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
	tmpRight.emplace_back(SUMFLAT);

	/* left has i number of 0 */
	std::vector<int> tmpLeft;
	tmpLeft.emplace_back(0);

	for (int i = 1; i < lhs; ++i) {
		tmpLeft.emplace_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

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
	tmpLeft.emplace_back(SUMFLAT);

	/* right has i number of 0 */
	std::vector<int> tmpRight;
	tmpRight.emplace_back(0);

	for (unsigned int i = 1 ; i < rhs_elements.size(); ++i) {
		tmpRight.emplace_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

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
	tmpLeft.emplace_back(SUMFLAT);

	/* right has i number of 0 */
	std::vector<int> tmpRight;
	tmpRight.emplace_back(0);

	for (int i = 1 ; i < rhs; ++i){
		tmpRight.emplace_back(0);

		std::vector<Arrangment> tmp04;
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));

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
						tmpLeft.emplace_back(EMPTYFLAT);
					tmpLeft.emplace_back(SUMFLAT);

					std::vector<int> tmpRight;
					for (unsigned int k = 0 ; k <= j; ++k)
						tmpRight.emplace_back(i);
					tmp03.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
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
						tmpLeft.emplace_back(j);

					std::vector<int> tmpRight;
					for (unsigned int k = 0; k < j; ++k)
						tmpRight.emplace_back(EMPTYFLAT);
					tmpRight.emplace_back(SUMFLAT);
					tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
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
						tmpLeft.emplace_back(EMPTYFLAT);
					tmpLeft.emplace_back(SUMFLAT);

					std::vector<int> tmpRight;
					for (int k = 0 ; k <= j; ++k)
						tmpRight.emplace_back(i);

					assert ((int)tmpLeft.size() == i + 1);
					assert ((int)tmpRight.size() == j + 1);
					tmp03.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
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
						tmpLeft.emplace_back(j);

					std::vector<int> tmpRight;
					for (int k = 0; k < j; ++k)
						tmpRight.emplace_back(EMPTYFLAT);
					tmpRight.emplace_back(SUMFLAT);

					assert ((int)tmpLeft.size() == i + 1);
					assert ((int)tmpRight.size() == j + 1);
					tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap, notMap));
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
 *
 */
Arrangment manuallyCreate_arrangment(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements){

	/* create manually */
	/*10000000 10000000 vs 0 0 1 1 1 */
	std::vector<int> left_arr;
	std::vector<int> right_arr;
	unsigned mid = rhs_elements.size() / 2;
 	if (false) {
 		left_arr.emplace_back(SUMFLAT);
 		left_arr.emplace_back(SUMFLAT);
 		for (unsigned i = 0; i <= mid; ++i)
 			right_arr.emplace_back(0);
 		for (unsigned i = mid + 1; i < rhs_elements.size(); ++i)
 			right_arr.emplace_back(1);
 	}
 	else {
 		left_arr.emplace_back(EMPTYFLAT);
 		left_arr.emplace_back(SUMFLAT);
 		for (unsigned i = 0; i < rhs_elements.size(); ++i)
 			right_arr.emplace_back(1);
 	}
	return Arrangment(left_arr, right_arr, constMap, notMap);
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
	if (lhs_elements[0].first.find("__flat_") != std::string::npos ||
			(lhs_elements.size() == 2 &&
					 ((connectedVariables.find(lhs_elements[0].first) != connectedVariables.end() && lhs_elements[1].second == 1) ||
					  (lhs_elements[0].second == -1 && lhs_elements[1].second == -2)))) {
		/* create manually */
		/*9999999 10000000 vs 1 1 1 1 1 */
		possibleCases.emplace_back(manuallyCreate_arrangment(lhs_elements, rhs_elements));
	}
	else {
		updatePossibleArrangements(lhs_elements, rhs_elements, arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)], possibleCases);
	}
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
			cases.emplace_back(tmp);
		}
		else {
		}
	}
#else

	/* 1 vs n, 1 vs 1, n vs 1 */
	for (unsigned int i = 0; i < possibleCases.size(); ++i) {
		//		arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)][i].printArrangement("Checking case");
		possibleCases[i].constMap.clear();
		possibleCases[i].constMap.insert(constMap.begin(), constMap.end());
		std::string tmp = possibleCases[i].
				generateSMT(PMAX, lhs_str, rhs_str, lhs_elements, rhs_elements, connectedVariables);

		if (tmp.length() > 0) {
			cases.emplace_back(tmp);
//			arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)][i].printArrangement("Correct case");
//			__debugPrint(logFile, "%d %s\n", __LINE__, tmp.c_str());
		}
		else {
		}
	}
#endif
	return cases;

}

/*
 * Given a flat,
 * generate its array name
 */
std::string generateVarArray(std::string a){
	return "arr_" + a;
}

/*
 * Given a flat,
 * generate its array name
 */
std::string generateVarLength(std::string a){
	return "len_" + a;
}

/*
 *
 */
int findVariableSize(std::string v){
	int minSize = MAXP;
	for (const auto& var : equalitiesMap)
		for (const auto& _eq : var.second) {
			int localMin = MAXP;
			if (std::find(_eq.begin(), _eq.end(), v) != _eq.end()) {
				/* count regex */
				for (const auto& s : _eq) {
					if (s[0] == '"')
						if (isRegexStr(s) && s.find("+") != std::string::npos)
							localMin--;
				}
				minSize = minSize < localMin ? minSize : localMin;
			}
		}
	return minSize;
}

/*
 *
 */
bool canSkipNotContain(
		std::string v,
		std::string arg,
		std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& var : equalitiesMap)
			for (const auto& _eq : var.second) {
				if (std::find(_eq.begin(), _eq.end(), v) != _eq.end()) {
					StringOP opTmp("Contains", var.first, arg);
					if (rewriterStrMap[opTmp].compare("false") == 0) {
						__debugPrint(logFile, "%d *** %s ***: Contains - %s - %s\n", __LINE__, __FUNCTION__, v.c_str(), arg.c_str());
						return true;
					}
				}
			}
	return false;
}
/*
 * startswith a b
 * startwith "a" b
 * startwith a "b"
 */
std::string create_constraints_StartsWith(
		std::string str00,
		std::string str01,
		std::string boolValue){
	__debugPrint(logFile, "%d *** %s ***: StartsWith %s %s\n", __LINE__, __FUNCTION__, str00.c_str(), str01.c_str());

	if (boolValue.compare("false") != 0)
		return "true";

	bool isConst_00 = false;
	bool isConst_01 = false;
	if (str00[0] == '\"' )
		isConst_00 = true;

	if (str01[0] == '\"')
		isConst_01 = true;

	assert(isConst_00 || isConst_01);

	std::vector<std::string> orConstraints;
	std::vector<std::string> andConstraints;

	std::string ret = "";

	if (isConst_00 == true) {
		/* (length b = 0 && ...) || length b = 1 && ...*/
		for (unsigned int j = 0; j < str00.length() - 2; ++j) {
			/* length = j*/
			andConstraints.emplace_back("(= " + generateVarLength(str01) + " " + std::to_string(j) + ")");
			for (unsigned int i = 1; i < j + 1; ++i) {
				andConstraints.emplace_back("(= (select " +
						generateVarArray(str01) + " " +
						std::to_string(i - 1) + ") " +
						std::to_string(str00[i]) + ")");
			}
			orConstraints.emplace_back(andConstraint(andConstraints));
			andConstraints.clear();
		}

		ret = orConstraint(orConstraints);

	}
	else if (isConst_01){
		/* (length a >= ... && ...) */
		andConstraints.emplace_back("(>= " + generateVarLength(str00) + " " + std::to_string(str01.length() - 2) + ")");
		for (unsigned int i = 1; i < str01.length() - 1; ++i) {
			andConstraints.emplace_back("(= (select " +
					generateVarArray(str00) + " " +
					std::to_string(i - 1) + ") " +
					std::to_string(str01[i]) + ")");
		}
		ret = andConstraint(andConstraints);
	}
	else {

		for (int j = 0; j <= std::min(CONNECTSIZE, 50); ++j) {
			/* length b = j*/
			andConstraints.emplace_back("(= " + generateVarLength(str01) + " " + std::to_string(j) + ")");
			for (int i = 0; i < j; ++i) {
				andConstraints.emplace_back("(= (select " +
						generateVarArray(str00) + " " +
						std::to_string(i) + ") " +
						"(= (select " +
						generateVarArray(str01) + " " +
						std::to_string(i) + ") " + ")");
			}
			orConstraints.emplace_back(andConstraint(andConstraints));
			andConstraints.clear();
		}
		ret = orConstraint(orConstraints);
		andConstraints.clear();
		andConstraints.emplace_back("(>= " + generateVarLength(str00) + " " + generateVarLength(str01) + ")");
		andConstraints.emplace_back(ret);

		ret = andConstraint(andConstraints);
	}

	ret = "(and \t(not " + ret + ")" +
				"\t(< " + generateVarLength(str00) + " " + std::to_string(std::min(CONNECTSIZE, 50)) + "))";
	__debugPrint(logFile, "%d >> %s\n", __LINE__, ret.c_str());
	return ret;
}

/*
 * endswith a b
 * endswith "a" b
 * endswith a "b"
 */
std::string create_constraints_EndsWith(
		std::string str00,
		std::string str01,
		std::string boolValue){
	__debugPrint(logFile, "%d *** %s ***: EndsWith %s %s\n", __LINE__, __FUNCTION__, str00.c_str(), str01.c_str());
	bool isConst_00 = false;
	bool isConst_01 = false;
	if (str00[0] == '\"' )
		isConst_00 = true;

	if (str01[0] == '\"')
		isConst_01 = true;

	assert(isConst_00 || isConst_01);

	std::vector<std::string> orConstraints;
	std::vector<std::string> andConstraints;

	std::string ret = "";

	if (isConst_00 == true) {
		/* endswith "a" b */
		/* (length b = 0 && ...) || length b = 1 && ...*/
		for (unsigned int j = 0; j < str00.length() - 2; ++j) {
			/* length = j*/
			andConstraints.emplace_back("(= " + generateVarLength(str01) + " " + std::to_string(j) + ")");
			for (unsigned int i = str00.length() - 1 - j; i < str00.length() - 1; ++i) {
				andConstraints.emplace_back("(= (select " +
						generateVarArray(str01) + " " +
						std::to_string(i - str00.length() + 1 + j) + ") " +
						std::to_string(str00[i]) + ")");
			}
			orConstraints.emplace_back(andConstraint(andConstraints));
			andConstraints.clear();
		}

		ret = orConstraint(orConstraints);

	}
	else if (isConst_01){
		/* endswith a "b" */
		/* (length a >= ... && ...) */
		andConstraints.emplace_back("(>= " + generateVarLength(str00) + " " + std::to_string(str01.length() - 2) + ")");
		for (unsigned int i = 1; i < str01.length() - 1; ++i) {
			andConstraints.emplace_back("(= (select " +
					generateVarArray(str00) + " " +
					"(+ (- " + generateVarLength(str00) + " " + std::to_string(str01.length() - 2) + ") " + std::to_string(i - 1) + ")) " +
					std::to_string(str01[i]) + ")");
		}

		ret = andConstraint(andConstraints);
	}
	else {
		/* do not handle this case*/
		assert(false);
	}

	if (boolValue.compare("false") == 0)
		ret = "(not " + ret + ")";
	__debugPrint(logFile, "%d >> %s\n", __LINE__, ret.c_str());
	return ret;
}

/*
 * replace a b c
 * replace "a" b c
 * replace a "b" c
 */
std::string create_constraints_Replace(std::string lhs, std::vector<std::string> args, std::string boolValue){
	bool isConst_00 = false;
	bool isConst_01 = false;
	bool isConst_02 = false;
	if (args[0][0] == '\"' )
		isConst_00 = true;

	if (args[1][0] == '\"')
		isConst_01 = true;

	if (args[2][0] == '\"')
		isConst_02 = true;

	/* do not replace */
	if (boolValue.compare("false") == 0){
		/* new value = old value = args[0] */
		/* len = len && value = value */
		std::vector<std::string> andConstraints;
		andConstraints.emplace_back("(= " + generateVarArray(args[0]) + " " + generateVarLength(lhs) +")");
		if (connectedVariables.find(args[0]) != connectedVariables.end() ||
				connectedVariables.find(lhs) != connectedVariables.end()){
			// TODO replace constraints: two connected variables
		}
	}

	/* */
	if (isConst_00) {

	}

	if (isConst_01) {

	}

	if (isConst_02) {

	}
	return "true";
}

/*
 * replaceAll a b c
 * replaceAll "a" b c
 * replaceAll a "b" c
 *
 * --> iter = iter
 */
std::string create_constraints_ReplaceAll(
		std::vector<std::string> args,
		std::string boolValue,
		std::map<std::string, std::vector<std::string>> eqToStr){

	__debugPrint(logFile, "%d *** %s ***: %s %s %s %s\n", __LINE__, __FUNCTION__, args[0].c_str(), args[1].c_str(), args[2].c_str(), boolValue.c_str());
	bool isConst_00 = false;
	bool isConst_01 = false;
	bool isConst_02 = false;
	if (args[0][0] == '"')
		isConst_00 = true;

	if (args[1][0] == '"')
		isConst_01 = true;

	if (args[2][0] == '"')
		isConst_02 = true;

	std::string s0 = "(" + args[1].substr(1, args[1].length() - 2) + ")+";
	std::string s1 = "(" + args[2].substr(1, args[2].length() - 2) + ")+";

	/* */
	if (isConst_00 && isConst_01 && isConst_02)
		return "true";
	else if (isConst_01 && isConst_02 && boolValue.compare("true") == 0) {
		std::string result = "";
		/* find all eq variable */
		std::vector<std::string> eqArg0 = find_eq_class(args[0]);
		assert (equalitiesMap.find(args[0]) != equalitiesMap.end());
		for (const auto& var : eqArg0) {
			__debugPrint(logFile, "%d %s == %s\n", __LINE__, args[0].c_str(), var.c_str());
			for (const auto& list : equalitiesMap[var]) {
				/* if all internal vars */
				std::string tmp = "";
				std::vector<std::string> listRegexPlus00;
				for (const auto& s : list)
					if (s[0] == '$')
						tmp = tmp + s;
					else if (s[0] != '"') {
						tmp = "";
						break;
					}
					else if (s.find(s0) == std::string::npos) {
						tmp = "";
						break;
					}
					else
						listRegexPlus00.emplace_back(s.substr(1, s.length() - 2));

				__debugPrint(logFile, "%d %s: tmp = %s\n", __LINE__, __FUNCTION__, tmp.c_str());

				if (tmp.length() == 0)
					continue;

				__debugPrint(logFile, "%d reach half: %s\n", __LINE__, tmp.c_str());
				/* */
				for (const auto& var : eqToStr) {

					if (var.first.compare(args[0]) != 0)
						for (unsigned i = 0; i < var.second.size(); ++i)
							if (var.second[i].compare(tmp) == 0) {
								/* check matching one more time */
								assert (equalitiesMap[var.first].size() > i);
								std::vector<std::string> listRegexPlus01;
								for (const auto& s : equalitiesMap[var.first][i])
									if (s[0] == '"') {
										if (s.find(s1) != std::string::npos)
											listRegexPlus01.emplace_back(s.substr(1, s.length() - 2));
									}
								if (listRegexPlus00.size() == listRegexPlus01.size()) {
									for (unsigned i = 0; i < listRegexPlus00.size(); ++i) {
										assert(constMap.find(listRegexPlus00[i]) != constMap.end());
										result += "(= " + constMap[listRegexPlus00[i]] + "__p0 " + constMap[listRegexPlus01[i]] +"__p0) ";
										__debugPrint(logFile, "%d %s vs %s\n", __LINE__, listRegexPlus00[i].c_str(), listRegexPlus01[i].c_str());
									}
									__debugPrint(logFile, "%d >> %s: %s\n", __LINE__, __FUNCTION__, result.c_str());

								}
								else
									assert (listRegexPlus01.size() == 0);
							}
				}
			}
		}
		if (result.length() > 0) {
			return "(and " + result + ")";
		}
	}
	return "true";
}

/*
 *
 */
std::string create_constraints_NOTContain(std::string var, std::string value){
	std::string lenName = generateVarLength(var);
	std::string arrName = generateVarArray(var);

	allVariables.emplace(var);

	std::vector<std::string> andConstraints;
	/*
	 * and (or ( | x | < 5 ; x_5 != .. ; x_4 != .. ))
	 * 		or ( | x | < 4 ; x_4 != .. ; x_3 != .. ))
	 * 		or ( | x | < 3 ; x_3 != .. ; x_2 != .. ))
	 * 		..
	 * )
	 * */
	int maxSize = findVariableSize(var) * MAXQ;
	for (unsigned i = value.length() - 2; i <= (unsigned)std::min(CONNECTSIZE, maxSize); ++i){
		std::vector<std::string> tmp;
		tmp.emplace_back("(< " + lenName + " " + std::to_string(i) + " )");

		for (unsigned int k = 0; k < value.length() - 2; ++k) {
			unsigned int pos = k + i - value.length() + 2;
			tmp.emplace_back("(not (= (select " + arrName + " " + std::to_string(pos) + ") " + std::to_string(value[k + 1]) + "))");
		}
		andConstraints.emplace_back(orConstraint(tmp));
	}

	andConstraints.emplace_back("(< " + lenName + " " + std::to_string(std::min(CONNECTSIZE, maxSize)) + " )");
	__debugPrint(logFile, "%d *** %s ***: %s\n%s\n", __LINE__, __FUNCTION__, value.c_str(), andConstraint(andConstraints).c_str());

	return andConstraint(andConstraints);
}



/*
 *
 */
std::string create_constraints_NOTEqual(
		std::string str00,
		std::string str01){
	__debugPrint(logFile, "%d *** %s ***: NOTEqual %s %s\n", __LINE__, __FUNCTION__, str00.c_str(), str01.c_str());
	bool isConst_00 = false;
	bool isConst_01 = false;
	if (str00[0] == '\"' )
		isConst_00 = true;

	if (str01[0] == '\"')
		isConst_01 = true;

	assert(!(isConst_00 && isConst_01));

	std::vector<std::string> orConstraints;
	std::vector<std::string> andConstraints;

	std::string ret = "";

	if (isConst_00 || isConst_01) {
		if (isConst_01) {
			/* swap */
			std::string tmp = str00;
			str00 = str01;
			str01 = tmp;
		}

		std::string len01 = generateVarLength(str01);
		std::string arr01 = generateVarArray(str01);

		/* != "a" b */
		orConstraints.emplace_back("(not (= " + len01 + " " + std::to_string((int)str00.length() - 2) + "))");

		/* (length a != 0 && ...) || length b = 1 && ...*/
		if (str00.length() > 2) {
			for (unsigned int j = 1; j < str00.length() - 1; ++j) {
				orConstraints.emplace_back("(not (= (select " + arr01 + " " + std::to_string(j - 1) + ") " + std::to_string((int)str00[j]) + "))");
			}
		}

		ret = orConstraint(orConstraints);

	}
	else {
		bool concat00 = str00.find("(Concat") != std::string::npos;
		bool concat01 = str01.find("(Concat") != std::string::npos;
		if (!concat00 && !concat01) {
			std::string len00 = generateVarLength(str00);
			std::string len01 = generateVarLength(str01);
			std::string arr00 = generateVarArray(str00);
			std::string arr01 = generateVarArray(str01);
			/* != "a" b */
			orConstraints.emplace_back("(not (= " + len00 + " " + len01 + "))");

			for (unsigned int i = 1; i < CONNECTSIZE; ++i){
				/*len a = len b <= i || a[i - 1] == b [i-1] */
				std::string tmp = "";
				tmp = tmp + "(< " + len00 + " " + std::to_string(i) + ") ";
				tmp = tmp + "(= (select " + arr00 + " " + std::to_string(i - 1) + ") (select " + arr01 + " " + std::to_string(i - 1) + "))";
				tmp = "(or " + tmp + ")";
				andConstraints.emplace_back(tmp);
			}
			orConstraints.emplace_back("(not " + andConstraint(andConstraints) + ")");
			ret = orConstraint(orConstraints);
		}
		else {
			// TODO not equal concat
			ret = "true";
		}
	}

	__debugPrint(logFile, "%d >> %s\n", __LINE__, ret.c_str());
	return ret;
}

/*
 *
 */
std::string create_constraints_ToLower(std::string str00, std::string str01){
	std::string len00 = generateVarLength(str00);
	std::string len01 = generateVarLength(str01);
	std::string arr00 = generateVarArray(str00);
	std::string arr01 = generateVarArray(str01);

	std::vector<std::string> andConstraints;

	for (unsigned int i = 1; i < CONNECTSIZE; ++i){
		/*len a <= i || a[i - 1] == b [i-1] */
		/*len a = len b <= i || a[i - 1] == b [i-1] */
		std::string tmp = "";
		tmp = tmp + "(< " + len00 + " " + std::to_string(i) + ") ";
		tmp = tmp + "(ite (and (<= 65 (select " + arr00 + " " + std::to_string(i - 1) + ")) (>= 90 (select " + arr00 + " " + std::to_string(i - 1) + ")))";
		tmp = tmp + " (= (+ (select " + arr00 + " " + std::to_string(i - 1) + ") 32) (select " + arr01 + " " + std::to_string(i - 1) + "))";
		tmp = tmp + " (= (select " + arr00 + " " + std::to_string(i - 1) + ") (select " + arr01 + " " + std::to_string(i - 1) + ")))";
		tmp = "(or " + tmp + ")";
		andConstraints.emplace_back(tmp);
	}
	return andConstraint(andConstraints);
}

/*
 *
 */
std::string create_constraints_ToUpper(std::string str00, std::string str01){
	std::string len00 = generateVarLength(str00);
	std::string len01 = generateVarLength(str01);
	std::string arr00 = generateVarArray(str00);
	std::string arr01 = generateVarArray(str01);

	std::vector<std::string> andConstraints;

	for (unsigned int i = 1; i < CONNECTSIZE; ++i){
		/*len a <= i || a[i - 1] == b [i-1] */
		/*len a = len b <= i || a[i - 1] == b [i-1] */
		std::string tmp = "";
		tmp = tmp + "(< " + len00 + " " + std::to_string(i) + ") ";
		tmp = tmp + "(ite (and (<= 97 (select " + arr00 + " " + std::to_string(i - 1) + ")) (>= 122 (select " + arr00 + " " + std::to_string(i - 1) + ")))";
		tmp = tmp + " (= (- (select " + arr00 + " " + std::to_string(i - 1) + ") 32) (select " + arr01 + " " + std::to_string(i - 1) + "))";
		tmp = tmp + " (= (select " + arr00 + " " + std::to_string(i - 1) + ") (select " + arr01 + " " + std::to_string(i - 1) + ")))";
		tmp = "(or " + tmp + ")";
		andConstraints.emplace_back(tmp);
	}
	return andConstraint(andConstraints);
}


/*
 *
 */
void handle_NOTContains(
		std::map<StringOP, std::string> rewriterStrMap){
	std::map<std::pair<std::string, std::string>, bool> done;
	for (const auto& element : rewriterStrMap){
		if (element.first.name.compare("Contains") == 0){
			if (element.second.compare("false") == 0){
				if (element.first.arg01.find("Concat ") != std::string::npos ||
						element.first.arg02.find("Concat ") != std::string::npos ||
						element.first.arg02.find("Automata ") != std::string::npos)
					continue;
				if (canSkipNotContain(element.first.arg01, element.first.arg02, rewriterStrMap)){
					continue;
				}
				std::string value02 = getPossibleValue(element.first.arg02);
				std::string value01 = getPossibleValue(element.first.arg01);
				__debugPrint(logFile, "%d *** %s ***: %s -- %s\n", __LINE__, __FUNCTION__, value01.c_str(), value02.c_str());
				if (value02.compare("!FoUnD") != 0 && value01.compare("!FoUnD") == 0 &&
						done.find(std::make_pair(element.first.arg01, value02)) == done.end()) {

					global_smtStatements.push_back({create_constraints_NOTContain(element.first.arg01, value02)});

					done[std::make_pair(element.first.arg01, value02)] = true;
				}
				else if (value02.compare("!FoUnD") == 0 && value01.compare("!FoUnD") != 0 &&
						done.find(std::make_pair(value01, element.first.arg02)) == done.end()) {
					// TODO handle_NOTContains
				}
				else if (value02.compare("!FoUnD") != 0 && value01.compare("!FoUnD") != 0) {
					/* const vs const */
					if (value01.find(value02.substr(1, value02.length() - 2)) == std::string::npos)
						return;
					else
						global_smtStatements.push_back({"false"});
				}
				else {
					// not handle this case
				}
			}
		}
	}
}

/*
 *
 */
void handle_NOTEqual(
		std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare("=") == 0 && s.second.compare("false") == 0){
			global_smtStatements.push_back({create_constraints_NOTEqual(s.first.arg01, s.first.arg02)});
		}
	}
}
/**
 * handle startswith constraints
 */
void handle_StartsWith(
		std::map<StringOP, std::string> rewriterStrMap){

	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare("StartsWith") == 0){
			global_smtStatements.push_back({create_constraints_StartsWith(s.first.arg01, s.first.arg02, s.second)});
		}
	}
}

/**
 * handle endswith constraints
 */
void handle_EndsWith(
		std::map<StringOP, std::string> rewriterStrMap){

	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare("EndsWith") == 0){
			global_smtStatements.push_back({create_constraints_EndsWith(s.first.arg01, s.first.arg02, s.second)});
		}
	}
}

/*
 * handle replace constraints
 * TODO handle_Replace
 */
void handle_Replace(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare("Replace") == 0){
		}
	}
}

/*
 * handle replace constraints
 * TODO handle_ReplaceAll
 */
void handle_ReplaceAll(std::map<StringOP, std::string> rewriterStrMap){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	/* prepare */
	std::map<std::string, std::vector<std::string>> eqToStr;
	for (const auto& var : equalitiesMap) {

		for (const auto& l : var.second) {
			std::string tmp = "";
			for (const auto s : l)
				if (s[0] != '"')
					tmp = tmp + s;
			eqToStr[var.first].emplace_back(tmp);
		}
	}

	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare("ReplaceAll") == 0){
			std::vector<std::string> args = {s.first.arg01, s.first.arg02, s.first.arg03};
			global_smtStatements.push_back({create_constraints_ReplaceAll(args, s.second, eqToStr)});
		}
	}
}
/*
 *
 */
void handle_ToUpper(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& s : rewriterStrMap) {
		if (s.second.compare("upper") == 0){
			global_smtStatements.push_back({create_constraints_ToUpper(s.first.arg01, s.first.arg02)});
		}
	}
}

/*
 *
 */
void handle_ToLower(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& s : rewriterStrMap) {
		if (s.second.compare("lower") == 0){
			global_smtStatements.push_back({create_constraints_ToLower(s.first.arg01, s.first.arg02)});
		}
	}
}

/*
 * define array for connected variable
 */
void create_constraints_array(std::vector<std::string> &defines, std::vector<std::string> &constraints){
	for (const auto& s : connectedVariables){
		defines.emplace_back("(declare-const arr_" + s + " (Array Int Int))");
//		constraints.emplace_back("(assert (< " + generateVarLength(s) + " " + std::to_string(100) +"))");
	}
}

/*
 * define array for connected variable
 */
void create_const_array(
		std::vector<std::string> &defines,
		std::vector<std::string> &constraints){

	for (std::map<std::string, std::string>::iterator it = constMap.begin(); it != constMap.end(); ++it){
		defines.emplace_back("(declare-const arr_" + it->second + " (Array Int Int))");
		if (!isRegexStr(it->first))
			for (unsigned int i = 0 ; i < it->first.length(); ++i) {
				constraints.emplace_back("(assert (= (select arr_" + it->second + " " + std::to_string(i) + ") " + std::to_string(it->first[i]) + "))");
			}
		else {
			std::string regexContent = parse_regex_content(it->first);
			std::vector<std::string> components = collectAlternativeComponents(regexContent);
			std::string constraint = "";
			for (const auto& c: components) {
				constraint = constraint + "\t (and ";
				for (unsigned int j = 0 ; j < c.length(); ++j) {
					constraint = constraint + ("(= (select arr_" + it->second + " " + std::to_string(j) + ") " + std::to_string(c[j]) + ") ");
				}
				constraint = constraint + ")\n";
			}
			constraint = "(assert (or \n" + constraint + "\n))";
			constraints.emplace_back(constraint);
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
	__debugPrint(logFile, "%d *** %s ***: %d\n", __LINE__, __FUNCTION__, regexCnt);
	for (int i = 0 ; i < regexCnt; ++i) {
		defines.emplace_back("(declare-const __regex_" + std::to_string(i) + " Int)");
		constraints.emplace_back("(assert (>= __regex_" + std::to_string(i) + " 0))");
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

			defines.emplace_back("(declare-const len_" + it->second + " Int)");
			/* len_x = sum(len_x_i)*/
			std::string lenX = "";
			std::string varName = "len_" + it->second + "_";
			if ( it->first.length() <= SPLIT_UNDER_BOUND - 2) { /* -2 because of "xxxx" */
				defines.emplace_back("(declare-const len_" + it->second + "_" + "1 Int)");
				constraints.emplace_back("(assert (>= len_" + it->second + "_" + "1 0))");
				lenX = varName + "1 0";
			}
			else for (int i = 1; i <= QCONSTMAX; ++i) {
				defines.emplace_back("(declare-const len_" + it->second + "_" + std::to_string(i) + " Int)");
				constraints.emplace_back("(assert (>= len_" + it->second + "_" + std::to_string(i) + " 0))");
				lenX = lenX + varName + std::to_string(i) + " ";
			}

			/* (+ sum(len_x_i) */
			if (QCONSTMAX > 1)
				lenX = "(+ " + lenX + ")";

			std::string lenName = std::to_string(it->first.length());
			/*(assert (= const (+ sum(len_x_i)))) */
			constraints.emplace_back("(assert (= " + lenName + " " + lenX  + "))");
			constraints.emplace_back("(assert (= " + lenName + " len_" + it->second  + "))");
		}
		else {
			defines.emplace_back("(declare-const len_" + it->second + "_" + std::to_string(std::abs(REGEX_CODE)) + " Int)");

			if (it->first.find("+") != std::string::npos)
				constraints.emplace_back("(assert (> len_" + it->second + "_" + std::to_string(std::abs(REGEX_CODE)) + " 0))");
			else {
				assert(it->first.find("*") != std::string::npos);
				constraints.emplace_back("(assert (>= len_" + it->second + "_" + std::to_string(std::abs(REGEX_CODE)) + " 0))");
			}

			create_constraints_regex(defines, constraints, it->first, it->second);
		}
}

/*
 * var name -> define var
 * (declare-const len_var_0 Int)
 * (declare-const len_var_0 Int)regexContent
 *
 * len_var = sum(len_var_0)
 * len_var_0 >= 0
 *
 */
void create_constraints_strVar(std::vector<std::string> &defines, std::vector<std::string> &constraints){
	for (const auto& var: allVariables){

		/* len_x = sum(len_x_i)*/
		std::string lenX = "";
		std::string lenVarName = generateVarLength(var);
		for (int i = 0; i < QMAX; ++i) {
			defines.emplace_back("(declare-const " + lenVarName + "_" + std::to_string(i) + " Int)");
			constraints.emplace_back("(assert (>= " + lenVarName + "_" + std::to_string(i) + " 0))");
			constraints.emplace_back("(assert (< " + lenVarName + "_" + std::to_string(i) + " 270))");
			lenX += lenVarName;
			lenX += "_";
			lenX += std::to_string(i);
			lenX += " ";
		}

		/* (+ sum(len_x_i) */
		if (QMAX > 1)
			lenX = "(+ " + lenX + ")";

		//constraints.emplace_back("(assert (< " + lenVarName + " 300))");
		constraints.emplace_back("(assert (= " + lenVarName + " " + lenX  + "))");

		if (var.find("__flat_") != std::string::npos || var.substr(0, 6).compare("$$_str") == 0) {
			/* they are internal variables */
			defines.emplace_back("(declare-const " + lenVarName + " Int)");
		}
	}
}

/*
 * len_const = (a * 1) + (b * 2) + ...
 */
void create_constraints_regex(std::vector<std::string> &defines, std::vector<std::string> &constraints, std::string regex, std::string name){
	__debugPrint(logFile, "%d *** %s ***: %s --> %s\n", __LINE__, __FUNCTION__, regex.c_str(), name.c_str());
	std::vector<std::string> components = collectAlternativeComponents(parse_regex_content(regex));

	assert(components.size() > 0);
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, regex.c_str());
	displayListString(components, "components");
	std::set<int> componentSizes;
	for (const auto& c: components)
		componentSizes.emplace(c.length());

	int cnt = 0;
	std::string constraint = "(assert (= len_" + name + "_" + std::to_string(std::abs(REGEX_CODE)) + " (+ ";
	for (const auto& size : componentSizes){
		std::string tmp = name + "__p" + std::to_string(cnt++);
		defines.emplace_back("(declare-const " + tmp + " Int)");
		constraint = constraint + "(* " + tmp + " " + std::to_string(size) + ") ";
	}
	constraint += ") ) )";
	constraints.emplace_back(constraint);
}

/*
 * len_x = sum(len_y)
 */
std::string createLengthConstraintForAssignment(std::string x, std::vector<std::string> components){
	if (components.size() == 0)
		return "";

	std::string lenX = "";
	int cnt = 0;
	for (const auto& component: components){
		if (component[0] != '\"'){ /* not a const */
			lenX = lenX + " len_" + component;
			cnt ++;
		}
		else if (component.length() > 2) { /* const is not an empty string */
			if(!isRegexStr(component)) {
				lenX = lenX + " " + std::to_string(component.length() - 2);
				cnt ++;
			}
			else {
				/* regex */
				assert(constMap.find(component.substr(1, component.length() - 2)) != constMap.end());
				lenX = lenX + " len_" + constMap[component.substr(1, component.length() - 2)] + "_" + std::to_string(abs(REGEX_CODE));
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
		else {
			lenX = "(= " + std::to_string(parse_regex_content(x.substr(1, x.length() - 2)).length()) + " " + lenX  + ")";
		}
	}

	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, lenX.c_str());

	return lenX;
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
	for (const auto& s : smtVarDefinition) {
		out << s << std::endl;
		out.flush();
	}

	for (const auto& s : constraints) {
		out << s << std::endl;
		out.flush();
	}

	/* repeated variables */
	for (unsigned int i = 0; i < repeatedVariableConstraints.size(); ++i) {
		out << repeatedVariableConstraints[i] << std::endl;
		out.flush();
	}

	/* assertions for flat automata*/
	for (const auto& s : global_smtStatements){
		if (s.size() == 1) {
			out << "(assert " << s[0] << " )\n";
		}
		else {
			out << "(assert " << orConstraint(s) << " )\n";
		}
		out.flush();
	}

	/* copy assertions from smt file */
	for (unsigned int i = 0 ; i < smtLenConstraints.size(); ++i) {
		out << smtLenConstraints[i];
		out.flush();
	}

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

	out << "(get-model)\n";
	out.flush();
	out.close();
}

void printSatisfyingAssignments(
		std::map<std::string, std::string> strValue,
		std::map<std::string, std::string> intResultMap
		){
	printf("Collecting concrete values\n");
	printf("================================================\n");

	for (const auto& def : smtVarDefinition){
		std::vector<std::string> tokens = parse_string_language(def, " ");

		std::string value = intResultMap[tokens[1]];
		if (value.length() > 0 &&
				tokens[1].find("$$") == std::string::npos &&
				tokens[1].find("__flat_") == std::string::npos) {
			if (tokens[1].substr(0, 4).compare("len_") == 0) {
			}
			else {
				printf("%s : %s\n", tokens[1].c_str(), value.c_str());
			}
		}
	}

	for (const auto& value : strValue)
		if (value.first.find("$$") == std::string::npos &&
				value.first.find("__flat_") == std::string::npos &&
				value.first.find("const") != 0 &&
				value.first[0] != '"'){
			printf("%s : %s\n", value.first.c_str(), value.second.c_str());
		}
	printf("------------------------------------------------\n");
}

/*
 * write & verify to file output
 */
void verifyOutput(std::string outFile,
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<std::string, std::string> lengthResultMap,
		std::map<std::string, std::string> strValue){
	assert(lengthResultMap.size() > 0);

	std::vector<std::string> additionalAssertions;

	__debugPrint(logFile, " *** %s *** \n", __FUNCTION__);

	/* length assertions */
	for (const auto& def : smtVarDefinition){
		std::vector<std::string> tokens = parse_string_language(def, " ");

		std::string value = lengthResultMap[tokens[1]];

		__debugPrint(logFile, "%d %s %s\n", __LINE__, def.c_str(), value.c_str());
		if (value.length() > 0 &&
				tokens[1].find("$$") == std::string::npos &&
				tokens[1].find("__flat_") == std::string::npos) {
			if (tokens[1].substr(0, 4).compare("len_") == 0) {
				std::string tmp = def.substr(4);
				additionalAssertions.emplace_back("(assert (= (Length " + tokens[1].substr(4) +") " + value + "))\n");
			}
			else {
				additionalAssertions.emplace_back("(assert (= " + tokens[1] + " " + value + "))\n");
			}
		}
	}

	for (const auto& value : strValue)
		if (value.first.find("$$") == std::string::npos &&
				value.first.find("__flat_") == std::string::npos &&
				value.first.find("const") != 0 &&
				value.first[0] != '"'){
			additionalAssertions.emplace_back("(assert (= " + value.first + " \"" + value.second + "\"))\n");
		}

	/* read & copy the input file */
	addConstraintsToSMTFile(NONGRM, _equalMap, additionalAssertions, outFile);
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
	//	displayListString(cases, " print cases");
	std::pair<std::vector<std::string>, std::map<std::string, int>> result = std::make_pair(cases, newVars);
	if (cases.size() == 0)
		newVars.clear();
	return result;
}

/*
 * print input
 */
void printEqualMap(std::map<std::string, std::vector<std::vector<std::string>>> equalMap) {
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalMap.begin();
			it != equalMap.end(); ++it) {
		__debugPrint(logFile, "%s = (%ld cases) \n", it->first.c_str(), it->second.size());
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
						anEq.emplace_back(collectConst(it->second[i][j]));
				}
				else {/* skip const */
					if (varLength.find(it->second[i][j]) == varLength.end() || /* does not know its length */
							(varLength.find(it->second[i][j]) != varLength.end() && varLength[it->second[i][j]] > 0)) /* or length > 0 */ {

						anEq.emplace_back(it->second[i][j]);
						allVariables.insert(it->second[i][j]);
					}
				}
			}
			setOfEQ.emplace_back(anEq);
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
 * Remove common prefix and suffix
 */
std::string stringDiff(std::string a, std::string b){
	unsigned pre = 0, suf = a.length() - 1;
	while (pre < a.length() && pre < b.length() && a[pre] == b[pre])
		++pre;
	while (suf >= 0 && a[suf] == b[b.length() - (a.length() - suf)])
		--suf;

	if (pre >= suf)
		return "";
	else
		return a.substr(pre, suf - pre + 1);
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
	for (const auto& _eq :  equalitiesMap) {
		std::vector<std::vector<std::string>> tmp_vector;
		for (const auto& vt : _eq.second){
			std::vector<std::string> elements;
			std::string tmpStr = "";
			/* push to map */
			for (const auto& s : vt) {
				if (s[0] == '\"') {
					/* prevent the case: (abc)*  + def */
					if (isRegexStr(s)) {
						std::vector<std::string> localElements;
						/* reuse the parse result */
						if (parserMap.find(s) != parserMap.end())
							localElements = parserMap[s];
						else {
							/* update regex */
							unsigned tmpPos = s.length() - 1;
							std::string indexStr = "";
							for (tmpPos = s.length() - 1; tmpPos >= 0; --tmpPos)
								if (s[tmpPos] == '\"') {
									break;
								}
								else if (s[tmpPos] >= '0' && s[tmpPos] <= '9')
									indexStr = s[tmpPos] + indexStr;
							int index = atoi(indexStr.c_str());
							assert(index >= 0);

							std::string content = s.substr(1, tmpPos - 1);

							__debugPrint(logFile, "%d content = %s, index = %d\n", __LINE__, content.c_str(), index);
							/* parse this regex */
							std::vector<std::vector<std::string>> regexElements = combineConstStr(refineVectors(parseRegexComponents(underApproxRegex(content))));

							/* assume that regexElements size is 1 */
							assert(regexElements.size() >= 1);

							if (regexElements.size() > 1)
								__debugPrint(logFile, "%d IMPORTANT NOTE: regexElements size = %ld\n", __LINE__, regexElements.size());

							unsigned int pos = 0;

							/* add to vector, create a sum for two continuous elements */
							while (pos < regexElements[0].size()){
								if (isRegexStr(regexElements[0][pos])) {
									localElements.emplace_back("\"" + regexElements[0][pos] + "___" + std::to_string(index) + "\"");
								}
								else {
									localElements.emplace_back(regexElements[0][pos]);
								}
								pos++;
							}

							parserMap[s] = localElements;
						}

						displayListString(localElements, " localElements list ");
						displayListString(elements, " elements list ");

						/*push to elements list */
						/* 1. handle the connecter point: tmpStr and first of local elements are const, sum them */
						bool constConnector = false;
						std::string firstOfLocalElements = localElements[0];
						if (firstOfLocalElements[0] == '\"' && !isRegexStr(firstOfLocalElements)){
							tmpStr =  tmpStr + firstOfLocalElements.substr(1, firstOfLocalElements.length() - 2);
							constConnector = true;
						}

						/* 2. add tmp the list */
						if (tmpStr.length() > 0) {
							elements.emplace_back("\"" + tmpStr + "\"");
							tmpStr = "";
						}

						if (constConnector == false)
							elements.insert(elements.end(), localElements.begin(), localElements.end());
						else {
							for (unsigned int kk = 1; kk < localElements.size(); ++kk)
								elements.emplace_back(localElements[kk]);
						}
					}
					else /* meet const str */
						tmpStr = tmpStr + s.substr(1, s.length() - 2);
				}
				else { /* meet variable */
					if (tmpStr.length() > 0) {
						elements.emplace_back("\"" + tmpStr + "\"");
						tmpStr = "";
					}
					elements.emplace_back(s);
				}
			}

			if (tmpStr.length() > 0) {
				elements.emplace_back("\"" + tmpStr + "\"");
				tmpStr = "";
			}

			if (elements.size() > 0)
				tmp_vector.emplace_back(elements);
		}
		new_eqMap[_eq.first] = tmp_vector;
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
//					if (isRegexStr(content)) {
//						content = content + "__" + std::to_string(constCnt);
//					}
					__debugPrint(logFile, "%d %s: add const to map: %s\n", __LINE__, __FUNCTION__, content.c_str());
					constMap[content] = "const_" + std::to_string(constCnt++);
				}
		}
	}
}

/*
 * Find connected variables
 * They are variables that are used by more than one variables
 */

void collectConnectedVariables(std::map<StringOP, std::string> rewriterStrMap){
	std::map<std::string, std::vector<std::string>> usedComponents;
	std::set<std::string> connectedVarSet;

	/* collect from equality map */
	for (const auto& eq : equalitiesMap) {
		if (eq.second.size() <= 1)
			continue;

		if (eq.second.size() > 4) {
			connectedVarSet.insert(eq.first);
			__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, eq.first.c_str());
		}

		std::map<std::string, std::vector<std::string>> tmpUsedComponents;
		for (const auto& v : eq.second)
			if (v.size() > 1){

				/* push to map */
				for (const auto& var : v)
					if (var[0] != '\"') {
						/* check if component is already in the map*/
						if (usedComponents.find(var) != usedComponents.end()) {
							if (!equalVector(v, usedComponents[var])){
								connectedVarSet.insert(var);
								__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, var.c_str());
							}
						}
						else {
							/* check the local equalities */
							std::vector<std::string> lhs;
							std::vector<std::string> rhs;
							for (const auto& v1 : eq.second) {
								optimizeEquality(v1, v, lhs, rhs);
								if (std::find(rhs.begin(), rhs.end(), var) != rhs.end() &&
										std::find(lhs.begin(), lhs.end(), var) != lhs.end()){
									connectedVarSet.insert(var);
									__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, var.c_str());
									break;
								}
							}

							tmpUsedComponents[var] = v;
						}
					}
			}

		usedComponents.insert(tmpUsedComponents.begin(), tmpUsedComponents.end());
	}

	/* from rewriterMap */
	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare("StartsWith") == 0 ||
				s.first.name.compare("EndsWith") == 0 ||
				s.first.name.compare("Replace") == 0 ||
				s.first.name.compare("ReplaceAll") == 0 ||
				(s.first.name.compare("Contains") == 0 && s.second.compare("false") == 0) ||
				(s.first.name.compare("=") == 0 && (s.second.compare("false") == 0 || s.second.compare("upper") == 0 || s.second.compare("lower") == 0))){
			if (s.first.arg01.find("Concat ") != std::string::npos ||
					s.first.arg02.find("Concat ") != std::string::npos ||
					s.first.arg02.find("Automata ") != std::string::npos)
				continue;

			if (s.first.name.compare("=") == 0 && s.second.compare("false") == 0)
				if (s.first.arg01.compare("\"\"") == 0 || s.first.arg02.compare("\"\"") == 0)
					continue;

			StringOP op = s.first;
			__debugPrint(logFile, "%d %s -> %s -- %s\n", __LINE__, op.toString().c_str(), s.first.arg01.c_str(), s.first.arg02.c_str());
			/* add all of variables to the connected var set*/
			if (s.first.arg01[0] != '\"') {
				connectedVarSet.emplace(s.first.arg01);
				__debugPrint(logFile, "%d Adding %s to connectedVar\n", __LINE__, s.first.arg01.c_str());
			}
			if (s.first.arg02[0] != '\"') {
				connectedVarSet.emplace(s.first.arg02);
				__debugPrint(logFile, "%d Adding %s to connectedVar\n", __LINE__, s.first.arg02.c_str());
			}
		}
	}

	connectedVariables.insert(connectedVarSet.begin(), connectedVarSet.end());

	/* a = b, a is a connected var --> b is connected var */
		for (const auto& eq : equalitiesMap)
			if (connectedVariables.find(eq.first) != connectedVariables.end()){
				for (const auto& v : eq.second)
					if (v.size() == 1){
						if (v[0][0] != '"')
							connectedVariables.emplace(v[0]);
					}
		}

	/* print test connected var */
	if (connectedVariables.size() > 0) {
		__debugPrint(logFile, "%d *** %s ***:\n", __LINE__, __FUNCTION__);

		for (const auto& s : connectedVariables){
			__debugPrint(logFile, "%s\n", s.c_str());
		}
		__debugPrint(logFile, "\n");
	}
}

/*
 * Remove all equalities without connected variables and consts
 */
void refineEqualMap(){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	std::map<std::string, std::vector<std::vector<std::string>>> new_eqMap;

	/* remove duplications */
	for (const auto& varEq: equalitiesMap) {
		if (connectedVariables.find(varEq.first) == connectedVariables.end() && varEq.first.find("$$") != std::string::npos)
			continue;

		std::vector<std::vector<std::string>> tmp_vector;
		std::vector<std::string> backup;
		for (const auto& _eq : varEq.second){
			/* x = x: remove if "x" is not a connected var */
			if (_eq.size() == 1 &&
					_eq[0].compare(varEq.first) == 0) {
				if (connectedVariables.find(_eq[0]) == connectedVariables.end()) {
					__debugPrint(logFile, "%d *** %s ***: remove %s\n", __LINE__, __FUNCTION__, _eq[0].c_str());
					continue;
				}
				else {
					if (varEq.second.size() == 1) {
						__debugPrint(logFile, "%d *** %s ***: remove %s\n", __LINE__, __FUNCTION__, _eq[0].c_str());
						continue;
					}
				}
			}

			/* push to map */
			for (unsigned int k = 0; k < _eq.size(); ++k) {
				if (_eq[k][0] == '\"' /* const */ ||
						connectedVariables.find(_eq[k]) != connectedVariables.end()) {
					tmp_vector.emplace_back(_eq);
					break;
				}
			}

			if (_eq.size() > 1 ||
					(_eq.size() == 1 && _eq[0].compare(varEq.first) != 0))
				backup = _eq;
		}

		/* add to create length constraint */
		if (tmp_vector.size() == 0 ||
				(tmp_vector.size() == 1 && connectedVariables.find(varEq.first) != connectedVariables.end())){
			if (backup.size() > 0) {
				tmp_vector.emplace_back(backup);
			}
		}

		/* remove all duplications in tmp_vector */
		std::vector<std::vector<std::string>> tmp_vector01;
		for (unsigned int i = 0; i < tmp_vector.size(); ++i){
			bool notAdd = false;
			for (unsigned int j = 0; j < i; ++j){
				if (equalVector(tmp_vector[i], tmp_vector[j])) {
					notAdd = true;
					break;
				}
			}
			if (notAdd == false)
				tmp_vector01.emplace_back(tmp_vector[i]);
		}

		if (tmp_vector01.size() > 0)
			new_eqMap[varEq.first] = tmp_vector01;
	}

	equalitiesMap.clear();
	equalitiesMap = new_eqMap;

	printEqualMap(equalitiesMap);
}

/*
 *
 */
std::map<std::string, std::string> decodeResultMap(std::map<std::string, std::string> resultMap){
	std::map<std::string, std::string> update;
	for (const auto& element : resultMap){
		update[element.first] = decodeStr(element.second);
	}

	return update;
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
 * (a) --> a
 */
void removeExtraParentheses(std::string &s){
	while (s[0] == '(' && findCorrespondRightParentheses(0, s) == (int)s.length() - 1)
		s = s.substr(1, s.length() - 2);
}

/*
 * (a)|(b | c) --> {a, b, c}
 */
std::set<std::string> extendComponent(std::string s){
	__debugPrint(logFile, "%d *** %s ***: \"%s\"\n", __LINE__, __FUNCTION__, s.c_str());
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

/**
 * (abc|cde|ghi)*
 */
void optimizeFlatAutomaton(std::string &s){
	std::string org = s;
	std::string tmp = s.substr(1, s.length() - 3);
	std::set<std::string> ret = extendComponent(tmp);
	displayListString(ret, " *** optimizeFlatAutomaton ***");
	assert(ret.size() > 0);
	s = "";
	for (const auto& it: ret){
		s = s + "|" + it;
	}

	if (org[org.length() - 1] == '*')
		s = "(" + s.substr(1) + ")*";
	else if (org[org.length() - 1] == '+')
		s = "(" + s.substr(1) + ")+";
	else {
		__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, org.c_str());
		assert(false);
	}
}

/*
 *
 */
std::vector<std::vector<std::string>> parseRegexComponents(std::string str){
	__debugPrint(logFile, "%d *** %s ***: \"%s\"\n", __LINE__, __FUNCTION__, str.c_str());
	if (str.length() == 0)
		return {};

	std::vector<std::vector<std::string>> result;

	std::vector<std::string> components = collectAlternativeComponents(str);
	if (components.size() > 1){
		for (const auto& c : components) {
			std::vector<std::vector<std::string>> tmp = parseRegexComponents(c);
			assert(tmp.size() <= 1);
			if (tmp.size() == 1)
				result.emplace_back(tmp[0]);
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
		std::vector<std::vector<std::string>> rightComponents = parseRegexComponents(str.substr(leftParentheses));
		for (unsigned int i = 0; i < rightComponents.size(); ++i) {
			std::vector<std::string> tmp = {header};
			tmp.insert(tmp.end(), rightComponents[i].begin(), rightComponents[i].end());
			result.emplace_back(tmp);
		}
		return result;
	}

	int rightParentheses = findCorrespondRightParentheses(leftParentheses, str);
	if (rightParentheses < 0) {
		assert (false);
	}
	else if (rightParentheses == (int)str.length() - 1){
		/* (a) */
		removeExtraParentheses(str);
		return parseRegexComponents(str);
	}
	else if (rightParentheses == (int)str.length() - 2 && (str[str.length() - 1] == '*' || str[str.length() - 1] == '+')){
		/* (a)* */
		optimizeFlatAutomaton(str);
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
			std::vector<std::vector<std::string>> leftComponents = parseRegexComponents(left);
			std::vector<std::vector<std::string>> rightComponents = parseRegexComponents(right);
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
			result.emplace_back(list[i]);

	for (unsigned int i = 0; i < result.size(); ++i)
		for (unsigned int j = 0; j < result[i].size(); ++j)
			if (result[i][j][0] != '(')
				result[i][j] = "\"" + result[i][j] + "\"";
	return result;
}

/*
 * a b c (abc)* --> abc (abc)*
 */
std::vector<std::vector<std::string>> combineConstStr(std::vector<std::vector<std::string>> regexElements){
	std::vector<std::vector<std::string>> results;
	for (unsigned int i = 0; i < regexElements.size(); ++i) {
		std::vector<std::string> tmp;
		bool isRegex_prev = true;
		for (unsigned int j = 0; j < regexElements[i].size(); ++j) {
			if (isRegex_prev == false) {
				isRegex_prev = isRegexStr(regexElements[i][j]);
				if (isRegex_prev == false) {
					std::string tmpStr = tmp[tmp.size() - 1];
					std::string newStr = regexElements[i][j];
					tmp[tmp.size() - 1] = "\"" + tmpStr.substr(1, tmpStr.length() - 2) + newStr.substr(1, newStr.length() - 2) + "\"";
				}
				else
					tmp.emplace_back(regexElements[i][j]);
			}
			else {
				isRegex_prev = isRegexStr(regexElements[i][j]);
				tmp.emplace_back(regexElements[i][j]);
			}
		}
		results.emplace_back(tmp);
	}
	return results;
}
/*
 * Input: x . y
 * Output: flat . flat . flat . flat . flat . flat
 */
std::vector<std::pair<std::string, int>> createEquality(std::vector<std::string> list){
	std::vector<std::pair<std::string, int>> elements;

	for (unsigned int k = 0; k < list.size(); ++k)
		if (list[k][0] == '\"') {

			if (!isRegexStr(list[k])) {
				if (list[k].length() > SPLIT_UNDER_BOUND) /* const string */ {
					for (int j = 0; j < QCONSTMAX; ++j) { /* split variables into QMAX parts */
						elements.emplace_back(std::make_pair(list[k].substr(1, list[k].length() - 2), -(j + 1)));
					}
				}
				else {
					/* length < SPLIT_UNDER_BOUND */
					elements.emplace_back(std::make_pair(list[k].substr(1, list[k].length() - 2), -1));
				}
			}
			else {
				/* regex */
				std::string content = list[k].substr(1, list[k].length() - 2);

				elements.emplace_back(std::make_pair(content, REGEX_CODE));
			}
		}
		else {
			for (int j = 0; j < QMAX; ++j) { /* split variables into QMAX parts */
				elements.emplace_back(std::make_pair(list[k], j));
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
	std::vector<std::string> result;
	for (int i = 0 ; i < flatP; ++i) {
		std::string varName = "__flat_" + std::to_string(noFlatVariables + i);
		result.emplace_back(varName);
		connectedVariables.insert(varName);
		allVariables.insert(varName);
	}
	noFlatVariables += flatP;
	return result;
}

/*
 * cut the same prefix and suffix
 * */
void optimizeEquality(
		std::vector<std::string> lhs,
		std::vector<std::string> rhs,
		std::vector<std::string> &new_lhs,
		std::vector<std::string> &new_rhs){
	new_lhs.clear();
	new_rhs.clear();
	/* cut prefix */
	int prefix = -1;
	for (unsigned int i = 0; i < std::min(lhs.size(), rhs.size()); ++i)
		if (lhs[i].compare(rhs[i]) == 0)
			prefix = i;
		else
			break;

	/* cut suffix */
	int suffix = -1;
	for (unsigned int i = 0; i < std::min(lhs.size(), rhs.size()); ++i)
		if (lhs[lhs.size() - 1 - i].compare(rhs[rhs.size() - 1 - i]) == 0)
			suffix = i;
		else
			break;

	for (unsigned int i = prefix + 1; i < lhs.size() - suffix - 1; ++i)
		new_lhs.emplace_back(lhs[i]);

	for (unsigned int i = prefix + 1; i < rhs.size() - suffix - 1; ++i)
		new_rhs.emplace_back(rhs[i]);
}

/*
 *
 */
std::string constraintsIfEmpty(
		std::vector<std::string> lhs,
		std::vector<std::string> rhs){
	if (lhs.size() == 0 || rhs.size() == 0){
		std::string tmpStr = "";
		if (lhs.size() == 0)
			tmpStr = createLengthConstraintForAssignment("", rhs);
		if (rhs.size() == 0)
			tmpStr = createLengthConstraintForAssignment("", lhs);
		if (tmpStr.size() > 0)
			return tmpStr;
		else
			return "true";
	}
	return "";
}
/*
 * Pthread
 * Each thread handles a part in the global map from start -> end
 */
//void *convertEqualities(void *tid){
void convertEqualities(){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

//	int start, *mytid, end;
//	mytid = (int *) tid;
//	/* define elements that will be handled by this thread*/
//	start = (*mytid * (equalitiesMap.size() / NUM_THREADS));
//	if (*mytid != NUM_THREADS - 1)
//		end = start + (equalitiesMap.size() / NUM_THREADS);
//	else
//		end = equalitiesMap.size();

	/* return a number of results*/
//	auto startIt = std::next(equalitiesMap.begin(), start);
//	auto endIt = std::next(equalitiesMap.begin(), end);
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin();
			it != equalitiesMap.end();
			++it) {

		std::string tmp = " ";
		clock_t t;

		/* different tactic for size of it->second */
		const int flatP = 1;
		const int maxPConsidered = 6;
		unsigned maxLocal = 0;
		for (const auto& element : it->second) {
			unsigned cnt = 0;
			for (const auto& s : element)
				if (s[0] == '\"' || s.length() > 3)
					cnt++;

			maxLocal = cnt > maxLocal ? cnt : maxLocal;
		}

#ifdef PRINTTEST_UNDERAPPROX
		__debugPrint(logFile, "%d Max list size: %d\n", __LINE__, maxLocal);
#endif
		if (it->second.size() == 0)
			continue;
		assert (it->second[0].size() > 0);

//		pthread_mutex_lock (&smt_mutex);
		global_smtStatements.push_back({createLengthConstraintForAssignment(it->first, it->second[0])});
//		pthread_mutex_unlock (&smt_mutex);

		if (connectedVariables.find(it->first) != connectedVariables.end() || it->first[0] == '"'){
			std::vector<std::pair<std::string, int>> lhs_elements = createEquality({it->first});
			/* compare with others */
			for (const auto& element: it->second) {
				std::vector<std::pair<std::string, int>> rhs_elements = createEquality(element);
				t = clock();
				std::pair<std::vector<std::string>, std::map<std::string, int>> result = equalityToSMT(	sumStringVector({it->first}),
						sumStringVector(element),
						lhs_elements,
						rhs_elements
				);
				t = clock() - t;

//				pthread_mutex_lock (&smt_mutex);
#ifdef PRINTTEST_UNDERAPPROX
				__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
				if (result.first.size() != 0) {
					/* sync result */
					for (const auto& r : result.second)
						global_smtVars[r.first] = 'd';

					global_smtStatements.emplace_back(result.first);
				}
				else {
					__debugPrint(logFile, "%d trivialUnsat = true\n", __LINE__);
					/* trivial unsat */
					trivialUnsat = true;
				}
//				pthread_mutex_unlock (&smt_mutex);
			}

		}
		else if (maxLocal > maxPConsidered) {
			/* add an eq = flat . flat . flat, then other equalities will compare will it */
//			pthread_mutex_lock (&smt_mutex);
			std::vector<std::string> genericFlat = createSetOfFlatVariables(flatP);
			std::vector<std::pair<std::string, int>> lhs_elements = createEquality(genericFlat);
//			pthread_mutex_unlock (&smt_mutex);
			/* compare with others */
			for (const auto& element: it->second) {
				std::vector<std::pair<std::string, int>> rhs_elements = createEquality(element);
				t = clock();
				std::pair<std::vector<std::string>, std::map<std::string, int>> result = equalityToSMT(	sumStringVector(genericFlat),
						sumStringVector(element),
						lhs_elements,
						rhs_elements
				);
				t = clock() - t;

//				pthread_mutex_lock (&smt_mutex);
#ifdef PRINTTEST_UNDERAPPROX
				__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
				if (result.first.size() != 0) {
					/* sync result */
					for (const auto& r : result.second) {
						global_smtVars[r.first] = 'd';
					}
					global_smtStatements.emplace_back(result.first);
				}
				else {
					__debugPrint(logFile, "%d trivialUnsat = true\n", __LINE__);
					/* trivial unsat */
					trivialUnsat = true;
				}
//				pthread_mutex_unlock (&smt_mutex);
			}
		}
		else {

			/* work as usual */
			for (unsigned int i = 0; i < it->second.size(); ++i)
				for (unsigned int j = i + 1; j < it->second.size(); ++j) {
					/* optimize: find longest common prefix and posfix */
					std::vector<std::string> lhs;
					std::vector<std::string> rhs;
					optimizeEquality(it->second[i], it->second[j], lhs, rhs);

					if (lhs.size() == 0 || rhs.size() == 0){
						global_smtStatements.push_back({constraintsIfEmpty(lhs, rhs)});
						continue;
					}

					/* [i] = [j] */
					std::vector<std::pair<std::string, int>> lhs_elements = createEquality(lhs);
					std::vector<std::pair<std::string, int>> rhs_elements = createEquality(rhs);
					t = clock();
					std::pair<std::vector<std::string>, std::map<std::string, int>> result = equalityToSMT(	sumStringVector(it->second[i]),
							sumStringVector(it->second[j]),
							lhs_elements,
							rhs_elements
					);
					t = clock() - t;

//					pthread_mutex_lock (&smt_mutex);
#ifdef PRINTTEST_UNDERAPPROX
					__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
					if (result.first.size() != 0) {

						/* sync result*/
						for (const auto& smtVar : result.second) {
							global_smtVars[smtVar.first] = 'd';
						}
						global_smtStatements.emplace_back(result.first);
					}
					else {
						__debugPrint(logFile, "%d trivialUnsat = true\n", __LINE__);
						/* trivial unsat */
						trivialUnsat = true;
					}
//					pthread_mutex_unlock (&smt_mutex);
				}
		}

	}
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
			lhs_elements.emplace_back(std::make_pair("varX" + std::to_string(i), j));
			rhs_elements.emplace_back(std::make_pair("varY" + std::to_string(i), j));
		}

	lhs_elements.emplace_back(std::make_pair(frame, -1));
	// std::cout << tim::measure<>::execution(equalityToSMT, lhs_elements, rhs_elements) << std::endl;
}

/*
 *
 */
void createStringFromSet(std::set<std::string> list, int length, std::string &ret, bool &found){
	if ((int)ret.length() == length) {
		found = true;
		return;
	}
	for (const auto& s : list) {
		if ((int)ret.length() + (int)s.length() <= length){
			ret = ret + s;
			createStringFromSet(list, length, ret, found);
			if (found)
				return;
			else
				ret = ret.substr(0, ret.length() - s.length());
		}
	}
}

/*
 * len = 10, (ab)* --> abababababab
 */
std::string getValueFromRegex(std::string s, int length){
	size_t openPar = s.find('(');
	assert (openPar != std::string::npos);
	unsigned closePar = findCorrespondRightParentheses(openPar, s);
	std::set<std::string> components = extendComponent(s.substr(openPar + 1, closePar - openPar - 1));

	if(components.size() == 1) {
		std::string ret = "";
		bool found = false;
		createStringFromSet(components, length, ret, found);
		displayListString(components, " components ");
		__debugPrint(logFile, "%d *** %s ***: <%s, %d> -> %s\n", __LINE__, __FUNCTION__, s.c_str(), length, ret.c_str());
		if (found == true)
			return ret;
		else
			return "!fOuNd";
	}
	else
		/* TODO: not support yet */
		return "!fOuNd";
}

/*
 *
 */
bool isInternalVar(std::string varName){
	if (varName[varName.length() - 2] == '_' && varName[varName.length() - 1] >= '0' && varName[varName.length() - 1] <= '9')
				return true;
	return false;
}

/*
 *
 */
int getConstLength(
		std::string var,
		std::map<std::string, int> len){
	std::string actualName = var.substr(1, var.length() - 2);
	int length = len[constMap[actualName]];
	if (isRegexStr(actualName)) {
		length = len[constMap[actualName] + "_100"];
	}
	return length;
}

/*
 *
 */
std::vector<int> getDataStr(
		std::string var,
		std::map<std::string, std::vector<int>> strValue){
	std::string actualName = var.substr(1, var.length() - 2);
	assert (isRegexStr(actualName));
	if (strValue.find(constMap[actualName]) != strValue.end())
		return strValue[constMap[actualName]];
	else
		return std::vector<int>(5000, 0);
}
/*
 *
 */
void syncConst(
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	for (const auto& var : equalitiesMap){
		if (strValue.find(var.first) == strValue.end())
			strValue[var.first] = std::vector<int>(5000, 0);

		if (var.first[0] == '"') {
			if (!isRegexStr(var.first)){
				std::vector<int> tmp(5000, 0);
				for (unsigned i = 1; i < var.first.length() - 1; ++i)
					tmp[i - 1] = var.first[i];
				strValue[var.first] = tmp;
				forwardPropagate(var.first, len, strValue);
				backwardPropagarate(var.first, len, strValue);
				__debugPrint(logFile, ">> %d done synConst\n", __LINE__);
				continue;
			}
			else {
				assert(constMap.find(var.first.substr(1, var.first.length() - 2)) != constMap.end());
				std::string tmp = getValueFromRegex(var.first, getConstLength(var.first, len));
				if (tmp.compare("!fOuNd") != 0) {
					std::vector<int> tmpVector(5000, 0);
					for (unsigned i = 0; i < tmp.length(); ++i)
						tmpVector.emplace_back(tmp[i]);
					strValue[var.first] = tmpVector;
					forwardPropagate(var.first, len, strValue);
					backwardPropagarate(var.first, len, strValue);
					__debugPrint(logFile, ">> %d done synConst\n", __LINE__);
					continue;
				}
			}
		}

		bool update = false;
		for (const auto& eq : var.second){
			int pos = 0;
			for (const auto& s : eq){
				if (s[0] == '"') {
					if (!isRegexStr(s)) {
						/* assign value directly */
						for (unsigned i = 1; i < s.length() - 1; ++i)
							if (strValue[var.first][pos + i - 1] == 0) {
								strValue[var.first][pos + i - 1] = s[i];
								update = true;
							}
							else
								assert(strValue[var.first][pos + i - 1] == s[i]);
					}
					else {
						/* find value */
						assert(constMap.find(s.substr(1, s.length() - 2)) != constMap.end());
						std::string tmp = getValueFromRegex(s, getConstLength(s, len));
						if (tmp.compare("!fOuNd") != 0) {
							std::vector<int> tmpVector(5000, 0);
							for (unsigned i = 0; i < tmp.length(); ++i)
								tmpVector.emplace_back(tmp[i]);
							strValue[s] = tmpVector;
							forwardPropagate(s, len, strValue);
							backwardPropagarate(s, len, strValue);
							__debugPrint(logFile, ">> %d done synConst\n", __LINE__);

							for (unsigned i = 0; i < tmp.length(); ++i)
								if (strValue[var.first][pos + i] == 0) {
									strValue[var.first][pos + i] = tmp[i];
									update = true;
								}
								else
									assert(strValue[var.first][pos + i] == tmp[i]);
						}
					}
					pos += getConstLength(s, len);

				}
				else
					pos += len[s];
			}
		}
		if (update == true) {
			forwardPropagate(var.first, len, strValue);
			backwardPropagarate(var.first, len, strValue);
			__debugPrint(logFile, ">> %d done synConst\n", __LINE__);
		}
	}
	__debugPrint(logFile, "%d >> done %s \n", __LINE__, __FUNCTION__);
}

/*
 * a = b . c .We know b, need to update a
 */
void forwardPropagate(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, newlyUpdate.c_str());
	std::vector<int> sValue;
	if (isRegexStr(newlyUpdate))
		sValue = getDataStr(newlyUpdate, strValue);
	else
		sValue = strValue[newlyUpdate];


	for (const auto& var : equalitiesMap){
		std::vector<int> value;
		if (isRegexStr(var.first))
			value = getDataStr(var.first, strValue);
		else if (strValue.find(var.first) == strValue.end())
			value = std::vector<int>(5000, 0);
		else
			value = strValue[var.first];

		/* update parents */
		bool foundInParents = false;
		for (const auto& eq : var.second)
			if (std::find(eq.begin(), eq.end(), newlyUpdate) != eq.end()) {
				int pos = 0;
				for (const auto& s : eq)
					if (s.compare(newlyUpdate) == 0 && !isConstStr(s)){
						int length = 0;
						if (s[0] == '"') {
							assert(isRegexStr(s));
							length = getConstLength(s, len);
						}
						else {
							assert(len.find(s) != len.end());
							length = len[s];
						}

						for (int i = 0; i < length; ++i)
							if (value[pos + i] == 0 && sValue[i] != 0) {
								value[pos + i] = sValue[i];
								foundInParents = true;
							}
							else if (value[pos + i] != 0 && sValue[i] != 0) {
								assert(value[pos + i] == sValue[i]);
							}
						pos += len[s];
					}
					else {
						if (isRegexStr(s))
							pos += getConstLength(s, len);
						else if (s[0] == '"')
							pos += s.length() - 2;
						else {
							assert(len.find(s) != len.end());
							pos += len[s];
						}
					}
			}


		if (foundInParents) {
			strValue[var.first] = value;
			/* update it parents */
			forwardPropagate(var.first, len, strValue);
			backwardPropagarate(var.first, len, strValue);
			__debugPrint(logFile, ">> %d done update parents\n", __LINE__);
			/* update peers */
			for (const auto& eq : var.second){
				int pos = 0;
				for (const auto& s : eq){
					if (isConstStr(s)) {
						pos += s.length() - 2;
					}
					else {
						int length = 0;
						std::vector<int> sValue;
						if (isRegexStr(s)) {
							/* regex */
							length = getConstLength(s, len);
							sValue = getDataStr(s, strValue);
						}
						else {
							/* var */
							assert(len.find(s) != len.end());
							length = len[s];
							if (strValue.find(s) == strValue.end())
								sValue = std::vector<int>(5000, 0);
							else
								sValue = strValue[s];
						}

						bool updated = false;
						for (int i = 0; i < len[s]; ++i) {
							if (sValue[i] != value[pos + i]) {
								updated = true;
								sValue[i] = value[pos + i];
							}
						}
						if (updated == true) {
							if (isRegexStr(s))
								strValue[constMap[s.substr(1, s.length() - 2)]] = sValue;
							else
								strValue[s] = sValue;
							forwardPropagate(s, len, strValue);
							backwardPropagarate(s, len, strValue);
							__debugPrint(logFile, ">> %d done update child\n", __LINE__);
						}
						pos += length;
					}
				}
			}
		}
	}
}

/*
 *
 */
std::vector<int> createString(
		std::string name,
		std::string value,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> strValue,
		bool &assigned){
	__debugPrint(logFile, "%d *** %s ***: %s = %s\n", __LINE__, __FUNCTION__, name.c_str(), value.c_str());
	std::vector<int> val(5000, 0);
	if (strValue.find(name) != strValue.end())
		val = strValue[name];

	/* update based on previous values */
	for (const auto& eq : equalitiesMap[name]){
		int pos = 0;
		for (const auto& var : eq) {
			if (var[0] == '"') {
				pos += getConstLength(var, len);
			}
			else if(strValue.find(var) != strValue.end()){
				/* add an evaluated value */
				for (int i = 0; i < len[var]; ++i)
					if (val[pos + i] == 0)
						val[pos + i] = strValue[var][i];
					else
						assert(val[pos + i] == strValue[var][i]);
				pos += len[var];
			}
			else
				/* unknown */
				pos += len[var];
		}
		assert(pos == len[name]);
	}

	/* update values found by the solver & previous iterations */

	for (int i = 0; i < len[name]; ++i)
		if (val[i] == 0)
			if (i < (int)value.length())
				val[i] = value[i];

	bool canAssign = false;
	for (int i = 0; i < len[name]; ++i)
		if (val[i] != 0) {
			canAssign = true;
			break;
		}

	if (canAssign) {
		for (int i = 0; i < len[name]; ++i)
			if (val[i] == 0)
				val[i] = 'a';
	}
	else {
		/* cannot assign because we do not know anything */
		assigned = false;
		return val;
	}

	__debugPrint(logFile, ">> %d: ", __LINE__);
	for (int i = 0; i < len[name]; ++i)
		__debugPrint(logFile, "%c", val[i]);
	__debugPrint(logFile, "\n");

	assigned = true;
	return val;
}

/*
 * a = b . c. We know a, need to update b and c
 */
void backwardPropagarate(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, newlyUpdate.c_str());
	std::vector<int> value = strValue[newlyUpdate];
	std::string name = newlyUpdate;
	if (isRegexStr(newlyUpdate)) {
		name = constMap[newlyUpdate.substr(1, newlyUpdate.length() - 2)];
		value = getDataStr(newlyUpdate, strValue);
	}
	else if (newlyUpdate[0] == '"')
		name = constMap[newlyUpdate.substr(1, newlyUpdate.length() - 2)];

	for (const auto& eq : equalitiesMap[newlyUpdate]){
		int pos = 0;
		__debugPrint(logFile, "%d step 0: size = %ld\n", __LINE__, eq.size());
		for (const auto& var : eq) {
			__debugPrint(logFile, "%d step 0.1: var = %s\n", __LINE__, var.c_str());
			if (var[0] == '"') {
				int length = getConstLength(var, len);
				if (isRegexStr(var)) {
					bool update = false;

					std::vector<int> sValue;
					if (strValue.find(constMap[var.substr(1, var.length() - 2)]) == strValue.end())
						sValue = std::vector<int>(5000, 0);
					else
						sValue = strValue[constMap[var.substr(1, var.length() - 2)]];

					for (int i = 0; i < length; ++i)
						if (value[pos + i] != 0 && sValue[i] != 0) {
							assert(value[pos + i] == sValue[i]);
						}
						else if (value[pos + i] != 0 && sValue[i] == 0){
							sValue[i] = value[pos + i];
							update = true;
						}
						else if (value[pos + i] == 0 && sValue[i] != 0){
							assert(false);
						}

					if (update == true) {
						strValue[constMap[var.substr(1, var.length() - 2)]] = sValue;
						__debugPrint(logFile, "%d var: %s = %s --> len = %d\n", __LINE__, var.substr(1, var.length() - 2).c_str(), constMap[var.substr(1, var.length() - 2)].c_str(), getConstLength(var, len));
						forwardPropagate(var, len, strValue);
					}
				}

				pos += length;
			}
			else if(strValue.find(var) != strValue.end()){
				/* verify a determined value */
				std::vector<int> sValue = strValue[var];
				bool update = false;
				for (int i = 0; i < len[var]; ++i)
					if (value[pos + i] != 0 && sValue[i] != 0) {
						assert(value[pos + i] == sValue[i]);
					}
					else if (value[pos + i] != 0 && sValue[i] == 0){
						sValue[i] = value[pos + i];
						update = true;
					}
					else if (value[pos + i] == 0 && sValue[i] != 0){
						assert(false);
					}
				pos += len[var];
				if (update == true) {
					strValue[var] = sValue;
					forwardPropagate(var, len, strValue);
				}
			}
			else {
				/* update a new value */
				std::vector<int> sValue;
				for (int i = 0; i < len[var]; ++i)
					sValue.emplace_back(value[pos + i]);
				strValue[var] = sValue;
				pos += len[var];
				forwardPropagate(var, len, strValue);
			}
		}
		__debugPrint(logFile, "%d %s: %d == %d\n", __LINE__, name.c_str(), pos, len[name]);
		assert(pos == len[name]);
	}
}

/*
 * create str values after running Z3
 */
std::map<std::string, std::string> formatResult(std::map<std::string, std::string> len, std::map<std::string, std::string> _strValue){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	std::vector<std::pair<std::string, int>> lenVector;
	std::map<std::string, int> lenInt;
	std::map<std::string, std::string> strValue;
	for (const auto& s : len)
		if (s.first.find("len_") == 0){
			std::string name = s.first.substr(4);
			lenVector.push_back(std::make_pair(name, atoi(s.second.c_str())));
			lenInt[name] = atoi(s.second.c_str());
			__debugPrint(logFile, "%d %s : %s -> %d\n", __LINE__, name.c_str(), s.second.c_str(), atoi(s.second.c_str()));
		}
		else {
			lenVector.push_back(std::make_pair(s.first, atoi(s.second.c_str())));
			lenInt[s.first] = atoi(s.second.c_str());
		}

	for (const auto& s : _strValue)
		if (s.first.find("arr_") == 0){
			std::string name = s.first.substr(4);
			strValue[name] = s.second;
		}
		else
			strValue[s.first] = s.second;

	for (const auto& s : strValue)
		__debugPrint(logFile, "%d %s : %s\n", __LINE__, s.first.c_str(), s.second.c_str());

	std::vector<unsigned> indexes = sort_indexes(lenVector);
	std::map<std::string, std::vector<int>> finalStrValue;
	for (const auto& var : lenVector) {
		std::string varName = var.first;
		if (isInternalVar(varName))
			continue;
		finalStrValue[var.first] = std::vector<int>(5000, 0);
	}
	syncConst(lenInt, finalStrValue);

	/* 1st: handling connected vars */
	for (const auto& s : indexes) {
		std::string varName = lenVector[s].first;
		if (len.find("len_" + varName) == len.end())
			continue;
		if (isInternalVar(varName))
			continue;
		if (lenVector[s].second == 0) {
			finalStrValue[varName] = {};
		}
		else {
			if (connectedVariables.find(varName) != connectedVariables.end()) {
				__debugPrint(logFile, "%d varname = %s\n", __LINE__, varName.c_str());
				bool assigned = true;
				std::vector<int> tmp = createString(varName, strValue[varName], lenInt, finalStrValue, assigned);

				if (assigned) {
					__debugPrint(logFile, "%d assign: %s\n", __LINE__, varName.c_str());
					finalStrValue[varName] = tmp;
					backwardPropagarate(varName, lenInt, finalStrValue);
					forwardPropagate(varName, lenInt, finalStrValue);

					__debugPrint(logFile, ">> %d done formating %s\n", __LINE__, varName.c_str());
				}
				else
					__debugPrint(logFile, "%d cannot assign: %s\n", __LINE__, varName.c_str());
			}
		}
	}

	/* 2nd: handling other vars */
	for (const auto& s : indexes) {
		std::string varName = lenVector[s].first;
		if (len.find("len_" + varName) == len.end())
			continue;
		if (isInternalVar(varName))
			continue;
		if (lenVector[s].second == 0) {
		}
		else {
			bool assigned = true;
			std::vector<int> tmp = createString(varName, strValue[varName], lenInt, finalStrValue, assigned);

			if (assigned) {
				__debugPrint(logFile, "%d assign: %s\n", __LINE__, varName.c_str());
				finalStrValue[varName] = tmp;
				backwardPropagarate(varName, lenInt, finalStrValue);
				forwardPropagate(varName, lenInt, finalStrValue);
			}
			else
				__debugPrint(logFile, "%d cannot assign: %s\n", __LINE__, varName.c_str());
		}
	}

	std::map<std::string, std::string> finalResult;
	for (const auto& var : finalStrValue){
		if (len.find("len_" + var.first) == len.end())
			continue;

		if (isInternalVar(var.first))
			continue;

		bool foundClue = false;
		for (int i = 0; i < lenInt[var.first]; ++i)
			if (var.second[i] != 0) {
				foundClue = true;
				break;
			}
		if (foundClue == false)
			continue;

		std::string value = "";
		for (int i = 0; i < lenInt[var.first]; ++i) {
			if (var.second[i] != 0) {
				value += var.second[i];
			}
		}
		std::string tmp = "";
		for (unsigned int i = 0; i < value.length(); ++i)
			if (value[i] == '\"')
				tmp = tmp + "\\\"";
			else if (value[i] == '\\')
				tmp = tmp + "\\\\";
			else if (value[i] == 9) // tab
				tmp = tmp + "\\t";
			else if (value[i] < 32 || value[i] > 126)
				tmp = tmp + 'a';
			else
				tmp = tmp + value[i];
		finalResult[var.first] = tmp;
	}

	for (const auto& var : finalResult){
		__debugPrint(logFile, "%d value of %s: %s\n", __LINE__, var.first.c_str(), var.second.c_str());
	}
	return finalResult;
}

/*
 *
 */
bool Z3_run(
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		bool finalCall = true) {
	std::string cmd = std::string(Z3_PATH) + "-smt2 " + OUTPUT;
	printf(">> Running Z3\n");

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("Z3 failed!");

	std::map<std::string, std::string> len_results;
	std::map<std::string, std::string> str_results;
	char buffer[5000];
	std::string result = "";
	bool sat = false;
	try {
		/* the first line */
		if (fgets(buffer, 4000, in) == NULL)
			assert(false);
		std::string getSat = buffer;
		getSat = getSat.substr(0, 3);
		__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, buffer);

		if (getSat.compare("sat") == 0) {
			printf(">> Z3: SAT\n\n");
			sat = true;
		}
		else {
			if (finalCall == true)
				printf(">> Z3: UNSAT\n\n");
			return sat;
		}
		std::map<std::string, std::string> array_map;
		/* the concrete values */
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 4000, in) != NULL) {
				line = buffer;
				if (line.find("(define") != std::string::npos) {
					/* collect variable */
					std::vector<std::string> tokens = parse_string_language(buffer, " (),.");

					std::string name = tokens[1];
					int elseValue = 0;
					if (array_map.find(name) != array_map.end()){
						/* array value */
						std::map<int, int> valueMap;
						while (true){
							/* read the value in the next line */
							if (fgets(buffer, 4000, in) == NULL)
								assert(false);
							tokens = parse_string_language(buffer, " (),.=");
							if (tokens[0].compare("ite") != 0) {
								elseValue = std::atoi(tokens[0].c_str());
								break;
							}
							else {
								valueMap[std::atoi(tokens[2].c_str())] = std::atoi(tokens[tokens.size() - 1].c_str());
							}
						}
						/* convert map to string */
						std::string valueStr = "";
						for (unsigned int j = 0; j < valueMap.size(); ++ j) {
							if (valueMap.find(j) != valueMap.end())
								valueStr = valueStr + (char)valueMap[j];
							else
								valueStr = valueStr + (char)elseValue;
						}
						__debugPrint(logFile, "%d value %s: %s\n", __LINE__, array_map[name].c_str(), valueStr.c_str());
						str_results[array_map[name]] = valueStr;
					}
					else if (name.find("arr_") != std::string::npos){
						/* array map */
						if (fgets(buffer, 4000, in) == NULL)
							assert(false);
						tokens = parse_string_language(buffer, " (),.\n\t\r");
						assert(tokens.size() == 3);
						array_map[tokens[2]] = name;
					}
					else {
						/* len value */
						/* read the value in the next line */
						if (fgets(buffer, 4000, in) == NULL)
							assert(false);
						tokens = parse_string_language(buffer, " (),.");
						if (tokens[0][0] == '-')
							len_results[name] = tokens[0] + " " + tokens[1];
						else
							len_results[name] = tokens[0];

						__debugPrint(logFile, "%d %s: %s\n", __LINE__, name.c_str(), len_results[name].c_str());
					}
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

	if (sat && getModel) {
		std::map<std::string, std::string> results = formatResult(len_results, str_results);
		printSatisfyingAssignments(decodeResultMap(results), len_results);
		if (beReviewed) {
			verifyOutput(lengthFile, _equalMap, len_results, results);
			sat = S3_reviews(lengthFile);
			if (sat == true) {
				printf("\nDouble-checked by S3P: successful.\n");
			}
			else
				assert(false);
		}
		else {
			sat = true;
		}
	}
	return sat;
}

/*
 *
 */
bool S3_reviews(std::string fileName){
	std::string cmd = std::string(VERIFIER) + " -f " + fileName;

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("S3 failed!");

	std::map<std::string, std::string> results;
	char buffer[5000];
	std::string result = "";
	try {
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 5000, in) != NULL) {
				line = buffer;
				if (line.substr(0, 8).compare(">> UNSAT") == 0)
					assert(false);
				else if (line.find("unknown function/constant") != std::string::npos){
					unsigned pos = line.find("unknown function/constant") + std::string("unknown function/constant").length() + 1;
					std::string funcName = "";
					while (line[pos] != ' ' && line[pos] != '"' && pos < line.length())
						funcName += line[pos++];
					printf("Warning: S3P does not support some functions: %s\n", funcName.c_str());
					break;
				}
			}

		}

	} catch (...) {
		pclose(in);
		throw;
	}
	pclose(in);

	return true;
}

/*
 * Pthread Caller
 */
void pthreadController(){
	convertEqualities();
//	pthread_t thread[NUM_THREADS];
//	int  tids[NUM_THREADS];
//	pthread_attr_t attr;
//	int rc;
//
//	/* Initialize and set thread detached attribute */
//	pthread_mutex_init(&smt_mutex, NULL);
//	pthread_attr_init(&attr);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//
//	/* create threads */
//	for(int t = 0; t < NUM_THREADS; t++) {
//		tids[t] = t;
//#ifdef DEBUGLOG
//		// printf("Controller: creating thread %d\n", t);
//#endif
//		rc = pthread_create(&thread[t], &attr, convertEqualities, (void *) &tids[t]);
//		if (rc) {
//			printf("ERROR; return code from pthread_create() is %d\n", rc);
//			exit(-1);
//		}
//	}
//
//	/* Free attribute and wait for the other threads */
//	pthread_attr_destroy(&attr);
//
//	/* join threads */
//	void *result;
//	for(int t = 0; t < NUM_THREADS; t++) {
//		rc = pthread_join(thread[t], &result);
//		if (rc) {
//			printf("ERROR; return code from pthread_join() is %d\n", rc);
//		}
//#ifdef DEBUGLOG
//		// printf("Controller: completed join with thread %d.\n", t);
//#endif
//	}
//
//	pthread_mutex_destroy(&smt_mutex);
}

/*
 *
 */
void reset(){
	smtLenConstraints.clear();
	smtVarDefinition.clear();
	global_smtStatements.clear();
	connectedVariables.clear();
	trivialUnsat = false;
}

/*
 * replace all "Length " by "len_"
 */
std::set<std::string> reformatCarryOnConstraints(std::set<std::string> _carryOnConstraints){
	std::set<std::string> ret;

	for (const auto& s : _carryOnConstraints){
		std::string tmp = s;
		while (true){
			size_t pos = tmp.find("(Length ");
			if (pos != std::string::npos){
				std::string _tmp = tmp.substr(0, pos) + "len_";
				for (unsigned int i = pos + 8; i < tmp.length(); ++i)
					if (tmp[i] != ')')
						_tmp = _tmp + tmp[i];
					else {
						_tmp = _tmp + tmp.substr(i + 1);
						break;
					}
				tmp = _tmp;
			}
			else {
				ret.emplace(tmp);
				break;
			}
		}
	}

	displayListString(ret, " reformat _carryOnConstraints");
	return ret;
}

/*
 *
 */
void init(std::map<StringOP, std::string> &rewriterStrMap){
	collectConnectedVariables(rewriterStrMap);
	refineEqualMap();

	/*collect var --> update --> collect again */
	collectConnectedVariables(rewriterStrMap);
	sumConstString();
	createConstMap();
}

/*
 *
 */
void additionalHandling(std::map<StringOP, std::string> rewriterStrMap){
	handle_NOTEqual(rewriterStrMap);
	handle_NOTContains(rewriterStrMap);
	handle_StartsWith(rewriterStrMap);
	handle_EndsWith(rewriterStrMap);
	handle_Replace(rewriterStrMap);
	handle_ToUpper(rewriterStrMap);
	handle_ToLower(rewriterStrMap);
	handle_ReplaceAll(rewriterStrMap);
}

/*
 *
 */
std::set<std::string> collectAllVars(){
	std::set<std::string> results;
	for (const auto& varEq: equalitiesMap) {
		if (varEq.first[0] != '"')
			results.emplace(varEq.first);

		for (const auto& _eq : varEq.second){
			for (const auto& v : _eq)
				if (v[0] != '"')
					results.emplace(v);
		}
	}
	return results;
}

/*
 *
 */
void updateRewriter(
		std::map<StringOP, std::string> &rewriterStrMap,
		std::set<std::string> allVars){
	std::map<StringOP, std::string> newRewriterStrMap;
	for (const auto& op : rewriterStrMap){
		if (op.first.name.compare("=") == 0) {
			if (op.second.compare("false") == 0) {
				if (equalitiesMap.find(op.first.arg01) != equalitiesMap.end() &&
						equalitiesMap.find(op.first.arg02) != equalitiesMap.end()) {
					StringOP tmp = op.first;
					__debugPrint(logFile, "%d remove in rewriter: (%s, %s)\n", __LINE__, tmp.toString().c_str(), op.second.c_str());
					continue;
				}
			}
		}
		else if (allVars.find(op.first.arg01) != allVars.end() ||
				allVars.find(op.first.arg02) != allVars.end() ||
				allVars.find(op.first.arg03) != allVars.end())
			newRewriterStrMap[op.first] = op.second;
		else {
			StringOP tmp = op.first;
			__debugPrint(logFile, "%d remove in rewriter: (%s, %s)\n", __LINE__, tmp.toString().c_str(), op.second.c_str());
		}
	}
	rewriterStrMap.clear();
	rewriterStrMap = newRewriterStrMap;
}

/*
 *
 */
bool underapproxController(
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<StringOP, std::string> rewriterStrMap,
		std::set<std::string> _carryOnConstraints,
		std::map<std::string, int> _currentLength,
		std::string fileDir ) {
	printf("\nRunning Under Approximation\n");
	clock_t tx;
	tx = clock();
	//	std::vector<std::vector<std::string>> test = refineVectors(parseRegexComponents(underApproxRegex("( not )*a > 1a1 or ( not )*1a1 > a")));
	//	for (unsigned int i = 0; i < test.size(); ++i)
	//		displayListString(test[i], " parse regex ");

	/* init varLength */
	varLength.clear();
	varLength.insert(_currentLength.begin(), _currentLength.end());

	/* init equalMap */
	parseEqualityMap(_equalMap);

	reset();

	init(rewriterStrMap);

	std::set<std::string> allVars = collectAllVars();
	updateRewriter(rewriterStrMap, allVars);

	additionalHandling(rewriterStrMap);

	std::set<std::string> carryOnConstraints = reformatCarryOnConstraints(_carryOnConstraints);
	for (const auto& s : carryOnConstraints)
		global_smtStatements.push_back({s});

	/* rewrite the CFG constraint */
	printEqualMap(equalitiesMap);
	if (constMap.size() > 0) {
		/* print test const map */
		__debugPrint(logFile, "%d Const map:\n", __LINE__);
		for (const auto& element : constMap)
			__debugPrint(logFile, "%s: %s\n", element.first.c_str(), element.second.c_str());
		__debugPrint(logFile, "\n");
	}

	__debugPrint(logFile, "%d filedir: %s, orgInput: %s\n", __LINE__, fileDir.c_str(), orgInput.c_str());
	toNonGRMFile(fileDir, NONGRM, equalitiesMap, constMap);

	/* init regexCnt */
	regexCnt = 0;

	bool result = false;

	if (connectedVariables.size() == 0 && equalitiesMap.size() == 0) {
		toLengthFile(NONGRM, true, rewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
		if (trivialUnsat) {
			printf(">> UNSAT\n");
			return false;
		}

		writeOutput_basic(OUTPUT);

		bool val = Z3_run(_equalMap, false);
		if (val == false){
			regexCnt = 0;
			toLengthFile(NONGRM, false, rewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
			if (trivialUnsat) {
				printf(">> UNSAT\n");
				return false;
			}
			writeOutput_basic(OUTPUT);
			result = Z3_run(_equalMap);
		}
	}
	else {
		toLengthFile(NONGRM, false, rewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
		pthreadController();
		if (trivialUnsat) {
			printf(">> UNSAT\n");
			return false;
		}
		else {
			printf(">> Generated SMT\n\n");
			writeOutput02(OUTPUT);

			result =  Z3_run(_equalMap);
		}
	}

	if (result == false) {
		/* skip */
	}
	tx = clock() - tx;
	printf("%d Underapprox: %.3f seconds.\n\n", __LINE__, ((float)tx)/CLOCKS_PER_SEC);
	__debugPrint(logFile, "%d *** %s ***\n%s\n", __LINE__, __FUNCTION__, result == true ? "true" : "false");
	return result;
}


