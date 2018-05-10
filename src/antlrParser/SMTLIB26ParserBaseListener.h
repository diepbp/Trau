/* parser/listener/visitor header section */

// Generated from SMTLIB26Parser.g4 by ANTLR 4.7

#pragma once

/* base listener preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB26ParserListener.h"

/* base listener postinclude section */

namespace antlrcpptest {

/**
 * This class provides an empty implementation of SMTLIB26ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SMTLIB26ParserBaseListener : public SMTLIB26ParserListener {
public:
/* base listener public declarations/members section */

  virtual void enterSymbol(SMTLIB26Parser::SymbolContext * /*ctx*/) override { }
  virtual void exitSymbol(SMTLIB26Parser::SymbolContext * /*ctx*/) override { }

  virtual void enterKeyword(SMTLIB26Parser::KeywordContext * /*ctx*/) override { }
  virtual void exitKeyword(SMTLIB26Parser::KeywordContext * /*ctx*/) override { }

  virtual void enterSpec_constant(SMTLIB26Parser::Spec_constantContext * /*ctx*/) override { }
  virtual void exitSpec_constant(SMTLIB26Parser::Spec_constantContext * /*ctx*/) override { }

  virtual void enterS_expr(SMTLIB26Parser::S_exprContext * /*ctx*/) override { }
  virtual void exitS_expr(SMTLIB26Parser::S_exprContext * /*ctx*/) override { }

  virtual void enterIdentifier(SMTLIB26Parser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(SMTLIB26Parser::IdentifierContext * /*ctx*/) override { }

  virtual void enterSort(SMTLIB26Parser::SortContext * /*ctx*/) override { }
  virtual void exitSort(SMTLIB26Parser::SortContext * /*ctx*/) override { }

  virtual void enterAttribute_value(SMTLIB26Parser::Attribute_valueContext * /*ctx*/) override { }
  virtual void exitAttribute_value(SMTLIB26Parser::Attribute_valueContext * /*ctx*/) override { }

  virtual void enterAttribute(SMTLIB26Parser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(SMTLIB26Parser::AttributeContext * /*ctx*/) override { }

  virtual void enterQual_identifier(SMTLIB26Parser::Qual_identifierContext * /*ctx*/) override { }
  virtual void exitQual_identifier(SMTLIB26Parser::Qual_identifierContext * /*ctx*/) override { }

  virtual void enterVar_binding(SMTLIB26Parser::Var_bindingContext * /*ctx*/) override { }
  virtual void exitVar_binding(SMTLIB26Parser::Var_bindingContext * /*ctx*/) override { }

  virtual void enterSorted_var(SMTLIB26Parser::Sorted_varContext * /*ctx*/) override { }
  virtual void exitSorted_var(SMTLIB26Parser::Sorted_varContext * /*ctx*/) override { }

  virtual void enterTerm(SMTLIB26Parser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(SMTLIB26Parser::TermContext * /*ctx*/) override { }

  virtual void enterSort_symbol_decl(SMTLIB26Parser::Sort_symbol_declContext * /*ctx*/) override { }
  virtual void exitSort_symbol_decl(SMTLIB26Parser::Sort_symbol_declContext * /*ctx*/) override { }

  virtual void enterMeta_spec_constant(SMTLIB26Parser::Meta_spec_constantContext * /*ctx*/) override { }
  virtual void exitMeta_spec_constant(SMTLIB26Parser::Meta_spec_constantContext * /*ctx*/) override { }

  virtual void enterFun_symbol_decl(SMTLIB26Parser::Fun_symbol_declContext * /*ctx*/) override { }
  virtual void exitFun_symbol_decl(SMTLIB26Parser::Fun_symbol_declContext * /*ctx*/) override { }

  virtual void enterPar_fun_symbol_decl(SMTLIB26Parser::Par_fun_symbol_declContext * /*ctx*/) override { }
  virtual void exitPar_fun_symbol_decl(SMTLIB26Parser::Par_fun_symbol_declContext * /*ctx*/) override { }

  virtual void enterTheory_decl(SMTLIB26Parser::Theory_declContext * /*ctx*/) override { }
  virtual void exitTheory_decl(SMTLIB26Parser::Theory_declContext * /*ctx*/) override { }

  virtual void enterTheory_attribute(SMTLIB26Parser::Theory_attributeContext * /*ctx*/) override { }
  virtual void exitTheory_attribute(SMTLIB26Parser::Theory_attributeContext * /*ctx*/) override { }

  virtual void enterLogic_attribute(SMTLIB26Parser::Logic_attributeContext * /*ctx*/) override { }
  virtual void exitLogic_attribute(SMTLIB26Parser::Logic_attributeContext * /*ctx*/) override { }

  virtual void enterLogic(SMTLIB26Parser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(SMTLIB26Parser::LogicContext * /*ctx*/) override { }

  virtual void enterB_value(SMTLIB26Parser::B_valueContext * /*ctx*/) override { }
  virtual void exitB_value(SMTLIB26Parser::B_valueContext * /*ctx*/) override { }

  virtual void enterOption(SMTLIB26Parser::OptionContext * /*ctx*/) override { }
  virtual void exitOption(SMTLIB26Parser::OptionContext * /*ctx*/) override { }

  virtual void enterInfo_flag(SMTLIB26Parser::Info_flagContext * /*ctx*/) override { }
  virtual void exitInfo_flag(SMTLIB26Parser::Info_flagContext * /*ctx*/) override { }

  virtual void enterCommand(SMTLIB26Parser::CommandContext * /*ctx*/) override { }
  virtual void exitCommand(SMTLIB26Parser::CommandContext * /*ctx*/) override { }

  virtual void enterScript(SMTLIB26Parser::ScriptContext * /*ctx*/) override { }
  virtual void exitScript(SMTLIB26Parser::ScriptContext * /*ctx*/) override { }

  virtual void enterGen_response(SMTLIB26Parser::Gen_responseContext * /*ctx*/) override { }
  virtual void exitGen_response(SMTLIB26Parser::Gen_responseContext * /*ctx*/) override { }

  virtual void enterError_behavior(SMTLIB26Parser::Error_behaviorContext * /*ctx*/) override { }
  virtual void exitError_behavior(SMTLIB26Parser::Error_behaviorContext * /*ctx*/) override { }

  virtual void enterReason_unknown(SMTLIB26Parser::Reason_unknownContext * /*ctx*/) override { }
  virtual void exitReason_unknown(SMTLIB26Parser::Reason_unknownContext * /*ctx*/) override { }

  virtual void enterStatus(SMTLIB26Parser::StatusContext * /*ctx*/) override { }
  virtual void exitStatus(SMTLIB26Parser::StatusContext * /*ctx*/) override { }

  virtual void enterInfo_response(SMTLIB26Parser::Info_responseContext * /*ctx*/) override { }
  virtual void exitInfo_response(SMTLIB26Parser::Info_responseContext * /*ctx*/) override { }

  virtual void enterGet_info_response(SMTLIB26Parser::Get_info_responseContext * /*ctx*/) override { }
  virtual void exitGet_info_response(SMTLIB26Parser::Get_info_responseContext * /*ctx*/) override { }

  virtual void enterCheck_sat_response(SMTLIB26Parser::Check_sat_responseContext * /*ctx*/) override { }
  virtual void exitCheck_sat_response(SMTLIB26Parser::Check_sat_responseContext * /*ctx*/) override { }

  virtual void enterGet_assertions_response(SMTLIB26Parser::Get_assertions_responseContext * /*ctx*/) override { }
  virtual void exitGet_assertions_response(SMTLIB26Parser::Get_assertions_responseContext * /*ctx*/) override { }

  virtual void enterProof(SMTLIB26Parser::ProofContext * /*ctx*/) override { }
  virtual void exitProof(SMTLIB26Parser::ProofContext * /*ctx*/) override { }

  virtual void enterGet_proof_response(SMTLIB26Parser::Get_proof_responseContext * /*ctx*/) override { }
  virtual void exitGet_proof_response(SMTLIB26Parser::Get_proof_responseContext * /*ctx*/) override { }

  virtual void enterGet_unsat_core_response(SMTLIB26Parser::Get_unsat_core_responseContext * /*ctx*/) override { }
  virtual void exitGet_unsat_core_response(SMTLIB26Parser::Get_unsat_core_responseContext * /*ctx*/) override { }

  virtual void enterValuation_pair(SMTLIB26Parser::Valuation_pairContext * /*ctx*/) override { }
  virtual void exitValuation_pair(SMTLIB26Parser::Valuation_pairContext * /*ctx*/) override { }

  virtual void enterGet_value_response(SMTLIB26Parser::Get_value_responseContext * /*ctx*/) override { }
  virtual void exitGet_value_response(SMTLIB26Parser::Get_value_responseContext * /*ctx*/) override { }

  virtual void enterT_valuation_pair(SMTLIB26Parser::T_valuation_pairContext * /*ctx*/) override { }
  virtual void exitT_valuation_pair(SMTLIB26Parser::T_valuation_pairContext * /*ctx*/) override { }

  virtual void enterGet_assignment_response(SMTLIB26Parser::Get_assignment_responseContext * /*ctx*/) override { }
  virtual void exitGet_assignment_response(SMTLIB26Parser::Get_assignment_responseContext * /*ctx*/) override { }

  virtual void enterGet_option_response(SMTLIB26Parser::Get_option_responseContext * /*ctx*/) override { }
  virtual void exitGet_option_response(SMTLIB26Parser::Get_option_responseContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

private:  
/* base listener private declarations/members section */
};

}  // namespace antlrcpptest
