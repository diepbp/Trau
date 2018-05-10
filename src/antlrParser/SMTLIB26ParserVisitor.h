/* parser/listener/visitor header section */

// Generated from SMTLIB26Parser.g4 by ANTLR 4.7

#pragma once

/* visitor preinclude section */

#include "antlr4-runtime.h"
#include "SMTLIB26Parser.h"

/* visitor postinclude section */

namespace antlrcpptest {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by SMTLIB26Parser.
 */
class  SMTLIB26ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:
  /* visitor public declarations/members section */

  /**
   * Visit parse trees produced by SMTLIB26Parser.
   */
    virtual antlrcpp::Any visitSymbol(SMTLIB26Parser::SymbolContext *context) = 0;

    virtual antlrcpp::Any visitKeyword(SMTLIB26Parser::KeywordContext *context) = 0;

    virtual antlrcpp::Any visitSpec_constant(SMTLIB26Parser::Spec_constantContext *context) = 0;

    virtual antlrcpp::Any visitS_expr(SMTLIB26Parser::S_exprContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(SMTLIB26Parser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitSort(SMTLIB26Parser::SortContext *context) = 0;

    virtual antlrcpp::Any visitAttribute_value(SMTLIB26Parser::Attribute_valueContext *context) = 0;

    virtual antlrcpp::Any visitAttribute(SMTLIB26Parser::AttributeContext *context) = 0;

    virtual antlrcpp::Any visitQual_identifier(SMTLIB26Parser::Qual_identifierContext *context) = 0;

    virtual antlrcpp::Any visitVar_binding(SMTLIB26Parser::Var_bindingContext *context) = 0;

    virtual antlrcpp::Any visitSorted_var(SMTLIB26Parser::Sorted_varContext *context) = 0;

    virtual antlrcpp::Any visitTerm(SMTLIB26Parser::TermContext *context) = 0;

    virtual antlrcpp::Any visitSort_symbol_decl(SMTLIB26Parser::Sort_symbol_declContext *context) = 0;

    virtual antlrcpp::Any visitMeta_spec_constant(SMTLIB26Parser::Meta_spec_constantContext *context) = 0;

    virtual antlrcpp::Any visitFun_symbol_decl(SMTLIB26Parser::Fun_symbol_declContext *context) = 0;

    virtual antlrcpp::Any visitPar_fun_symbol_decl(SMTLIB26Parser::Par_fun_symbol_declContext *context) = 0;

    virtual antlrcpp::Any visitTheory_decl(SMTLIB26Parser::Theory_declContext *context) = 0;

    virtual antlrcpp::Any visitTheory_attribute(SMTLIB26Parser::Theory_attributeContext *context) = 0;

    virtual antlrcpp::Any visitLogic_attribute(SMTLIB26Parser::Logic_attributeContext *context) = 0;

    virtual antlrcpp::Any visitLogic(SMTLIB26Parser::LogicContext *context) = 0;

    virtual antlrcpp::Any visitB_value(SMTLIB26Parser::B_valueContext *context) = 0;

    virtual antlrcpp::Any visitOption(SMTLIB26Parser::OptionContext *context) = 0;

    virtual antlrcpp::Any visitInfo_flag(SMTLIB26Parser::Info_flagContext *context) = 0;

    virtual antlrcpp::Any visitCommand(SMTLIB26Parser::CommandContext *context) = 0;

    virtual antlrcpp::Any visitScript(SMTLIB26Parser::ScriptContext *context) = 0;

    virtual antlrcpp::Any visitGen_response(SMTLIB26Parser::Gen_responseContext *context) = 0;

    virtual antlrcpp::Any visitError_behavior(SMTLIB26Parser::Error_behaviorContext *context) = 0;

    virtual antlrcpp::Any visitReason_unknown(SMTLIB26Parser::Reason_unknownContext *context) = 0;

    virtual antlrcpp::Any visitStatus(SMTLIB26Parser::StatusContext *context) = 0;

    virtual antlrcpp::Any visitInfo_response(SMTLIB26Parser::Info_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_info_response(SMTLIB26Parser::Get_info_responseContext *context) = 0;

    virtual antlrcpp::Any visitCheck_sat_response(SMTLIB26Parser::Check_sat_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_assertions_response(SMTLIB26Parser::Get_assertions_responseContext *context) = 0;

    virtual antlrcpp::Any visitProof(SMTLIB26Parser::ProofContext *context) = 0;

    virtual antlrcpp::Any visitGet_proof_response(SMTLIB26Parser::Get_proof_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_unsat_core_response(SMTLIB26Parser::Get_unsat_core_responseContext *context) = 0;

    virtual antlrcpp::Any visitValuation_pair(SMTLIB26Parser::Valuation_pairContext *context) = 0;

    virtual antlrcpp::Any visitGet_value_response(SMTLIB26Parser::Get_value_responseContext *context) = 0;

    virtual antlrcpp::Any visitT_valuation_pair(SMTLIB26Parser::T_valuation_pairContext *context) = 0;

    virtual antlrcpp::Any visitGet_assignment_response(SMTLIB26Parser::Get_assignment_responseContext *context) = 0;

    virtual antlrcpp::Any visitGet_option_response(SMTLIB26Parser::Get_option_responseContext *context) = 0;


private:  
/* visitor private declarations/members section */
};

}  // namespace antlrcpptest
