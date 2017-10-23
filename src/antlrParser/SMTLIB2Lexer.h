/* lexer header section */

// Generated from SMTLIB2Lexer.g4 by ANTLR 4.7

#pragma once

/* lexer precinclude section */

#include "antlr4-runtime.h"


/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


namespace antlrcpptest {

/* lexer context section */

class  SMTLIB2Lexer : public antlr4::Lexer {
public:
  enum {
    SYM_AND = 1, SYM_OR = 2, SYM_NOT = 3, SYM_BOOL = 4, SYM_CONTINUED_EXECUTION = 5, 
    SYM_ERROR = 6, SYM_FALSE = 7, SYM_IMMEDIATE_EXIT = 8, SYM_INCOMPLETE = 9, 
    SYM_LOGIC = 10, SYM_MEMOUT = 11, SYM_SAT = 12, SYM_SUCCESS = 13, SYM_THEORY = 14, 
    SYM_TRUE = 15, SYM_UNKNOWN = 16, SYM_UNSAT = 17, SYM_UNSUPPORTED = 18, 
    KEYWORD_ALL_STATISTICS = 19, KEYWORD_AUTHORS = 20, KEYWORD_AXIOMS = 21, 
    KEYWORD_CHAINABLE = 22, KEYWORD_DEFINITION = 23, KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL = 24, 
    KEYWORD_ERROR_BEHAVIOR = 25, KEYWORD_EXPAND_DEFINITIONS = 26, KEYWORD_EXTENSIONS = 27, 
    KEYWORD_FUNS = 28, KEYWORD_FUNS_DESCRIPTION = 29, KEYWORD_INTERACTIVE_MODE = 30, 
    KEYWORD_LANGUAGE = 31, KEYWORD_LEFT_ASSOC = 32, KEYWORD_NAME = 33, KEYWORD_NAMED = 34, 
    KEYWORD_NOTES = 35, KEYWORD_PRINT_SUCCESS = 36, KEYWORD_PRODUCE_ASSIGNMENTS = 37, 
    KEYWORD_PRODUCE_MODELS = 38, KEYWORD_PRODUCE_PROOFS = 39, KEYWORD_PRODUCE_UNSAT_CORES = 40, 
    KEYWORD_RANDOM_SEED = 41, KEYWORD_REASON_UNKNOWN = 42, KEYWORD_REGULAR_OUTPUT_CHANNEL = 43, 
    KEYWORD_RIGHT_ASSOC = 44, KEYWORD_SORTS = 45, KEYWORD_SORTS_DESCRIPTION = 46, 
    KEYWORD_STATUS = 47, KEYWORD_THEORIES = 48, KEYWORD_VALUES = 49, KEYWORD_VERBOSITY = 50, 
    KEYWORD_VERSION = 51, TOKEN_BANG = 52, TOKEN_UNDERSCORE = 53, TOKEN_AS = 54, 
    TOKEN_DECIMAL = 55, TOKEN_EXISTS = 56, TOKEN_FORALL = 57, TOKEN_LET = 58, 
    TOKEN_NUMERAL = 59, TOKEN_PAR = 60, TOKEN_STRING = 61, TOKEN_CMD_ASSERT = 62, 
    TOKEN_CMD_CHECK_SAT = 63, TOKEN_CMD_DECLARE_SORT = 64, TOKEN_CMD_DECLARE_FUN = 65, 
    TOKEN_CMD_DEFINE_SORT = 66, TOKEN_CMD_DEFINE_FUN = 67, TOKEN_CMD_EXIT = 68, 
    TOKEN_CMD_GET_ASSERTIONS = 69, TOKEN_CMD_GET_ASSIGNMENT = 70, TOKEN_CMD_GET_INFO = 71, 
    TOKEN_CMD_GET_OPTION = 72, TOKEN_CMD_GET_PROOF = 73, TOKEN_CMD_GET_UNSAT_CORE = 74, 
    TOKEN_CMD_GET_VALUE = 75, TOKEN_CMD_POP = 76, TOKEN_CMD_PUSH = 77, TOKEN_CMD_SET_LOGIC = 78, 
    TOKEN_CMD_SET_INFO = 79, TOKEN_CMD_SET_OPTION = 80, TOKEN_CMD_GET_MODEL = 81, 
    NUMERAL = 82, DECIMAL = 83, HEXADECIMAL = 84, BINARY = 85, STRING = 86, 
    WS = 87, SIMPLE_SYM = 88, QUOTED_SYM = 89, COMMENT = 90, KEYWORD_TOKEN = 91, 
    OpenPar = 92, ClosePar = 93
  };

  SMTLIB2Lexer(antlr4::CharStream *input);
  ~SMTLIB2Lexer();

  /* public lexer declarations section */
  bool canTestFoo() { return true; }
  bool isItFoo() { return true; }
  bool isItBar() { return true; }

  void myFooLexerAction() { /* do something*/ };
  void myBarLexerAction() { /* do something*/ };

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

  virtual void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;
private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;

  /* private lexer declarations/members section */

  // Individual action functions triggered by action() above.
  void WSAction(antlr4::RuleContext *context, size_t actionIndex);
  void COMMENTAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace antlrcpptest
