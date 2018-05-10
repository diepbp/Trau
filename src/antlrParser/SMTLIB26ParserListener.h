/* parser/listener/visitor header section */

// Generated from SMTLIB26Parser.g4 by ANTLR 4.7

#pragma once

/* listener preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB26Parser.h"

/* listener postinclude section */

namespace antlrcpptest {

/**
 * This interface defines an abstract listener for a parse tree produced by SMTLIB26Parser.
 */
class  SMTLIB26ParserListener : public antlr4::tree::ParseTreeListener {
public:
/* listener public declarations/members section */

  virtual void enterSymbol(SMTLIB26Parser::SymbolContext *ctx) = 0;
  virtual void exitSymbol(SMTLIB26Parser::SymbolContext *ctx) = 0;

  virtual void enterKeyword(SMTLIB26Parser::KeywordContext *ctx) = 0;
  virtual void exitKeyword(SMTLIB26Parser::KeywordContext *ctx) = 0;

  virtual void enterSpec_constant(SMTLIB26Parser::Spec_constantContext *ctx) = 0;
  virtual void exitSpec_constant(SMTLIB26Parser::Spec_constantContext *ctx) = 0;

  virtual void enterS_expr(SMTLIB26Parser::S_exprContext *ctx) = 0;
  virtual void exitS_expr(SMTLIB26Parser::S_exprContext *ctx) = 0;

  virtual void enterIdentifier(SMTLIB26Parser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(SMTLIB26Parser::IdentifierContext *ctx) = 0;

  virtual void enterSort(SMTLIB26Parser::SortContext *ctx) = 0;
  virtual void exitSort(SMTLIB26Parser::SortContext *ctx) = 0;

  virtual void enterAttribute_value(SMTLIB26Parser::Attribute_valueContext *ctx) = 0;
  virtual void exitAttribute_value(SMTLIB26Parser::Attribute_valueContext *ctx) = 0;

  virtual void enterAttribute(SMTLIB26Parser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(SMTLIB26Parser::AttributeContext *ctx) = 0;

  virtual void enterQual_identifier(SMTLIB26Parser::Qual_identifierContext *ctx) = 0;
  virtual void exitQual_identifier(SMTLIB26Parser::Qual_identifierContext *ctx) = 0;

  virtual void enterVar_binding(SMTLIB26Parser::Var_bindingContext *ctx) = 0;
  virtual void exitVar_binding(SMTLIB26Parser::Var_bindingContext *ctx) = 0;

  virtual void enterSorted_var(SMTLIB26Parser::Sorted_varContext *ctx) = 0;
  virtual void exitSorted_var(SMTLIB26Parser::Sorted_varContext *ctx) = 0;

  virtual void enterTerm(SMTLIB26Parser::TermContext *ctx) = 0;
  virtual void exitTerm(SMTLIB26Parser::TermContext *ctx) = 0;

  virtual void enterSort_symbol_decl(SMTLIB26Parser::Sort_symbol_declContext *ctx) = 0;
  virtual void exitSort_symbol_decl(SMTLIB26Parser::Sort_symbol_declContext *ctx) = 0;

  virtual void enterMeta_spec_constant(SMTLIB26Parser::Meta_spec_constantContext *ctx) = 0;
  virtual void exitMeta_spec_constant(SMTLIB26Parser::Meta_spec_constantContext *ctx) = 0;

  virtual void enterFun_symbol_decl(SMTLIB26Parser::Fun_symbol_declContext *ctx) = 0;
  virtual void exitFun_symbol_decl(SMTLIB26Parser::Fun_symbol_declContext *ctx) = 0;

  virtual void enterPar_fun_symbol_decl(SMTLIB26Parser::Par_fun_symbol_declContext *ctx) = 0;
  virtual void exitPar_fun_symbol_decl(SMTLIB26Parser::Par_fun_symbol_declContext *ctx) = 0;

  virtual void enterTheory_decl(SMTLIB26Parser::Theory_declContext *ctx) = 0;
  virtual void exitTheory_decl(SMTLIB26Parser::Theory_declContext *ctx) = 0;

  virtual void enterTheory_attribute(SMTLIB26Parser::Theory_attributeContext *ctx) = 0;
  virtual void exitTheory_attribute(SMTLIB26Parser::Theory_attributeContext *ctx) = 0;

  virtual void enterLogic_attribute(SMTLIB26Parser::Logic_attributeContext *ctx) = 0;
  virtual void exitLogic_attribute(SMTLIB26Parser::Logic_attributeContext *ctx) = 0;

  virtual void enterLogic(SMTLIB26Parser::LogicContext *ctx) = 0;
  virtual void exitLogic(SMTLIB26Parser::LogicContext *ctx) = 0;

  virtual void enterB_value(SMTLIB26Parser::B_valueContext *ctx) = 0;
  virtual void exitB_value(SMTLIB26Parser::B_valueContext *ctx) = 0;

  virtual void enterOption(SMTLIB26Parser::OptionContext *ctx) = 0;
  virtual void exitOption(SMTLIB26Parser::OptionContext *ctx) = 0;

  virtual void enterInfo_flag(SMTLIB26Parser::Info_flagContext *ctx) = 0;
  virtual void exitInfo_flag(SMTLIB26Parser::Info_flagContext *ctx) = 0;

  virtual void enterCommand(SMTLIB26Parser::CommandContext *ctx) = 0;
  virtual void exitCommand(SMTLIB26Parser::CommandContext *ctx) = 0;

  virtual void enterScript(SMTLIB26Parser::ScriptContext *ctx) = 0;
  virtual void exitScript(SMTLIB26Parser::ScriptContext *ctx) = 0;

  virtual void enterGen_response(SMTLIB26Parser::Gen_responseContext *ctx) = 0;
  virtual void exitGen_response(SMTLIB26Parser::Gen_responseContext *ctx) = 0;

  virtual void enterError_behavior(SMTLIB26Parser::Error_behaviorContext *ctx) = 0;
  virtual void exitError_behavior(SMTLIB26Parser::Error_behaviorContext *ctx) = 0;

  virtual void enterReason_unknown(SMTLIB26Parser::Reason_unknownContext *ctx) = 0;
  virtual void exitReason_unknown(SMTLIB26Parser::Reason_unknownContext *ctx) = 0;

  virtual void enterStatus(SMTLIB26Parser::StatusContext *ctx) = 0;
  virtual void exitStatus(SMTLIB26Parser::StatusContext *ctx) = 0;

  virtual void enterInfo_response(SMTLIB26Parser::Info_responseContext *ctx) = 0;
  virtual void exitInfo_response(SMTLIB26Parser::Info_responseContext *ctx) = 0;

  virtual void enterGet_info_response(SMTLIB26Parser::Get_info_responseContext *ctx) = 0;
  virtual void exitGet_info_response(SMTLIB26Parser::Get_info_responseContext *ctx) = 0;

  virtual void enterCheck_sat_response(SMTLIB26Parser::Check_sat_responseContext *ctx) = 0;
  virtual void exitCheck_sat_response(SMTLIB26Parser::Check_sat_responseContext *ctx) = 0;

  virtual void enterGet_assertions_response(SMTLIB26Parser::Get_assertions_responseContext *ctx) = 0;
  virtual void exitGet_assertions_response(SMTLIB26Parser::Get_assertions_responseContext *ctx) = 0;

  virtual void enterProof(SMTLIB26Parser::ProofContext *ctx) = 0;
  virtual void exitProof(SMTLIB26Parser::ProofContext *ctx) = 0;

  virtual void enterGet_proof_response(SMTLIB26Parser::Get_proof_responseContext *ctx) = 0;
  virtual void exitGet_proof_response(SMTLIB26Parser::Get_proof_responseContext *ctx) = 0;

  virtual void enterGet_unsat_core_response(SMTLIB26Parser::Get_unsat_core_responseContext *ctx) = 0;
  virtual void exitGet_unsat_core_response(SMTLIB26Parser::Get_unsat_core_responseContext *ctx) = 0;

  virtual void enterValuation_pair(SMTLIB26Parser::Valuation_pairContext *ctx) = 0;
  virtual void exitValuation_pair(SMTLIB26Parser::Valuation_pairContext *ctx) = 0;

  virtual void enterGet_value_response(SMTLIB26Parser::Get_value_responseContext *ctx) = 0;
  virtual void exitGet_value_response(SMTLIB26Parser::Get_value_responseContext *ctx) = 0;

  virtual void enterT_valuation_pair(SMTLIB26Parser::T_valuation_pairContext *ctx) = 0;
  virtual void exitT_valuation_pair(SMTLIB26Parser::T_valuation_pairContext *ctx) = 0;

  virtual void enterGet_assignment_response(SMTLIB26Parser::Get_assignment_responseContext *ctx) = 0;
  virtual void exitGet_assignment_response(SMTLIB26Parser::Get_assignment_responseContext *ctx) = 0;

  virtual void enterGet_option_response(SMTLIB26Parser::Get_option_responseContext *ctx) = 0;
  virtual void exitGet_option_response(SMTLIB26Parser::Get_option_responseContext *ctx) = 0;


private:  
/* listener private declarations/members section */
};

}  // namespace antlrcpptest
