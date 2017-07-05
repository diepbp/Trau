/*
 * GrmOverApprox.h
 *
 *  Created on: Feb 15, 2017
 *      Author: diepbp
 */

#ifndef GRMUNDERAPPROX_H_
#define GRMUNDERAPPROX_H_


#include "TokenParser.h"
#include "utils.h"


namespace UnderApproxCFG{
	/*
	 *
	 */
	void printNonTerminal(std::map<std::string, std::vector<std::vector<std::string>>> list, std::string name);


	/*
	 *
	 */
	void printGraph(std::vector<std::set<int>> graph, std::map<std::string, int> nonTerminal);

	std::vector<std::string> readGrm(std::string inputFile);

	std::map<std::string, std::vector<std::string>> underapprox_CFG(std::string inputFile);

	std::vector<int> travelFrom(int start, std::vector<std::set<int>> graph);

	std::string mapBack(std::map<std::string, int> nonTerminal, int index);

	/*
	 * checking there exists a cycle on a graph
	 * */
	bool hasCycle(std::string start, std::map<std::string, std::vector<std::string>> graph);

	bool nonUsedVertex(std::string vertex, std::map<std::string, std::vector<std::string>> graph);

	/*
	 *
	 */
	bool isNonTerminal(std::string name, std::vector<std::string> nonTerminals);

	/*
	 *
	 */
	std::vector<std::string> replaceRhs_cycle(
			std::string lhs_cycle,
			std::vector<std::string> rhs_cycle,
			std::vector<std::string> nonTerminals,
			std::set<std::string> &usedVertices);

	/*
	 *
	 */
	void addEdges(
			std::string lhs_cycle,
			std::vector<std::string> rhs_cycle,
			std::vector<std::string> nonTerminals,
			std::map<std::string, std::vector<std::vector<std::string>>> &ret,
			std::set<std::string> &usedVertices);

	/*
	 *  vertex format: X_0_[0..100]
	 */
	std::string findUnusedVertex(std::string rhs_name, std::set<std::string> &usedVertices);

	/*
	 * rewrite transitions to remove cycle
	 */
	std::map<std::string, std::vector<std::vector<std::string>>> rewriteCFGTransition(
			std::vector<std::string> nonTerminals,
			std::string lhs,
			std::vector<std::vector<std::string>> all_rhs,
			int cycleNo,
			std::map<std::string, std::vector<std::string>> &usedEdges,
			std::set<std::string> &usedVertices);


	/*
	 * Step 3: find all strongly connected components
	 */
	std::vector<std::vector<std::string>> findStronglyConnectedComponent(
			std::vector<std::set<int>> graph,
			std::map<std::string, int> nonTerminal);

	/**
	 * list of some (non) terminals, each non-terminal has several possible values
	 */
	std::vector<std::string> concatStringElements(std::vector<std::vector<std::string>> list);

	/**
	 *
	 */
	std::vector<std::string> combineDisjuctionStr(
			std::vector<std::vector<std::vector<std::string>>> list,
			std::vector<int> selectedList,
			int caseType);

	/*
	 *
	 */
	std::vector<std::string> combine_pre_posfix(
			std::vector<std::string> pre,
			std::vector<std::string> mid,
			std::vector<std::string> pos);

	/*
	 * eval a node in graph
	 */
	void evalNode(
			std::map<std::string, std::vector<std::vector<std::string>>> graph,
			std::string node,
			std::map<std::string, std::vector<std::string>> &nodeValues);

	/*
	 * eval all nodes in graph
	 */
	std::map<std::string, std::vector<std::string>> evalGraph(
			std::map<std::string,
			std::vector<std::vector<std::string>>> graph);

	/*
	 * Step 4: rewrite CFG
	 */
	void rewriteCFG(
			std::vector<std::vector<std::string>> components,
			int size_unroll,
			std::map<std::string, std::vector<std::vector<std::string>>> &nonTerminalMap);
	/*
	 *
	 */
	void reformulateRegex(std::map<std::string, std::vector<std::string>> &regex);

	void optimizeRegex(std::map<std::string, std::vector<std::string>> &regex);

	std::string optimizeStringRegex(std::string str);
}
#endif /* GRMUNDERAPPROX_H_ */
