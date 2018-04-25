/*
 * regex.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef REGEX_H_
#define REGEX_H_

#include "Automaton.h"
#include "RegexState.h"

class RegEx {
public:
	RegEx();
	~RegEx();

	bool Compile(std::string strRegEx);
	bool Match(std::string strText);
	bool MatchAll(std::string strText);
	typedef std::vector<RegExState*> Table;
	typedef Table::reverse_iterator TableReverseIterator;
	typedef Table::iterator TableIterator;
	typedef std::set<RegExState*>::iterator StateIterator;

	Automaton CreateAutomaton(std::string name);

private:
	Table m_NFATable;
	Table m_DFATable;

	std::stack<Table >       m_CharacterClassStack;
	std::stack<char>         m_ExpressionStack;
	std::set<char>           m_InputSet;
	std::string              m_strText;
	std::string              m_PostStrRegEx;
	char*                    m_InfixRegEx;
	char                     m_CurPreProcChar;
	int                      m_nNextStateID;

	bool ConstructThompsonNFA();
	void PushOnCharacterStack(char chInput);
	bool PopTable(Table  &NFATable);
	bool Concatenate();
	bool Closure();
	bool ClosureOptional();
	bool ClosurePlus();
	bool Or();
	bool IsMetaChar(char inputCh);
	bool IsInput(char inputCh);
	bool IsLeftParan(char inputCh);
	bool IsRightParan(char inputCh);
	void EpsilonClosure(std::set<RegExState*> T, std::set<RegExState*> &Res);
	void Move(char chInput, std::set<RegExState*> T, std::set<RegExState*> &Res);
	void ConvertNFAtoDFA();
	void ReduceDFA();
	void CleanUp();

	int CovertToPostfix();
	int PreProcessLiterals();
	int PreProcessClosure();
	int PrePreprocessConcatenation();
	int PreProcessOr();
	std::string PreProcessBracket( std::string strRegEx);
	void MinimizeDFA ();

	void PrintTable(Table &table);

protected:
};


#endif /* REGEX_H_ */
