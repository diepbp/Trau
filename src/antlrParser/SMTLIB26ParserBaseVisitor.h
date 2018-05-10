/* parser/listener/visitor header section */

// Generated from SMTLIB26Parser.g4 by ANTLR 4.7

#pragma once

/* base visitor preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB26ParserVisitor.h"

/* base visitor postinclude section */

namespace antlrcpptest {

/**
 * This class provides an empty implementation of SMTLIB26ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SMTLIB26ParserBaseVisitor : public SMTLIB26ParserVisitor {
public:
/* base visitor public declarations/members section */

  virtual antlrcpp::Any visitSymbol(SMTLIB26Parser::SymbolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKeyword(SMTLIB26Parser::KeywordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSpec_constant(SMTLIB26Parser::Spec_constantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitS_expr(SMTLIB26Parser::S_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(SMTLIB26Parser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSort(SMTLIB26Parser::SortContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttribute_value(SMTLIB26Parser::Attribute_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttribute(SMTLIB26Parser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQual_identifier(SMTLIB26Parser::Qual_identifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVar_binding(SMTLIB26Parser::Var_bindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSorted_var(SMTLIB26Parser::Sorted_varContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTerm(SMTLIB26Parser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSort_symbol_decl(SMTLIB26Parser::Sort_symbol_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMeta_spec_constant(SMTLIB26Parser::Meta_spec_constantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFun_symbol_decl(SMTLIB26Parser::Fun_symbol_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPar_fun_symbol_decl(SMTLIB26Parser::Par_fun_symbol_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheory_decl(SMTLIB26Parser::Theory_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheory_attribute(SMTLIB26Parser::Theory_attributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogic_attribute(SMTLIB26Parser::Logic_attributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogic(SMTLIB26Parser::LogicContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitB_value(SMTLIB26Parser::B_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOption(SMTLIB26Parser::OptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInfo_flag(SMTLIB26Parser::Info_flagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCommand(SMTLIB26Parser::CommandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitScript(SMTLIB26Parser::ScriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGen_response(SMTLIB26Parser::Gen_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitError_behavior(SMTLIB26Parser::Error_behaviorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReason_unknown(SMTLIB26Parser::Reason_unknownContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatus(SMTLIB26Parser::StatusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInfo_response(SMTLIB26Parser::Info_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_info_response(SMTLIB26Parser::Get_info_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCheck_sat_response(SMTLIB26Parser::Check_sat_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_assertions_response(SMTLIB26Parser::Get_assertions_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProof(SMTLIB26Parser::ProofContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_proof_response(SMTLIB26Parser::Get_proof_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_unsat_core_response(SMTLIB26Parser::Get_unsat_core_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValuation_pair(SMTLIB26Parser::Valuation_pairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_value_response(SMTLIB26Parser::Get_value_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitT_valuation_pair(SMTLIB26Parser::T_valuation_pairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_assignment_response(SMTLIB26Parser::Get_assignment_responseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGet_option_response(SMTLIB26Parser::Get_option_responseContext *ctx) override {
    return visitChildren(ctx);
  }


private:  
/* base visitor private declarations/members section */
};

}  // namespace antlrcpptest
