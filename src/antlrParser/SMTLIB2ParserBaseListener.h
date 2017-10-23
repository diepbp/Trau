/* parser/listener/visitor header section */

// Generated from SMTLIB2Parser.g4 by ANTLR 4.7

#pragma once

/* base listener preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB2ParserListener.h"

/* base listener postinclude section */

namespace antlrcpptest {

/**
 * This class provides an empty implementation of SMTLIB2ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SMTLIB2ParserBaseListener : public SMTLIB2ParserListener {
public:
/* base listener public declarations/members section */

  virtual void enterSymbol(SMTLIB2Parser::SymbolContext * /*ctx*/) override { }
  virtual void exitSymbol(SMTLIB2Parser::SymbolContext * /*ctx*/) override { }

  virtual void enterKeyword(SMTLIB2Parser::KeywordContext * /*ctx*/) override { }
  virtual void exitKeyword(SMTLIB2Parser::KeywordContext * /*ctx*/) override { }

  virtual void enterSpec_constant(SMTLIB2Parser::Spec_constantContext * /*ctx*/) override { }
  virtual void exitSpec_constant(SMTLIB2Parser::Spec_constantContext * /*ctx*/) override { }

  virtual void enterS_expr(SMTLIB2Parser::S_exprContext * /*ctx*/) override { }
  virtual void exitS_expr(SMTLIB2Parser::S_exprContext * /*ctx*/) override { }

  virtual void enterIdentifier(SMTLIB2Parser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(SMTLIB2Parser::IdentifierContext * /*ctx*/) override { }

  virtual void enterSort(SMTLIB2Parser::SortContext * /*ctx*/) override { }
  virtual void exitSort(SMTLIB2Parser::SortContext * /*ctx*/) override { }

  virtual void enterAttribute_value(SMTLIB2Parser::Attribute_valueContext * /*ctx*/) override { }
  virtual void exitAttribute_value(SMTLIB2Parser::Attribute_valueContext * /*ctx*/) override { }

  virtual void enterAttribute(SMTLIB2Parser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(SMTLIB2Parser::AttributeContext * /*ctx*/) override { }

  virtual void enterQual_identifier(SMTLIB2Parser::Qual_identifierContext * /*ctx*/) override { }
  virtual void exitQual_identifier(SMTLIB2Parser::Qual_identifierContext * /*ctx*/) override { }

  virtual void enterVar_binding(SMTLIB2Parser::Var_bindingContext * /*ctx*/) override { }
  virtual void exitVar_binding(SMTLIB2Parser::Var_bindingContext * /*ctx*/) override { }

  virtual void enterSorted_var(SMTLIB2Parser::Sorted_varContext * /*ctx*/) override { }
  virtual void exitSorted_var(SMTLIB2Parser::Sorted_varContext * /*ctx*/) override { }

  virtual void enterTerm(SMTLIB2Parser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(SMTLIB2Parser::TermContext * /*ctx*/) override { }

  virtual void enterSort_symbol_decl(SMTLIB2Parser::Sort_symbol_declContext * /*ctx*/) override { }
  virtual void exitSort_symbol_decl(SMTLIB2Parser::Sort_symbol_declContext * /*ctx*/) override { }

  virtual void enterMeta_spec_constant(SMTLIB2Parser::Meta_spec_constantContext * /*ctx*/) override { }
  virtual void exitMeta_spec_constant(SMTLIB2Parser::Meta_spec_constantContext * /*ctx*/) override { }

  virtual void enterFun_symbol_decl(SMTLIB2Parser::Fun_symbol_declContext * /*ctx*/) override { }
  virtual void exitFun_symbol_decl(SMTLIB2Parser::Fun_symbol_declContext * /*ctx*/) override { }

  virtual void enterPar_fun_symbol_decl(SMTLIB2Parser::Par_fun_symbol_declContext * /*ctx*/) override { }
  virtual void exitPar_fun_symbol_decl(SMTLIB2Parser::Par_fun_symbol_declContext * /*ctx*/) override { }

  virtual void enterTheory_decl(SMTLIB2Parser::Theory_declContext * /*ctx*/) override { }
  virtual void exitTheory_decl(SMTLIB2Parser::Theory_declContext * /*ctx*/) override { }

  virtual void enterTheory_attribute(SMTLIB2Parser::Theory_attributeContext * /*ctx*/) override { }
  virtual void exitTheory_attribute(SMTLIB2Parser::Theory_attributeContext * /*ctx*/) override { }

  virtual void enterLogic_attribute(SMTLIB2Parser::Logic_attributeContext * /*ctx*/) override { }
  virtual void exitLogic_attribute(SMTLIB2Parser::Logic_attributeContext * /*ctx*/) override { }

  virtual void enterLogic(SMTLIB2Parser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(SMTLIB2Parser::LogicContext * /*ctx*/) override { }

  virtual void enterB_value(SMTLIB2Parser::B_valueContext * /*ctx*/) override { }
  virtual void exitB_value(SMTLIB2Parser::B_valueContext * /*ctx*/) override { }

  virtual void enterOption(SMTLIB2Parser::OptionContext * /*ctx*/) override { }
  virtual void exitOption(SMTLIB2Parser::OptionContext * /*ctx*/) override { }

  virtual void enterInfo_flag(SMTLIB2Parser::Info_flagContext * /*ctx*/) override { }
  virtual void exitInfo_flag(SMTLIB2Parser::Info_flagContext * /*ctx*/) override { }

  virtual void enterCommand(SMTLIB2Parser::CommandContext * /*ctx*/) override { }
  virtual void exitCommand(SMTLIB2Parser::CommandContext * /*ctx*/) override { }

  virtual void enterScript(SMTLIB2Parser::ScriptContext * /*ctx*/) override { }
  virtual void exitScript(SMTLIB2Parser::ScriptContext * /*ctx*/) override { }

  virtual void enterGen_response(SMTLIB2Parser::Gen_responseContext * /*ctx*/) override { }
  virtual void exitGen_response(SMTLIB2Parser::Gen_responseContext * /*ctx*/) override { }

  virtual void enterError_behavior(SMTLIB2Parser::Error_behaviorContext * /*ctx*/) override { }
  virtual void exitError_behavior(SMTLIB2Parser::Error_behaviorContext * /*ctx*/) override { }

  virtual void enterReason_unknown(SMTLIB2Parser::Reason_unknownContext * /*ctx*/) override { }
  virtual void exitReason_unknown(SMTLIB2Parser::Reason_unknownContext * /*ctx*/) override { }

  virtual void enterStatus(SMTLIB2Parser::StatusContext * /*ctx*/) override { }
  virtual void exitStatus(SMTLIB2Parser::StatusContext * /*ctx*/) override { }

  virtual void enterInfo_response(SMTLIB2Parser::Info_responseContext * /*ctx*/) override { }
  virtual void exitInfo_response(SMTLIB2Parser::Info_responseContext * /*ctx*/) override { }

  virtual void enterGet_info_response(SMTLIB2Parser::Get_info_responseContext * /*ctx*/) override { }
  virtual void exitGet_info_response(SMTLIB2Parser::Get_info_responseContext * /*ctx*/) override { }

  virtual void enterCheck_sat_response(SMTLIB2Parser::Check_sat_responseContext * /*ctx*/) override { }
  virtual void exitCheck_sat_response(SMTLIB2Parser::Check_sat_responseContext * /*ctx*/) override { }

  virtual void enterGet_assertions_response(SMTLIB2Parser::Get_assertions_responseContext * /*ctx*/) override { }
  virtual void exitGet_assertions_response(SMTLIB2Parser::Get_assertions_responseContext * /*ctx*/) override { }

  virtual void enterProof(SMTLIB2Parser::ProofContext * /*ctx*/) override { }
  virtual void exitProof(SMTLIB2Parser::ProofContext * /*ctx*/) override { }

  virtual void enterGet_proof_response(SMTLIB2Parser::Get_proof_responseContext * /*ctx*/) override { }
  virtual void exitGet_proof_response(SMTLIB2Parser::Get_proof_responseContext * /*ctx*/) override { }

  virtual void enterGet_unsat_core_response(SMTLIB2Parser::Get_unsat_core_responseContext * /*ctx*/) override { }
  virtual void exitGet_unsat_core_response(SMTLIB2Parser::Get_unsat_core_responseContext * /*ctx*/) override { }

  virtual void enterValuation_pair(SMTLIB2Parser::Valuation_pairContext * /*ctx*/) override { }
  virtual void exitValuation_pair(SMTLIB2Parser::Valuation_pairContext * /*ctx*/) override { }

  virtual void enterGet_value_response(SMTLIB2Parser::Get_value_responseContext * /*ctx*/) override { }
  virtual void exitGet_value_response(SMTLIB2Parser::Get_value_responseContext * /*ctx*/) override { }

  virtual void enterT_valuation_pair(SMTLIB2Parser::T_valuation_pairContext * /*ctx*/) override { }
  virtual void exitT_valuation_pair(SMTLIB2Parser::T_valuation_pairContext * /*ctx*/) override { }

  virtual void enterGet_assignment_response(SMTLIB2Parser::Get_assignment_responseContext * /*ctx*/) override { }
  virtual void exitGet_assignment_response(SMTLIB2Parser::Get_assignment_responseContext * /*ctx*/) override { }

  virtual void enterGet_option_response(SMTLIB2Parser::Get_option_responseContext * /*ctx*/) override { }
  virtual void exitGet_option_response(SMTLIB2Parser::Get_option_responseContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

private:  
/* base listener private declarations/members section */
};

}  // namespace antlrcpptest
