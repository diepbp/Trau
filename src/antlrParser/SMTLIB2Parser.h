/* parser/listener/visitor header section */

// Generated from SMTLIB2Parser.g4 by ANTLR 4.7

#pragma once

/* parser precinclude section */

#include "antlr4-runtime.h"


/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


namespace antlrcpptest {

/* parser context section */

class  SMTLIB2Parser : public antlr4::Parser {
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

  enum {
    RuleSymbol = 0, RuleKeyword = 1, RuleSpec_constant = 2, RuleS_expr = 3, 
    RuleIdentifier = 4, RuleSort = 5, RuleAttribute_value = 6, RuleAttribute = 7, 
    RuleQual_identifier = 8, RuleVar_binding = 9, RuleSorted_var = 10, RuleTerm = 11, 
    RuleSort_symbol_decl = 12, RuleMeta_spec_constant = 13, RuleFun_symbol_decl = 14, 
    RulePar_fun_symbol_decl = 15, RuleTheory_decl = 16, RuleTheory_attribute = 17, 
    RuleLogic_attribute = 18, RuleLogic = 19, RuleB_value = 20, RuleOption = 21, 
    RuleInfo_flag = 22, RuleCommand = 23, RuleScript = 24, RuleGen_response = 25, 
    RuleError_behavior = 26, RuleReason_unknown = 27, RuleStatus = 28, RuleInfo_response = 29, 
    RuleGet_info_response = 30, RuleCheck_sat_response = 31, RuleGet_assertions_response = 32, 
    RuleProof = 33, RuleGet_proof_response = 34, RuleGet_unsat_core_response = 35, 
    RuleValuation_pair = 36, RuleGet_value_response = 37, RuleT_valuation_pair = 38, 
    RuleGet_assignment_response = 39, RuleGet_option_response = 40
  };

  SMTLIB2Parser(antlr4::TokenStream *input);
  ~SMTLIB2Parser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  /* public parser declarations/members section */
  bool myAction() { return true; }
  bool doesItBlend() { return true; }
  void cleanUp() {}
  void doInit() {}
  void doAfter() {}


  class SymbolContext;
  class KeywordContext;
  class Spec_constantContext;
  class S_exprContext;
  class IdentifierContext;
  class SortContext;
  class Attribute_valueContext;
  class AttributeContext;
  class Qual_identifierContext;
  class Var_bindingContext;
  class Sorted_varContext;
  class TermContext;
  class Sort_symbol_declContext;
  class Meta_spec_constantContext;
  class Fun_symbol_declContext;
  class Par_fun_symbol_declContext;
  class Theory_declContext;
  class Theory_attributeContext;
  class Logic_attributeContext;
  class LogicContext;
  class B_valueContext;
  class OptionContext;
  class Info_flagContext;
  class CommandContext;
  class ScriptContext;
  class Gen_responseContext;
  class Error_behaviorContext;
  class Reason_unknownContext;
  class StatusContext;
  class Info_responseContext;
  class Get_info_responseContext;
  class Check_sat_responseContext;
  class Get_assertions_responseContext;
  class ProofContext;
  class Get_proof_responseContext;
  class Get_unsat_core_responseContext;
  class Valuation_pairContext;
  class Get_value_responseContext;
  class T_valuation_pairContext;
  class Get_assignment_responseContext;
  class Get_option_responseContext; 

  class  SymbolContext : public antlr4::ParserRuleContext {
  public:
    SymbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SIMPLE_SYM();
    antlr4::tree::TerminalNode *SYM_AND();
    antlr4::tree::TerminalNode *SYM_OR();
    antlr4::tree::TerminalNode *SYM_NOT();
    antlr4::tree::TerminalNode *QUOTED_SYM();
    antlr4::tree::TerminalNode *SYM_BOOL();
    antlr4::tree::TerminalNode *SYM_CONTINUED_EXECUTION();
    antlr4::tree::TerminalNode *SYM_ERROR();
    antlr4::tree::TerminalNode *SYM_FALSE();
    antlr4::tree::TerminalNode *SYM_IMMEDIATE_EXIT();
    antlr4::tree::TerminalNode *SYM_INCOMPLETE();
    antlr4::tree::TerminalNode *SYM_LOGIC();
    antlr4::tree::TerminalNode *SYM_MEMOUT();
    antlr4::tree::TerminalNode *SYM_SAT();
    antlr4::tree::TerminalNode *SYM_SUCCESS();
    antlr4::tree::TerminalNode *SYM_THEORY();
    antlr4::tree::TerminalNode *SYM_TRUE();
    antlr4::tree::TerminalNode *SYM_UNKNOWN();
    antlr4::tree::TerminalNode *SYM_UNSAT();
    antlr4::tree::TerminalNode *SYM_UNSUPPORTED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SymbolContext* symbol();

  class  KeywordContext : public antlr4::ParserRuleContext {
  public:
    KeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_TOKEN();
    antlr4::tree::TerminalNode *KEYWORD_ALL_STATISTICS();
    antlr4::tree::TerminalNode *KEYWORD_AUTHORS();
    antlr4::tree::TerminalNode *KEYWORD_AXIOMS();
    antlr4::tree::TerminalNode *KEYWORD_CHAINABLE();
    antlr4::tree::TerminalNode *KEYWORD_DEFINITION();
    antlr4::tree::TerminalNode *KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL();
    antlr4::tree::TerminalNode *KEYWORD_ERROR_BEHAVIOR();
    antlr4::tree::TerminalNode *KEYWORD_EXPAND_DEFINITIONS();
    antlr4::tree::TerminalNode *KEYWORD_EXTENSIONS();
    antlr4::tree::TerminalNode *KEYWORD_FUNS();
    antlr4::tree::TerminalNode *KEYWORD_FUNS_DESCRIPTION();
    antlr4::tree::TerminalNode *KEYWORD_INTERACTIVE_MODE();
    antlr4::tree::TerminalNode *KEYWORD_LANGUAGE();
    antlr4::tree::TerminalNode *KEYWORD_LEFT_ASSOC();
    antlr4::tree::TerminalNode *KEYWORD_NAME();
    antlr4::tree::TerminalNode *KEYWORD_NAMED();
    antlr4::tree::TerminalNode *KEYWORD_NOTES();
    antlr4::tree::TerminalNode *KEYWORD_PRINT_SUCCESS();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_ASSIGNMENTS();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_MODELS();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_PROOFS();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_UNSAT_CORES();
    antlr4::tree::TerminalNode *KEYWORD_RANDOM_SEED();
    antlr4::tree::TerminalNode *KEYWORD_REASON_UNKNOWN();
    antlr4::tree::TerminalNode *KEYWORD_REGULAR_OUTPUT_CHANNEL();
    antlr4::tree::TerminalNode *KEYWORD_RIGHT_ASSOC();
    antlr4::tree::TerminalNode *KEYWORD_SORTS();
    antlr4::tree::TerminalNode *KEYWORD_SORTS_DESCRIPTION();
    antlr4::tree::TerminalNode *KEYWORD_STATUS();
    antlr4::tree::TerminalNode *KEYWORD_THEORIES();
    antlr4::tree::TerminalNode *KEYWORD_VALUES();
    antlr4::tree::TerminalNode *KEYWORD_VERBOSITY();
    antlr4::tree::TerminalNode *KEYWORD_VERSION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeywordContext* keyword();

  class  Spec_constantContext : public antlr4::ParserRuleContext {
  public:
    Spec_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERAL();
    antlr4::tree::TerminalNode *DECIMAL();
    antlr4::tree::TerminalNode *HEXADECIMAL();
    antlr4::tree::TerminalNode *BINARY();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Spec_constantContext* spec_constant();

  class  S_exprContext : public antlr4::ParserRuleContext {
  public:
    S_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Spec_constantContext *spec_constant();
    SymbolContext *symbol();
    KeywordContext *keyword();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<S_exprContext *> s_expr();
    S_exprContext* s_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  S_exprContext* s_expr();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SymbolContext *symbol();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *TOKEN_UNDERSCORE();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<antlr4::tree::TerminalNode *> NUMERAL();
    antlr4::tree::TerminalNode* NUMERAL(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  SortContext : public antlr4::ParserRuleContext {
  public:
    SortContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<SortContext *> sort();
    SortContext* sort(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SortContext* sort();

  class  Attribute_valueContext : public antlr4::ParserRuleContext {
  public:
    Attribute_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SymbolContext *symbol();
    Spec_constantContext *spec_constant();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<S_exprContext *> s_expr();
    S_exprContext* s_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Attribute_valueContext* attribute_value();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KeywordContext *keyword();
    Attribute_valueContext *attribute_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeContext* attribute();

  class  Qual_identifierContext : public antlr4::ParserRuleContext {
  public:
    Qual_identifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *TOKEN_AS();
    SortContext *sort();
    antlr4::tree::TerminalNode *ClosePar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qual_identifierContext* qual_identifier();

  class  Var_bindingContext : public antlr4::ParserRuleContext {
  public:
    Var_bindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    SymbolContext *symbol();
    TermContext *term();
    antlr4::tree::TerminalNode *ClosePar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Var_bindingContext* var_binding();

  class  Sorted_varContext : public antlr4::ParserRuleContext {
  public:
    Sorted_varContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    SymbolContext *symbol();
    SortContext *sort();
    antlr4::tree::TerminalNode *ClosePar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sorted_varContext* sorted_var();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Spec_constantContext *spec_constant();
    Qual_identifierContext *qual_identifier();
    std::vector<antlr4::tree::TerminalNode *> OpenPar();
    antlr4::tree::TerminalNode* OpenPar(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ClosePar();
    antlr4::tree::TerminalNode* ClosePar(size_t i);
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    antlr4::tree::TerminalNode *TOKEN_LET();
    std::vector<Var_bindingContext *> var_binding();
    Var_bindingContext* var_binding(size_t i);
    antlr4::tree::TerminalNode *TOKEN_FORALL();
    std::vector<Sorted_varContext *> sorted_var();
    Sorted_varContext* sorted_var(size_t i);
    antlr4::tree::TerminalNode *TOKEN_EXISTS();
    antlr4::tree::TerminalNode *TOKEN_BANG();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TermContext* term();

  class  Sort_symbol_declContext : public antlr4::ParserRuleContext {
  public:
    Sort_symbol_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *NUMERAL();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sort_symbol_declContext* sort_symbol_decl();

  class  Meta_spec_constantContext : public antlr4::ParserRuleContext {
  public:
    Meta_spec_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TOKEN_NUMERAL();
    antlr4::tree::TerminalNode *TOKEN_DECIMAL();
    antlr4::tree::TerminalNode *TOKEN_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Meta_spec_constantContext* meta_spec_constant();

  class  Fun_symbol_declContext : public antlr4::ParserRuleContext {
  public:
    Fun_symbol_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    Spec_constantContext *spec_constant();
    std::vector<SortContext *> sort();
    SortContext* sort(size_t i);
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    Meta_spec_constantContext *meta_spec_constant();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fun_symbol_declContext* fun_symbol_decl();

  class  Par_fun_symbol_declContext : public antlr4::ParserRuleContext {
  public:
    Par_fun_symbol_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Fun_symbol_declContext *fun_symbol_decl();
    std::vector<antlr4::tree::TerminalNode *> OpenPar();
    antlr4::tree::TerminalNode* OpenPar(size_t i);
    antlr4::tree::TerminalNode *TOKEN_PAR();
    std::vector<antlr4::tree::TerminalNode *> ClosePar();
    antlr4::tree::TerminalNode* ClosePar(size_t i);
    IdentifierContext *identifier();
    std::vector<SymbolContext *> symbol();
    SymbolContext* symbol(size_t i);
    std::vector<SortContext *> sort();
    SortContext* sort(size_t i);
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Par_fun_symbol_declContext* par_fun_symbol_decl();

  class  Theory_declContext : public antlr4::ParserRuleContext {
  public:
    Theory_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *SYM_THEORY();
    antlr4::tree::TerminalNode *ClosePar();
    SymbolContext *symbol();
    std::vector<Theory_attributeContext *> theory_attribute();
    Theory_attributeContext* theory_attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Theory_declContext* theory_decl();

  class  Theory_attributeContext : public antlr4::ParserRuleContext {
  public:
    Theory_attributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SORTS();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<Sort_symbol_declContext *> sort_symbol_decl();
    Sort_symbol_declContext* sort_symbol_decl(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_FUNS();
    std::vector<Par_fun_symbol_declContext *> par_fun_symbol_decl();
    Par_fun_symbol_declContext* par_fun_symbol_decl(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_SORTS_DESCRIPTION();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *KEYWORD_FUNS_DESCRIPTION();
    antlr4::tree::TerminalNode *KEYWORD_DEFINITION();
    antlr4::tree::TerminalNode *KEYWORD_VALUES();
    antlr4::tree::TerminalNode *KEYWORD_NOTES();
    AttributeContext *attribute();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Theory_attributeContext* theory_attribute();

  class  Logic_attributeContext : public antlr4::ParserRuleContext {
  public:
    Logic_attributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_THEORIES();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<SymbolContext *> symbol();
    SymbolContext* symbol(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_LANGUAGE();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *KEYWORD_EXTENSIONS();
    antlr4::tree::TerminalNode *KEYWORD_VALUES();
    antlr4::tree::TerminalNode *KEYWORD_NOTES();
    AttributeContext *attribute();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Logic_attributeContext* logic_attribute();

  class  LogicContext : public antlr4::ParserRuleContext {
  public:
    LogicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *SYM_LOGIC();
    SymbolContext *symbol();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<Logic_attributeContext *> logic_attribute();
    Logic_attributeContext* logic_attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicContext* logic();

  class  B_valueContext : public antlr4::ParserRuleContext {
  public:
    B_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYM_TRUE();
    antlr4::tree::TerminalNode *SYM_FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  B_valueContext* b_value();

  class  OptionContext : public antlr4::ParserRuleContext {
  public:
    OptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_PRINT_SUCCESS();
    B_valueContext *b_value();
    antlr4::tree::TerminalNode *KEYWORD_EXPAND_DEFINITIONS();
    antlr4::tree::TerminalNode *KEYWORD_INTERACTIVE_MODE();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_PROOFS();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_UNSAT_CORES();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_MODELS();
    antlr4::tree::TerminalNode *KEYWORD_PRODUCE_ASSIGNMENTS();
    antlr4::tree::TerminalNode *KEYWORD_REGULAR_OUTPUT_CHANNEL();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL();
    antlr4::tree::TerminalNode *KEYWORD_RANDOM_SEED();
    antlr4::tree::TerminalNode *NUMERAL();
    antlr4::tree::TerminalNode *KEYWORD_VERBOSITY();
    AttributeContext *attribute();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptionContext* option();

  class  Info_flagContext : public antlr4::ParserRuleContext {
  public:
    Info_flagContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ERROR_BEHAVIOR();
    antlr4::tree::TerminalNode *KEYWORD_NAME();
    antlr4::tree::TerminalNode *KEYWORD_AUTHORS();
    antlr4::tree::TerminalNode *KEYWORD_VERSION();
    antlr4::tree::TerminalNode *KEYWORD_STATUS();
    antlr4::tree::TerminalNode *KEYWORD_REASON_UNKNOWN();
    KeywordContext *keyword();
    antlr4::tree::TerminalNode *KEYWORD_ALL_STATISTICS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Info_flagContext* info_flag();

  class  CommandContext : public antlr4::ParserRuleContext {
  public:
    CommandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> OpenPar();
    antlr4::tree::TerminalNode* OpenPar(size_t i);
    antlr4::tree::TerminalNode *TOKEN_CMD_SET_LOGIC();
    std::vector<SymbolContext *> symbol();
    SymbolContext* symbol(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ClosePar();
    antlr4::tree::TerminalNode* ClosePar(size_t i);
    antlr4::tree::TerminalNode *TOKEN_CMD_SET_OPTION();
    OptionContext *option();
    antlr4::tree::TerminalNode *TOKEN_CMD_SET_INFO();
    AttributeContext *attribute();
    antlr4::tree::TerminalNode *TOKEN_CMD_DECLARE_SORT();
    antlr4::tree::TerminalNode *NUMERAL();
    antlr4::tree::TerminalNode *TOKEN_CMD_DEFINE_SORT();
    std::vector<SortContext *> sort();
    SortContext* sort(size_t i);
    antlr4::tree::TerminalNode *TOKEN_CMD_DECLARE_FUN();
    antlr4::tree::TerminalNode *TOKEN_CMD_DEFINE_FUN();
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    std::vector<Sorted_varContext *> sorted_var();
    Sorted_varContext* sorted_var(size_t i);
    antlr4::tree::TerminalNode *TOKEN_CMD_PUSH();
    antlr4::tree::TerminalNode *TOKEN_CMD_POP();
    antlr4::tree::TerminalNode *TOKEN_CMD_ASSERT();
    antlr4::tree::TerminalNode *TOKEN_CMD_CHECK_SAT();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_ASSERTIONS();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_PROOF();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_UNSAT_CORE();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_VALUE();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_ASSIGNMENT();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_OPTION();
    KeywordContext *keyword();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_INFO();
    Info_flagContext *info_flag();
    antlr4::tree::TerminalNode *TOKEN_CMD_EXIT();
    antlr4::tree::TerminalNode *TOKEN_CMD_GET_MODEL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommandContext* command();

  class  ScriptContext : public antlr4::ParserRuleContext {
  public:
    ScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CommandContext *> command();
    CommandContext* command(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptContext* script();

  class  Gen_responseContext : public antlr4::ParserRuleContext {
  public:
    Gen_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYM_UNSUPPORTED();
    antlr4::tree::TerminalNode *SYM_SUCCESS();
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *SYM_ERROR();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *ClosePar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Gen_responseContext* gen_response();

  class  Error_behaviorContext : public antlr4::ParserRuleContext {
  public:
    Error_behaviorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYM_IMMEDIATE_EXIT();
    antlr4::tree::TerminalNode *SYM_CONTINUED_EXECUTION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Error_behaviorContext* error_behavior();

  class  Reason_unknownContext : public antlr4::ParserRuleContext {
  public:
    Reason_unknownContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYM_MEMOUT();
    antlr4::tree::TerminalNode *SYM_INCOMPLETE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Reason_unknownContext* reason_unknown();

  class  StatusContext : public antlr4::ParserRuleContext {
  public:
    StatusContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYM_SAT();
    antlr4::tree::TerminalNode *SYM_UNSAT();
    antlr4::tree::TerminalNode *SYM_UNKNOWN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatusContext* status();

  class  Info_responseContext : public antlr4::ParserRuleContext {
  public:
    Info_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ERROR_BEHAVIOR();
    Error_behaviorContext *error_behavior();
    antlr4::tree::TerminalNode *KEYWORD_NAME();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *KEYWORD_AUTHORS();
    antlr4::tree::TerminalNode *KEYWORD_VERSION();
    antlr4::tree::TerminalNode *KEYWORD_REASON_UNKNOWN();
    Reason_unknownContext *reason_unknown();
    AttributeContext *attribute();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Info_responseContext* info_response();

  class  Get_info_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_info_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<Info_responseContext *> info_response();
    Info_responseContext* info_response(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_info_responseContext* get_info_response();

  class  Check_sat_responseContext : public antlr4::ParserRuleContext {
  public:
    Check_sat_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatusContext *status();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Check_sat_responseContext* check_sat_response();

  class  Get_assertions_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_assertions_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<TermContext *> term();
    TermContext* term(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_assertions_responseContext* get_assertions_response();

  class  ProofContext : public antlr4::ParserRuleContext {
  public:
    ProofContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    S_exprContext *s_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProofContext* proof();

  class  Get_proof_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_proof_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProofContext *proof();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_proof_responseContext* get_proof_response();

  class  Get_unsat_core_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_unsat_core_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<SymbolContext *> symbol();
    SymbolContext* symbol(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_unsat_core_responseContext* get_unsat_core_response();

  class  Valuation_pairContext : public antlr4::ParserRuleContext {
  public:
    Valuation_pairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    antlr4::tree::TerminalNode *ClosePar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Valuation_pairContext* valuation_pair();

  class  Get_value_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_value_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<Valuation_pairContext *> valuation_pair();
    Valuation_pairContext* valuation_pair(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_value_responseContext* get_value_response();

  class  T_valuation_pairContext : public antlr4::ParserRuleContext {
  public:
    T_valuation_pairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    SymbolContext *symbol();
    B_valueContext *b_value();
    antlr4::tree::TerminalNode *ClosePar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  T_valuation_pairContext* t_valuation_pair();

  class  Get_assignment_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_assignment_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OpenPar();
    antlr4::tree::TerminalNode *ClosePar();
    std::vector<T_valuation_pairContext *> t_valuation_pair();
    T_valuation_pairContext* t_valuation_pair(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_assignment_responseContext* get_assignment_response();

  class  Get_option_responseContext : public antlr4::ParserRuleContext {
  public:
    Get_option_responseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Attribute_valueContext *attribute_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Get_option_responseContext* get_option_response();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;

  /* private parser declarations section */

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace antlrcpptest
