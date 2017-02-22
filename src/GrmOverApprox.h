/*
 * GrmOverApprox.h
 *
 *  Created on: Feb 15, 2017
 *      Author: diepbp
 */

#ifndef GRMOVERAPPROX_H_
#define GRMOVERAPPROX_H_


#include "utils.h"

struct Rule{
	std::string start;
	std::string label;
	std::string finish;

	Rule(std::string _start, std::string _label, std::string _finish) : start(_start), label(_label), finish(_finish){}
	Rule(){}

	std::string toString(){
		if (label.length() > 0)
			return start + " -> " + label + " + " + finish;
		else
			return start + " -> " + finish;
	}
};

/*
 *
 */
void printNonTerminal(std::map<std::string, std::vector<std::string>> list, std::string name, std::string endStr);


/*
 *
 */
void printGraph(std::vector<std::set<int>> graph, std::map<std::string, int> nonTerminal);

std::vector<std::string> readGrm(std::string inputFile);

std::map<std::string, std::string> CFG_parser(std::string inputFile);

std::vector<int> travelFrom(int start, std::vector<std::set<int>> graph);

std::string mapBack(std::map<std::string, int> nonTerminal, int index);

/*
 *
 */
std::vector<Rule> rewriteTransition(std::vector<std::string> nonTerminals, std::string lsh, std::vector<std::string> rhs);

/*
 *
 */
std::string evalNode(std::vector<Rule> rules, std::string name);

/*
 *
 */
void removeANode(std::vector<Rule> &rules, std::string removeNode);

/*
 * Step 3: find all strongly connected components
 */
std::vector<std::vector<std::string>> findStronglyConnectedComponent(
		std::vector<std::set<int>> graph,
		std::map<std::string, int> nonTerminal);

/*
 * Step 4: construct automaton for each component
 */
void constructAutomataForStronglyConnectedComponent(
		std::vector<std::vector<std::string>> components,
		std::map<std::string, std::vector<std::string>> nonTerminalMap,
		std::vector<std::vector<Rule>> &automata);

/*
 * Step 5:
 */
bool expandAutomaton(
		std::vector<Rule> rules,
		std::map<std::string, int> nonTerminal,
		std::map<std::string, std::string> &regex);

/*
 * Step 6:
 */
void finalUpdate(
		std::map<std::string, std::string> &regex,
		std::map<std::string, int> nonTerminal);

/*
 *
 */
void reformulateRegex(std::map<std::string, std::string> &regex);
#endif /* GRMOVERAPPROX_H_ */
