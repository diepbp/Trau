/*
 * UnderApprox.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef UNDERAPPROX_H_
#define UNDERAPPROX_H_

#include "Arrangement.h"
#include "FileConverter.h"
#include "Utils.h"

#define ALLVAR 0
#define MAXP 6
#define MAXQ 7
#define DEFAULT_CHAR 'a'
#define REGEX_BOUND 10

extern std::string orgInput;
extern bool getModel;
extern bool beReviewed;

static std::map<std::string, std::vector<std::vector<std::string>>> equalitiesMap;
static std::map<std::string, std::vector<std::vector<std::string>>> fullEqualitiesMap;
static std::map<StringOP, std::string> orgRewriterStrMap;
static std::map<std::string, int> global_smtVars;
static std::vector<std::vector<std::string>> global_smtStatements;

#ifdef ALLVAR
static std::set<std::string> allVariables;
#endif

static int regexCnt;
static std::map<std::pair<std::string, std::string>, bool> notContainMap;
static std::vector<std::string> smtVarDefinition;
static std::vector<std::string> smtLenConstraints;

static std::vector<std::string> repeatedVariableConstraints;
static std::map<std::string, int> connectedVariables;

//static std::map<std::pair<std::string, std::string>, std::string> constMap;
static std::map<std::string, std::string> constMap;
static std::map<std::string, int> varLength;
static std::map<std::pair<int, int>, std::vector<Arrangment>> arrangements;

static std::map<std::string, int> varPieces;
static std::map<std::string, std::set<std::string>> appearanceMap;

static int noFlatVariables = 0;
static int connectingSize;
static int maxInt = -1;
static long sumInt = -1;
static long sumConstLength = 0;
static bool lazy = true;
extern bool unknownResult;
extern std::map<int, std::string> languageMap;
extern int languageVersion;
static std::set<std::string> generatedEqualities;

/*
 * get value from eq map
 */
std::string getPossibleValue(std::string s);

void updatePossibleArrangements(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		std::vector<Arrangment> tmp,
		std::vector<Arrangment> &possibleCases);

void updatePossibleArrangements(
		std::vector<Arrangment> tmp,
		std::vector<Arrangment> &possibleCases);

/*
 *
 */
bool isUnionStr(std::string str);

/*
 *
 */
bool isConstStr(std::string str);

/*
 *
 */
bool passNotContainMapReview(
		Arrangment a,
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);

/*
 * First base case
 */
void handleCase_0_0(
		bool usingFilter = true);

void handleCase_0_0_general();
/*
 * 2nd base case (sum lhs...) = [0]
 */
void handleCase_n_0(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		bool usingFilter = true);

void handleCase_n_0_general(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);
/*
 * 2nd base case [0] = (sum rhs...)
 */
void handleCase_0_n(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		bool usingFilter = true);

void handleCase_0_n_general(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);

/*
 * general case
 */
void handleCase_n_n(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements,
		bool usingFilter = true);

void handleCase_n_n_general(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);

/*
 *
 */
Arrangment manuallyCreate_arrangment(
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);

/*
 * lhs: size of the lhs
 * rhs: size of the rhs
 * lhs_elements: elements of lhs
 * rhs_elements: elements of rhs
 *
 * Pre-Condition: x_i == 0 --> x_i+1 == 0
 *
 */
std::vector<std::string> collectAllPossibleArrangements(
		std::string lhs_str, std::string rhs_str,
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);

/*
 *
 */
int findVariableSize(std::string v);

/*
 * startswith a b
 * startwith "a" b
 * startwith a "b"
 */
std::string create_constraints_StartsWith(
		std::string str00,
		std::string str01,
		std::string boolValue);

/*
 * endswith a b
 * endswith "a" b
 * endswith a "b"
 */
std::string create_constraints_EndsWith(
		std::string str00,
		std::string str01,
		std::string boolValue);

/*
 * replace a b c
 * replace "a" b c
 * replace a "b" c
 */
std::string create_constraints_Replace(std::string lhs, std::vector<std::string> args, std::string boolValue);

/*
 * replaceAll a b c
 * replaceAll "a" b c
 * replaceAll a "b" c
 *
 * --> iter = iter
 */
std::string create_constraints_ReplaceAll(
		std::vector<std::string> args,
		std::string boolValue,
		std::map<std::string, std::vector<std::string>> eqToStr);

/*
 *
 */
std::string create_constraints_NOTContain(std::string var, std::string value);

/*
 *
 */
std::string create_constraints_NOTEqual(
		std::string str00,
		std::string str01);

/*
 *
 */
std::string create_constraints_ToLower(std::string str00, std::string str01);

/*
 *
 */
std::string create_constraints_ToUpper(std::string str00, std::string str01);

/*
 *
 */
void handle_NOTContains(
		std::map<StringOP, std::string> rewriterStrMap);

/**
 * handle startwith constraints
 */
void handle_StartsWith(std::map<StringOP, std::string> rewriterStrMap);

/**
 * handle endswith constraints
 */
void handle_EndsWith(
		std::map<StringOP, std::string> rewriterStrMap);

/*
 * handle replace constraints
 */
void handle_Replace(std::map<StringOP, std::string> rewriterStrMap);

/*
 * handle replace constraints
 */
void handle_ReplaceAll(std::map<StringOP, std::string> rewriterStrMap);

/*
 *
 */
void handle_ToUpper(std::map<StringOP, std::string> rewriterStrMap);

/*
 *
 */
void handle_ToLower(std::map<StringOP, std::string> rewriterStrMap);

/*
 * define array for connected variable
 */
void create_constraints_array(std::vector<std::string> &defines, std::vector<std::string> &constraints);

/*
 * define array for connected variable
 */
void create_const_array(std::vector<std::string> &defines, std::vector<std::string> &constraints);

/*
 *
 * (declare-const __regex_x Int)
 *
 * __regex_x >= 0
 *
 */
void create_constraints_RegexCnt(std::vector<std::string> &defines, std::vector<std::string> &constraints);

/*
 * var name -> define var
 * (declare-const len_const_0_0 Int)
 * (declare-const len_const_1_0 Int)
 *
 * const = sum(len_const_0_0)
 * len_const_0_0 >= 0
 *
 */
void create_constraints_const(std::vector<std::string> &defines, std::vector<std::string> &constraints);

/*
 * var name -> define var
 * (declare-const len_var_0 Int)
 * (declare-const len_var_0 Int)
 *
 * len_var = sum(len_var_0)
 * len_var_0 >= 0
 *
 */
void create_constraints_strVar(std::vector<std::string> &defines, std::vector<std::string> &constraints);

/*
 * len_const = (a * 1) + (b * 2) + ...
 */
void create_constraints_regex(std::vector<std::string> &defines, std::vector<std::string> &constraints, std::string regex, std::string name);

/*
 * len_x = sum(len_y)
 */
std::string createLengthConstraintForAssignment(std::string x, std::vector<std::string> components);

/*
 * write to file output
 */
void writeOutput02(std::string outFile);

void writeOutput_basic(std::string outFile);

/*
 * write & verify to file output
 */
std::vector<std::string> createSatisfyingAssignments(
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<std::string, std::string> lengthResultMap,
		std::map<std::string, std::string> strValue);



/*
 * convert lhs == rhs to SMT formula
 */
std::vector<std::string> equalityToSMT(
		std::string lhs, std::string rhs,
		std::vector<std::pair<std::string, int>> lhs_elements,
		std::vector<std::pair<std::string, int>> rhs_elements);

/*
 * print input
 */
void printEqualMap(std::map<std::string, std::vector<std::vector<std::string>>> equalMap);


/*
 * AutomataDef to const
 */
std::string collectConst(std::string str);

std::string generate_simple_constraint(std::vector<std::vector<std::string>> eqVector);

/**
 * collect all variables we need to handle
 */
void parseEqualityMap(std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<std::string, std::vector<std::vector<std::string>>> _fullEqualMap);

/*
 * Create a general value that the component belongs to
 */
std::string sumStringVector(std::vector<std::string> list);

/*
 * sum const strings
 * "a" . "b" = "ab"
 */
void sumConstString();


/*
 * Assign a name for each const string,
 * We need that name when we split const
 */
void createConstMap();

/*
*
*/
void addToConnectedVar(StringOP op, std::map<std::string, int> &connectedVarSet, int length);

/*
 * Find connected variables
 * They are variables that are used by more than one variables
 */

void collectConnectedVariables(std::map<StringOP, std::string> rewriterStrMap);

/**
 * transform char range function
 */
std::vector<std::string> reformatCharRange(std::vector<std::string> v);


/*
 * Remove all equalities without connected variables and consts
 */

void refineEqualMap(void refineEqualMap(std::map<StringOP, std::string> rewriterStrMap));

/*
 *
 */
std::map<std::string, std::string> decodeResultMap(std::map<std::string, std::string> resultMap);

/*
 *
 */
std::string underApproxRegex(std::string str);

/**
 * (abc|cde|ghi)*
 */
void optimizeFlatAutomaton(std::string &s);

/*
 *
 */
std::vector<std::vector<std::string>> parseRegexComponents(std::string str);

/*
 *
 */
bool equalVector(std::vector<std::string> a, std::vector<std::string> b);

/*
 *
 */
bool similarVector(
		std::vector<std::string> a,
		std::vector<std::string> b,
		std::map<std::string, std::vector<std::string>> notEqualMap
		);

/*
 *
 */
std::vector<std::vector<std::string>> refineVectors(std::vector<std::vector<std::string>> list);

/*
 * a b c (abc)* --> abc (abc)*
 */
std::vector<std::vector<std::string>> combineConstStr(std::vector<std::vector<std::string>> regexElements);

/*
 * Input: x . y
 * Output: flat . flat . flat . flat . flat . flat
 */
std::vector<std::pair<std::string, int>> createEquality(std::vector<std::string> list);

std::vector<std::string> createSetOfFlatVariables(int flatP);

/*
 * cut the same prefix and posfix
 * */
void optimizeEquality(
		std::vector<std::string> lhs,
		std::vector<std::string> rhs,
		std::vector<std::string> &new_lhs,
		std::vector<std::string> &new_rhs);
/*
 *
 */
unsigned findMaxP(std::vector<std::vector<std::string>> v);

/*
 * Pthread
 * Each thread handles a part in the global map from start -> end
 */
void convertEqualities();

/*
 * Just do sequential to compare performance
 */
void testSequential();

/*
 *
 */
void testEqualityToSMT();

/*
 *
 */
void createStringFromSet(std::set<std::string> list, int length, std::string &ret, bool &found);

/*
 * len = 10, (ab)* --> abababababab
 */
std::string getTrivialRegex(std::string s, int length);

/*
 * len = 10, (ab)* --> abababababab
 */
std::string getValueFromRegex(std::string s, int length);

/*
 *
 */
void syncConst(
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);

/*
 *
 */
std::vector<int> createString(
		std::string name,
		std::string value,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> strValue,
		std::vector<std::pair<int, int>> iters,
		bool &assigned,
		bool assignAnyway);

/*
 *
 */
std::string getVarName(std::string s);

/*
 *
 */
int getVarLength(
		std::string newlyUpdate,
		std::map<std::string, int> len);

/*
 *
 */
std::vector<int> getVarValue(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue);

/*
 *
 */
void backwardPropagarate(
		std::string name,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);

/*
 * a = b . c. We know a, need to update b and c
 */
void backwardPropagarate_simple(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);

/*
 *
 */
void forwardPropagate(
		std::string newlyUpdate,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);

/*
 *
 */
bool needValue(std::string name,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> strValue);

/*
 *
 */
bool isBlankValue(std::string name,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> strValue);

/*
 *
 */
bool findExistsingValue(
		std::string varName,
		std::vector<StringOP> equalities,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		std::vector<std::string> eqVar);

/*
 * create str values after running Z3
 */
void formatOtherVars(
		std::vector<unsigned> indexes,
		std::map<std::string, std::string> solverValues,
		std::vector<std::pair<std::string, int>> lenVector,
		std::map<std::string, int> len,
		std::map<std::string, int> iterInt,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);

/*
 *
 */
void formatRegexes(
		std::vector<unsigned> indexes,
		std::vector<std::pair<std::string, int>> lenVector,
		std::map<std::string, int> len,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);

/*
 *
 */
void formatConnectedVars(
		std::vector<unsigned> indexes,
		std::map<std::string, std::string> solverValues,
		std::vector<std::pair<std::string, int>> lenVector,
		std::map<std::string, int> len,
		std::map<std::string, int> iterInt,
		std::map<std::string, std::vector<int>> &strValue,
		bool &completion);
/*
 * create str values after running Z3
 */
std::map<std::string, std::string> formatResult(
		std::map<std::string,
		std::string> len,
		std::map<std::string, std::string> _strValue,
		bool &completion);

/*
 *
 */
bool Z3_run(
		std::string cmd,
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		bool finalCall);

/*
 * Pthread Caller
 */
void pthreadController();

/*
 *
 */
void reset();

/*
 * replace all "Length " by "len_"
 */
std::set<std::string> reformatCarryOnConstraints(std::set<std::string> _carryOnConstraints);

/*
 *
 */
void createNotContainMap(std::map<StringOP, std::string> rewriterStrMap);

/*
 *
 */
std::map<std::string, std::vector<std::string>> createNotEqualMap(std::map<StringOP, std::string> rewriterStrMap);

/*
 *
 */
/*
 *
 */
void createAppearanceMap();

/*
 * */
void staticIntegerAnalysis(std::string fileName);

/*
 *
 */
void initConnectingSize(bool prep);

/*
 *
 */
void init(std::map<StringOP, std::string> rewriterStrMap);

void additinalHandling(std::map<std::string, std::string> rewriterStrMap);

/*
 *
 */
void defineIntVars(std::map<StringOP, std::string> rewriterStrMap);

/*
 *
 */
bool isTrivialInequality(std::string x, std::string  y);

/*
 *
 */
void updateRewriter(
		std::map<StringOP, std::string> &rewriterStrMap);

/*
 *
 */
bool hasInequalities(std::map<StringOP, std::string> rewriterStrMap);


bool underapproxController(
		std::map<std::string, std::vector<std::vector<std::string>>> _equalMap,
		std::map<std::string, std::vector<std::vector<std::string>>> _fullEqualMap,
		std::map<StringOP, std::string> rewriterStrMap,
		std::set<std::string> carryOnConstraints,
		std::map<std::string, int> _currentLength,
		std::string fileDir,
		bool lazy = true);

#endif /* UNDERAPPROX_H_ */
