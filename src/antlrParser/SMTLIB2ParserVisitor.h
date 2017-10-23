/* parser/listener/visitor header section */

// Generated from SMTLIB2Parser.g4 by ANTLR 4.7

#pragma once

/* visitor preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB2Parser.h"

/* visitor postinclude section */

namespace antlrcpptest {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by SMTLIB2Parser.
 */
class  SMTLIB2ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:
  /* visitor public declarations/members section */

  /**
   * Visit parse trees produced by SMTLIB2Parser.
   */
    virtual antlrcpp::Any visitSymbol(SMTLIB2Parser::SymbolContext *context) = 0;

    virtual antlrcpp::Any visitKeyword(SMTLIB2Parser::KeywordContext *context) = 0;

    virtual antlrcpp::Any visitSpec_constant(SMTLIB2Parser::Spec_constantContext *context) = 0;

    virtual antlrcpp::Any visitS_expr(SMTLIB2Parser::S_exprContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(SMTLIB2Parser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitSort(SMTLIB2Parser::SortContext *context) = 0;

    virtual antlrcpp::Any visitAttribute_value(SMTLIB2Parser::Attribute_valueContext *context) = 0;

    virtual antlrcpp::Any visitAttribute(SMTLIB2Parser::AttributeContext *context) = 0;

    virtual antlrcpp::Any visitQual_identifier(SMTLIB2Parser::Qual_identifierContext *context) = 0;

    virtual antlrcpp::Any visitVar_binding(SMTLIB2Parser::Var_bindingContext *context) = 0;

    virtual antlrcpp::Any visitSorted_var(SMTLIB2Parser::Sorted_varContext *context) = 0;

    virtual antlrcpp::Any visitTerm(SMTLIB2Parser::TermContext *context) = 0;

    virtual antlrcpp::Any visitSort_symbol_decl(SMTLIB2Parser::Sort_symbol_declContext *context) = 0;

    virtual antlrcpp::Any visitMeta_spec_constant(SMTLIB2Parser::Meta_spec_constantContext *context) = 0;

    virtual antlrcpp::Any visitFun_symbol_decl(SMTLIB2Parser::Fun_symbol_declContext *context) = 0;

    virtual antlrcpp::Any visitPar_fun_symbol_decl(SMTLIB2Parser::Par_fun_symbol_declContext *context) = 0;

    virtual antlrcpp::Any visitTheory_decl(SMTLIB2Parser::Theory_declContext *context) = 0;

    virtual antlrcpp::Any visitTheory_attribute(SMTLIB2Parser::Theory_attributeContext *context) = 0;

    virtual antlrcpp::Any visitLogic_attribute(SMTLIB2Parser::Logic_attributeContext *context) = 0;

    virtual antlrcpp::Any visitLogic(SMTLIB2Parser::LogicContext *context) = 0;

    virtual antlrcpp::Any visitB_value(SMTLIB2Parser::B_valueContext *context) = 0;

    virtual antlrcpp::Any visitOption(SMTLIB2Parser::OptionContext *context) = 0;

    virtual antlrcpp::Any visitInfo_flag(SMTLIB2Parser::Info_flagContext *context) = 0;

    virtual antlrcpp::Any visitCommand(SMTLIB2Parser::CommandContext *context) = 0;

    virtual antlrcpp::Any visitScript(SMTLIB2Parser::ScriptContext *context) = 0;

    virtual antlrcpp::Any visitGen_response(SMTLIB2Parser::Gen_responseContext *context) = 0;

    virtual antlrcpp::Any visitError_behavior(SMTLIB2Parser::Error_behaviorContext *context) = 0;

    virtual antlrcpp::Any visitReason_unknown(SMTLIB2Parser::Reason_unknownContext *context) = 0;

    virtual antlrcpp::Any visitStatus(SMTLIB2Parser::StatusContext *context) = 0;

    virtual antlrcpp::Any visitInfo_response(SMTLIB2Parser::Info_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_info_response(SMTLIB2Parser::Get_info_responseContext *context) = 0;

    virtual antlrcpp::Any visitCheck_sat_response(SMTLIB2Parser::Check_sat_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_assertions_response(SMTLIB2Parser::Get_assertions_responseContext *context) = 0;

    virtual antlrcpp::Any visitProof(SMTLIB2Parser::ProofContext *context) = 0;

    virtual antlrcpp::Any visitGet_proof_response(SMTLIB2Parser::Get_proof_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_unsat_core_response(SMTLIB2Parser::Get_unsat_core_responseContext *context) = 0;

    virtual antlrcpp::Any visitValuation_pair(SMTLIB2Parser::Valuation_pairContext *context) = 0;

    virtual antlrcpp::Any visitGet_value_response(SMTLIB2Parser::Get_value_responseContext *context) = 0;

    virtual antlrcpp::Any visitT_valuation_pair(SMTLIB2Parser::T_valuation_pairContext *context) = 0;

    virtual antlrcpp::Any visitGet_assignment_response(SMTLIB2Parser::Get_assignment_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_option_response(SMTLIB2Parser::Get_option_responseContext *context) = 0;


private:  
/* visitor private declarations/members section */
};

}  // namespace antlrcpptest
