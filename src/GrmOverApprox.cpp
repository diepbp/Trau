/*
 * GrmOverApprox.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: diepbp
 */

#include "GrmOverApprox.h"

void printNonTerminal(std::map<std::string, std::vector<std::vector<std::string>>> list, std::string name) {
	printf("%d %s: \n", __LINE__, name.c_str());
	for (std::map<std::string, std::vector<std::vector<std::string>>>::iterator it = list.begin(); it != list.end(); ++it) {
		printf(" %s: ", it->first.c_str());
		for (unsigned int j = 0 ; j < it->second.size(); ++j) {
			printf("\t");
			for (unsigned int k = 0 ; k < it->second[j].size(); ++k)
				printf(" ---%s---", it->second[j][k].c_str());
			printf("\n");
		}
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
	GRMParser parser("GRM_token_automata.dat");
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
		printf("%d --%s--\n", __LINE__, lines[i].c_str());
		for (unsigned int j = 2 ; j < components.size(); ++j) {
			if (components[j].type.compare("nonterminal") == 0) {
				int pos = nonTerminal[components[j].content];
				graph[nonTerminal[components[0].content]].insert(pos);
				printf("%d --%s-- w. --%s--\n", __LINE__, components[0].content.c_str(), components[j].content.c_str());
			}
		}
	}


	printNonTerminal(nonTerminalMap, "nonTerminalMap");
	printGraph(graph, nonTerminal);

	std::vector<std::vector<std::string>> graphComponents = findStronglyConnectedComponent(graph, nonTerminal);
	std::vector<std::vector<Rule>> automata;
	constructAutomataForStronglyConnectedComponent(graphComponents, nonTerminalMap, automata);

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
int findRightParenthesis(std::string str){
	int leftParenthesis = 0;
	assert (str[leftParenthesis] == '(');
	int counter = 1;
	for (unsigned int j = leftParenthesis + 1; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
			if (counter == 0){
				return j;
			}
		}
		else if (str[j] == '('){
			counter++;
		}
	}
	return -1;
}

/*
 *
 */
bool hasAlternativeComponents(std::string str){
	std::vector<std::string> result;
	int counter = 0;
	for (unsigned int j = 0; j < str.length(); ++j) {
		if (str[j] == ')'){
			counter--;
		}
		else if (str[j] == '('){
			counter++;
		}
		else if ((str[j] == '|' || str[j] == '~') && counter == 0) {
			return true;
		}
	}
	return false;
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
			bool addParenthesis = true;
//			printf("%d transition: %s\n", __LINE__, transition[tmp].c_str());
			if (transition[tmp][0] == '('){
				int rightParenthesis = findRightParenthesis(transition[tmp]);
				if (rightParenthesis == (int)transition[tmp].length() - 1 || hasAlternativeComponents(transition[tmp]))
					addParenthesis = false;
			}

			if (addParenthesis == false)
				transition[tmp] = transition[tmp] +	"|(" + newRules[i].label + ")";
			else
				transition[tmp] = "(" + transition[tmp] +	")|(" + newRules[i].label + ")";
		}
	}

	for (std::map<std::pair<std::string, std::string>, std::string>::iterator it = transition.begin(); it != transition.end(); ++it) {
		if (hasAlternativeComponents(it->second)) {
			rules.push_back(Rule(it->first.first, "(" + it->second + ")", it->first.second));
		}
		else
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
 * Step 4: construct automaton for each component
 */
void constructAutomataForStronglyConnectedComponent(
		std::vector<std::vector<std::string>> components,
		std::map<std::string, std::vector<std::vector<std::string>>> nonTerminalMap,
		std::vector<std::vector<Rule>> &automata){
	for (unsigned int i = 0 ; i < components.size(); ++i) {

		std::vector<Rule> rules;
		for (unsigned int j = 0 ; j < components[i].size(); ++j) {
		/* rewrite the rule */
			for (unsigned int k = 0; k < nonTerminalMap[components[i][j]].size(); ++k) {
				std::vector<std::string> tokens = nonTerminalMap[components[i][j]][k];

				/* merge all terminals */
				std::vector<std::string> newTokens;
				std::string terminal = "";
				std::string currentToken = "";
				for (unsigned int t = 0 ; t < tokens.size(); ++t) {
					if (std::find(components[i].begin(), components[i].end(), tokens[t]) == components[i].end()) {
						/* terminal */
						terminal = terminal + tokens[t] + " ";
					}
					else {
						if (terminal.length() > 0) {
							if (terminal[terminal.length() - 1] == ' ')
								terminal = terminal.substr(0, terminal.length() - 1);
							newTokens.push_back(terminal);

							terminal = "";
						}
						newTokens.push_back(tokens[t]);
					}
				}

				if (terminal[terminal.length() - 1] == ' ')
					terminal = terminal.substr(0, terminal.length() - 1);
				if (terminal.length() > 0) {
					newTokens.push_back(terminal);
				}

				/* rewrite the rule */
				std::vector<Rule> tmp_rules = rewriteTransition(components[i], components[i][j], newTokens);
				rules.insert(rules.end(), tmp_rules.begin(), tmp_rules.end());

				printf("%d Result \n", __LINE__);
				for (unsigned int t = 0; t < tmp_rules.size(); ++t)
					printf("%d %s\n", __LINE__, tmp_rules[t].toString().c_str());
			}

		}
		for (unsigned int j = 0; j < components[i].size(); ++j)
			rules.push_back(Rule("__" + components[i][j], "", "__epsilon__"));
		rules.push_back(Rule("__starter__", "", components[i][0]));
		for (unsigned int t = 0; t < rules.size(); ++t)
			printf("%d %s\n", __LINE__, rules[t].toString().c_str());

		automata.push_back(rules);
	}
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
		printf("%d value before: %s\n", __LINE__, varRegex.c_str());
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
						constStr = constStr + varRegex[i - 1] + varRegex[i];
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

//		printf("%d value: %s\n", __LINE__, replaced.c_str());
		regex[it->first] = replaced;
	}
}
