// Generated from SMTLIB26Parser.g4 by ANTLR 4.7
package antlrcpptest;
/* parser/listener/visitor header section */
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link SMTLIB26Parser}.
 */
public interface SMTLIB26ParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#symbol}.
	 * @param ctx the parse tree
	 */
	void enterSymbol(SMTLIB26Parser.SymbolContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#symbol}.
	 * @param ctx the parse tree
	 */
	void exitSymbol(SMTLIB26Parser.SymbolContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#keyword}.
	 * @param ctx the parse tree
	 */
	void enterKeyword(SMTLIB26Parser.KeywordContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#keyword}.
	 * @param ctx the parse tree
	 */
	void exitKeyword(SMTLIB26Parser.KeywordContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#spec_constant}.
	 * @param ctx the parse tree
	 */
	void enterSpec_constant(SMTLIB26Parser.Spec_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#spec_constant}.
	 * @param ctx the parse tree
	 */
	void exitSpec_constant(SMTLIB26Parser.Spec_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#s_expr}.
	 * @param ctx the parse tree
	 */
	void enterS_expr(SMTLIB26Parser.S_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#s_expr}.
	 * @param ctx the parse tree
	 */
	void exitS_expr(SMTLIB26Parser.S_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#identifier}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(SMTLIB26Parser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#identifier}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(SMTLIB26Parser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#sort}.
	 * @param ctx the parse tree
	 */
	void enterSort(SMTLIB26Parser.SortContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#sort}.
	 * @param ctx the parse tree
	 */
	void exitSort(SMTLIB26Parser.SortContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#attribute_value}.
	 * @param ctx the parse tree
	 */
	void enterAttribute_value(SMTLIB26Parser.Attribute_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#attribute_value}.
	 * @param ctx the parse tree
	 */
	void exitAttribute_value(SMTLIB26Parser.Attribute_valueContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#attribute}.
	 * @param ctx the parse tree
	 */
	void enterAttribute(SMTLIB26Parser.AttributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#attribute}.
	 * @param ctx the parse tree
	 */
	void exitAttribute(SMTLIB26Parser.AttributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#qual_identifier}.
	 * @param ctx the parse tree
	 */
	void enterQual_identifier(SMTLIB26Parser.Qual_identifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#qual_identifier}.
	 * @param ctx the parse tree
	 */
	void exitQual_identifier(SMTLIB26Parser.Qual_identifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#var_binding}.
	 * @param ctx the parse tree
	 */
	void enterVar_binding(SMTLIB26Parser.Var_bindingContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#var_binding}.
	 * @param ctx the parse tree
	 */
	void exitVar_binding(SMTLIB26Parser.Var_bindingContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#sorted_var}.
	 * @param ctx the parse tree
	 */
	void enterSorted_var(SMTLIB26Parser.Sorted_varContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#sorted_var}.
	 * @param ctx the parse tree
	 */
	void exitSorted_var(SMTLIB26Parser.Sorted_varContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(SMTLIB26Parser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(SMTLIB26Parser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#sort_symbol_decl}.
	 * @param ctx the parse tree
	 */
	void enterSort_symbol_decl(SMTLIB26Parser.Sort_symbol_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#sort_symbol_decl}.
	 * @param ctx the parse tree
	 */
	void exitSort_symbol_decl(SMTLIB26Parser.Sort_symbol_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#meta_spec_constant}.
	 * @param ctx the parse tree
	 */
	void enterMeta_spec_constant(SMTLIB26Parser.Meta_spec_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#meta_spec_constant}.
	 * @param ctx the parse tree
	 */
	void exitMeta_spec_constant(SMTLIB26Parser.Meta_spec_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#fun_symbol_decl}.
	 * @param ctx the parse tree
	 */
	void enterFun_symbol_decl(SMTLIB26Parser.Fun_symbol_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#fun_symbol_decl}.
	 * @param ctx the parse tree
	 */
	void exitFun_symbol_decl(SMTLIB26Parser.Fun_symbol_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#par_fun_symbol_decl}.
	 * @param ctx the parse tree
	 */
	void enterPar_fun_symbol_decl(SMTLIB26Parser.Par_fun_symbol_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#par_fun_symbol_decl}.
	 * @param ctx the parse tree
	 */
	void exitPar_fun_symbol_decl(SMTLIB26Parser.Par_fun_symbol_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#theory_decl}.
	 * @param ctx the parse tree
	 */
	void enterTheory_decl(SMTLIB26Parser.Theory_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#theory_decl}.
	 * @param ctx the parse tree
	 */
	void exitTheory_decl(SMTLIB26Parser.Theory_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#theory_attribute}.
	 * @param ctx the parse tree
	 */
	void enterTheory_attribute(SMTLIB26Parser.Theory_attributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#theory_attribute}.
	 * @param ctx the parse tree
	 */
	void exitTheory_attribute(SMTLIB26Parser.Theory_attributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#logic_attribute}.
	 * @param ctx the parse tree
	 */
	void enterLogic_attribute(SMTLIB26Parser.Logic_attributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#logic_attribute}.
	 * @param ctx the parse tree
	 */
	void exitLogic_attribute(SMTLIB26Parser.Logic_attributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#logic}.
	 * @param ctx the parse tree
	 */
	void enterLogic(SMTLIB26Parser.LogicContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#logic}.
	 * @param ctx the parse tree
	 */
	void exitLogic(SMTLIB26Parser.LogicContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#b_value}.
	 * @param ctx the parse tree
	 */
	void enterB_value(SMTLIB26Parser.B_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#b_value}.
	 * @param ctx the parse tree
	 */
	void exitB_value(SMTLIB26Parser.B_valueContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#option}.
	 * @param ctx the parse tree
	 */
	void enterOption(SMTLIB26Parser.OptionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#option}.
	 * @param ctx the parse tree
	 */
	void exitOption(SMTLIB26Parser.OptionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#info_flag}.
	 * @param ctx the parse tree
	 */
	void enterInfo_flag(SMTLIB26Parser.Info_flagContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#info_flag}.
	 * @param ctx the parse tree
	 */
	void exitInfo_flag(SMTLIB26Parser.Info_flagContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#command}.
	 * @param ctx the parse tree
	 */
	void enterCommand(SMTLIB26Parser.CommandContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#command}.
	 * @param ctx the parse tree
	 */
	void exitCommand(SMTLIB26Parser.CommandContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#script}.
	 * @param ctx the parse tree
	 */
	void enterScript(SMTLIB26Parser.ScriptContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#script}.
	 * @param ctx the parse tree
	 */
	void exitScript(SMTLIB26Parser.ScriptContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#gen_response}.
	 * @param ctx the parse tree
	 */
	void enterGen_response(SMTLIB26Parser.Gen_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#gen_response}.
	 * @param ctx the parse tree
	 */
	void exitGen_response(SMTLIB26Parser.Gen_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#error_behavior}.
	 * @param ctx the parse tree
	 */
	void enterError_behavior(SMTLIB26Parser.Error_behaviorContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#error_behavior}.
	 * @param ctx the parse tree
	 */
	void exitError_behavior(SMTLIB26Parser.Error_behaviorContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#reason_unknown}.
	 * @param ctx the parse tree
	 */
	void enterReason_unknown(SMTLIB26Parser.Reason_unknownContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#reason_unknown}.
	 * @param ctx the parse tree
	 */
	void exitReason_unknown(SMTLIB26Parser.Reason_unknownContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#status}.
	 * @param ctx the parse tree
	 */
	void enterStatus(SMTLIB26Parser.StatusContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#status}.
	 * @param ctx the parse tree
	 */
	void exitStatus(SMTLIB26Parser.StatusContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#info_response}.
	 * @param ctx the parse tree
	 */
	void enterInfo_response(SMTLIB26Parser.Info_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#info_response}.
	 * @param ctx the parse tree
	 */
	void exitInfo_response(SMTLIB26Parser.Info_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_info_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_info_response(SMTLIB26Parser.Get_info_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_info_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_info_response(SMTLIB26Parser.Get_info_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#check_sat_response}.
	 * @param ctx the parse tree
	 */
	void enterCheck_sat_response(SMTLIB26Parser.Check_sat_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#check_sat_response}.
	 * @param ctx the parse tree
	 */
	void exitCheck_sat_response(SMTLIB26Parser.Check_sat_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_assertions_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_assertions_response(SMTLIB26Parser.Get_assertions_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_assertions_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_assertions_response(SMTLIB26Parser.Get_assertions_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#proof}.
	 * @param ctx the parse tree
	 */
	void enterProof(SMTLIB26Parser.ProofContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#proof}.
	 * @param ctx the parse tree
	 */
	void exitProof(SMTLIB26Parser.ProofContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_proof_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_proof_response(SMTLIB26Parser.Get_proof_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_proof_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_proof_response(SMTLIB26Parser.Get_proof_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_unsat_core_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_unsat_core_response(SMTLIB26Parser.Get_unsat_core_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_unsat_core_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_unsat_core_response(SMTLIB26Parser.Get_unsat_core_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#valuation_pair}.
	 * @param ctx the parse tree
	 */
	void enterValuation_pair(SMTLIB26Parser.Valuation_pairContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#valuation_pair}.
	 * @param ctx the parse tree
	 */
	void exitValuation_pair(SMTLIB26Parser.Valuation_pairContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_value_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_value_response(SMTLIB26Parser.Get_value_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_value_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_value_response(SMTLIB26Parser.Get_value_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#t_valuation_pair}.
	 * @param ctx the parse tree
	 */
	void enterT_valuation_pair(SMTLIB26Parser.T_valuation_pairContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#t_valuation_pair}.
	 * @param ctx the parse tree
	 */
	void exitT_valuation_pair(SMTLIB26Parser.T_valuation_pairContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_assignment_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_assignment_response(SMTLIB26Parser.Get_assignment_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_assignment_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_assignment_response(SMTLIB26Parser.Get_assignment_responseContext ctx);
	/**
	 * Enter a parse tree produced by {@link SMTLIB26Parser#get_option_response}.
	 * @param ctx the parse tree
	 */
	void enterGet_option_response(SMTLIB26Parser.Get_option_responseContext ctx);
	/**
	 * Exit a parse tree produced by {@link SMTLIB26Parser#get_option_response}.
	 * @param ctx the parse tree
	 */
	void exitGet_option_response(SMTLIB26Parser.Get_option_responseContext ctx);
}