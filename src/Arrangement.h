/*
 * Arrangement.h
 *
 *  Created on: Dec 8, 2016
 *      Author: diepbp
 */

#ifndef ARRANGEMENT_H_
#define ARRANGEMENT_H_

#include "utils.h"

#define ROUNDCHECK 1
#define LOCALSPLITMAX 20
#define SUMFLAT 100000000
#define EMPTYFLAT 9999999

#define REGEX_CODE -100
#define MINUSZERO 999

class Arrangment{
public:

	std::vector<int> left_arr;
	std::vector<int> right_arr;

	// std::map<std::pair<std::string, std::string>, std::string> constMap; // extra info for all Arrangement
	std::map<std::string, std::string> constMap; // extra info for all Arrangement
	std::map<std::string, std::set<std::string>> notMap; // extra info for all Arrangement

	Arrangment(std::vector<int> _left_arr,
			std::vector<int> _right_arr,
//			std::map<std::pair<std::string, std::string>, std::string> _constMap,
			std::map<std::string, std::string> _constMap,
			std::map<std::string, std::set<std::string>> _notMap
			){
		left_arr.insert(left_arr.end(), _left_arr.begin(), _left_arr.end());
		right_arr.insert(right_arr.end(), _right_arr.begin(), _right_arr.end());

		/* extra info */
		constMap.insert(_constMap.begin(), _constMap.end());
		notMap.insert(_notMap.begin(), _notMap.end());
	}

	void addLeft(int number) {
		left_arr.push_back(number);
	}

	void addRight(int number) {
		right_arr.push_back(number);
	}

	bool canSplit(int boundedFlat, int boundSize, int pos, std::string frame, std::vector<std::string> &flats) {
		if ((int)flats.size() == boundedFlat)
			return false;

		for (int size = 1; size <= boundSize; ++size) { /* size of a flat */
			std::string flat = frame.substr(pos, size);
			flats.push_back(flat); /* add to stack */
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
					/* de-stack */
					flats.pop_back();
				}
			}
			else {
				return true;
			}
		}
		return false;
	}

	/*
	 * Input: string that we are going to split, and number of flats
	 * Ouput: able to split or not
	 */
	int splitWithMinFlats(int boundedFlat, int boundSize, std::string frame){
		for (int i = 1; i <= boundedFlat; ++i) { /* number of flats */
			std::vector<std::string> flats;
				if (canSplit(i, PMAX, 0, frame, flats)){
					return i;
				}
				flats.clear();
			}
		return -1;
	}

	void splitPrintTest(std::vector<int> currentSplit, std::string msg = ""){
		printf("%s\n", msg.c_str());
		for (unsigned int i = 0; i < currentSplit.size(); ++i)
			printf("%d - ", currentSplit[i]);
		printf("\n------------\n");
	}

	 /**
	 * Print a list
	 */
		template<typename T>
		void printList(T list, std::string msg = "") {
			if (msg.length() > 0 )
				printf("%s\n", msg.c_str());
			for (std::vector<int>::iterator it = list.begin(); it != list.end(); ++it) {
				printf("%d ", *it);
			}
			printf("\n");
		}

		bool feasibleSplit_const(
				std::string str,
				std::vector<std::pair<std::string, int> > elementNames,
				std::vector<int> currentSplit){
//#ifdef PRINTTEST_UNDERAPPROX
//			printf("%d Checking split\n", __LINE__);
//#endif
			/* check general split */
			/* x_i == 0 --> x_i+1 == 0 */
			for (unsigned int i = 1; i < currentSplit.size(); ++i)
				if (currentSplit[i] != 0){
					if (elementNames[i].second > 0) /* var */ {
						if (currentSplit[i - 1] == 0) /* empty */
							return false;
					}
					else if (elementNames[i].second == -2) /* const */{
						if (currentSplit[i - 1] == 0) /* empty */
							return false;
					}

				}

			/* check feasible const split */
			int pos = 0;
			for (unsigned int i = 0; i < currentSplit.size(); ++i) {
				if (elementNames[i].second == REGEX_CODE) {
					std::string lhs = str.substr(pos, currentSplit[i]);
					/* check whether lhs can be created from rhs */
					std::string rhs = "";
					while (rhs.length() < lhs.length())
						rhs = rhs +  elementNames[i].first;
					if (lhs.compare(rhs) != 0)
						return false;
				}

				/* TODO: bound P */
				else if (elementNames[i].second < 0) { /* const */
					assert ((int)elementNames[i].first.length() >= currentSplit[i]);

					std::string lhs = str.substr(pos, currentSplit[i]);
					std::string rhs = "";
					if (elementNames[i].second == -1) /* head */ {
						rhs = elementNames[i].first.substr(0, currentSplit[i]);


						if (i + 1 < elementNames.size()) {
							if (QCONSTMAX == 1 || elementNames[i].first.length() == 1) {
								assert (currentSplit[i] == (int)elementNames[i].first.length()); /* const length must be equal to length of const */
							}
							else {
								assert (elementNames[i + 1].second == -2);
								assert ((currentSplit[i] + currentSplit[i + 1] == (int)elementNames[i].first.length())); /* sum of all const parts must be equal to length of const */
							}
						}
					}
					else { /* tail */
						rhs = elementNames[i].first.substr(elementNames[i].first.length() - currentSplit[i], currentSplit[i]);
					}

					if (lhs.compare(rhs) != 0){
						// printf("%s - %s\n", lhs.c_str(), rhs.c_str());
						return false;
					}
				}
				pos += currentSplit[i];
			}
			return true;
		}

		bool feasibleSplit_regex(
				std::string str,
				std::vector<std::pair<std::string, int> > elementNames,
				std::vector<int> currentSplit){

			/* check general split */
			/* x_i == 0 --> x_i+1 == 0 */
			for (unsigned int i = 1; i < currentSplit.size(); ++i)
				if (currentSplit[i] != 0){
					if (elementNames[i].second > 0) /* var */ {
						if (currentSplit[i - 1] == 0) /* empty */
							return false;
					}
					else if (elementNames[i].second == -2) /* const */{
						if (currentSplit[i - 1] == 0) /* empty */
							return false;
					}

				}

			return true;
		}

		/*
		 * (lhs)* = (rhs)* where lhs starts at posLHS
		 */
		std::vector<std::pair<int, int> > regex_in_regex_at_pos(std::string lhs, std::string rhs, int posLhs) {
			/* extend string if it is short */
			std::string initialLhs = lhs;
			while (rhs.length() + posLhs > initialLhs.length()) /* make sure that | initialLhs | > | rhs | */
				initialLhs = initialLhs + lhs;

//			bool isloopExist = true;

			std::vector<std::pair<int, int> > possibleCases;

			if (rhs.compare(initialLhs.substr(posLhs, rhs.length())) == 0) {
				int pos_lhs = (posLhs + rhs.length()) % lhs.length();
				int iterRhs = 1;

				possibleCases.push_back((std::pair<int, int>)std::make_pair(posLhs, 0));
				possibleCases.push_back((std::pair<int, int>)std::make_pair(posLhs, 1));

				std::string double_str = initialLhs + initialLhs;
				while (pos_lhs != posLhs) {

					/* loop until it goes back the inital possition */
					if (rhs.compare(double_str.substr(pos_lhs, rhs.length())) == 0) {
						possibleCases.push_back((std::pair<int, int>)std::make_pair(pos_lhs, ++iterRhs));
						pos_lhs = (pos_lhs + rhs.length()) % lhs.length();
					}
					else {
//						isloopExist = false;
						break;
					}
				}
			}
			else /* cannot happens */ {
//				isloopExist = false;
				possibleCases.push_back((std::pair<int, int>)std::make_pair(0, -1));
			}

			/* print test */
	//		printf("%d regex_in_regex_at_pos has loop: %s\n", __LINE__, isloopExist? "true" : "false");
	//		for (int i = 0; i < possibleCases.size(); ++i) {
	//			printf("\t%d %d\n", possibleCases[i].first, possibleCases[i].second);
	//		}

			return possibleCases;
		}

		/*
		 * (lhs)* = .* rhs .* where lhs starts at posLHS
		 */
		bool const_in_regex_at_pos(std::string lhs, std::string rhs, int posLhs){
			/* extend string if it is short */
			std::string initialLhs = lhs;
			while (rhs.length() + posLhs > initialLhs.length()) /* make sure that | initialLhs | > | rhs | */
				initialLhs = initialLhs + lhs;

			if (rhs.compare(initialLhs.substr(posLhs, rhs.length())) == 0) {
				return true;
			}
			return false;
		}

		// TODO const_in_const_at_pos

		/*
		 * (lhs)* = .* rhs.-2 .* where lhs starts at posLHS
		 */
		std::vector<int> tail_in_regex_at_pos(std::string lhs, std::string rhs, int posLhs){
			std::vector<int> potentialPos;
			for (int i = 0; i <= (int)rhs.length(); ++i) {
				/* length = i */
				std::string tmpRhs = rhs.substr(i);

				/* extend string if it is short */
				std::string initialLhs = lhs;
				while (tmpRhs.length() + posLhs > initialLhs.length()) /* make sure that | initialLhs | > | rhs | */
					initialLhs = initialLhs + lhs;

				if (tmpRhs.compare(initialLhs.substr(posLhs, tmpRhs.length())) == 0) {
					potentialPos.push_back(rhs.length() - i);
				}
			}
			return potentialPos;
		}

		// TODO tail_in_const_at_pos

		/*
		 * (lhs)* = .* rhs.-1 .* where lhs starts at posLHS
		 */
		std::vector<int> head_in_regex_at_pos(std::string lhs, std::string rhs, int posLhs){
			std::vector<int> potentialPos;
			for (int i = 0; i <= (int)rhs.length(); ++i) {
				/* length = i */
				std::string tmpRhs = rhs.substr(0, i);

				/* extend string if it is short */
				std::string initialLhs = lhs;
				while (tmpRhs.length() + posLhs > initialLhs.length()) /* make sure that | initialLhs | > | rhs | */
					initialLhs = initialLhs + lhs;

				if (tmpRhs.compare(initialLhs.substr(posLhs, tmpRhs.length())) == 0) {
					potentialPos.push_back(i);
				}
				else
					return potentialPos;
			}
			return potentialPos;
		}

		// TODO head_in_const_at_pos

		/*
		 * textLeft: length of string
		 * nMax: number of flats
		 * pMax: size of a flat
		 *
		 * Pre-Condition: 1st flat and n-th flat must be greater than 0
		 * Output: of the form 1 * 1 + 1 * 0 + 1 * 0 + 1 * 0 + 1 * 0 + 1 * 0 + 1 * 0 + 1 * 0 + 1 * 3 + 2 * 3 = 10
		 */
		void collectAllPossibleSplits_const(
				int pos,
				std::string str, /* const */
				int pMax,
				std::vector<std::pair<std::string, int> > elementNames,
				std::vector<int> currentSplit,
				std::vector<std::vector<int> > &allPossibleSplits
				) {
			/* reach end */
//#ifdef PRINTTEST_UNDERAPPROX
//			printf("%d New iteration\n", __LINE__);
//#endif
			if (currentSplit.size() == elementNames.size() &&
					pos == (int)str.length() &&
					feasibleSplit_const(str, elementNames, currentSplit)) {

//				 splitPrintTest(currentSplit, "Accepted");
				 allPossibleSplits.push_back(currentSplit);
				return;
			}
			else if (currentSplit.size() >= elementNames.size()) {
//				 splitPrintTest(currentSplit, "Rejected");
				return;
			}

			unsigned int textLeft = str.length() - pos;
//#ifdef PRINTTEST_UNDERAPPROX
//			for (unsigned int i = 0 ; i < elementNames.size(); ++i)
//				printf("(%s, %d)", elementNames[i].first.c_str(), elementNames[i].second);
//			printf("\n%d collectAllPossibleSplits_const 1: %s %d %d %s\n", __LINE__, str.c_str(), textLeft, elementNames[currentSplit.size()].second, elementNames[currentSplit.size()].first.c_str());
//#endif
			/* special case for const: leng = leng */
			if (elementNames[currentSplit.size()].second == -1 && (QCONSTMAX == 1 || elementNames[currentSplit.size()].first.length() == 1)) {
//#ifdef PRINTTEST_UNDERAPPROX
//				printf("%d collectAllPossibleSplits_const 2: %ld %ld\n", __LINE__, currentSplit.size(), elementNames.size());
//				printf("%d %ld <= %ld\n", __LINE__, elementNames[currentSplit.size()].first.length(), textLeft);
//#endif
				if (elementNames[currentSplit.size()].first.length() <= textLeft) {
					currentSplit.push_back(elementNames[currentSplit.size()].first.length());
//#ifdef PRINTTEST_UNDERAPPROX
//					printf("%d call one more %d %d\n", __LINE__, pos, pos + elementNames[currentSplit.size() - 1].first.length());
//#endif
					collectAllPossibleSplits_const(pos + elementNames[currentSplit.size() - 1].first.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}
//#ifdef PRINTTEST_UNDERAPPROX
//				printf("%d collectAllPossibleSplits_const Done 2\n", __LINE__);
//#endif
			}

			/* special case for const tail, when we know the length of const head */
			else if (elementNames[currentSplit.size()].second == -2 && currentSplit.size() > 0 && QCONSTMAX == 2) /* const */ {

				assert (elementNames[currentSplit.size() - 1].second == -1);
				unsigned int length = (unsigned int)elementNames[currentSplit.size()].first.length() - currentSplit[currentSplit.size() - 1]; /* this part gets all const string remaining */

				if (length <= textLeft) {
					currentSplit.push_back(length);
					collectAllPossibleSplits_const(pos + length, str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}

			}

			else if (currentSplit.size() == elementNames.size() - 1) /* the last one */ {

				if ((elementNames[currentSplit.size()].second < 0 && elementNames[currentSplit.size()].first.length() >= textLeft) || /* const */
						(elementNames[currentSplit.size()].second >= 0)) {
					currentSplit.push_back(str.length() - pos);
					collectAllPossibleSplits_const(str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}
				else {
				}
			}

			else {
				for (unsigned int i = 0; i <= textLeft; ++i) {
					unsigned int length = i;
					if (elementNames[currentSplit.size()].second == REGEX_CODE) /* regex */ {
						if (length % elementNames[currentSplit.size()].first.length() != 0) /* only accept the relevant length */
							continue;
						currentSplit.push_back(length);
						collectAllPossibleSplits_const(pos + length, str, pMax, elementNames, currentSplit, allPossibleSplits);
						currentSplit.pop_back();
					}
					else if (	elementNames[currentSplit.size()].second < 0 &&
										elementNames[currentSplit.size()].second >= -QCONSTMAX) /* const */ {
						if (length < elementNames[currentSplit.size()].first.length() && (length <= 7) ) /* cannot cover this length && 10 is a magic number lol */ {
							currentSplit.push_back(length);
							collectAllPossibleSplits_const(pos + length, str, pMax, elementNames, currentSplit, allPossibleSplits);
							currentSplit.pop_back();
						}
					}
					else {
						currentSplit.push_back(length);
						collectAllPossibleSplits_const(pos + length, str, pMax, elementNames, currentSplit, allPossibleSplits);
						currentSplit.pop_back();
					}
				}
			}
		}

		void collectAllPossibleSplits_regex(
				int pos,
				std::string str, /* regex */
				int pMax,
				std::vector<std::pair<std::string, int> > elementNames,
				std::vector<int> currentSplit,
				std::vector<std::vector<int> > &allPossibleSplits
				) {
			// printf("%d pos = %d\n", __LINE__, pos);
			/* reach end */
			if (currentSplit.size() == elementNames.size() &&
					pos == 0 &&
					feasibleSplit_regex(str, elementNames, currentSplit)) {

				// splitPrintTest(currentSplit, "Accepted");
				 allPossibleSplits.push_back(currentSplit);
				return;
			}
			else if (currentSplit.size() >= elementNames.size()) {
				// splitPrintTest(currentSplit, "Rejected");
				return;
			}

			/* special case for const: regex = .* const .* */
			if (elementNames[currentSplit.size()].second == -1 && QCONSTMAX == 1) {
				// printf("%d Case 00: const qmax = 1\n", __LINE__);
				/* compare text, check whether the string can start from the location pos in text */
				if (const_in_regex_at_pos(str, elementNames[currentSplit.size()].first, pos)) {
					currentSplit.push_back(elementNames[currentSplit.size()].first.length());
					collectAllPossibleSplits_regex((pos + elementNames[currentSplit.size() - 1].first.length()) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}
			}

			/* special case for const tail, when we know the length of const head */
			else if (elementNames[currentSplit.size()].second == -2 && currentSplit.size() > 0) /* tail, not the first */ {
				// printf("%d Case 01: const tail at middle\n", __LINE__);
				assert (elementNames[currentSplit.size() - 1].second == -1);
				int length = elementNames[currentSplit.size()].first.length() - currentSplit[currentSplit.size() - 1]; /* this part gets all const string remaining */

				currentSplit.push_back(length);
				collectAllPossibleSplits_regex((pos + length) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
				currentSplit.pop_back();
			}

			else if (elementNames[currentSplit.size()].second == -2 && currentSplit.size() == 0) /* tail, first */ {
				// printf("%d Case 02: const tail at first\n", __LINE__);
				/* find all possible start points */
				std::vector<int> tail = tail_in_regex_at_pos(str, elementNames[currentSplit.size()].first, pos);
				for (unsigned int i = 0 ; i < tail.size(); ++i) {
					currentSplit.push_back(tail[i]);
					collectAllPossibleSplits_regex((pos + tail[i]) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}

			}

			else if (elementNames[currentSplit.size()].second == -1 && currentSplit.size() + 1 == elementNames.size() && QCONSTMAX == 2) /* head, the last element */ {
				// printf("%d Case 03: const head at last: %d\n", __LINE__, pos);
				/* find all possible start points */
				std::vector<int> head = head_in_regex_at_pos(str, elementNames[currentSplit.size()].first, pos);
				for (unsigned int i = 0 ; i < head.size(); ++i) {
					// printf("%d Case 03: value = %d\n", __LINE__, head[i]);
					currentSplit.push_back(head[i]);
					collectAllPossibleSplits_regex((pos + head[i]) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}
			}

			else if (elementNames[currentSplit.size()].second == -1 && currentSplit.size() + 1 < elementNames.size() && QCONSTMAX == 2) /* head, not the last element */ {
				// printf("%d Case 04: const head at middle\n", __LINE__);
				/* check full string */
				assert (elementNames[currentSplit.size() + 1].second == -2);
				if (const_in_regex_at_pos(str, elementNames[currentSplit.size()].first, pos)) {
					for (unsigned int i = 1 ; i <= elementNames[currentSplit.size()].first.length(); ++i) { /* cannot be empty */
						currentSplit.push_back(i);
						collectAllPossibleSplits_regex((pos + i) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
						currentSplit.pop_back();
					}
				}
			}

			else if (elementNames[currentSplit.size()].second == REGEX_CODE) /* regex */ {
				// printf("%d Case 06: regex %s %s %d\n", __LINE__, str.c_str(), elementNames[currentSplit.size()].first.c_str(), pos);
				std::vector<std::pair<int, int> > regexPos = regex_in_regex_at_pos(str, elementNames[currentSplit.size()].first, pos);
				/* loop ? */
				bool loop = false;
				if (regexPos.size() > 0 && regexPos[regexPos.size() - 1].second * elementNames[currentSplit.size()].first.length() % str.length() == 0)
					loop = true;

				assert(regexPos.size() >= 1);
				if (regexPos[0].second == -1) /* iterate 0 */ {
					currentSplit.push_back(0);
					collectAllPossibleSplits_regex(pos, str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}

				else if (loop == true) /* assign value < 0 */
					for (unsigned int i = 0 ; i < regexPos.size(); ++i) {
						// printf("%d Case 06: value = (loop)%ld\n", __LINE__, - elementNames[currentSplit.size()].first.length() * regexPos[i].second);
						int tmp = (elementNames[currentSplit.size()].first.length() * regexPos[i].second) % str.length();
						if (tmp == 0)
							currentSplit.push_back(MINUSZERO);
						else
							currentSplit.push_back(-tmp);
						collectAllPossibleSplits_regex((pos + elementNames[currentSplit.size() - 1].first.length() * regexPos[i].second) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
						currentSplit.pop_back();
					}
				else
					for (unsigned int i = 0 ; i < regexPos.size(); ++i) { /* assign value >= 0 */
						int tmp = (pos + elementNames[currentSplit.size()].first.length() * regexPos[i].second) % str.length();
						// printf("%d Case 06: value = (unloop)%d\n", __LINE__, tmp);
						currentSplit.push_back(elementNames[currentSplit.size()].first.length() * regexPos[i].second);
						collectAllPossibleSplits_regex(tmp, str, pMax, elementNames, currentSplit, allPossibleSplits);
						currentSplit.pop_back();
					}
			}

			else {
				// printf("%d Case 07.\n", __LINE__);
				for (unsigned int i = 0; i < str.length(); ++i) { /* assign value < 0 because it can iterate many times */
					int length = i;
					currentSplit.push_back(- length);
					collectAllPossibleSplits_regex((pos + length) % str.length(), str, pMax, elementNames, currentSplit, allPossibleSplits);
					currentSplit.pop_back();
				}
			}
		}

		/*
		 * Given a flat,
		 * generate its size constraint
		 */
		std::string generateFlatSize(std::pair<std::string, int> a, std::string l_r_hs = ""){
			std::string result = "";
			if (a.second >= 0) {
				/* simpler version */
				result = result + "len_" + a.first + "_" + std::to_string(a.second);
			}
			else {
				/* const string */
				assert (l_r_hs.length() > 0);
//				result = result + "len_" + constMap[std::make_pair(a.first, l_r_hs)] + "_" + std::to_string(std::abs(a.second));
				result = result + "len_" + constMap[a.first] + "_" + std::to_string(std::abs(a.second));
				// printf("%d, at generate flat size (%s of %s) = %s\n", __LINE__, a.first.c_str(), l_r_hs.c_str(),constMap[std::make_pair(a.first, l_r_hs)].c_str());
			}
			return result;
		}

		std::string orConstraint(std::set<std::string> possibleCases){
			std::string result = "";
			if (possibleCases.size() > 1) {
				result = "(or ";
				for (std::set<std::string>::iterator it = possibleCases.begin(); it != possibleCases.end(); ++it)
					result = result + *it + " ";
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
				for (unsigned int i = 0; i < possibleCases.size(); ++i)
					result = result + possibleCases[i] + " ";
				result = result + ")";
			}
			else if (possibleCases.size() == 1){
				result = possibleCases[0];
			}
			return result;
		}

		std::string andConstraint(std::set<std::string> possibleCases){
			std::string result = "";
			if (possibleCases.size() > 1) {
				result = "(and ";
				for (std::set<std::string>::iterator it = possibleCases.begin(); it != possibleCases.end(); ++it)
					result = result + *it + " ";
				result = result + ")";
			}
			else if (possibleCases.size() == 1){
				result = *possibleCases.begin();
			}
			return result;
		}

		std::string addConstraint(std::vector<std::string> elements) {
			std::string result = "";
			if (elements.size() > 1) {
				result = "(+ ";
				for (unsigned int i = 0; i < elements.size(); ++i)
					result = result + elements[i] + " ";
				result = result + ")";
			}
			else if (elements.size() == 1){
				result = elements[0];
			}
			else
				result = "0";
			return result;
		}

		/*
		 * (+ a b c)
		 */
		std::string addConstraint_full(std::vector<std::string> elements) {
			std::string result = "";
			if (elements.size() == 0)
				return "0";
			if (elements.size() == 1)
				return elements[0];
			if (elements.size() > 1) {
				result = "(+ ";
				for (unsigned int i = 0; i < elements.size(); ++i)
					result = result + elements[i] + " ";
				result = result + ")";
			}
			return result;
		}

	  /*
	   * Input: split a string
	   * Output: SMT
	   */
	  std::string fromSplitToLengConstraint_const(
	  		std::pair<std::string, int> a, /* const */
	  		std::vector<std::pair<std::string, int> > elementNames,
	  		std::vector<int> split,
	  		std::string lhs, std::string rhs){

	  	int totalLength = 0;
	  	for (unsigned int j = 0; j < split.size(); ++j)
	  		totalLength = totalLength + split[j];

	  	std::vector<std::string> strAnd;
	  	strAnd.push_back("(= " + generateFlatSize(a, lhs) + " " + std::to_string(totalLength) + ")");

	  	std::vector<std::string> addElements;

	  	/* check if size of all consts = 0 */
	  	bool sumConst_0 = true, metVar = false;
	  	unsigned int splitPos = 0;
	  	for (unsigned int i = 0; i < elementNames.size(); ++i) {
	  		if (elementNames[i].second < 0) { /* const or regex */
	  			if (metVar) /* check the next one */
	  				splitPos++;
	  			if (split[splitPos++] > 0){
	  				sumConst_0 = false;
	  				break;
	  			}
	  			addElements.push_back(generateFlatSize(elementNames[i], rhs));
	  			metVar = false;
	  		}
	  		else
	  			metVar = true;
	  	}

	  	if (sumConst_0 == true) {
	  		return "(= 0 " + addConstraint_full(addElements) + ")";
	  	}
	  	else {
	  	}

	  	/* work as usual */
	  	addElements.clear();
	  	splitPos = 0;

	  	for (unsigned int i = 0; i < elementNames.size(); ++i){
	  		if (elementNames[i].second >= 0) /* not const */ {
	  			addElements.push_back(generateFlatSize(elementNames[i]));
	  		}
	  		else { /* const or regex */
	  			if (addElements.size() > 0){ /* create a sum for previous elements */
	  				strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(split[splitPos]) + ")");
	  				splitPos++;
	  				addElements.clear();
	  			}

	  			if (elementNames[i].second == -1 && i < elementNames.size() - 1) { /* const and not at the end */
	  				if (QCONSTMAX == 1) {
	  					strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos]) + ")");
	  					splitPos++;
	  				}
	  				else {
	  					assert(elementNames[i + 1].second == -2);
	  					strAnd.push_back("(= (+ " + generateFlatSize(elementNames[i], rhs) + " " + generateFlatSize(elementNames[i + 1], rhs) + ") " + std::to_string(split[splitPos] + split[splitPos + 1]) + ")");
	  					i++;
	  					splitPos += 2;
	  				}
	  			}
	  			else { /* const at the end or regex */
	  				strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos++]) + ")");
	  			}
	  		}
	  	}

	  	if (addElements.size() > 0) {
	  		/* create a sum for previous elements */

	  		strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(split[splitPos++]) + ")");
	  	}
	  	assert(splitPos == split.size());
	  	return andConstraint(strAnd);
	  }

	  /*
	   * Input: split a string
	   * Output: SMT
	   */
	  std::string fromSplitToLengConstraint_regex(
	  		std::pair<std::string, int> a, /* regex */
	  		std::vector<std::pair<std::string, int> > elementNames,
	  		std::vector<int> split,
	  		std::string lhs, std::string rhs){

	  	std::vector<std::string> strAnd;

	  	std::vector<std::string> addElements;

	  	/* check if size of all consts = 0 */
	  	bool sumConst_0 = true, metVar = false;
	  	unsigned int splitPos = 0;
	  	for (unsigned int i = 0; i < elementNames.size(); ++i) {
	  		if (elementNames[i].second < 0) { /* const or regex */
	  			if (metVar) /* check the next one */
	  				splitPos++;
	  			if (split[splitPos++] != 0){
	  				sumConst_0 = false;
	  				break;
	  			}
	  			addElements.push_back(generateFlatSize(elementNames[i], rhs));
	  			metVar = false;
	  		}
	  		else
	  			metVar = true;
	  	}

	  	if (sumConst_0 == true) {
	  		return "(= 0 " + addConstraint_full(addElements) + ")";
	  	}
	  	else {
	  	}

	  	/* work as usual */
	  	addElements.clear();
	  	splitPos = 0;

	  	for (unsigned int i = 0; i < elementNames.size(); ++i){
	  		if (elementNames[i].second >= 0) /* not const */ {
	  			addElements.push_back(generateFlatSize(elementNames[i]));
	  		}
	  		else { /* const or regex */
	  			if (addElements.size() > 0){ /* create a sum for previous elements */
	  				strAnd.push_back("(= (% " + addConstraint_full(addElements) + " " +  std::to_string(a.first.length()) + ") " + std::to_string(std::abs(split[splitPos])) + ")");
	  				splitPos++;
	  				addElements.clear();
	  			}

	  			if (elementNames[i].second == -1 && i < elementNames.size() - 1) { /* const and not at the end */
	  				if (QCONSTMAX == 1) {
	  					strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos]) + ")");
	  					splitPos++;
	  				}
	  				else {
	  					assert(elementNames[i + 1].second == -2);
	  					strAnd.push_back("(= (+ " + generateFlatSize(elementNames[i], rhs) + " " + generateFlatSize(elementNames[i + 1], rhs) + ") " + std::to_string(split[splitPos] + split[splitPos + 1]) + ")");
	  					i++;
	  					splitPos += 2;
	  				}
	  			}
	  			else if (elementNames[i].second == REGEX_CODE) {/* regex */
	  				if (split[splitPos] >= 0 && split[splitPos] != MINUSZERO) { /* do not repeat */
	  					strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos]) + ")");
	  					splitPos++;
	  				}
	  				else { /* can repeat many times */
	  					if (split[splitPos] == MINUSZERO)
	  						split[splitPos] = 0;
	  					strAnd.push_back("(= (% " + generateFlatSize(elementNames[i], rhs) + " " +  std::to_string(a.first.length()) + ") " + std::to_string(std::abs(split[splitPos])) + ")");
	  					splitPos++;
	  				}
	  			}
	  			else { /* const at the end */
	  				strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos++]) + ")");
	  			}
	  		}
	  	}

	  	if (addElements.size() > 0) {
	  		/* create a sum for previous elements */

	  		strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(split[splitPos++]) + ")");
	  	}
	  	assert(splitPos == split.size());
	  	return andConstraint(strAnd);
	  }

		/*
		 * Input: constA and a number of flats
		 * Output: all possible ways to split constA
		 */
		std::vector<std::vector<int> > collectAllPossibleSplits(
				std::pair<std::string, int> lhs,
				std::vector<std::pair<std::string, int> > elementNames,
				int pMax
				){
			/* create alias elementNames with smaller number of elements*/
			std::vector<std::pair<std::string, int> > alias;
			int pre = 0;
			int cnt = 0;
			for (unsigned int i = 0; i < elementNames.size(); ++i)
				if (elementNames[i].second < 0) {
					if (pre > 0) {
						alias.push_back(std::make_pair("e" + std::to_string(cnt++), pre));
						pre = 0;
					}
					alias.push_back(elementNames[i]);
				}
				else
					pre++;
			if (pre > 0)
				alias.push_back(std::make_pair("e" + std::to_string(cnt++), pre));

			/* use alias instead of elementNames */
			std::vector<std::vector<int> > allPossibleSplits;
			if (lhs.second == -2) /* tail */ {
				for (unsigned int i = 1; i <= lhs.first.length(); ++i) {
					std::vector<int> curr;
					collectAllPossibleSplits_const(0, lhs.first.substr(i), 10, alias, curr, allPossibleSplits);
				}
			}
			else if (lhs.second == -1) /* head */ {
				if (QCONSTMAX == 1) {
					std::vector<int> curr;
					collectAllPossibleSplits_const(0, lhs.first, 10, alias, curr, allPossibleSplits);
				}
				else for (unsigned int i = 0; i <= lhs.first.length(); ++i) {
					std::vector<int> curr;

					collectAllPossibleSplits_const(0, lhs.first.substr(0, i), 10, alias, curr, allPossibleSplits);

				}
			}
			else if (lhs.second == REGEX_CODE) /* regex */ {
				std::vector<int> curr;
				collectAllPossibleSplits_regex(0, lhs.first, 10, alias, curr, allPossibleSplits);
			}
			else
				assert(false);

			/* print test */
//			for (int i = 0; i < allPossibleSplits.size(); ++i){
//				splitPrintTest(allPossibleSplits[i], "Accepted");
//			}
//
//			printf("%d cases: %ld\n", __LINE__, allPossibleSplits.size());

//			std::set<std::string> resultParts;
//			if (lhs.second != REGEX_CODE)
//				for (int i = 0; i < allPossibleSplits.size(); ++i){
//					resultParts.emplace(fromSplitToLengConstraint_const(lhs, elementNames, allPossibleSplits[i], "", ""));
//				}
//			else
//				for (int i = 0; i < allPossibleSplits.size(); ++i){
//					resultParts.emplace(fromSplitToLengConstraint_regex(lhs, elementNames, allPossibleSplits[i], "", ""));
//				}
//
//
//			for (std::set<std::string>::iterator it = resultParts.begin(); it != resultParts.end(); ++it)
//				printf("%d %s\n", __LINE__, it->c_str());

			return allPossibleSplits;
		}

	/*
	 * create (or constraint01 constraint02 .. constraint0n)
	 */
	std::string orConstraint(std::vector<std::string> possibleCases){
		std::string result = "";
		assert (possibleCases.size() > 0);
		if (possibleCases.size() > 1) {
			result = "(or ";
			for (unsigned int i = 0; i < possibleCases.size(); ++i)
				result = result + possibleCases[i] + " ";
			result = result + ")";
		}
		else if (possibleCases.size() == 1){
			result = possibleCases[0];
		}
		return result;
	}

	/*
	 * a b c
	 */
	std::string addConstraint_half(std::vector<std::string> elements) {
		std::string result = "";
		if (elements.size() == 0)
			return "0";
		if (elements.size() == 1)
			return elements[0];
		if (elements.size() > 1) {
			result = "";
			for (unsigned int i = 0; i < elements.size(); ++i)
				result = result + elements[i] + " ";
		}
		return result;
	}

	std::string notConstraint(
			std::pair<std::string, int> a /* const || var */,
			std::pair<std::string, int> b /* const || var */) {
		if (a.second < 0) /* const */ {
			if (b.second < 0) /* const */
				return "(not (= " + std::to_string(b.first.length()) + " " + std::to_string(a.first.length()) + "))";
			else /* var */
				return "(not (= len_" + b.first + " " + std::to_string(a.first.length()) + "))";
		}
		else {
			if (b.second < 0) /* const */
				return "(not (= " + std::to_string(b.first.length()) + " len_" + a.first + "))";
			else /* var */
				return "(not (= len_" + b.first + " len_" + a.first + "))";
		}
	}

  /*
   *
   */
  std::string leng_prefix_lhs(std::pair<std::string, int> a,
  		std::vector<std::pair<std::string, int>> elementNames,
  		std::string lhs, std::string rhs,
  		int pos) {
  	std::vector<std::string> addElements;
  	for (int i = a.second + 1; i < 0; ++i){ /* prefix of a - const */
  		addElements.push_back(generateFlatSize(std::make_pair(a.first, i), lhs));
  	}

  	for (int i = a.second - 1; i >= 0; --i){ /* a is var */
  		addElements.push_back(generateFlatSize(std::make_pair(a.first, i), lhs));
  	}

  	for (int i = 0 ; i < pos; ++i) { /* pre-elements */
  		addElements.push_back(generateFlatSize(elementNames[i], rhs));
  	}

  	return addConstraint_half(addElements);
  }

  /*
   *
   */
  std::string leng_prefix_rhs(std::pair<std::string, int> a, /* var */
  		std::string rhs) {
  	std::vector<std::string> addElements;
  	for (int i = a.second + 1; i < 0; ++i){ /* a is const */
  		addElements.push_back(generateFlatSize(std::make_pair(a.first, i), rhs));
  	}

  	for (int i = a.second - 1; i >= 0; --i){ /* a is var */
  		addElements.push_back(generateFlatSize(std::make_pair(a.first, i), rhs));
  	}

  	return addConstraint_half(addElements);
  }

  /*
   *
   */
//  std::string leng_prefix_element(std::vector<std::pair<std::string, int>> elementNames,
//  		std::string rhs,
//  		int pos) {
//  	std::vector<std::string> addElements;
//  	assert (pos < elementNames.size());
//
//  	for (int i = 0; i < pos; ++i){
//  		addElements.push_back(generateFlatSize(elementNames[i], rhs));
//  	}
//
//  	return addConstraint(addElements);
//  }

	/*
	 * Given a flat,
	 * generate its size constraint
	 */
	std::string generateFlatArray(std::pair<std::string, int> a, std::string l_r_hs = ""){
		std::string result = "";
		if (a.second >= 0) {
			/* simpler version */
			result = result + "arr_" + a.first;
		}
		else {
			/* const string */
			assert (l_r_hs.length() > 0);
//			result = result + "arr_" + constMap[std::make_pair(a.first, l_r_hs)];
			result = result + "arr_" + constMap[a.first];
			// printf("%d, at generate flat size (%s of %s) = %s\n", __LINE__, a.first.c_str(), l_r_hs.c_str(),constMap[std::make_pair(a.first, l_r_hs)].c_str());
		}
		return result;
	}

	/*
	 * 0: No const, No connected var
	 * 1: No const
	 * 2: Otherwise
	 */
	int checkTheBestSplitType(
			std::vector<std::pair<std::string, int>> elementNames,
			std::set<std::string> connectedVariables){
		int result = 0;
		/* 0: No const, No connected var */
		for (unsigned int i = 0 ; i < elementNames.size(); ++i)
			if (elementNames[i].second < 0 || connectedVariables.find(elementNames[i].first) != connectedVariables.end()) {
				result = 1;
				break;
			}

		/* 1: No const */
		if (result == 1) {
			for (unsigned int i = 0 ; i < elementNames.size(); ++i)
				if (elementNames[i].second < 0) {
					result = 2;
					break;
				}
		}
		return result;
	}

	/*
	 * No const,
	 * No Connected var
	 */
	bool isFreeToSplit_haveConnected(
			std::vector<std::pair<std::string, int>> elementNames,
			std::set<std::string> connectedVariables){
		for (unsigned int i = 0 ; i < elementNames.size(); ++i)
			if (elementNames[i].second < 0 || connectedVariables.find(elementNames[i].first) != connectedVariables.end())
				return false;
		return true;
	}

  /*
   * Input: split a string
   * Output: SMT
   */
  std::string fromSplitToLengConstraint(
  		std::pair<std::string, int> a, /* const */
  		std::vector<std::pair<std::string, int> > elementNames,
  		std::vector<int> split,
  		std::string lhs, std::string rhs){

  	int totalLength = 0;
  	for (unsigned int j = 0; j < split.size(); ++j)
  		totalLength = totalLength + split[j];

  	std::vector<std::string> strAnd;
  	strAnd.push_back("(= " + generateFlatSize(a, lhs) + " " + std::to_string(totalLength) + ")");

  	std::vector<std::string> addElements;

  	/* check if size of all consts = 0 */
  	bool sumConst_0 = true, metVar = false;
  	unsigned int splitPos = 0;
  	for (unsigned int i = 0; i < elementNames.size(); ++i) {
  		if (elementNames[i].second < 0) {
  			if (metVar)
  				splitPos++;
  			if (split[splitPos++] > 0){
  				sumConst_0 = false;
  				break;
  			}
  			addElements.push_back(generateFlatSize(elementNames[i], rhs));
  			metVar = false;
  		}
  		else
  			metVar = true;
  	}

  	if (sumConst_0 == true) {
  		return "(= 0 " + addConstraint_full(addElements) + ")";
  	}
  	else {
//  		for (int i = 0; i < elementNames.size(); ++i)
//  			printf("%s.%d ", elementNames[i].first.c_str(), elementNames[i].second);
//  		printf("\n");
//  		for (int i = 0; i < split.size(); ++i)
//  			printf("%d ", split[i]);
//  		printf("\n");
  	}

  	/* work as usual */
  	addElements.clear();
  	splitPos = 0;

  	for (unsigned int i = 0; i < elementNames.size(); ++i){
  		if (elementNames[i].second >= 0) /* not const */ {
  			addElements.push_back(generateFlatSize(elementNames[i]));
  		}
  		else { /* const */
  			if (addElements.size() > 0){ /* create a sum for previous elements */
  				strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(split[splitPos]) + ")");
  				splitPos++;
  				addElements.clear();
  			}

  			if (elementNames[i].second == -1 && i < elementNames.size() - 1) {
  				if (QCONSTMAX == 1 || elementNames[i].first.length() == 1) {
  					strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos]) + ")");
  					splitPos++;
  				}
  				else {
  					assert(elementNames[i + 1].second == -2);
  					strAnd.push_back("(= (+ " + generateFlatSize(elementNames[i], rhs) + " " + generateFlatSize(elementNames[i + 1], rhs) + ") " + std::to_string(split[splitPos] + split[splitPos + 1]) + ")");
  					i++;
  					splitPos += 2;
  				}
  			}
  			else {
  				strAnd.push_back("(= " + generateFlatSize(elementNames[i], rhs) + " " + std::to_string(split[splitPos++]) + ")");
  			}
  		}
  	}

  	if (addElements.size() > 0) {
  		/* create a sum for previous elements */

  		strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(split[splitPos++]) + ")");
  	}
  	assert(splitPos == split.size());
  	return andConstraint(strAnd);
  }

  /*
   * Input: split a string
   * Output: SMT
   */
  std::string fromSplitToSMT(
  		std::pair<std::string, int> a, /* const */
  		std::vector<std::pair<std::string, int>> elementNames,
  		std::vector<int> split,
  		std::set<std::string> connectedVariables,
  		std::map<std::string, int> &newVars){

  	int totalLength = 0;
  	for (unsigned int j = 0; j < split.size(); ++j)
  		totalLength = totalLength + split[j];

  	std::string value = "";
  	if (a.second == -1) /* head */
  		value = a.first.substr(0, totalLength);
  	else if (a.second == -2) /* tail */
  		value = a.first.substr(a.first.length() - totalLength, totalLength);

  	std::vector<std::string> strAnd;

  	std::vector<std::string> addElements;
  	int addLength = 0;

  	std::vector<std::string> connectedParts;
  	int addConnected = 0;

  	for (unsigned int i = 0; i < elementNames.size(); ++i){
  		if (elementNames[i].second >= 0) /* not const */ {
  			/* connected variable */
  			if (connectedVariables.find(elementNames[i].first) != connectedVariables.end()) { /* connected variable */

  				/* create a sum for previous elements */
  				if (addElements.size() > 0) {
  					strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(addLength) + ")");

  					/* reset previous elements*/
  					addElements.clear();
  					addLength = 0;
  				}

  				/* check if it is the same variable */
  				bool sameVar = false;
  				if (i > 0 && elementNames[i].second == elementNames[i - 1].second + 1) {
  					sameVar = true;
  				}

  				/* if it is the same, we skip. Otherwise, we create constraints, AND reset list */
  				if (sameVar == false) {
  					strAnd.push_back("(= " + addConstraint_full(connectedParts) + " " + std::to_string(addConnected) + ")");
  					int pos = 0;
  					for (unsigned int j = 0; j <= i; ++j)
  						pos = pos + split[j];
  					pos = pos - addConnected;

  					strAnd.push_back(const_to_var(elementNames[i], value.substr(pos, addConnected), newVars));

  					/* reset */
  					connectedParts.clear();
  					addConnected = 0;
  				}

  				/* push element to list */
  				connectedParts.push_back(generateFlatSize(elementNames[i]));
  				addConnected += split[i];
  			}
  			else {
  				addElements.push_back(generateFlatSize(elementNames[i]));
  				addLength += split[i];
  			}
  		}
  		else
  			assert (false);
  	}

  	if (addElements.size() > 0) {
  		/* create a sum for previous elements */
  		strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(addLength) + ")");

  		/* DONOT need to reset previous elements*/
  	}

  	// TODO:
  	if (connectedParts.size() > 0) {
  		/* create a sum for previous elements */
  		strAnd.push_back("(= " + addConstraint_full(addElements) + " " + std::to_string(addLength) + ")");

  		/* DONOT need to reset previous elements*/
  	}
  	assert (strAnd.size() > 0);
  	return andConstraint(strAnd);
  }

  /*
   *
   */
  std::string connectedVar_anywhere(
  		std::pair<std::string, int> a, /* const */
  		std::vector<std::pair<std::string, int>> elementNames, /* no const */
  		std::string lhs, std::string rhs,
  		std::set<std::string> connectedVariables,
  		std::map<std::string, int> &newVars){

  	std::string arrayLhs = generateFlatArray(a, lhs);
  	std::vector<std::string> resultParts;

  	for (unsigned int i = 0; i < elementNames.size(); ++i){
  		if (elementNames[i].second >= 0) /* not const */ {

  			/* connected variable */
  			if (connectedVariables.find(elementNames[i].first) != connectedVariables.end()) { /* connected variable */
  				/* how many part of that connected variable are in the const */
  				int partCnt = 1;
  				std::vector<std::string> addElements; addElements.push_back(generateFlatSize(elementNames[i]));
  				for (unsigned int j = i + 1; j < elementNames.size(); ++j)
  					if (elementNames[j].second > elementNames[j - 1].second && elementNames[j].second > 0) {
  						partCnt++;
  						// printf("%d %s.%d\n", __LINE__, elementNames[j].first.c_str(), elementNames[j].second);
  						addElements.push_back(generateFlatSize(elementNames[j]));
  					}

  				/* sublen = part_1 + part2 + .. */
  				std::string subLen = addConstraint_full(addElements);

  				std::string prefix_rhs = leng_prefix_rhs(elementNames[i], rhs);
  				std::string prefix_lhs = leng_prefix_lhs(a, elementNames, lhs, rhs, i);

  				bool lhs_zero = false;
  				bool rhs_zero = false;
  				if (prefix_lhs.length() == 1 && prefix_lhs[0] == '0')
  					lhs_zero = true;
  				if (prefix_rhs.length() == 1 && prefix_rhs[0] == '0')
  					rhs_zero = true;

  				std::string arrayRhs = generateFlatArray(elementNames[i], rhs);

  				if (QCONSTMAX == 1) {
  					resultParts.push_back("(= " + subLen + " " + std::to_string(a.first.length()) + ")");
  					/* forall ((i Int)) (and (< i a.first.length()))*/
//  					char strTmp[1000];

//  					sprintf(strTmp, "(forall ((i Int)) (and (< i %ld) (= (select %s (+ i %s)) (select %s (+ i %s)))))",
//  							a.first.length(),
//  							arrayLhs.c_str(), prefix_lhs.c_str(),
//  							arrayRhs.c_str(), prefix_rhs.c_str());

  					for (unsigned int k = 0; k < a.first.length(); ++k){
  						resultParts.push_back("(= (select " + arrayLhs + " (+ " + std::to_string(k) + " " + prefix_lhs + ")) " +
									 "(select " + arrayRhs + " (+ " + std::to_string(k) + " " + prefix_rhs + ")))");

  					}
  				}
  				else {
						std::vector<std::string> possibleCases; /* sublen = 0 || sublen = 1 || .. */
//						int minNumber = std::min(LOCALSPLITMAX, (int)a.first.length());
//						char strTmp[1000];
//						sprintf(strTmp, "(exists ((j Int)) (implies (and (< j %d) (= j %s)) (forall ((i Int)) (implies (and (>= i 0) (< i j)) (= (select %s (+ i %s)) (select %s (+ i %s)))))))",
//								minNumber,
//								subLen.c_str(),
//								arrayLhs.c_str(), prefix_lhs.c_str(),
//								arrayRhs.c_str(), prefix_rhs.c_str());
//						__debugPrint(logFile, "%d %s \n", __LINE__, strTmp);
//						possibleCases.push_back(strTmp);

//						/* clone to optimize leng of generated string */
						if (lhs_zero && rhs_zero) {
							for (int j = 0; j <= std::min(LOCALSPLITMAX, (int)a.first.length()); j++){
								std::vector<std::string> subpossibleCases; /*at_0 = x && at_1 == y && ..*/
								subpossibleCases.push_back("(= " + subLen + " " + std::to_string(j) + ")");
								for (int k = 0; k < j; ++k){
									subpossibleCases.push_back("(= (select " + arrayLhs + " " + std::to_string(k) + ") " +
											"(select " + arrayRhs + " " + std::to_string(k) + "))");
								}
								possibleCases.push_back(andConstraint(subpossibleCases));
							}

							/* exists and forall */
//							char strTmp[1000];
//							sprintf(strTmp, "(exists ((%s Int)) (implies (and (< %s %d) (< %s %d))) (forall ((i Int)) (and (< i %s) (= (select %s i) (select %s i)))))",
//															subLen.c_str(),
//															subLen.c_str(),
//															LOCALSPLITMAX,
//															a.first.length(),
//															subLen.c_str(),
//															arrayLhs.c_str(),
//															arrayRhs.c_str());
//							__debugPrint(logFile, "%d %s\n", __LINE__, strTmp);
						}
						else if (lhs_zero && !rhs_zero){
							for (int j = 0; j <= std::min(LOCALSPLITMAX, (int)a.first.length()); j++){
								std::vector<std::string> subpossibleCases; /*at_0 = x && at_1 == y && ..*/
								subpossibleCases.push_back("(= " + subLen + " " + std::to_string(j) + ")");
								for (int k = 0; k < j; ++k){
									subpossibleCases.push_back("(= (select " + arrayLhs + " " + std::to_string(k) + ") " +
											"(select " + arrayRhs + " (+ " + std::to_string(k) + " " + prefix_rhs + ")))");
								}
								possibleCases.push_back(andConstraint(subpossibleCases));
							}

							/* exists and forall */
//							char strTmp[1000];
//							sprintf(strTmp, "(exists ((%s Int)) (implies (and (< %s %d) (< %s %d))) (forall ((i Int)) (and (< i %s) (= (select %s i) (select %s (+ i %s))))))",
//																subLen.c_str(),
//																subLen.c_str(),
//																LOCALSPLITMAX,
//																a.first.length(),
//																subLen.c_str(),
//																arrayLhs.c_str(),
//																arrayRhs.c_str(), prefix_rhs.c_str());
//							__debugPrint(logFile, "%d %s\n", __LINE__, strTmp);
						}
						else if (!lhs_zero && rhs_zero){
							for (int j = 0; j <= std::min(LOCALSPLITMAX, (int)a.first.length()); j++){
								std::vector<std::string> subpossibleCases; /*at_0 = x && at_1 == y && ..*/
								subpossibleCases.push_back("(= " + subLen + " " + std::to_string(j) + ")");
								for (int k = 0; k < j; ++k){
									subpossibleCases.push_back("(= (select " + arrayLhs + " (+ " + std::to_string(k) + " " + prefix_lhs + ")) " +
											"(select " + arrayRhs + " " + std::to_string(k) + "))");
								}
								possibleCases.push_back(andConstraint(subpossibleCases));
							}
							/* exists and forall */
//							char strTmp[1000];
//							sprintf(strTmp, "(exists ((%s Int)) (implies (and (< %s %d) (< %s %d))) (forall ((i Int)) (and (< i %s) (= (select %s (+ i %s)) (select %s (+ i %s))))))",
//																subLen.c_str(),
//																subLen.c_str(),
//																LOCALSPLITMAX,
//																a.first.length(),
//																subLen.c_str(),
//																arrayLhs.c_str(), prefix_lhs.c_str(),
//																arrayRhs.c_str());
						}
						else for (int j = 0; j <= std::min(LOCALSPLITMAX, (int)a.first.length()); j++){
							std::vector<std::string> subpossibleCases; /*at_0 = x && at_1 == y && ..*/
							subpossibleCases.push_back("(= " + subLen + " " + std::to_string(j) + ")");
							for (int k = 0; k < j; ++k){
								subpossibleCases.push_back("(= (select " + arrayLhs + " (+ " + std::to_string(k) + " " + prefix_lhs + ")) " +
																					 "(select " + arrayRhs + " (+ " + std::to_string(k) + " " + prefix_rhs + ")))");

							}
							possibleCases.push_back(andConstraint(subpossibleCases));
						}
						i += (partCnt - 1);
						resultParts.push_back(orConstraint(possibleCases));
  				}
  			}
  		}
  	}

  	return andConstraint(resultParts);
  }

  /*
   * maximum length the string can be until sum[i]
   * 1. count the remaining const
   * return sumConst - count
   */
  int maxLengthUntilPos(std::vector<std::pair<std::string, int>> sum, int pos){
  	int result = 0;
  	for (int i = sum.size() - 2; i >= pos; --i)
  		if (sum[i].second == -1 && sum[i + 1].second == -2) /* const string */ {
  			result = result + sum[i].first.length();
  		}
  	return PMAX - result;
  }

  /*
   * minimum length the string can be until sum[i]
   * 1. count the remaining const
   * return sumConst
   */
  int minLengthUntilPos(std::vector<std::pair<std::string, int>> sum, int pos){
  	int result = 0;
  	for (int i = 0; i < pos - 1; ++i)
  		if (sum[i].second == -1 && sum[i + 1].second == -2) /* const string */ {
  			result = result + sum[i].first.length();
  		}
  	return result;
  }

  /*
   * total length of [0..pos] flats
   * (+ ...)
   */
  std::string headerLength(
  		std::vector<std::pair<std::string, int>> elementNames,
  		int pos,
  		std::string rhs_str){
  	if (pos == 0) {
  		assert (false);
  		return "0";
  	}

  	std::string result = "";
  	int length = 0;
  	/* check fixed length? */
  	for (int i = 0; i < pos - 1; ++i) {
  		if (elementNames[i].second < 0){
  			if (elementNames[i].second == -1 && elementNames[i + 1].second == -2) {
  				length += elementNames[i].first.length();
  			}
  		}
  		else {
  			length = -1;
  			break;
  		}
  	}
  	if (length >= 0 && elementNames[pos - 1].second == -2)
  		return "const_" + std::to_string(length);

  	/* work as usual */
  	for (int i = 0; i < pos; ++i) {
  		assert (false);
  		result = result + generateFlatSize(elementNames[i]) + " ";
  	}
  	if (pos > 1)
  		result = "(+ " + result + ")";
  	return result;
  }

  /*
   * Case: X =  "abc"
   * return: (and X_0 = a && X_[1] = b && X_[1] = c)
   */
  std::string const_to_var(
  		std::pair<std::string, int> a,
  		std::string constB,
  		std::map<std::string, int> &newVars) {
  	std::string result = "";

  	std::string varName = a.first + "_" + std::to_string(a.second) + "_";
  	for (unsigned int i = 0; i < constB.length(); ++i) {
  		/* constraint */
  		result = result + "(= " + varName + std::to_string(i) + " " + std::to_string(constB[i]) + ") ";

  		/* and new var */
  		newVars[varName + std::to_string(i)] = 'd';
  	}
  	return result;
  }

  /*
   * Generate constraints for the case
   * X = T . "abc" . Y . Z
   * constPos: position of const element
   * return: (or (and length header = i && X_i = a && X_[i+1] = b && X_[i+2] = c))
   */
  std::string handle_Const_WithPosition_array(
  		std::pair<std::string, int> a,
  		std::vector<std::pair<std::string, int>> elementNames,
  		std::string lhs_str, std::string rhs_str,
  		int constPos,
  		std::string value, /* value of string */
  		int start, int finish,
  		std::map<std::string, int> &newVars,
  		std::string extraConstraint = "" /* length = ? */) {
  	assert (elementNames[constPos].second < 0);

  	std::vector<std::string> locationConstraint;
  	if (extraConstraint.length() > 0)
  		locationConstraint.push_back(extraConstraint);

  	/* find the start position --> */
  	std::string startPos = leng_prefix_lhs(a, elementNames, lhs_str, rhs_str, constPos);

  	/* optimize length of generated string */
  	std::string tmp01 = generateFlatArray(a, lhs_str);

  	if (startPos.size() == 1 && startPos[0] == '0') {
  		for (int i = start; i < finish; ++i) {
  			locationConstraint.push_back("(= (select " + tmp01 + " " + std::to_string(i - start) + ") " + std::to_string(value[i]) + ")");
  		}
  	}

  	else for (int i = start; i < finish; ++i) {
  		locationConstraint.push_back("(= (select " + tmp01 + " (+ " + std::to_string(i - start) + " " + startPos + ")) " + std::to_string(value[i]) + ")");
  	}

  	assert (locationConstraint.size() > 0);
  	std::string result = andConstraint(locationConstraint) + "\n";
  	return result;
  }

  /*
   * Generate constraints for the case
   * X = T . "abc" . Y . Z
   * constPos: position of const element
   * return: (or (and length header = i && X_i = a && X_[i+1] = b && X_[i+2] = c))
   */
  std::string handle_SubConst_WithPosition_array(
  		std::pair<std::string, int> a,
  		std::vector<std::pair<std::string, int>> elementNames,
  		std::string lhs_str, std::string rhs_str,
  		int constPos,
  		std::map<std::string, int> &newVars) {
  	assert (elementNames[constPos].second < 0);

  	/* find the start position --> */
  	std::vector<std::string> locationConstraint;

  	std::vector<std::string> possibleCases;
  	if (elementNames[constPos].second == -1) {

  		for (int i = 0; i <= std::min(LOCALSPLITMAX, (int)elementNames[constPos].first.length()); ++i) {
  			/*length = i*/
  			std::string tmp = "(= " + generateFlatSize(elementNames[constPos], rhs_str) + " " + std::to_string(i) + ")";
  			possibleCases.push_back(handle_Const_WithPosition_array(a, elementNames, lhs_str, rhs_str, constPos, elementNames[constPos].first, 0, i, newVars, tmp));
//  			possibleCases.push_back(handle_Const_WithPosition_array(a, elementNames, lhs_str, rhs_str, constPos, elementNames[constPos].first.substr(0, i), newVars, tmp));
  		}
  	}
  	else {
  		for (int i = 0; i <= std::min(LOCALSPLITMAX, (int)elementNames[constPos].first.length()); ++i) {
  			/*length = i*/
  			std::string tmp = "(= " + generateFlatSize(elementNames[constPos], rhs_str) + " " + std::to_string(elementNames[constPos].first.length() - i) + ")";
//  			possibleCases.push_back(handle_Const_WithPosition_array(a, elementNames, lhs_str, rhs_str, constPos, elementNames[constPos].first.substr(i), newVars, tmp));
  			possibleCases.push_back(handle_Const_WithPosition_array(a, elementNames, lhs_str, rhs_str, constPos, elementNames[constPos].first, i, elementNames[constPos].first.length(), newVars, tmp));
  		}
  	}

  	std::string result = orConstraint(possibleCases);
  	return result;
  }

	/*
	 *
	 */
	std::string unrollConnectedVariable(
			std::pair<std::string, int> a, /* connected variable */
			std::vector<std::pair<std::string, int> > elementNames, /* contain const */
			std::string lhs_str, std::string rhs_str,
			std::set<std::string> connectedVariables,
			std::map<std::string, int> &newVars){

		assert(connectedVariables.find(a.first) != connectedVariables.end());
		/* (and ...) */
		std::vector<std::string> possibleCases;

		for (unsigned int i = 0 ; i < elementNames.size(); ++i){
			if (elementNames[i].second < 0){ /* const */
				if (elementNames.size() == 1 && QCONSTMAX > 1) { /* |lhs| = 1 vs |rhs| = 1*/
					possibleCases.push_back(handle_SubConst_WithPosition_array(a, elementNames, lhs_str, rhs_str, i, newVars));
				}
				else if (i == 0 && elementNames[i].second == -2 && QCONSTMAX > 1) /* tail of string, head of elements*/ {
					possibleCases.push_back(handle_SubConst_WithPosition_array(a, elementNames, lhs_str, rhs_str, i, newVars));
				}
				else if (i == elementNames.size() - 1 && elementNames[i].second == -1 && QCONSTMAX > 1) /* head of string, tail of elements */ {
					possibleCases.push_back(handle_SubConst_WithPosition_array(a, elementNames, lhs_str, rhs_str, i, newVars));
				}
				else if (elementNames[i].second == -1) /* only care about first element */ {
					// std::string tmp = "(= (+ " + generateFlatSize(elementNames[i], rhs_str) + " " + generateFlatSize(elementNames[i + 1], rhs_str) + ") " + std::to_string(elementNames[i].first.length()) + ")";
					possibleCases.push_back(handle_Const_WithPosition_array(a, elementNames, lhs_str, rhs_str, i, elementNames[i].first, 0, elementNames[i].first.length(), newVars));
				}
			}
		}
		return andConstraint(possibleCases);
	}

  /*
   *
   * Flat = empty
   */

  	std::string generateConstraint00(
  			std::pair<std::string, int> a,
  			std::string l_r_hs,
  			std::map<std::string, int> &newVars){

  		return "(= " + generateFlatSize(a, l_r_hs) + " 0)";
  	}

  	/*
  	 * Flat = Flat
  	 * size = size && it = it  ||
  	 * size = size && it = 1
  	 */
  	std::string generateConstraint01(
  			std::string lhs_str, std::string rhs_str,
  			std::pair<std::string, int> a, std::pair<std::string, int> b,
  			int pMax,
  			std::set<std::string> connectedVariables,
  			std::map<std::string, int> &newVars){
  		bool isConstA = a.second < 0;
  		bool isConstB = b.second < 0;



  		std::string nameA = generateFlatSize(a, lhs_str);
  		std::string nameB = generateFlatSize(b, rhs_str);

  		/* do not need AND */
  		std::string result = "(= " + nameA + " " + nameB + ")";

  		if (!isConstA && !isConstB) {
  			/* size = size && it = it */
  		}
  		else if (isConstA && isConstB) {
  			if (QCONSTMAX == 1 && a.first.compare(b.first) != 0) /* const = const */
  				return "";
  			std::vector<std::string> possibleCases;

  			if (a.second == -1 && b.second == -1) /* head vs head */ {
  				for (int i = std::min(a.first.length(), b.first.length()); i >= 0; --i) {
  					if (a.first.substr(0, i).compare(b.first.substr(0, i)) == 0) {
  						/* size can be from 0..i */
  						result = result + " (<= " + nameA + " " + std::to_string(i) + ")";
  						return result;
  					}
  				}
  			}
  			else if (a.second == -1 && b.second == -2) /* head vs tail */ {
  				for (int i = std::min(a.first.length(), b.first.length()); i >= 0; --i) {
  					if (a.first.substr(0, i).compare(b.first.substr(b.first.length() - i)) == 0) {
  						/* size can be i */
  						possibleCases.push_back("(= " + nameA + " " + std::to_string(i) + ")");
  					}
  				}
  			}
  			else if (a.second == -2 && b.second == -1) /* tail vs head */ {
  				for (int i = std::min(a.first.length(), b.first.length()); i >= 0; --i) {
  					if (b.first.substr(0, i).compare(a.first.substr(a.first.length() - i)) == 0) {
  						/* size can be i */
  						possibleCases.push_back("(= " + nameA + " " + std::to_string(i) + ")");
  					}
  				}
  			}
  			else if (a.second == -2 && b.second == -2) /* tail vs tail */ {

  				for (int i = std::min(a.first.length(), b.first.length()); i >= 0; --i) {
  					if (a.first.substr(a.first.length() - i, i).compare(b.first.substr(b.first.length() - i, i)) == 0) {
  						/* size can be i */
  						result = result + " (<= " + nameA + " " + std::to_string(i) + ")";
  						// printf("%d %s.2 = %s.2 --> %d\n", __LINE__, a.first.c_str(), b.first.c_str(), i);
  						return result;
  					}
  				}
  			}

  			/* create or constraint */
  			std::string tmp = orConstraint(possibleCases);
  			if (tmp.length() == 0)
  				return tmp;
  			else
  				result = result + " " + tmp;

  			return result;
  		}

  		else if (isConstA) {
  			/* size = size && it = 1*/

  			/* record characters for some special variables */
  			if (connectedVariables.find(b.first) != connectedVariables.end()){
  				std::vector<std::pair<std::string, int>> elements;
  				elements.push_back(a);
  				result = result + " " + unrollConnectedVariable(b, elements, rhs_str, lhs_str, connectedVariables, newVars);
  			}

  			/* constraint for not equal */
  			/* (not (= len_b a.length)) */
  			if (notMap.find(b.first) != notMap.end() &&
  					notMap[b.first].find(a.first) != notMap[b.first].end()) {
  				result = result + " " + notConstraint(a, b);
  			}
  		}

  		else { /* isConstB */
  			/* size = size && it = 1*/
  			/* record characters for some special variables */
  			if (connectedVariables.find(a.first) != connectedVariables.end()){
  				std::vector<std::pair<std::string, int>> elements;
  				elements.push_back(b);
  				result = result + " " + unrollConnectedVariable(a, elements, lhs_str, rhs_str, connectedVariables, newVars);
  			}

  			/* constraint for not equal */
  			/* (not (= len_a b.length)) */
  			if (notMap.find(a.first) != notMap.end() &&
  					notMap[a.first].find(b.first) != notMap[a.first].end()) {
  				result = result + " " + notConstraint(a, b);
  			}
  		}

  		return result;
  	}

	/*
	 * Flat = sum (flats)
	 */
	std::string generateConstraint02(
			std::pair<std::string, int> a,
			std::vector<std::pair<std::string, int>> elementNames,
			std::string lhs_str, std::string rhs_str,
			int pMax,
			std::set<std::string> connectedVariables,
			std::map<std::string, int> &newVars){
		std::string result = "";
		/* constraint for not equal */
		for (unsigned int i = 0; i < elementNames.size(); ++i)
			if ((notMap.find(elementNames[i].first) != notMap.end() &&
					notMap[elementNames[i].first].find(a.first) != notMap[elementNames[i].first].end()) ||
				(notMap.find(a.first) != notMap.end() &&
									notMap[a.first].find(elementNames[i].first) != notMap[a.first].end())) {
				result = result + " " + notConstraint(a, elementNames[i]);
			}

		if (a.second < 0) { /* const string */
			/* check feasibility */
			int max_lhs = a.first.length();

			int max_rhs = 0;
			for (unsigned int i = 0; i < elementNames.size(); ++i) {
				if (elementNames[i].second == -1) {
					if (QCONSTMAX == 2 && i + 1 < elementNames.size() && elementNames[i + 1].second == -2)
						max_rhs += elementNames[i].first.length();
					else if (QCONSTMAX == 1)
						max_rhs += elementNames[i].first.length();
				}
			}
			if (max_lhs < max_rhs)
				return "";

			/* cannot split */
			// int minFlats = splitWithMinFlats(sum.size(), pMax, a.first);

			/* collect */
			/* I only handle the case of splitting const string into two parts*/
			std::vector<std::string> addElements;
			for (unsigned int i = 0 ; i < elementNames.size(); ++i)
				addElements.push_back(generateFlatSize(elementNames[i], rhs_str));

			result = result + " (= " + generateFlatSize(a, lhs_str) + " " + addConstraint_full(addElements) + ")";

			/*
			 * 0: No const, No connected var
			 * 1: No const
			 * 2: Otherwise
			 */
			int splitType = checkTheBestSplitType(elementNames, connectedVariables);

			if (splitType == 0) {/* rhs only has simple variables */
				/* do not do anything */
			}
			else if (splitType == 1) {
				/* connected var can be anywhere */
				result = result + " " + connectedVar_anywhere(a, elementNames, lhs_str, rhs_str, connectedVariables, newVars);
			}
			else {

				result = result + " " + connectedVar_anywhere(a, elementNames, lhs_str, rhs_str, connectedVariables, newVars);

				std::vector<std::vector<int>> allPossibleSplits = collectAllPossibleSplits(a, elementNames, pMax);
				std::set<std::string> strSplits;

				for (unsigned int i = 0; i < allPossibleSplits.size(); ++i) {
					/* check feasibility */

					strSplits.emplace(fromSplitToLengConstraint(a, elementNames, allPossibleSplits[i], lhs_str, rhs_str));
					// strSplits.emplace(fromSplitToSMT(a, elementNames, allPossibleSplits[i], connectedVariables, newVars)); /* without Z3 array */
					// assert(strSplits[strSplits.size() - 1].length() > 5); /* not empty string */
				}

				if (strSplits.size() > 0)
					result = result + " " + orConstraint(strSplits);
				else
					return "";
			}
		}

		else {
			/* lhs is not a const string */

			int minLength = 0;
			for (unsigned int i = 0 ; i < elementNames.size() - 1; ++i)
				if (elementNames[i].second == -1 &&
						elementNames[i + 1].second == -2) {/* const */
					minLength += elementNames[i].first.length();
				}
			if (minLength > pMax) {
				return "";
			}

			/* do not need AND */
			/* result = sum (length) */
			result = result + "(= " + generateFlatSize(a, lhs_str) + " (+ ";
			for (unsigned int i = 0; i < elementNames.size(); ++i) {
				// TODO: can do it better by replacing const length by a number
				result = result + generateFlatSize(elementNames[i], rhs_str) + " ";
			}

			if (elementNames.size() == 1)
				result = result + " 0";

			result = result + ")) ";

			/* DO NOT care about empty flats or not*/

			/* handle const for connected variables*/
			if (connectedVariables.find(a.first) != connectedVariables.end())
				result = result + unrollConnectedVariable(a, elementNames, lhs_str, rhs_str, connectedVariables, newVars);
		}


		return result;
	}

	std::string generateSMT(int pMax,
			std::string lhs_str, std::string rhs_str,
			std::vector<std::pair<std::string, int>> lhs_elements,
			std::vector<std::pair<std::string, int>> rhs_elements,
			std::set<std::string> connectedVariables,
			std::map<std::string, int> &newVars){

		std::vector<std::string> result_element;

		bool checkLeft[lhs_elements.size()];
		bool checkRight[rhs_elements.size()];
		memset(checkLeft, 0, sizeof checkLeft);
		memset(checkRight, 0, sizeof checkRight);

		/* do the left */
		for (unsigned int i = 0; i < left_arr.size(); ++i)
			if (left_arr[i] == SUMFLAT) { /* a = bx + cy */

				checkLeft[i] = true;

				std::vector<std::pair<std::string, int>> elements;
				for (unsigned int j = 0; j < right_arr.size(); ++j)
					if (right_arr[j] == (int)i) {
						elements.push_back(rhs_elements[j]);
						checkRight[j] = true;
					}

				std::string tmp = generateConstraint02(lhs_elements[i], elements, lhs_str, rhs_str, pMax, connectedVariables, newVars);

				if (tmp.length() == 0) { /* cannot happen due to const */
//					printf("%d 02 because of lhs[%d]\n", __LINE__, i);
					return "";
				}
				result_element.push_back(tmp);

			}
			else if (left_arr[i] == EMPTYFLAT) {

				/* empty */
				/* some first flats can be empty */
				if (lhs_elements[i].second == -1) /* head of const */ {
					if ((QCONSTMAX == 2 && i + 1 < lhs_elements.size() && left_arr[i + 1] == EMPTYFLAT && lhs_elements[i].first.length() > 0) ||
							(QCONSTMAX == 1 && lhs_elements[i].first.length() > 0)) /* const string is empty */
						return "";
				}
				checkLeft[i] = true;
				std::string tmp = generateConstraint00(lhs_elements[i], lhs_str, newVars);

				if (tmp.length() == 0) {/* cannot happen due to const */
					return "";
				}
				result_element.push_back(tmp);
			}

		/* do the right */
		for (unsigned int i = 0; i < right_arr.size(); ++i)
			if (right_arr[i] == SUMFLAT) { /* a = bx + cy */
				checkRight[i] = true;

				std::vector<std::pair<std::string, int>> elements;
				for (unsigned int j = 0; j < left_arr.size(); ++j)
					if (left_arr[j] == (int)i) {
						elements.push_back(lhs_elements[j]);
						checkLeft[j] = true;
					}

				std::string tmp = generateConstraint02(rhs_elements[i], elements, rhs_str, lhs_str, pMax, connectedVariables, newVars);
				if (tmp.length() == 0) { /* cannot happen due to const */
//					printf("%d 02 because of rhs[%d]\n", __LINE__, i);
					return "";
				}
				result_element.push_back(tmp);
			}
			else if (right_arr[i] == EMPTYFLAT) {
				/* empty */
				/* some first flats can be empty */
				if (rhs_elements[i].second == -1) /* head of const */ {
					if ((QCONSTMAX == 2 && i + 1 < rhs_elements.size() && right_arr[i + 1] == EMPTYFLAT && rhs_elements[i].first.length() > 0) ||
							(QCONSTMAX == 1 && rhs_elements[i].first.length() > 0))/*const string is empty*/
						return "";
				}
				checkRight[i] = true;
				std::string tmp = generateConstraint00(rhs_elements[i], rhs_str, newVars);
				if (tmp.length() == 0) {/* cannot happen due to const */
					return "";
				}
				result_element.push_back(tmp);
			}

		/* do the rest */
		/* do not need AND */
		std::string constraint01 = "";
		for (unsigned int i = 0 ; i < lhs_elements.size(); ++i)
			if (checkLeft[i] == false) {
				checkLeft[i] = true;
				checkRight[left_arr[i]] = true;

				if (QCONSTMAX == 2 &&
						lhs_elements[i].second == -1 && rhs_elements[left_arr[i]].second == -1 &&
						checkLeft[i + 1] == false &&
						lhs_elements[i + 1].second == -2 && rhs_elements[left_arr[i + 1]].second == -2) /* const = const */{
					if (lhs_elements[i].first.compare(rhs_elements[left_arr[i]].first) == 0) { /* "abc" = "abc" */
						constraint01 = constraint01 +	"(= " + generateFlatSize(lhs_elements[i], lhs_str) + " " + generateFlatSize(rhs_elements[left_arr[i]], rhs_str) + ") " +
								"(= " + generateFlatSize(lhs_elements[i + 1], lhs_str) + " " + generateFlatSize(rhs_elements[left_arr[i + 1]], rhs_str) + ") ";
						checkLeft[i + 1] = true;
						checkRight[left_arr[i + 1]] = true;
						i++;
						// printf("%d constraints01: %s\n", __LINE__, constraint01.c_str());
					}
					else { /* "abc" = "def" */
						// printf("%d CANNOT HAPPEN: %s = %s\n", __LINE__, lhs_elements[i].first.c_str(), rhs_elements[left_arr[i]].first.c_str());
						return "";
					}
				}
				else {
					std::string tmp = generateConstraint01(lhs_str, rhs_str, lhs_elements[i], (std::pair<std::string, int>)rhs_elements[left_arr[i]], pMax, connectedVariables, newVars);
					if (tmp.length() == 0) { /* cannot happen due to const */
						return "";
					}
					constraint01 = constraint01 + tmp + " ";
				}
			}

		if (constraint01.length() > 5) {
			result_element.push_back(constraint01);

		}

		for (unsigned int i = 0 ; i < rhs_elements.size(); ++i)
			if (checkRight[i] == false)
				assert (false);

		/* sum up */
		std::string result = "(and \n";
		for (unsigned int i = 0 ; i < result_element.size(); ++i)
			result = result + result_element[i] + "\n";
		result = result + ")";

		return result;
	}

	/*
	 * we do not allow empty flats in the middle
	 */
	bool isPossibleArrangement(){
		if (left_arr[left_arr.size() -1] == EMPTYFLAT &&
				right_arr[right_arr.size() -1] == EMPTYFLAT)
			return false;
		/* not allow empty flats in the middle */
		unsigned int startPos = 0;
		unsigned int endPos = left_arr.size() - 1;
		/* check lhs */
		for (startPos = 0; startPos < left_arr.size(); ++startPos)
			if (left_arr[startPos] != EMPTYFLAT)
				break;
		for (endPos = left_arr.size() - 1; endPos >= 0; --endPos)
			if (left_arr[endPos] != EMPTYFLAT)
				break;
		for (unsigned int i = startPos; i < endPos; ++i)
			if (left_arr[i] == EMPTYFLAT) {
				// printArrangement("ERRORR");
				return false;
			}

		/* check rhs */
		for (startPos = 0; startPos < right_arr.size(); ++startPos)
			if (right_arr[startPos] != EMPTYFLAT)
				break;
		for (endPos = right_arr.size() - 1; endPos >= 0; --endPos)
			if (right_arr[endPos] != EMPTYFLAT)
				break;
		for (unsigned int i = startPos; i < endPos; ++i)
			if (right_arr[i] == EMPTYFLAT) {
				// printArrangement("ERRORR");
				return false;
			}
		return true;
	}

	/*
	 * Pre-Condition: x_i == 0 --> x_i+1 == 0
	 */
	bool isPossibleArrangement(
			std::vector<std::pair<std::string, int>> lhs_elements,
			std::vector<std::pair<std::string, int>> rhs_elements){
		/* bla bla */
		for (unsigned int i = 0; i < left_arr.size(); ++i)
			if (left_arr[i] != -1){
				for (int j = i - 1; j >= 0; --j){
					if (lhs_elements[j].second < lhs_elements[i].second) { /* same var */
						if (left_arr[j] == -1)
							return false;
					}
					else
						break;
				}
			}
		for (unsigned int i = 0; i < right_arr.size(); ++i)
			if (right_arr[i] != -1){
				for (int j = i - 1; j >= 0; --j){
					if (rhs_elements[j].second < rhs_elements[i].second) { /* same var */
						if (right_arr[j] == -1)
							return false;
					}
					else
						break;
				}
			}
		return true;
	}


	void printArrangement(std::string msg = ""){
		if (msg.length() > 0)
			__debugPrint(logFile, "%s\n", msg.c_str());

		for (unsigned int i = 0; i < left_arr.size(); ++i)
			__debugPrint(logFile, "%*d ", 3, left_arr[i]);
		__debugPrint(logFile, "\n");
		for (unsigned int i = 0; i < right_arr.size(); ++i)
			__debugPrint(logFile, "%*d ", 3, right_arr[i]);
		__debugPrint(logFile, "\n");
	}
};


#endif /* ARRANGEMENT_H_ */
