/*
 * StringTheory.h
 *
 *  Created on: Jun 1, 2016
 *      Author: diepbp
 */

#ifndef STRINGTHEORY_H_
#define STRINGTHEORY_H_

#include "UnderApprox.h"
#include "regex.h"

#define ARITH 0
//#define PARIKH 1

#define NMAX 1000
#define STR_LEN 4
#define QMAX 2
//#define PMAX 2
#define PRE_LENVAR "!!lEn_"
#define PRE_VALUE "$$vAlUe_"
#define PRE_LANGUAGE "$$lAnG_"
#define UNKNOWN_AUTOMATON "uNkNoWn"

extern std::string inputFile;
extern std::string inputFile_converted;

extern std::map<std::string, int> variables;
extern std::vector<std::vector<int>> graph;
extern std::map<std::string, std::string> ourGrm;

extern int value_count;
extern int sLevel;
// extern std::map<std::string, std::set<char>> charSet;
extern Z3_ast emptyConstStr;

extern const std::string escapeDict[];

extern int numOfFlats;

extern std::map<Z3_ast, std::vector<Z3_ast>> children_Map;

extern std::map<Z3_ast, std::vector<Z3_ast>> concrete_value_Map;
extern std::map<Z3_ast, int> lang_value_Map;
extern std::map<Z3_ast, Z3_ast> final_value_Map;
extern std::map<std::vector<Z3_ast>, int> lang_value_Map1;
extern std::map<std::pair<Z3_ast, int>, Z3_ast> parikh_Node_map;
extern std::set<Z3_ast> inputVarInLen;
// extern std::map<Z3_ast, std::vector<std::string>> eqMap;
extern std::map<std::pair<Z3_ast, int>, Automaton> internalVarMap;
extern std::map<std::pair<Z3_ast, int>, std::string> tmpInternalVarMap;

static std::map<std::string, std::set<char>> charSet;

static std::map<std::pair<Z3_ast, Z3_ast>, int> eqList;
/**
   \brief Data-structure for storing theory specific data.
*/
typedef struct _AutomatonStringData
{
    Z3_sort String;
    Z3_sort Regex;
    Z3_sort Automata;
    Z3_sort Grammar;

    Z3_func_decl Concat;
    Z3_func_decl Length;
    Z3_func_decl SubString;
    Z3_func_decl Indexof;
    Z3_func_decl Indexof2;
    Z3_func_decl StartsWith;
    Z3_func_decl EndsWith;
    Z3_func_decl Contains;
    Z3_func_decl Replace;
    Z3_func_decl LastIndexof;
    Z3_func_decl CharAt;

    Z3_func_decl Str2Reg;
    Z3_func_decl RegexStar;
    Z3_func_decl RegexPlus;
    Z3_func_decl RegexCharRange;
    Z3_func_decl RegexIn;
    Z3_func_decl RegexUnion;
    Z3_func_decl RegexConcat;
    Z3_func_decl Unroll;

    Z3_func_decl AutomataDef;
    Z3_func_decl NonDet_AutomataDef;

    Z3_func_decl Parikh;

    Z3_func_decl GrammarIn;
    Z3_func_decl Str2Grm;
} AutomatonStringData;
/**
   \brief Data-structure for storing theory specific data.
*/
typedef struct _AutomatonStringData AutomatonStringData;



typedef enum
{
  my_Z3_ConstStr,    // 0
  my_Z3_ConstBool,   // 1
  my_Z3_Func,        // 2
  my_Z3_Num,         // 3
  my_Z3_Var,         // 4, boolean, bv, int varables
  my_Z3_Str_Var,     // 5
  my_Z3_Regex_Var,   // 8
  my_Z3_Quantifier,  // 7
  my_Z3_Unknown,     // 9
  my_Z3_Grammar_Var
} T_TheoryType;

std::set<std::string> createFlats(int p, int q, std::set<char> charSet);

void string_theory();

/**
   \brief exit gracefully in case of error.
*/
void exitf(const char* message);

/**
   \brief Simpler error handler.
 */
void error_handler(Z3_context ctx, Z3_error_code e);

/**
   \brief Create a logical context.

   Enable model construction. Other configuration parameters can be passed in the cfg variable.

   Also enable tracing to stderr and register custom error handler.
*/
Z3_context mk_context_custom(Z3_config cfg);

/**
   \brief Create a logical context.

   Enable model construction only.

   Also enable tracing to stderr and register standard error handler.
*/
Z3_context mk_context();

/**
   \brief Create a boolean variable using the given name.
*/
Z3_ast mk_bool_var(Z3_context ctx, const char * name);

Z3_ast mk_str_value(Z3_theory t, char const * str);

Z3_ast mk_str_var(Z3_theory t, char const * name);

/**
   \brief Create the unary function application: <tt>(f x)</tt>.
*/
Z3_ast mk_unary_app(Z3_context ctx, Z3_func_decl f, Z3_ast x);

/**
   \brief Create the binary function application: <tt>(f x y)</tt>.
*/
Z3_ast mk_binary_app(Z3_context ctx, Z3_func_decl f, Z3_ast x, Z3_ast y);

Z3_ast mk_length(Z3_theory t, Z3_ast n);

Z3_ast mk_concat(Z3_theory t, Z3_ast n1, Z3_ast n2, bool &updateCharSet);

Z3_ast Concat(Z3_theory t, Z3_ast n1, Z3_ast n2);

void getNodesInConcat(Z3_theory t, Z3_ast node, std::vector<Z3_ast> & nodeList);
void getAllNodesInConcat(Z3_theory t, Z3_ast node, std::vector<Z3_ast> & nodeList);

/*
 * Find domain of variables
 */
void reduceVariableDomain(Z3_theory t);
void findVariableDomain();
std::set<char> collectChars(std::vector<std::string> constStrs);
void classifyStrings_Variables(std::vector<int> queue, std::vector<std::string> &constStrs, std::vector<std::string> &vars, std::map<std::string, int> variables);
/**
   \brief Check whether the logical context is satisfiable, and compare the result with the expected result.
   If the context is satisfiable, then display the model.
*/
void check(Z3_theory t);

/**
   \brief Simple theory example.
   The theory has a binary function f, and a unit element u.

   The theory axioms are:
   - <tt>forall X. f(X, u) = X</tt>
   - <tt>forall X. f(u, X) = X</tt>
*/
Z3_theory mk_theory(Z3_context ctx);

/**
   \brief Callback: invoked when \c t is deleted.
   This callback can be used to free theory specific data-structures.
*/
void Th_delete(Z3_theory t);

/**
   \brief The reduce_app callback can be used to extend Z3's simplifier.
   The simplifier is used to preprocess formulas.
*/
std::string convertInputTrickyConstStr(std::string inputStr);

Z3_bool cb_reduce_eq(Z3_theory t, Z3_ast s_1, Z3_ast s_2, Z3_ast * r);

Z3_bool Th_reduce_app(Z3_theory t, Z3_func_decl d, unsigned n, Z3_ast const args[], Z3_ast * result);

/**
   \brief Callback: invoked when \c n is finally added to the logical context.
   \c n is an application of the form <tt>g(...)</tt> where \c g is an
   interpreted function symbol of \c t.
*/
void Th_new_app(Z3_theory t, Z3_ast n);

/**
   \brief Callback: invoked when \c n is finally added to the logical context.
   \c n is an expression of sort \c s, where \c s is an interpreted sort of \c t.
*/
void Th_new_elem(Z3_theory t, Z3_ast n);

/**
   \brief Callback: invoked when Z3 starts the search for a satisfying assignment.
*/
void Th_init_search(Z3_theory t);


/**
   \brief Callback: invoked when Z3 creates a case-split (aka backtracking point).
*/
void Th_push(Z3_theory t);

/**
   \brief Callback: invoked when Z3 backtracks a case-split.

   \see Th_push
*/
void Th_pop(Z3_theory t);

/**
   \brief Callback: invoked when the logical context containing \c t is reset.
*/
void Th_reset(Z3_theory t);

/**
   \brief Callback: invoked when Z3 restarts the search for a satisfying assignment.
*/
void Th_restart(Z3_theory t);

/**
   \brief Callback: invoked when <tt>n1 = n2</tt> is true in the logical context.

   Z3 will only invoke this callback using expressions \c n1 and \c n2 s.t.
   #Th_new_app or #Th_new_elem was invoked for them.
*/
void Th_new_eq(Z3_theory t, Z3_ast n1, Z3_ast n2);

void implyEqualityForConcatMember(Z3_theory t, Z3_ast lhs, Z3_ast rhs);

std::set<Z3_ast> findAllConcatContainingNode(Z3_theory t, Z3_ast node, int pos);

std::vector<Z3_ast> initLengthPropagation(Z3_theory t, Z3_ast nn1, Z3_ast nn2);

bool updateLengthNode_withValue(Z3_theory t, Z3_ast node, int minn, int maxx);
void updateLengthNode_fromSolver(Z3_theory t, Z3_ast node);
void doLengthPropagation(Z3_theory t, std::vector<Z3_ast> nodeList);
bool collectBestDomain(std::vector<Z3_ast> eq_nodes, std::pair<int, int> &domain);

void handleArithmetic(Z3_theory t, Z3_ast nn1, Z3_ast nn2);
int calculateAutomatonSize(Z3_theory t, Z3_ast node);
void checkConcatLenInEqc(Z3_theory t, Z3_ast n);
int inferLenConcat(Z3_theory t, Z3_ast n);
int haveEQLength(Z3_theory t, Z3_ast n1, Z3_ast n2);
void strEqLengthAxiom(Z3_theory t, Z3_ast varAst, Z3_ast strAst, int line);

bool checkLengthConsistency(Z3_theory t, std::vector<Z3_ast> eq01, std::vector<Z3_ast> eq02);

/*
 * check satisfiable of 'nn1 = nn2'
 */
bool checkEqualConsistency(Z3_theory t, Z3_ast nn1, Z3_ast nn2);
bool propagate(Z3_theory t, Z3_ast node);

void updateEqualMap(Z3_theory t, Z3_ast nn1, Z3_ast nn2);

bool checkParents(Z3_theory t, std::vector<Z3_ast> parents);
bool checkParent(Z3_theory t, Z3_ast node);
//void propagate(Z3_theory t, Z3_ast node, Automaton ton);

Automaton updateNode(Z3_theory t, Z3_ast node, bool &success);
Automaton evalNode(Z3_theory t, Z3_ast node, bool isIndependence);
// Automaton evalNode_Lazy(Z3_theory t, Z3_ast node, bool isIndependence);

void updateForAllEqualNodes(Z3_ast node, Automaton value);
Automaton evalAutomataDef(Z3_theory t, Z3_ast arg);
Automaton evalConcat(Z3_theory t, Z3_ast arg00, Z3_ast arg01, bool isIndependence);
Automaton evalVariable(Z3_theory t, Z3_ast node, bool isIndependence);
Automaton evalIntersection(Z3_theory t, std::vector<Z3_ast> list, bool isIndependence);
std::vector<Automaton> removeEqualAutomata(std::vector<Automaton> list);
std::vector<Automaton> removeGenericAutomata(std::vector<Automaton> list);

bool isCheckedNode(Z3_theory t, Z3_ast node, std::vector<Z3_ast> checkedNode);
bool crossCheck_Update(Z3_theory t, std::vector<Z3_ast> v1, std::vector<Z3_ast> v2, Z3_ast nn1, Z3_ast nn2 );
bool crossCheck(Z3_theory t, std::vector<Z3_ast> v1, Z3_ast node);

void updateInternalVarMap(std::vector<Z3_ast> list, Automaton value);
void updateInternalVarMap(Z3_ast node, Automaton value);
void updateInternalVarMap_independence(std::vector<Z3_ast> list, Automaton value);
void updateInternalVarMap_independence(Z3_ast node, Automaton value);

Automaton getPreCalculatedValue(Z3_theory t, Z3_ast node);
Automaton getPreCalculatedValue_independence(Z3_theory t, Z3_ast node);
std::vector<Z3_ast> getEqualValues(Z3_ast node);

Z3_ast handleAutomaton_VarKnownLength_lazy(Z3_theory t, int len, Z3_ast node);
Z3_ast handleAutomaton_VarKnownLength(Z3_theory t, int len, Z3_ast nn2);
void handleAutomaton_Automaton(Z3_theory t, Z3_ast nn1, Z3_ast nn2);
Z3_ast extendEqualVar_Automata(Z3_theory t, Z3_ast n1, Z3_ast n2);
Z3_ast extendEqualVars_Automata(Z3_theory t, std::vector<std::pair<Z3_ast, int>> langVal);

std::string customizeString(std::string s);

/**
   \brief Callback: invoked when <tt>n1 = n2</tt> is false in the logical context.

   Z3 will only invoke this callback using expressions \c n1 and \c n2 s.t.
   #Th_new_app or #Th_new_elem was invoked for them.
*/
void Th_new_diseq(Z3_theory t, Z3_ast n1, Z3_ast n2);

/**
   \brief Callback: invoked when \c n becomes relevant in the current search branch.
   Irrelevant expressions may be ignored by the theory solver.

   Z3 will only invoke this callback using a expression \c n s.t.
   #Th_new_app or #Th_new_elem was invoked for it.
*/
void Th_new_relevant(Z3_theory t, Z3_ast n);

/**
   \brief Callback: invoked when \c n is assigned to true/false.

   Z3 will only invoke this callback using a expression \c n s.t.
   #Th_new_app or #Th_new_elem was invoked for it.
*/
void Th_new_assignment(Z3_theory t, Z3_ast n, Z3_bool v);

/*
 * if
 * 		it is Concat -->
 * 		it is equal to AutomataDef -->
 */
void extendVariableToFindAllPossibleEqualities(
		Z3_theory t, Z3_ast node,
		std::set<Z3_ast> connectedVariables,
		std::set<std::string> &variableBelongToOthers,
		std::map<Z3_ast, std::vector<std::vector<Z3_ast>>> &allEqPossibilities,
		int level);

/**
   \brief Callback: invoked before Z3 starts building a model.
   This callback can be used to perform expensive operations lazily.
*/
Z3_bool Th_final_check(Z3_theory t);
bool checkDone(Z3_theory t);

void updateLength(Z3_theory t);
void calculateConcatLength(Z3_theory t);
bool hasLanguageConstraints(Z3_theory t, Z3_ast node);

std::pair<int, int> getLengthDomain(Z3_ast node);
void assignLanguageForLength(Z3_theory t, bool &assignSomethingNew, bool &satified);
void assignLanguage(Z3_theory t, bool &hasLanguage);
bool assignConcreteValue(Z3_theory t);
void assignFinalValues(Z3_theory t);
void assignFinalValues(Z3_theory t, std::map<Z3_ast, std::string> str_values, std::vector<Z3_ast> &axiomToAdd);
Z3_ast axiom_FinalValue(Z3_theory t, Z3_ast node, std::string value);
void assignOtherValue(Z3_theory t);

bool guessLanguage(Z3_theory t, Z3_ast node);
bool canSplit(int boundedFlat,
							int boundSize,
							int pos,
							std::string frame,
							std::vector<std::string> &flats);

bool determindConcat(Z3_theory t,
										std::vector<Z3_ast> leaves_list,
										int pos, std::map<Z3_ast,
										std::string> str_values, std::map<Z3_ast,
										int> len_values,
										std::vector<Z3_ast> &axiomToAdd,
										std::vector<Z3_ast> &errorNodes);
void update_ExtendList(Z3_theory t, std::vector<Z3_ast> eq, std::vector<Z3_ast> &tmp_ConcatList, int pos);

void update_constValue(Z3_theory t,
												Z3_ast node,
												std::string value,
												std::map<Z3_ast, std::string> &str_values,
												std::map<Z3_ast, int> &len_values,
												int line);

void undo_update_constValue(Z3_theory t,
												Z3_ast node,
												std::map<Z3_ast, std::string> &str_values,
												int line);

void undo_update_LengthValue(Z3_theory t,
												Z3_ast node,
												std::map<Z3_ast, int> &len_values,
												int line);

bool initialize(Z3_theory t, std::map<Z3_ast, std::string> &str_values,  std::map<Z3_ast, int> &len_values);
bool initializeNode(Z3_theory t, Z3_ast node, std::map<Z3_ast, std::string> &str_values,  std::map<Z3_ast, int> &len_values, std::map<Z3_ast, bool> &handled);

bool split_knownHead(Z3_theory t, std::string value, Z3_ast arg0, Z3_ast arg1, std::string &value_arg1, std::map<Z3_ast, std::string> str_values, std::map<Z3_ast, int> len_values);
bool split_knownTail(Z3_theory t, std::string value, Z3_ast arg0, Z3_ast arg1, std::string &value_arg0, std::map<Z3_ast, std::string> str_values, std::map<Z3_ast, int> len_values);
bool split_knownHeadLength(Z3_theory t, std::string value, Z3_ast arg0, Z3_ast arg1, std::string &value_arg0, std::string &value_arg1, std::map<Z3_ast, std::string> str_values, std::map<Z3_ast, int> len_values);
bool split_knownTailLength(Z3_theory t, std::string value, Z3_ast arg0, Z3_ast arg1, std::string &value_arg0, std::string &value_arg1, std::map<Z3_ast, std::string> str_values, std::map<Z3_ast, int> len_values);

std::pair<int, int> getLengthRange(Z3_theory t, Z3_ast node, std::map<Z3_ast, int> len_values);

Z3_ast createLanguageAxiom(Z3_theory t, Z3_ast node, std::set<std::string> list);
Z3_ast createLanguageAxiom(Z3_theory t, Z3_ast node, std::string language);

Z3_ast createValueAxiom(Z3_theory t, Z3_ast node, bool &success);
std::vector<Z3_ast> createValueAxiom(Z3_theory t, Z3_ast node);
int getConcreteValue_variable(Z3_theory t, Z3_ast node, Z3_ast value);

Z3_ast negatedConstraint(Z3_theory t);
Z3_ast negatedConstraint(Z3_theory t, Z3_ast node, int num);

std::vector<Z3_ast> collectLanguageValue(Z3_theory t);
Z3_ast collectSingleLanguageValue(Z3_theory t, Z3_ast node);
std::vector<Z3_ast> collectStringValue(Z3_theory t);
int collectSingleLanguage_index(Z3_theory t, Z3_ast node);

std::vector<std::string> parse_string_language(std::string s, std::string delimieters = " ()*");

std::vector<Z3_ast> createParikhConstraints_simpleLanguage(Z3_theory t, Z3_ast node, std::string language);
std::vector<Z3_ast> createParikhConstraints_evenSimplerLanguage(Z3_theory t, Z3_ast node, std::string language);
std::vector<Z3_ast> createParikhConstraints_string(Z3_theory t, Z3_ast node, std::string value);
std::vector<Z3_ast> basicArithConstraints_forEqual(Z3_theory t, Z3_ast nn1, Z3_ast nn2);
std::vector<Z3_ast> basicArithConstraints_forConcat(Z3_theory t, Z3_ast nn1, Z3_ast nn2);
std::vector<Z3_ast> basicArithConstraints_forNode(Z3_theory t, Z3_ast node);
std::vector<Z3_ast> basicArithConstraints_forNode_simple(Z3_theory t, Z3_ast node);

Z3_ast getInternalValue(Z3_theory t, Z3_ast node);
Z3_ast createOrStr(Z3_theory t, std::set<std::string> strs, Z3_ast node);

bool hasLanguageOverVar(Z3_theory t, Z3_ast node);
bool hasConstraintOverVar(Z3_theory t, Z3_ast node);
bool relatedToConcat(Z3_theory t, Z3_ast node);

std::string createStringWithLength_lazy(Z3_theory t, Z3_ast node, int len, std::map<std::string, std::set<char>> charSet);
std::string createStringWithLength(Z3_theory t, Z3_ast node, int len, std::map<std::string, std::set<char>> charSet);
std::string createChar(std::set<char> charSet);
Z3_ast findEqualVariable(Z3_theory t, Z3_ast node);
std::string createGenericLanguage(Z3_theory t, Z3_ast node, std::map<std::string, std::set<char>> charSet);

/*
 * Mark variable appeared in map "varAppearMap"
 */
void classifyAstByType(Z3_theory t, Z3_ast node, std::map<Z3_ast, int> & varMap, std::map<Z3_ast, int> & concatMap,
		std::map<Z3_ast, std::set<Z3_ast>> & membership);

/*
 *
 */
bool isInterestingFuncKind(Z3_decl_kind func_decl);

void classifyAstByTypeInPositiveContext(Z3_theory t, Z3_ast node, std::map<Z3_ast, int> & varMap, std::map<Z3_ast, int> & concatMap,
		std::map<Z3_ast, std::set<Z3_ast>> & membership);

/*
 * Decide whether two n1 and n2 are ALREADY in a same eq class
 * Or n1 and n2 are ALREADY treated equal by the core
 * BUT, they may or may not be really equal
 */
bool inSameEqc(Z3_theory t, Z3_ast n1, Z3_ast n2);

/*
 * Dependence analysis from current context assignment
 * - "freeVarMap" contains a set of variables that doesn't constrained by Concats.
 *    But it's possible that it's bounded by unrolls
 *    For the case of
 *    (1) var1 = unroll(r1, t1)
 *        var1 is in the freeVarMap
 *        > should unroll r1 for var1
 *    (2) var1 = unroll(r1, t1) /\ var1 = Concat(var2, var3)
 *        var2, var3 are all in freeVar
 *        > should split the unroll function so that var2 and var3 are bounded by new unrolls
 */
void ctxDepAnalysis(Z3_theory t, std::map<Z3_ast, int> & strVarMap, std::map<Z3_ast, int> & freeVarMap,
    std::map<Z3_ast, std::set<Z3_ast> > & unrollGroupMap);

Z3_ast getLengthAST(Z3_theory t, Z3_ast n);

Z3_ast getParikhChar(Z3_theory t, Z3_ast n, char c);

/*
 * Query the integer theory.
 *   - If n has length value in integer theory, return the value.
 *   - Else, return -1.
 */
int getLenValue(Z3_theory t, Z3_ast node);

int getBoundLenValue(Z3_theory t, Z3_ast node,  int& lowerBound, int& upperBound);
/**
   \brief If the equivalence class containing \c n contains a theory value, then return it.
   Otherwise, return 0.

   \remark An equivalence class may contain at most one theory value
   since theory values are different by definition.
*/
Z3_ast get_eqc_value(Z3_theory t, Z3_ast n, bool & hasEqcValue);

void printStrArgLen(Z3_theory t, Z3_ast node, int ll);
/**
   \brief Display equivalence class containing \c n.
*/
void display_eqc(Z3_theory t, Z3_ast n, std::vector<Z3_ast> equivalent);
std::vector<Z3_ast> collect_eqc(Z3_theory t, Z3_ast n);

/**
   \brief Display the parent theory operators of the equivalence class containing \c n.
*/
void display_eqc_parents(Z3_theory t, Z3_ast n, std::vector<Z3_ast> equivalent);
std::vector<Z3_ast> collect_eqc_parents(Z3_theory t, Z3_ast n);
std::set<Z3_ast> collectAllParents(Z3_theory t, Z3_ast node);
std::set<Z3_ast> collectAllFurtherParents(Z3_theory t, Z3_ast node);
void collectAllFurtherParents(Z3_theory t, Z3_ast node, std::set<Z3_ast> &list);

void displayListNode(Z3_theory t, std::vector<Z3_ast> l, std::string msg = "");
void displayListNode(Z3_theory t, std::set<Z3_ast> l, std::string msg = "");
void __printNode(Z3_theory t, Z3_ast node);
void __printNodeAxiom(Z3_theory t, Z3_ast node);

void display_new_eq(Z3_theory t, Z3_ast n1, Z3_ast n2, std::vector<Z3_ast> eq01, std::vector<Z3_ast> eq01_parent, std::vector<Z3_ast> eq02, std::vector<Z3_ast> eq02_parent);
void displayStringSolverInformation(Z3_theory t);

void collect_from_new_eq(Z3_theory t, Z3_ast n1, Z3_ast n2, std::vector<Z3_ast>& eq01, std::vector<Z3_ast>& eq01_parent, std::vector<Z3_ast>& eq02, std::vector<Z3_ast>& eq02_parent);

/**
   \brief Instantiate the unit axiom for the parents of \c n because
   \c n is now equal to unit u in the logical context.
*/
void apply_unit_axiom_for_parents_of(Z3_theory t, Z3_ast n);

bool isVariable(Z3_theory t, Z3_ast n);

bool isStrVariable(Z3_theory t, Z3_ast n);

bool isAutomatonFunc(Z3_theory t, Z3_ast n);

bool isNonDetAutomatonFunc(Z3_theory t, Z3_ast n);

bool isDetAutomatonFunc(Z3_theory t, Z3_ast n);

bool isConcatFunc(Z3_theory t, Z3_ast n);

bool isConstStr(Z3_theory t, Z3_ast node);

bool isLengthFunc(Z3_theory t, Z3_ast n);

bool isUnrollFunc(Z3_theory t, Z3_ast n);

bool isRegexStar(Z3_theory t, Z3_ast n);

bool isStr2Regex(Z3_theory t, Z3_ast n);

bool isRegexIn(Z3_theory t, Z3_ast n);

bool isRegexUnion(Z3_theory t, Z3_ast n);

bool isRegexConcat(Z3_theory t, Z3_ast n);

void __printNode(Z3_theory t, Z3_ast node);

void __printNodeAxiom(Z3_theory t, Z3_ast node);

std::string getStdRegexStr(Z3_theory t, Z3_ast regex);

std::string str2RegexStr(std::string str);

std::string getStdGrmStr(Z3_theory t, Z3_ast grammar);

std::string lookUpGrammar(std::string name);

T_TheoryType getNodeType(Z3_theory t, Z3_ast n);

std::string getConstStrValue(Z3_theory t, Z3_ast n);

void basicStrVarAxiom(Z3_theory t, Z3_ast vNode, int line);

void addAxiom(Z3_theory t, Z3_ast toAssert, int line, bool display);

void addAxiom_Theory(Z3_theory t, Z3_ast toAssert, int line, bool display);

void checkInputVar(Z3_theory t, Z3_ast node);

void overApproxController();

#endif /* STRINGTHEORY_H_ */
