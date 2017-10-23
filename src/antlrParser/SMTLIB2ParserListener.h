/* parser/listener/visitor header section */

// Generated from SMTLIB2Parser.g4 by ANTLR 4.7

#pragma once

/* listener preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB2Parser.h"

/* listener postinclude section */

namespace antlrcpptest {

/**
 * This interface defines an abstract listener for a parse tree produced by SMTLIB2Parser.
 */
class  SMTLIB2ParserListener : public antlr4::tree::ParseTreeListener {
public:
/* listener public declarations/members section */

  virtual void enterSymbol(SMTLIB2Parser::SymbolContext *ctx) = 0;
  virtual void exitSymbol(SMTLIB2Parser::SymbolContext *ctx) = 0;

  virtual void enterKeyword(SMTLIB2Parser::KeywordContext *ctx) = 0;
  virtual void exitKeyword(SMTLIB2Parser::KeywordContext *ctx) = 0;

  virtual void enterSpec_constant(SMTLIB2Parser::Spec_constantContext *ctx) = 0;
  virtual void exitSpec_constant(SMTLIB2Parser::Spec_constantContext *ctx) = 0;

  virtual void enterS_expr(SMTLIB2Parser::S_exprContext *ctx) = 0;
  virtual void exitS_expr(SMTLIB2Parser::S_exprContext *ctx) = 0;

  virtual void enterIdentifier(SMTLIB2Parser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(SMTLIB2Parser::IdentifierContext *ctx) = 0;

  virtual void enterSort(SMTLIB2Parser::SortContext *ctx) = 0;
  virtual void exitSort(SMTLIB2Parser::SortContext *ctx) = 0;

  virtual void enterAttribute_value(SMTLIB2Parser::Attribute_valueContext *ctx) = 0;
  virtual void exitAttribute_value(SMTLIB2Parser::Attribute_valueContext *ctx) = 0;

  virtual void enterAttribute(SMTLIB2Parser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(SMTLIB2Parser::AttributeContext *ctx) = 0;

  virtual void enterQual_identifier(SMTLIB2Parser::Qual_identifierContext *ctx) = 0;
  virtual void exitQual_identifier(SMTLIB2Parser::Qual_identifierContext *ctx) = 0;

  virtual void enterVar_binding(SMTLIB2Parser::Var_bindingContext *ctx) = 0;
  virtual void exitVar_binding(SMTLIB2Parser::Var_bindingContext *ctx) = 0;

  virtual void enterSorted_var(SMTLIB2Parser::Sorted_varContext *ctx) = 0;
  virtual void exitSorted_var(SMTLIB2Parser::Sorted_varContext *ctx) = 0;

  virtual void enterTerm(SMTLIB2Parser::TermContext *ctx) = 0;
  virtual void exitTerm(SMTLIB2Parser::TermContext *ctx) = 0;

  virtual void enterSort_symbol_decl(SMTLIB2Parser::Sort_symbol_declContext *ctx) = 0;
  virtual void exitSort_symbol_decl(SMTLIB2Parser::Sort_symbol_declContext *ctx) = 0;

  virtual void enterMeta_spec_constant(SMTLIB2Parser::Meta_spec_constantContext *ctx) = 0;
  virtual void exitMeta_spec_constant(SMTLIB2Parser::Meta_spec_constantContext *ctx) = 0;

  virtual void enterFun_symbol_decl(SMTLIB2Parser::Fun_symbol_declContext *ctx) = 0;
  virtual void exitFun_symbol_decl(SMTLIB2Parser::Fun_symbol_declContext *ctx) = 0;

  virtual void enterPar_fun_symbol_decl(SMTLIB2Parser::Par_fun_symbol_declContext *ctx) = 0;
  virtual void exitPar_fun_symbol_decl(SMTLIB2Parser::Par_fun_symbol_declContext *ctx) = 0;

  virtual void enterTheory_decl(SMTLIB2Parser::Theory_declContext *ctx) = 0;
  virtual void exitTheory_decl(SMTLIB2Parser::Theory_declContext *ctx) = 0;

  virtual void enterTheory_attribute(SMTLIB2Parser::Theory_attributeContext *ctx) = 0;
  virtual void exitTheory_attribute(SMTLIB2Parser::Theory_attributeContext *ctx) = 0;

  virtual void enterLogic_attribute(SMTLIB2Parser::Logic_attributeContext *ctx) = 0;
  virtual void exitLogic_attribute(SMTLIB2Parser::Logic_attributeContext *ctx) = 0;

  virtual void enterLogic(SMTLIB2Parser::LogicContext *ctx) = 0;
  virtual void exitLogic(SMTLIB2Parser::LogicContext *ctx) = 0;

  virtual void enterB_value(SMTLIB2Parser::B_valueContext *ctx) = 0;
  virtual void exitB_value(SMTLIB2Parser::B_valueContext *ctx) = 0;

  virtual void enterOption(SMTLIB2Parser::OptionContext *ctx) = 0;
  virtual void exitOption(SMTLIB2Parser::OptionContext *ctx) = 0;

  virtual void enterInfo_flag(SMTLIB2Parser::Info_flagContext *ctx) = 0;
  virtual void exitInfo_flag(SMTLIB2Parser::Info_flagContext *ctx) = 0;

  virtual void enterCommand(SMTLIB2Parser::CommandContext *ctx) = 0;
  virtual void exitCommand(SMTLIB2Parser::CommandContext *ctx) = 0;

  virtual void enterScript(SMTLIB2Parser::ScriptContext *ctx) = 0;
  virtual void exitScript(SMTLIB2Parser::ScriptContext *ctx) = 0;

  virtual void enterGen_response(SMTLIB2Parser::Gen_responseContext *ctx) = 0;
  virtual void exitGen_response(SMTLIB2Parser::Gen_responseContext *ctx) = 0;

  virtual void enterError_behavior(SMTLIB2Parser::Error_behaviorContext *ctx) = 0;
  virtual void exitError_behavior(SMTLIB2Parser::Error_behaviorContext *ctx) = 0;

  virtual void enterReason_unknown(SMTLIB2Parser::Reason_unknownContext *ctx) = 0;
  virtual void exitReason_unknown(SMTLIB2Parser::Reason_unknownContext *ctx) = 0;

  virtual void enterStatus(SMTLIB2Parser::StatusContext *ctx) = 0;
  virtual void exitStatus(SMTLIB2Parser::StatusContext *ctx) = 0;

  virtual void enterInfo_response(SMTLIB2Parser::Info_responseContext *ctx) = 0;
  virtual void exitInfo_response(SMTLIB2Parser::Info_responseContext *ctx) = 0;

  virtual void enterGet_info_response(SMTLIB2Parser::Get_info_responseContext *ctx) = 0;
  virtual void exitGet_info_response(SMTLIB2Parser::Get_info_responseContext *ctx) = 0;

  virtual void enterCheck_sat_response(SMTLIB2Parser::Check_sat_responseContext *ctx) = 0;
  virtual void exitCheck_sat_response(SMTLIB2Parser::Check_sat_responseContext *ctx) = 0;

  virtual void enterGet_assertions_response(SMTLIB2Parser::Get_assertions_responseContext *ctx) = 0;
  virtual void exitGet_assertions_response(SMTLIB2Parser::Get_assertions_responseContext *ctx) = 0;

  virtual void enterProof(SMTLIB2Parser::ProofContext *ctx) = 0;
  virtual void exitProof(SMTLIB2Parser::ProofContext *ctx) = 0;

  virtual void enterGet_proof_response(SMTLIB2Parser::Get_proof_responseContext *ctx) = 0;
  virtual void exitGet_proof_response(SMTLIB2Parser::Get_proof_responseContext *ctx) = 0;

  virtual void enterGet_unsat_core_response(SMTLIB2Parser::Get_unsat_core_responseContext *ctx) = 0;
  virtual void exitGet_unsat_core_response(SMTLIB2Parser::Get_unsat_core_responseContext *ctx) = 0;

  virtual void enterValuation_pair(SMTLIB2Parser::Valuation_pairContext *ctx) = 0;
  virtual void exitValuation_pair(SMTLIB2Parser::Valuation_pairContext *ctx) = 0;

  virtual void enterGet_value_response(SMTLIB2Parser::Get_value_responseContext *ctx) = 0;
  virtual void exitGet_value_response(SMTLIB2Parser::Get_value_responseContext *ctx) = 0;

  virtual void enterT_valuation_pair(SMTLIB2Parser::T_valuation_pairContext *ctx) = 0;
  virtual void exitT_valuation_pair(SMTLIB2Parser::T_valuation_pairContext *ctx) = 0;

  virtual void enterGet_assignment_response(SMTLIB2Parser::Get_assignment_responseContext *ctx) = 0;
  virtual void exitGet_assignment_response(SMTLIB2Parser::Get_assignment_responseContext *ctx) = 0;

  virtual void enterGet_option_response(SMTLIB2Parser::Get_option_responseContext *ctx) = 0;
  virtual void exitGet_option_response(SMTLIB2Parser::Get_option_responseContext *ctx) = 0;


private:  
/* listener private declarations/members section */
};

}  // namespace antlrcpptest
