/* parser/listener/visitor header section */

// Generated from SMTLIB2Parser.g4 by ANTLR 4.7

/* parser precinclude section */

#include "SMTLIB2ParserListener.h"
#include "SMTLIB2ParserVisitor.h"

#include "SMTLIB2Parser.h"


/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


using namespace antlrcpp;
using namespace antlrcpptest;
using namespace antlr4;

SMTLIB2Parser::SMTLIB2Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SMTLIB2Parser::~SMTLIB2Parser() {
  delete _interpreter;
}

std::string SMTLIB2Parser::getGrammarFileName() const {
  return "SMTLIB2Parser.g4";
}

const std::vector<std::string>& SMTLIB2Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SMTLIB2Parser::getVocabulary() const {
  return _vocabulary;
}

/* parser definitions section */

//----------------- SymbolContext ------------------------------------------------------------------

SMTLIB2Parser::SymbolContext::SymbolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SIMPLE_SYM() {
  return getToken(SMTLIB2Parser::SIMPLE_SYM, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_AND() {
  return getToken(SMTLIB2Parser::SYM_AND, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_OR() {
  return getToken(SMTLIB2Parser::SYM_OR, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_NOT() {
  return getToken(SMTLIB2Parser::SYM_NOT, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::QUOTED_SYM() {
  return getToken(SMTLIB2Parser::QUOTED_SYM, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_BOOL() {
  return getToken(SMTLIB2Parser::SYM_BOOL, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_CONTINUED_EXECUTION() {
  return getToken(SMTLIB2Parser::SYM_CONTINUED_EXECUTION, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_ERROR() {
  return getToken(SMTLIB2Parser::SYM_ERROR, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_FALSE() {
  return getToken(SMTLIB2Parser::SYM_FALSE, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_IMMEDIATE_EXIT() {
  return getToken(SMTLIB2Parser::SYM_IMMEDIATE_EXIT, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_INCOMPLETE() {
  return getToken(SMTLIB2Parser::SYM_INCOMPLETE, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_LOGIC() {
  return getToken(SMTLIB2Parser::SYM_LOGIC, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_MEMOUT() {
  return getToken(SMTLIB2Parser::SYM_MEMOUT, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_SAT() {
  return getToken(SMTLIB2Parser::SYM_SAT, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_SUCCESS() {
  return getToken(SMTLIB2Parser::SYM_SUCCESS, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_THEORY() {
  return getToken(SMTLIB2Parser::SYM_THEORY, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_TRUE() {
  return getToken(SMTLIB2Parser::SYM_TRUE, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_UNKNOWN() {
  return getToken(SMTLIB2Parser::SYM_UNKNOWN, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_UNSAT() {
  return getToken(SMTLIB2Parser::SYM_UNSAT, 0);
}

tree::TerminalNode* SMTLIB2Parser::SymbolContext::SYM_UNSUPPORTED() {
  return getToken(SMTLIB2Parser::SYM_UNSUPPORTED, 0);
}


size_t SMTLIB2Parser::SymbolContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleSymbol;
}

void SMTLIB2Parser::SymbolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSymbol(this);
}

void SMTLIB2Parser::SymbolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSymbol(this);
}


antlrcpp::Any SMTLIB2Parser::SymbolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitSymbol(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::symbol() {
  SymbolContext *_localctx = _tracker.createInstance<SymbolContext>(_ctx, getState());
  enterRule(_localctx, 0, SMTLIB2Parser::RuleSymbol);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
      | (1ULL << SMTLIB2Parser::SYM_OR)
      | (1ULL << SMTLIB2Parser::SYM_NOT)
      | (1ULL << SMTLIB2Parser::SYM_BOOL)
      | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
      | (1ULL << SMTLIB2Parser::SYM_ERROR)
      | (1ULL << SMTLIB2Parser::SYM_FALSE)
      | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
      | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
      | (1ULL << SMTLIB2Parser::SYM_LOGIC)
      | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
      | (1ULL << SMTLIB2Parser::SYM_SAT)
      | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
      | (1ULL << SMTLIB2Parser::SYM_THEORY)
      | (1ULL << SMTLIB2Parser::SYM_TRUE)
      | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
      | (1ULL << SMTLIB2Parser::SYM_UNSAT)
      | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || _la == SMTLIB2Parser::SIMPLE_SYM

    || _la == SMTLIB2Parser::QUOTED_SYM)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordContext ------------------------------------------------------------------

SMTLIB2Parser::KeywordContext::KeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_TOKEN() {
  return getToken(SMTLIB2Parser::KEYWORD_TOKEN, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_ALL_STATISTICS() {
  return getToken(SMTLIB2Parser::KEYWORD_ALL_STATISTICS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_AUTHORS() {
  return getToken(SMTLIB2Parser::KEYWORD_AUTHORS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_AXIOMS() {
  return getToken(SMTLIB2Parser::KEYWORD_AXIOMS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_CHAINABLE() {
  return getToken(SMTLIB2Parser::KEYWORD_CHAINABLE, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_DEFINITION() {
  return getToken(SMTLIB2Parser::KEYWORD_DEFINITION, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL() {
  return getToken(SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_ERROR_BEHAVIOR() {
  return getToken(SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_EXPAND_DEFINITIONS() {
  return getToken(SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_EXTENSIONS() {
  return getToken(SMTLIB2Parser::KEYWORD_EXTENSIONS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_FUNS() {
  return getToken(SMTLIB2Parser::KEYWORD_FUNS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_FUNS_DESCRIPTION() {
  return getToken(SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_INTERACTIVE_MODE() {
  return getToken(SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_LANGUAGE() {
  return getToken(SMTLIB2Parser::KEYWORD_LANGUAGE, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_LEFT_ASSOC() {
  return getToken(SMTLIB2Parser::KEYWORD_LEFT_ASSOC, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_NAME() {
  return getToken(SMTLIB2Parser::KEYWORD_NAME, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_NAMED() {
  return getToken(SMTLIB2Parser::KEYWORD_NAMED, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_NOTES() {
  return getToken(SMTLIB2Parser::KEYWORD_NOTES, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_PRINT_SUCCESS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRINT_SUCCESS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_PRODUCE_ASSIGNMENTS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_PRODUCE_MODELS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_MODELS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_PRODUCE_PROOFS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_PRODUCE_UNSAT_CORES() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_RANDOM_SEED() {
  return getToken(SMTLIB2Parser::KEYWORD_RANDOM_SEED, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_REASON_UNKNOWN() {
  return getToken(SMTLIB2Parser::KEYWORD_REASON_UNKNOWN, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_REGULAR_OUTPUT_CHANNEL() {
  return getToken(SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_RIGHT_ASSOC() {
  return getToken(SMTLIB2Parser::KEYWORD_RIGHT_ASSOC, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_SORTS() {
  return getToken(SMTLIB2Parser::KEYWORD_SORTS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_SORTS_DESCRIPTION() {
  return getToken(SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_STATUS() {
  return getToken(SMTLIB2Parser::KEYWORD_STATUS, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_THEORIES() {
  return getToken(SMTLIB2Parser::KEYWORD_THEORIES, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_VALUES() {
  return getToken(SMTLIB2Parser::KEYWORD_VALUES, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_VERBOSITY() {
  return getToken(SMTLIB2Parser::KEYWORD_VERBOSITY, 0);
}

tree::TerminalNode* SMTLIB2Parser::KeywordContext::KEYWORD_VERSION() {
  return getToken(SMTLIB2Parser::KEYWORD_VERSION, 0);
}


size_t SMTLIB2Parser::KeywordContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleKeyword;
}

void SMTLIB2Parser::KeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword(this);
}

void SMTLIB2Parser::KeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword(this);
}


antlrcpp::Any SMTLIB2Parser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::KeywordContext* SMTLIB2Parser::keyword() {
  KeywordContext *_localctx = _tracker.createInstance<KeywordContext>(_ctx, getState());
  enterRule(_localctx, 2, SMTLIB2Parser::RuleKeyword);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
      | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
      | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
      | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
      | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
      | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
      | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
      | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
      | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Spec_constantContext ------------------------------------------------------------------

SMTLIB2Parser::Spec_constantContext::Spec_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Spec_constantContext::NUMERAL() {
  return getToken(SMTLIB2Parser::NUMERAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::Spec_constantContext::DECIMAL() {
  return getToken(SMTLIB2Parser::DECIMAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::Spec_constantContext::HEXADECIMAL() {
  return getToken(SMTLIB2Parser::HEXADECIMAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::Spec_constantContext::BINARY() {
  return getToken(SMTLIB2Parser::BINARY, 0);
}

tree::TerminalNode* SMTLIB2Parser::Spec_constantContext::STRING() {
  return getToken(SMTLIB2Parser::STRING, 0);
}


size_t SMTLIB2Parser::Spec_constantContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleSpec_constant;
}

void SMTLIB2Parser::Spec_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpec_constant(this);
}

void SMTLIB2Parser::Spec_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpec_constant(this);
}


antlrcpp::Any SMTLIB2Parser::Spec_constantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitSpec_constant(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Spec_constantContext* SMTLIB2Parser::spec_constant() {
  Spec_constantContext *_localctx = _tracker.createInstance<Spec_constantContext>(_ctx, getState());
  enterRule(_localctx, 4, SMTLIB2Parser::RuleSpec_constant);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    _la = _input->LA(1);
    if (!(((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (SMTLIB2Parser::NUMERAL - 82))
      | (1ULL << (SMTLIB2Parser::DECIMAL - 82))
      | (1ULL << (SMTLIB2Parser::HEXADECIMAL - 82))
      | (1ULL << (SMTLIB2Parser::BINARY - 82))
      | (1ULL << (SMTLIB2Parser::STRING - 82)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_exprContext ------------------------------------------------------------------

SMTLIB2Parser::S_exprContext::S_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::Spec_constantContext* SMTLIB2Parser::S_exprContext::spec_constant() {
  return getRuleContext<SMTLIB2Parser::Spec_constantContext>(0);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::S_exprContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

SMTLIB2Parser::KeywordContext* SMTLIB2Parser::S_exprContext::keyword() {
  return getRuleContext<SMTLIB2Parser::KeywordContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::S_exprContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::S_exprContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::S_exprContext *> SMTLIB2Parser::S_exprContext::s_expr() {
  return getRuleContexts<SMTLIB2Parser::S_exprContext>();
}

SMTLIB2Parser::S_exprContext* SMTLIB2Parser::S_exprContext::s_expr(size_t i) {
  return getRuleContext<SMTLIB2Parser::S_exprContext>(i);
}


size_t SMTLIB2Parser::S_exprContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleS_expr;
}

void SMTLIB2Parser::S_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterS_expr(this);
}

void SMTLIB2Parser::S_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitS_expr(this);
}


antlrcpp::Any SMTLIB2Parser::S_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitS_expr(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::S_exprContext* SMTLIB2Parser::s_expr() {
  S_exprContext *_localctx = _tracker.createInstance<S_exprContext>(_ctx, getState());
  enterRule(_localctx, 6, SMTLIB2Parser::RuleS_expr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SMTLIB2Parser::NUMERAL:
      case SMTLIB2Parser::DECIMAL:
      case SMTLIB2Parser::HEXADECIMAL:
      case SMTLIB2Parser::BINARY:
      case SMTLIB2Parser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(88);
        spec_constant();
        break;
      }

      case SMTLIB2Parser::SYM_AND:
      case SMTLIB2Parser::SYM_OR:
      case SMTLIB2Parser::SYM_NOT:
      case SMTLIB2Parser::SYM_BOOL:
      case SMTLIB2Parser::SYM_CONTINUED_EXECUTION:
      case SMTLIB2Parser::SYM_ERROR:
      case SMTLIB2Parser::SYM_FALSE:
      case SMTLIB2Parser::SYM_IMMEDIATE_EXIT:
      case SMTLIB2Parser::SYM_INCOMPLETE:
      case SMTLIB2Parser::SYM_LOGIC:
      case SMTLIB2Parser::SYM_MEMOUT:
      case SMTLIB2Parser::SYM_SAT:
      case SMTLIB2Parser::SYM_SUCCESS:
      case SMTLIB2Parser::SYM_THEORY:
      case SMTLIB2Parser::SYM_TRUE:
      case SMTLIB2Parser::SYM_UNKNOWN:
      case SMTLIB2Parser::SYM_UNSAT:
      case SMTLIB2Parser::SYM_UNSUPPORTED:
      case SMTLIB2Parser::SIMPLE_SYM:
      case SMTLIB2Parser::QUOTED_SYM: {
        enterOuterAlt(_localctx, 2);
        setState(89);
        symbol();
        break;
      }

      case SMTLIB2Parser::KEYWORD_ALL_STATISTICS:
      case SMTLIB2Parser::KEYWORD_AUTHORS:
      case SMTLIB2Parser::KEYWORD_AXIOMS:
      case SMTLIB2Parser::KEYWORD_CHAINABLE:
      case SMTLIB2Parser::KEYWORD_DEFINITION:
      case SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL:
      case SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR:
      case SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS:
      case SMTLIB2Parser::KEYWORD_EXTENSIONS:
      case SMTLIB2Parser::KEYWORD_FUNS:
      case SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION:
      case SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE:
      case SMTLIB2Parser::KEYWORD_LANGUAGE:
      case SMTLIB2Parser::KEYWORD_LEFT_ASSOC:
      case SMTLIB2Parser::KEYWORD_NAME:
      case SMTLIB2Parser::KEYWORD_NAMED:
      case SMTLIB2Parser::KEYWORD_NOTES:
      case SMTLIB2Parser::KEYWORD_PRINT_SUCCESS:
      case SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS:
      case SMTLIB2Parser::KEYWORD_PRODUCE_MODELS:
      case SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS:
      case SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES:
      case SMTLIB2Parser::KEYWORD_RANDOM_SEED:
      case SMTLIB2Parser::KEYWORD_REASON_UNKNOWN:
      case SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL:
      case SMTLIB2Parser::KEYWORD_RIGHT_ASSOC:
      case SMTLIB2Parser::KEYWORD_SORTS:
      case SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION:
      case SMTLIB2Parser::KEYWORD_STATUS:
      case SMTLIB2Parser::KEYWORD_THEORIES:
      case SMTLIB2Parser::KEYWORD_VALUES:
      case SMTLIB2Parser::KEYWORD_VERBOSITY:
      case SMTLIB2Parser::KEYWORD_VERSION:
      case SMTLIB2Parser::KEYWORD_TOKEN: {
        enterOuterAlt(_localctx, 3);
        setState(90);
        keyword();
        break;
      }

      case SMTLIB2Parser::OpenPar: {
        enterOuterAlt(_localctx, 4);
        setState(91);
        match(SMTLIB2Parser::OpenPar);
        setState(95);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
          | (1ULL << SMTLIB2Parser::SYM_OR)
          | (1ULL << SMTLIB2Parser::SYM_NOT)
          | (1ULL << SMTLIB2Parser::SYM_BOOL)
          | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
          | (1ULL << SMTLIB2Parser::SYM_ERROR)
          | (1ULL << SMTLIB2Parser::SYM_FALSE)
          | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
          | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
          | (1ULL << SMTLIB2Parser::SYM_LOGIC)
          | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
          | (1ULL << SMTLIB2Parser::SYM_SAT)
          | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
          | (1ULL << SMTLIB2Parser::SYM_THEORY)
          | (1ULL << SMTLIB2Parser::SYM_TRUE)
          | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
          | (1ULL << SMTLIB2Parser::SYM_UNSAT)
          | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED)
          | (1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
          | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
          | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
          | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
          | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
          | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
          | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
          | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
          | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
          | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
          | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
          | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
          | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
          | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
          | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
          | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
          | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
          | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
          | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
          | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
          | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
          | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
          | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
          | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
          | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
          | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
          | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
          | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 82)) & ((1ULL << (SMTLIB2Parser::NUMERAL - 82))
          | (1ULL << (SMTLIB2Parser::DECIMAL - 82))
          | (1ULL << (SMTLIB2Parser::HEXADECIMAL - 82))
          | (1ULL << (SMTLIB2Parser::BINARY - 82))
          | (1ULL << (SMTLIB2Parser::STRING - 82))
          | (1ULL << (SMTLIB2Parser::SIMPLE_SYM - 82))
          | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 82))
          | (1ULL << (SMTLIB2Parser::KEYWORD_TOKEN - 82))
          | (1ULL << (SMTLIB2Parser::OpenPar - 82)))) != 0)) {
          setState(92);
          s_expr();
          setState(97);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(98);
        match(SMTLIB2Parser::ClosePar);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

SMTLIB2Parser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::IdentifierContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::IdentifierContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::IdentifierContext::TOKEN_UNDERSCORE() {
  return getToken(SMTLIB2Parser::TOKEN_UNDERSCORE, 0);
}

tree::TerminalNode* SMTLIB2Parser::IdentifierContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::IdentifierContext::NUMERAL() {
  return getTokens(SMTLIB2Parser::NUMERAL);
}

tree::TerminalNode* SMTLIB2Parser::IdentifierContext::NUMERAL(size_t i) {
  return getToken(SMTLIB2Parser::NUMERAL, i);
}


size_t SMTLIB2Parser::IdentifierContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleIdentifier;
}

void SMTLIB2Parser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void SMTLIB2Parser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


antlrcpp::Any SMTLIB2Parser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::IdentifierContext* SMTLIB2Parser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 8, SMTLIB2Parser::RuleIdentifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(112);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SMTLIB2Parser::SYM_AND:
      case SMTLIB2Parser::SYM_OR:
      case SMTLIB2Parser::SYM_NOT:
      case SMTLIB2Parser::SYM_BOOL:
      case SMTLIB2Parser::SYM_CONTINUED_EXECUTION:
      case SMTLIB2Parser::SYM_ERROR:
      case SMTLIB2Parser::SYM_FALSE:
      case SMTLIB2Parser::SYM_IMMEDIATE_EXIT:
      case SMTLIB2Parser::SYM_INCOMPLETE:
      case SMTLIB2Parser::SYM_LOGIC:
      case SMTLIB2Parser::SYM_MEMOUT:
      case SMTLIB2Parser::SYM_SAT:
      case SMTLIB2Parser::SYM_SUCCESS:
      case SMTLIB2Parser::SYM_THEORY:
      case SMTLIB2Parser::SYM_TRUE:
      case SMTLIB2Parser::SYM_UNKNOWN:
      case SMTLIB2Parser::SYM_UNSAT:
      case SMTLIB2Parser::SYM_UNSUPPORTED:
      case SMTLIB2Parser::SIMPLE_SYM:
      case SMTLIB2Parser::QUOTED_SYM: {
        enterOuterAlt(_localctx, 1);
        setState(101);
        symbol();
        break;
      }

      case SMTLIB2Parser::OpenPar: {
        enterOuterAlt(_localctx, 2);
        setState(102);
        match(SMTLIB2Parser::OpenPar);
        setState(103);
        match(SMTLIB2Parser::TOKEN_UNDERSCORE);
        setState(104);
        symbol();
        setState(106); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(105);
          match(SMTLIB2Parser::NUMERAL);
          setState(108); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == SMTLIB2Parser::NUMERAL);
        setState(110);
        match(SMTLIB2Parser::ClosePar);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SortContext ------------------------------------------------------------------

SMTLIB2Parser::SortContext::SortContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::IdentifierContext* SMTLIB2Parser::SortContext::identifier() {
  return getRuleContext<SMTLIB2Parser::IdentifierContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::SortContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::SortContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::SortContext *> SMTLIB2Parser::SortContext::sort() {
  return getRuleContexts<SMTLIB2Parser::SortContext>();
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::SortContext::sort(size_t i) {
  return getRuleContext<SMTLIB2Parser::SortContext>(i);
}


size_t SMTLIB2Parser::SortContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleSort;
}

void SMTLIB2Parser::SortContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSort(this);
}

void SMTLIB2Parser::SortContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSort(this);
}


antlrcpp::Any SMTLIB2Parser::SortContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitSort(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::sort() {
  SortContext *_localctx = _tracker.createInstance<SortContext>(_ctx, getState());
  enterRule(_localctx, 10, SMTLIB2Parser::RuleSort);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(124);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(114);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(115);
      match(SMTLIB2Parser::OpenPar);
      setState(116);
      identifier();
      setState(118); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(117);
        sort();
        setState(120); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 88) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 88)) & ((1ULL << (SMTLIB2Parser::SIMPLE_SYM - 88))
        | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 88))
        | (1ULL << (SMTLIB2Parser::OpenPar - 88)))) != 0));
      setState(122);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attribute_valueContext ------------------------------------------------------------------

SMTLIB2Parser::Attribute_valueContext::Attribute_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Attribute_valueContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

SMTLIB2Parser::Spec_constantContext* SMTLIB2Parser::Attribute_valueContext::spec_constant() {
  return getRuleContext<SMTLIB2Parser::Spec_constantContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Attribute_valueContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Attribute_valueContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::S_exprContext *> SMTLIB2Parser::Attribute_valueContext::s_expr() {
  return getRuleContexts<SMTLIB2Parser::S_exprContext>();
}

SMTLIB2Parser::S_exprContext* SMTLIB2Parser::Attribute_valueContext::s_expr(size_t i) {
  return getRuleContext<SMTLIB2Parser::S_exprContext>(i);
}


size_t SMTLIB2Parser::Attribute_valueContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleAttribute_value;
}

void SMTLIB2Parser::Attribute_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute_value(this);
}

void SMTLIB2Parser::Attribute_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute_value(this);
}


antlrcpp::Any SMTLIB2Parser::Attribute_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitAttribute_value(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Attribute_valueContext* SMTLIB2Parser::attribute_value() {
  Attribute_valueContext *_localctx = _tracker.createInstance<Attribute_valueContext>(_ctx, getState());
  enterRule(_localctx, 12, SMTLIB2Parser::RuleAttribute_value);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SMTLIB2Parser::SYM_AND:
      case SMTLIB2Parser::SYM_OR:
      case SMTLIB2Parser::SYM_NOT:
      case SMTLIB2Parser::SYM_BOOL:
      case SMTLIB2Parser::SYM_CONTINUED_EXECUTION:
      case SMTLIB2Parser::SYM_ERROR:
      case SMTLIB2Parser::SYM_FALSE:
      case SMTLIB2Parser::SYM_IMMEDIATE_EXIT:
      case SMTLIB2Parser::SYM_INCOMPLETE:
      case SMTLIB2Parser::SYM_LOGIC:
      case SMTLIB2Parser::SYM_MEMOUT:
      case SMTLIB2Parser::SYM_SAT:
      case SMTLIB2Parser::SYM_SUCCESS:
      case SMTLIB2Parser::SYM_THEORY:
      case SMTLIB2Parser::SYM_TRUE:
      case SMTLIB2Parser::SYM_UNKNOWN:
      case SMTLIB2Parser::SYM_UNSAT:
      case SMTLIB2Parser::SYM_UNSUPPORTED:
      case SMTLIB2Parser::SIMPLE_SYM:
      case SMTLIB2Parser::QUOTED_SYM: {
        enterOuterAlt(_localctx, 1);
        setState(126);
        symbol();
        break;
      }

      case SMTLIB2Parser::NUMERAL:
      case SMTLIB2Parser::DECIMAL:
      case SMTLIB2Parser::HEXADECIMAL:
      case SMTLIB2Parser::BINARY:
      case SMTLIB2Parser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(127);
        spec_constant();
        break;
      }

      case SMTLIB2Parser::OpenPar: {
        enterOuterAlt(_localctx, 3);
        setState(128);
        match(SMTLIB2Parser::OpenPar);
        setState(132);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
          | (1ULL << SMTLIB2Parser::SYM_OR)
          | (1ULL << SMTLIB2Parser::SYM_NOT)
          | (1ULL << SMTLIB2Parser::SYM_BOOL)
          | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
          | (1ULL << SMTLIB2Parser::SYM_ERROR)
          | (1ULL << SMTLIB2Parser::SYM_FALSE)
          | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
          | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
          | (1ULL << SMTLIB2Parser::SYM_LOGIC)
          | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
          | (1ULL << SMTLIB2Parser::SYM_SAT)
          | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
          | (1ULL << SMTLIB2Parser::SYM_THEORY)
          | (1ULL << SMTLIB2Parser::SYM_TRUE)
          | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
          | (1ULL << SMTLIB2Parser::SYM_UNSAT)
          | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED)
          | (1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
          | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
          | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
          | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
          | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
          | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
          | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
          | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
          | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
          | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
          | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
          | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
          | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
          | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
          | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
          | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
          | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
          | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
          | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
          | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
          | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
          | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
          | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
          | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
          | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
          | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
          | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
          | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
          | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 82)) & ((1ULL << (SMTLIB2Parser::NUMERAL - 82))
          | (1ULL << (SMTLIB2Parser::DECIMAL - 82))
          | (1ULL << (SMTLIB2Parser::HEXADECIMAL - 82))
          | (1ULL << (SMTLIB2Parser::BINARY - 82))
          | (1ULL << (SMTLIB2Parser::STRING - 82))
          | (1ULL << (SMTLIB2Parser::SIMPLE_SYM - 82))
          | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 82))
          | (1ULL << (SMTLIB2Parser::KEYWORD_TOKEN - 82))
          | (1ULL << (SMTLIB2Parser::OpenPar - 82)))) != 0)) {
          setState(129);
          s_expr();
          setState(134);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(135);
        match(SMTLIB2Parser::ClosePar);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeContext ------------------------------------------------------------------

SMTLIB2Parser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::KeywordContext* SMTLIB2Parser::AttributeContext::keyword() {
  return getRuleContext<SMTLIB2Parser::KeywordContext>(0);
}

SMTLIB2Parser::Attribute_valueContext* SMTLIB2Parser::AttributeContext::attribute_value() {
  return getRuleContext<SMTLIB2Parser::Attribute_valueContext>(0);
}


size_t SMTLIB2Parser::AttributeContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleAttribute;
}

void SMTLIB2Parser::AttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute(this);
}

void SMTLIB2Parser::AttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute(this);
}


antlrcpp::Any SMTLIB2Parser::AttributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitAttribute(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 14, SMTLIB2Parser::RuleAttribute);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(138);
      keyword();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(139);
      keyword();
      setState(140);
      attribute_value();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Qual_identifierContext ------------------------------------------------------------------

SMTLIB2Parser::Qual_identifierContext::Qual_identifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::IdentifierContext* SMTLIB2Parser::Qual_identifierContext::identifier() {
  return getRuleContext<SMTLIB2Parser::IdentifierContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Qual_identifierContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Qual_identifierContext::TOKEN_AS() {
  return getToken(SMTLIB2Parser::TOKEN_AS, 0);
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::Qual_identifierContext::sort() {
  return getRuleContext<SMTLIB2Parser::SortContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Qual_identifierContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}


size_t SMTLIB2Parser::Qual_identifierContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleQual_identifier;
}

void SMTLIB2Parser::Qual_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQual_identifier(this);
}

void SMTLIB2Parser::Qual_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQual_identifier(this);
}


antlrcpp::Any SMTLIB2Parser::Qual_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitQual_identifier(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Qual_identifierContext* SMTLIB2Parser::qual_identifier() {
  Qual_identifierContext *_localctx = _tracker.createInstance<Qual_identifierContext>(_ctx, getState());
  enterRule(_localctx, 16, SMTLIB2Parser::RuleQual_identifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(144);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(145);
      match(SMTLIB2Parser::OpenPar);
      setState(146);
      match(SMTLIB2Parser::TOKEN_AS);
      setState(147);
      identifier();
      setState(148);
      sort();
      setState(149);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_bindingContext ------------------------------------------------------------------

SMTLIB2Parser::Var_bindingContext::Var_bindingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Var_bindingContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Var_bindingContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

SMTLIB2Parser::TermContext* SMTLIB2Parser::Var_bindingContext::term() {
  return getRuleContext<SMTLIB2Parser::TermContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Var_bindingContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}


size_t SMTLIB2Parser::Var_bindingContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleVar_binding;
}

void SMTLIB2Parser::Var_bindingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_binding(this);
}

void SMTLIB2Parser::Var_bindingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_binding(this);
}


antlrcpp::Any SMTLIB2Parser::Var_bindingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitVar_binding(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Var_bindingContext* SMTLIB2Parser::var_binding() {
  Var_bindingContext *_localctx = _tracker.createInstance<Var_bindingContext>(_ctx, getState());
  enterRule(_localctx, 18, SMTLIB2Parser::RuleVar_binding);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    match(SMTLIB2Parser::OpenPar);
    setState(154);
    symbol();
    setState(155);
    term();
    setState(156);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sorted_varContext ------------------------------------------------------------------

SMTLIB2Parser::Sorted_varContext::Sorted_varContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Sorted_varContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Sorted_varContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::Sorted_varContext::sort() {
  return getRuleContext<SMTLIB2Parser::SortContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Sorted_varContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}


size_t SMTLIB2Parser::Sorted_varContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleSorted_var;
}

void SMTLIB2Parser::Sorted_varContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSorted_var(this);
}

void SMTLIB2Parser::Sorted_varContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSorted_var(this);
}


antlrcpp::Any SMTLIB2Parser::Sorted_varContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitSorted_var(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Sorted_varContext* SMTLIB2Parser::sorted_var() {
  Sorted_varContext *_localctx = _tracker.createInstance<Sorted_varContext>(_ctx, getState());
  enterRule(_localctx, 20, SMTLIB2Parser::RuleSorted_var);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    match(SMTLIB2Parser::OpenPar);
    setState(159);
    symbol();
    setState(160);
    sort();
    setState(161);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

SMTLIB2Parser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::Spec_constantContext* SMTLIB2Parser::TermContext::spec_constant() {
  return getRuleContext<SMTLIB2Parser::Spec_constantContext>(0);
}

SMTLIB2Parser::Qual_identifierContext* SMTLIB2Parser::TermContext::qual_identifier() {
  return getRuleContext<SMTLIB2Parser::Qual_identifierContext>(0);
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::TermContext::OpenPar() {
  return getTokens(SMTLIB2Parser::OpenPar);
}

tree::TerminalNode* SMTLIB2Parser::TermContext::OpenPar(size_t i) {
  return getToken(SMTLIB2Parser::OpenPar, i);
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::TermContext::ClosePar() {
  return getTokens(SMTLIB2Parser::ClosePar);
}

tree::TerminalNode* SMTLIB2Parser::TermContext::ClosePar(size_t i) {
  return getToken(SMTLIB2Parser::ClosePar, i);
}

std::vector<SMTLIB2Parser::TermContext *> SMTLIB2Parser::TermContext::term() {
  return getRuleContexts<SMTLIB2Parser::TermContext>();
}

SMTLIB2Parser::TermContext* SMTLIB2Parser::TermContext::term(size_t i) {
  return getRuleContext<SMTLIB2Parser::TermContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::TermContext::TOKEN_LET() {
  return getToken(SMTLIB2Parser::TOKEN_LET, 0);
}

std::vector<SMTLIB2Parser::Var_bindingContext *> SMTLIB2Parser::TermContext::var_binding() {
  return getRuleContexts<SMTLIB2Parser::Var_bindingContext>();
}

SMTLIB2Parser::Var_bindingContext* SMTLIB2Parser::TermContext::var_binding(size_t i) {
  return getRuleContext<SMTLIB2Parser::Var_bindingContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::TermContext::TOKEN_FORALL() {
  return getToken(SMTLIB2Parser::TOKEN_FORALL, 0);
}

std::vector<SMTLIB2Parser::Sorted_varContext *> SMTLIB2Parser::TermContext::sorted_var() {
  return getRuleContexts<SMTLIB2Parser::Sorted_varContext>();
}

SMTLIB2Parser::Sorted_varContext* SMTLIB2Parser::TermContext::sorted_var(size_t i) {
  return getRuleContext<SMTLIB2Parser::Sorted_varContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::TermContext::TOKEN_EXISTS() {
  return getToken(SMTLIB2Parser::TOKEN_EXISTS, 0);
}

tree::TerminalNode* SMTLIB2Parser::TermContext::TOKEN_BANG() {
  return getToken(SMTLIB2Parser::TOKEN_BANG, 0);
}

std::vector<SMTLIB2Parser::AttributeContext *> SMTLIB2Parser::TermContext::attribute() {
  return getRuleContexts<SMTLIB2Parser::AttributeContext>();
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::TermContext::attribute(size_t i) {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(i);
}


size_t SMTLIB2Parser::TermContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleTerm;
}

void SMTLIB2Parser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void SMTLIB2Parser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}


antlrcpp::Any SMTLIB2Parser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::TermContext* SMTLIB2Parser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 22, SMTLIB2Parser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(220);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(163);
      spec_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(164);
      qual_identifier();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(165);
      match(SMTLIB2Parser::OpenPar);
      setState(166);
      qual_identifier();
      setState(168); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(167);
        term();
        setState(170); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (SMTLIB2Parser::NUMERAL - 82))
        | (1ULL << (SMTLIB2Parser::DECIMAL - 82))
        | (1ULL << (SMTLIB2Parser::HEXADECIMAL - 82))
        | (1ULL << (SMTLIB2Parser::BINARY - 82))
        | (1ULL << (SMTLIB2Parser::STRING - 82))
        | (1ULL << (SMTLIB2Parser::SIMPLE_SYM - 82))
        | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 82))
        | (1ULL << (SMTLIB2Parser::OpenPar - 82)))) != 0));
      setState(172);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(174);
      match(SMTLIB2Parser::OpenPar);
      setState(175);
      match(SMTLIB2Parser::TOKEN_LET);
      setState(176);
      match(SMTLIB2Parser::OpenPar);
      setState(178); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(177);
        var_binding();
        setState(180); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SMTLIB2Parser::OpenPar);
      setState(182);
      match(SMTLIB2Parser::ClosePar);
      setState(183);
      term();
      setState(184);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(186);
      match(SMTLIB2Parser::OpenPar);
      setState(187);
      match(SMTLIB2Parser::TOKEN_FORALL);
      setState(188);
      match(SMTLIB2Parser::OpenPar);
      setState(190); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(189);
        sorted_var();
        setState(192); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SMTLIB2Parser::OpenPar);
      setState(194);
      match(SMTLIB2Parser::ClosePar);
      setState(195);
      term();
      setState(196);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(198);
      match(SMTLIB2Parser::OpenPar);
      setState(199);
      match(SMTLIB2Parser::TOKEN_EXISTS);
      setState(200);
      match(SMTLIB2Parser::OpenPar);
      setState(202); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(201);
        sorted_var();
        setState(204); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SMTLIB2Parser::OpenPar);
      setState(206);
      match(SMTLIB2Parser::ClosePar);
      setState(207);
      term();
      setState(208);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(210);
      match(SMTLIB2Parser::OpenPar);
      setState(211);
      match(SMTLIB2Parser::TOKEN_BANG);
      setState(212);
      term();
      setState(214); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(213);
        attribute();
        setState(216); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
        | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
        | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
        | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
        | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
        | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
        | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
        | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
        | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN);
      setState(218);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sort_symbol_declContext ------------------------------------------------------------------

SMTLIB2Parser::Sort_symbol_declContext::Sort_symbol_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Sort_symbol_declContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

SMTLIB2Parser::IdentifierContext* SMTLIB2Parser::Sort_symbol_declContext::identifier() {
  return getRuleContext<SMTLIB2Parser::IdentifierContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Sort_symbol_declContext::NUMERAL() {
  return getToken(SMTLIB2Parser::NUMERAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::Sort_symbol_declContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::AttributeContext *> SMTLIB2Parser::Sort_symbol_declContext::attribute() {
  return getRuleContexts<SMTLIB2Parser::AttributeContext>();
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::Sort_symbol_declContext::attribute(size_t i) {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(i);
}


size_t SMTLIB2Parser::Sort_symbol_declContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleSort_symbol_decl;
}

void SMTLIB2Parser::Sort_symbol_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSort_symbol_decl(this);
}

void SMTLIB2Parser::Sort_symbol_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSort_symbol_decl(this);
}


antlrcpp::Any SMTLIB2Parser::Sort_symbol_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitSort_symbol_decl(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Sort_symbol_declContext* SMTLIB2Parser::sort_symbol_decl() {
  Sort_symbol_declContext *_localctx = _tracker.createInstance<Sort_symbol_declContext>(_ctx, getState());
  enterRule(_localctx, 24, SMTLIB2Parser::RuleSort_symbol_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    match(SMTLIB2Parser::OpenPar);
    setState(223);
    identifier();
    setState(224);
    match(SMTLIB2Parser::NUMERAL);
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
      | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
      | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
      | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
      | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
      | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
      | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
      | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
      | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN) {
      setState(225);
      attribute();
      setState(230);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(231);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Meta_spec_constantContext ------------------------------------------------------------------

SMTLIB2Parser::Meta_spec_constantContext::Meta_spec_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Meta_spec_constantContext::TOKEN_NUMERAL() {
  return getToken(SMTLIB2Parser::TOKEN_NUMERAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::Meta_spec_constantContext::TOKEN_DECIMAL() {
  return getToken(SMTLIB2Parser::TOKEN_DECIMAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::Meta_spec_constantContext::TOKEN_STRING() {
  return getToken(SMTLIB2Parser::TOKEN_STRING, 0);
}


size_t SMTLIB2Parser::Meta_spec_constantContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleMeta_spec_constant;
}

void SMTLIB2Parser::Meta_spec_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMeta_spec_constant(this);
}

void SMTLIB2Parser::Meta_spec_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMeta_spec_constant(this);
}


antlrcpp::Any SMTLIB2Parser::Meta_spec_constantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitMeta_spec_constant(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Meta_spec_constantContext* SMTLIB2Parser::meta_spec_constant() {
  Meta_spec_constantContext *_localctx = _tracker.createInstance<Meta_spec_constantContext>(_ctx, getState());
  enterRule(_localctx, 26, SMTLIB2Parser::RuleMeta_spec_constant);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::TOKEN_DECIMAL)
      | (1ULL << SMTLIB2Parser::TOKEN_NUMERAL)
      | (1ULL << SMTLIB2Parser::TOKEN_STRING))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fun_symbol_declContext ------------------------------------------------------------------

SMTLIB2Parser::Fun_symbol_declContext::Fun_symbol_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Fun_symbol_declContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

SMTLIB2Parser::Spec_constantContext* SMTLIB2Parser::Fun_symbol_declContext::spec_constant() {
  return getRuleContext<SMTLIB2Parser::Spec_constantContext>(0);
}

std::vector<SMTLIB2Parser::SortContext *> SMTLIB2Parser::Fun_symbol_declContext::sort() {
  return getRuleContexts<SMTLIB2Parser::SortContext>();
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::Fun_symbol_declContext::sort(size_t i) {
  return getRuleContext<SMTLIB2Parser::SortContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::Fun_symbol_declContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::AttributeContext *> SMTLIB2Parser::Fun_symbol_declContext::attribute() {
  return getRuleContexts<SMTLIB2Parser::AttributeContext>();
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::Fun_symbol_declContext::attribute(size_t i) {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(i);
}

SMTLIB2Parser::Meta_spec_constantContext* SMTLIB2Parser::Fun_symbol_declContext::meta_spec_constant() {
  return getRuleContext<SMTLIB2Parser::Meta_spec_constantContext>(0);
}

SMTLIB2Parser::IdentifierContext* SMTLIB2Parser::Fun_symbol_declContext::identifier() {
  return getRuleContext<SMTLIB2Parser::IdentifierContext>(0);
}


size_t SMTLIB2Parser::Fun_symbol_declContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleFun_symbol_decl;
}

void SMTLIB2Parser::Fun_symbol_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFun_symbol_decl(this);
}

void SMTLIB2Parser::Fun_symbol_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFun_symbol_decl(this);
}


antlrcpp::Any SMTLIB2Parser::Fun_symbol_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitFun_symbol_decl(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Fun_symbol_declContext* SMTLIB2Parser::fun_symbol_decl() {
  Fun_symbol_declContext *_localctx = _tracker.createInstance<Fun_symbol_declContext>(_ctx, getState());
  enterRule(_localctx, 28, SMTLIB2Parser::RuleFun_symbol_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(272);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(235);
      match(SMTLIB2Parser::OpenPar);
      setState(236);
      spec_constant();
      setState(237);
      sort();
      setState(241);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
        | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
        | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
        | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
        | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
        | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
        | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
        | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
        | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN) {
        setState(238);
        attribute();
        setState(243);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(244);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(246);
      match(SMTLIB2Parser::OpenPar);
      setState(247);
      meta_spec_constant();
      setState(248);
      sort();
      setState(252);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
        | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
        | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
        | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
        | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
        | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
        | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
        | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
        | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN) {
        setState(249);
        attribute();
        setState(254);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(255);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(257);
      match(SMTLIB2Parser::OpenPar);
      setState(258);
      identifier();
      setState(260); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(259);
        sort();
        setState(262); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 88) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 88)) & ((1ULL << (SMTLIB2Parser::SIMPLE_SYM - 88))
        | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 88))
        | (1ULL << (SMTLIB2Parser::OpenPar - 88)))) != 0));
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
        | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
        | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
        | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
        | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
        | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
        | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
        | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
        | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN) {
        setState(264);
        attribute();
        setState(269);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(270);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Par_fun_symbol_declContext ------------------------------------------------------------------

SMTLIB2Parser::Par_fun_symbol_declContext::Par_fun_symbol_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::Fun_symbol_declContext* SMTLIB2Parser::Par_fun_symbol_declContext::fun_symbol_decl() {
  return getRuleContext<SMTLIB2Parser::Fun_symbol_declContext>(0);
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::Par_fun_symbol_declContext::OpenPar() {
  return getTokens(SMTLIB2Parser::OpenPar);
}

tree::TerminalNode* SMTLIB2Parser::Par_fun_symbol_declContext::OpenPar(size_t i) {
  return getToken(SMTLIB2Parser::OpenPar, i);
}

tree::TerminalNode* SMTLIB2Parser::Par_fun_symbol_declContext::TOKEN_PAR() {
  return getToken(SMTLIB2Parser::TOKEN_PAR, 0);
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::Par_fun_symbol_declContext::ClosePar() {
  return getTokens(SMTLIB2Parser::ClosePar);
}

tree::TerminalNode* SMTLIB2Parser::Par_fun_symbol_declContext::ClosePar(size_t i) {
  return getToken(SMTLIB2Parser::ClosePar, i);
}

SMTLIB2Parser::IdentifierContext* SMTLIB2Parser::Par_fun_symbol_declContext::identifier() {
  return getRuleContext<SMTLIB2Parser::IdentifierContext>(0);
}

std::vector<SMTLIB2Parser::SymbolContext *> SMTLIB2Parser::Par_fun_symbol_declContext::symbol() {
  return getRuleContexts<SMTLIB2Parser::SymbolContext>();
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Par_fun_symbol_declContext::symbol(size_t i) {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(i);
}

std::vector<SMTLIB2Parser::SortContext *> SMTLIB2Parser::Par_fun_symbol_declContext::sort() {
  return getRuleContexts<SMTLIB2Parser::SortContext>();
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::Par_fun_symbol_declContext::sort(size_t i) {
  return getRuleContext<SMTLIB2Parser::SortContext>(i);
}

std::vector<SMTLIB2Parser::AttributeContext *> SMTLIB2Parser::Par_fun_symbol_declContext::attribute() {
  return getRuleContexts<SMTLIB2Parser::AttributeContext>();
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::Par_fun_symbol_declContext::attribute(size_t i) {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(i);
}


size_t SMTLIB2Parser::Par_fun_symbol_declContext::getRuleIndex() const {
  return SMTLIB2Parser::RulePar_fun_symbol_decl;
}

void SMTLIB2Parser::Par_fun_symbol_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPar_fun_symbol_decl(this);
}

void SMTLIB2Parser::Par_fun_symbol_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPar_fun_symbol_decl(this);
}


antlrcpp::Any SMTLIB2Parser::Par_fun_symbol_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitPar_fun_symbol_decl(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Par_fun_symbol_declContext* SMTLIB2Parser::par_fun_symbol_decl() {
  Par_fun_symbol_declContext *_localctx = _tracker.createInstance<Par_fun_symbol_declContext>(_ctx, getState());
  enterRule(_localctx, 30, SMTLIB2Parser::RulePar_fun_symbol_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(300);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(274);
      fun_symbol_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(275);
      match(SMTLIB2Parser::OpenPar);
      setState(276);
      match(SMTLIB2Parser::TOKEN_PAR);
      setState(277);
      match(SMTLIB2Parser::OpenPar);
      setState(279); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(278);
        symbol();
        setState(281); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || _la == SMTLIB2Parser::SIMPLE_SYM

      || _la == SMTLIB2Parser::QUOTED_SYM);
      setState(283);
      match(SMTLIB2Parser::ClosePar);
      setState(284);
      match(SMTLIB2Parser::OpenPar);
      setState(285);
      identifier();
      setState(287); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(286);
        sort();
        setState(289); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 88) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 88)) & ((1ULL << (SMTLIB2Parser::SIMPLE_SYM - 88))
        | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 88))
        | (1ULL << (SMTLIB2Parser::OpenPar - 88)))) != 0));
      setState(294);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
        | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
        | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
        | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
        | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
        | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
        | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
        | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
        | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
        | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
        | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
        | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
        | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
        | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
        | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
        | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
        | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
        | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN) {
        setState(291);
        attribute();
        setState(296);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(297);
      match(SMTLIB2Parser::ClosePar);
      setState(298);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Theory_declContext ------------------------------------------------------------------

SMTLIB2Parser::Theory_declContext::Theory_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Theory_declContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_declContext::SYM_THEORY() {
  return getToken(SMTLIB2Parser::SYM_THEORY, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_declContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Theory_declContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

std::vector<SMTLIB2Parser::Theory_attributeContext *> SMTLIB2Parser::Theory_declContext::theory_attribute() {
  return getRuleContexts<SMTLIB2Parser::Theory_attributeContext>();
}

SMTLIB2Parser::Theory_attributeContext* SMTLIB2Parser::Theory_declContext::theory_attribute(size_t i) {
  return getRuleContext<SMTLIB2Parser::Theory_attributeContext>(i);
}


size_t SMTLIB2Parser::Theory_declContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleTheory_decl;
}

void SMTLIB2Parser::Theory_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTheory_decl(this);
}

void SMTLIB2Parser::Theory_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTheory_decl(this);
}


antlrcpp::Any SMTLIB2Parser::Theory_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitTheory_decl(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Theory_declContext* SMTLIB2Parser::theory_decl() {
  Theory_declContext *_localctx = _tracker.createInstance<Theory_declContext>(_ctx, getState());
  enterRule(_localctx, 32, SMTLIB2Parser::RuleTheory_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
    match(SMTLIB2Parser::OpenPar);
    setState(303);
    match(SMTLIB2Parser::SYM_THEORY);
    setState(305);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
      | (1ULL << SMTLIB2Parser::SYM_OR)
      | (1ULL << SMTLIB2Parser::SYM_NOT)
      | (1ULL << SMTLIB2Parser::SYM_BOOL)
      | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
      | (1ULL << SMTLIB2Parser::SYM_ERROR)
      | (1ULL << SMTLIB2Parser::SYM_FALSE)
      | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
      | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
      | (1ULL << SMTLIB2Parser::SYM_LOGIC)
      | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
      | (1ULL << SMTLIB2Parser::SYM_SAT)
      | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
      | (1ULL << SMTLIB2Parser::SYM_THEORY)
      | (1ULL << SMTLIB2Parser::SYM_TRUE)
      | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
      | (1ULL << SMTLIB2Parser::SYM_UNSAT)
      | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || _la == SMTLIB2Parser::SIMPLE_SYM

    || _la == SMTLIB2Parser::QUOTED_SYM) {
      setState(304);
      symbol();
    }
    setState(308); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(307);
      theory_attribute();
      setState(310); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
      | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
      | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
      | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
      | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
      | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
      | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
      | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
      | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN);
    setState(312);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Theory_attributeContext ------------------------------------------------------------------

SMTLIB2Parser::Theory_attributeContext::Theory_attributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_SORTS() {
  return getToken(SMTLIB2Parser::KEYWORD_SORTS, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::Sort_symbol_declContext *> SMTLIB2Parser::Theory_attributeContext::sort_symbol_decl() {
  return getRuleContexts<SMTLIB2Parser::Sort_symbol_declContext>();
}

SMTLIB2Parser::Sort_symbol_declContext* SMTLIB2Parser::Theory_attributeContext::sort_symbol_decl(size_t i) {
  return getRuleContext<SMTLIB2Parser::Sort_symbol_declContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_FUNS() {
  return getToken(SMTLIB2Parser::KEYWORD_FUNS, 0);
}

std::vector<SMTLIB2Parser::Par_fun_symbol_declContext *> SMTLIB2Parser::Theory_attributeContext::par_fun_symbol_decl() {
  return getRuleContexts<SMTLIB2Parser::Par_fun_symbol_declContext>();
}

SMTLIB2Parser::Par_fun_symbol_declContext* SMTLIB2Parser::Theory_attributeContext::par_fun_symbol_decl(size_t i) {
  return getRuleContext<SMTLIB2Parser::Par_fun_symbol_declContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_SORTS_DESCRIPTION() {
  return getToken(SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::STRING() {
  return getToken(SMTLIB2Parser::STRING, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_FUNS_DESCRIPTION() {
  return getToken(SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_DEFINITION() {
  return getToken(SMTLIB2Parser::KEYWORD_DEFINITION, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_VALUES() {
  return getToken(SMTLIB2Parser::KEYWORD_VALUES, 0);
}

tree::TerminalNode* SMTLIB2Parser::Theory_attributeContext::KEYWORD_NOTES() {
  return getToken(SMTLIB2Parser::KEYWORD_NOTES, 0);
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::Theory_attributeContext::attribute() {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(0);
}


size_t SMTLIB2Parser::Theory_attributeContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleTheory_attribute;
}

void SMTLIB2Parser::Theory_attributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTheory_attribute(this);
}

void SMTLIB2Parser::Theory_attributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTheory_attribute(this);
}


antlrcpp::Any SMTLIB2Parser::Theory_attributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitTheory_attribute(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Theory_attributeContext* SMTLIB2Parser::theory_attribute() {
  Theory_attributeContext *_localctx = _tracker.createInstance<Theory_attributeContext>(_ctx, getState());
  enterRule(_localctx, 34, SMTLIB2Parser::RuleTheory_attribute);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(343);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(314);
      match(SMTLIB2Parser::KEYWORD_SORTS);
      setState(315);
      match(SMTLIB2Parser::OpenPar);
      setState(317); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(316);
        sort_symbol_decl();
        setState(319); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SMTLIB2Parser::OpenPar);
      setState(321);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(323);
      match(SMTLIB2Parser::KEYWORD_FUNS);
      setState(324);
      match(SMTLIB2Parser::OpenPar);
      setState(326); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(325);
        par_fun_symbol_decl();
        setState(328); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SMTLIB2Parser::OpenPar);
      setState(330);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(332);
      match(SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION);
      setState(333);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(334);
      match(SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION);
      setState(335);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(336);
      match(SMTLIB2Parser::KEYWORD_DEFINITION);
      setState(337);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(338);
      match(SMTLIB2Parser::KEYWORD_VALUES);
      setState(339);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(340);
      match(SMTLIB2Parser::KEYWORD_NOTES);
      setState(341);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(342);
      attribute();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Logic_attributeContext ------------------------------------------------------------------

SMTLIB2Parser::Logic_attributeContext::Logic_attributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::KEYWORD_THEORIES() {
  return getToken(SMTLIB2Parser::KEYWORD_THEORIES, 0);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::SymbolContext *> SMTLIB2Parser::Logic_attributeContext::symbol() {
  return getRuleContexts<SMTLIB2Parser::SymbolContext>();
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Logic_attributeContext::symbol(size_t i) {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::KEYWORD_LANGUAGE() {
  return getToken(SMTLIB2Parser::KEYWORD_LANGUAGE, 0);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::STRING() {
  return getToken(SMTLIB2Parser::STRING, 0);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::KEYWORD_EXTENSIONS() {
  return getToken(SMTLIB2Parser::KEYWORD_EXTENSIONS, 0);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::KEYWORD_VALUES() {
  return getToken(SMTLIB2Parser::KEYWORD_VALUES, 0);
}

tree::TerminalNode* SMTLIB2Parser::Logic_attributeContext::KEYWORD_NOTES() {
  return getToken(SMTLIB2Parser::KEYWORD_NOTES, 0);
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::Logic_attributeContext::attribute() {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(0);
}


size_t SMTLIB2Parser::Logic_attributeContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleLogic_attribute;
}

void SMTLIB2Parser::Logic_attributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_attribute(this);
}

void SMTLIB2Parser::Logic_attributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_attribute(this);
}


antlrcpp::Any SMTLIB2Parser::Logic_attributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitLogic_attribute(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Logic_attributeContext* SMTLIB2Parser::logic_attribute() {
  Logic_attributeContext *_localctx = _tracker.createInstance<Logic_attributeContext>(_ctx, getState());
  enterRule(_localctx, 36, SMTLIB2Parser::RuleLogic_attribute);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(363);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(345);
      match(SMTLIB2Parser::KEYWORD_THEORIES);
      setState(346);
      match(SMTLIB2Parser::OpenPar);
      setState(348); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(347);
        symbol();
        setState(350); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || _la == SMTLIB2Parser::SIMPLE_SYM

      || _la == SMTLIB2Parser::QUOTED_SYM);
      setState(352);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(354);
      match(SMTLIB2Parser::KEYWORD_LANGUAGE);
      setState(355);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(356);
      match(SMTLIB2Parser::KEYWORD_EXTENSIONS);
      setState(357);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(358);
      match(SMTLIB2Parser::KEYWORD_VALUES);
      setState(359);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(360);
      match(SMTLIB2Parser::KEYWORD_NOTES);
      setState(361);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(362);
      attribute();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicContext ------------------------------------------------------------------

SMTLIB2Parser::LogicContext::LogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::LogicContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::LogicContext::SYM_LOGIC() {
  return getToken(SMTLIB2Parser::SYM_LOGIC, 0);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::LogicContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::LogicContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::Logic_attributeContext *> SMTLIB2Parser::LogicContext::logic_attribute() {
  return getRuleContexts<SMTLIB2Parser::Logic_attributeContext>();
}

SMTLIB2Parser::Logic_attributeContext* SMTLIB2Parser::LogicContext::logic_attribute(size_t i) {
  return getRuleContext<SMTLIB2Parser::Logic_attributeContext>(i);
}


size_t SMTLIB2Parser::LogicContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleLogic;
}

void SMTLIB2Parser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void SMTLIB2Parser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}


antlrcpp::Any SMTLIB2Parser::LogicContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitLogic(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::LogicContext* SMTLIB2Parser::logic() {
  LogicContext *_localctx = _tracker.createInstance<LogicContext>(_ctx, getState());
  enterRule(_localctx, 38, SMTLIB2Parser::RuleLogic);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(365);
    match(SMTLIB2Parser::OpenPar);
    setState(366);
    match(SMTLIB2Parser::SYM_LOGIC);
    setState(367);
    symbol();
    setState(369); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(368);
      logic_attribute();
      setState(371); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
      | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
      | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
      | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
      | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
      | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
      | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
      | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
      | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN);
    setState(373);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- B_valueContext ------------------------------------------------------------------

SMTLIB2Parser::B_valueContext::B_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::B_valueContext::SYM_TRUE() {
  return getToken(SMTLIB2Parser::SYM_TRUE, 0);
}

tree::TerminalNode* SMTLIB2Parser::B_valueContext::SYM_FALSE() {
  return getToken(SMTLIB2Parser::SYM_FALSE, 0);
}


size_t SMTLIB2Parser::B_valueContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleB_value;
}

void SMTLIB2Parser::B_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterB_value(this);
}

void SMTLIB2Parser::B_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitB_value(this);
}


antlrcpp::Any SMTLIB2Parser::B_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitB_value(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::B_valueContext* SMTLIB2Parser::b_value() {
  B_valueContext *_localctx = _tracker.createInstance<B_valueContext>(_ctx, getState());
  enterRule(_localctx, 40, SMTLIB2Parser::RuleB_value);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(375);
    _la = _input->LA(1);
    if (!(_la == SMTLIB2Parser::SYM_FALSE

    || _la == SMTLIB2Parser::SYM_TRUE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionContext ------------------------------------------------------------------

SMTLIB2Parser::OptionContext::OptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_PRINT_SUCCESS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRINT_SUCCESS, 0);
}

SMTLIB2Parser::B_valueContext* SMTLIB2Parser::OptionContext::b_value() {
  return getRuleContext<SMTLIB2Parser::B_valueContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_EXPAND_DEFINITIONS() {
  return getToken(SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_INTERACTIVE_MODE() {
  return getToken(SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_PRODUCE_PROOFS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_PRODUCE_UNSAT_CORES() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_PRODUCE_MODELS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_MODELS, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_PRODUCE_ASSIGNMENTS() {
  return getToken(SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_REGULAR_OUTPUT_CHANNEL() {
  return getToken(SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::STRING() {
  return getToken(SMTLIB2Parser::STRING, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL() {
  return getToken(SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_RANDOM_SEED() {
  return getToken(SMTLIB2Parser::KEYWORD_RANDOM_SEED, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::NUMERAL() {
  return getToken(SMTLIB2Parser::NUMERAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::OptionContext::KEYWORD_VERBOSITY() {
  return getToken(SMTLIB2Parser::KEYWORD_VERBOSITY, 0);
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::OptionContext::attribute() {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(0);
}


size_t SMTLIB2Parser::OptionContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleOption;
}

void SMTLIB2Parser::OptionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOption(this);
}

void SMTLIB2Parser::OptionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOption(this);
}


antlrcpp::Any SMTLIB2Parser::OptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitOption(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::OptionContext* SMTLIB2Parser::option() {
  OptionContext *_localctx = _tracker.createInstance<OptionContext>(_ctx, getState());
  enterRule(_localctx, 42, SMTLIB2Parser::RuleOption);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(400);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(377);
      match(SMTLIB2Parser::KEYWORD_PRINT_SUCCESS);
      setState(378);
      b_value();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(379);
      match(SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS);
      setState(380);
      b_value();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(381);
      match(SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE);
      setState(382);
      b_value();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(383);
      match(SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS);
      setState(384);
      b_value();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(385);
      match(SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES);
      setState(386);
      b_value();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(387);
      match(SMTLIB2Parser::KEYWORD_PRODUCE_MODELS);
      setState(388);
      b_value();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(389);
      match(SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS);
      setState(390);
      b_value();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(391);
      match(SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL);
      setState(392);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(393);
      match(SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL);
      setState(394);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(395);
      match(SMTLIB2Parser::KEYWORD_RANDOM_SEED);
      setState(396);
      match(SMTLIB2Parser::NUMERAL);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(397);
      match(SMTLIB2Parser::KEYWORD_VERBOSITY);
      setState(398);
      match(SMTLIB2Parser::NUMERAL);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(399);
      attribute();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Info_flagContext ------------------------------------------------------------------

SMTLIB2Parser::Info_flagContext::Info_flagContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_ERROR_BEHAVIOR() {
  return getToken(SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_NAME() {
  return getToken(SMTLIB2Parser::KEYWORD_NAME, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_AUTHORS() {
  return getToken(SMTLIB2Parser::KEYWORD_AUTHORS, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_VERSION() {
  return getToken(SMTLIB2Parser::KEYWORD_VERSION, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_STATUS() {
  return getToken(SMTLIB2Parser::KEYWORD_STATUS, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_REASON_UNKNOWN() {
  return getToken(SMTLIB2Parser::KEYWORD_REASON_UNKNOWN, 0);
}

SMTLIB2Parser::KeywordContext* SMTLIB2Parser::Info_flagContext::keyword() {
  return getRuleContext<SMTLIB2Parser::KeywordContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Info_flagContext::KEYWORD_ALL_STATISTICS() {
  return getToken(SMTLIB2Parser::KEYWORD_ALL_STATISTICS, 0);
}


size_t SMTLIB2Parser::Info_flagContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleInfo_flag;
}

void SMTLIB2Parser::Info_flagContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInfo_flag(this);
}

void SMTLIB2Parser::Info_flagContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInfo_flag(this);
}


antlrcpp::Any SMTLIB2Parser::Info_flagContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitInfo_flag(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Info_flagContext* SMTLIB2Parser::info_flag() {
  Info_flagContext *_localctx = _tracker.createInstance<Info_flagContext>(_ctx, getState());
  enterRule(_localctx, 44, SMTLIB2Parser::RuleInfo_flag);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(410);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(402);
      match(SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(403);
      match(SMTLIB2Parser::KEYWORD_NAME);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(404);
      match(SMTLIB2Parser::KEYWORD_AUTHORS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(405);
      match(SMTLIB2Parser::KEYWORD_VERSION);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(406);
      match(SMTLIB2Parser::KEYWORD_STATUS);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(407);
      match(SMTLIB2Parser::KEYWORD_REASON_UNKNOWN);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(408);
      keyword();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(409);
      match(SMTLIB2Parser::KEYWORD_ALL_STATISTICS);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommandContext ------------------------------------------------------------------

SMTLIB2Parser::CommandContext::CommandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::CommandContext::OpenPar() {
  return getTokens(SMTLIB2Parser::OpenPar);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::OpenPar(size_t i) {
  return getToken(SMTLIB2Parser::OpenPar, i);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_SET_LOGIC() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_SET_LOGIC, 0);
}

std::vector<SMTLIB2Parser::SymbolContext *> SMTLIB2Parser::CommandContext::symbol() {
  return getRuleContexts<SMTLIB2Parser::SymbolContext>();
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::CommandContext::symbol(size_t i) {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(i);
}

std::vector<tree::TerminalNode *> SMTLIB2Parser::CommandContext::ClosePar() {
  return getTokens(SMTLIB2Parser::ClosePar);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::ClosePar(size_t i) {
  return getToken(SMTLIB2Parser::ClosePar, i);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_SET_OPTION() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_SET_OPTION, 0);
}

SMTLIB2Parser::OptionContext* SMTLIB2Parser::CommandContext::option() {
  return getRuleContext<SMTLIB2Parser::OptionContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_SET_INFO() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_SET_INFO, 0);
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::CommandContext::attribute() {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_DECLARE_SORT() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_DECLARE_SORT, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::NUMERAL() {
  return getToken(SMTLIB2Parser::NUMERAL, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_DEFINE_SORT() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_DEFINE_SORT, 0);
}

std::vector<SMTLIB2Parser::SortContext *> SMTLIB2Parser::CommandContext::sort() {
  return getRuleContexts<SMTLIB2Parser::SortContext>();
}

SMTLIB2Parser::SortContext* SMTLIB2Parser::CommandContext::sort(size_t i) {
  return getRuleContext<SMTLIB2Parser::SortContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_DECLARE_FUN() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_DECLARE_FUN, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_DEFINE_FUN() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_DEFINE_FUN, 0);
}

std::vector<SMTLIB2Parser::TermContext *> SMTLIB2Parser::CommandContext::term() {
  return getRuleContexts<SMTLIB2Parser::TermContext>();
}

SMTLIB2Parser::TermContext* SMTLIB2Parser::CommandContext::term(size_t i) {
  return getRuleContext<SMTLIB2Parser::TermContext>(i);
}

std::vector<SMTLIB2Parser::Sorted_varContext *> SMTLIB2Parser::CommandContext::sorted_var() {
  return getRuleContexts<SMTLIB2Parser::Sorted_varContext>();
}

SMTLIB2Parser::Sorted_varContext* SMTLIB2Parser::CommandContext::sorted_var(size_t i) {
  return getRuleContext<SMTLIB2Parser::Sorted_varContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_PUSH() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_PUSH, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_POP() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_POP, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_ASSERT() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_ASSERT, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_CHECK_SAT() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_CHECK_SAT, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_ASSERTIONS() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_ASSERTIONS, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_PROOF() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_PROOF, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_UNSAT_CORE() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_UNSAT_CORE, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_VALUE() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_VALUE, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_ASSIGNMENT() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_ASSIGNMENT, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_OPTION() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_OPTION, 0);
}

SMTLIB2Parser::KeywordContext* SMTLIB2Parser::CommandContext::keyword() {
  return getRuleContext<SMTLIB2Parser::KeywordContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_INFO() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_INFO, 0);
}

SMTLIB2Parser::Info_flagContext* SMTLIB2Parser::CommandContext::info_flag() {
  return getRuleContext<SMTLIB2Parser::Info_flagContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_EXIT() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_EXIT, 0);
}

tree::TerminalNode* SMTLIB2Parser::CommandContext::TOKEN_CMD_GET_MODEL() {
  return getToken(SMTLIB2Parser::TOKEN_CMD_GET_MODEL, 0);
}


size_t SMTLIB2Parser::CommandContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleCommand;
}

void SMTLIB2Parser::CommandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCommand(this);
}

void SMTLIB2Parser::CommandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCommand(this);
}


antlrcpp::Any SMTLIB2Parser::CommandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitCommand(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::CommandContext* SMTLIB2Parser::command() {
  CommandContext *_localctx = _tracker.createInstance<CommandContext>(_ctx, getState());
  enterRule(_localctx, 46, SMTLIB2Parser::RuleCommand);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(531);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(412);
      match(SMTLIB2Parser::OpenPar);
      setState(413);
      match(SMTLIB2Parser::TOKEN_CMD_SET_LOGIC);
      setState(414);
      symbol();
      setState(415);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(417);
      match(SMTLIB2Parser::OpenPar);
      setState(418);
      match(SMTLIB2Parser::TOKEN_CMD_SET_OPTION);
      setState(419);
      option();
      setState(420);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(422);
      match(SMTLIB2Parser::OpenPar);
      setState(423);
      match(SMTLIB2Parser::TOKEN_CMD_SET_INFO);
      setState(424);
      attribute();
      setState(425);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(427);
      match(SMTLIB2Parser::OpenPar);
      setState(428);
      match(SMTLIB2Parser::TOKEN_CMD_DECLARE_SORT);
      setState(429);
      symbol();
      setState(430);
      match(SMTLIB2Parser::NUMERAL);
      setState(431);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(433);
      match(SMTLIB2Parser::OpenPar);
      setState(434);
      match(SMTLIB2Parser::TOKEN_CMD_DEFINE_SORT);
      setState(435);
      symbol();
      setState(436);
      match(SMTLIB2Parser::OpenPar);
      setState(440);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || _la == SMTLIB2Parser::SIMPLE_SYM

      || _la == SMTLIB2Parser::QUOTED_SYM) {
        setState(437);
        symbol();
        setState(442);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(443);
      match(SMTLIB2Parser::ClosePar);
      setState(444);
      sort();
      setState(445);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(447);
      match(SMTLIB2Parser::OpenPar);
      setState(448);
      match(SMTLIB2Parser::TOKEN_CMD_DECLARE_FUN);
      setState(449);
      symbol();
      setState(450);
      match(SMTLIB2Parser::OpenPar);
      setState(454);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 88) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 88)) & ((1ULL << (SMTLIB2Parser::SIMPLE_SYM - 88))
        | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 88))
        | (1ULL << (SMTLIB2Parser::OpenPar - 88)))) != 0)) {
        setState(451);
        sort();
        setState(456);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(457);
      match(SMTLIB2Parser::ClosePar);
      setState(458);
      sort();
      setState(459);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(461);
      match(SMTLIB2Parser::OpenPar);
      setState(462);
      match(SMTLIB2Parser::TOKEN_CMD_DEFINE_FUN);
      setState(463);
      symbol();
      setState(464);
      match(SMTLIB2Parser::OpenPar);
      setState(468);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SMTLIB2Parser::OpenPar) {
        setState(465);
        sorted_var();
        setState(470);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(471);
      match(SMTLIB2Parser::ClosePar);
      setState(472);
      sort();
      setState(473);
      term();
      setState(474);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(476);
      match(SMTLIB2Parser::OpenPar);
      setState(477);
      match(SMTLIB2Parser::TOKEN_CMD_PUSH);
      setState(478);
      match(SMTLIB2Parser::NUMERAL);
      setState(479);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(480);
      match(SMTLIB2Parser::OpenPar);
      setState(481);
      match(SMTLIB2Parser::TOKEN_CMD_POP);
      setState(482);
      match(SMTLIB2Parser::NUMERAL);
      setState(483);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(484);
      match(SMTLIB2Parser::OpenPar);
      setState(485);
      match(SMTLIB2Parser::TOKEN_CMD_ASSERT);
      setState(486);
      term();
      setState(487);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(489);
      match(SMTLIB2Parser::OpenPar);
      setState(490);
      match(SMTLIB2Parser::TOKEN_CMD_CHECK_SAT);
      setState(491);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(492);
      match(SMTLIB2Parser::OpenPar);
      setState(493);
      match(SMTLIB2Parser::TOKEN_CMD_GET_ASSERTIONS);
      setState(494);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(495);
      match(SMTLIB2Parser::OpenPar);
      setState(496);
      match(SMTLIB2Parser::TOKEN_CMD_GET_PROOF);
      setState(497);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(498);
      match(SMTLIB2Parser::OpenPar);
      setState(499);
      match(SMTLIB2Parser::TOKEN_CMD_GET_UNSAT_CORE);
      setState(500);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(501);
      match(SMTLIB2Parser::OpenPar);
      setState(502);
      match(SMTLIB2Parser::TOKEN_CMD_GET_VALUE);
      setState(503);
      match(SMTLIB2Parser::OpenPar);
      setState(505); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(504);
        term();
        setState(507); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
        | (1ULL << SMTLIB2Parser::SYM_OR)
        | (1ULL << SMTLIB2Parser::SYM_NOT)
        | (1ULL << SMTLIB2Parser::SYM_BOOL)
        | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
        | (1ULL << SMTLIB2Parser::SYM_ERROR)
        | (1ULL << SMTLIB2Parser::SYM_FALSE)
        | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
        | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
        | (1ULL << SMTLIB2Parser::SYM_LOGIC)
        | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
        | (1ULL << SMTLIB2Parser::SYM_SAT)
        | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
        | (1ULL << SMTLIB2Parser::SYM_THEORY)
        | (1ULL << SMTLIB2Parser::SYM_TRUE)
        | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
        | (1ULL << SMTLIB2Parser::SYM_UNSAT)
        | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (SMTLIB2Parser::NUMERAL - 82))
        | (1ULL << (SMTLIB2Parser::DECIMAL - 82))
        | (1ULL << (SMTLIB2Parser::HEXADECIMAL - 82))
        | (1ULL << (SMTLIB2Parser::BINARY - 82))
        | (1ULL << (SMTLIB2Parser::STRING - 82))
        | (1ULL << (SMTLIB2Parser::SIMPLE_SYM - 82))
        | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 82))
        | (1ULL << (SMTLIB2Parser::OpenPar - 82)))) != 0));
      setState(509);
      match(SMTLIB2Parser::ClosePar);
      setState(510);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(512);
      match(SMTLIB2Parser::OpenPar);
      setState(513);
      match(SMTLIB2Parser::TOKEN_CMD_GET_ASSIGNMENT);
      setState(514);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(515);
      match(SMTLIB2Parser::OpenPar);
      setState(516);
      match(SMTLIB2Parser::TOKEN_CMD_GET_OPTION);
      setState(517);
      keyword();
      setState(518);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(520);
      match(SMTLIB2Parser::OpenPar);
      setState(521);
      match(SMTLIB2Parser::TOKEN_CMD_GET_INFO);
      setState(522);
      info_flag();
      setState(523);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(525);
      match(SMTLIB2Parser::OpenPar);
      setState(526);
      match(SMTLIB2Parser::TOKEN_CMD_EXIT);
      setState(527);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(528);
      match(SMTLIB2Parser::OpenPar);
      setState(529);
      match(SMTLIB2Parser::TOKEN_CMD_GET_MODEL);
      setState(530);
      match(SMTLIB2Parser::ClosePar);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptContext ------------------------------------------------------------------

SMTLIB2Parser::ScriptContext::ScriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SMTLIB2Parser::CommandContext *> SMTLIB2Parser::ScriptContext::command() {
  return getRuleContexts<SMTLIB2Parser::CommandContext>();
}

SMTLIB2Parser::CommandContext* SMTLIB2Parser::ScriptContext::command(size_t i) {
  return getRuleContext<SMTLIB2Parser::CommandContext>(i);
}


size_t SMTLIB2Parser::ScriptContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleScript;
}

void SMTLIB2Parser::ScriptContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScript(this);
}

void SMTLIB2Parser::ScriptContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScript(this);
}


antlrcpp::Any SMTLIB2Parser::ScriptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitScript(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::ScriptContext* SMTLIB2Parser::script() {
  ScriptContext *_localctx = _tracker.createInstance<ScriptContext>(_ctx, getState());
  enterRule(_localctx, 48, SMTLIB2Parser::RuleScript);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(534); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(533);
      command();
      setState(536); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == SMTLIB2Parser::OpenPar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Gen_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Gen_responseContext::Gen_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Gen_responseContext::SYM_UNSUPPORTED() {
  return getToken(SMTLIB2Parser::SYM_UNSUPPORTED, 0);
}

tree::TerminalNode* SMTLIB2Parser::Gen_responseContext::SYM_SUCCESS() {
  return getToken(SMTLIB2Parser::SYM_SUCCESS, 0);
}

tree::TerminalNode* SMTLIB2Parser::Gen_responseContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Gen_responseContext::SYM_ERROR() {
  return getToken(SMTLIB2Parser::SYM_ERROR, 0);
}

tree::TerminalNode* SMTLIB2Parser::Gen_responseContext::STRING() {
  return getToken(SMTLIB2Parser::STRING, 0);
}

tree::TerminalNode* SMTLIB2Parser::Gen_responseContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}


size_t SMTLIB2Parser::Gen_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGen_response;
}

void SMTLIB2Parser::Gen_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGen_response(this);
}

void SMTLIB2Parser::Gen_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGen_response(this);
}


antlrcpp::Any SMTLIB2Parser::Gen_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGen_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Gen_responseContext* SMTLIB2Parser::gen_response() {
  Gen_responseContext *_localctx = _tracker.createInstance<Gen_responseContext>(_ctx, getState());
  enterRule(_localctx, 50, SMTLIB2Parser::RuleGen_response);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(544);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SMTLIB2Parser::SYM_UNSUPPORTED: {
        enterOuterAlt(_localctx, 1);
        setState(538);
        match(SMTLIB2Parser::SYM_UNSUPPORTED);
        break;
      }

      case SMTLIB2Parser::SYM_SUCCESS: {
        enterOuterAlt(_localctx, 2);
        setState(539);
        match(SMTLIB2Parser::SYM_SUCCESS);
        break;
      }

      case SMTLIB2Parser::OpenPar: {
        enterOuterAlt(_localctx, 3);
        setState(540);
        match(SMTLIB2Parser::OpenPar);
        setState(541);
        match(SMTLIB2Parser::SYM_ERROR);
        setState(542);
        match(SMTLIB2Parser::STRING);
        setState(543);
        match(SMTLIB2Parser::ClosePar);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Error_behaviorContext ------------------------------------------------------------------

SMTLIB2Parser::Error_behaviorContext::Error_behaviorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Error_behaviorContext::SYM_IMMEDIATE_EXIT() {
  return getToken(SMTLIB2Parser::SYM_IMMEDIATE_EXIT, 0);
}

tree::TerminalNode* SMTLIB2Parser::Error_behaviorContext::SYM_CONTINUED_EXECUTION() {
  return getToken(SMTLIB2Parser::SYM_CONTINUED_EXECUTION, 0);
}


size_t SMTLIB2Parser::Error_behaviorContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleError_behavior;
}

void SMTLIB2Parser::Error_behaviorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterError_behavior(this);
}

void SMTLIB2Parser::Error_behaviorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitError_behavior(this);
}


antlrcpp::Any SMTLIB2Parser::Error_behaviorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitError_behavior(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Error_behaviorContext* SMTLIB2Parser::error_behavior() {
  Error_behaviorContext *_localctx = _tracker.createInstance<Error_behaviorContext>(_ctx, getState());
  enterRule(_localctx, 52, SMTLIB2Parser::RuleError_behavior);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(546);
    _la = _input->LA(1);
    if (!(_la == SMTLIB2Parser::SYM_CONTINUED_EXECUTION

    || _la == SMTLIB2Parser::SYM_IMMEDIATE_EXIT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Reason_unknownContext ------------------------------------------------------------------

SMTLIB2Parser::Reason_unknownContext::Reason_unknownContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Reason_unknownContext::SYM_MEMOUT() {
  return getToken(SMTLIB2Parser::SYM_MEMOUT, 0);
}

tree::TerminalNode* SMTLIB2Parser::Reason_unknownContext::SYM_INCOMPLETE() {
  return getToken(SMTLIB2Parser::SYM_INCOMPLETE, 0);
}


size_t SMTLIB2Parser::Reason_unknownContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleReason_unknown;
}

void SMTLIB2Parser::Reason_unknownContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReason_unknown(this);
}

void SMTLIB2Parser::Reason_unknownContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReason_unknown(this);
}


antlrcpp::Any SMTLIB2Parser::Reason_unknownContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitReason_unknown(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Reason_unknownContext* SMTLIB2Parser::reason_unknown() {
  Reason_unknownContext *_localctx = _tracker.createInstance<Reason_unknownContext>(_ctx, getState());
  enterRule(_localctx, 54, SMTLIB2Parser::RuleReason_unknown);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    _la = _input->LA(1);
    if (!(_la == SMTLIB2Parser::SYM_INCOMPLETE

    || _la == SMTLIB2Parser::SYM_MEMOUT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatusContext ------------------------------------------------------------------

SMTLIB2Parser::StatusContext::StatusContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::StatusContext::SYM_SAT() {
  return getToken(SMTLIB2Parser::SYM_SAT, 0);
}

tree::TerminalNode* SMTLIB2Parser::StatusContext::SYM_UNSAT() {
  return getToken(SMTLIB2Parser::SYM_UNSAT, 0);
}

tree::TerminalNode* SMTLIB2Parser::StatusContext::SYM_UNKNOWN() {
  return getToken(SMTLIB2Parser::SYM_UNKNOWN, 0);
}


size_t SMTLIB2Parser::StatusContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleStatus;
}

void SMTLIB2Parser::StatusContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatus(this);
}

void SMTLIB2Parser::StatusContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatus(this);
}


antlrcpp::Any SMTLIB2Parser::StatusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitStatus(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::StatusContext* SMTLIB2Parser::status() {
  StatusContext *_localctx = _tracker.createInstance<StatusContext>(_ctx, getState());
  enterRule(_localctx, 56, SMTLIB2Parser::RuleStatus);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(550);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_SAT)
      | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
      | (1ULL << SMTLIB2Parser::SYM_UNSAT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Info_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Info_responseContext::Info_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Info_responseContext::KEYWORD_ERROR_BEHAVIOR() {
  return getToken(SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR, 0);
}

SMTLIB2Parser::Error_behaviorContext* SMTLIB2Parser::Info_responseContext::error_behavior() {
  return getRuleContext<SMTLIB2Parser::Error_behaviorContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::Info_responseContext::KEYWORD_NAME() {
  return getToken(SMTLIB2Parser::KEYWORD_NAME, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_responseContext::STRING() {
  return getToken(SMTLIB2Parser::STRING, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_responseContext::KEYWORD_AUTHORS() {
  return getToken(SMTLIB2Parser::KEYWORD_AUTHORS, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_responseContext::KEYWORD_VERSION() {
  return getToken(SMTLIB2Parser::KEYWORD_VERSION, 0);
}

tree::TerminalNode* SMTLIB2Parser::Info_responseContext::KEYWORD_REASON_UNKNOWN() {
  return getToken(SMTLIB2Parser::KEYWORD_REASON_UNKNOWN, 0);
}

SMTLIB2Parser::Reason_unknownContext* SMTLIB2Parser::Info_responseContext::reason_unknown() {
  return getRuleContext<SMTLIB2Parser::Reason_unknownContext>(0);
}

SMTLIB2Parser::AttributeContext* SMTLIB2Parser::Info_responseContext::attribute() {
  return getRuleContext<SMTLIB2Parser::AttributeContext>(0);
}


size_t SMTLIB2Parser::Info_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleInfo_response;
}

void SMTLIB2Parser::Info_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInfo_response(this);
}

void SMTLIB2Parser::Info_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInfo_response(this);
}


antlrcpp::Any SMTLIB2Parser::Info_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitInfo_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Info_responseContext* SMTLIB2Parser::info_response() {
  Info_responseContext *_localctx = _tracker.createInstance<Info_responseContext>(_ctx, getState());
  enterRule(_localctx, 58, SMTLIB2Parser::RuleInfo_response);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(563);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(552);
      match(SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR);
      setState(553);
      error_behavior();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(554);
      match(SMTLIB2Parser::KEYWORD_NAME);
      setState(555);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(556);
      match(SMTLIB2Parser::KEYWORD_AUTHORS);
      setState(557);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(558);
      match(SMTLIB2Parser::KEYWORD_VERSION);
      setState(559);
      match(SMTLIB2Parser::STRING);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(560);
      match(SMTLIB2Parser::KEYWORD_REASON_UNKNOWN);
      setState(561);
      reason_unknown();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(562);
      attribute();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_info_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_info_responseContext::Get_info_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Get_info_responseContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Get_info_responseContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::Info_responseContext *> SMTLIB2Parser::Get_info_responseContext::info_response() {
  return getRuleContexts<SMTLIB2Parser::Info_responseContext>();
}

SMTLIB2Parser::Info_responseContext* SMTLIB2Parser::Get_info_responseContext::info_response(size_t i) {
  return getRuleContext<SMTLIB2Parser::Info_responseContext>(i);
}


size_t SMTLIB2Parser::Get_info_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_info_response;
}

void SMTLIB2Parser::Get_info_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_info_response(this);
}

void SMTLIB2Parser::Get_info_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_info_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_info_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_info_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_info_responseContext* SMTLIB2Parser::get_info_response() {
  Get_info_responseContext *_localctx = _tracker.createInstance<Get_info_responseContext>(_ctx, getState());
  enterRule(_localctx, 60, SMTLIB2Parser::RuleGet_info_response);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(565);
    match(SMTLIB2Parser::OpenPar);
    setState(567); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(566);
      info_response();
      setState(569); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::KEYWORD_ALL_STATISTICS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AUTHORS)
      | (1ULL << SMTLIB2Parser::KEYWORD_AXIOMS)
      | (1ULL << SMTLIB2Parser::KEYWORD_CHAINABLE)
      | (1ULL << SMTLIB2Parser::KEYWORD_DEFINITION)
      | (1ULL << SMTLIB2Parser::KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_ERROR_BEHAVIOR)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXPAND_DEFINITIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_EXTENSIONS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS)
      | (1ULL << SMTLIB2Parser::KEYWORD_FUNS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_INTERACTIVE_MODE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LANGUAGE)
      | (1ULL << SMTLIB2Parser::KEYWORD_LEFT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAME)
      | (1ULL << SMTLIB2Parser::KEYWORD_NAMED)
      | (1ULL << SMTLIB2Parser::KEYWORD_NOTES)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRINT_SUCCESS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_ASSIGNMENTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_MODELS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_PROOFS)
      | (1ULL << SMTLIB2Parser::KEYWORD_PRODUCE_UNSAT_CORES)
      | (1ULL << SMTLIB2Parser::KEYWORD_RANDOM_SEED)
      | (1ULL << SMTLIB2Parser::KEYWORD_REASON_UNKNOWN)
      | (1ULL << SMTLIB2Parser::KEYWORD_REGULAR_OUTPUT_CHANNEL)
      | (1ULL << SMTLIB2Parser::KEYWORD_RIGHT_ASSOC)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS)
      | (1ULL << SMTLIB2Parser::KEYWORD_SORTS_DESCRIPTION)
      | (1ULL << SMTLIB2Parser::KEYWORD_STATUS)
      | (1ULL << SMTLIB2Parser::KEYWORD_THEORIES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VALUES)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERBOSITY)
      | (1ULL << SMTLIB2Parser::KEYWORD_VERSION))) != 0) || _la == SMTLIB2Parser::KEYWORD_TOKEN);
    setState(571);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Check_sat_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Check_sat_responseContext::Check_sat_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::StatusContext* SMTLIB2Parser::Check_sat_responseContext::status() {
  return getRuleContext<SMTLIB2Parser::StatusContext>(0);
}


size_t SMTLIB2Parser::Check_sat_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleCheck_sat_response;
}

void SMTLIB2Parser::Check_sat_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCheck_sat_response(this);
}

void SMTLIB2Parser::Check_sat_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCheck_sat_response(this);
}


antlrcpp::Any SMTLIB2Parser::Check_sat_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitCheck_sat_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Check_sat_responseContext* SMTLIB2Parser::check_sat_response() {
  Check_sat_responseContext *_localctx = _tracker.createInstance<Check_sat_responseContext>(_ctx, getState());
  enterRule(_localctx, 62, SMTLIB2Parser::RuleCheck_sat_response);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(573);
    status();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_assertions_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_assertions_responseContext::Get_assertions_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Get_assertions_responseContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Get_assertions_responseContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::TermContext *> SMTLIB2Parser::Get_assertions_responseContext::term() {
  return getRuleContexts<SMTLIB2Parser::TermContext>();
}

SMTLIB2Parser::TermContext* SMTLIB2Parser::Get_assertions_responseContext::term(size_t i) {
  return getRuleContext<SMTLIB2Parser::TermContext>(i);
}


size_t SMTLIB2Parser::Get_assertions_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_assertions_response;
}

void SMTLIB2Parser::Get_assertions_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_assertions_response(this);
}

void SMTLIB2Parser::Get_assertions_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_assertions_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_assertions_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_assertions_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_assertions_responseContext* SMTLIB2Parser::get_assertions_response() {
  Get_assertions_responseContext *_localctx = _tracker.createInstance<Get_assertions_responseContext>(_ctx, getState());
  enterRule(_localctx, 64, SMTLIB2Parser::RuleGet_assertions_response);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(575);
    match(SMTLIB2Parser::OpenPar);
    setState(577); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(576);
      term();
      setState(579); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
      | (1ULL << SMTLIB2Parser::SYM_OR)
      | (1ULL << SMTLIB2Parser::SYM_NOT)
      | (1ULL << SMTLIB2Parser::SYM_BOOL)
      | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
      | (1ULL << SMTLIB2Parser::SYM_ERROR)
      | (1ULL << SMTLIB2Parser::SYM_FALSE)
      | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
      | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
      | (1ULL << SMTLIB2Parser::SYM_LOGIC)
      | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
      | (1ULL << SMTLIB2Parser::SYM_SAT)
      | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
      | (1ULL << SMTLIB2Parser::SYM_THEORY)
      | (1ULL << SMTLIB2Parser::SYM_TRUE)
      | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
      | (1ULL << SMTLIB2Parser::SYM_UNSAT)
      | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || ((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (SMTLIB2Parser::NUMERAL - 82))
      | (1ULL << (SMTLIB2Parser::DECIMAL - 82))
      | (1ULL << (SMTLIB2Parser::HEXADECIMAL - 82))
      | (1ULL << (SMTLIB2Parser::BINARY - 82))
      | (1ULL << (SMTLIB2Parser::STRING - 82))
      | (1ULL << (SMTLIB2Parser::SIMPLE_SYM - 82))
      | (1ULL << (SMTLIB2Parser::QUOTED_SYM - 82))
      | (1ULL << (SMTLIB2Parser::OpenPar - 82)))) != 0));
    setState(581);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProofContext ------------------------------------------------------------------

SMTLIB2Parser::ProofContext::ProofContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::S_exprContext* SMTLIB2Parser::ProofContext::s_expr() {
  return getRuleContext<SMTLIB2Parser::S_exprContext>(0);
}


size_t SMTLIB2Parser::ProofContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleProof;
}

void SMTLIB2Parser::ProofContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProof(this);
}

void SMTLIB2Parser::ProofContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProof(this);
}


antlrcpp::Any SMTLIB2Parser::ProofContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitProof(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::ProofContext* SMTLIB2Parser::proof() {
  ProofContext *_localctx = _tracker.createInstance<ProofContext>(_ctx, getState());
  enterRule(_localctx, 66, SMTLIB2Parser::RuleProof);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(583);
    s_expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_proof_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_proof_responseContext::Get_proof_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::ProofContext* SMTLIB2Parser::Get_proof_responseContext::proof() {
  return getRuleContext<SMTLIB2Parser::ProofContext>(0);
}


size_t SMTLIB2Parser::Get_proof_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_proof_response;
}

void SMTLIB2Parser::Get_proof_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_proof_response(this);
}

void SMTLIB2Parser::Get_proof_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_proof_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_proof_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_proof_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_proof_responseContext* SMTLIB2Parser::get_proof_response() {
  Get_proof_responseContext *_localctx = _tracker.createInstance<Get_proof_responseContext>(_ctx, getState());
  enterRule(_localctx, 68, SMTLIB2Parser::RuleGet_proof_response);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(585);
    proof();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_unsat_core_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_unsat_core_responseContext::Get_unsat_core_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Get_unsat_core_responseContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Get_unsat_core_responseContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::SymbolContext *> SMTLIB2Parser::Get_unsat_core_responseContext::symbol() {
  return getRuleContexts<SMTLIB2Parser::SymbolContext>();
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::Get_unsat_core_responseContext::symbol(size_t i) {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(i);
}


size_t SMTLIB2Parser::Get_unsat_core_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_unsat_core_response;
}

void SMTLIB2Parser::Get_unsat_core_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_unsat_core_response(this);
}

void SMTLIB2Parser::Get_unsat_core_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_unsat_core_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_unsat_core_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_unsat_core_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_unsat_core_responseContext* SMTLIB2Parser::get_unsat_core_response() {
  Get_unsat_core_responseContext *_localctx = _tracker.createInstance<Get_unsat_core_responseContext>(_ctx, getState());
  enterRule(_localctx, 70, SMTLIB2Parser::RuleGet_unsat_core_response);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(587);
    match(SMTLIB2Parser::OpenPar);
    setState(589); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(588);
      symbol();
      setState(591); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SMTLIB2Parser::SYM_AND)
      | (1ULL << SMTLIB2Parser::SYM_OR)
      | (1ULL << SMTLIB2Parser::SYM_NOT)
      | (1ULL << SMTLIB2Parser::SYM_BOOL)
      | (1ULL << SMTLIB2Parser::SYM_CONTINUED_EXECUTION)
      | (1ULL << SMTLIB2Parser::SYM_ERROR)
      | (1ULL << SMTLIB2Parser::SYM_FALSE)
      | (1ULL << SMTLIB2Parser::SYM_IMMEDIATE_EXIT)
      | (1ULL << SMTLIB2Parser::SYM_INCOMPLETE)
      | (1ULL << SMTLIB2Parser::SYM_LOGIC)
      | (1ULL << SMTLIB2Parser::SYM_MEMOUT)
      | (1ULL << SMTLIB2Parser::SYM_SAT)
      | (1ULL << SMTLIB2Parser::SYM_SUCCESS)
      | (1ULL << SMTLIB2Parser::SYM_THEORY)
      | (1ULL << SMTLIB2Parser::SYM_TRUE)
      | (1ULL << SMTLIB2Parser::SYM_UNKNOWN)
      | (1ULL << SMTLIB2Parser::SYM_UNSAT)
      | (1ULL << SMTLIB2Parser::SYM_UNSUPPORTED))) != 0) || _la == SMTLIB2Parser::SIMPLE_SYM

    || _la == SMTLIB2Parser::QUOTED_SYM);
    setState(593);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Valuation_pairContext ------------------------------------------------------------------

SMTLIB2Parser::Valuation_pairContext::Valuation_pairContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Valuation_pairContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

std::vector<SMTLIB2Parser::TermContext *> SMTLIB2Parser::Valuation_pairContext::term() {
  return getRuleContexts<SMTLIB2Parser::TermContext>();
}

SMTLIB2Parser::TermContext* SMTLIB2Parser::Valuation_pairContext::term(size_t i) {
  return getRuleContext<SMTLIB2Parser::TermContext>(i);
}

tree::TerminalNode* SMTLIB2Parser::Valuation_pairContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}


size_t SMTLIB2Parser::Valuation_pairContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleValuation_pair;
}

void SMTLIB2Parser::Valuation_pairContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValuation_pair(this);
}

void SMTLIB2Parser::Valuation_pairContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValuation_pair(this);
}


antlrcpp::Any SMTLIB2Parser::Valuation_pairContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitValuation_pair(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Valuation_pairContext* SMTLIB2Parser::valuation_pair() {
  Valuation_pairContext *_localctx = _tracker.createInstance<Valuation_pairContext>(_ctx, getState());
  enterRule(_localctx, 72, SMTLIB2Parser::RuleValuation_pair);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(595);
    match(SMTLIB2Parser::OpenPar);
    setState(596);
    term();
    setState(597);
    term();
    setState(598);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_value_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_value_responseContext::Get_value_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Get_value_responseContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Get_value_responseContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::Valuation_pairContext *> SMTLIB2Parser::Get_value_responseContext::valuation_pair() {
  return getRuleContexts<SMTLIB2Parser::Valuation_pairContext>();
}

SMTLIB2Parser::Valuation_pairContext* SMTLIB2Parser::Get_value_responseContext::valuation_pair(size_t i) {
  return getRuleContext<SMTLIB2Parser::Valuation_pairContext>(i);
}


size_t SMTLIB2Parser::Get_value_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_value_response;
}

void SMTLIB2Parser::Get_value_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_value_response(this);
}

void SMTLIB2Parser::Get_value_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_value_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_value_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_value_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_value_responseContext* SMTLIB2Parser::get_value_response() {
  Get_value_responseContext *_localctx = _tracker.createInstance<Get_value_responseContext>(_ctx, getState());
  enterRule(_localctx, 74, SMTLIB2Parser::RuleGet_value_response);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(600);
    match(SMTLIB2Parser::OpenPar);
    setState(602); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(601);
      valuation_pair();
      setState(604); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == SMTLIB2Parser::OpenPar);
    setState(606);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- T_valuation_pairContext ------------------------------------------------------------------

SMTLIB2Parser::T_valuation_pairContext::T_valuation_pairContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::T_valuation_pairContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

SMTLIB2Parser::SymbolContext* SMTLIB2Parser::T_valuation_pairContext::symbol() {
  return getRuleContext<SMTLIB2Parser::SymbolContext>(0);
}

SMTLIB2Parser::B_valueContext* SMTLIB2Parser::T_valuation_pairContext::b_value() {
  return getRuleContext<SMTLIB2Parser::B_valueContext>(0);
}

tree::TerminalNode* SMTLIB2Parser::T_valuation_pairContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}


size_t SMTLIB2Parser::T_valuation_pairContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleT_valuation_pair;
}

void SMTLIB2Parser::T_valuation_pairContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterT_valuation_pair(this);
}

void SMTLIB2Parser::T_valuation_pairContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitT_valuation_pair(this);
}


antlrcpp::Any SMTLIB2Parser::T_valuation_pairContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitT_valuation_pair(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::T_valuation_pairContext* SMTLIB2Parser::t_valuation_pair() {
  T_valuation_pairContext *_localctx = _tracker.createInstance<T_valuation_pairContext>(_ctx, getState());
  enterRule(_localctx, 76, SMTLIB2Parser::RuleT_valuation_pair);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(608);
    match(SMTLIB2Parser::OpenPar);
    setState(609);
    symbol();
    setState(610);
    b_value();
    setState(611);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_assignment_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_assignment_responseContext::Get_assignment_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SMTLIB2Parser::Get_assignment_responseContext::OpenPar() {
  return getToken(SMTLIB2Parser::OpenPar, 0);
}

tree::TerminalNode* SMTLIB2Parser::Get_assignment_responseContext::ClosePar() {
  return getToken(SMTLIB2Parser::ClosePar, 0);
}

std::vector<SMTLIB2Parser::T_valuation_pairContext *> SMTLIB2Parser::Get_assignment_responseContext::t_valuation_pair() {
  return getRuleContexts<SMTLIB2Parser::T_valuation_pairContext>();
}

SMTLIB2Parser::T_valuation_pairContext* SMTLIB2Parser::Get_assignment_responseContext::t_valuation_pair(size_t i) {
  return getRuleContext<SMTLIB2Parser::T_valuation_pairContext>(i);
}


size_t SMTLIB2Parser::Get_assignment_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_assignment_response;
}

void SMTLIB2Parser::Get_assignment_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_assignment_response(this);
}

void SMTLIB2Parser::Get_assignment_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_assignment_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_assignment_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_assignment_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_assignment_responseContext* SMTLIB2Parser::get_assignment_response() {
  Get_assignment_responseContext *_localctx = _tracker.createInstance<Get_assignment_responseContext>(_ctx, getState());
  enterRule(_localctx, 78, SMTLIB2Parser::RuleGet_assignment_response);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(613);
    match(SMTLIB2Parser::OpenPar);
    setState(617);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SMTLIB2Parser::OpenPar) {
      setState(614);
      t_valuation_pair();
      setState(619);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(620);
    match(SMTLIB2Parser::ClosePar);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Get_option_responseContext ------------------------------------------------------------------

SMTLIB2Parser::Get_option_responseContext::Get_option_responseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SMTLIB2Parser::Attribute_valueContext* SMTLIB2Parser::Get_option_responseContext::attribute_value() {
  return getRuleContext<SMTLIB2Parser::Attribute_valueContext>(0);
}


size_t SMTLIB2Parser::Get_option_responseContext::getRuleIndex() const {
  return SMTLIB2Parser::RuleGet_option_response;
}

void SMTLIB2Parser::Get_option_responseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_option_response(this);
}

void SMTLIB2Parser::Get_option_responseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SMTLIB2ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_option_response(this);
}


antlrcpp::Any SMTLIB2Parser::Get_option_responseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SMTLIB2ParserVisitor*>(visitor))
    return parserVisitor->visitGet_option_response(this);
  else
    return visitor->visitChildren(this);
}

SMTLIB2Parser::Get_option_responseContext* SMTLIB2Parser::get_option_response() {
  Get_option_responseContext *_localctx = _tracker.createInstance<Get_option_responseContext>(_ctx, getState());
  enterRule(_localctx, 80, SMTLIB2Parser::RuleGet_option_response);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(622);
    attribute_value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> SMTLIB2Parser::_decisionToDFA;
atn::PredictionContextCache SMTLIB2Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SMTLIB2Parser::_atn;
std::vector<uint16_t> SMTLIB2Parser::_serializedATN;

std::vector<std::string> SMTLIB2Parser::_ruleNames = {
  "symbol", "keyword", "spec_constant", "s_expr", "identifier", "sort", 
  "attribute_value", "attribute", "qual_identifier", "var_binding", "sorted_var", 
  "term", "sort_symbol_decl", "meta_spec_constant", "fun_symbol_decl", "par_fun_symbol_decl", 
  "theory_decl", "theory_attribute", "logic_attribute", "logic", "b_value", 
  "option", "info_flag", "command", "script", "gen_response", "error_behavior", 
  "reason_unknown", "status", "info_response", "get_info_response", "check_sat_response", 
  "get_assertions_response", "proof", "get_proof_response", "get_unsat_core_response", 
  "valuation_pair", "get_value_response", "t_valuation_pair", "get_assignment_response", 
  "get_option_response"
};

std::vector<std::string> SMTLIB2Parser::_literalNames = {
  "", "'and'", "'or'", "'not'", "'Bool'", "'continued-execution'", "'error'", 
  "'false'", "'immediate-exit'", "'incomplete'", "'logic'", "'memout'", 
  "'sat'", "'success'", "'theory'", "'true'", "'unknown'", "'unsat'", "'unsupported'", 
  "':all-statistics'", "':authors'", "':axioms'", "':chainable'", "':definition'", 
  "':diagnostic-output-channel'", "':error-behavior'", "':expand-definitions'", 
  "':extensions'", "':funs'", "':funs-description'", "':interactive-mode'", 
  "':language'", "':left-assoc'", "':name'", "':named'", "':notes'", "':print-success'", 
  "':produce-assignments'", "':produce-models'", "':produce-proofs'", "':produce-unsat-cores'", 
  "':random-seed'", "':reason-unknown'", "':regular-output-channel'", "':right-assoc'", 
  "':sorts'", "':sorts-description'", "':status'", "':theories'", "':values'", 
  "':verbosity'", "':version'", "'!'", "'_'", "'as'", "'DECIMAL'", "'exists'", 
  "'forall'", "'let'", "'NUMERAL'", "'par'", "'STRING'", "'assert'", "'check-sat'", 
  "'declare-sort'", "'declare-fun'", "'define-sort'", "'define-fun'", "'exit'", 
  "'get-assertions'", "'get-assignment'", "'get-info'", "'get-option'", 
  "'get-proof'", "'get-unsat-core'", "'get-value'", "'pop'", "'push'", "'set-logic'", 
  "'set-info'", "'set-option'", "'get-model'", "", "", "", "", "", "", "", 
  "", "", "", "'('", "')'"
};

std::vector<std::string> SMTLIB2Parser::_symbolicNames = {
  "", "SYM_AND", "SYM_OR", "SYM_NOT", "SYM_BOOL", "SYM_CONTINUED_EXECUTION", 
  "SYM_ERROR", "SYM_FALSE", "SYM_IMMEDIATE_EXIT", "SYM_INCOMPLETE", "SYM_LOGIC", 
  "SYM_MEMOUT", "SYM_SAT", "SYM_SUCCESS", "SYM_THEORY", "SYM_TRUE", "SYM_UNKNOWN", 
  "SYM_UNSAT", "SYM_UNSUPPORTED", "KEYWORD_ALL_STATISTICS", "KEYWORD_AUTHORS", 
  "KEYWORD_AXIOMS", "KEYWORD_CHAINABLE", "KEYWORD_DEFINITION", "KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL", 
  "KEYWORD_ERROR_BEHAVIOR", "KEYWORD_EXPAND_DEFINITIONS", "KEYWORD_EXTENSIONS", 
  "KEYWORD_FUNS", "KEYWORD_FUNS_DESCRIPTION", "KEYWORD_INTERACTIVE_MODE", 
  "KEYWORD_LANGUAGE", "KEYWORD_LEFT_ASSOC", "KEYWORD_NAME", "KEYWORD_NAMED", 
  "KEYWORD_NOTES", "KEYWORD_PRINT_SUCCESS", "KEYWORD_PRODUCE_ASSIGNMENTS", 
  "KEYWORD_PRODUCE_MODELS", "KEYWORD_PRODUCE_PROOFS", "KEYWORD_PRODUCE_UNSAT_CORES", 
  "KEYWORD_RANDOM_SEED", "KEYWORD_REASON_UNKNOWN", "KEYWORD_REGULAR_OUTPUT_CHANNEL", 
  "KEYWORD_RIGHT_ASSOC", "KEYWORD_SORTS", "KEYWORD_SORTS_DESCRIPTION", "KEYWORD_STATUS", 
  "KEYWORD_THEORIES", "KEYWORD_VALUES", "KEYWORD_VERBOSITY", "KEYWORD_VERSION", 
  "TOKEN_BANG", "TOKEN_UNDERSCORE", "TOKEN_AS", "TOKEN_DECIMAL", "TOKEN_EXISTS", 
  "TOKEN_FORALL", "TOKEN_LET", "TOKEN_NUMERAL", "TOKEN_PAR", "TOKEN_STRING", 
  "TOKEN_CMD_ASSERT", "TOKEN_CMD_CHECK_SAT", "TOKEN_CMD_DECLARE_SORT", "TOKEN_CMD_DECLARE_FUN", 
  "TOKEN_CMD_DEFINE_SORT", "TOKEN_CMD_DEFINE_FUN", "TOKEN_CMD_EXIT", "TOKEN_CMD_GET_ASSERTIONS", 
  "TOKEN_CMD_GET_ASSIGNMENT", "TOKEN_CMD_GET_INFO", "TOKEN_CMD_GET_OPTION", 
  "TOKEN_CMD_GET_PROOF", "TOKEN_CMD_GET_UNSAT_CORE", "TOKEN_CMD_GET_VALUE", 
  "TOKEN_CMD_POP", "TOKEN_CMD_PUSH", "TOKEN_CMD_SET_LOGIC", "TOKEN_CMD_SET_INFO", 
  "TOKEN_CMD_SET_OPTION", "TOKEN_CMD_GET_MODEL", "NUMERAL", "DECIMAL", "HEXADECIMAL", 
  "BINARY", "STRING", "WS", "SIMPLE_SYM", "QUOTED_SYM", "COMMENT", "KEYWORD_TOKEN", 
  "OpenPar", "ClosePar"
};

dfa::Vocabulary SMTLIB2Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SMTLIB2Parser::_tokenNames;

SMTLIB2Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x5f, 0x273, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x7, 0x5, 0x60, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x63, 0xb, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0x66, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x6, 0x6, 0x6d, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x6e, 
    0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x73, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x6, 0x7, 0x79, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x7a, 0x3, 
    0x7, 0x3, 0x7, 0x5, 0x7, 0x7f, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x7, 0x8, 0x85, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x88, 0xb, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0x8b, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x5, 0x9, 0x91, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x9a, 0xa, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x6, 
    0xd, 0xab, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0xac, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x6, 0xd, 0xb5, 0xa, 0xd, 0xd, 0xd, 
    0xe, 0xd, 0xb6, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x6, 0xd, 0xc1, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 
    0xc2, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x6, 0xd, 0xcd, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0xce, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x6, 0xd, 0xd9, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0xda, 0x3, 0xd, 0x3, 
    0xd, 0x5, 0xd, 0xdf, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x7, 0xe, 0xe5, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xe8, 0xb, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x7, 0x10, 0xf2, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0xf5, 0xb, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 
    0x10, 0xfd, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x100, 0xb, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x6, 0x10, 0x107, 
    0xa, 0x10, 0xd, 0x10, 0xe, 0x10, 0x108, 0x3, 0x10, 0x7, 0x10, 0x10c, 
    0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x10f, 0xb, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x5, 0x10, 0x113, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x6, 0x11, 0x11a, 0xa, 0x11, 0xd, 0x11, 0xe, 0x11, 0x11b, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x6, 0x11, 0x122, 0xa, 0x11, 
    0xd, 0x11, 0xe, 0x11, 0x123, 0x3, 0x11, 0x7, 0x11, 0x127, 0xa, 0x11, 
    0xc, 0x11, 0xe, 0x11, 0x12a, 0xb, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x5, 0x11, 0x12f, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 
    0x134, 0xa, 0x12, 0x3, 0x12, 0x6, 0x12, 0x137, 0xa, 0x12, 0xd, 0x12, 
    0xe, 0x12, 0x138, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x6, 0x13, 0x140, 0xa, 0x13, 0xd, 0x13, 0xe, 0x13, 0x141, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x6, 0x13, 0x149, 0xa, 0x13, 
    0xd, 0x13, 0xe, 0x13, 0x14a, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x15a, 0xa, 0x13, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x6, 0x14, 0x15f, 0xa, 0x14, 0xd, 0x14, 0xe, 0x14, 
    0x160, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x16e, 
    0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x6, 0x15, 0x174, 
    0xa, 0x15, 0xd, 0x15, 0xe, 0x15, 0x175, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x193, 
    0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x19d, 0xa, 0x18, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 
    0x1b9, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x1bc, 0xb, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x7, 0x19, 0x1c7, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 
    0x1ca, 0xb, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 0x1d5, 0xa, 0x19, 
    0xc, 0x19, 0xe, 0x19, 0x1d8, 0xb, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x6, 0x19, 0x1fc, 
    0xa, 0x19, 0xd, 0x19, 0xe, 0x19, 0x1fd, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 
    0x19, 0x216, 0xa, 0x19, 0x3, 0x1a, 0x6, 0x1a, 0x219, 0xa, 0x1a, 0xd, 
    0x1a, 0xe, 0x1a, 0x21a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x223, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x236, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 
    0x6, 0x20, 0x23a, 0xa, 0x20, 0xd, 0x20, 0xe, 0x20, 0x23b, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x6, 0x22, 0x244, 
    0xa, 0x22, 0xd, 0x22, 0xe, 0x22, 0x245, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 0x25, 0x6, 0x25, 0x250, 
    0xa, 0x25, 0xd, 0x25, 0xe, 0x25, 0x251, 0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x6, 
    0x27, 0x25d, 0xa, 0x27, 0xd, 0x27, 0xe, 0x27, 0x25e, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 
    0x3, 0x29, 0x7, 0x29, 0x26a, 0xa, 0x29, 0xc, 0x29, 0xe, 0x29, 0x26d, 
    0xb, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x2, 
    0x2, 0x2b, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 
    0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x2, 0xa, 0x4, 0x2, 0x3, 0x14, 0x5a, 
    0x5b, 0x4, 0x2, 0x15, 0x35, 0x5d, 0x5d, 0x3, 0x2, 0x54, 0x58, 0x5, 0x2, 
    0x39, 0x39, 0x3d, 0x3d, 0x3f, 0x3f, 0x4, 0x2, 0x9, 0x9, 0x11, 0x11, 
    0x4, 0x2, 0x7, 0x7, 0xa, 0xa, 0x4, 0x2, 0xb, 0xb, 0xd, 0xd, 0x4, 0x2, 
    0xe, 0xe, 0x12, 0x13, 0x2, 0x2b4, 0x2, 0x54, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x56, 0x3, 0x2, 0x2, 0x2, 0x6, 0x58, 0x3, 0x2, 0x2, 0x2, 0x8, 0x65, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x72, 0x3, 0x2, 0x2, 0x2, 0xc, 0x7e, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x90, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x99, 0x3, 0x2, 0x2, 0x2, 0x14, 0x9b, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x18, 0xde, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0xe0, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xeb, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x112, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x22, 0x130, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x159, 0x3, 0x2, 0x2, 0x2, 0x26, 0x16d, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x179, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x192, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x19c, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x215, 0x3, 0x2, 0x2, 0x2, 0x32, 0x218, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0x222, 0x3, 0x2, 0x2, 0x2, 0x36, 0x224, 0x3, 0x2, 0x2, 0x2, 0x38, 0x226, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x228, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x235, 0x3, 
    0x2, 0x2, 0x2, 0x3e, 0x237, 0x3, 0x2, 0x2, 0x2, 0x40, 0x23f, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x241, 0x3, 0x2, 0x2, 0x2, 0x44, 0x249, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x48, 0x24d, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x255, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x262, 0x3, 0x2, 0x2, 0x2, 0x50, 0x267, 0x3, 0x2, 0x2, 0x2, 0x52, 0x270, 
    0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x9, 0x2, 0x2, 0x2, 0x55, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x56, 0x57, 0x9, 0x3, 0x2, 0x2, 0x57, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x58, 0x59, 0x9, 0x4, 0x2, 0x2, 0x59, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x66, 0x5, 0x6, 0x4, 0x2, 0x5b, 0x66, 0x5, 0x2, 0x2, 0x2, 
    0x5c, 0x66, 0x5, 0x4, 0x3, 0x2, 0x5d, 0x61, 0x7, 0x5e, 0x2, 0x2, 0x5e, 
    0x60, 0x5, 0x8, 0x5, 0x2, 0x5f, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x63, 
    0x3, 0x2, 0x2, 0x2, 0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x3, 
    0x2, 0x2, 0x2, 0x62, 0x64, 0x3, 0x2, 0x2, 0x2, 0x63, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x66, 0x7, 0x5f, 0x2, 0x2, 0x65, 0x5a, 0x3, 0x2, 0x2, 
    0x2, 0x65, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x65, 0x5c, 0x3, 0x2, 0x2, 0x2, 
    0x65, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x66, 0x9, 0x3, 0x2, 0x2, 0x2, 0x67, 
    0x73, 0x5, 0x2, 0x2, 0x2, 0x68, 0x69, 0x7, 0x5e, 0x2, 0x2, 0x69, 0x6a, 
    0x7, 0x37, 0x2, 0x2, 0x6a, 0x6c, 0x5, 0x2, 0x2, 0x2, 0x6b, 0x6d, 0x7, 
    0x54, 0x2, 0x2, 0x6c, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 
    0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x3, 0x2, 0x2, 
    0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x7, 0x5f, 0x2, 0x2, 
    0x71, 0x73, 0x3, 0x2, 0x2, 0x2, 0x72, 0x67, 0x3, 0x2, 0x2, 0x2, 0x72, 
    0x68, 0x3, 0x2, 0x2, 0x2, 0x73, 0xb, 0x3, 0x2, 0x2, 0x2, 0x74, 0x7f, 
    0x5, 0xa, 0x6, 0x2, 0x75, 0x76, 0x7, 0x5e, 0x2, 0x2, 0x76, 0x78, 0x5, 
    0xa, 0x6, 0x2, 0x77, 0x79, 0x5, 0xc, 0x7, 0x2, 0x78, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x78, 0x3, 0x2, 0x2, 
    0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 
    0x7c, 0x7d, 0x7, 0x5f, 0x2, 0x2, 0x7d, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7e, 
    0x74, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x75, 0x3, 0x2, 0x2, 0x2, 0x7f, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x80, 0x8b, 0x5, 0x2, 0x2, 0x2, 0x81, 0x8b, 0x5, 
    0x6, 0x4, 0x2, 0x82, 0x86, 0x7, 0x5e, 0x2, 0x2, 0x83, 0x85, 0x5, 0x8, 
    0x5, 0x2, 0x84, 0x83, 0x3, 0x2, 0x2, 0x2, 0x85, 0x88, 0x3, 0x2, 0x2, 
    0x2, 0x86, 0x84, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x3, 0x2, 0x2, 0x2, 
    0x87, 0x89, 0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x89, 
    0x8b, 0x7, 0x5f, 0x2, 0x2, 0x8a, 0x80, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x81, 
    0x3, 0x2, 0x2, 0x2, 0x8a, 0x82, 0x3, 0x2, 0x2, 0x2, 0x8b, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x8c, 0x91, 0x5, 0x4, 0x3, 0x2, 0x8d, 0x8e, 0x5, 0x4, 
    0x3, 0x2, 0x8e, 0x8f, 0x5, 0xe, 0x8, 0x2, 0x8f, 0x91, 0x3, 0x2, 0x2, 
    0x2, 0x90, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8d, 0x3, 0x2, 0x2, 0x2, 
    0x91, 0x11, 0x3, 0x2, 0x2, 0x2, 0x92, 0x9a, 0x5, 0xa, 0x6, 0x2, 0x93, 
    0x94, 0x7, 0x5e, 0x2, 0x2, 0x94, 0x95, 0x7, 0x38, 0x2, 0x2, 0x95, 0x96, 
    0x5, 0xa, 0x6, 0x2, 0x96, 0x97, 0x5, 0xc, 0x7, 0x2, 0x97, 0x98, 0x7, 
    0x5f, 0x2, 0x2, 0x98, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x99, 0x92, 0x3, 0x2, 
    0x2, 0x2, 0x99, 0x93, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x9b, 0x9c, 0x7, 0x5e, 0x2, 0x2, 0x9c, 0x9d, 0x5, 0x2, 0x2, 0x2, 
    0x9d, 0x9e, 0x5, 0x18, 0xd, 0x2, 0x9e, 0x9f, 0x7, 0x5f, 0x2, 0x2, 0x9f, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x5e, 0x2, 0x2, 0xa1, 0xa2, 
    0x5, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x5, 0xc, 0x7, 0x2, 0xa3, 0xa4, 0x7, 
    0x5f, 0x2, 0x2, 0xa4, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xdf, 0x5, 0x6, 
    0x4, 0x2, 0xa6, 0xdf, 0x5, 0x12, 0xa, 0x2, 0xa7, 0xa8, 0x7, 0x5e, 0x2, 
    0x2, 0xa8, 0xaa, 0x5, 0x12, 0xa, 0x2, 0xa9, 0xab, 0x5, 0x18, 0xd, 0x2, 
    0xaa, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x3, 0x2, 0x2, 0x2, 0xac, 
    0xaa, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 
    0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x7, 0x5f, 0x2, 0x2, 0xaf, 0xdf, 0x3, 
    0x2, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x5e, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0x3c, 
    0x2, 0x2, 0xb2, 0xb4, 0x7, 0x5e, 0x2, 0x2, 0xb3, 0xb5, 0x5, 0x14, 0xb, 
    0x2, 0xb4, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x3, 0x2, 0x2, 0x2, 
    0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xb7, 
    0xb8, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0x5f, 0x2, 0x2, 0xb9, 0xba, 
    0x5, 0x18, 0xd, 0x2, 0xba, 0xbb, 0x7, 0x5f, 0x2, 0x2, 0xbb, 0xdf, 0x3, 
    0x2, 0x2, 0x2, 0xbc, 0xbd, 0x7, 0x5e, 0x2, 0x2, 0xbd, 0xbe, 0x7, 0x3b, 
    0x2, 0x2, 0xbe, 0xc0, 0x7, 0x5e, 0x2, 0x2, 0xbf, 0xc1, 0x5, 0x16, 0xc, 
    0x2, 0xc0, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 
    0xc2, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc3, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x5f, 0x2, 0x2, 0xc5, 0xc6, 
    0x5, 0x18, 0xd, 0x2, 0xc6, 0xc7, 0x7, 0x5f, 0x2, 0x2, 0xc7, 0xdf, 0x3, 
    0x2, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0x5e, 0x2, 0x2, 0xc9, 0xca, 0x7, 0x3a, 
    0x2, 0x2, 0xca, 0xcc, 0x7, 0x5e, 0x2, 0x2, 0xcb, 0xcd, 0x5, 0x16, 0xc, 
    0x2, 0xcc, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 
    0xd0, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd1, 0x7, 0x5f, 0x2, 0x2, 0xd1, 0xd2, 
    0x5, 0x18, 0xd, 0x2, 0xd2, 0xd3, 0x7, 0x5f, 0x2, 0x2, 0xd3, 0xdf, 0x3, 
    0x2, 0x2, 0x2, 0xd4, 0xd5, 0x7, 0x5e, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x36, 
    0x2, 0x2, 0xd6, 0xd8, 0x5, 0x18, 0xd, 0x2, 0xd7, 0xd9, 0x5, 0x10, 0x9, 
    0x2, 0xd8, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 0x2, 0x2, 0x2, 
    0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 
    0xdc, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x5f, 0x2, 0x2, 0xdd, 0xdf, 
    0x3, 0x2, 0x2, 0x2, 0xde, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xde, 0xa6, 0x3, 
    0x2, 0x2, 0x2, 0xde, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xde, 0xb0, 0x3, 0x2, 
    0x2, 0x2, 0xde, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xde, 0xc8, 0x3, 0x2, 0x2, 
    0x2, 0xde, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xdf, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0xe0, 0xe1, 0x7, 0x5e, 0x2, 0x2, 0xe1, 0xe2, 0x5, 0xa, 0x6, 0x2, 0xe2, 
    0xe6, 0x7, 0x54, 0x2, 0x2, 0xe3, 0xe5, 0x5, 0x10, 0x9, 0x2, 0xe4, 0xe3, 
    0x3, 0x2, 0x2, 0x2, 0xe5, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe4, 0x3, 
    0x2, 0x2, 0x2, 0xe6, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe9, 0x3, 0x2, 
    0x2, 0x2, 0xe8, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x7, 0x5f, 0x2, 
    0x2, 0xea, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xec, 0x9, 0x5, 0x2, 0x2, 
    0xec, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x7, 0x5e, 0x2, 0x2, 0xee, 
    0xef, 0x5, 0x6, 0x4, 0x2, 0xef, 0xf3, 0x5, 0xc, 0x7, 0x2, 0xf0, 0xf2, 
    0x5, 0x10, 0x9, 0x2, 0xf1, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf5, 0x3, 
    0x2, 0x2, 0x2, 0xf3, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf4, 0x3, 0x2, 
    0x2, 0x2, 0xf4, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf3, 0x3, 0x2, 0x2, 
    0x2, 0xf6, 0xf7, 0x7, 0x5f, 0x2, 0x2, 0xf7, 0x113, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xf9, 0x7, 0x5e, 0x2, 0x2, 0xf9, 0xfa, 0x5, 0x1c, 0xf, 0x2, 0xfa, 
    0xfe, 0x5, 0xc, 0x7, 0x2, 0xfb, 0xfd, 0x5, 0x10, 0x9, 0x2, 0xfc, 0xfb, 
    0x3, 0x2, 0x2, 0x2, 0xfd, 0x100, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xfc, 0x3, 
    0x2, 0x2, 0x2, 0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 0xff, 0x101, 0x3, 0x2, 
    0x2, 0x2, 0x100, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x7, 0x5f, 
    0x2, 0x2, 0x102, 0x113, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x7, 0x5e, 
    0x2, 0x2, 0x104, 0x106, 0x5, 0xa, 0x6, 0x2, 0x105, 0x107, 0x5, 0xc, 
    0x7, 0x2, 0x106, 0x105, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 0x3, 0x2, 
    0x2, 0x2, 0x108, 0x106, 0x3, 0x2, 0x2, 0x2, 0x108, 0x109, 0x3, 0x2, 
    0x2, 0x2, 0x109, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10c, 0x5, 0x10, 
    0x9, 0x2, 0x10b, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10f, 0x3, 0x2, 
    0x2, 0x2, 0x10d, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x3, 0x2, 
    0x2, 0x2, 0x10e, 0x110, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x10d, 0x3, 0x2, 
    0x2, 0x2, 0x110, 0x111, 0x7, 0x5f, 0x2, 0x2, 0x111, 0x113, 0x3, 0x2, 
    0x2, 0x2, 0x112, 0xed, 0x3, 0x2, 0x2, 0x2, 0x112, 0xf8, 0x3, 0x2, 0x2, 
    0x2, 0x112, 0x103, 0x3, 0x2, 0x2, 0x2, 0x113, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x114, 0x12f, 0x5, 0x1e, 0x10, 0x2, 0x115, 0x116, 0x7, 0x5e, 0x2, 0x2, 
    0x116, 0x117, 0x7, 0x3e, 0x2, 0x2, 0x117, 0x119, 0x7, 0x5e, 0x2, 0x2, 
    0x118, 0x11a, 0x5, 0x2, 0x2, 0x2, 0x119, 0x118, 0x3, 0x2, 0x2, 0x2, 
    0x11a, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x119, 0x3, 0x2, 0x2, 0x2, 
    0x11b, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11d, 0x3, 0x2, 0x2, 0x2, 
    0x11d, 0x11e, 0x7, 0x5f, 0x2, 0x2, 0x11e, 0x11f, 0x7, 0x5e, 0x2, 0x2, 
    0x11f, 0x121, 0x5, 0xa, 0x6, 0x2, 0x120, 0x122, 0x5, 0xc, 0x7, 0x2, 
    0x121, 0x120, 0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x3, 0x2, 0x2, 0x2, 
    0x123, 0x121, 0x3, 0x2, 0x2, 0x2, 0x123, 0x124, 0x3, 0x2, 0x2, 0x2, 
    0x124, 0x128, 0x3, 0x2, 0x2, 0x2, 0x125, 0x127, 0x5, 0x10, 0x9, 0x2, 
    0x126, 0x125, 0x3, 0x2, 0x2, 0x2, 0x127, 0x12a, 0x3, 0x2, 0x2, 0x2, 
    0x128, 0x126, 0x3, 0x2, 0x2, 0x2, 0x128, 0x129, 0x3, 0x2, 0x2, 0x2, 
    0x129, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x128, 0x3, 0x2, 0x2, 0x2, 
    0x12b, 0x12c, 0x7, 0x5f, 0x2, 0x2, 0x12c, 0x12d, 0x7, 0x5f, 0x2, 0x2, 
    0x12d, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x114, 0x3, 0x2, 0x2, 0x2, 
    0x12e, 0x115, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x21, 0x3, 0x2, 0x2, 0x2, 0x130, 
    0x131, 0x7, 0x5e, 0x2, 0x2, 0x131, 0x133, 0x7, 0x10, 0x2, 0x2, 0x132, 
    0x134, 0x5, 0x2, 0x2, 0x2, 0x133, 0x132, 0x3, 0x2, 0x2, 0x2, 0x133, 
    0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x136, 0x3, 0x2, 0x2, 0x2, 0x135, 
    0x137, 0x5, 0x24, 0x13, 0x2, 0x136, 0x135, 0x3, 0x2, 0x2, 0x2, 0x137, 
    0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 0x136, 0x3, 0x2, 0x2, 0x2, 0x138, 
    0x139, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x13a, 
    0x13b, 0x7, 0x5f, 0x2, 0x2, 0x13b, 0x23, 0x3, 0x2, 0x2, 0x2, 0x13c, 
    0x13d, 0x7, 0x2f, 0x2, 0x2, 0x13d, 0x13f, 0x7, 0x5e, 0x2, 0x2, 0x13e, 
    0x140, 0x5, 0x1a, 0xe, 0x2, 0x13f, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x140, 
    0x141, 0x3, 0x2, 0x2, 0x2, 0x141, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x141, 
    0x142, 0x3, 0x2, 0x2, 0x2, 0x142, 0x143, 0x3, 0x2, 0x2, 0x2, 0x143, 
    0x144, 0x7, 0x5f, 0x2, 0x2, 0x144, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x145, 
    0x146, 0x7, 0x1e, 0x2, 0x2, 0x146, 0x148, 0x7, 0x5e, 0x2, 0x2, 0x147, 
    0x149, 0x5, 0x20, 0x11, 0x2, 0x148, 0x147, 0x3, 0x2, 0x2, 0x2, 0x149, 
    0x14a, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14a, 
    0x14b, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14c, 
    0x14d, 0x7, 0x5f, 0x2, 0x2, 0x14d, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x14e, 
    0x14f, 0x7, 0x30, 0x2, 0x2, 0x14f, 0x15a, 0x7, 0x58, 0x2, 0x2, 0x150, 
    0x151, 0x7, 0x1f, 0x2, 0x2, 0x151, 0x15a, 0x7, 0x58, 0x2, 0x2, 0x152, 
    0x153, 0x7, 0x19, 0x2, 0x2, 0x153, 0x15a, 0x7, 0x58, 0x2, 0x2, 0x154, 
    0x155, 0x7, 0x33, 0x2, 0x2, 0x155, 0x15a, 0x7, 0x58, 0x2, 0x2, 0x156, 
    0x157, 0x7, 0x25, 0x2, 0x2, 0x157, 0x15a, 0x7, 0x58, 0x2, 0x2, 0x158, 
    0x15a, 0x5, 0x10, 0x9, 0x2, 0x159, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x159, 
    0x145, 0x3, 0x2, 0x2, 0x2, 0x159, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x159, 
    0x150, 0x3, 0x2, 0x2, 0x2, 0x159, 0x152, 0x3, 0x2, 0x2, 0x2, 0x159, 
    0x154, 0x3, 0x2, 0x2, 0x2, 0x159, 0x156, 0x3, 0x2, 0x2, 0x2, 0x159, 
    0x158, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x25, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 
    0x7, 0x32, 0x2, 0x2, 0x15c, 0x15e, 0x7, 0x5e, 0x2, 0x2, 0x15d, 0x15f, 
    0x5, 0x2, 0x2, 0x2, 0x15e, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 
    0x3, 0x2, 0x2, 0x2, 0x160, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x160, 0x161, 
    0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 
    0x7, 0x5f, 0x2, 0x2, 0x163, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x164, 0x165, 
    0x7, 0x21, 0x2, 0x2, 0x165, 0x16e, 0x7, 0x58, 0x2, 0x2, 0x166, 0x167, 
    0x7, 0x1d, 0x2, 0x2, 0x167, 0x16e, 0x7, 0x58, 0x2, 0x2, 0x168, 0x169, 
    0x7, 0x33, 0x2, 0x2, 0x169, 0x16e, 0x7, 0x58, 0x2, 0x2, 0x16a, 0x16b, 
    0x7, 0x25, 0x2, 0x2, 0x16b, 0x16e, 0x7, 0x58, 0x2, 0x2, 0x16c, 0x16e, 
    0x5, 0x10, 0x9, 0x2, 0x16d, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x164, 
    0x3, 0x2, 0x2, 0x2, 0x16d, 0x166, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x168, 
    0x3, 0x2, 0x2, 0x2, 0x16d, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x16c, 
    0x3, 0x2, 0x2, 0x2, 0x16e, 0x27, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x7, 
    0x5e, 0x2, 0x2, 0x170, 0x171, 0x7, 0xc, 0x2, 0x2, 0x171, 0x173, 0x5, 
    0x2, 0x2, 0x2, 0x172, 0x174, 0x5, 0x26, 0x14, 0x2, 0x173, 0x172, 0x3, 
    0x2, 0x2, 0x2, 0x174, 0x175, 0x3, 0x2, 0x2, 0x2, 0x175, 0x173, 0x3, 
    0x2, 0x2, 0x2, 0x175, 0x176, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 0x3, 
    0x2, 0x2, 0x2, 0x177, 0x178, 0x7, 0x5f, 0x2, 0x2, 0x178, 0x29, 0x3, 
    0x2, 0x2, 0x2, 0x179, 0x17a, 0x9, 0x6, 0x2, 0x2, 0x17a, 0x2b, 0x3, 0x2, 
    0x2, 0x2, 0x17b, 0x17c, 0x7, 0x26, 0x2, 0x2, 0x17c, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x17d, 0x17e, 0x7, 0x1c, 0x2, 0x2, 0x17e, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x17f, 0x180, 0x7, 0x20, 0x2, 0x2, 0x180, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x181, 0x182, 0x7, 0x29, 0x2, 0x2, 0x182, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x183, 0x184, 0x7, 0x2a, 0x2, 0x2, 0x184, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x185, 0x186, 0x7, 0x28, 0x2, 0x2, 0x186, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x187, 0x188, 0x7, 0x27, 0x2, 0x2, 0x188, 0x193, 0x5, 0x2a, 
    0x16, 0x2, 0x189, 0x18a, 0x7, 0x2d, 0x2, 0x2, 0x18a, 0x193, 0x7, 0x58, 
    0x2, 0x2, 0x18b, 0x18c, 0x7, 0x1a, 0x2, 0x2, 0x18c, 0x193, 0x7, 0x58, 
    0x2, 0x2, 0x18d, 0x18e, 0x7, 0x2b, 0x2, 0x2, 0x18e, 0x193, 0x7, 0x54, 
    0x2, 0x2, 0x18f, 0x190, 0x7, 0x34, 0x2, 0x2, 0x190, 0x193, 0x7, 0x54, 
    0x2, 0x2, 0x191, 0x193, 0x5, 0x10, 0x9, 0x2, 0x192, 0x17b, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x192, 0x17f, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x181, 0x3, 0x2, 0x2, 0x2, 0x192, 0x183, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x185, 0x3, 0x2, 0x2, 0x2, 0x192, 0x187, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x189, 0x3, 0x2, 0x2, 0x2, 0x192, 0x18b, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x192, 0x18f, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x191, 0x3, 0x2, 0x2, 0x2, 0x193, 0x2d, 0x3, 0x2, 0x2, 
    0x2, 0x194, 0x19d, 0x7, 0x1b, 0x2, 0x2, 0x195, 0x19d, 0x7, 0x23, 0x2, 
    0x2, 0x196, 0x19d, 0x7, 0x16, 0x2, 0x2, 0x197, 0x19d, 0x7, 0x35, 0x2, 
    0x2, 0x198, 0x19d, 0x7, 0x31, 0x2, 0x2, 0x199, 0x19d, 0x7, 0x2c, 0x2, 
    0x2, 0x19a, 0x19d, 0x5, 0x4, 0x3, 0x2, 0x19b, 0x19d, 0x7, 0x15, 0x2, 
    0x2, 0x19c, 0x194, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x195, 0x3, 0x2, 0x2, 
    0x2, 0x19c, 0x196, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x197, 0x3, 0x2, 0x2, 
    0x2, 0x19c, 0x198, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x199, 0x3, 0x2, 0x2, 
    0x2, 0x19c, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19b, 0x3, 0x2, 0x2, 
    0x2, 0x19d, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x19f, 0x7, 0x5e, 0x2, 
    0x2, 0x19f, 0x1a0, 0x7, 0x50, 0x2, 0x2, 0x1a0, 0x1a1, 0x5, 0x2, 0x2, 
    0x2, 0x1a1, 0x1a2, 0x7, 0x5f, 0x2, 0x2, 0x1a2, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x1a3, 0x1a4, 0x7, 0x5e, 0x2, 0x2, 0x1a4, 0x1a5, 0x7, 0x52, 0x2, 
    0x2, 0x1a5, 0x1a6, 0x5, 0x2c, 0x17, 0x2, 0x1a6, 0x1a7, 0x7, 0x5f, 0x2, 
    0x2, 0x1a7, 0x216, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1a9, 0x7, 0x5e, 0x2, 
    0x2, 0x1a9, 0x1aa, 0x7, 0x51, 0x2, 0x2, 0x1aa, 0x1ab, 0x5, 0x10, 0x9, 
    0x2, 0x1ab, 0x1ac, 0x7, 0x5f, 0x2, 0x2, 0x1ac, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x1ad, 0x1ae, 0x7, 0x5e, 0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x42, 0x2, 
    0x2, 0x1af, 0x1b0, 0x5, 0x2, 0x2, 0x2, 0x1b0, 0x1b1, 0x7, 0x54, 0x2, 
    0x2, 0x1b1, 0x1b2, 0x7, 0x5f, 0x2, 0x2, 0x1b2, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x1b3, 0x1b4, 0x7, 0x5e, 0x2, 0x2, 0x1b4, 0x1b5, 0x7, 0x44, 0x2, 
    0x2, 0x1b5, 0x1b6, 0x5, 0x2, 0x2, 0x2, 0x1b6, 0x1ba, 0x7, 0x5e, 0x2, 
    0x2, 0x1b7, 0x1b9, 0x5, 0x2, 0x2, 0x2, 0x1b8, 0x1b7, 0x3, 0x2, 0x2, 
    0x2, 0x1b9, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1b8, 0x3, 0x2, 0x2, 
    0x2, 0x1ba, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bd, 0x3, 0x2, 0x2, 
    0x2, 0x1bc, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1be, 0x7, 0x5f, 0x2, 
    0x2, 0x1be, 0x1bf, 0x5, 0xc, 0x7, 0x2, 0x1bf, 0x1c0, 0x7, 0x5f, 0x2, 
    0x2, 0x1c0, 0x216, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c2, 0x7, 0x5e, 0x2, 
    0x2, 0x1c2, 0x1c3, 0x7, 0x43, 0x2, 0x2, 0x1c3, 0x1c4, 0x5, 0x2, 0x2, 
    0x2, 0x1c4, 0x1c8, 0x7, 0x5e, 0x2, 0x2, 0x1c5, 0x1c7, 0x5, 0xc, 0x7, 
    0x2, 0x1c6, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1ca, 0x3, 0x2, 0x2, 
    0x2, 0x1c8, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1c9, 0x3, 0x2, 0x2, 
    0x2, 0x1c9, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1c8, 0x3, 0x2, 0x2, 
    0x2, 0x1cb, 0x1cc, 0x7, 0x5f, 0x2, 0x2, 0x1cc, 0x1cd, 0x5, 0xc, 0x7, 
    0x2, 0x1cd, 0x1ce, 0x7, 0x5f, 0x2, 0x2, 0x1ce, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x1cf, 0x1d0, 0x7, 0x5e, 0x2, 0x2, 0x1d0, 0x1d1, 0x7, 0x45, 0x2, 
    0x2, 0x1d1, 0x1d2, 0x5, 0x2, 0x2, 0x2, 0x1d2, 0x1d6, 0x7, 0x5e, 0x2, 
    0x2, 0x1d3, 0x1d5, 0x5, 0x16, 0xc, 0x2, 0x1d4, 0x1d3, 0x3, 0x2, 0x2, 
    0x2, 0x1d5, 0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1d4, 0x3, 0x2, 0x2, 
    0x2, 0x1d6, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d9, 0x3, 0x2, 0x2, 
    0x2, 0x1d8, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1d9, 0x1da, 0x7, 0x5f, 0x2, 
    0x2, 0x1da, 0x1db, 0x5, 0xc, 0x7, 0x2, 0x1db, 0x1dc, 0x5, 0x18, 0xd, 
    0x2, 0x1dc, 0x1dd, 0x7, 0x5f, 0x2, 0x2, 0x1dd, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x1de, 0x1df, 0x7, 0x5e, 0x2, 0x2, 0x1df, 0x1e0, 0x7, 0x4f, 0x2, 
    0x2, 0x1e0, 0x1e1, 0x7, 0x54, 0x2, 0x2, 0x1e1, 0x216, 0x7, 0x5f, 0x2, 
    0x2, 0x1e2, 0x1e3, 0x7, 0x5e, 0x2, 0x2, 0x1e3, 0x1e4, 0x7, 0x4e, 0x2, 
    0x2, 0x1e4, 0x1e5, 0x7, 0x54, 0x2, 0x2, 0x1e5, 0x216, 0x7, 0x5f, 0x2, 
    0x2, 0x1e6, 0x1e7, 0x7, 0x5e, 0x2, 0x2, 0x1e7, 0x1e8, 0x7, 0x40, 0x2, 
    0x2, 0x1e8, 0x1e9, 0x5, 0x18, 0xd, 0x2, 0x1e9, 0x1ea, 0x7, 0x5f, 0x2, 
    0x2, 0x1ea, 0x216, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 0x7, 0x5e, 0x2, 
    0x2, 0x1ec, 0x1ed, 0x7, 0x41, 0x2, 0x2, 0x1ed, 0x216, 0x7, 0x5f, 0x2, 
    0x2, 0x1ee, 0x1ef, 0x7, 0x5e, 0x2, 0x2, 0x1ef, 0x1f0, 0x7, 0x47, 0x2, 
    0x2, 0x1f0, 0x216, 0x7, 0x5f, 0x2, 0x2, 0x1f1, 0x1f2, 0x7, 0x5e, 0x2, 
    0x2, 0x1f2, 0x1f3, 0x7, 0x4b, 0x2, 0x2, 0x1f3, 0x216, 0x7, 0x5f, 0x2, 
    0x2, 0x1f4, 0x1f5, 0x7, 0x5e, 0x2, 0x2, 0x1f5, 0x1f6, 0x7, 0x4c, 0x2, 
    0x2, 0x1f6, 0x216, 0x7, 0x5f, 0x2, 0x2, 0x1f7, 0x1f8, 0x7, 0x5e, 0x2, 
    0x2, 0x1f8, 0x1f9, 0x7, 0x4d, 0x2, 0x2, 0x1f9, 0x1fb, 0x7, 0x5e, 0x2, 
    0x2, 0x1fa, 0x1fc, 0x5, 0x18, 0xd, 0x2, 0x1fb, 0x1fa, 0x3, 0x2, 0x2, 
    0x2, 0x1fc, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fb, 0x3, 0x2, 0x2, 
    0x2, 0x1fd, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x1ff, 0x3, 0x2, 0x2, 
    0x2, 0x1ff, 0x200, 0x7, 0x5f, 0x2, 0x2, 0x200, 0x201, 0x7, 0x5f, 0x2, 
    0x2, 0x201, 0x216, 0x3, 0x2, 0x2, 0x2, 0x202, 0x203, 0x7, 0x5e, 0x2, 
    0x2, 0x203, 0x204, 0x7, 0x48, 0x2, 0x2, 0x204, 0x216, 0x7, 0x5f, 0x2, 
    0x2, 0x205, 0x206, 0x7, 0x5e, 0x2, 0x2, 0x206, 0x207, 0x7, 0x4a, 0x2, 
    0x2, 0x207, 0x208, 0x5, 0x4, 0x3, 0x2, 0x208, 0x209, 0x7, 0x5f, 0x2, 
    0x2, 0x209, 0x216, 0x3, 0x2, 0x2, 0x2, 0x20a, 0x20b, 0x7, 0x5e, 0x2, 
    0x2, 0x20b, 0x20c, 0x7, 0x49, 0x2, 0x2, 0x20c, 0x20d, 0x5, 0x2e, 0x18, 
    0x2, 0x20d, 0x20e, 0x7, 0x5f, 0x2, 0x2, 0x20e, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x20f, 0x210, 0x7, 0x5e, 0x2, 0x2, 0x210, 0x211, 0x7, 0x46, 0x2, 
    0x2, 0x211, 0x216, 0x7, 0x5f, 0x2, 0x2, 0x212, 0x213, 0x7, 0x5e, 0x2, 
    0x2, 0x213, 0x214, 0x7, 0x53, 0x2, 0x2, 0x214, 0x216, 0x7, 0x5f, 0x2, 
    0x2, 0x215, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1a3, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1ad, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1c1, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1de, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1e6, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1ee, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x215, 0x1f4, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x215, 0x202, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x205, 0x3, 0x2, 0x2, 0x2, 0x215, 0x20a, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x20f, 0x3, 0x2, 0x2, 0x2, 0x215, 0x212, 0x3, 0x2, 0x2, 
    0x2, 0x216, 0x31, 0x3, 0x2, 0x2, 0x2, 0x217, 0x219, 0x5, 0x30, 0x19, 
    0x2, 0x218, 0x217, 0x3, 0x2, 0x2, 0x2, 0x219, 0x21a, 0x3, 0x2, 0x2, 
    0x2, 0x21a, 0x218, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x21b, 0x3, 0x2, 0x2, 
    0x2, 0x21b, 0x33, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x223, 0x7, 0x14, 0x2, 
    0x2, 0x21d, 0x223, 0x7, 0xf, 0x2, 0x2, 0x21e, 0x21f, 0x7, 0x5e, 0x2, 
    0x2, 0x21f, 0x220, 0x7, 0x8, 0x2, 0x2, 0x220, 0x221, 0x7, 0x58, 0x2, 
    0x2, 0x221, 0x223, 0x7, 0x5f, 0x2, 0x2, 0x222, 0x21c, 0x3, 0x2, 0x2, 
    0x2, 0x222, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x222, 0x21e, 0x3, 0x2, 0x2, 
    0x2, 0x223, 0x35, 0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 0x9, 0x7, 0x2, 0x2, 
    0x225, 0x37, 0x3, 0x2, 0x2, 0x2, 0x226, 0x227, 0x9, 0x8, 0x2, 0x2, 0x227, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x228, 0x229, 0x9, 0x9, 0x2, 0x2, 0x229, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0x22a, 0x22b, 0x7, 0x1b, 0x2, 0x2, 0x22b, 0x236, 
    0x5, 0x36, 0x1c, 0x2, 0x22c, 0x22d, 0x7, 0x23, 0x2, 0x2, 0x22d, 0x236, 
    0x7, 0x58, 0x2, 0x2, 0x22e, 0x22f, 0x7, 0x16, 0x2, 0x2, 0x22f, 0x236, 
    0x7, 0x58, 0x2, 0x2, 0x230, 0x231, 0x7, 0x35, 0x2, 0x2, 0x231, 0x236, 
    0x7, 0x58, 0x2, 0x2, 0x232, 0x233, 0x7, 0x2c, 0x2, 0x2, 0x233, 0x236, 
    0x5, 0x38, 0x1d, 0x2, 0x234, 0x236, 0x5, 0x10, 0x9, 0x2, 0x235, 0x22a, 
    0x3, 0x2, 0x2, 0x2, 0x235, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x235, 0x22e, 
    0x3, 0x2, 0x2, 0x2, 0x235, 0x230, 0x3, 0x2, 0x2, 0x2, 0x235, 0x232, 
    0x3, 0x2, 0x2, 0x2, 0x235, 0x234, 0x3, 0x2, 0x2, 0x2, 0x236, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x237, 0x239, 0x7, 0x5e, 0x2, 0x2, 0x238, 0x23a, 0x5, 
    0x3c, 0x1f, 0x2, 0x239, 0x238, 0x3, 0x2, 0x2, 0x2, 0x23a, 0x23b, 0x3, 
    0x2, 0x2, 0x2, 0x23b, 0x239, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23c, 0x3, 
    0x2, 0x2, 0x2, 0x23c, 0x23d, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23e, 0x7, 
    0x5f, 0x2, 0x2, 0x23e, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x240, 0x5, 
    0x3a, 0x1e, 0x2, 0x240, 0x41, 0x3, 0x2, 0x2, 0x2, 0x241, 0x243, 0x7, 
    0x5e, 0x2, 0x2, 0x242, 0x244, 0x5, 0x18, 0xd, 0x2, 0x243, 0x242, 0x3, 
    0x2, 0x2, 0x2, 0x244, 0x245, 0x3, 0x2, 0x2, 0x2, 0x245, 0x243, 0x3, 
    0x2, 0x2, 0x2, 0x245, 0x246, 0x3, 0x2, 0x2, 0x2, 0x246, 0x247, 0x3, 
    0x2, 0x2, 0x2, 0x247, 0x248, 0x7, 0x5f, 0x2, 0x2, 0x248, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x249, 0x24a, 0x5, 0x8, 0x5, 0x2, 0x24a, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x24b, 0x24c, 0x5, 0x44, 0x23, 0x2, 0x24c, 0x47, 0x3, 0x2, 
    0x2, 0x2, 0x24d, 0x24f, 0x7, 0x5e, 0x2, 0x2, 0x24e, 0x250, 0x5, 0x2, 
    0x2, 0x2, 0x24f, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x250, 0x251, 0x3, 0x2, 
    0x2, 0x2, 0x251, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x251, 0x252, 0x3, 0x2, 
    0x2, 0x2, 0x252, 0x253, 0x3, 0x2, 0x2, 0x2, 0x253, 0x254, 0x7, 0x5f, 
    0x2, 0x2, 0x254, 0x49, 0x3, 0x2, 0x2, 0x2, 0x255, 0x256, 0x7, 0x5e, 
    0x2, 0x2, 0x256, 0x257, 0x5, 0x18, 0xd, 0x2, 0x257, 0x258, 0x5, 0x18, 
    0xd, 0x2, 0x258, 0x259, 0x7, 0x5f, 0x2, 0x2, 0x259, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x25a, 0x25c, 0x7, 0x5e, 0x2, 0x2, 0x25b, 0x25d, 0x5, 0x4a, 
    0x26, 0x2, 0x25c, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25e, 0x3, 0x2, 
    0x2, 0x2, 0x25e, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x3, 0x2, 
    0x2, 0x2, 0x25f, 0x260, 0x3, 0x2, 0x2, 0x2, 0x260, 0x261, 0x7, 0x5f, 
    0x2, 0x2, 0x261, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x262, 0x263, 0x7, 0x5e, 
    0x2, 0x2, 0x263, 0x264, 0x5, 0x2, 0x2, 0x2, 0x264, 0x265, 0x5, 0x2a, 
    0x16, 0x2, 0x265, 0x266, 0x7, 0x5f, 0x2, 0x2, 0x266, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x267, 0x26b, 0x7, 0x5e, 0x2, 0x2, 0x268, 0x26a, 0x5, 0x4e, 
    0x28, 0x2, 0x269, 0x268, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x26d, 0x3, 0x2, 
    0x2, 0x2, 0x26b, 0x269, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x26c, 0x3, 0x2, 
    0x2, 0x2, 0x26c, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x26b, 0x3, 0x2, 
    0x2, 0x2, 0x26e, 0x26f, 0x7, 0x5f, 0x2, 0x2, 0x26f, 0x51, 0x3, 0x2, 
    0x2, 0x2, 0x270, 0x271, 0x5, 0xe, 0x8, 0x2, 0x271, 0x53, 0x3, 0x2, 0x2, 
    0x2, 0x33, 0x61, 0x65, 0x6e, 0x72, 0x7a, 0x7e, 0x86, 0x8a, 0x90, 0x99, 
    0xac, 0xb6, 0xc2, 0xce, 0xda, 0xde, 0xe6, 0xf3, 0xfe, 0x108, 0x10d, 
    0x112, 0x11b, 0x123, 0x128, 0x12e, 0x133, 0x138, 0x141, 0x14a, 0x159, 
    0x160, 0x16d, 0x175, 0x192, 0x19c, 0x1ba, 0x1c8, 0x1d6, 0x1fd, 0x215, 
    0x21a, 0x222, 0x235, 0x23b, 0x245, 0x251, 0x25e, 0x26b, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SMTLIB2Parser::Initializer SMTLIB2Parser::_init;
