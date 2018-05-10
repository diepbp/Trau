// Generated from SMTLIB26Parser.g4 by ANTLR 4.7
package antlrcpptest;
/* parser/listener/visitor header section */
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link SMTLIB26Parser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface SMTLIB26ParserVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#symbol}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSymbol(SMTLIB26Parser.SymbolContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#keyword}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitKeyword(SMTLIB26Parser.KeywordContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#spec_constant}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSpec_constant(SMTLIB26Parser.Spec_constantContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#s_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitS_expr(SMTLIB26Parser.S_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#identifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentifier(SMTLIB26Parser.IdentifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#sort}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSort(SMTLIB26Parser.SortContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#attribute_value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAttribute_value(SMTLIB26Parser.Attribute_valueContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#attribute}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAttribute(SMTLIB26Parser.AttributeContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#qual_identifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitQual_identifier(SMTLIB26Parser.Qual_identifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#var_binding}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVar_binding(SMTLIB26Parser.Var_bindingContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#sorted_var}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSorted_var(SMTLIB26Parser.Sorted_varContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#term}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTerm(SMTLIB26Parser.TermContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#sort_symbol_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSort_symbol_decl(SMTLIB26Parser.Sort_symbol_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#meta_spec_constant}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMeta_spec_constant(SMTLIB26Parser.Meta_spec_constantContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#fun_symbol_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFun_symbol_decl(SMTLIB26Parser.Fun_symbol_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#par_fun_symbol_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPar_fun_symbol_decl(SMTLIB26Parser.Par_fun_symbol_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#theory_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTheory_decl(SMTLIB26Parser.Theory_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#theory_attribute}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTheory_attribute(SMTLIB26Parser.Theory_attributeContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#logic_attribute}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogic_attribute(SMTLIB26Parser.Logic_attributeContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#logic}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogic(SMTLIB26Parser.LogicContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#b_value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitB_value(SMTLIB26Parser.B_valueContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#option}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOption(SMTLIB26Parser.OptionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#info_flag}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInfo_flag(SMTLIB26Parser.Info_flagContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#command}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCommand(SMTLIB26Parser.CommandContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#script}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitScript(SMTLIB26Parser.ScriptContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#gen_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGen_response(SMTLIB26Parser.Gen_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#error_behavior}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitError_behavior(SMTLIB26Parser.Error_behaviorContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#reason_unknown}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReason_unknown(SMTLIB26Parser.Reason_unknownContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#status}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatus(SMTLIB26Parser.StatusContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#info_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInfo_response(SMTLIB26Parser.Info_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_info_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_info_response(SMTLIB26Parser.Get_info_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#check_sat_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCheck_sat_response(SMTLIB26Parser.Check_sat_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_assertions_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_assertions_response(SMTLIB26Parser.Get_assertions_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#proof}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProof(SMTLIB26Parser.ProofContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_proof_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_proof_response(SMTLIB26Parser.Get_proof_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_unsat_core_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_unsat_core_response(SMTLIB26Parser.Get_unsat_core_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#valuation_pair}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitValuation_pair(SMTLIB26Parser.Valuation_pairContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_value_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_value_response(SMTLIB26Parser.Get_value_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#t_valuation_pair}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitT_valuation_pair(SMTLIB26Parser.T_valuation_pairContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_assignment_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_assignment_response(SMTLIB26Parser.Get_assignment_responseContext ctx);
	/**
	 * Visit a parse tree produced by {@link SMTLIB26Parser#get_option_response}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGet_option_response(SMTLIB26Parser.Get_option_responseContext ctx);
}