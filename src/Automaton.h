/*
 * Automaton.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef AUTOMATON_H_
#define AUTOMATON_H_

#include "z3utils.h"
#include "Transition.h"


#define UNKNOWN_AUTOMATON "uNkNoWn"
#define LABELN				256
#define SIZEN					2000
struct Automaton {
	std::string name;
	std::vector<int> states;
	std::vector<Transition> transitions;
	std::vector<int> labels;
	std::vector<int> initStates;
	std::vector<int> acceptStates;

	std::map<int, std::vector<Transition>> transitionMap;

	fst::StdVectorFst fst;

	std::string constValue = "";
	std::string frame = "";
	bool isGeneric = false;

	Automaton(){
		name = UNKNOWN_AUTOMATON;
	}

	Automaton& operator = (const Automaton& obj){
		name = obj.name;
		states = obj.states;
		transitionMap = obj.transitionMap;
		transitions = obj.transitions;
		labels = obj.labels;
		initStates = obj.initStates;
		acceptStates = obj.acceptStates;
		fst = obj.fst;
		constValue = obj.constValue;
		isGeneric = obj.isGeneric;
		return *this;
	}

	Automaton(std::string _name): name(_name){}

	Automaton(std::string _name,
						std::vector<int> _states,
						std::vector<Transition> _transitions,
						std::vector<int> _labels,
						std::vector<int> _initStates,
						std::vector<int> _acceptStates): name(_name), states(_states), transitions(_transitions), labels(_labels), initStates(_initStates), acceptStates(_acceptStates)
	{
		assert(initStates.size() == 1);
		fst = automatonToFst();

		for (unsigned int i = 0; i < transitions.size(); ++i)
			transitionMap[transitions[i].out].push_back(transitions[i]);
	}

	Z3_ast CalculateParikhImage(Z3_theory t);

	void setGeneric(bool value);
	bool getGeneric();
	bool isError();
	bool isUnknown();
	bool isEqual(Automaton automaton);

	Automaton Intersect(Automaton automaton);

	Automaton Intersect(std::string name, Automaton automaton);

	Automaton Concat(std::string name, Automaton automaton);

	Automaton Concat(Automaton automaton);

	Automaton fstToAutomaton(std::string _name, fst::StdVectorFst tmpRet);

	fst::StdVectorFst automatonToFst();

	/*
	 * Find all vertices that can be reached from init and can go to accept
	 */
	std::vector<int> findConnectedCompnent(int init, std::map<int, std::vector<Transition> > outList, std::map<int, std::vector<Transition> > inList, int accept, int MaxState);
	std::string calculateParikh(std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, int acceptingState);
	Z3_ast calculateParikh(Z3_theory t, std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, int acceptingState);

	Z3_ast createEdgeConstraints(Z3_theory t);

	std::string createLengthConstraints();
	Z3_ast createLengthConstraints(Z3_theory t, Z3_ast lenNode);

	std::string createVarLen();

	std::string createVarChar(int label);

	std::string calculateParikh_NotConnected(std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, std::vector<int> unConnected);
	Z3_ast calculateParikh_NotConnected(Z3_theory t, std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, std::vector<int> unConnected);


	/*
	 * Find all vertices that can be reached from the init
	 */
	std::vector<int> findConnectedComponent_init(int init, std::map<int, std::vector<Transition> > outList, int MaxState);
	/*
	 * Find all vertices that can be reached from the init
	 */
	std::vector<int> findConnectedComponent_accept(int accept, std::map<int, std::vector<Transition> > inList, int MaxState);

	std::vector<std::string> transitionsToString(std::vector<Transition> v);

	std::string getFrame();
	void DFS_Frame(int pos, std::string currentStr, bool &stop);

	std::set<int> collectFirstChar();
	std::set<int> collectLastChar();
	bool match(std::string str);
	bool fitParikhImg(std::string str);
	void DFS_Match(
			int pos,
			int charPos,
			std::string destination,
			bool& matched,
			int components
			);


	std::set<std::string> createStringUpToLength(int length);
	void DFS_Upto(int pos, int length, std::string currentStr, std::set<std::string> &ret);

	std::set<std::string> createStringFixedLength(int length);
	void DFS_fixed(int pos, int length, std::string currentStr, std::set<std::string> &ret);

	std::set<std::string> createStringWithLengthRange(int lengthMin, int lengthMax);
	void DFS_LengthRange(int pos, int lengthMin, int lengthMax, std::string currentStr, std::set<std::string> &ret, int components);


	bool isConst();
	void BFS_const(int& cnt);
	bool reachFinalState(int state);

	std::string getConst();

	std::string toString_to(int from, std::vector<int> v);
	std::string toString_from(int to, std::vector<int> v);

	std::string toString(bool printTransition = false);

	void writeFst(std::string name);
};



#endif /* AUTOMATON_H_ */
