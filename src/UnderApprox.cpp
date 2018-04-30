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
#define NOTFOUND "!FoUnD"
#define FLATPREFIX "__flat_"
bool trivialUnsat = false;
bool createAnyway = true;

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
			return NOTFOUND;
	}
	return NOTFOUND;
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

bool passNotContainMapReview(
		Arrangment a,
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements){
	/* do the left */
	for (unsigned int i = 0; i < lhs_elements.size(); ++i)
		if (a.left_arr[i] == SUMFLAT) { /* a = bx + cy */

			for (unsigned int j = 0; j < rhs_elements.size(); ++j)
				if (a.right_arr[j] == (int)i) {
					if (rhs_elements[j].second < 0) {
						std::string strContent = "";
						if (isRegexStr(rhs_elements[j].first)) {
							if (rhs_elements[j].first.find('+') != std::string::npos)
								strContent = parse_regex_full_content(rhs_elements[j].first);
						}
						else
							strContent = rhs_elements[j].first;
						for (const auto notContain : notContainMap)
							if (notContain.first.first.compare(lhs_elements[i].first) == 0 &&
									strContent.find(notContain.first.second) != std::string::npos) {
								__debugPrint(logFile, "%d %s: %s cannot contain %s because of %s\n", __LINE__, __FUNCTION__, notContain.first.first.c_str(), rhs_elements[j].first.c_str(), notContain.first.second.c_str());
								return false;
							}
					}
				}
		}

	/* do the right */
	for (unsigned int i = 0; i < rhs_elements.size(); ++i)
		if (a.right_arr[i] == SUMFLAT) { /* a = bx + cy */

			for (unsigned int j = 0; j < lhs_elements.size(); ++j)
				if (a.left_arr[j] == (int)i) {
					if (lhs_elements[j].second < 0)
						for (const auto notContain : notContainMap)
							if (notContain.first.first.compare(rhs_elements[i].first) == 0 &&
									lhs_elements[j].first.find(notContain.first.second) != std::string::npos) {
								__debugPrint(logFile, "%d %s: %s cannot contain %s\n", __LINE__, __FUNCTION__, notContain.first.first.c_str(), lhs_elements[j].first.c_str());
								return false;
							}
				}
		}
	return true;
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
	arrangements[std::make_pair(0, 0)].emplace_back(Arrangment(tmpLeft, tmpRight, constMap));
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
		arrangements[std::make_pair(0, 0)].emplace_back(Arrangment(tmpLeft, tmpRight, constMap));
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
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));

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
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));

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
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));

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
		tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));

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
					tmp03.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));
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
					tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));
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
					tmp03.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));
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
					tmp04.emplace_back(Arrangment(tmpLeft, tmpRight, constMap));
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
				possibleCases.insert(possibleCases.end(), tmp03.begin(), tmp03.end());
				possibleCases.insert(possibleCases.end(), tmp04.begin(), tmp04.end());
				possibleCases.insert(possibleCases.end(), tmp05.begin(), tmp05.end());
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
	return Arrangment(left_arr, right_arr, constMap);
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
		std::vector<std::pair<std::string, int>> rhs_elements){
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
	if (lhs_elements[0].first.find(FLATPREFIX) != std::string::npos ||
			(lhs_elements.size() == 2 &&
					 ((connectedVariables.find(lhs_elements[0].first) != connectedVariables.end() && lhs_elements[1].second % QMAX == 1) ||
					  (lhs_elements[0].second % QCONSTMAX == -1 && lhs_elements[1].second % QCONSTMAX == 0)))) {
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
		if (passNotContainMapReview(possibleCases[i], lhs_elements, rhs_elements)) {
			possibleCases[i].constMap.clear();
			possibleCases[i].constMap.insert(constMap.begin(), constMap.end());
			std::string tmp = possibleCases[i].
					generateSMT(PMAX, lhs_str, rhs_str, lhs_elements, rhs_elements, connectedVariables);

			if (tmp.length() > 0) {
				cases.emplace_back(tmp);
				arrangements[std::make_pair(lhs_elements.size() - 1, rhs_elements.size() - 1)][i].printArrangement("Correct case");
				__debugPrint(logFile, "%d %s\n", __LINE__, tmp.c_str());
			}
			else {
			}
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
	return ARRPREFIX + a;
}

/*
 * Given a flat,
 * generate its array name
 */
std::string generateVarLength(std::string a){
	return LENPREFIX + a;
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
					StringOP opTmp(CONTAINS, var.first, arg);
					if (rewriterStrMap[opTmp].compare(FALSETR) == 0) {
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

	if (boolValue.compare(FALSETR) != 0)
		return TRUESTR;

	bool isConst_00 = false;
	bool isConst_01 = false;
	if (str00[0] == '"' )
		isConst_00 = true;

	if (str01[0] == '"')
		isConst_01 = true;

	assert(isConst_00 || isConst_01);

	std::vector<std::string> orConstraints;
	std::vector<std::string> andConstraints;

	std::string ret = "";

	if (isConst_00 == true) {
		/* (length b = 0 && ...) || length b = 1 && ...*/
		for (unsigned j = 0; j < str00.length() - 2; ++j) {
			/* length = j*/
			andConstraints.emplace_back(createEqualConstraint(generateVarLength(str01), std::to_string(j)));
			for (unsigned int i = 1; i < j + 1; ++i) {
				andConstraints.emplace_back(createEqualConstraint(
						createSelectConstraint(generateVarArray(str01), std::to_string(i - 1)),
						std::to_string(str00[i])));
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

	if (boolValue.compare(FALSETR) == 0)
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
	if (boolValue.compare(FALSETR) == 0){
		/* new value = old value = args[0] */
		/* len = len && value = value */
		std::vector<std::string> andConstraints;
		andConstraints.emplace_back(createEqualConstraint(generateVarArray(args[0]), generateVarLength(lhs)));
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
	return TRUESTR;
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
		return TRUESTR;
	else if (isConst_01 && isConst_02 && boolValue.compare(TRUESTR) == 0) {
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
	return TRUESTR;
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
		tmp.emplace_back(createLessConstraint(lenName, std::to_string(i)));

		for (unsigned k = 0; k < value.length() - 2; ++k) {
			unsigned pos = k + i - value.length() + 2;
			tmp.emplace_back(createNotOperator(createEqualConstraint(
											createSelectConstraint(arrName, std::to_string(pos)),
											std::to_string(value[k + 1]))));
		}
		andConstraints.emplace_back(orConstraint(tmp));
	}

	andConstraints.emplace_back(createLessConstraint(lenName, std::to_string(std::min(CONNECTSIZE, maxSize))));
	__debugPrint(logFile, "%d *** %s ***: %s\n%s\n", __LINE__, __FUNCTION__, value.c_str(), andConstraint(andConstraints).c_str());

	return andConstraint(andConstraints);
}

/*
 *
 */
std::string create_constraints_equal(
	std::string str00,
	std::string str01){
	bool isConst_00 = false;
	bool isConst_01 = false;
	if (str00[0] == '\"' )
		isConst_00 = true;

	if (str01[0] == '\"')
		isConst_01 = true;
	if (isConst_00 || isConst_01) {
		if (isConst_01) {
			/* swap */
			std::string tmp = str00;
			str00 = str01;
			str01 = tmp;
		}

		if (isRegexStr(str00)) {
			return TRUESTR;
		}
		else if (isUnionStr(str00)) {
			return TRUESTR;
		}

		std::string len01 = generateVarLength(str01);
		/* != "a" b */
		return createEqualConstraint(len01, std::to_string((int)str00.length() - 2));
	}
	else {
		bool concat00 = str00.find("(" + std::string(CONCAT)) != std::string::npos;
		bool concat01 = str01.find("(" + std::string(CONCAT)) != std::string::npos;
		if (!concat00 && !concat01) {
			/* x = y */

			std::string len00 = generateVarLength(str00);
			std::string len01 = generateVarLength(str01);

			/* = a b */
			return createEqualConstraint(len00, len01);
		}
		else {
			if (concat00){
				std::string tmp = str00;
				str00 = str01;
				str01 = tmp;
			}
			std::vector<std::pair<std::string, int>> tokens  = parseTerm(str01);
			std::string tmp = "";
			for (const auto& s : tokens)
				if (s.first.compare("(") != 0 && s.first.compare(")") != 0 && s.first.compare(CONCAT) != 0) {
					if (s.first[0] != '"')
						tmp = tmp + generateVarLength(s.first) + " ";
					else
						tmp = tmp + std::to_string(s.first.length() - 2) + " ";
				}
			return createEqualConstraint(generateVarLength(str00),
					"(+ " + tmp + ")");
		}

	}
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

		if (isRegexStr(str00)) {
			// TODO not equal regex
			unknownResult = true;
			return FALSETR;
		}
		else if (isUnionStr(str00)) {
			// TODO not equal union
			return TRUESTR;
		}

		std::string len01 = generateVarLength(str01);
		std::string arr01 = generateVarArray(str01);

		/* != "a" b */
		orConstraints.emplace_back(createNotOperator(createEqualConstraint(len01, std::to_string((int)str00.length() - 2))));

		/* (length a != 0 && ...) || length b = 1 && ...*/
		if (str00.length() > 2) {
			for (unsigned int j = 1; j < str00.length() - 1; ++j) {
				orConstraints.emplace_back(createNotOperator(createEqualConstraint(
						createSelectConstraint(arr01, std::to_string(j - 1)),
						std::to_string((int)str00[j]))));
			}
		}

		ret = orConstraint(orConstraints);

	}
	else {
		bool concat00 = str00.find("(Concat") != std::string::npos;
		bool concat01 = str01.find("(Concat") != std::string::npos;
		if (!concat00 && !concat01) {
			/* x != y */

			std::string len00 = generateVarLength(str00);
			std::string len01 = generateVarLength(str01);
			std::string arr00 = generateVarArray(str00);
			std::string arr01 = generateVarArray(str01);

			/* != a b */
			orConstraints.emplace_back(createNotOperator(createEqualConstraint(len00, len01)));

			for (unsigned int i = 1; i < CONNECTSIZE; ++i){
				/*len a = len b <= i || a[i - 1] == b [i-1] */
				std::string tmp = "";
				tmp += createLessConstraint(len00, std::to_string(i));
				tmp += createEqualConstraint(
								createSelectConstraint(arr00, std::to_string(i - 1)),
								createSelectConstraint(arr01, std::to_string(i - 1)))	;
				tmp = "(or " + tmp + ")";
				andConstraints.emplace_back(tmp);
			}
			orConstraints.emplace_back(createNotOperator(andConstraint(andConstraints)));
			ret = orConstraint(orConstraints);
		}
		else {
			// TODO not equal concat
			ret = TRUESTR;
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
		tmp += createLessConstraint(len00, std::to_string(i));
		tmp = tmp + "(ite (and " + createLessEqualConstraint("65", createSelectConstraint(arr00, std::to_string(i - 1))) +
				createLessEqualConstraint(createSelectConstraint(arr00, std::to_string(i - 1)), "90") + "))";

		tmp += createEqualConstraint(
				createSelectConstraint(arr01, std::to_string(i - 1)),
				createPlusOperator(
							createSelectConstraint(arr00, std::to_string(i - 1)),
							"32"));
		tmp += createEqualConstraint(
				createSelectConstraint(arr00, std::to_string(i - 1)),
				createSelectConstraint(arr01, std::to_string(i - 1)));
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
		tmp += createLessConstraint(len00, std::to_string(i));
		tmp = tmp + "(ite (and " + createLessEqualConstraint("97", createSelectConstraint(arr00, std::to_string(i - 1))) +
						createLessEqualConstraint(createSelectConstraint(arr00, std::to_string(i - 1)), "122") + "))";
		tmp += createEqualConstraint(
						createSelectConstraint(arr00, std::to_string(i - 1)),
						createPlusOperator(
									createSelectConstraint(arr01, std::to_string(i - 1)),
									"32"));
		tmp += createEqualConstraint(
						createSelectConstraint(arr00, std::to_string(i - 1)),
						createSelectConstraint(arr01, std::to_string(i - 1)));
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
		if (element.first.name.compare(CONTAINS) == 0){
			if (element.second.compare(FALSETR) == 0){
				if (element.first.arg01.find(CONCAT) != std::string::npos ||
						element.first.arg02.find(CONCAT) != std::string::npos ||
						element.first.arg02.find("Automata ") != std::string::npos)
					continue;
				if (canSkipNotContain(element.first.arg01, element.first.arg02, rewriterStrMap)){
					continue;
				}
				std::string value02 = getPossibleValue(element.first.arg02);
				std::string value01 = getPossibleValue(element.first.arg01);
				__debugPrint(logFile, "%d *** %s ***: %s -- %s\n", __LINE__, __FUNCTION__, value01.c_str(), value02.c_str());
				if (value02.compare(NOTFOUND) != 0 && value01.compare(NOTFOUND) == 0 &&
						done.find(std::make_pair(element.first.arg01, value02)) == done.end()) {

					global_smtStatements.push_back({create_constraints_NOTContain(element.first.arg01, value02)});

					done[std::make_pair(element.first.arg01, value02)] = true;
				}
				else if (value02.compare(NOTFOUND) == 0 && value01.compare(NOTFOUND) != 0 &&
						done.find(std::make_pair(value01, element.first.arg02)) == done.end()) {
					// TODO handle_NOTContains
				}
				else if (value02.compare(NOTFOUND) != 0 && value01.compare(NOTFOUND) != 0) {
					/* const vs const */
					if (value01.find(value02.substr(1, value02.length() - 2)) == std::string::npos)
						return;
					else
						global_smtStatements.push_back({FALSETR});
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
		if (s.first.name.compare("=") == 0){
			if (s.second.compare(FALSETR) == 0) {
				if ((connectedVariables.find(s.first.arg01) != connectedVariables.end() ||
						connectedVariables.find(s.first.arg02) != connectedVariables.end() ||
						s.first.arg01.compare("\"\"") == 0 ||
						s.first.arg02.compare("\"\"") == 0)){
					global_smtStatements.push_back({create_constraints_NOTEqual(s.first.arg01, s.first.arg02)});
				}
			}
			else {
//				global_smtStatements.push_back({create_constraints_equal(s.first.arg01, s.first.arg02)});
			}
		}

	}
}

/**
 * handle startswith constraints
 */
void handle_StartsWith(
		std::map<StringOP, std::string> rewriterStrMap){

	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare(STARTSWITH) == 0){
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
		if (s.first.name.compare(STARTSWITH) == 0){
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
		if (s.first.name.compare(REPLACE) == 0){
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
		if (s.first.name.compare(REPLACEALL) == 0){
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
		if (s.second.compare(TOUPPER) == 0){
			global_smtStatements.push_back({create_constraints_ToUpper(s.first.arg01, s.first.arg02)});
		}
	}
}

/*
 *
 */
void handle_ToLower(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& s : rewriterStrMap) {
		if (s.second.compare(TOLOWER) == 0){
			global_smtStatements.push_back({create_constraints_ToLower(s.first.arg01, s.first.arg02)});
		}
	}
}

/*
 * define array for connected variable
 */
void create_constraints_array(std::vector<std::string> &defines, std::vector<std::string> &constraints){
	for (const auto& s : connectedVariables){
		defines.emplace_back(createArrayDefinition(ARRPREFIX + s.first));
	}
}

/*
 * define array for connected variable
 */
void create_const_array(
		std::vector<std::string> &defines,
		std::vector<std::string> &constraints){

	for (const auto& var : constMap){
		std::string varArr = ARRPREFIX + var.second;
		defines.emplace_back(createArrayDefinition(varArr));
		if (!isRegexStr(var.first) && !isUnionStr(var.first)){
			for (unsigned int i = 0 ; i < var.first.length(); ++i) {
				constraints.emplace_back(createAssert(createEqualConstraint(
						createSelectConstraint(varArr, std::to_string(i)),
						std::to_string(var.first[i]))));
			}
		}
		else if (isRegexStr(var.first)){
			std::string regexContent = parse_regex_content(var.first);
			std::vector<std::string> components = collectAlternativeComponents(regexContent);

			unsigned minSize = 10000, maxSize = 0;
			for (const auto& s : components){
				if (s.size() < minSize)
					minSize = s.length();
				if (s.size() > maxSize)
					maxSize = s.length();
			}

			std::string constraint = "(or \n";
			/* 1st */
			for (const auto& c: components) {
				constraint = constraint + " (and ";
				for (unsigned j = 0 ; j < c.length(); ++j) {
					constraint += createEqualConstraint(
									createSelectConstraint(varArr, std::to_string(j)),
									std::to_string(c[j]));
				}
				constraint = constraint + ")";
			}
			constraint = constraint + ")\n";

			/* 2..n */
			if (minSize == maxSize) {

				int base = minSize;
				while (base < 50) {
					constraint = constraint + "(or ";
					for (const auto& c: components) {
						constraint = constraint + " (and ";
						for (unsigned int j = 0 ; j < c.length(); ++j) {
							constraint += createEqualConstraint(
											createSelectConstraint(varArr, std::to_string(j + base)),
											std::to_string(c[j]));
						}
						constraint = constraint + ")";
					}
					base += minSize;
					constraint = constraint + ")\n";
				}
			}
			constraint = "(assert (and \n" + constraint + "\n))";
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

	for (const auto constNode : constMap)
		if (!isRegexStr(constNode.first) && isUnionStr(constNode.first)){
			std::set<std::string> components = extendComponent(constNode.first);
			__debugPrint(logFile, "%d ", __LINE__);
			for (const auto& s : components)
				__debugPrint(logFile, "%s ", s.c_str());
			__debugPrint(logFile, "\n");

			std::string varName = LENPREFIX + constNode.second;
			defines.emplace_back(createIntDefinition(varName));

			std::vector<std::string> orConstraints;
			for (const auto& s : components){
				std::vector<std::string> tmp;
				tmp.emplace_back(createEqualConstraint(std::to_string(s.length()), varName));
				std::string varArr = ARRPREFIX + constNode.second;
				for (unsigned i = 0; i < s.length(); ++i)
					tmp.emplace_back(createEqualConstraint(
							createSelectConstraint(varArr, std::to_string(i)),
							std::to_string(s[i])));
				orConstraints.emplace_back(andConstraint(tmp));
			}
			constraints.emplace_back(createAssert(orConstraint(orConstraints)));

			std::string lenX = "";
			for (int i = 1; i <= std::max(varPieces[constNode.first], QCONSTMAX); ++i) {
				defines.emplace_back(createIntDefinition(varName + "_" + std::to_string(i)));
				constraints.emplace_back(createAssert(createLessEqualConstraint(ZERO, varName + "_" + std::to_string(i))));
				lenX = lenX + varName + "_" + std::to_string(i) + " ";
				if (i % QCONSTMAX == 0) {
					/* (+ sum(len_x_i) */
					if (QCONSTMAX > 1)
						lenX = "(+ " + lenX + ")";
					/*(assert (= const (+ sum(len_x_i)))) */
					constraints.emplace_back(createAssert(createEqualConstraint(
							varName,
							lenX)));
					lenX = "";
				}
			}

		}
		else if (!isRegexStr(constNode.first) && !isUnionStr(constNode.first)){
			std::string lenValue = std::to_string(constNode.first.length());
			std::string lenName = LENPREFIX + constNode.second;
			defines.emplace_back(createIntDefinition(lenName));
			constraints.emplace_back(createAssert(createEqualConstraint(lenValue, lenName)));

			/* len_x = sum(len_x_i)*/
			std::string lenX = "";
			if (constNode.first.length() <= SPLIT_LOWER_BOUND - 2) { /* -2 because of "xxxx" */
				defines.emplace_back(createIntDefinition(lenName + "_1"));
				constraints.emplace_back(createAssert(createLessEqualConstraint(ZERO, lenName + "_1")));
				lenX = lenName + "_1 0";
				if (QCONSTMAX > 1)
					lenX = "(+ " + lenX + ")";
				constraints.emplace_back(createAssert(createEqualConstraint(lenValue, lenX)));
			}
			else for (int i = 1; i <= std::max(varPieces[constNode.first], QCONSTMAX); ++i) {
				defines.emplace_back(createIntDefinition(lenName + "_" + std::to_string(i)));
				constraints.emplace_back(createAssert(createLessEqualConstraint(ZERO, lenName + "_" + std::to_string(i))));
				lenX = lenX + lenName + "_" + std::to_string(i) + " ";
				if (i % QCONSTMAX == 0) {
					/* (+ sum(len_x_i) */
					if (QCONSTMAX > 1)
						lenX = "(+ " + lenX + ")";
					/*(assert (= const (+ sum(len_x_i)))) */
					constraints.emplace_back(createAssert(createEqualConstraint(lenValue, lenX)));
					lenX = "";
				}
			}
		}
		else {
			std::string lenName = std::string(LENPREFIX) + constNode.second + "_" + std::to_string(std::abs(REGEX_CODE));
			defines.emplace_back(createIntDefinition(lenName));

			if (constNode.first.find("+") != std::string::npos)
				constraints.emplace_back(createAssert(createLessConstraint(ZERO, lenName)));
			else {
				assert(constNode.first.find("*") != std::string::npos);
				constraints.emplace_back(createAssert(createLessEqualConstraint(ZERO, lenName)));
			}

			create_constraints_regex(defines, constraints, constNode.first, constNode.second);
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
	int maxLength = 270;
	for (const auto& constStr : constMap)
		maxLength = std::max(maxLength, (int)constStr.first.length());
	std::string maxLengthStr = std::to_string(maxLength);
	for (const auto& var: allVariables){

		/* len_x = sum(len_x_i)*/
		std::string lenX = "";
		std::string lenVarName = generateVarLength(var);
		for (int i = 0; i < std::max(QMAX, varPieces[var]); ++i) {
			std::string lenTmp = lenVarName + "_" + std::to_string(i);
			defines.emplace_back(createIntDefinition(lenTmp));
			constraints.emplace_back(createAssert(createLessEqualConstraint(ZERO, lenTmp)));
			lenX = lenX + lenTmp + " ";

			if ((i + 1) % QMAX == 0) {
				/* (+ sum(len_x_i) */
				if (QMAX > 1)
					lenX = "(+ " + lenX + ")";
				constraints.emplace_back(createAssert(createEqualConstraint(lenVarName, lenX)));
				lenX = "";
			}
		}

		if (var.find(FLATPREFIX) != std::string::npos || var.substr(0, 6).compare("$$_str") == 0) {
			/* they are internal variables */
			defines.emplace_back(createIntDefinition(lenVarName));
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
	std::string constraint = "(assert (= " + std::string(LENPREFIX) + name + "_" + std::to_string(std::abs(REGEX_CODE)) + " (+ ";
	for (const auto& size : componentSizes){
		std::string tmp = name + "__p" + std::to_string(cnt++);
		defines.emplace_back(createIntDefinition(tmp));
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
			lenX = lenX + " " + LENPREFIX + component;
			cnt ++;
		}
		else if (component.length() > 2) { /* const is not an empty string */
			if(!isRegexStr(component)) {
				lenX = lenX + " " + LENPREFIX + constMap[component.substr(1, component.length() - 2)];
				cnt ++;
			}
			else {
				/* regex */
				assert(constMap.find(component.substr(1, component.length() - 2)) != constMap.end());
				lenX = lenX + " " + LENPREFIX + constMap[component.substr(1, component.length() - 2)] + "_" + std::to_string(abs(REGEX_CODE));
				cnt ++;
			}
		}
	}

	/* (+ sum(len_y)) */
	if (cnt > 1)
		lenX = "(+ " + lenX + ")";

	/*(= len_X (+ sum(len_y)) */
	if (x[0] != '\"')
		lenX = createEqualConstraint(std::string(LENPREFIX) + x, lenX);
	else {
		if(!isRegexStr(x) && !isUnionStr(x))
			lenX = createEqualConstraint(std::to_string(x.length() - 2), lenX);
		else if (isRegexStr(x)){
			lenX = createEqualConstraint(lenX, LENPREFIX + constMap[x.substr(1, x.length() - 2)] + "_" + std::to_string(abs(REGEX_CODE)));
			assert(constMap.find(x.substr(1, x.length() - 2)) != constMap.end());
		}
		else {
			lenX = createEqualConstraint(lenX, LENPREFIX + constMap[x.substr(1, x.length() - 2)]);
			assert(constMap.find(x.substr(1, x.length() - 2)) != constMap.end());
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
				tokens[1].find(FLATPREFIX) == std::string::npos) {
			if (tokens[1].substr(0, 4).compare(LENPREFIX) == 0) {
			}
			else {
				printf("%s : %s\n", tokens[1].c_str(), value.c_str());
			}
		}
	}

	for (const auto& value : strValue)
		if (value.first.find("$$") == std::string::npos &&
				value.first.find(FLATPREFIX) == std::string::npos &&
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
				tokens[1].find(FLATPREFIX) == std::string::npos) {
			if (tokens[1].substr(0, 4).compare(LENPREFIX) == 0) {
				std::string tmp = def.substr(4);
				additionalAssertions.emplace_back("(assert (= (Length " + tokens[1].substr(4) +") " + value + "))\n");
			}
			else {
				if (value[0] != '-')
					additionalAssertions.emplace_back("(assert (= " + tokens[1] + " " + value + "))\n");
				else
					additionalAssertions.emplace_back("(assert (= " + tokens[1] + " (- 0 " + value.substr(1) + ")))\n");
			}
		}
	}

	for (const auto& value : strValue)
		if (value.first.find("$$") == std::string::npos &&
				value.first.find(FLATPREFIX) == std::string::npos &&
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
std::vector<std::string> equalityToSMT(
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


	std::vector<std::string> cases = collectAllPossibleArrangements(
			lhs, rhs,
			lhs_elements, rhs_elements);
	return cases;
}

/*
 * print input
 */
void printEqualMap(std::map<std::string, std::vector<std::vector<std::string>>> equalMap) {
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	for (const auto _eq : equalMap) {
		if (_eq.second.size() > 0) {
			__debugPrint(logFile, "%s = (%ld cases) \n", _eq.first.c_str(), _eq.second.size());
			for (const auto vec : _eq.second) {
				for (const auto s : vec) {
					__debugPrint(logFile, "\t%s ",  s.c_str());
				}
				__debugPrint(logFile, "\n");
			}
			__debugPrint(logFile, "\n");
		}
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
			result = result + " " + LENPREFIX + eqVector[0][i];
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
		for (unsigned i = 0 ; i < it->second.size(); ++i) {
			std::vector<std::string> anEq;
			for (unsigned j = 0; j < it->second[i].size(); ++j) {
				if (it->second[i][j][0] == '\"') { /* AutomataDef */
					std::string constStr = collectConst(it->second[i][j]);
					if (constStr.length() > 2)
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
#ifdef DEBUGLOG
							__debugPrint(logFile, "%d regexElements: %ld\n", __LINE__, regexElements.size());
#endif
							/* assume that regexElements size is 1 */
							assert(regexElements.size() >= 1);
							if (regexElements.size() > 1)
								unknownResult = true;

							unsigned int pos = 0;

							/* add to vector, create a sum for two continuous elements */
							while (pos < regexElements[0].size()){
								if (isRegexStr(regexElements[0][pos])) {
									localElements.emplace_back("\"" + regexElements[0][pos] + "___" + std::to_string(index * 10 + pos) + "\"");
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

	for (const auto _eq : equalitiesMap) {
		if (_eq.first[0] == '"') {
			std::string content = _eq.first.substr(1, _eq.first.length() - 2);
			constMap[content] = "const_" + std::to_string(constCnt++);
		}
		for (const auto v: _eq.second){

			/* create a general value that the component belongs to */
			std::string value = sumStringVector(v);

			/* push to map */
			for (const auto s : v)
				if (s[0] == '\"'){
					std::string content = s.substr(1, s.length() - 2);
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
	__debugPrint(logFile, "%d *** %s ***", __LINE__, __FUNCTION__);
	std::map<std::string, std::vector<std::string>> usedComponents;
	std::map<std::string, int> connectedVarSet;
	connectedVariables.clear();
	/* collect from equality map */
	for (const auto& eq : equalitiesMap) {
		if (eq.second.size() > 4 && eq.first[0] != '"') {
			if (connectedVariables.find(eq.first) == connectedVariables.end())
				connectedVarSet[eq.first] = CONNECTSIZE;
			__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, eq.first.c_str());
		}

		std::map<std::string, std::vector<std::string>> tmpUsedComponents;
		for (const auto& v : eq.second)
			if (v.size() > 1){
				std::map<std::string, int> variableCounting;
				for (const auto& var : v)
					if (var[0] != '"'){
						if (equalitiesMap.find(var) != equalitiesMap.end())
							for (const auto& _eq : equalitiesMap[var]) {
								if (_eq.size() == 1 && _eq[0][0] != '"' && _eq[0].compare(var) != 0){
									variableCounting[_eq[0]]++;
									if (variableCounting[_eq[0]] > 1){
										connectedVarSet[_eq[0]] = CONNECTSIZE;
										__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, _eq[0].c_str());
									}
								}

							}
						variableCounting[var]++;
						if (variableCounting[var] > 1){

							connectedVarSet[var] = CONNECTSIZE;
							__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, var.c_str());
						}
					}

				if (eq.second.size() == 1)
					continue;

				/* push to map */
				for (const auto& var : v)
					if (var[0] != '\"') {
						/* check if component is already in the map*/
						if (usedComponents.find(var) != usedComponents.end()) {
							if (!equalVector(v, usedComponents[var])){
								connectedVarSet[var] = CONNECTSIZE;
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
									connectedVarSet[var] = CONNECTSIZE;
									__debugPrint(logFile, "%d Add %s to connectedVar\n", __LINE__, var.c_str());
									break;
								}
							}

							tmpUsedComponents[var] = v;
						}
					}
			}

		if (eq.second.size() > 1)
			usedComponents.insert(tmpUsedComponents.begin(), tmpUsedComponents.end());
	}

	/* from rewriterMap */
	for (const auto& s : rewriterStrMap) {
		if (s.first.name.compare(CHARAT) == 0 ||
				s.first.name.compare(STARTSWITH) == 0 ||
				s.first.name.compare(ENDSWITH) == 0 ||
				s.first.name.compare(REPLACE) == 0 ||
				s.first.name.compare(REPLACEALL) == 0 ||
				(s.first.name.compare(CONTAINS) == 0 && s.second.compare(FALSETR) == 0) ||
				(s.first.name.compare("=") == 0 && (s.second.compare(FALSETR) == 0 || s.second.compare(TOUPPER) == 0 || s.second.compare(TOLOWER) == 0))){
			StringOP op = s.first;
			__debugPrint(logFile, "%d %s -> %s -- %s\n", __LINE__, op.toString().c_str(), s.first.arg01.c_str(), s.first.arg02.c_str());

			if (s.first.arg01.find(CONCAT) != std::string::npos ||
					s.first.arg02.find(CONCAT) != std::string::npos ||
					s.first.arg02.find("Automata ") != std::string::npos)
				continue;

			if (s.first.name.compare("=") == 0 && s.second.compare(FALSETR) == 0) {
				if (s.first.arg01.compare("\"\"") == 0 || s.first.arg02.compare("\"\"") == 0)
					continue;

				bool canSkip = false;
				if (s.first.arg02[0] == '"' && !isRegexStr(s.first.arg02)) {
					if (equalitiesMap.find(s.first.arg01) != equalitiesMap.end())
						for (const auto _eq : equalitiesMap[s.first.arg01]) {
							for (const auto e : _eq)
								if (e[0] == '"' && !isRegexStr(e) && !isUnionStr(e) && s.first.arg02.find(e) == std::string::npos) {
									canSkip = true;
									break;
								}
							if (canSkip)
								break;
						}
				}

				if (s.first.arg01[0] == '"' && !isRegexStr(s.first.arg01)) {
					if (equalitiesMap.find(s.first.arg02) != equalitiesMap.end())
						for (const auto _eq : equalitiesMap[s.first.arg02]) {
							for (const auto e : _eq)
								if (e[0] == '"' && !isRegexStr(e) && !isUnionStr(e) && s.first.arg01.find(e) == std::string::npos) {
									canSkip = true;
									break;
								}
							if (canSkip)
								break;
						}
				}

				if (canSkip) {
					__debugPrint(logFile, "%d skip %s != %s\n", __LINE__, s.first.arg01.c_str(), s.first.arg02.c_str());
					continue;
				}
			}

			if (s.first.name.compare(CHARAT) == 0){
				if (s.first.arg01[0] != '\"') {
					__debugPrint(logFile, "%d Adding %s to connectedVar\n", __LINE__, s.first.arg01.c_str());
					connectedVarSet[s.first.arg01] = CONNECTSIZE;
				}
			}

			/* add all of variables to the connected var set*/
			if (s.first.arg01[0] != '\"') {
				if (s.first.name.compare("=") == 0 || s.first.name.compare(STARTSWITH) == 0) {
					if (s.first.arg02[0] == '"') {
						if (connectedVarSet.find(s.first.arg01) == connectedVarSet.end())
							connectedVarSet[s.first.arg01] = s.first.arg02.length() - 2;
						else
							connectedVarSet[s.first.arg01] = std::max((int)s.first.arg02.length() - 2, connectedVarSet[s.first.arg01]);
					}
					else
						connectedVarSet[s.first.arg01] = CONNECTSIZE;
				}
				else
					connectedVarSet[s.first.arg01] = CONNECTSIZE;
				__debugPrint(logFile, "%d Adding %s to connectedVar\n", __LINE__, s.first.arg01.c_str());
			}

			if (s.first.arg02[0] != '"') {
				if (s.first.name.compare("=") == 0 || s.first.name.compare(STARTSWITH) == 0) {
					if (s.first.arg01[0] == '"') {
						if (connectedVarSet.find(s.first.arg02) == connectedVarSet.end())
							connectedVarSet[s.first.arg02] = s.first.arg01.length() - 2;
						else
							connectedVarSet[s.first.arg02] = std::max((int)s.first.arg01.length() - 2, connectedVarSet[s.first.arg02]);
					}
					else
						connectedVarSet[s.first.arg02] = CONNECTSIZE;
				}
				else
					connectedVarSet[s.first.arg02] = CONNECTSIZE;
				__debugPrint(logFile, "%d Adding %s to connectedVar\n", __LINE__, s.first.arg02.c_str());
			}
		}
	}

	for (const auto& var : connectedVarSet)
		connectedVariables[var.first] = var.second;

	/* a = b, a is a connected var --> b is connected var */
	for (const auto& eq : equalitiesMap)
		if (connectedVariables.find(eq.first) != connectedVariables.end()){
			for (const auto& v : eq.second)
				if (v.size() == 1){
					if (v[0][0] != '"')
						connectedVariables[v[0]] = connectedVariables[eq.first];
				}
		}

	/* print test connected var */
	if (connectedVariables.size() > 0) {
		__debugPrint(logFile, "%d *** %s ***:\n", __LINE__, __FUNCTION__);

		for (const auto& s : connectedVariables){
			__debugPrint(logFile, "%s - up to %d\n", s.first.c_str(), s.second);
		}
		__debugPrint(logFile, "\n");
	}
}

/**
 * transform char range function
 */
std::vector<std::string> reformatCharRange(std::vector<std::string> v){
	std::vector<std::string> ret;
	for (const auto& s : v) {
		if (s[0] == '"' && s.find('[') != std::string::npos) {
			__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, s.c_str());
			std::string newS = s;
			while (newS.find('[') != std::string::npos) {

				unsigned posStart = 0;
				while (posStart < newS.length() && newS[posStart] != '[')
					posStart++;
				unsigned posFinsih = posStart + 1;
				while (posFinsih < newS.length() && newS[posFinsih] != ']')
					posFinsih++;

				if (posFinsih >= newS.length())
					break;

				if (posFinsih - posStart != 4)
					break;
				std::string tmp = "(";
				for (int i = newS[posStart + 1]; i < newS[posFinsih - 1]; ++i)
					tmp = tmp + (char) i + "|";
				tmp = tmp + (char)newS[posFinsih - 1] + ")+";

				newS.replace(posStart, 6, tmp); // [a-e]+
			}
			ret.emplace_back(newS);
		}
		else
			ret.emplace_back(s);
	}
	return ret;
}

/*
 * Remove all equalities without connected variables and consts
 */
void refineEqualMap(std::map<StringOP, std::string> rewriterStrMap){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	std::map<std::string, std::vector<std::vector<std::string>>> new_eqMap;
	std::map<std::string, std::vector<std::string>> notEqualMap = createNotEqualMap(rewriterStrMap);

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
			for (unsigned k = 0; k < _eq.size(); ++k) {
				if (_eq[k][0] == '\"' /* const */ ||
						connectedVariables.find(_eq[k]) != connectedVariables.end()) {

					tmp_vector.emplace_back(reformatCharRange(_eq));
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
		for (unsigned i = 0; i < tmp_vector.size(); ++i){
			bool notAdd = false;
			for (unsigned j = 0; j < i; ++j){
				if (similarVector(tmp_vector[i], tmp_vector[j], notEqualMap)) {
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
	__debugPrint(logFile, "%d collectAlternativeComponents: %ld\n", __LINE__, components.size());
	if (components.size() > 1){
		for (const auto& c : components) {
			std::vector<std::vector<std::string>> tmp = parseRegexComponents(c);
#ifdef DEBUGLOG
			__debugPrint(logFile, "%d components: %ld\n", __LINE__, tmp.size());
			for (const auto& re : tmp){
				__debugPrint(logFile, "%d ", __LINE__);
				for (const auto &s : re)
					__debugPrint(logFile, "%s ", s.c_str());
				__debugPrint(logFile, "\n");
			}
#endif
			for (const auto& comp : tmp)
				result.emplace_back(comp);
		}
		bool merge = true;
		std::string tmp = "";
		for (const auto& s : result)
			if (s.size() > 0 && isRegexStr(s[0])){
				merge = false;
				break;
			}
			else if (s.size() > 0)
				tmp = tmp + "|" + s[0];

		if (merge == true) {
			tmp = tmp.substr(1);
			__debugPrint(logFile, "%d return %s\n", __LINE__, tmp.c_str());
			return {{tmp}};
		}
		else
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
#ifdef DEBUGLOG
		__debugPrint(logFile, "%d leaving  %s\n", __LINE__, __FUNCTION__);
#endif
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

		__debugPrint(logFile, "%d left = %s --- right = %s\n", __LINE__, left.c_str(), right.c_str());

		if (str[pos] != '|' || str[pos] != '~') {
			std::vector<std::vector<std::string>> leftComponents = parseRegexComponents(left);
			std::vector<std::vector<std::string>> rightComponents = parseRegexComponents(right);
			if (leftComponents.size() > 0) {
				if (rightComponents.size() > 0) {
					for (int i = 0; i < std::min(REGEX_BOUND, (int)leftComponents.size()); ++i)
						for (int j = 0; j < std::min(REGEX_BOUND, (int)rightComponents.size()); ++j) {
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
	for (unsigned i = 0; i < a.size(); ++i)
		if (a[i].compare(b[i]) != 0) {
			return false;
		}
	return true;
}

/*
 *
 */
bool similarVector(
		std::vector<std::string> a,
		std::vector<std::string> b,
		std::map<std::string, std::vector<std::string>> notEqualMap
		){
	if (equalVector(a, b))
		return true;

	unsigned posB = 0;
	for (unsigned i = 0; i < a.size(); ++i){
		if (a[i][0] != '"') {
			if (connectedVariables.find(a[i]) != connectedVariables.end()) {
				return false;
				if (notEqualMap.find(a[i]) == notEqualMap.end())
					return false;

				/* var vs var */
				while (posB < b.size()){
					if (b[posB][0] == '"')
						return false;
					else if (connectedVariables.find(b[posB]) != connectedVariables.end()) {
						return false;
						if (!equalVector(notEqualMap[a[i]], notEqualMap[b[posB]])) {
							return false;
						}
						else {
							posB++;
							break;
						}
					}
					else {
						++posB;
						if (posB > b.size())
							return false;
					}
				}
			}
		}
		else {
			/* const vs const */
			while (posB < b.size()){
				if (b[posB][0] == '"') {
					if (a[i].compare(b[posB]) == 0) {
						posB++;
						break;
					}
					else
						return false;
				}
				else if (connectedVariables.find(b[posB]) != connectedVariables.end()) {
					return false;
				}
				else {
					++posB;
					if (posB > b.size())
						return false;
				}
			}
		}
	}

	for (unsigned i = posB; i < b.size(); ++i)
		if (b[i][0] == '"' || connectedVariables.find(b[i]) != connectedVariables.end())
			return false;

	if (a.size() > 1) {
		/* print test */
		__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
		for (const auto s : a)
			__debugPrint(logFile, "%s ", s.c_str());
		__debugPrint(logFile, "\n");
		for (const auto s : b)
			__debugPrint(logFile, "%s ", s.c_str());
		__debugPrint(logFile, "\n");
	}
	return true;
}

/*
 * remove duplication
 */
std::vector<std::vector<std::string>> refineVectors(std::vector<std::vector<std::string>> list){
	__debugPrint(logFile, "%d *** %s ***: %ld\n", __LINE__, __FUNCTION__, list.size());
	for (const auto& l : list) {
		for (const auto& s : l)
			__debugPrint(logFile, "%s ", s.c_str());
		__debugPrint(logFile, "\n");
	}
	std::vector<std::vector<std::string>> result;
	if (list.size() < 1000) {
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

		for (unsigned int i = 0 ; i < list.size(); ++i)
			if (!duplicated[i])
				result.emplace_back(list[i]);
	}
	else
		result = list;

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
	__debugPrint(logFile, "%d *** %s ***: %ld\n", __LINE__, __FUNCTION__, regexElements.size());
	for (const auto& l : regexElements) {
		for (const auto& s : l)
			__debugPrint(logFile, "%s ", s.c_str());
		__debugPrint(logFile, "\n");
	}
	std::vector<std::vector<std::string>> results;
	for (unsigned i = 0; i < regexElements.size(); ++i) {
		std::vector<std::string> tmp;
		bool isRegex_prev = true;
		for (unsigned j = 0; j < regexElements[i].size(); ++j) {
			if (isRegex_prev == false) {
				isRegex_prev = isRegexStr(regexElements[i][j]) || isUnionStr(regexElements[i][j]);
				if (isRegex_prev == false) {
					std::string tmpStr = tmp[tmp.size() - 1];
					std::string newStr = regexElements[i][j];
					tmp[tmp.size() - 1] = "\"" + tmpStr.substr(1, tmpStr.length() - 2) + newStr.substr(1, newStr.length() - 2) + "\"";
				}
				else
					tmp.emplace_back(regexElements[i][j]);
			}
			else {
				isRegex_prev = isRegexStr(regexElements[i][j]) || isUnionStr(regexElements[i][j]);
				tmp.emplace_back(regexElements[i][j]);
			}
		}
		results.emplace_back(tmp);
	}
	__debugPrint(logFile, "%d leaving %s \n", __LINE__, __FUNCTION__);
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
			std::string content = list[k].substr(1, list[k].length() - 2);
			if (!isRegexStr(list[k])) {
				if (list[k].length() > SPLIT_LOWER_BOUND) /* const string */ {
					if (varPieces.find(content) == varPieces.end())
						varPieces[content] = 0;
					for (int j = varPieces[content]; j < varPieces[content] + QCONSTMAX; ++j) { /* split variables into QMAX parts */
						elements.emplace_back(std::make_pair(content, -(j + 1)));
					}
					varPieces[content] += QCONSTMAX;
				}
				else {
					/* length < SPLIT_LOWER_BOUND */
					elements.emplace_back(std::make_pair(content, -1));
				}
			}
			else {
				/* regex */
				std::string content = list[k].substr(1, list[k].length() - 2);

				elements.emplace_back(std::make_pair(content, REGEX_CODE));
			}
		}
		else {
			if (varPieces.find(list[k]) == varPieces.end())
				varPieces[list[k]] = 0;
			for (int j = varPieces[list[k]]; j < varPieces[list[k]] + QCONSTMAX; ++j) { /* split variables into QMAX parts */
				elements.emplace_back(std::make_pair(list[k], j));
			}
			varPieces[list[k]] += QMAX;
		}

	return elements;
}

/**
 * extra variables
 */
std::vector<std::string> createSetOfFlatVariables(int flatP) {
	std::vector<std::string> result;
	for (int i = 0 ; i < flatP; ++i) {
		std::string varName = FLATPREFIX + std::to_string(noFlatVariables + i);
		result.emplace_back(varName);
		connectedVariables[varName] = CONNECTSIZE;
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
	for (unsigned i = 0; i < std::min(lhs.size(), rhs.size()); ++i)
		if (lhs[i].compare(rhs[i]) == 0)
			prefix = i;
		else
			break;

	/* cut suffix */
	int suffix = -1;
	for (unsigned i = 0; i < std::min(lhs.size(), rhs.size()); ++i)
		if (lhs[lhs.size() - 1 - i].compare(rhs[rhs.size() - 1 - i]) == 0)
			suffix = i;
		else
			break;

	for (unsigned i = prefix + 1; i < lhs.size() - suffix - 1; ++i)
		new_lhs.emplace_back(lhs[i]);

	for (unsigned i = prefix + 1; i < rhs.size() - suffix - 1; ++i)
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
			return TRUESTR;
	}
	return "";
}

/*
 *
 */
unsigned findMaxP(std::vector<std::vector<std::string>> v){
	unsigned maxLocal = 0;

	/* find regex */
//	for (unsigned i = 0; i < v.size(); ++i)
//		for (const auto& s : v[i])
//			if (isRegexStr(s))
//				return 1;
	for (unsigned i = 0; i < v.size(); ++i)
		for (unsigned j = i + 1; j < v.size(); ++j){

			/* optimize: find longest common prefix and posfix */
			std::vector<std::string> lhs;
			std::vector<std::string> rhs;
			optimizeEquality(v[i], v[j], lhs, rhs);

			unsigned cnt = 0;
			for (const auto& s : lhs)
				if (s[0] == '\"' || s.length() > 3)
					cnt++;
			maxLocal = cnt > maxLocal ? cnt : maxLocal;

			cnt = 0;
			for (const auto& s : rhs)
				if (s[0] == '\"' || s.length() > 3)
					cnt++;
			maxLocal = cnt > maxLocal ? cnt : maxLocal;
		}

	return maxLocal;
}
/*
 * Pthread
 * Each thread handles a part in the global map from start -> end
 */
//void *convertEqualities(void *tid){
void convertEqualities(){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = equalitiesMap.begin();
			it != equalitiesMap.end();
			++it) {

		std::string tmp = " ";
		clock_t t;

		/* different tactic for size of it->second */
		const int flatP = 1;
		const int maxPConsidered = 6;
		unsigned maxLocal = findMaxP(it->second);

		__debugPrint(logFile, "%d Max list size: %d\n", __LINE__, maxLocal);

		if (it->second.size() == 0)
			continue;
		assert (it->second[0].size() > 0);

		global_smtStatements.push_back({createLengthConstraintForAssignment(it->first, it->second[0])});

		if (connectedVariables.find(it->first) != connectedVariables.end() || it->first[0] == '"'){
			std::vector<std::pair<std::string, int>> lhs_elements = createEquality({it->first});
			/* compare with others */
			for (const auto& element: it->second) {
				std::vector<std::pair<std::string, int>> rhs_elements = createEquality(element);
				t = clock();
				std::vector<std::string> result = equalityToSMT(	sumStringVector({it->first}),
						sumStringVector(element),
						lhs_elements,
						rhs_elements
				);
				t = clock() - t;

#ifdef PRINTTEST_UNDERAPPROX
				__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
				if (result.size() != 0) {
					/* sync result */
					global_smtStatements.emplace_back(result);
				}
				else {
					__debugPrint(logFile, "%d trivialUnsat = true\n", __LINE__);
					/* trivial unsat */
					trivialUnsat = true;
				}
			}

		}
		else if (maxLocal > maxPConsidered) {
			/* add an eq = flat . flat . flat, then other equalities will compare will it */
			std::vector<std::string> genericFlat = createSetOfFlatVariables(flatP);
			std::vector<std::pair<std::string, int>> lhs_elements = createEquality(genericFlat);
			/* compare with others */
			for (const auto& element: it->second) {
				std::vector<std::pair<std::string, int>> rhs_elements = createEquality(element);
				t = clock();
				std::vector<std::string> result = equalityToSMT(
						sumStringVector(genericFlat),
						sumStringVector(element),
						lhs_elements,
						rhs_elements
				);
				t = clock() - t;

#ifdef PRINTTEST_UNDERAPPROX
				__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
				if (result.size() != 0) {
					/* sync result */
					global_smtStatements.emplace_back(result);
				}
				else {
					__debugPrint(logFile, "%d trivialUnsat = true\n", __LINE__);
					/* trivial unsat */
					trivialUnsat = true;
				}
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
					std::vector<std::string> result = equalityToSMT(
							sumStringVector(it->second[i]),
							sumStringVector(it->second[j]),
							lhs_elements,
							rhs_elements
					);
					t = clock() - t;

#ifdef PRINTTEST_UNDERAPPROX
					__debugPrint(logFile, "%d Convert to SMT: %.3f seconds.\n\n", __LINE__, ((float)t)/CLOCKS_PER_SEC);
#endif
					if (result.size() != 0) {
						/* sync result*/
						global_smtStatements.emplace_back(result);
					}
					else {
						__debugPrint(logFile, "%d trivialUnsat = true\n", __LINE__);
						/* trivial unsat */
						trivialUnsat = true;
					}
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

			std::vector<std::string> result = equalityToSMT(	sumStringVector(it->second[i]),
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
std::string getTrivialRegex(std::string s, int length){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, s.c_str());
	if (s.length() == 0)
		return s;
	else if (s[0] == '"')
		s = s.substr(1, s.length() - 2);
	if (isRegexStr(s) && !isUnionStr(s)) {
		size_t openPar = s.find('(');
		assert (openPar != std::string::npos);
		unsigned closePar = findCorrespondRightParentheses(openPar, s);
		std::set<std::string> components = extendComponent(s.substr(openPar + 1, closePar - openPar - 1));
		std::string ret = "";
		bool found = false;
		createStringFromSet(components, length, ret, found);
		displayListString(components, " components ");
		__debugPrint(logFile, "%d *** %s ***: <%s, %d> -> %s\n", __LINE__, __FUNCTION__, s.c_str(), length, ret.c_str());
		if (found == true)
			return ret;
		else
			return NOTFOUND;
	}
	else {
		return NOTFOUND;
	}
}

/*
 * len = 10, (ab)* --> abababababab
 */
std::string getValueFromRegex(std::string s, int length){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, s.c_str());
	if (s.length() == 0)
		return s;
	else if (s[0] == '"')
		s = s.substr(1, s.length() - 2);
	if(isRegexStr(s)) {
		size_t openPar = s.find('(');
		assert (openPar != std::string::npos);
		unsigned closePar = findCorrespondRightParentheses(openPar, s);
		std::set<std::string> components = extendComponent(s.substr(openPar + 1, closePar - openPar - 1));
		std::string ret = "";
		bool found = false;
		createStringFromSet(components, length, ret, found);
		displayListString(components, " components ");
		__debugPrint(logFile, "%d *** %s ***: <%s, %d> -> %s\n", __LINE__, __FUNCTION__, s.c_str(), length, ret.c_str());
		if (found == true)
			return ret;
		else
			return NOTFOUND;
	}
	else if (isUnionStr(s)){
		std::vector<std::string> components = collectAlternativeComponents(s);
		for (const auto& c : components)
			if ((int)c.length() == length)
				return c;
		assert(false);
		return NOTFOUND;
	}
	else {
		/**
		 * simple const
		 */
		return NOTFOUND;
	}
}

/*
 *
 */
bool isInternalVar(std::string name,
		std::map<std::string, int> len){
	unsigned pos = name.length() - 1;
	if (name.find("$$") == 0)
		return true;
	while (pos > 0){
		if (!(name[pos] >= '0' && name[pos] <= '9')){
			if (name[pos] != '_')
				return false;
			std::string tmp = name.substr(0, pos);
			if (len.find(tmp) != len.end())
				return true;
			else {
				return false;
			}
		}
		pos = pos - 1;
	}
	return false;
}



/*
 * of the form xxxx_123 and xxx is in len map
 */

/*
 *
 */
void syncConst(
		std::map<std::string, std::string> solverValues,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	std::set<std::string> propagatingList;
	for (const auto& var : equalitiesMap){

		/* init value */
		if (var.first[0] == '"') {
			if (!isRegexStr(var.first) && !isUnionStr(var.first)){
				std::vector<int> tmp;
				for (int i = 0; i < getVarLength(var.first, len); ++i)
					tmp.emplace_back(var.first[i + 1]);
				strValue[getVarName(var.first)] = tmp;
				propagatingList.emplace(var.first);
			}
			else {
				int varLength = getVarLength(var.first, len);
				std::string tmp = getTrivialRegex(var.first, varLength);
				if (tmp.compare(NOTFOUND) != 0) {
					assert(varLength == (int)tmp.length());
					std::vector<int> tmpVector(varLength, 0);
					for (int i = 0; i < varLength; ++i)
						tmpVector[i] = tmp[i];
					strValue[getVarName(var.first)] = tmpVector;
					propagatingList.emplace(var.first);
					if (completion == false) {
						__debugPrint(logFile, ">> %d cannot find var: %s\n", __LINE__, var.first.c_str());
						return;
					}
					__debugPrint(logFile, ">> %d done synConst\n", __LINE__);
					continue;
				}
			}
		}

		bool update = false;
		std::vector<int> tmp = getVarValue(var.first, len, strValue);
		for (const auto& eq : var.second){
			__debugPrint(logFile, "%d varName = %s\n", __LINE__, var.first.c_str());
			int pos = 0;
			for (const auto& s : eq){
				int lengthS = getVarLength(s, len);
				if (s[0] == '"') {
					if (!isRegexStr(s) && !isUnionStr(s)) {
						/* assign value directly */
						std::vector<int> tmpValue;
						for (unsigned i = 1; i < s.length() - 1; ++i) {
							tmpValue.emplace_back(s[i]);
							if (tmp[pos + i - 1] == 0) {
								tmp[pos + i - 1] = s[i];
								update = true;
							}
							else {
								if (tmp[pos + i - 1] != s[i]) {
									__debugPrint(logFile, "%d @%d/%d/%i %c vs %c in %s\n", __LINE__, pos, i, pos + i - 1, tmp[pos + i - 1], s[i], s.c_str());
								}
								assert(tmp[pos + i - 1] == s[i]);
							}
						}

						strValue[getVarName(s)] = tmpValue;
					}
					else if (isRegexStr(s)) {
						/* find value */
						assert(constMap.find(s.substr(1, s.length() - 2)) != constMap.end());
						std::string tmpRegex = getTrivialRegex(s, lengthS);
						if (tmpRegex.compare(NOTFOUND) != 0) {
							std::vector<int> tmpVector;
							for (unsigned i = 0; i < tmpRegex.length(); ++i)
								tmpVector.emplace_back(tmpRegex[i]);
							strValue[getVarName(s)] = tmpVector;
							propagatingList.emplace(s);
						}
					}
					else if (isUnionStr(s)){
//						std::string varName = getVarName(s);
//						if (solverValues.find(varName) != solverValues.end()){
//							assert((int)solverValues[varName].length() == getVarLength(s, len));
//							std::vector<int> tmpVector;
//							for (unsigned i = 0; i < solverValues[varName].length(); ++i)
//								tmpVector.emplace_back(solverValues[varName][i]);
//							strValue[getVarName(s)] = tmpVector;
//							propagatingList.emplace(s);
//						}
					}
				}
				pos += lengthS;

			}
		}
		if (update == true) {
			strValue[getVarName(var.first)] = tmp;
			propagatingList.emplace(var.first);
		}
	}

	for (const auto& s : propagatingList) {
		if (s[0] == '"')
			forwardPropagate(s, len, strValue, completion);
		if (s[0] == '"' || equalitiesMap[s].size() > 1)
			backwardPropagarate(s, len, strValue, completion);
		if (completion == false) {
			__debugPrint(logFile, ">> %d cannot find var: %s\n", __LINE__, s.c_str());
			return;
		}
	}
	__debugPrint(logFile, "%d >> done %s \n", __LINE__, __FUNCTION__);
}

/*
 *
 */
std::string getVarName(std::string s){
	if (s[0] == '"'){
		assert(constMap.find(s.substr(1, s.length() - 2)) != constMap.end());
		return constMap[s.substr(1, s.length() - 2)];
	}
	return s;
}

/*
 *
 */
int getVarLength(
		std::string newlyUpdate,
		std::map<std::string, int> len){
	if (newlyUpdate[0] == '"'){
		std::string tmp = newlyUpdate.substr(1, newlyUpdate.length() - 2);
		tmp = constMap[tmp];
		assert(len.find(tmp) != len.end());
		return len[tmp];
	}
	else {
//		__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, newlyUpdate.c_str());
		assert(len.find(newlyUpdate) != len.end());
		return len[newlyUpdate];
	}
}

/*
 *
 */
std::vector<int> getVarValue(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue){
	if (newlyUpdate[0] == '"'){
		std::string tmp = newlyUpdate.substr(1, newlyUpdate.length() - 2);
		tmp = constMap[tmp];
		if (strValue.find(tmp) != strValue.end()) {
			std::vector<int> value = strValue[tmp];
			int length = getVarLength(newlyUpdate, len);
			if ((int)value.size() < length) {
				for (int i = (int)value.size(); i < length; ++i)
					value.emplace_back(0);
				strValue[tmp] = value;
			}
			return value;
		}
		else {
			int length = getVarLength(newlyUpdate, len);
			strValue[tmp] = std::vector<int>(length, 0);
			return strValue[tmp];
		}
	}
	else {
		if (strValue.find(newlyUpdate) != strValue.end()) {
			std::vector<int> value = strValue[newlyUpdate];
			int length = getVarLength(newlyUpdate, len);
			if ((int)value.size() < length) {
				for (int i = (int)value.size(); i < length; ++i)
					value.emplace_back(0);
				strValue[newlyUpdate] = value;
			}
			return value;
		}
		else {
			int length = getVarLength(newlyUpdate, len);
			strValue[newlyUpdate] = std::vector<int>(length, 0);
			return strValue[newlyUpdate];
		}

	}
}

/*
 * a = b . c .We know b, need to update a
 */
void forwardPropagate(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***: %s (completion : %d)\n", __LINE__, __FUNCTION__, newlyUpdate.c_str(), completion? 1 : 0);
	if (completion == false)
		return;
	std::vector<int> sValue = getVarValue(newlyUpdate, len, strValue);
	int length = sValue.size();

	if (length == 0) {
		return;
	}

	for (unsigned i = 0; i < sValue.size(); ++i)
		if (sValue[i] != 0) {
			__debugPrint(logFile, "%c", (char)sValue[i]);
		}
		else
			__debugPrint(logFile, "%d", sValue[i]);
	__debugPrint(logFile, "\n");

	for (const auto& var : equalitiesMap){
		if (var.first[0] == '"' && !isRegexStr(var.first) && !isUnionStr(var.first))
			continue;
		std::vector<int> value = getVarValue(var.first, len, strValue);
		int varLen = value.size();

		/* update parents */
		bool foundInParents = false;
		for (const auto& eq : var.second)
			if (std::find(eq.begin(), eq.end(), newlyUpdate) != eq.end()) {
				for (unsigned i = 0; i < value.size(); ++i)
					if (value[i] != 0) {
						__debugPrint(logFile, "%c", (char)value[i]);
					}
					else
						__debugPrint(logFile, "%d", value[i]);
				__debugPrint(logFile, "\n");
				int pos = 0;
				for (const auto& s : eq) {
					int varLength = getVarLength(s, len);
					if (s.compare(newlyUpdate) == 0){
						__debugPrint(logFile, "%d update %s by %s, value size = %ld\n", __LINE__, var.first.c_str(), newlyUpdate.c_str(), value.size());

						for (int i = 0; i < varLength; ++i)
							if (value[pos + i] == 0 && sValue[i] != 0) {
								value[pos + i] = sValue[i];
								foundInParents = true;
							}
							else if (value[pos + i] != 0 && sValue[i] != 0 && value[pos + i] != sValue[i]) {
								__debugPrint(logFile, "%d error when %s at %d/%d/%ld of %s\n", __LINE__, newlyUpdate.c_str(), pos, pos + i, value.size(), var.first.c_str());
								completion = false;
								return;
							}
					}
					pos += varLength;
				}
			}

		if (foundInParents) {
			__debugPrint(logFile, "%d %s update var : %s, len = %d, size value = %ld\n", __LINE__, newlyUpdate.c_str(), var.first.c_str(), varLen, value.size());
			for (unsigned i = 0; i < value.size(); ++i)
				if (value[i] != 0) {
					__debugPrint(logFile, "%c", (char)value[i]);
				}
				else
					__debugPrint(logFile, "%d", value[i]);
			__debugPrint(logFile, "\n");
			strValue[getVarName(var.first)] = value;
			/* update it parents */
//			forwardPropagate(var.first, len, strValue, completion);
//			if (completion == false) {
//				__debugPrint(logFile, ">> %d cannot find var: %s\n", __LINE__, var.first.c_str());
//				return;
//			}


			/* update peers */
			if (var.second.size() > 1) {
				__debugPrint(logFile, ">> %d update peers\n", __LINE__);
				for (const auto& eq : var.second){
					value = getVarValue(var.first, len, strValue);
					int pos = 0;
					for (const auto& s : eq){
						if (isConstStr(s) && !isUnionStr(s)) {
							pos += getVarLength(s, len);
						}
						else {
							int varLength = getVarLength(s, len);
							std::vector<int> sValue = getVarValue(s, len, strValue);

							bool updated = false;
							for (int i = 0; i < varLength; ++i) {
								if (sValue[i] != value[pos + i]) {
									updated = true;
									sValue[i] = value[pos + i];
								}
							}
							if (updated == true) {

								strValue[getVarName(s)] = sValue;
								if (equalitiesMap.find(s) == equalitiesMap.end())
									forwardPropagate(s, len, strValue, completion);
								else
									backwardPropagarate(s, len, strValue, completion);
								if (completion == false) {
									__debugPrint(logFile, ">> %d cannot find var: %s\n", __LINE__, s.c_str());
									return;
								}
								__debugPrint(logFile, ">> %d done update child\n", __LINE__);
							}
							pos += varLength;
						}
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
		bool &assigned,
		bool assignAnyway = false){
	int lenVar = getVarLength(name, len);

	__debugPrint(logFile, "%d *** %s ***: %s = %s, len = %d\n", __LINE__, __FUNCTION__, name.c_str(), value.c_str(), lenVar);
	std::vector<int> val = getVarValue(name, len, strValue);

	__debugPrint(logFile, ">> %d: ", __LINE__);
	for (int i = 0; i < lenVar; ++i)
		if (val[i] != 0) {
			__debugPrint(logFile, "%c", val[i]);
		}
		else
			__debugPrint(logFile, "%d", val[i]);
	__debugPrint(logFile, "\n");

	/* update based on previous values */
//	if (assignAnyway)
//		for (const auto& eq : equalitiesMap[name]){
//			int pos = 0;
//			for (const auto& var : eq) {
//				int tmpLen = getVarLength(var, len);
//				if (var[0] == '"') {
//				}
//				else {
//					std::vector<int> tmpValue = getVarValue(var, len, strValue);
//					/* add an evaluated value */
//					for (int i = 0; i < tmpLen; ++i)
//						if (val[pos + i] == 0)
//							val[pos + i] = tmpValue[i];
//						else {
//							if (val[pos + i] != 0 && tmpValue[i] != 0 && val[pos + i] != tmpValue[i]) {
//								len[name] = -10001;
//								return val;
//							}
//						}
//				}
//				pos += tmpLen;
//			}
//			__debugPrint(logFile, "%d pos = %d and lenVar = %d\n", __LINE__, pos, lenVar);
//			assert(pos == lenVar);
//		}

	/* update values found by the solver & previous iterations */
	for (int i = 0; i < lenVar; ++i)
		if (val[i] == 0)
			if (i < (int)value.length())
				val[i] = value[i];

	bool canAssign = false;
	for (int i = 0; i < lenVar; ++i)
		if (val[i] != 0) {
			canAssign = true;
			break;
		}

	/* do not support substr */

	if (canAssign || assignAnyway) {
		for (int i = 0; i < lenVar; ++i)
			if (val[i] == 0)
				val[i] = DEFAULT_CHAR;
	}
	else {
		/* cannot assign because we do not know anything */
		assigned = false;
		return val;
	}

	__debugPrint(logFile, ">> %d: ", __LINE__);
	for (int i = 0; i < lenVar; ++i)
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
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***: %s (completion: %d)\n", __LINE__, __FUNCTION__, newlyUpdate.c_str(), completion ? 1 : 0);
	if (completion == false)
		return;

	std::vector<int> value = getVarValue(newlyUpdate, len, strValue);
	int length = getVarLength(newlyUpdate, len);

	if (length == 0) {
		return;
	}

	for (unsigned i = 0; i < value.size(); ++i)
		if (value[i] != 0) {
			__debugPrint(logFile, "%c", value[i]);
		}
		else {
			__debugPrint(logFile, "%d", value[i]);
		}
	__debugPrint(logFile, "\n");
	__debugPrint(logFile, "%d equal size: %ld\n", __LINE__, equalitiesMap[newlyUpdate].size());
	for (const auto& eq : equalitiesMap[newlyUpdate]){
		int pos = 0;
		__debugPrint(logFile, "%d step 0: size = %ld\n", __LINE__, eq.size());
		for (const auto& var : eq) {
			__debugPrint(logFile, "%d step 0.1: var = %s\n", __LINE__, var.c_str());
			if (var[0] == '"') {
				int lengthVar = getVarLength(var, len);
				__debugPrint(logFile, "%d length = %d\n", __LINE__, lengthVar);
				if (isRegexStr(var) || isUnionStr(var)) {
					bool update = false;
					std::vector<int> sValue = getVarValue(var, len, strValue);

					for (int i = 0; i < lengthVar; ++i)
						if (value[pos + i] != 0 && sValue[i] != 0 && value[pos + i] != sValue[i]) {
							completion = false;
							return;
						}
						else if (value[pos + i] != 0 && sValue[i] == 0){
							sValue[i] = value[pos + i];
							update = true;
						}
						else if (value[pos + i] == 0 && sValue[i] != 0){
							__debugPrint(logFile, "%d weird case at i = %d, %d\n", __LINE__, i, sValue[i]);
						}
						else {
							__debugPrint(logFile, "%d weird case at i %d = %d, pos + i: %d vs %d\n", __LINE__, i, sValue[i], pos + i, value[pos + i]);
						}

					if (update == true) {
						strValue[getVarName(var)] = sValue;
						__debugPrint(logFile, "%d var: %s --> len = %d\n", __LINE__, var.c_str(), lengthVar);
						forwardPropagate(var, len, strValue, completion);
						if (completion == false) {
							__debugPrint(logFile, ">> %d cannot find value for var: %s\n", __LINE__, var.c_str());
							return;
						}
					}
					else {
						__debugPrint(logFile, ">> %d no update for var: %s\n", __LINE__, var.c_str());
					}
				}

				pos += lengthVar;
			}
			else if(strValue.find(var) != strValue.end()){
				std::vector<int> sValue = getVarValue(var, len, strValue);
				int lengthVar = getVarLength(var, len);
				/* verify a determined value */


				bool update = false;
				for (int i = 0; i < lengthVar; ++i)
					if (value[pos + i] != 0 && sValue[i] != 0 && value[pos + i] != sValue[i]) {
						completion = false;
						return;
					}
					else if (value[pos + i] != 0 && sValue[i] == 0){
						sValue[i] = value[pos + i];
						update = true;
					}
					else if (value[pos + i] == 0 && sValue[i] != 0){
					}

				pos += lengthVar;

				if (update == true) {
					__debugPrint(logFile, "%d update existed value\n", __LINE__);
					for (unsigned i = 0; i < sValue.size(); ++i)
						if (sValue[i] != 0) {
							__debugPrint(logFile, "%c", sValue[i]);
						}
						else
							__debugPrint(logFile, "%d", sValue[i]);
					__debugPrint(logFile, "\n");

					strValue[getVarName(var)] = sValue;
					forwardPropagate(var, len, strValue, completion);
					if (completion == false) {
						__debugPrint(logFile, ">> %d cannot find value for var: %s\n", __LINE__, var.c_str());
						return;
					}
				}
			}
			else {
				__debugPrint(logFile, "%d assign a new value\n", __LINE__);
				assert(len.find(var) != len.end());
				int lengthVar = getVarLength(var, len);
				/* update a new value */
				std::vector<int> sValue;
				for (int i = 0; i < lengthVar; ++i)
					sValue.emplace_back(value[pos + i]);
				strValue[getVarName(var)] = sValue;
				pos += lengthVar;
				forwardPropagate(var, len, strValue, completion);
				if (completion == false) {
					__debugPrint(logFile, ">> %d cannot find value for var: %s\n", __LINE__, var.c_str());
					return;
				}
			}
		}
		__debugPrint(logFile, "%d %s: %d == %d\n", __LINE__, newlyUpdate.c_str(), pos, length);
		assert(pos == length);
	}
}

/*
 *
 */
std::string getNameFromConst(std::string constX){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, constX.c_str());
	for (const auto& s : constMap)
		if (s.second.compare(constX) == 0)
			return "\"" + s.first + "\"";
	return "";
}

/*
 *
 */
bool needValue(std::string name,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> strValue){
	std::vector<int> value = getVarValue(name, len, strValue);
	for (const auto& v : value)
		if (v == 0)
			return true;
	return false;
}


/*
 *
 */
bool isBlankValue(std::string name,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> strValue){
	std::vector<int> value = getVarValue(name, len, strValue);
	for (const auto& v : value)
		if (v != 0)
			return false;
	return true;
}

/*
 *
 */
std::string findEqValueInConcat(
		std::string concat,
		std::map<std::string, int> len){
	std::vector<std::pair<std::string, int>> tokens = parseTerm(concat);
	std::string ret = "";
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, concat.c_str());
	for (const auto& token : tokens){
		if (token.first[0] == '"') {
			if (token.first.length() > 2) {
				if (ret.length() == 0)
					ret = token.first;
				else
					return "";
			}
		}
		else if (token.first.compare("(") != 0 && token.first.compare(")") != 0 && token.first.compare(CONCAT) != 0 &&
				getVarLength(token.first, len) > 0) {
			if (ret.length() == 0)
				ret = token.first;
			else
				return "";
		}
	}
	__debugPrint(logFile, "%d >> %s\n", __LINE__, ret.c_str());
	return ret;
}

std::map<std::string, int> createSimpleEqualMap(
		std::vector<StringOP> equalities,
		std::map<std::string, int> len){
	std::map<std::string, int> index;
	int maxIndex = 0;
	for (const auto& op : equalities){
		std::string arg01 = op.arg01;
		std::string arg02 = op.arg02;
		if (arg02.find("(" + std::string(CONCAT)) == 0){
			arg02 = findEqValueInConcat(arg02, len);
		}
		if (arg02.length() > 0) {
			if (index.find(arg01) != index.end()){
				if (index.find(arg02) != index.end()) {
					int num01 = index[arg01];
					int num02 = index[arg02];
					for (const auto& v : index)
						if (v.second == num02)
							index[v.first] = num01;
				}
				else {
					index[arg02] = index[arg01];
				}

			}
			else if (index.find(arg02) != index.end()){
				index[arg01] = index[arg02];
			}
			else {
				maxIndex++;
				index[arg01] = maxIndex;
				index[arg02] = maxIndex;
			}
		}
		else {
			if (index.find(arg01) == index.end()){
				maxIndex++;
				index[arg01] = maxIndex;
			}
		}
	}
	return index;
}

/*
 *
 */
std::vector<std::string> findEqualVar(
		std::string varName,
		std::vector<StringOP> equalities,
		std::map<std::string, int> len){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, varName.c_str());
	std::vector<std::string> ret;
	ret.emplace_back(varName);
	unsigned pos = 0;
	while (pos < ret.size()) {
		varName = ret[pos++];
		for (const auto& op : equalities) {
			std::string arg01 = op.arg01;
			std::string arg02 = op.arg02;
			assert(arg01.find("(" + std::string(CONCAT)) != 0);

			if (arg01.compare(varName) == 0) {
				if (std::find(ret.begin(), ret.end(), arg02) == ret.end()) {
					/* x = concat y z and |z| = 0 */
					if (arg02.find("(" + std::string(CONCAT)) == 0){
						__debugPrint(logFile, "%d varname: %s\n", __LINE__, varName.c_str());
						std::string tmp = findEqValueInConcat(arg02, len);
						if (tmp.length() > 0 && std::find(ret.begin(), ret.end(), tmp) == ret.end()) {
							__debugPrint(logFile, "%d adding %s\n", __LINE__, tmp.c_str());
							ret.emplace_back(tmp);
						}
					}
					else /* x = y*/ {
						__debugPrint(logFile, "%d adding %s\n", __LINE__, arg02.c_str());
						ret.emplace_back(arg02);
					}
				}
			}
			else {
				if (arg02.compare(varName) == 0) {
					if (std::find(ret.begin(), ret.end(), arg01) == ret.end()) {
						__debugPrint(logFile, "%d adding %s\n", __LINE__, arg01.c_str());
						ret.emplace_back(arg01);
					}
				}
				/* y = concat x z and |z| = 0 */
				else if (std::find(ret.begin(), ret.end(), arg01) == ret.end() &&
						arg02.find(varName) != std::string::npos) {
					if (arg02.find("(" + std::string(CONCAT)) == 0){
						std::string tmp = findEqValueInConcat(arg02, len);
						if (tmp.compare(varName) == 0) {
							__debugPrint(logFile, "%d adding %s\n", __LINE__, arg01.c_str());
							ret.emplace_back(arg01);
						}
					}
				}
			}
		}
	}
	return ret;
}

/*
 *
 */
bool findExistsingValue(
		std::string varName,
		std::vector<StringOP> equalities,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		std::vector<std::string> eqVar){
	__debugPrint(logFile, "%d *** %s ***: %s\n", __LINE__, __FUNCTION__, varName.c_str());
	bool foundValue = false;

	displayListString(eqVar, "eq value");
	std::vector<int> value;
	for (const auto& var : eqVar){
		if (var[0] == '"') {
			for (unsigned i = 1; i < var.length() - 1; ++i)
				value.emplace_back(var[i]);
			foundValue = true;
			break;
		}
		else if (!needValue(var, len, strValue)) {
			foundValue = true;
			value = strValue[var];
			break;
		}
	}



	if (!foundValue) {
		__debugPrint(logFile, "%d not found value %s yet\n", __LINE__, varName.c_str());
		/* find value from Concat */
		for (const auto& op : equalities){
			if (op.arg02.find("(" + std::string(CONCAT)) == 0 &&
					std::find(eqVar.begin(), eqVar.end(), op.arg01) == eqVar.end()){
				std::vector<std::pair<std::string, int>> tokens = parseTerm(op.arg02);
				std::vector<std::string> tmpTokens;
				for (const auto& token : tokens)
					if (token.first.compare("(") != 0 && token.first.compare(")") != 0 && token.first.compare(CONCAT) != 0)
						tmpTokens.emplace_back(token.first);
				unsigned pos = 0;
				std::vector<int> tmpVal = getVarValue(op.arg01, len, strValue);
				__debugPrint(logFile, "%d %s\n", __LINE__, op.arg02.c_str());
				for (const auto& token : tmpTokens)
					if (std::find(eqVar.begin(), eqVar.end(), token) != eqVar.end()){
						int leng = getVarLength(varName, len);
						if (pos + leng <= tmpVal.size()){
							value.clear();
							for (unsigned i = pos; i < pos + leng; ++i)
								value.emplace_back(tmpVal[i]);
							foundValue = true;
							break;
						}
						else
							break;
					}
					else {
						if (token[0] == '"')
							pos += token.length() - 2;
						else if (needValue(token, len, strValue)){
							std::vector<int> tmp01;
							int leng = getVarLength(token, len);
							if (pos + leng <= tmpVal.size()) {
								/* weird case: some information from solver is not correct */
								for (unsigned i = pos; i < pos + leng; ++i)
									tmp01.emplace_back(tmpVal[i]);
								strValue[token] = tmp01;
							}
							pos += leng;

						}
						else
							pos += getVarLength(token, len);
					}
			}
		}
	}


	/* update for all */
	if (foundValue) {
		for (const auto& var : eqVar) {
			__debugPrint(logFile, "%d update: %s, value = %ld\n", __LINE__, var.c_str(), value.size());
			strValue[var] = value;
		}
	}
	return foundValue;
}

/*
 * create str values after running Z3
 */
void formatOtherVars(
		std::vector<unsigned> indexes,
		std::map<std::string, std::string> solverValues,
		std::vector<std::pair<std::string, int>> lenVector,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);

	/* get less important equalities */
	std::vector<StringOP> equalities;
	for (const auto& op : orgRewriterStrMap){
		if (op.first.name.compare("=") == 0 &&
				op.second.compare(TRUESTR) == 0 &&
				op.first.arg02.find("\"") == std::string::npos &&
				op.first.arg01.find("\"") == std::string::npos){
			StringOP _op("=", op.first.arg01, op.first.arg02);
			if (op.first.arg01.find("(" + std::string(CONCAT)) == 0) {
				_op.arg01 = op.first.arg02;
				_op.arg02 = op.first.arg01;
			}
			equalities.emplace_back(_op);
			__debugPrint(logFile, "%d %s\n", __LINE__, _op.toString().c_str());
		}
	}

	std::map<std::string, int> index = createSimpleEqualMap(equalities, len);

	/* 3rd: handling other vars */
	for (const auto& s : indexes) {
		std::string varName = lenVector[s].first;
		if (allVariables.find(varName) == allVariables.end() || isInternalVar(varName, len))
			continue;
		if (lenVector[s].second == 0) {
		}
		else {
			bool assigned = true;

			/* skip if it is a subvar: _1_2*/
			if (varName.length()  == 0 )
				continue;

			if (needValue(varName, len, strValue)) {
				__debugPrint(logFile, "%d consider var: %s\n", __LINE__, varName.c_str());

				std::vector<std::string> eqVar;
				if (index.find(varName) == index.end()) {
					eqVar.emplace_back(varName);
				}
				else {
					int num = index[varName];
					for (const auto& v : index)
						if (v.second == num)
							eqVar.emplace_back(v.first);
				}

				if (isBlankValue(varName, len, strValue))
					if (findExistsingValue(varName, equalities, len, strValue, eqVar))
						continue;
				std::string solverValue = solverValues[varName];
				std::vector<int> tmp = createString(varName, solverValue, len, strValue, assigned, createAnyway);

				if (assigned) {
					__debugPrint(logFile, "%d assign: %s\n", __LINE__, varName.c_str());
					for (const auto& var : eqVar) {
						__debugPrint(logFile, "%d update: %s\n", __LINE__, var.c_str());
						strValue[var] = tmp;
					}
					if (completion == false) {
						__debugPrint(logFile, ">> %d cannot find value for var: %s\n", __LINE__, varName.c_str());
					}
					__debugPrint(logFile, ">> %d done formating %s\n", __LINE__, varName.c_str());
				}
				else
					__debugPrint(logFile, "%d cannot assign: %s\n", __LINE__, varName.c_str());
			}
		}
	}
}

/*
 *
 */
void formatRegexes(
		std::vector<unsigned> indexes,
		std::map<std::string, std::string> solverValues,
		std::vector<std::pair<std::string, int>> lenVector,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	/* 2nd: handling regex */
	for (const auto& s : indexes) {
		std::string varName = lenVector[s].first;
		if (varName.find("const") != std::string::npos){

			if (varName.length() > 4 && varName.substr(varName.length() - 4).compare("_100") == 0)
				varName = varName.substr(0, varName.length() - 4);
			std::string orgVarName = varName;

			std::string solverValue = solverValues[varName];
			varName = getNameFromConst(varName);

			/* skip if it is a subvar: _1_2*/
			if (varName.length()  == 0)
				continue;

			if (needValue(varName, len, strValue)) {
				__debugPrint(logFile, "%d consider var: %s\n", __LINE__, varName.c_str());
				std::string tmpStr = getValueFromRegex(varName, getVarLength(varName, len));
				if (tmpStr.compare(NOTFOUND) != 0){
					assert((int)tmpStr.length() == getVarLength(varName, len));
					std::vector<int> tmp;
					for (unsigned i = 0; i < tmpStr.length(); ++i)
						tmp.push_back(tmpStr[i]);
					__debugPrint(logFile, "%d assign: %s: %s\n", __LINE__, varName.c_str(), tmpStr.c_str());
					strValue[orgVarName] = tmp;
					backwardPropagarate(varName, len, strValue, completion);
					forwardPropagate(varName, len, strValue, completion);
					if (completion == false) {
						__debugPrint(logFile, ">> %d cannot find value for var: %s\n", __LINE__, varName.c_str());
					}
					__debugPrint(logFile, ">> %d done formating %s\n", __LINE__, varName.c_str());
				}
				else
					__debugPrint(logFile, "%d cannot assign: %s\n", __LINE__, varName.c_str());
			}
		}
	}
}

/*
 *
 */
void formatConnectedVars(
		std::vector<unsigned> indexes,
		std::map<std::string, std::string> solverValues,
		std::vector<std::pair<std::string, int>> lenVector,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion){
	/* 1st: handling connected vars */
	for (const auto& s : indexes) {
		std::string varName = lenVector[s].first;
		if (allVariables.find(varName) == allVariables.end() ||
				isInternalVar(varName, len))
			continue;
		if (lenVector[s].second == 0) {
			strValue[varName] = {};
		}
		else {

			if (varName.length() > 4 && varName.substr(varName.length() - 4).compare("_100") == 0)
				varName = varName.substr(0, varName.length() - 4);
			std::string orgVarName = varName;

			if (connectedVariables.find(varName) != connectedVariables.end()) {
				__debugPrint(logFile, "%d varname = %s\n", __LINE__, varName.c_str());
				std::string solverValue = solverValues[varName];
				if (varName.find("const") != std::string::npos)
					varName = getNameFromConst(varName);

				/* skip if it is a subvar: _1_2*/
				if (varName.length()  == 0 )
					continue;

				if (needValue(varName, len, strValue)) {
					__debugPrint(logFile, "%d consider var: %s\n", __LINE__, varName.c_str());
					bool assigned = true;
					std::vector<int> tmp = createString(varName, solverValue, len, strValue, assigned);
					if (assigned) {
						__debugPrint(logFile, "%d assign: %s\n", __LINE__, varName.c_str());
						strValue[orgVarName] = tmp;

						backwardPropagarate(varName, len, strValue, completion);
						forwardPropagate(varName, len, strValue, completion);
						if (completion == false) {
							__debugPrint(logFile, ">> %d cannot find value for var: %s\n", __LINE__, varName.c_str());
						}
						__debugPrint(logFile, ">> %d done formating %s\n", __LINE__, varName.c_str());
					}
					else
						__debugPrint(logFile, "%d cannot assign: %s\n", __LINE__, varName.c_str());
				}
			}
		}
	}
}

/*
 * create str values after running Z3
 */
std::map<std::string, std::string> formatResult(
		std::map<std::string, std::string> len,
		std::map<std::string, std::string> _strValue,
		bool &completion){
	__debugPrint(logFile, "%d *** %s ***\n", __LINE__, __FUNCTION__);
	std::vector<std::pair<std::string, int>> lenVector;
	std::map<std::string, int> lenInt;
	std::map<std::string, std::string> strValue;

	/* format lengths */
	for (const auto& s : len)
		if (s.first.find(LENPREFIX) == 0){
			std::string name = s.first.substr(4);
			lenVector.push_back(std::make_pair(name, atoi(s.second.c_str())));
			lenInt[name] = atoi(s.second.c_str());
			if (name.length() > 4 && name.substr(name.length() - 4).compare("_100") == 0) {
				lenInt[name.substr(0, name.length() - 4)] = atoi(s.second.c_str());
				__debugPrint(logFile, "%d %s : %s -> %d\n", __LINE__, name.substr(0, name.length() - 4).c_str(), s.second.c_str(), atoi(s.second.c_str()));
			}
			__debugPrint(logFile, "%d %s : %s -> %d\n", __LINE__, name.c_str(), s.second.c_str(), atoi(s.second.c_str()));
		}
		else {
			lenVector.push_back(std::make_pair(s.first, atoi(s.second.c_str())));
			lenInt[s.first] = atoi(s.second.c_str());
		}

	/* format values */
	for (const auto& s : _strValue)
		if (s.first.find(ARRPREFIX) == 0){
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
		if (isInternalVar(varName, lenInt))
			continue;
		finalStrValue[var.first] = std::vector<int>(lenInt[var.first], 0);
	}

	for (const auto& var : lenInt) {
			__debugPrint(logFile, "%d: len %s = %d\n", __LINE__, var.first.c_str(), var.second);
			}

	syncConst(strValue, lenInt, finalStrValue, completion);
	formatConnectedVars(indexes, strValue, lenVector, lenInt, finalStrValue, completion);

	for (const auto& s: finalStrValue) {
		__debugPrint(logFile, ">> %d: len = %d, %s", __LINE__, lenInt[s.first], s.first.c_str());
		for (unsigned i = 0; i < s.second.size(); ++i)
			if (s.second[i] != 0) {
				__debugPrint(logFile, "%c", s.second[i]);
			}
			else
				__debugPrint(logFile, "0");
		__debugPrint(logFile, "\n");
	}

	formatRegexes(indexes, strValue, lenVector, lenInt, finalStrValue, completion);
	formatOtherVars(indexes, strValue, lenVector, lenInt, finalStrValue, completion);
	std::map<std::string, std::string> finalResult;
	for (const auto& var : finalStrValue){
		int varLength = getVarLength(var.first, lenInt);
		if (varLength == 0) {
			if (allVariables.find(var.first) != allVariables.end())
				finalResult[var.first] = "";
			continue;
		}

		if (isInternalVar(var.first, lenInt))
			continue;

		bool foundClue = false;
		for (int i = 0; i < varLength; ++i)
			if (var.second[i] != 0) {
				foundClue = true;
				break;
			}
		if (foundClue == false)
			continue;

		std::string value = "";
		for (int i = 0; i < varLength; ++i) {
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
	printf(">> Running Z3\n\n");

	FILE* in = popen(cmd.c_str(), "r");
	if (!in)
		throw std::runtime_error("Z3 failed!");

	std::map<std::string, std::string> len_results;
	std::map<std::string, std::string> str_results;
	char buffer[10000];
	std::string result = "";
	bool sat = false;
	try {
		/* the first line */
		if (fgets(buffer, 9900, in) == NULL)
			assert(false);
		std::string getSat = buffer;
		if (getSat.find("error ") != std::string::npos)
			assert(false);

		getSat = getSat.substr(0, 3);
		__debugPrint(logFile, "%d %s: %s\n", __LINE__, __FUNCTION__, buffer);

		if (getSat.compare("sat") == 0) {
//			printf(">> Z3: SAT\n\n");
			sat = true;
		}

		else {
//			if (finalCall == true)
//				printf(">> Z3: UNSAT\n\n");
			return sat;
		}
		std::map<std::string, std::string> array_map;
		/* the concrete values */
		while (!feof(in)) {
			std::string line = "";
			if (fgets(buffer, 9900, in) != NULL) {
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
							if (fgets(buffer, 9900, in) == NULL)
								assert(false);
							tokens = parse_string_language(buffer, " (),.=");
							if (tokens[0].compare("ite") != 0) {
								elseValue = std::atoi(tokens[0].c_str());
								if (elseValue > 'z' || elseValue < '!')
									elseValue = DEFAULT_CHAR;
								break;
							}
							else {
								int tmpNum = std::atoi(tokens[tokens.size() - 1].c_str());
								if (tmpNum > 'z' || tmpNum < '!')
									tmpNum = DEFAULT_CHAR;
								valueMap[std::atoi(tokens[2].c_str())] = tmpNum;
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
					else if (name.find(ARRPREFIX) != std::string::npos){
						/* array map */
						if (fgets(buffer, 9900, in) == NULL)
							assert(false);
						tokens = parse_string_language(buffer, " (),.\n\t\r");
						assert(tokens.size() == 3);
						array_map[tokens[2]] = name;
					}
					else {
						/* len value */
						/* read the value in the next line */
						if (fgets(buffer, 9900, in) == NULL)
							assert(false);
						tokens = parse_string_language(buffer, " (),.");
						if (tokens[0][0] == '-')
							len_results[name] = tokens[0] + " " + tokens[1];
						else
							len_results[name] = tokens[0];
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
		bool completion = true;
		std::map<std::string, std::string> results = formatResult(len_results, str_results, completion);
		if (completion == false)
#ifdef DEBUGLOG
			assert(false);
#else
		unknownResult = true;
		return false;
#endif
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
				if (line.substr(0, 8).compare(">> UNSAT") == 0) {
					__debugPrint(logFile, "%d %s\n", __LINE__, line.c_str());
					assert(false);
				}
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
	varPieces.clear();
	notContainMap.clear();
	smtLenConstraints.clear();
	smtVarDefinition.clear();
	global_smtStatements.clear();
	connectedVariables.clear();
	trivialUnsat = false;
	unknownResult = false;
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
				std::string _tmp = tmp.substr(0, pos) + LENPREFIX;
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
 * v01 is inside v02?
 */
int vectorInsideVector(std::vector<std::string> v01, std::vector<std::string> v02){
	for (unsigned int i = 0; i <= v02.size() - v01.size(); ++i) {
		unsigned int pos = 0;
		while (pos < v01.size() && v02[i + pos].compare(v01[pos]) == 0)
			pos++;
		if (pos == v01.size())
			return i;
	}
	return -1;
}

/*
 *
 */
void addConnectedVarToEQmap(){
	std::map<std::string, std::vector<std::vector<std::string>>> _newEqMap = equalitiesMap;
	for (const auto& varEq00: equalitiesMap) {
		if (connectedVariables.find(varEq00.first) != connectedVariables.end() && varEq00.second[0].size() > 1){
			for (const auto& varEq: equalitiesMap) {
				std::vector<std::vector<std::string>> tmpVector = varEq.second;
				if (varEq.first.compare(varEq00.first) != 0){

					for (const auto eq00: varEq.second) {
						for (const auto eq01: varEq00.second)
							if (eq00.size() > eq01.size()) {
								int pos = vectorInsideVector(eq01, eq00);
								if (pos != -1) {
									__debugPrint(logFile, "%d %s: %s %s %d\n", __LINE__, __FUNCTION__, varEq.first.c_str(), varEq00.first.c_str(), pos);
									/* create a new one */
									std::vector<std::string> tmp;
									for (int i = 0; i < pos; ++i)
										tmp.emplace_back(eq00[i]);
									tmp.emplace_back(varEq00.first);
									for (unsigned int i = pos + eq01.size(); i < eq00.size(); ++i)
										tmp.emplace_back(eq00[i]);

									_newEqMap[varEq.first].emplace_back(tmp);
									break;
								}
							}

					}
				}
			}
		}
	}
	equalitiesMap.clear();
	equalitiesMap = _newEqMap;
	printEqualMap(equalitiesMap);
}

/*
 *
 */
void createNotContainMap(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto op : rewriterStrMap)
		if (op.first.name.compare(CONTAINS) == 0 && op.second.compare(FALSETR) == 0){
			if (op.first.arg02[0] == '"') {
				notContainMap[std::make_pair(op.first.arg01, op.first.arg02.substr(1, op.first.arg02.length() - 2))] = false;
			}
		}
}

/*
 *
 */
std::map<std::string, std::vector<std::string>> createNotEqualMap(std::map<StringOP, std::string> rewriterStrMap){
	std::map<std::string, std::vector<std::string>> ret;
	for (const auto op : rewriterStrMap)
		if (op.first.name.compare("=") == 0 && op.second.compare(FALSETR) == 0){
			if (op.first.arg02[0] == '"') {
				if (ret.find(op.first.arg01) == ret.end())
					ret[op.first.arg01] = {op.first.arg02.substr(1, op.first.arg02.length() - 2)};
				else
					ret[op.first.arg01].emplace_back(op.first.arg02.substr(1, op.first.arg02.length() - 2));
			}
		}
	return ret;
}

/*
 *
 */
void init(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& op : rewriterStrMap)
		if (op.first.name.compare(SUBSTRING) == 0)
			createAnyway = false;
	createNotContainMap(rewriterStrMap);
	sumConstString();

	collectConnectedVariables(rewriterStrMap);
	refineEqualMap(rewriterStrMap);

	/*collect var --> update --> collect again */
	collectConnectedVariables(rewriterStrMap);
	addConnectedVarToEQmap();
	createConstMap();
	refineEqualMap(rewriterStrMap);
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
bool isTrivialInequality(std::string x, std::string  y){
	__debugPrint(logFile, "%d *** %s ***: %s != %s\n", __LINE__, __FUNCTION__, x.c_str(), y.c_str());
	if (isRegexStr(x) || isUnionStr(x)) {
		__debugPrint(logFile, "%d *** %s ***: false\n", __LINE__, __FUNCTION__);
		return false;
	}
	if (isRegexStr(y) || isUnionStr(y)){
		__debugPrint(logFile, "%d *** %s ***: false\n", __LINE__, __FUNCTION__);
		return false;
	}

	if (equalitiesMap.find(x) != equalitiesMap.end()) {
		/* check if y inside x */
		for (const auto& v : equalitiesMap[x]){
			if (std::find(v.begin(), v.end(), y) != v.end()) {
				for (const auto& s : v)
					if (isConstStr(s)) /* x = "a" + y */
						return true;
			}
			if (isConstStr(y)) {
				for (const auto& s : v)
					if (isConstStr(s) && y.find(s.substr(1, s.length() - 2)) == std::string::npos)
						return true;
			}
		}
	}

	if (equalitiesMap.find(y) != equalitiesMap.end()) {
		/* check if x inside y */
		for (const auto& v : equalitiesMap[y]){
			if (std::find(v.begin(), v.end(), x) != v.end()) {
				for (const auto& s : v)
					if (isConstStr(s)) /* y = "a" + x */
						return true;
			}
			if (isConstStr(x)) {
				for (const auto& s : v)
					if (isConstStr(s) && x.find(s.substr(1, s.length() - 2)) == std::string::npos)
						return true;
			}
		}
	}

	if (equalitiesMap.find(x) != equalitiesMap.end() &&
			equalitiesMap.find(y) != equalitiesMap.end()) {
		for (const auto& _x : equalitiesMap[x]) {
			for (const auto& _y : equalitiesMap[y]) {
				unsigned pos = 0;
				while (pos < _x.size() && pos < _y.size()) {
					if (_x[pos].compare(_y[pos]) == 0)
						++pos;
					else {
						if (isConstStr(_x[pos]) && isConstStr(_y[pos]) &&
								!isUnionStr(_x[pos]) && !isUnionStr(_y[pos])) {
							/* x = a + b + "abc" | y = a + b + "def" */
							__debugPrint(logFile, "%d *** %s ***: true\n", __LINE__, __FUNCTION__);
							return true;
						}
						else
							break;
					}
				}
				if (!(pos < _x.size() && pos < _y.size()))
					continue;
			}
		}
	}
	__debugPrint(logFile, "%d *** %s ***: false\n", __LINE__, __FUNCTION__);
	return false;
}

/*
 *
 */
void updateRewriter(
		std::map<StringOP, std::string> &rewriterStrMap){
	orgRewriterStrMap = rewriterStrMap;
	std::map<StringOP, std::string> newRewriterStrMap;
	for (const auto& op : rewriterStrMap){

		if (op.first.name.compare("=") == 0 && op.second.compare(FALSETR) == 0){
			if (!isTrivialInequality(op.first.arg01, op.first.arg02)) {
				newRewriterStrMap[op.first] = op.second;
			}
			continue;
		}

		if (allVariables.find(op.first.arg01) != allVariables.end() ||
				allVariables.find(op.first.arg02) != allVariables.end() ||
				allVariables.find(op.first.arg03) != allVariables.end())
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
bool hasInequalities(std::map<StringOP, std::string> rewriterStrMap){
	for (const auto& op : rewriterStrMap){
		if (op.first.name.compare("=") == 0 && op.second.compare(FALSETR) == 0){
			return true;
		}
	}
	return false;
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

	/* init varLength */
	varLength.clear();
	varLength.insert(_currentLength.begin(), _currentLength.end());

	/* init equalMap */
	parseEqualityMap(_equalMap);
	reset();
	init(rewriterStrMap);
	updateRewriter(rewriterStrMap);

	for (const auto& elem : rewriterStrMap){
		StringOP op = elem.first;
		__debugPrint(logFile, "%d rewriterStrMap \t%s: %s\n", __LINE__, op.toString().c_str(), elem.second.c_str());
	}

	for (const auto& c : connectedVariables) {
		__debugPrint(logFile, "%d connectedVar: %s %d\n", __LINE__, c.first.c_str(), c.second);
	}


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

	toNonGRMFile(fileDir, NONGRM, equalitiesMap, constMap);

	/* init regexCnt */
	regexCnt = 0;

	bool result = false;

	if (connectedVariables.size() == 0 &&
			equalitiesMap.size() == 0 &&
			!hasInequalities(orgRewriterStrMap)) {
		toLengthFile(NONGRM, true, orgRewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
		if (trivialUnsat) {
			printf(">> UNSAT\n");
			return false;
		}

		writeOutput_basic(OUTPUT);

		/* re-assign equalityMap */

		result = Z3_run(_equalMap, false);
		if (result == false){
			regexCnt = 0;
			toLengthFile(NONGRM, false, orgRewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
			if (trivialUnsat) {
				printf(">> UNSAT\n");
				return false;
			}
			writeOutput_basic(OUTPUT);
			result = Z3_run(_equalMap);
		}
	}
	else {
		toLengthFile(NONGRM, false, orgRewriterStrMap, regexCnt, smtVarDefinition, smtLenConstraints);
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
	return result;
}


