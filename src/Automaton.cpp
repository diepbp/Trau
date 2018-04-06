/*
 * Automaton.cpp
 *
 *  Created on: Jun 6, 2016
 *      Author: diepbp
 */

#ifndef AUTOMATON_CPP_
#define AUTOMATON_CPP_

#include "Automaton.h"

Z3_ast Automaton::CalculateParikhImage(Z3_theory t){
#ifdef DEBUGLOG
	__debugPrint(logFile, "%d at %s: Calculate Parikh Image of: %s", __LINE__, __FILE__, name.c_str());
	__debugPrint(logFile, "\n");
#endif
	Z3_context ctx = Z3_theory_get_context(t);
	std::map<int, std::vector<Transition>> inList;
	std::map<int, std::vector<Transition>> outList;

	int maxState = 0;
	for( int i = 0; i < (int)transitions.size(); ++i) {
		inList[transitions[i].in].push_back(transitions[i]);
		outList[transitions[i].out].push_back(transitions[i]);

		maxState = maxState > transitions[i].in ? maxState : transitions[i].in;
		maxState = maxState > transitions[i].out ? maxState : transitions[i].out;

	}

	// find some consistent flow
	std::vector<int> empty;
	std::vector<Z3_ast> allRet;
	for(unsigned int i = 0; i < acceptStates.size(); ++i) {
		std::vector<Z3_ast> tmpRet;
		printf("%d New disjunction\n", __LINE__);

		// find the connected component
		std::vector<int> unConnected = findConnectedCompnent(initStates[0], outList, inList, acceptStates[i], maxState);
		Z3_ast part01 = calculateParikh(t, inList, outList, acceptStates[i]);
		Z3_ast part02 = calculateParikh_NotConnected(t, inList, outList, unConnected);
		std::string ret = "";
		if (part01 != NULL)
			tmpRet.push_back(part01);
		if (part02 != NULL)
			tmpRet.push_back(part02);

		allRet.push_back(mk_and_fromVector(t, tmpRet));
	}

	Z3_ast parikh =  mk_or_fromVector(t, allRet);
//	printZ3Node(t, parikh);

	// length constraints
	Z3_ast ret[2] = {createEdgeConstraints(t), parikh};

	return Z3_mk_and(ctx, 2, ret);


	return mk_or_fromVector(t, allRet);
}
/*
 *
 */
void Automaton::setGeneric(bool value){
	isGeneric = value;
}

/*
 *
 */
bool Automaton::getGeneric(){
	return isGeneric;
}

/*
 *
 */
bool Automaton::isError(){
	if (acceptStates.size() == 0)
		return true;
	if (std::find(initStates.begin(), initStates.end(), -1) != initStates.end())
		return true;
	return false;
}

/*
 *
 */
bool Automaton::isUnknown(){
	if (name.compare(UNKNOWN_AUTOMATON) == 0)
		return true;
	return false;
}

/*
 *
 */
bool Automaton::isEqual(Automaton automaton){
	if (acceptStates.size() != automaton.acceptStates.size())
		return false;

	if (transitions.size() != automaton.transitions.size())
			return false;

	for (unsigned int i = 0; i < acceptStates.size(); ++i)
		if (std::find(automaton.acceptStates.begin(), automaton.acceptStates.end(), acceptStates[i]) == automaton.acceptStates.end())
			return false;

	for (unsigned int i = 0; i < transitions.size(); ++i){
		bool found = false;
		for (unsigned int j = 0; j < automaton.transitions.size(); ++j) {
			if (transitions[i].isEqual(automaton.transitions[j])) {
				found = true;
				break;
			}
		}
		if (found == false)
			return false;
	}
	return true;
}


Automaton Automaton::Intersect(Automaton automaton){
//	automatonToFst();
//	automaton.automatonToFst();

  fst::ArcSort(&fst, fst::StdOLabelCompare());
  fst::ArcSort(&automaton.fst, fst::StdILabelCompare());

	fst::StdVectorFst tmpRet;
	fst::Intersect(fst, automaton.fst, &tmpRet);

	return fstToAutomaton(name + "__" + automaton.name, tmpRet);
}

Automaton Automaton::Intersect(std::string name, Automaton automaton){
	fst::StdVectorFst tmpRet;

  fst::ArcSort(&fst, fst::StdOLabelCompare());
  fst::ArcSort(&automaton.fst, fst::StdILabelCompare());

	fst::Intersect(fst, automaton.fst, &tmpRet);

	return fstToAutomaton(name, tmpRet);
}

Automaton Automaton::Concat(Automaton automaton){
	fst::StdVectorFst tmp = fst;
	fst::Concat(&tmp, automaton.fst);

	return fstToAutomaton(name + "__" + automaton.name, tmp);
}

Automaton Automaton::Concat(std::string _name, Automaton automaton){
	// generic automaton concats generic automaton = UNCHANGED
	if (isGeneric && automaton.isGeneric) {
		name = _name;
		return *this;
	}

	// one of them is empty automaton
	if (labels.size() == 0 && states.size() == 1 && acceptStates.size() == 1 && acceptStates[0] == 0) {
		automaton.name = _name;
		return automaton;
	}
	else if (automaton.labels.size() == 0 && automaton.states.size() == 1 && automaton.acceptStates.size() == 1 && automaton.acceptStates[0] == 0){
		name = _name;
		return *this;
	}


	fst::StdVectorFst tmp = fst;
	fst::Concat(&tmp, automaton.fst);

	return fstToAutomaton(_name, tmp);
}


Automaton Automaton::fstToAutomaton(std::string _name, fst::StdVectorFst tmpRet){
	// convert to Automaton
	std::vector<int> _acceptStates;
	std::vector<int> _states;
	std::vector<int> _labels;
	std::vector<int> _initStates;
	std::vector<Transition> _transitions;

	bool labelAdd[LABELN]; memset(labelAdd, 0, sizeof labelAdd);
	int maxState = 0;

	_initStates.push_back(tmpRet.Start());

	for (fst::StateIterator<fst::StdFst> siter(tmpRet); !siter.Done(); siter.Next()) {
		fst::StdArc::StateId state_id = siter.Value();

		_states.push_back(state_id);
		maxState = maxState > state_id ? maxState : state_id;

		for (fst::ArcIterator<fst::StdFst> aiter(tmpRet, state_id); !aiter.Done(); aiter.Next()) {
			const fst::StdArc &arc = aiter.Value();
			Transition t(state_id, arc.ilabel, arc.nextstate);
			labelAdd[arc.ilabel] = true;
			_transitions.push_back(t);
		}
	}

	for (int i = 0; i < LABELN; ++i)
		if (labelAdd[i] == true)
			_labels.push_back(i);

	for (int i = 0; i <= maxState; ++i) {
		if ((int)tmpRet.Final(i).Value() >= 1)
			_acceptStates.push_back(i);
	}

	Automaton ret(_name, _states, _transitions, _labels, _initStates, _acceptStates);

	return ret;
}

fst::StdVectorFst Automaton::automatonToFst(){
	fst::StdVectorFst fst;

	int maxState = 0;
	for (unsigned int i = 0; i < states.size(); ++i) {
		maxState = maxState > states[i] ? maxState : states[i];
	}

	// add states
	for (int i = 0; i <= maxState; ++i) {
		fst.AddState();
	}

	// set init states
	for (unsigned int i = 0; i < initStates.size(); ++i) {
		fst.SetStart(initStates[i]);
	}

	for (unsigned int i = 0; i < acceptStates.size(); ++i) {
		fst.SetFinal(acceptStates[i], true);
	}

	for (unsigned int i = 0; i < transitions.size(); ++i){
		fst.AddArc(transitions[i].out, fst::StdArc(transitions[i].label, transitions[i].label, true, transitions[i].in));
	}
	return fst;
}

/*
 * Find all vertices that can be reached from init and can go to accept
 */
std::vector<int> Automaton::findConnectedCompnent(int init, std::map<int, std::vector<Transition> > outList, std::map<int, std::vector<Transition> > inList, int accept, int MaxState) {
	std::vector<int> fromInit = findConnectedComponent_init(init, outList, MaxState);
	std::vector<int> toOut = findConnectedComponent_accept(accept, inList, MaxState);

	std::vector<int> tmpRet;
	for(unsigned int i = 0; i < fromInit.size(); ++i)
		if (std::find(toOut.begin(), toOut.end(), fromInit[i]) != toOut.end())
			tmpRet.push_back(fromInit[i]);

	std::vector<int> ret;
	for(int i = 0; i <= MaxState; ++i)
		if (std::find(tmpRet.begin(), tmpRet.end(), i) == tmpRet.end())
			ret.push_back(i);

	printf("UnReached from %d to %d: ", init, accept);
	for(unsigned int i = 0; i < ret.size(); ++i){
		printf("%d ", ret[i]);
	}
	printf("\n");
	return ret;
}

//std::string Automaton::calculateParikh(std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, int acceptingState){
//	std::string ret;
//	// for each consistent flow
//	for( int i = 0; i < (int)states.size(); ++i) {
//		std::string tmp = "";
//
//		std::string left = transitionsToString(inList[states[i]]);
//		if (left.length() == 0)
//			left = "0";
//
//		std::string right = transitionsToString(outList[states[i]]);
//		if (right.length() == 0)
//			right = "0";
//
//		if(states[i] == acceptingState && states[i] == initStates[0]) {
//			tmp = "1 + " + left + " = " + right + " + 1";
//		}
//		else if(states[i] == acceptingState && states[i] != initStates[0]) {
//			tmp =  left + " = " + right + " + 1";
//		}
//		else
//			tmp = states[i] == initStates[0] ?
//					"1 + " + left + " = " + right :
//					left + " = " + right;
//		tmp = "(" + tmp + ")";
//		ret = ret.size() == 0 ? tmp : ret + " && " + tmp;
//	}
//
//	return ret;
//}

Z3_ast Automaton::calculateParikh(Z3_theory t, std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, int acceptingState){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string ret;
	// for each consistent flow
	std::vector<Z3_ast> retAst;
	Z3_ast one = mk_int(ctx, 1);
	for( int i = 0; i < (int)states.size(); ++i) {
		std::string tmp = "";
		std::vector<std::string> left, right;
		Z3_ast leftAst, rightAst, tmpAst;

		left = transitionsToString(inList[states[i]]);
		Z3_ast * items = new Z3_ast[left.size()];
		for (unsigned int j = 0; j < left.size(); j++) {
			items[j] = mk_int_var(ctx, left[j].c_str());
		}
		leftAst = left.size() == 0 ? mk_int(ctx, 0) : Z3_mk_add(ctx, left.size(), items );

		right = transitionsToString(outList[states[i]]);
		items = new Z3_ast[right.size()];
		for (unsigned int j = 0; j < right.size(); j++) {
			items[j] = mk_int_var(ctx, right[j].c_str());
		}
		rightAst = right.size() == 0 ? mk_int(ctx, 0) : Z3_mk_add(ctx, right.size(), items );

		if(states[i] == acceptingState && states[i] == initStates[0]) {
			tmpAst = Z3_mk_eq(ctx, leftAst, rightAst);
		}
		else if(states[i] == acceptingState && states[i] != initStates[0]) {
			Z3_ast rightSide[2] = {rightAst, one};
			tmpAst = Z3_mk_eq(ctx, leftAst, Z3_mk_add(ctx, 2, rightSide));
		}
		else if(states[i] == initStates[0]){
			Z3_ast leftSide[2] = {leftAst, one};
			tmpAst = Z3_mk_eq(ctx, Z3_mk_add(ctx, 2, leftSide), rightAst);
		}
		else
			tmpAst = Z3_mk_eq(ctx, leftAst, rightAst);
		retAst.push_back(tmpAst);
	}

	return mk_and_fromVector(t, retAst);
}

Z3_ast Automaton::createEdgeConstraints(Z3_theory t) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "%d at %s: Create Edge Constraints of: %s", __LINE__, __FILE__, name.c_str());
	__debugPrint(logFile, "\n");
#endif

	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> edge_constraints;
	std::vector<std::string> len_constraints;

	Z3_ast zero = mk_int(ctx, 0);

	for (int j = 0; j < (int)transitions.size(); ++j){
		edge_constraints.push_back(Z3_mk_ge(ctx, mk_int_var(ctx, transitions[j].createVar(name).c_str()), zero));
	}

	return mk_and_fromVector(t, edge_constraints);
}

std::string Automaton::createLengthConstraints() {
#ifdef DEBUGLOG
	__debugPrint(logFile, "%d at %s: Create Length Constraints.\n", __LINE__, __FILE__);
#endif

	std::string char_constraints = "";
	std::string len_constraints = "";
	for (int i = 0; i < (int)labels.size(); ++i) {
		std::string constraint_i = "";
		for (int j = 0; j < (int)transitions.size(); ++j)
			if (transitions[j].label == labels[i]){
				constraint_i = constraint_i.size() == 0 ?
						transitions[j].createVar(name) :
						constraint_i + " + " + transitions[j].createVar(name);
			}

		std::string varChar = createVarChar(labels[i]);

		constraint_i = constraint_i.length() == 0 ?
				"(" + varChar + " = 0" + ")":
				"(" + varChar + " = " + constraint_i + ")";

		char_constraints = char_constraints.length() == 0 ?
				constraint_i :
				char_constraints + " && " + constraint_i;

		len_constraints = len_constraints.length() == 0 ?
				varChar :
				len_constraints + " + " + varChar;
	}

	len_constraints = len_constraints.length() == 0 ?
			createVarLen() + " = 0" :
			createVarLen() + " = " + len_constraints;

	printf("Length constraint: %s\n", len_constraints.c_str());
	printf("Char constraint: %s\n", char_constraints.c_str());
	return "(" + char_constraints + ") && (" + len_constraints + ")";
}

Z3_ast Automaton::createLengthConstraints(Z3_theory t, Z3_ast lenNode) {
#ifdef DEBUGLOG
	__debugPrint(logFile, "%d at %s: Create Length Constraints of: %s", __LINE__, __FILE__, name.c_str());
	__debugPrint(logFile, "\n");
#endif

	Z3_context ctx = Z3_theory_get_context(t);
	std::vector<Z3_ast> char_constraints;
	std::vector<std::string> len_constraints;

	Z3_ast zero = mk_int(ctx, 0);

	for (int i = 0; i < (int)labels.size(); ++i) {
		std::string varChar = createVarChar(labels[i]);
		std::vector<std::string> constraint_i;
		for (int j = 0; j < (int)transitions.size(); ++j)
			if (transitions[j].label == labels[i]){
				constraint_i.push_back(transitions[j].createVar(name));
			}

		if (constraint_i.size() == 0)
			char_constraints.push_back(Z3_mk_eq(ctx, mk_int_var(ctx, varChar.c_str()), zero));
		else {
			Z3_ast * items = new Z3_ast[constraint_i.size()];
			for (unsigned int j = 0; j < constraint_i.size(); j++) {
				items[j] = mk_int_var(ctx, constraint_i[j].c_str());
			}
			char_constraints.push_back(Z3_mk_eq(ctx, mk_int_var(ctx, varChar.c_str()), Z3_mk_add(ctx, constraint_i.size(), items)));
		}
		len_constraints.push_back(varChar);
	}

	if (len_constraints.size() == 0)
		char_constraints.push_back(Z3_mk_eq(ctx, lenNode, zero));
	else {
		Z3_ast * items = new Z3_ast[len_constraints.size()];
		for (unsigned int j = 0; j < len_constraints.size(); j++) {
			items[j] = mk_int_var(ctx, len_constraints[j].c_str());
		}
		char_constraints.push_back(Z3_mk_eq(ctx, lenNode, Z3_mk_add(ctx, len_constraints.size(), items)));
	}
	return mk_and_fromVector(t, char_constraints);
}

std::string Automaton::createVarLen(){
	return name + "_len";
}

std::string Automaton::createVarChar(int label){
	return name + "_c" + std::to_string(label);
}

std::string Automaton::calculateParikh_NotConnected(std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, std::vector<int> unConnected){
	std::string ret;

	// for each consistent flow
	for (unsigned int i = 0; i < unConnected.size(); ++i){
		for (unsigned int j = 0; j < outList[unConnected[i]].size(); ++j){
			ret = ret.size() == 0 ?
					"(0 == " + outList[unConnected[i]][j].createVar(name) + ")" :
					ret + " && " + "(0 == " + outList[unConnected[i]][j].createVar(name) + ")";
		}
		for (unsigned int j = 0; j < inList[unConnected[i]].size(); ++j){
			ret = ret.size() == 0 ?
					"(0 == " + inList[unConnected[i]][j].createVar(name) + ")" :
					ret + " && " + "(0 == " + inList[unConnected[i]][j].createVar(name) + ")";
		}
	}
	return ret;
}

Z3_ast Automaton::calculateParikh_NotConnected(Z3_theory t, std::map<int, std::vector<Transition>> inList, std::map<int, std::vector<Transition>> outList, std::vector<int> unConnected){
	Z3_context ctx = Z3_theory_get_context(t);
	std::string ret;
	Z3_ast zero = mk_int(ctx, 0);
	std::vector<Z3_ast> retAst;
	// for each consistent flow
	for (unsigned int i = 0; i < unConnected.size(); ++i){
		for (unsigned int j = 0; j < outList[unConnected[i]].size(); ++j){
			std::string var = outList[unConnected[i]][j].createVar(name);
			Z3_ast varAst = mk_int_var(ctx, var.c_str());
			retAst.push_back(Z3_mk_eq(ctx, zero, varAst));
		}
		for (unsigned int j = 0; j < inList[unConnected[i]].size(); ++j){
			std::string var = inList[unConnected[i]][j].createVar(name);
			Z3_ast varAst = mk_int_var(ctx, var.c_str());
			retAst.push_back(Z3_mk_eq(ctx, zero, varAst));
		}
	}

	if (retAst.size() != 0)
		return mk_and_fromVector(t, retAst);
	else
		return NULL;
}



/*
 * Find all vertices that can be reached from the init
 */
std::vector<int> Automaton::findConnectedComponent_init(int init, std::map<int, std::vector<Transition> > outList, int MaxState){
	std::vector<int> q;
	std::vector<int> ret;
	bool checker[SIZEN];
	memset(checker, 0, sizeof checker);

	q.push_back(init);
	checker[init] = true;

	unsigned int pos = 0;
	while (pos < q.size()){
		int v = q[pos++];
		for (unsigned int i = 0; i < outList[v].size(); ++i){
			if (checker[outList[v][i].in] == false){
				checker[outList[v][i].in] = true;
				q.push_back(outList[v][i].in);
			}
		}
	}

	for (int i = 0; i <= MaxState; ++i){
		if (checker[i] == true) {
			ret.push_back(i);
		}
	}
	return ret;
}

/*
 * Find all vertices that can be reached from the init
 */
std::vector<int> Automaton::findConnectedComponent_accept(int accept, std::map<int, std::vector<Transition> > inList, int MaxState){
	std::vector<int> q;
	std::vector<int> ret;
	bool checker[SIZEN];
	memset(checker, 0, sizeof checker);

	q.push_back(accept);
	checker[accept] = true;

	unsigned int pos = 0;
	while (pos < q.size()){
		int v = q[pos++];
		for (unsigned int i = 0; i < inList[v].size(); ++i){
			if (checker[inList[v][i].out] == false){
				checker[inList[v][i].out] = true;
				q.push_back(inList[v][i].out);
			}
		}
	}

	for (int i = 0; i <= MaxState; ++i){
		if (checker[i] == true) {
			ret.push_back(i);
		}
	}
	return ret;
}

std::string Automaton::toString_to(int from, std::vector<int> v){
	std::string ret = "";
	for (unsigned int i = 0; i < v.size(); ++i)
		ret = ret.size() == 0 ?
				"e_" + std::to_string(from) + "_" + std::to_string(v[i]) + " " :
				ret + " + e_" + std::to_string(from) + "_" + std::to_string(v[i]) + " ";
	return ret;
}

std::string Automaton::toString_from(int to, std::vector<int> v){
	std::string ret = "";
	for (unsigned int i = 0; i < v.size(); ++i)
		ret = ret.size() == 0 ?
				"e_" + std::to_string(v[i]) + "_" + std::to_string(to) + " " :
				ret + "+ e_" + std::to_string(v[i]) + "_" + std::to_string(to) + " ";
	return ret;
}

std::set<int> Automaton::collectFirstChar() {
	std::set<int> ret;
	for (unsigned int i = 0; i < transitionMap[0].size(); ++i) {
		if (transitionMap[0][i].label != 0)
			ret.insert(transitionMap[0][i].label);
	}

	return ret;
}

std::set<int> Automaton::collectLastChar() {
	std::set<int> ret;
	for (unsigned int i = 0; i < acceptStates.size(); ++i) {
		for (unsigned int j = 0; j < transitions.size(); ++j)
			if (transitions[j].in == acceptStates[i]) {
				if (transitions[j].label != 0)
					ret.insert(transitions[j].label);
			}
	}
	return ret;
}

/*
 * Get the shortest string
 */
std::string Automaton::getFrame(){
	bool stop = false;
	DFS_Frame(0, "", stop);
	return frame;
}

/*
 * Find the shortest string of an automata
 */
void Automaton::DFS_Frame(int pos, std::string currentStr, bool &stop) {
	/* skip */
	frame = "";
	return;
	if (stop)
		return;

	std::vector<int>::iterator it = std::find(acceptStates.begin(), acceptStates.end(), pos);
	if (it != acceptStates.end()) {
		frame = currentStr;
		stop = true;
	}

	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i)
		if (transitionMap[pos][i].label == 0) {
			DFS_Frame(transitionMap[pos][i].in, currentStr, stop);
		}

	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i)
		if (transitionMap[pos][i].label != 0){
			DFS_Frame(transitionMap[pos][i].in, currentStr + (char)transitionMap[pos][i].label, stop);
		}
}

//void Automaton::DFS_Frame_component(int pos, std::string currentStr, std::set<std::string> &ret, bool &stop) {
//	if (stop)
//		return;
//
//	std::vector<int>::iterator it = std::find(acceptStates.begin(), acceptStates.end(), pos);
//	if (it != acceptStates.end()) {
//		ret.insert(currentStr);
//		stop = true;
//	}
//
//	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i)
//		if (transitionMap[pos][i].label == 0) {
//			if (currentStr.length() > 0) {
//				ret.insert(currentStr);
//				currentStr = "";
//			}
//
//			DFS_Frame(transitionMap[pos][i].in, currentStr, ret);
//		}
//
//	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i)
//		if (transitionMap[pos][i].label != 0){
//			DFS_Frame(transitionMap[pos][i].in, currentStr + (char)transitionMap[pos][i].label, ret);
//		}
//}


/*
 * Does a string belong to the language
 */
bool Automaton::match(std::string str){
	if (isUnknown())
		return true;

	bool match = false;

	std::set<int> firstChar = collectFirstChar();
	std::set<int> lastChar = collectLastChar();

	if (str.length() > 0 &&
			std::find(firstChar.begin(), firstChar.end(), str[0]) == firstChar.end() &&
			std::find(firstChar.begin(), firstChar.end(), 0) == firstChar.end() &&
			firstChar.size() > 0) {
		__debugPrint(logFile, "%s --> First character doesn't fit. %d\n", str.c_str(), (int)firstChar.size());
		for (std::set<int>::iterator it = firstChar.begin(); it != firstChar.end(); ++it)
			__debugPrint(logFile, "%c, ", *it);
		__debugPrint(logFile, "\n");
		return false;
	}

	if (str.length() > 0 &&
			std::find(lastChar.begin(), lastChar.end(), str[str.length() - 1]) == lastChar.end() &&
			std::find(lastChar.begin(), lastChar.end(), 0) == lastChar.end() &&
			lastChar.size() > 0) {
		__debugPrint(logFile, "%s --> Last character doesn't fit. %d\n", str.c_str(), (int)lastChar.size());

		for (std::set<int>::iterator it = lastChar.begin(); it != lastChar.end(); ++it)
			__debugPrint(logFile, "%c, ", *it);
		__debugPrint(logFile, "\n");

//		__debugPrint(logFile, "\n %s\n", toString(true).c_str());
		return false;
	}

	bool stop = false;
	DFS_Frame(0, "", stop);

	if (!fitParikhImg(str)) {
		__debugPrint(logFile, "%s --> ParikhImg doesn't fit. %s\n", str.c_str(), frame.c_str());
		return false;
	}

	DFS_Match(0, 0, str, match, 0);
	return match;
}

bool Automaton::fitParikhImg(std::string str){
	std::map<char, int> parikhImg;
	for (unsigned int i = 0 ; i < str.length(); ++i) {
		parikhImg[str[i]]++;
	}

	for (unsigned int i = 0; i < frame.length(); ++i)
		parikhImg[frame[i]]--;

	for (std::map<char, int>::iterator it = parikhImg.begin(); it != parikhImg.end(); ++it) {
		if (it->second < 0)
			return false;
	}
	return true;
}

void Automaton::DFS_Match(
		int pos,
		int charPos,
		std::string destination,
		bool& matched,
		int components) {
//	__debugPrint(logFile, "\nchar pos: %d, pos: %d\n", charPos, pos);
	std::vector<int>::iterator it = std::find(acceptStates.begin(), acceptStates.end(), pos);
	if (it != acceptStates.end() && charPos == (int)destination.length())
		matched = true;

	if (matched == true)
		return;

	if ((int)destination.length() < charPos)
		return;

	if ((int)(frame.length() - components) > (int)(destination.length() - charPos)) {
		__debugPrint(logFile, "%d Out of frame: %d (%d/%ld)\n", __LINE__, charPos, components, frame.length());
		return;
	}

	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i) {
		if (transitionMap[pos][i].label == 0) {
			DFS_Match(transitionMap[pos][i].in, charPos, destination, matched, components);
		}
	}

	bool singleTransition = transitionMap[pos].size() == 1;
	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i) {
		if (transitionMap[pos][i].label == destination[charPos]) {
			if (singleTransition == true)
				DFS_Match(transitionMap[pos][i].in, charPos + 1, destination, matched, components + 1);
			else
				DFS_Match(transitionMap[pos][i].in, charPos + 1, destination, matched, components);
		}
	}

}

std::vector<std::string> Automaton::transitionsToString(std::vector<Transition> v){
	std::vector<std::string> ret;
	for (unsigned int i = 0; i < v.size(); ++i)
		ret.push_back(v[i].createVar(name));
	return ret;
}

std::set<std::string> Automaton::createStringUpToLength(int length) {
	std::set<std::string> ret;
	DFS_Upto(0, length, "", ret);
	return ret;
}

std::set<std::string> Automaton::createStringWithLengthRange(int lengthMin, int lengthMax) {
	std::set<std::string> ret;

	bool stop = false;
	DFS_Frame(0, "", stop);

	DFS_LengthRange(0, lengthMin, lengthMax, "", ret, 0);
	return ret;
}

std::set<std::string> Automaton::createStringFixedLength(int length) {
	std::set<std::string> ret;
	DFS_fixed(0, length, "", ret);
	return ret;
}


void Automaton::DFS_Upto(int pos, int length, std::string currentStr, std::set<std::string> &ret) {
	std::vector<int>::iterator it = std::find(acceptStates.begin(), acceptStates.end(), pos);
	if (it != acceptStates.end() && (int)currentStr.length() <= length)
		ret.insert(currentStr);
	if ((int)currentStr.length() > length)
		return;
	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i) {
		if (transitionMap[pos][i].label == 0)
			DFS_Upto(transitionMap[pos][i].in, length, currentStr, ret);
		else
			DFS_Upto(transitionMap[pos][i].in, length, currentStr + (char)transitionMap[pos][i].label, ret);
	}
}

/*
 * Number of texts is smaller than 1
 * Length should be limited
 * Each node should not be repeated 4
 */
void Automaton::DFS_LengthRange(int pos,
		int lengthMin, int lengthMax,
		std::string currentStr,
		std::set<std::string> &ret,
		int components) {
//	if (ret.size() >= value_count)
	if (ret.size() >= 1)
		return;

	std::vector<int>::iterator it = std::find(acceptStates.begin(), acceptStates.end(), pos);
	if (it != acceptStates.end() && (int)currentStr.length() >= lengthMin && (int)currentStr.length() <= lengthMax) {
		ret.insert(currentStr);
	}

	if ((int)currentStr.length() > lengthMax){
		return;
	}

	__debugPrint(logFile, "%d %s -- %d (%d/%d)\n", __LINE__, currentStr.c_str(), (int)currentStr.length(), components, (int)frame.length());

	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i)
		if (transitionMap[pos][i].label == 0) {
			DFS_LengthRange(transitionMap[pos][i].in, lengthMin, lengthMax, currentStr, ret, components);
		}

	bool singleTransition = transitionMap[pos].size() == 1;
	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i)
		if (transitionMap[pos][i].label != 0){
			if (singleTransition == true)
				DFS_LengthRange(transitionMap[pos][i].in, lengthMin, lengthMax, currentStr + (char)transitionMap[pos][i].label, ret, components + 1);
			else
				DFS_LengthRange(transitionMap[pos][i].in, lengthMin, lengthMax, currentStr + (char)transitionMap[pos][i].label, ret, components);
		}

}

void Automaton::DFS_fixed(int pos, int length, std::string currentStr, std::set<std::string> &ret) {
	std::vector<int>::iterator it = std::find(acceptStates.begin(), acceptStates.end(), pos);
	if (it != acceptStates.end() && (int)currentStr.length() == length)
		ret.insert(currentStr);
	if ((int)currentStr.length() > length)
				return;
	for (unsigned int i = 0; i < transitionMap[pos].size(); ++i) {
		if (transitionMap[pos][i].label == 0)
			DFS_fixed(transitionMap[pos][i].in, length, currentStr, ret);
		else
			DFS_fixed(transitionMap[pos][i].in, length, currentStr + (char)transitionMap[pos][i].label, ret);
	}
}

bool Automaton::isConst(){
	int cnt = 0;

	if (acceptStates.size() > 1 || name.compare(UNKNOWN_AUTOMATON) == 0)
		return false;
	BFS_const(cnt);
	return cnt == 1;
}

/*
 * go to final state without revisiting any nodes
 */
bool Automaton::reachFinalState(int state){
	std::vector<int> q;
	bool checked[SIZEN];
	memset(checked, 0, sizeof checked);

	q.push_back(state);
	checked[state] = true;

	unsigned int pos = 0;
	while(pos < q.size()) {
		int node = q[pos];
		pos++;

		for (unsigned int i = 0; i < transitionMap[node].size(); ++i) {
			if (std::find(acceptStates.begin(), acceptStates.end(), transitionMap[node][i].in) != acceptStates.end() ) {
				return true;
			}
			if (checked[transitionMap[node][i].in] == false) {
				q.push_back(transitionMap[node][i].in);
				checked[transitionMap[node][i].in] = true;
			}
		}
	}
	return false;
}

void Automaton::BFS_const(int& cnt) {
	std::vector<std::pair<std::string, int>> q;
	q.push_back(std::make_pair("", 0));

	bool checked[SIZEN];
	memset(checked, 0, sizeof checked);

	unsigned int pos = 0;
	while(pos < q.size()) {
		int node = q[pos].second;
		std::string value = q[pos].first;
		pos++;

		for (unsigned int i = 0; i < transitionMap[node].size(); ++i) {
			if (std::find(acceptStates.begin(), acceptStates.end(), transitionMap[node][i].in) != acceptStates.end() ) {
				cnt++;
				if (transitionMap[node][i].label != 0)
					constValue = value + (char)transitionMap[node][i].label;
				else
					constValue = value;
				if (cnt >= 2) {
					constValue = "";
					return;
				}
			}

			if (checked[transitionMap[node][i].in] == true) {
				// check if can go to a final state
				if (reachFinalState(transitionMap[node][i].in)) {
					cnt = 2;
					return;
				}
			}
			else
				checked[transitionMap[node][i].in] = true;

			if (transitionMap[node][i].label != 0)
				q.push_back(std::make_pair(value + (char)transitionMap[node][i].label, transitionMap[node][i].in));
			else
				q.push_back(std::make_pair(value, transitionMap[node][i].in));
		}
	}
}

std::string Automaton::getConst(){
	assert(constValue.length() >= 0);
	return constValue;
}

std::string Automaton::toString(bool printTransition){
	std::string ret = "Automaton " + name + ":\n";
	ret = ret + "States: \n";
	for (unsigned int i = 0; i < states.size(); ++i)
		ret += std::to_string(states[i]) + " ";

	ret = ret + "\nLabels: \n";
	for (unsigned int i = 0; i < labels.size(); ++i)
		ret += std::to_string(labels[i]) + " ";

	if (printTransition == true) {
	ret = ret + "\nTransitions: \n";
	for (unsigned int i = 0; i < transitions.size(); ++i)
		ret += "\t" + transitions[i].toString() + "\n";
	}
	ret = ret + "\nInits: \n";
	for (unsigned int i = 0; i < initStates.size(); ++i)
		ret += std::to_string(initStates[i]) + " ";

	ret = ret + "\nAccepts: \n";
	for (unsigned int i = 0; i < acceptStates.size(); ++i)
		ret += std::to_string(acceptStates[i]) + " ";
	return ret;
}

void Automaton::writeFst(std::string name){
	fst.Write(name);
}



#endif /* AUTOMATON_CPP_ */
