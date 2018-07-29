/*
 * GrmOverApprox.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: diepbp
 */

#include "GrmUnderApprox.h"


void UnderApproxCFG::printNonTerminal(std::map<std::string, std::vector<std::vector<std::string>>> list, std::string name) {
	__debugPrint(logFile, "%d %s: \n", __LINE__, name.c_str());
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = list.begin(); it != list.end(); ++it) {
		__debugPrint(logFile, " %s: ", it->first.c_str());
		for (unsigned int j = 0 ; j < it->second.size(); ++j) {
			__debugPrint(logFile, "\t");
			for (unsigned int k = 0 ; k < it->second[j].size(); ++k)
				__debugPrint(logFile, " ---%s---", it->second[j][k].c_str());
			__debugPrint(logFile, "\n");
		}
		__debugPrint(logFile, "\n");
	}
	__debugPrint(logFile, "\n");
}

/*
 *
 */
void UnderApproxCFG::printGraph(std::vector<std::set<int>> graph, std::map<std::string, int> nonTerminal) {
	for (std::map<std::string, int>::iterator it = nonTerminal.begin(); it != nonTerminal.end(); ++it){
		__debugPrint(logFile, "%s (%d): ", it->first.c_str(), it->second);
		for (std::set<int>::iterator itor = graph[it->second].begin(); itor != graph[it->second].end(); ++itor)
			__debugPrint(logFile, "(%d) ", *itor);
		__debugPrint(logFile, "\n");
	}
}

/*
 *
 */
std::vector<std::string> UnderApproxCFG::readGrm(std::string inputFile){
	FILE* in = fopen(inputFile.c_str(), "r");
	if (!in)
		throw std::runtime_error("Cannot open input file!");
	std::vector<std::string> lines;
	char buffer[1000];
	while (!feof(in)){
		if (fgets(buffer, 1000, in) != NULL){
			lines.push_back(buffer);
		}
	}
	pclose(in);
	return lines;
}

/*
 *
 */
std::map<std::string, std::vector<std::string>> UnderApproxCFG::underapprox_CFG(std::string inputFile){
	const int SIZE_UNROLL = 2;
	std::vector<std::set<int>> graph;
	std::vector<std::string> lines = readGrm(inputFile);
	TokenParser parser("GRM_token_automata.dat");
	displayListString(lines, "Input");

	// find nonterminal
	std::map<std::string, std::vector<std::vector<std::string>>> nonTerminalMap;
	std::map<std::string, int> nonTerminal;
	int cnt = 0;
	for (unsigned int i = 0 ; i < lines.size(); ++i){
		std::vector<TokenElement> components = parser.tokenHandler(lines[i], 0);

		if (components[0].type.compare("nonterminal") != 0 || components[1].type.compare("equal_operator") != 0)
			throw std::runtime_error("Grammar error.\n");

		/* init */
		if (nonTerminal.find(components[0].content) == nonTerminal.end()) {
			nonTerminal[components[0].content] = cnt++;
			graph.push_back(std::set<int>());
		}

		/* find parts */
		std::vector<std::string> subPart;
		for (unsigned int j = 2; j < components.size(); ++j) {
			if (components[j].type.compare("or_operator") == 0) {
				nonTerminalMap[components[0].content].push_back(subPart);
				subPart.clear();
			}
			else
				subPart.push_back(components[j].content);

		}

		if (subPart.size() > 0)
			nonTerminalMap[components[0].content].push_back(subPart);
	}

	// build graph
	for (unsigned int i = 0 ; i < lines.size(); ++i){
		std::vector<TokenElement> components = parser.tokenHandler(lines[i], 0);
		__debugPrint(logFile, "%d --%s--\n", __LINE__, lines[i].c_str());
		for (unsigned int j = 2 ; j < components.size(); ++j) {
			if (components[j].type.compare("nonterminal") == 0) {
				int pos = nonTerminal[components[j].content];
				graph[nonTerminal[components[0].content]].insert(pos);
				__debugPrint(logFile, "%d --%s-- w. --%s--\n", __LINE__, components[0].content.c_str(), components[j].content.c_str());
			}
		}
	}


	printNonTerminal(nonTerminalMap, "nonTerminalMap");
	printGraph(graph, nonTerminal);

	std::vector<std::vector<std::string>> graphComponents = findStronglyConnectedComponent(graph, nonTerminal);

	rewriteCFG(graphComponents, SIZE_UNROLL, nonTerminalMap);
	std::map<std::string, std::vector<std::string>> regex = evalGraph(nonTerminalMap);
	reformulateRegex(regex);
	optimizeRegex(regex);
	return regex;
}

/*
 * Find all reachable nodes from a node
 */
std::vector<int> UnderApproxCFG::travelFrom(int start, std::vector<std::set<int>> graph) {
	std::vector<int> queue;
	bool visited[100];

	memset(visited, false, sizeof visited);
	visited[start] = true;
	queue.push_back(start);

	unsigned int pos = 0;
	while (pos < queue.size()) {
		int node = queue[pos++];
		for (std::set<int>::iterator it = graph[node].begin(); it != graph[node].end(); ++it) {
			if (visited[*it] == false) {
				visited[*it] = true;
				queue.push_back(*it);
			}
		}
	}
	return queue;
}

/*
 * Map from index --> string
 */
std::string UnderApproxCFG::mapBack(std::map<std::string, int> nonTerminal, int index) {
	for (std::map<std::string, int>::iterator it = nonTerminal.begin(); it != nonTerminal.end(); ++it)
		if (it->second == index)
			return it->first;
	return "UNKNOWN";
}

/*
 * checking there exists a cycle on a graph
 * */
bool UnderApproxCFG::hasCycle(std::string start, std::map<std::string, std::vector<std::string>> graph){
	std::vector<std::string> q;
	q.push_back(start);
	unsigned int pos = 0;

	while (pos < q.size()){
		std::string state = q[pos];
		for (unsigned int i = 0; i < graph[state].size(); ++i) {
			if (std::find(q.begin(), q.end(), graph[state][i]) == q.end()) {
				/* not in queue */
				q.push_back(graph[state][i]);
			}
			else
				if (graph[state][i].compare(start) == 0)
					return true;
		}
		pos++;
	}
	return false;
}

/*
 * checking there exists an edge used the vertex on a graph
 * */
bool UnderApproxCFG::nonUsedVertex(std::string vertex, std::map<std::string, std::vector<std::string>> graph){
	for (std::map<std::string, std::vector<std::string>>::iterator it = graph.begin(); it != graph.end(); ++it)
		if (std::find(it->second.begin(), it->second.end(), vertex) != it->second.end())
			return false;
	return true;
}

/*
 *
 */
bool UnderApproxCFG::isNonTerminal(std::string name, std::vector<std::string> nonTerminals){

	if (name[0] == '$' && name.length() > 2) {
		std::string tmp = "";
		if (name[name.length() - 2] == '_') {
			tmp = name.substr(0,name.length() - 2);
		}
		else if (name[name.length() - 3] == '_') {
			tmp = name.substr(0,name.length() - 3);
		}
		else
			return false;

		for (unsigned int i = 0; i < nonTerminals.size(); ++i)
			if (tmp.compare(nonTerminals[i]) == 0)
				return true;
	}

	return false;
}

/*
 *
 */
std::vector<std::string> UnderApproxCFG::replaceRhs_cycle(
		std::string lhs_cycle,
		std::vector<std::string> rhs_cycle,
		std::vector<std::string> nonTerminals,
		std::set<std::string> &usedVertices) {
	for (unsigned int i = 0; i < rhs_cycle.size(); ++i)
		if (UnderApproxCFG::isNonTerminal(rhs_cycle[i], nonTerminals) && rhs_cycle[i].compare(lhs_cycle) != 0 ){
			rhs_cycle[i] = findUnusedVertex(rhs_cycle[i], usedVertices);

			/* mark as used */
			usedVertices.emplace(rhs_cycle[i]);
		}
		else if (rhs_cycle[i][0] == '$' && rhs_cycle[i].compare(lhs_cycle) != 0){
			rhs_cycle[i] = rhs_cycle[i] + "_0_0";
		}
	return rhs_cycle;
}

/*
 *
 */
void UnderApproxCFG::addEdges(
		std::string lhs_cycle,
		std::vector<std::string> rhs_cycle,
		std::vector<std::string> nonTerminals,
		std::map<std::string, std::vector<std::vector<std::string>>> &ret,
		std::set<std::string> &usedVertices){
	bool specialCase_beginning = false;
	bool specialCase_end = false;

	if (rhs_cycle[0].length() > 4) {
		specialCase_beginning = rhs_cycle[0].substr(0, 4).compare("_!!_") == 0;
	}
	if (rhs_cycle[rhs_cycle.size() - 1].length() > 4) {
		specialCase_end = rhs_cycle[rhs_cycle.size() - 1].substr(0, 4).compare("_!!_") == 0;
	}

	assert(!(specialCase_beginning && specialCase_end));

	bool added = false;
	/* check how many copies of are already used */
	for(std::set<std::string>:: iterator it = usedVertices.begin(); it != usedVertices.end(); ++it){

		if (it->substr(0, lhs_cycle.length()).compare(lhs_cycle) == 0) {
			/* check for the special case started by _!!_ */
			if (specialCase_beginning == true)
				rhs_cycle[0] = it->c_str();
			if (specialCase_end == true)
				rhs_cycle[rhs_cycle.size() - 1] = it->c_str();

			std::vector<std::string> tmp = UnderApproxCFG::replaceRhs_cycle(*it, rhs_cycle, nonTerminals, usedVertices);
			ret[*it].push_back(tmp);
			__debugPrint(logFile, "%d adding an edge\n", __LINE__);
			displayListString(tmp, "--");
			added = true;
		}
	}

	/* cannot find any used lhs */

	if (added == false) {
		lhs_cycle = lhs_cycle + "_0";
		if (specialCase_beginning == true) {
			rhs_cycle[0] = lhs_cycle;
		}
		if (specialCase_end == true) {
			rhs_cycle[rhs_cycle.size() - 1] = lhs_cycle;
		}
		__debugPrint(logFile, "%d before adding an edge\n", __LINE__);
		displayListString(rhs_cycle, "");
		std::vector<std::string> tmp = UnderApproxCFG::replaceRhs_cycle(lhs_cycle, rhs_cycle, nonTerminals, usedVertices);
		ret[lhs_cycle].push_back(tmp);
		__debugPrint(logFile, "%d adding an edge\n", __LINE__);
		displayListString(tmp, "--");
		added = true;
	}
}

/*
 *  vertex format: X_0_[0..100]
 */
std::string UnderApproxCFG::findUnusedVertex(std::string rhs_name, std::set<std::string> &usedVertices){
	int maxValue = 0;
	while (maxValue < 100){
		std::string rhs_name_index = rhs_name + "_" + std::to_string(maxValue++);
		if (usedVertices.find(rhs_name_index) == usedVertices.end()){
			return rhs_name_index;
		}

	}
	assert(false);
	return "";
}

/*
 * rewrite transitions to remove cycle
 */
std::map<std::string, std::vector<std::vector<std::string>>> UnderApproxCFG::rewriteCFGTransition(
		std::vector<std::string> nonTerminals,
		std::string lhs,
		std::vector<std::vector<std::string>> all_rhs,
		int cycleNo,
		std::map<std::string, std::vector<std::string>> &usedEdges,
		std::set<std::string> &usedVertices) {

	__debugPrint(logFile, ">> %d Rewrite: %s\n", __LINE__, lhs.c_str());
	std::map<std::string, std::vector<std::vector<std::string>>> ret;
	/* create cycle - 1 copies */

	/* for each cycle, how many copies do we use, stored in usedVertices */
	for (int cycle = 0; cycle < cycleNo; ++cycle) {
		/* create a copy at cycle, */
		std::string lhs_cycle = lhs + "_" + std::to_string(cycle);
		std::map<std::string, int> cycleIndex;
		if (cycle == cycleNo - 1) {
			/* the last cycle: do not use non-terminal symbols */
			bool foundTransition = false;
			for (unsigned int j = 0; j < all_rhs.size(); ++j) {
				bool nonTerminalTransition = true;
				for (unsigned int i = 0 ; i < all_rhs[j].size(); ++i){
					if (std::find(nonTerminals.begin(), nonTerminals.end(), all_rhs[j][i]) != nonTerminals.end()) {
						/* is a non-terminal */
						nonTerminalTransition = false;
						break;
					}
				}
				if (nonTerminalTransition == true){
					/* used this one */
					/* check how many copies of are already used */
					UnderApproxCFG::addEdges(lhs_cycle, all_rhs[j], nonTerminals, ret, usedVertices);
					foundTransition = true;
				}
			}
			if (foundTransition == true)
				continue;
		}

		for (unsigned int j = 0; j < all_rhs.size(); ++j) {
			std::vector<std::string> rhs_cycle;

			bool adding = true;

			for (unsigned int i = 0 ; i < all_rhs[j].size(); ++i)
				if (std::find(nonTerminals.begin(), nonTerminals.end(), all_rhs[j][i]) != nonTerminals.end()) {
					/* nonterminal state */
					std::string rhs_name = "";

					/* X -> a X | X b ---but not--- X -> X X*/
					if (all_rhs[j][i].compare(lhs) == 0 &&
							(i == 0 || i == all_rhs[j].size() - 1) &&
							!(all_rhs[j][0].compare(lhs) == 0 && all_rhs[j][all_rhs[j].size() - 1].compare(lhs) == 0)) {
						/* allow looping --> special case */
						__debugPrint(logFile, "%d special case\n", __LINE__);
						rhs_name = "_!!_" + all_rhs[j][i] + "_" + std::to_string(cycle);
					}

					else if (cycleIndex.find(all_rhs[j][i]) != cycleIndex.end())/* use the same one if used before */ {
						rhs_name = all_rhs[j][i] + "_" + std::to_string(cycleIndex[all_rhs[j][i]]);
					}

					else {

						/* find relevant cycle */
						for (int k = cycle; k < cycleNo; ++k) {
							/* if vertex is not used && no cycle --> ok */

							rhs_name = all_rhs[j][i] + "_" + std::to_string(k);

							/* if vertex is not used */
							if (nonUsedVertex(rhs_name, usedEdges)) {
								usedEdges[lhs_cycle].push_back(rhs_name);
								cycleIndex[all_rhs[j][i]] = k;

								/* no cycle */
								if (!hasCycle(lhs_cycle, usedEdges)) {
									break;
								}
								else
									usedEdges[lhs_cycle].pop_back();
							}
							else {
								rhs_name = "";
							}
						}
					}

					/**/
					if (rhs_name.length() > 0) {
						rhs_cycle.push_back(rhs_name);
					}
					else
						adding = false;
				}
				else {
					/* terminal state */
					rhs_cycle.push_back(all_rhs[j][i]);
				}

			if (adding == true) {
				addEdges(lhs_cycle, rhs_cycle, nonTerminals, ret, usedVertices);
			}
			else {
				__debugPrint(logFile, "%d add an empty transitions for \"%s\"\n", __LINE__, lhs_cycle.c_str());
				/* empty transition */
				addEdges(lhs_cycle, {"\"\""}, nonTerminals, ret, usedVertices);
			}
		}
	}
	/* print test */
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = ret.begin(); it != ret.end(); ++it) {
		__debugPrint(logFile, "%d %s: \n", __LINE__, it->first.c_str());
		for (unsigned int i = 0; i < it->second.size(); ++i){
			displayListString(it->second[i], "---");
		}
	}
	__debugPrint(logFile, "\n");

	return ret;
}

/**
 * list of some (non) terminals, each non-terminal has several possible values
 */
std::vector<std::string> UnderApproxCFG::concatStringElements(std::vector<std::vector<std::string>> list) {
	std::vector<std::string> results;
	if (list.size() > 0) {
		assert(list[0].size() > 0);
		results.insert(results.end(), list[0].begin(), list[0].end());

		for (unsigned int i = 1 ; i < list.size(); ++i) {
			assert(list[i].size() > 0);
			std::vector<std::string> tmp;
			tmp.insert(tmp.end(), results.begin(), results.end());

			results.clear();

			for (unsigned int j = 0; j < tmp.size(); ++j)
				for (unsigned int k = 0; k < list[i].size(); ++k)
					results.push_back(tmp[j] + list[i][k]);
		}
	}
	return results;
}

/**
 *
 */
std::vector<std::string> UnderApproxCFG::combineDisjuctionStr(
		std::vector<std::vector<std::vector<std::string>>> list,
		std::vector<int> selectedList,
		int caseType){

	std::vector<std::string> results;
	for (unsigned int i = 0 ; i < selectedList.size(); ++i) {
		std::vector<std::string> tmp = concatStringElements(list[selectedList[i]]);
		if (caseType == 1 || caseType == 2)
			for (unsigned int j = 0; j < tmp.size(); ++j)
				tmp[j] = "(" + tmp[j] + ")*";
		results.insert(results.end(), tmp.begin(), tmp.end());
	}

	return results;
}

/*
 *
 */
std::vector<std::string> UnderApproxCFG::combine_pre_posfix(
		std::vector<std::string> pre,
		std::vector<std::string> mid,
		std::vector<std::string> pos){
	std::vector<std::string> results;
	if (pre.size() == 0)
		pre.push_back("");
	if (mid.size() == 0)
		mid.push_back("");
	if (pos.size() == 0)
		pos.push_back("");
	for (unsigned int i = 0; i < pre.size(); ++i)
		for (unsigned int j = 0; j < mid.size(); ++j)
			for (unsigned int k = 0; k < pos.size(); ++k)
				results.push_back(pre[i] + mid[j] + pos[k]);
	return results;
}

/*
 * eval a node in graph
 */
void UnderApproxCFG::evalNode(
		std::map<std::string, std::vector<std::vector<std::string>>> graph,
		std::string node,
		std::map<std::string, std::vector<std::string>> &nodeValues){

	std::vector<std::vector<std::vector<std::string>>> results;
	std::vector<int> oneStar;
	std::vector<int> twoStars;
	std::vector<int> otherwise;

	/* eval the base case which ends by _0, and then broadcast */
	if (node.substr(node.length() - 2).compare("_0") != 0) {
		int pos = 0;
		for (pos = (int)node.length() - 1; pos >=0; --pos){
			if (node[pos] == '_')
				break;
		}

		std::string tmp = node.substr(0, pos) + "_0";

		__debugPrint(logFile, "%d Eval %s instead of %s\n", __LINE__, tmp.c_str(), node.c_str());
		if (nodeValues.find(tmp) == nodeValues.end()) {
			evalNode(graph, tmp, nodeValues);
		}

		nodeValues[node] = nodeValues[tmp];
		return;
	}

	/* eval all elements that construct a node */
	for (unsigned int i = 0; i < graph[node].size(); ++i) {
		assert(graph[node].size() > 0);
		std::vector<std::vector<std::string>> result;
		/* normal case */
		for (unsigned int j = 0; j < graph[node][i].size(); ++j) {
			if (graph[node][i][j][0] == '$' && graph[node][i][j].compare(node) != 0) {
				/* non terminal state */
				if (nodeValues.find(graph[node][i][j]) == nodeValues.end()) {
					/* not evaluated */
					evalNode(graph, graph[node][i][j], nodeValues);
				}
				result.push_back(nodeValues[graph[node][i][j]]);
			}
			else if (graph[node][i][j].compare(node) != 0){
				result.push_back({graph[node][i][j]});
			}
		}

		/* special case to calculate the node itself */
		int caseType = 0;
		for (unsigned int j = 0; j < graph[node][i].size(); ++j) {
			if (graph[node][i][j].compare(node) == 0) {
				assert(j == 0 || j == graph[node][i].size() - 1);
				if (j == 0) {
					caseType = 1;
				}
				else {
					caseType = 2;
				}
			}
		}

		results.push_back(result);
		if (caseType == 0)
			otherwise.push_back(results.size() - 1);
		else if (caseType == 1)
			oneStar.push_back(results.size() - 1);
		else if (caseType == 2)
			twoStars.push_back(results.size() - 1);
	}

	/* prefix */
	std::vector<std::string> twoStarStr = combineDisjuctionStr(results, twoStars, 2);

	std::vector<std::string> otherwiseStr = combineDisjuctionStr(results, otherwise, 0);

	/* posfix */
	std::vector<std::string> oneStarStr = combineDisjuctionStr(results, oneStar, 1);


	nodeValues[node] = combine_pre_posfix(twoStarStr, otherwiseStr, oneStarStr);
}

/*
 * eval all nodes in graph
 */
std::map<std::string, std::vector<std::string>> UnderApproxCFG::evalGraph(
		std::map<std::string,
		std::vector<std::vector<std::string>>> graph){
	std::map<std::string, std::vector<std::string>> nodeValues;
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = graph.begin(); it != graph.end(); ++it) {
		assert (it->first.length() >= 2);
		if (it->first.find("_0_") != std::string::npos && !(it->first[0] == '_' && it->first[1] == '_'))
			evalNode(graph, it->first, nodeValues);
	}

	for(std::map<std::string, std::vector<std::string>>::iterator it = nodeValues.begin(); it != nodeValues.end(); ++it) {
		__debugPrint(logFile, "%d %s--> \n", __LINE__, it->first.c_str());
		displayListString(it->second, "");
	}
	return nodeValues;
}

/*
 * Step 3: find all strongly connected components
 */
std::vector<std::vector<std::string>> UnderApproxCFG::findStronglyConnectedComponent(
		std::vector<std::set<int>> graph,
		std::map<std::string, int> nonTerminal) {
	bool relation[100][100];
	memset(relation, 0, sizeof relation);

	for (unsigned int i = 0 ; i < graph.size(); ++i) {
		std::vector<int> visited = travelFrom(i, graph);
		for (unsigned int j = 0; j < visited.size(); ++j)
			relation[i][visited[j]] = true;
	}

	int stronglyComponents[100];
	for (unsigned int i = 0 ; i < graph.size(); ++i)
		stronglyComponents[i] = i;

	for (unsigned int i = 0 ; i < graph.size(); ++i)
		for (unsigned int j = i+1; j < graph.size(); ++j)
			if (relation[i][j] == true && relation[j][i] == true) {
				stronglyComponents[i] = stronglyComponents[i] > stronglyComponents[j] ? stronglyComponents[j] : stronglyComponents[i];
				stronglyComponents[j] = stronglyComponents[i];
			}

//	printf("%d Strongly Connected Component\n", __LINE__);
//	for (unsigned int i = 0; i < graph.size(); ++i)
//		printf("%d %d: %d\n", __LINE__, i, stronglyComponents[i]);

	// mapping
	bool check[100];
	memset(check, false, sizeof check);
	std::vector<std::vector<std::string>> components;
	for (int i = 0 ; i < (int)nonTerminal.size(); ++i)
		if (check[i] == false) {
			// find all members of its component
			std::vector<std::string> component;
			component.push_back(mapBack(nonTerminal, i));

			for (unsigned int j = i + 1; j < nonTerminal.size(); ++j)
				if (stronglyComponents[j] == stronglyComponents[i]) {
					component.push_back(mapBack(nonTerminal, j));
					check[j] = true;
				}

			components.push_back(component);
		}

	return components;
}

/*
 * Step 4: rewrite CFG
 */
void UnderApproxCFG::rewriteCFG(
		std::vector<std::vector<std::string>> components,
		int size_unroll,
		std::map<std::string, std::vector<std::vector<std::string>>> &nonTerminalMap){

	std::map<std::string, std::vector<std::vector<std::string>>> newNonTerminalMap;
	std::set<std::string> usedVertices;
	for (unsigned int i = 0 ; i < components.size(); ++i) {

		std::map<std::string, std::vector<std::string>> usedEdges;
		for (unsigned int j = 0 ; j < components[i].size(); ++j) {

			/* rewrite the rule */
			std::map<std::string, std::vector<std::vector<std::string>>> rewrittenTransitions = rewriteCFGTransition(
																										components[i],
																										components[i][j],
																										nonTerminalMap[components[i][j]],
																										size_unroll,
																										usedEdges,
																										usedVertices);

			/* update the map */
			newNonTerminalMap.insert(rewrittenTransitions.begin(), rewrittenTransitions.end());
		}
	}

	nonTerminalMap.clear();
	nonTerminalMap.insert(newNonTerminalMap.begin(), newNonTerminalMap.end());
}

/**
 * Step 7
 */
void UnderApproxCFG::reformulateRegex(std::map<std::string, std::vector<std::string>> &regex) {
	for (std::map<std::string, std::vector<std::string>>::iterator it = regex.begin(); it != regex.end(); ++it) {
		std::set<std::string> newValues;
		for (unsigned int i = 0; i < it->second.size(); ++i) {
			std::string varRegex = it->second[i];
			int state = 0; // 1: " ; 2: ""; 0: otherwise
			std::string constStr = "";
			std::string replaced = "";
			for (unsigned int i = 0 ; i < varRegex.length(); ++i) {
				if (varRegex[i] == '"' && !(i > 0 && varRegex[i - 1] == '\\')) {
					if (state == 0) {
						state = 1;
					}
					else if (state == 1) {
						replaced = replaced + constStr;
						constStr = "";
						state = 0;
					}
				}
				else {
					if (state == 1) {
						if (varRegex[i] == '"') {
							assert(varRegex[i - 1] == '\\');
//							constStr = constStr + varRegex[i - 1] + varRegex[i];
							constStr = constStr + varRegex[i];
						}
						else if (varRegex[i] != '\\')
							constStr = constStr + varRegex[i];
					}
					else if (varRegex[i] == '|')
						replaced = replaced + '~';
					else if (varRegex[i] != ' ')
						replaced = replaced + varRegex[i];
				}
			}
			newValues.emplace(replaced);
		}
		regex[it->first].clear();
		regex[it->first].insert(regex[it->first].end(), newValues.begin(), newValues.end());

	}
}

void UnderApproxCFG::optimizeRegex(std::map<std::string, std::vector<std::string>> &regex){
	/* check two consecutive stars */
	std::map<std::string, std::vector<std::string>> finalRegex;
	for (std::map<std::string, std::vector<std::string>>::iterator it = regex.begin(); it != regex.end(); ++it) {
		std::set<std::string> tmp;
		for (unsigned int i = 0; i < it->second.size(); ++i){
			tmp.emplace(optimizeStringRegex(it->second[i]));
		}
		it->second.clear();
		it->second.insert(it->second.end(), tmp.begin(), tmp.end());

		if (it->first.find("_0_0") != std::string::npos)
			finalRegex[it->first.substr(0, it->first.length() - 4)] = it->second;
	}

	for(std::map<std::string, std::vector<std::string>>::iterator it = finalRegex.begin(); it != finalRegex.end(); ++it) {
		__debugPrint(logFile, "%d %s--> \n", __LINE__, it->first.c_str());
		displayListString(it->second, "");
	}

	/* replace the regex by final regex */
	regex.clear();
	regex.insert(finalRegex.begin(), finalRegex.end());
}

std::string UnderApproxCFG::optimizeStringRegex(std::string str){
	int posStar = -1;
	int posLeftParentheses = -1;
	unsigned int pos = 0;
	while (pos < str.length()){
		if (str[pos] == '*') {
			posStar = pos;
			unsigned int tmpLength = posStar - posLeftParentheses + 1;
			if (tmpLength + pos < str.length()){
				if (str.substr(posLeftParentheses, tmpLength).compare(str.substr(pos + 1, tmpLength)) == 0) {
//					printf("%d before: %s\n", __LINE__, str.c_str());
					str = str.substr(0, pos) + str.substr(pos + tmpLength);
//					printf("%d after: %s\n\n", __LINE__, str.c_str());
				}
			}
		}
		else if (str[pos] == '(')
			posLeftParentheses = pos;
		pos++;
	}
	return str;
}
