/*
 * GrmOverApprox.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: diepbp
 */

#include "GrmOverApprox.h"

void printNonTerminal(std::map<std::string, std::vector<std::string>> list, std::string name, std::string endStr) {
	printf("%d %s: \n", __LINE__, name.c_str());
	for (std::map<std::string, std::vector<std::string>>::iterator it = list.begin(); it != list.end(); ++it) {
		printf(" %s: ", it->first.c_str());
		for (unsigned int j = 0 ; j < it->second.size(); ++j)
			printf(" ---%s--- ||", it->second[j].c_str());
		printf("\n");
	}
	printf("\n");
}

/*
 *
 */
void printGraph(std::vector<std::set<int>> graph, std::map<std::string, int> nonTerminal) {
	for (std::map<std::string, int>::iterator it = nonTerminal.begin(); it != nonTerminal.end(); ++it){
		printf("%s (%d): ", it->first.c_str(), it->second);
		for (std::set<int>::iterator itor = graph[it->second].begin(); itor != graph[it->second].end(); ++itor)
			printf("(%d) ", *itor);
		printf("\n");
	}
}

/*
 *
 */
std::vector<std::string> readGrm(std::string inputFile){
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
std::map<std::string, std::string> CFG_parser(std::string inputFile){
	std::map<std::string, std::string> regex;
	std::vector<std::set<int>> graph;
	std::vector<std::string> lines = readGrm(inputFile);
	displayListString(lines, "Input");

	// find nonterminal
	std::map<std::string, std::vector<std::string>> nonTerminalMap;
	std::map<std::string, int> nonTerminal;
	int cnt = 0;
	for (unsigned int i = 0 ; i < lines.size(); ++i){
		std::vector<std::string> tokens = parse_string_language(lines[i], " \n");
		if (nonTerminal.find(tokens[0]) == nonTerminal.end()) {
			nonTerminal[tokens[0]] = cnt++;
			graph.push_back(std::set<int>());
		}

		unsigned int j = 0;
		/* find = */
		for (j = 0; j < lines[i].length(); ++j)
			if (lines[i][j] == '=')
				break;

		if (j >= lines[i].length() - 1) {
			printf("Grammar error at line %d!\n", i);
			return regex;
		}

		if (lines[i][j + 1] != ' ') {
			printf("Grammar error at line %d!\n", i);
			return regex;
		}

		/* find parts */
		std::vector<std::string> components;
		std::string component = "";
		for (unsigned int k = j + 2; k < lines[i].length(); ++k)
			if (lines[i][k] == '|' || lines[i][k] == '\n') {
				/* check component */
				if (component[0] != '$') /* not non-terminal*/ {
					for (unsigned int t = 0; t < component.length(); ++t)
						if (component[t] >= 'A' && component[t] <= 'W') {
							printf("%d %s\n", __LINE__, component.c_str());
							throw std::runtime_error("Do not accept UPPER CHARACTERS in CFG!\n");
						}
				}
				if (component[component.length() - 1] == ' ')
					nonTerminalMap[tokens[0]].push_back(component.substr(0, component.length() - 1));
				else
					nonTerminalMap[tokens[0]].push_back(component);
				component = "";
				if (lines[i][k] == '|' && lines[i][k + 1] != ' ' ) {
					printf("Grammar error at line %d!\n", i);
					throw std::runtime_error("Grammar error!\n");
					return regex;
				}
				else
					k++;
			}
			else {
				component = component + lines[i][k];
			}
	}

	// build graph
	for (unsigned int i = 0 ; i < lines.size(); ++i){
		std::vector<std::string> tokens = parse_string_language(lines[i], " \n");
//		printf("%d %s\n", __LINE__, lines[i].c_str());
		for (unsigned int j = 1 ; j < tokens.size(); ++j) {
			if (tokens[j].length() > 0)
				if (nonTerminal.find(tokens[j]) != nonTerminal.end()) {
					int pos = nonTerminal[tokens[j]];
					graph[nonTerminal[tokens[0]]].insert(pos);
//					printf("%d %s w. %s (%ld)\n", __LINE__, tokens[0].c_str(), tokens[j].c_str(), tokens[j].length());
				}
		}
	}


//	printNonTerminal(nonTerminalMap, "nonTerminalMap", " ");
//	printGraph(graph, nonTerminal);

	std::vector<std::vector<std::string>> components = findStronglyConnectedComponent(graph, nonTerminal);
	std::vector<std::vector<Rule>> automata;
	constructAutomataForStronglyConnectedComponent(components, nonTerminalMap, automata);

	for (unsigned int i = 0; i < automata.size(); ++i)
		expandAutomaton(automata[i], nonTerminal, regex);

	finalUpdate(regex, nonTerminal);
	reformulateRegex(regex);
	return regex;
}

/*
 * Find all reachable nodes from a node
 */
std::vector<int> travelFrom(int start, std::vector<std::set<int>> graph) {
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
std::string mapBack(std::map<std::string, int> nonTerminal, int index) {
	for (std::map<std::string, int>::iterator it = nonTerminal.begin(); it != nonTerminal.end(); ++it)
		if (it->second == index)
			return it->first;
	return "UNKNOWN";
}

/*
 *
 */
std::vector<Rule> rewriteTransition(std::vector<std::string> nonTerminals, std::string lsh, std::vector<std::string> rhs) {
	std::vector<Rule> ret;
	unsigned int pos = 0;
	std::string left = lsh;
	while (pos < rhs.size()){
		if (std::find(nonTerminals.begin(), nonTerminals.end(), rhs[pos]) != nonTerminals.end()) {
			/* nonterminal */
			if (pos != rhs.size() - 1) {
				/* not the last element */
				ret.push_back(Rule(left, "", rhs[pos]));
				left = "__" + rhs[pos];
				pos = pos + 1;
			}
			else {
				/* the last element */
				ret.push_back(Rule(left, "", rhs[pos]));
				ret.push_back(Rule("__" + rhs[pos], "", "__" + lsh));
				break;
			}

		}
		else {
			/* terminal */
			if (pos == rhs.size() - 1) {
				/* the last element */
				ret.push_back(Rule(left, rhs[pos], "__" + lsh));
				break;
			}
			else {
				/* not the last element */
				assert (std::find(nonTerminals.begin(), nonTerminals.end(), rhs[pos + 1]) != nonTerminals.end());
				ret.push_back(Rule(left, rhs[pos], rhs[pos + 1]));
				left = "__" + rhs[pos + 1];
				pos = pos + 2;

			}
		}
	}
	return ret;
}

/*
 *
 */
std::string evalNode(std::vector<Rule> rules, std::string name) {
	std::set<std::string> states;
	for (unsigned int i = 0 ; i < rules.size(); ++i){
		states.insert(rules[i].start);
		states.insert(rules[i].finish);
	}
//	printf("%d evalNode: %s\n", __LINE__, name.c_str());

	std::vector<std::string> nodeList;
	nodeList.insert(nodeList.end(), states.begin(), states.end());

	// change start
	for (unsigned int i = 0 ; i < rules.size(); ++i)
		if (rules[i].start == "__starter__")
			rules[i].finish = name;

//	printf("%d Start\n", __LINE__);
//	for (unsigned int i = 0 ; i < rules.size(); ++i)
//		printf("%s\n", rules[i].toString().c_str());

	while (true) {
		int pos = -1;
		while (pos < (int)nodeList.size()) {
			pos++;
			if (nodeList[pos].compare("__starter__") == 0)
				continue;
			if (nodeList[pos].compare("__epsilon__") == 0)
				continue;
			break;
		}
		if (pos >= (int)nodeList.size())
			break;

		std::string removeNode = nodeList[pos];
		for (std::vector<std::string>::iterator it = nodeList.begin(); it != nodeList.end();)
			if (it->compare(removeNode) == 0) {
				nodeList.erase(it);
				break;
			}
			else
				it++;

		removeANode(rules, removeNode);

//		printf("%d Update: remove %s\n", __LINE__, removeNode.c_str());
//		for (unsigned int i = 0 ; i < rules.size(); ++i)
//			printf("%s\n", rules[i].toString().c_str());
	}

	// construct regex
	std::set<std::string> regex;
	for (unsigned int i = 0 ; i < rules.size(); ++i)
		regex.insert(rules[i].label);

	std::string ret = "";
	for (std::set<std::string>::iterator it = regex.begin(); it != regex.end(); ++it)
		if (ret.length() == 0)
			ret = ret + *it;
		else
			ret = ret + "|" + *it;
//	printf("%d Result: %s\n", __LINE__, ret.c_str());
	return ret;
}

/*
 *
 */
void removeANode(std::vector<Rule> &rules, std::string removeNode) {
	// check itself
	std::string itself = "";
	for (unsigned int i = 0 ; i < rules.size(); ++i)
		if (rules[i].finish.compare(removeNode) == 0 &&
				rules[i].start.compare(removeNode) == 0) {
			if (itself.length() > 0)
				itself = itself + "|" + rules[i].label;
			else
				itself = itself + rules[i].label;
		}

	// remove all itself-s
	if (itself.length() > 0) {
		if (!(itself.length() > 3 && itself[0] == '(' && itself[itself.length() - 1] == '*' && itself[itself.length() - 2] == ')'))
			itself = "(" + itself + ")*";

		for (std::vector<Rule>::iterator it = rules.begin(); it != rules.end();)
			if (it->finish.compare(removeNode) == 0 &&
					it->start.compare(removeNode) == 0)
				rules.erase(it);
			else
				it++;
	}

	std::vector<Rule> in;
	for (unsigned int i = 0 ; i < rules.size(); ++i)
		if (rules[i].finish.compare(removeNode) == 0)
			in.push_back(rules[i]);

	std::vector<Rule> out;
	for (unsigned int i = 0 ; i < rules.size(); ++i)
		if (rules[i].start.compare(removeNode) == 0)
			out.push_back(rules[i]);

	for (unsigned int i = 0 ; i < in.size(); ++i)
		for (unsigned int j = 0; j < out.size(); ++j)
			rules.push_back(Rule(in[i].start, in[i].label + itself + out[j].label, out[j].finish));

	// remove
	for (std::vector<Rule>::iterator it = rules.begin(); it != rules.end();)
		if (it->finish.compare(removeNode) == 0 ||
				it->start.compare(removeNode) == 0)
			rules.erase(it);
		else
			it++;

	// remove duplicate
	std::vector<Rule> newRules;
	for (unsigned int i = 0; i < rules.size(); ++i) {
		bool add = true;
		for (unsigned int j = i + 1; j < rules.size(); ++j)
			if (rules[i].finish == rules[j].finish &&
					rules[i].start == rules[j].start &&
					rules[i].label == rules[j].label) {
				add = false;
				break;
			}
		if (add == true)
			newRules.push_back(rules[i]);
	}

	rules.clear();

	// combine
	std::map<std::pair<std::string, std::string>, std::string> transition;
	for (unsigned int i = 0; i < newRules.size(); ++i){
		std::pair<std::string, std::string> tmp = std::make_pair(newRules[i].start, newRules[i].finish);
		if (transition.find(tmp) == transition.end() ||
				transition[tmp].length() == 0) {
			if (newRules[i].label.length() > 0)
				transition[tmp] = newRules[i].label;
			else
				transition[tmp] = "";
		}
		else if (newRules[i].label.length() > 0) {
			if (transition[tmp][0] == '(' && transition[tmp][transition[tmp].length() - 1] == ')')
				transition[tmp] = transition[tmp] +	"|(" + newRules[i].label + ")";
			else
				transition[tmp] = "(" + transition[tmp] +	")|(" + newRules[i].label + ")";
		}
	}

	for (std::map<std::pair<std::string, std::string>, std::string>::iterator it = transition.begin(); it != transition.end(); ++it) {
		rules.push_back(Rule(it->first.first, it->second, it->first.second));
	}
}

/*
 * Step 3: find all strongly connected components
 */
std::vector<std::vector<std::string>> findStronglyConnectedComponent(
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
			// find all memebers of its component
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
 * Step 4: construct automaton for each component
 */
void constructAutomataForStronglyConnectedComponent(
		std::vector<std::vector<std::string>> components,
		std::map<std::string, std::vector<std::string>> nonTerminalMap,
		std::vector<std::vector<Rule>> &automata){
	//
	for (unsigned int i = 0 ; i < components.size(); ++i) {
//		displayListString(components[i], "Component: ");

		std::vector<Rule> rules;
		for (unsigned int j = 0 ; j < components[i].size(); ++j) {
		// rewrite the rule
			for (unsigned int k = 0; k < nonTerminalMap[components[i][j]].size(); ++k) {
				std::string rhs = nonTerminalMap[components[i][j]][k];
//				printf("%d Rewrite: --%s--\n", __LINE__, rhs.c_str());
				std::vector<std::string> tokens = parse_string_language(rhs, " \n");

				// merge all terminals
				std::vector<std::string> newTokens;
				std::string terminal = "";
				std::string currentToken = "";
				for (unsigned int t = 0 ; t < tokens.size(); ++t) {
					if (std::find(components[i].begin(), components[i].end(), tokens[t]) == components[i].end()) {
						// terminal
						terminal = terminal + tokens[t] + " ";
					}
					else {
						if (terminal.length() > 0) {
							if (terminal[terminal.length() - 1] == ' ')
								terminal = terminal.substr(0, terminal.length() - 1);
							if (terminal[0] != '$' && rhs[0] == ' ' && rhs[rhs.length() - 1] == ' ')
								terminal = " "  + terminal + " ";
							newTokens.push_back(terminal);

							terminal = "";
						}
						newTokens.push_back(tokens[t]);
					}
				}

				if (terminal[terminal.length() - 1] == ' ')
					terminal = terminal.substr(0, terminal.length() - 1);
				if (terminal.length() > 0) {
					if (terminal[0] != '$' && rhs[0] == ' ' && rhs[rhs.length() - 1] == ' ')
						terminal = " "  + terminal + " ";
					newTokens.push_back(terminal);
				}

				// rewrite the rule
				std::vector<Rule> tmp_rules = rewriteTransition(components[i], components[i][j], newTokens);
				rules.insert(rules.end(), tmp_rules.begin(), tmp_rules.end());

//				printf("%d Result \n", __LINE__);
//				for (unsigned int t = 0; t < tmp_rules.size(); ++t)
//					printf("%d %s\n", __LINE__, tmp_rules[t].toString().c_str());
			}
//			printf("%d\n", __LINE__);

		}
		for (unsigned int j = 0; j < components[i].size(); ++j)
			rules.push_back(Rule("__" + components[i][j], "", "__epsilon__"));
		rules.push_back(Rule("__starter__", "", components[i][0]));
//		for (unsigned int t = 0; t < rules.size(); ++t)
//			printf("%d %s\n", __LINE__, rules[t].toString().c_str());

		automata.push_back(rules);
	}


//	printf("%d FINISH\n", __LINE__);
}

/*
 * Step 5:
 */
bool expandAutomaton(
		std::vector<Rule> rules,
		std::map<std::string, int> nonTerminal,
		std::map<std::string, std::string> &regex){
	std::set<std::string> states;
	for (unsigned int i = 0 ; i < rules.size(); ++i){
		states.insert(rules[i].start);
		states.insert(rules[i].finish);
	}

	std::vector<std::string> nodeList;
	nodeList.insert(nodeList.end(), states.begin(), states.end());
	for (unsigned int i = 0; i < nodeList.size(); ++i)
		if (nodeList[i].length() <= 2 ||
				!(nodeList[i][0] == '_' && nodeList[i][1] == '_')) {
			regex[nodeList[i]] = evalNode(rules, nodeList[i]);
		}
	return true;
}

/*
 * Step 6:
 */
void finalUpdate(
		std::map<std::string, std::string> &regex,
		std::map<std::string, int> nonTerminal){
	bool updating = true;
	while (updating) {
		updating = false;
		for (std::map<std::string, std::string>::iterator it = regex.begin(); it != regex.end(); ++it) {
			std::string varRegex = it->second;
			for (std::map<std::string, int>::iterator it = nonTerminal.begin(); it != nonTerminal.end(); ++it) {
				std::string nonter = it->first;
				std::size_t found = varRegex.find(nonter);
				while (found != std::string::npos) {
//					printf("%d before %s (%s: %s)\n", __LINE__, varRegex.c_str(), nonter.c_str(), regex[nonter].c_str());
					varRegex.replace(found, nonter.length(), "(" + regex[nonter] + ")");
//					printf("%d after %s\n", __LINE__, varRegex.c_str());
					found = varRegex.find(nonter);
					updating = true;
				}
			}
			regex[it->first] = varRegex;
//			printf("%d %s: %s\n", __LINE__, it->first.c_str(), regex[it->first].c_str());
		}
	}
}

/**
 * Step 7
 */
void reformulateRegex(std::map<std::string, std::string> &regex) {
	for (std::map<std::string, std::string>::iterator it = regex.begin(); it != regex.end(); ++it) {
		std::string varRegex = it->second;
		for (unsigned int i = 0 ; i < varRegex.length(); ++i)
			if (varRegex[i] == '|')
				varRegex[i] = '~';
		std::vector<std::string> tokens = parse_string_language(varRegex, " ");

		std::string sum = "";
		for (unsigned int j = 0; j < tokens.size(); ++j) {
			if (j == 0)
				sum = tokens[j];
			else {
				sum = sum + " " + tokens[j];
			}
		}

//		printf("%d %s: %s\n", __LINE__, it->first.c_str(), sum.c_str());
		regex[it->first] = varRegex;
	}
}
