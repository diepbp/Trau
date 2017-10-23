/* parser/listener/visitor header section */

// Generated from SMTLIB2Parser.g4 by ANTLR 4.7

#pragma once

/* base visitor preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB2ParserVisitor.h"

/* base visitor postinclude section */

namespace antlrcpptest {

/**
 * This class provides an empty implementation of SMTLIB2ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SMTLIB2ParserBaseVisitor : public SMTLIB2ParserVisitor {
public:
/* base visitor public declarations/members section */

  virtual antlrcpp::Any visitSymbol(SMTLIB2Parser::SymbolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKeyword(SMTLIB2Parser::KeywordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSpec_constant(SMTLIB2Parser::Spec_constantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitS_expr(SMTLIB2Parser::S_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(SMTLIB2Parser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSort(SMTLIB2Parser::SortContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttribute_value(SMTLIB2Parser::Attribute_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttribute(SMTLIB2Parser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQual_identifier(SMTLIB2Parser::Qual_identifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVar_binding(SMTLIB2Parser::Var_bindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSorted_var(SMTLIB2Parser::Sorted_varContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTerm(SMTLIB2Parser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSort_symbol_decl(SMTLIB2Parser::Sort_symbol_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMeta_spec_constant(SMTLIB2Parser::Meta_spec_constantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFun_symbol_decl(SMTLIB2Parser::Fun_symbol_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPar_fun_symbol_decl(SMTLIB2Parser::Par_fun_symbol_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheory_decl(SMTLIB2Parser::Theory_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheory_attribute(SMTLIB2Parser::Theory_attributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogic_attribute(SMTLIB2Parser::Logic_attributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogic(SMTLIB2Parser::LogicContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitB_value(SMTLIB2Parser::B_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOption(SMTLIB2Parser::OptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInfo_flag(SMTLIB2Parser::Info_flagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCommand(SMTLIB2Parser::CommandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitScript(SMTLIB2Parser::ScriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGen_response(SMTLIB2Parser::Gen_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitError_behavior(SMTLIB2Parser::Error_behaviorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReason_unknown(SMTLIB2Parser::Reason_unknownContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatus(SMTLIB2Parser::StatusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInfo_response(SMTLIB2Parser::Info_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_info_response(SMTLIB2Parser::Get_info_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCheck_sat_response(SMTLIB2Parser::Check_sat_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_assertions_response(SMTLIB2Parser::Get_assertions_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProof(SMTLIB2Parser::ProofContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_proof_response(SMTLIB2Parser::Get_proof_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_unsat_core_response(SMTLIB2Parser::Get_unsat_core_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValuation_pair(SMTLIB2Parser::Valuation_pairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_value_response(SMTLIB2Parser::Get_value_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitT_valuation_pair(SMTLIB2Parser::T_valuation_pairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_assignment_response(SMTLIB2Parser::Get_assignment_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_option_response(SMTLIB2Parser::Get_option_responseContext *ctx) override {
    return visitChildren(ctx);
  }


private:  
/* base visitor private declarations/members section */
};

}  // namespace antlrcpptest
