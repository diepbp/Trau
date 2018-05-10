// Generated from SMTLIB26Parser.g4 by ANTLR 4.7
package antlrcpptest;
/* parser/listener/visitor header section */
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class SMTLIB26Parser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		SYM_AND=1, SYM_OR=2, SYM_NOT=3, SYM_BOOL=4, SYM_CONTINUED_EXECUTION=5, 
		SYM_ERROR=6, SYM_FALSE=7, SYM_IMMEDIATE_EXIT=8, SYM_INCOMPLETE=9, SYM_LOGIC=10, 
		SYM_MEMOUT=11, SYM_SAT=12, SYM_SUCCESS=13, SYM_THEORY=14, SYM_TRUE=15, 
		SYM_UNKNOWN=16, SYM_UNSAT=17, SYM_UNSUPPORTED=18, KEYWORD_ALL_STATISTICS=19, 
		KEYWORD_AUTHORS=20, KEYWORD_AXIOMS=21, KEYWORD_CHAINABLE=22, KEYWORD_DEFINITION=23, 
		KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL=24, KEYWORD_ERROR_BEHAVIOR=25, KEYWORD_EXPAND_DEFINITIONS=26, 
		KEYWORD_EXTENSIONS=27, KEYWORD_FUNS=28, KEYWORD_FUNS_DESCRIPTION=29, KEYWORD_INTERACTIVE_MODE=30, 
		KEYWORD_LANGUAGE=31, KEYWORD_LEFT_ASSOC=32, KEYWORD_NAME=33, KEYWORD_NAMED=34, 
		KEYWORD_NOTES=35, KEYWORD_PRINT_SUCCESS=36, KEYWORD_PRODUCE_ASSIGNMENTS=37, 
		KEYWORD_PRODUCE_MODELS=38, KEYWORD_PRODUCE_PROOFS=39, KEYWORD_PRODUCE_UNSAT_CORES=40, 
		KEYWORD_RANDOM_SEED=41, KEYWORD_REASON_UNKNOWN=42, KEYWORD_REGULAR_OUTPUT_CHANNEL=43, 
		KEYWORD_RIGHT_ASSOC=44, KEYWORD_SORTS=45, KEYWORD_SORTS_DESCRIPTION=46, 
		KEYWORD_STATUS=47, KEYWORD_THEORIES=48, KEYWORD_VALUES=49, KEYWORD_VERBOSITY=50, 
		KEYWORD_VERSION=51, TOKEN_BANG=52, TOKEN_UNDERSCORE=53, TOKEN_AS=54, TOKEN_DECIMAL=55, 
		TOKEN_EXISTS=56, TOKEN_FORALL=57, TOKEN_LET=58, TOKEN_NUMERAL=59, TOKEN_PAR=60, 
		TOKEN_STRING=61, TOKEN_CMD_ASSERT=62, TOKEN_CMD_CHECK_SAT=63, TOKEN_CMD_DECLARE_SORT=64, 
		TOKEN_CMD_DECLARE_FUN=65, TOKEN_CMD_DEFINE_SORT=66, TOKEN_CMD_DEFINE_FUN=67, 
		TOKEN_CMD_EXIT=68, TOKEN_CMD_GET_ASSERTIONS=69, TOKEN_CMD_GET_ASSIGNMENT=70, 
		TOKEN_CMD_GET_INFO=71, TOKEN_CMD_GET_OPTION=72, TOKEN_CMD_GET_PROOF=73, 
		TOKEN_CMD_GET_UNSAT_CORE=74, TOKEN_CMD_GET_VALUE=75, TOKEN_CMD_POP=76, 
		TOKEN_CMD_PUSH=77, TOKEN_CMD_SET_LOGIC=78, TOKEN_CMD_SET_INFO=79, TOKEN_CMD_SET_OPTION=80, 
		TOKEN_CMD_GET_MODEL=81, NUMERAL=82, DECIMAL=83, HEXADECIMAL=84, BINARY=85, 
		STRING=86, WS=87, SIMPLE_SYM=88, QUOTED_SYM=89, COMMENT=90, KEYWORD_TOKEN=91, 
		OpenPar=92, ClosePar=93;
	public static final int
		RULE_symbol = 0, RULE_keyword = 1, RULE_spec_constant = 2, RULE_s_expr = 3, 
		RULE_identifier = 4, RULE_sort = 5, RULE_attribute_value = 6, RULE_attribute = 7, 
		RULE_qual_identifier = 8, RULE_var_binding = 9, RULE_sorted_var = 10, 
		RULE_term = 11, RULE_sort_symbol_decl = 12, RULE_meta_spec_constant = 13, 
		RULE_fun_symbol_decl = 14, RULE_par_fun_symbol_decl = 15, RULE_theory_decl = 16, 
		RULE_theory_attribute = 17, RULE_logic_attribute = 18, RULE_logic = 19, 
		RULE_b_value = 20, RULE_option = 21, RULE_info_flag = 22, RULE_command = 23, 
		RULE_script = 24, RULE_gen_response = 25, RULE_error_behavior = 26, RULE_reason_unknown = 27, 
		RULE_status = 28, RULE_info_response = 29, RULE_get_info_response = 30, 
		RULE_check_sat_response = 31, RULE_get_assertions_response = 32, RULE_proof = 33, 
		RULE_get_proof_response = 34, RULE_get_unsat_core_response = 35, RULE_valuation_pair = 36, 
		RULE_get_value_response = 37, RULE_t_valuation_pair = 38, RULE_get_assignment_response = 39, 
		RULE_get_option_response = 40;
	public static final String[] ruleNames = {
		"symbol", "keyword", "spec_constant", "s_expr", "identifier", "sort", 
		"attribute_value", "attribute", "qual_identifier", "var_binding", "sorted_var", 
		"term", "sort_symbol_decl", "meta_spec_constant", "fun_symbol_decl", "par_fun_symbol_decl", 
		"theory_decl", "theory_attribute", "logic_attribute", "logic", "b_value", 
		"option", "info_flag", "command", "script", "gen_response", "error_behavior", 
		"reason_unknown", "status", "info_response", "get_info_response", "check_sat_response", 
		"get_assertions_response", "proof", "get_proof_response", "get_unsat_core_response", 
		"valuation_pair", "get_value_response", "t_valuation_pair", "get_assignment_response", 
		"get_option_response"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'and'", "'or'", "'not'", "'Bool'", "'continued-execution'", "'error'", 
		"'false'", "'immediate-exit'", "'incomplete'", "'logic'", "'memout'", 
		"'sat'", "'success'", "'theory'", "'true'", "'unknown'", "'unsat'", "'unsupported'", 
		"':all-statistics'", "':authors'", "':axioms'", "':chainable'", "':definition'", 
		"':diagnostic-output-channel'", "':error-behavior'", "':expand-definitions'", 
		"':extensions'", "':funs'", "':funs-description'", "':interactive-mode'", 
		"':language'", "':left-assoc'", "':name'", "':named'", "':notes'", "':print-success'", 
		"':produce-assignments'", "':produce-models'", "':produce-proofs'", "':produce-unsat-cores'", 
		"':random-seed'", "':reason-unknown'", "':regular-output-channel'", "':right-assoc'", 
		"':sorts'", "':sorts-description'", "':status'", "':theories'", "':values'", 
		"':verbosity'", "':version'", "'!'", "'_'", "'as'", "'DECIMAL'", "'exists'", 
		"'forall'", "'let'", "'NUMERAL'", "'par'", "'STRING'", "'assert'", "'check-sat'", 
		"'declare-sort'", "'declare-fun'", "'define-sort'", "'define-fun'", "'exit'", 
		"'get-assertions'", "'get-assignment'", "'get-info'", "'get-option'", 
		"'get-proof'", "'get-unsat-core'", "'get-value'", "'pop'", "'push'", "'set-logic'", 
		"'set-info'", "'set-option'", "'get-model'", null, null, null, null, null, 
		null, null, null, null, null, "'('", "')'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "SYM_AND", "SYM_OR", "SYM_NOT", "SYM_BOOL", "SYM_CONTINUED_EXECUTION", 
		"SYM_ERROR", "SYM_FALSE", "SYM_IMMEDIATE_EXIT", "SYM_INCOMPLETE", "SYM_LOGIC", 
		"SYM_MEMOUT", "SYM_SAT", "SYM_SUCCESS", "SYM_THEORY", "SYM_TRUE", "SYM_UNKNOWN", 
		"SYM_UNSAT", "SYM_UNSUPPORTED", "KEYWORD_ALL_STATISTICS", "KEYWORD_AUTHORS", 
		"KEYWORD_AXIOMS", "KEYWORD_CHAINABLE", "KEYWORD_DEFINITION", "KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL", 
		"KEYWORD_ERROR_BEHAVIOR", "KEYWORD_EXPAND_DEFINITIONS", "KEYWORD_EXTENSIONS", 
		"KEYWORD_FUNS", "KEYWORD_FUNS_DESCRIPTION", "KEYWORD_INTERACTIVE_MODE", 
		"KEYWORD_LANGUAGE", "KEYWORD_LEFT_ASSOC", "KEYWORD_NAME", "KEYWORD_NAMED", 
		"KEYWORD_NOTES", "KEYWORD_PRINT_SUCCESS", "KEYWORD_PRODUCE_ASSIGNMENTS", 
		"KEYWORD_PRODUCE_MODELS", "KEYWORD_PRODUCE_PROOFS", "KEYWORD_PRODUCE_UNSAT_CORES", 
		"KEYWORD_RANDOM_SEED", "KEYWORD_REASON_UNKNOWN", "KEYWORD_REGULAR_OUTPUT_CHANNEL", 
		"KEYWORD_RIGHT_ASSOC", "KEYWORD_SORTS", "KEYWORD_SORTS_DESCRIPTION", "KEYWORD_STATUS", 
		"KEYWORD_THEORIES", "KEYWORD_VALUES", "KEYWORD_VERBOSITY", "KEYWORD_VERSION", 
		"TOKEN_BANG", "TOKEN_UNDERSCORE", "TOKEN_AS", "TOKEN_DECIMAL", "TOKEN_EXISTS", 
		"TOKEN_FORALL", "TOKEN_LET", "TOKEN_NUMERAL", "TOKEN_PAR", "TOKEN_STRING", 
		"TOKEN_CMD_ASSERT", "TOKEN_CMD_CHECK_SAT", "TOKEN_CMD_DECLARE_SORT", "TOKEN_CMD_DECLARE_FUN", 
		"TOKEN_CMD_DEFINE_SORT", "TOKEN_CMD_DEFINE_FUN", "TOKEN_CMD_EXIT", "TOKEN_CMD_GET_ASSERTIONS", 
		"TOKEN_CMD_GET_ASSIGNMENT", "TOKEN_CMD_GET_INFO", "TOKEN_CMD_GET_OPTION", 
		"TOKEN_CMD_GET_PROOF", "TOKEN_CMD_GET_UNSAT_CORE", "TOKEN_CMD_GET_VALUE", 
		"TOKEN_CMD_POP", "TOKEN_CMD_PUSH", "TOKEN_CMD_SET_LOGIC", "TOKEN_CMD_SET_INFO", 
		"TOKEN_CMD_SET_OPTION", "TOKEN_CMD_GET_MODEL", "NUMERAL", "DECIMAL", "HEXADECIMAL", 
		"BINARY", "STRING", "WS", "SIMPLE_SYM", "QUOTED_SYM", "COMMENT", "KEYWORD_TOKEN", 
		"OpenPar", "ClosePar"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "SMTLIB26Parser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }


	/* public parser declarations/members section */
	bool myAction() { return true; }
	bool doesItBlend() { return true; }
	void cleanUp() {}
	void doInit() {}
	void doAfter() {}

	public SMTLIB26Parser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class SymbolContext extends ParserRuleContext {
		public TerminalNode SIMPLE_SYM() { return getToken(SMTLIB26Parser.SIMPLE_SYM, 0); }
		public TerminalNode SYM_AND() { return getToken(SMTLIB26Parser.SYM_AND, 0); }
		public TerminalNode SYM_OR() { return getToken(SMTLIB26Parser.SYM_OR, 0); }
		public TerminalNode SYM_NOT() { return getToken(SMTLIB26Parser.SYM_NOT, 0); }
		public TerminalNode QUOTED_SYM() { return getToken(SMTLIB26Parser.QUOTED_SYM, 0); }
		public TerminalNode SYM_BOOL() { return getToken(SMTLIB26Parser.SYM_BOOL, 0); }
		public TerminalNode SYM_CONTINUED_EXECUTION() { return getToken(SMTLIB26Parser.SYM_CONTINUED_EXECUTION, 0); }
		public TerminalNode SYM_ERROR() { return getToken(SMTLIB26Parser.SYM_ERROR, 0); }
		public TerminalNode SYM_FALSE() { return getToken(SMTLIB26Parser.SYM_FALSE, 0); }
		public TerminalNode SYM_IMMEDIATE_EXIT() { return getToken(SMTLIB26Parser.SYM_IMMEDIATE_EXIT, 0); }
		public TerminalNode SYM_INCOMPLETE() { return getToken(SMTLIB26Parser.SYM_INCOMPLETE, 0); }
		public TerminalNode SYM_LOGIC() { return getToken(SMTLIB26Parser.SYM_LOGIC, 0); }
		public TerminalNode SYM_MEMOUT() { return getToken(SMTLIB26Parser.SYM_MEMOUT, 0); }
		public TerminalNode SYM_SAT() { return getToken(SMTLIB26Parser.SYM_SAT, 0); }
		public TerminalNode SYM_SUCCESS() { return getToken(SMTLIB26Parser.SYM_SUCCESS, 0); }
		public TerminalNode SYM_THEORY() { return getToken(SMTLIB26Parser.SYM_THEORY, 0); }
		public TerminalNode SYM_TRUE() { return getToken(SMTLIB26Parser.SYM_TRUE, 0); }
		public TerminalNode SYM_UNKNOWN() { return getToken(SMTLIB26Parser.SYM_UNKNOWN, 0); }
		public TerminalNode SYM_UNSAT() { return getToken(SMTLIB26Parser.SYM_UNSAT, 0); }
		public TerminalNode SYM_UNSUPPORTED() { return getToken(SMTLIB26Parser.SYM_UNSUPPORTED, 0); }
		public SymbolContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_symbol; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterSymbol(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitSymbol(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitSymbol(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SymbolContext symbol() throws RecognitionException {
		SymbolContext _localctx = new SymbolContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_symbol);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(82);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || _la==SIMPLE_SYM || _la==QUOTED_SYM) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class KeywordContext extends ParserRuleContext {
		public TerminalNode KEYWORD_TOKEN() { return getToken(SMTLIB26Parser.KEYWORD_TOKEN, 0); }
		public TerminalNode KEYWORD_ALL_STATISTICS() { return getToken(SMTLIB26Parser.KEYWORD_ALL_STATISTICS, 0); }
		public TerminalNode KEYWORD_AUTHORS() { return getToken(SMTLIB26Parser.KEYWORD_AUTHORS, 0); }
		public TerminalNode KEYWORD_AXIOMS() { return getToken(SMTLIB26Parser.KEYWORD_AXIOMS, 0); }
		public TerminalNode KEYWORD_CHAINABLE() { return getToken(SMTLIB26Parser.KEYWORD_CHAINABLE, 0); }
		public TerminalNode KEYWORD_DEFINITION() { return getToken(SMTLIB26Parser.KEYWORD_DEFINITION, 0); }
		public TerminalNode KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL() { return getToken(SMTLIB26Parser.KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL, 0); }
		public TerminalNode KEYWORD_ERROR_BEHAVIOR() { return getToken(SMTLIB26Parser.KEYWORD_ERROR_BEHAVIOR, 0); }
		public TerminalNode KEYWORD_EXPAND_DEFINITIONS() { return getToken(SMTLIB26Parser.KEYWORD_EXPAND_DEFINITIONS, 0); }
		public TerminalNode KEYWORD_EXTENSIONS() { return getToken(SMTLIB26Parser.KEYWORD_EXTENSIONS, 0); }
		public TerminalNode KEYWORD_FUNS() { return getToken(SMTLIB26Parser.KEYWORD_FUNS, 0); }
		public TerminalNode KEYWORD_FUNS_DESCRIPTION() { return getToken(SMTLIB26Parser.KEYWORD_FUNS_DESCRIPTION, 0); }
		public TerminalNode KEYWORD_INTERACTIVE_MODE() { return getToken(SMTLIB26Parser.KEYWORD_INTERACTIVE_MODE, 0); }
		public TerminalNode KEYWORD_LANGUAGE() { return getToken(SMTLIB26Parser.KEYWORD_LANGUAGE, 0); }
		public TerminalNode KEYWORD_LEFT_ASSOC() { return getToken(SMTLIB26Parser.KEYWORD_LEFT_ASSOC, 0); }
		public TerminalNode KEYWORD_NAME() { return getToken(SMTLIB26Parser.KEYWORD_NAME, 0); }
		public TerminalNode KEYWORD_NAMED() { return getToken(SMTLIB26Parser.KEYWORD_NAMED, 0); }
		public TerminalNode KEYWORD_NOTES() { return getToken(SMTLIB26Parser.KEYWORD_NOTES, 0); }
		public TerminalNode KEYWORD_PRINT_SUCCESS() { return getToken(SMTLIB26Parser.KEYWORD_PRINT_SUCCESS, 0); }
		public TerminalNode KEYWORD_PRODUCE_ASSIGNMENTS() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_ASSIGNMENTS, 0); }
		public TerminalNode KEYWORD_PRODUCE_MODELS() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_MODELS, 0); }
		public TerminalNode KEYWORD_PRODUCE_PROOFS() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_PROOFS, 0); }
		public TerminalNode KEYWORD_PRODUCE_UNSAT_CORES() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_UNSAT_CORES, 0); }
		public TerminalNode KEYWORD_RANDOM_SEED() { return getToken(SMTLIB26Parser.KEYWORD_RANDOM_SEED, 0); }
		public TerminalNode KEYWORD_REASON_UNKNOWN() { return getToken(SMTLIB26Parser.KEYWORD_REASON_UNKNOWN, 0); }
		public TerminalNode KEYWORD_REGULAR_OUTPUT_CHANNEL() { return getToken(SMTLIB26Parser.KEYWORD_REGULAR_OUTPUT_CHANNEL, 0); }
		public TerminalNode KEYWORD_RIGHT_ASSOC() { return getToken(SMTLIB26Parser.KEYWORD_RIGHT_ASSOC, 0); }
		public TerminalNode KEYWORD_SORTS() { return getToken(SMTLIB26Parser.KEYWORD_SORTS, 0); }
		public TerminalNode KEYWORD_SORTS_DESCRIPTION() { return getToken(SMTLIB26Parser.KEYWORD_SORTS_DESCRIPTION, 0); }
		public TerminalNode KEYWORD_STATUS() { return getToken(SMTLIB26Parser.KEYWORD_STATUS, 0); }
		public TerminalNode KEYWORD_THEORIES() { return getToken(SMTLIB26Parser.KEYWORD_THEORIES, 0); }
		public TerminalNode KEYWORD_VALUES() { return getToken(SMTLIB26Parser.KEYWORD_VALUES, 0); }
		public TerminalNode KEYWORD_VERBOSITY() { return getToken(SMTLIB26Parser.KEYWORD_VERBOSITY, 0); }
		public TerminalNode KEYWORD_VERSION() { return getToken(SMTLIB26Parser.KEYWORD_VERSION, 0); }
		public KeywordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keyword; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterKeyword(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitKeyword(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitKeyword(this);
			else return visitor.visitChildren(this);
		}
	}

	public final KeywordContext keyword() throws RecognitionException {
		KeywordContext _localctx = new KeywordContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_keyword);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Spec_constantContext extends ParserRuleContext {
		public TerminalNode NUMERAL() { return getToken(SMTLIB26Parser.NUMERAL, 0); }
		public TerminalNode DECIMAL() { return getToken(SMTLIB26Parser.DECIMAL, 0); }
		public TerminalNode HEXADECIMAL() { return getToken(SMTLIB26Parser.HEXADECIMAL, 0); }
		public TerminalNode BINARY() { return getToken(SMTLIB26Parser.BINARY, 0); }
		public TerminalNode STRING() { return getToken(SMTLIB26Parser.STRING, 0); }
		public Spec_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_spec_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterSpec_constant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitSpec_constant(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitSpec_constant(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Spec_constantContext spec_constant() throws RecognitionException {
		Spec_constantContext _localctx = new Spec_constantContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_spec_constant);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(86);
			_la = _input.LA(1);
			if ( !(((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (NUMERAL - 82)) | (1L << (DECIMAL - 82)) | (1L << (HEXADECIMAL - 82)) | (1L << (BINARY - 82)) | (1L << (STRING - 82)))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class S_exprContext extends ParserRuleContext {
		public Spec_constantContext spec_constant() {
			return getRuleContext(Spec_constantContext.class,0);
		}
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public KeywordContext keyword() {
			return getRuleContext(KeywordContext.class,0);
		}
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<S_exprContext> s_expr() {
			return getRuleContexts(S_exprContext.class);
		}
		public S_exprContext s_expr(int i) {
			return getRuleContext(S_exprContext.class,i);
		}
		public S_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_s_expr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterS_expr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitS_expr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitS_expr(this);
			else return visitor.visitChildren(this);
		}
	}

	public final S_exprContext s_expr() throws RecognitionException {
		S_exprContext _localctx = new S_exprContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_s_expr);
		int _la;
		try {
			setState(99);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NUMERAL:
			case DECIMAL:
			case HEXADECIMAL:
			case BINARY:
			case STRING:
				enterOuterAlt(_localctx, 1);
				{
				setState(88);
				spec_constant();
				}
				break;
			case SYM_AND:
			case SYM_OR:
			case SYM_NOT:
			case SYM_BOOL:
			case SYM_CONTINUED_EXECUTION:
			case SYM_ERROR:
			case SYM_FALSE:
			case SYM_IMMEDIATE_EXIT:
			case SYM_INCOMPLETE:
			case SYM_LOGIC:
			case SYM_MEMOUT:
			case SYM_SAT:
			case SYM_SUCCESS:
			case SYM_THEORY:
			case SYM_TRUE:
			case SYM_UNKNOWN:
			case SYM_UNSAT:
			case SYM_UNSUPPORTED:
			case SIMPLE_SYM:
			case QUOTED_SYM:
				enterOuterAlt(_localctx, 2);
				{
				setState(89);
				symbol();
				}
				break;
			case KEYWORD_ALL_STATISTICS:
			case KEYWORD_AUTHORS:
			case KEYWORD_AXIOMS:
			case KEYWORD_CHAINABLE:
			case KEYWORD_DEFINITION:
			case KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL:
			case KEYWORD_ERROR_BEHAVIOR:
			case KEYWORD_EXPAND_DEFINITIONS:
			case KEYWORD_EXTENSIONS:
			case KEYWORD_FUNS:
			case KEYWORD_FUNS_DESCRIPTION:
			case KEYWORD_INTERACTIVE_MODE:
			case KEYWORD_LANGUAGE:
			case KEYWORD_LEFT_ASSOC:
			case KEYWORD_NAME:
			case KEYWORD_NAMED:
			case KEYWORD_NOTES:
			case KEYWORD_PRINT_SUCCESS:
			case KEYWORD_PRODUCE_ASSIGNMENTS:
			case KEYWORD_PRODUCE_MODELS:
			case KEYWORD_PRODUCE_PROOFS:
			case KEYWORD_PRODUCE_UNSAT_CORES:
			case KEYWORD_RANDOM_SEED:
			case KEYWORD_REASON_UNKNOWN:
			case KEYWORD_REGULAR_OUTPUT_CHANNEL:
			case KEYWORD_RIGHT_ASSOC:
			case KEYWORD_SORTS:
			case KEYWORD_SORTS_DESCRIPTION:
			case KEYWORD_STATUS:
			case KEYWORD_THEORIES:
			case KEYWORD_VALUES:
			case KEYWORD_VERBOSITY:
			case KEYWORD_VERSION:
			case KEYWORD_TOKEN:
				enterOuterAlt(_localctx, 3);
				{
				setState(90);
				keyword();
				}
				break;
			case OpenPar:
				enterOuterAlt(_localctx, 4);
				{
				setState(91);
				match(OpenPar);
				setState(95);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED) | (1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || ((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (NUMERAL - 82)) | (1L << (DECIMAL - 82)) | (1L << (HEXADECIMAL - 82)) | (1L << (BINARY - 82)) | (1L << (STRING - 82)) | (1L << (SIMPLE_SYM - 82)) | (1L << (QUOTED_SYM - 82)) | (1L << (KEYWORD_TOKEN - 82)) | (1L << (OpenPar - 82)))) != 0)) {
					{
					{
					setState(92);
					s_expr();
					}
					}
					setState(97);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(98);
				match(ClosePar);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IdentifierContext extends ParserRuleContext {
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode TOKEN_UNDERSCORE() { return getToken(SMTLIB26Parser.TOKEN_UNDERSCORE, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<TerminalNode> NUMERAL() { return getTokens(SMTLIB26Parser.NUMERAL); }
		public TerminalNode NUMERAL(int i) {
			return getToken(SMTLIB26Parser.NUMERAL, i);
		}
		public IdentifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterIdentifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitIdentifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitIdentifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IdentifierContext identifier() throws RecognitionException {
		IdentifierContext _localctx = new IdentifierContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_identifier);
		int _la;
		try {
			setState(112);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYM_AND:
			case SYM_OR:
			case SYM_NOT:
			case SYM_BOOL:
			case SYM_CONTINUED_EXECUTION:
			case SYM_ERROR:
			case SYM_FALSE:
			case SYM_IMMEDIATE_EXIT:
			case SYM_INCOMPLETE:
			case SYM_LOGIC:
			case SYM_MEMOUT:
			case SYM_SAT:
			case SYM_SUCCESS:
			case SYM_THEORY:
			case SYM_TRUE:
			case SYM_UNKNOWN:
			case SYM_UNSAT:
			case SYM_UNSUPPORTED:
			case SIMPLE_SYM:
			case QUOTED_SYM:
				enterOuterAlt(_localctx, 1);
				{
				setState(101);
				symbol();
				}
				break;
			case OpenPar:
				enterOuterAlt(_localctx, 2);
				{
				setState(102);
				match(OpenPar);
				setState(103);
				match(TOKEN_UNDERSCORE);
				setState(104);
				symbol();
				setState(106); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(105);
					match(NUMERAL);
					}
					}
					setState(108); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==NUMERAL );
				setState(110);
				match(ClosePar);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SortContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<SortContext> sort() {
			return getRuleContexts(SortContext.class);
		}
		public SortContext sort(int i) {
			return getRuleContext(SortContext.class,i);
		}
		public SortContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sort; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterSort(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitSort(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitSort(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SortContext sort() throws RecognitionException {
		SortContext _localctx = new SortContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_sort);
		int _la;
		try {
			setState(124);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(114);
				identifier();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(115);
				match(OpenPar);
				setState(116);
				identifier();
				setState(118); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(117);
					sort();
					}
					}
					setState(120); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 88)) & ~0x3f) == 0 && ((1L << (_la - 88)) & ((1L << (SIMPLE_SYM - 88)) | (1L << (QUOTED_SYM - 88)) | (1L << (OpenPar - 88)))) != 0) );
				setState(122);
				match(ClosePar);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Attribute_valueContext extends ParserRuleContext {
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public Spec_constantContext spec_constant() {
			return getRuleContext(Spec_constantContext.class,0);
		}
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<S_exprContext> s_expr() {
			return getRuleContexts(S_exprContext.class);
		}
		public S_exprContext s_expr(int i) {
			return getRuleContext(S_exprContext.class,i);
		}
		public Attribute_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterAttribute_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitAttribute_value(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitAttribute_value(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Attribute_valueContext attribute_value() throws RecognitionException {
		Attribute_valueContext _localctx = new Attribute_valueContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_attribute_value);
		int _la;
		try {
			setState(136);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYM_AND:
			case SYM_OR:
			case SYM_NOT:
			case SYM_BOOL:
			case SYM_CONTINUED_EXECUTION:
			case SYM_ERROR:
			case SYM_FALSE:
			case SYM_IMMEDIATE_EXIT:
			case SYM_INCOMPLETE:
			case SYM_LOGIC:
			case SYM_MEMOUT:
			case SYM_SAT:
			case SYM_SUCCESS:
			case SYM_THEORY:
			case SYM_TRUE:
			case SYM_UNKNOWN:
			case SYM_UNSAT:
			case SYM_UNSUPPORTED:
			case SIMPLE_SYM:
			case QUOTED_SYM:
				enterOuterAlt(_localctx, 1);
				{
				setState(126);
				symbol();
				}
				break;
			case NUMERAL:
			case DECIMAL:
			case HEXADECIMAL:
			case BINARY:
			case STRING:
				enterOuterAlt(_localctx, 2);
				{
				setState(127);
				spec_constant();
				}
				break;
			case OpenPar:
				enterOuterAlt(_localctx, 3);
				{
				setState(128);
				match(OpenPar);
				setState(132);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED) | (1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || ((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (NUMERAL - 82)) | (1L << (DECIMAL - 82)) | (1L << (HEXADECIMAL - 82)) | (1L << (BINARY - 82)) | (1L << (STRING - 82)) | (1L << (SIMPLE_SYM - 82)) | (1L << (QUOTED_SYM - 82)) | (1L << (KEYWORD_TOKEN - 82)) | (1L << (OpenPar - 82)))) != 0)) {
					{
					{
					setState(129);
					s_expr();
					}
					}
					setState(134);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(135);
				match(ClosePar);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AttributeContext extends ParserRuleContext {
		public KeywordContext keyword() {
			return getRuleContext(KeywordContext.class,0);
		}
		public Attribute_valueContext attribute_value() {
			return getRuleContext(Attribute_valueContext.class,0);
		}
		public AttributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterAttribute(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitAttribute(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitAttribute(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AttributeContext attribute() throws RecognitionException {
		AttributeContext _localctx = new AttributeContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_attribute);
		try {
			setState(142);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(138);
				keyword();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(139);
				keyword();
				setState(140);
				attribute_value();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Qual_identifierContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode TOKEN_AS() { return getToken(SMTLIB26Parser.TOKEN_AS, 0); }
		public SortContext sort() {
			return getRuleContext(SortContext.class,0);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public Qual_identifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qual_identifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterQual_identifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitQual_identifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitQual_identifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Qual_identifierContext qual_identifier() throws RecognitionException {
		Qual_identifierContext _localctx = new Qual_identifierContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_qual_identifier);
		try {
			setState(151);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(144);
				identifier();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(145);
				match(OpenPar);
				setState(146);
				match(TOKEN_AS);
				setState(147);
				identifier();
				setState(148);
				sort();
				setState(149);
				match(ClosePar);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Var_bindingContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public Var_bindingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var_binding; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterVar_binding(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitVar_binding(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitVar_binding(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Var_bindingContext var_binding() throws RecognitionException {
		Var_bindingContext _localctx = new Var_bindingContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_var_binding);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(153);
			match(OpenPar);
			setState(154);
			symbol();
			setState(155);
			term();
			setState(156);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Sorted_varContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public SortContext sort() {
			return getRuleContext(SortContext.class,0);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public Sorted_varContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sorted_var; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterSorted_var(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitSorted_var(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitSorted_var(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Sorted_varContext sorted_var() throws RecognitionException {
		Sorted_varContext _localctx = new Sorted_varContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_sorted_var);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(158);
			match(OpenPar);
			setState(159);
			symbol();
			setState(160);
			sort();
			setState(161);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TermContext extends ParserRuleContext {
		public Spec_constantContext spec_constant() {
			return getRuleContext(Spec_constantContext.class,0);
		}
		public Qual_identifierContext qual_identifier() {
			return getRuleContext(Qual_identifierContext.class,0);
		}
		public List<TerminalNode> OpenPar() { return getTokens(SMTLIB26Parser.OpenPar); }
		public TerminalNode OpenPar(int i) {
			return getToken(SMTLIB26Parser.OpenPar, i);
		}
		public List<TerminalNode> ClosePar() { return getTokens(SMTLIB26Parser.ClosePar); }
		public TerminalNode ClosePar(int i) {
			return getToken(SMTLIB26Parser.ClosePar, i);
		}
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public TerminalNode TOKEN_LET() { return getToken(SMTLIB26Parser.TOKEN_LET, 0); }
		public List<Var_bindingContext> var_binding() {
			return getRuleContexts(Var_bindingContext.class);
		}
		public Var_bindingContext var_binding(int i) {
			return getRuleContext(Var_bindingContext.class,i);
		}
		public TerminalNode TOKEN_FORALL() { return getToken(SMTLIB26Parser.TOKEN_FORALL, 0); }
		public List<Sorted_varContext> sorted_var() {
			return getRuleContexts(Sorted_varContext.class);
		}
		public Sorted_varContext sorted_var(int i) {
			return getRuleContext(Sorted_varContext.class,i);
		}
		public TerminalNode TOKEN_EXISTS() { return getToken(SMTLIB26Parser.TOKEN_EXISTS, 0); }
		public TerminalNode TOKEN_BANG() { return getToken(SMTLIB26Parser.TOKEN_BANG, 0); }
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterTerm(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitTerm(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitTerm(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TermContext term() throws RecognitionException {
		TermContext _localctx = new TermContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_term);
		int _la;
		try {
			setState(220);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(163);
				spec_constant();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(164);
				qual_identifier();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(165);
				match(OpenPar);
				setState(166);
				qual_identifier();
				setState(168); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(167);
					term();
					}
					}
					setState(170); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (NUMERAL - 82)) | (1L << (DECIMAL - 82)) | (1L << (HEXADECIMAL - 82)) | (1L << (BINARY - 82)) | (1L << (STRING - 82)) | (1L << (SIMPLE_SYM - 82)) | (1L << (QUOTED_SYM - 82)) | (1L << (OpenPar - 82)))) != 0) );
				setState(172);
				match(ClosePar);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(174);
				match(OpenPar);
				setState(175);
				match(TOKEN_LET);
				setState(176);
				match(OpenPar);
				setState(178); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(177);
					var_binding();
					}
					}
					setState(180); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==OpenPar );
				setState(182);
				match(ClosePar);
				setState(183);
				term();
				setState(184);
				match(ClosePar);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(186);
				match(OpenPar);
				setState(187);
				match(TOKEN_FORALL);
				setState(188);
				match(OpenPar);
				setState(190); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(189);
					sorted_var();
					}
					}
					setState(192); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==OpenPar );
				setState(194);
				match(ClosePar);
				setState(195);
				term();
				setState(196);
				match(ClosePar);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(198);
				match(OpenPar);
				setState(199);
				match(TOKEN_EXISTS);
				setState(200);
				match(OpenPar);
				setState(202); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(201);
					sorted_var();
					}
					}
					setState(204); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==OpenPar );
				setState(206);
				match(ClosePar);
				setState(207);
				term();
				setState(208);
				match(ClosePar);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(210);
				match(OpenPar);
				setState(211);
				match(TOKEN_BANG);
				setState(212);
				term();
				setState(214); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(213);
					attribute();
					}
					}
					setState(216); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN );
				setState(218);
				match(ClosePar);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Sort_symbol_declContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode NUMERAL() { return getToken(SMTLIB26Parser.NUMERAL, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public Sort_symbol_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sort_symbol_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterSort_symbol_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitSort_symbol_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitSort_symbol_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Sort_symbol_declContext sort_symbol_decl() throws RecognitionException {
		Sort_symbol_declContext _localctx = new Sort_symbol_declContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_sort_symbol_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(222);
			match(OpenPar);
			setState(223);
			identifier();
			setState(224);
			match(NUMERAL);
			setState(228);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN) {
				{
				{
				setState(225);
				attribute();
				}
				}
				setState(230);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(231);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Meta_spec_constantContext extends ParserRuleContext {
		public TerminalNode TOKEN_NUMERAL() { return getToken(SMTLIB26Parser.TOKEN_NUMERAL, 0); }
		public TerminalNode TOKEN_DECIMAL() { return getToken(SMTLIB26Parser.TOKEN_DECIMAL, 0); }
		public TerminalNode TOKEN_STRING() { return getToken(SMTLIB26Parser.TOKEN_STRING, 0); }
		public Meta_spec_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_meta_spec_constant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterMeta_spec_constant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitMeta_spec_constant(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitMeta_spec_constant(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Meta_spec_constantContext meta_spec_constant() throws RecognitionException {
		Meta_spec_constantContext _localctx = new Meta_spec_constantContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_meta_spec_constant);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(233);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << TOKEN_DECIMAL) | (1L << TOKEN_NUMERAL) | (1L << TOKEN_STRING))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Fun_symbol_declContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public Spec_constantContext spec_constant() {
			return getRuleContext(Spec_constantContext.class,0);
		}
		public List<SortContext> sort() {
			return getRuleContexts(SortContext.class);
		}
		public SortContext sort(int i) {
			return getRuleContext(SortContext.class,i);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public Meta_spec_constantContext meta_spec_constant() {
			return getRuleContext(Meta_spec_constantContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public Fun_symbol_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fun_symbol_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterFun_symbol_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitFun_symbol_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitFun_symbol_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Fun_symbol_declContext fun_symbol_decl() throws RecognitionException {
		Fun_symbol_declContext _localctx = new Fun_symbol_declContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_fun_symbol_decl);
		int _la;
		try {
			setState(272);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(235);
				match(OpenPar);
				setState(236);
				spec_constant();
				setState(237);
				sort();
				setState(241);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN) {
					{
					{
					setState(238);
					attribute();
					}
					}
					setState(243);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(244);
				match(ClosePar);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(246);
				match(OpenPar);
				setState(247);
				meta_spec_constant();
				setState(248);
				sort();
				setState(252);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN) {
					{
					{
					setState(249);
					attribute();
					}
					}
					setState(254);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(255);
				match(ClosePar);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(257);
				match(OpenPar);
				setState(258);
				identifier();
				setState(260); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(259);
					sort();
					}
					}
					setState(262); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 88)) & ~0x3f) == 0 && ((1L << (_la - 88)) & ((1L << (SIMPLE_SYM - 88)) | (1L << (QUOTED_SYM - 88)) | (1L << (OpenPar - 88)))) != 0) );
				setState(267);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN) {
					{
					{
					setState(264);
					attribute();
					}
					}
					setState(269);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(270);
				match(ClosePar);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Par_fun_symbol_declContext extends ParserRuleContext {
		public Fun_symbol_declContext fun_symbol_decl() {
			return getRuleContext(Fun_symbol_declContext.class,0);
		}
		public List<TerminalNode> OpenPar() { return getTokens(SMTLIB26Parser.OpenPar); }
		public TerminalNode OpenPar(int i) {
			return getToken(SMTLIB26Parser.OpenPar, i);
		}
		public TerminalNode TOKEN_PAR() { return getToken(SMTLIB26Parser.TOKEN_PAR, 0); }
		public List<TerminalNode> ClosePar() { return getTokens(SMTLIB26Parser.ClosePar); }
		public TerminalNode ClosePar(int i) {
			return getToken(SMTLIB26Parser.ClosePar, i);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<SymbolContext> symbol() {
			return getRuleContexts(SymbolContext.class);
		}
		public SymbolContext symbol(int i) {
			return getRuleContext(SymbolContext.class,i);
		}
		public List<SortContext> sort() {
			return getRuleContexts(SortContext.class);
		}
		public SortContext sort(int i) {
			return getRuleContext(SortContext.class,i);
		}
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public Par_fun_symbol_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_par_fun_symbol_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterPar_fun_symbol_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitPar_fun_symbol_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitPar_fun_symbol_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Par_fun_symbol_declContext par_fun_symbol_decl() throws RecognitionException {
		Par_fun_symbol_declContext _localctx = new Par_fun_symbol_declContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_par_fun_symbol_decl);
		int _la;
		try {
			setState(300);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,25,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(274);
				fun_symbol_decl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(275);
				match(OpenPar);
				setState(276);
				match(TOKEN_PAR);
				setState(277);
				match(OpenPar);
				setState(279); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(278);
					symbol();
					}
					}
					setState(281); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || _la==SIMPLE_SYM || _la==QUOTED_SYM );
				setState(283);
				match(ClosePar);
				setState(284);
				match(OpenPar);
				setState(285);
				identifier();
				setState(287); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(286);
					sort();
					}
					}
					setState(289); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 88)) & ~0x3f) == 0 && ((1L << (_la - 88)) & ((1L << (SIMPLE_SYM - 88)) | (1L << (QUOTED_SYM - 88)) | (1L << (OpenPar - 88)))) != 0) );
				setState(294);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN) {
					{
					{
					setState(291);
					attribute();
					}
					}
					setState(296);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(297);
				match(ClosePar);
				setState(298);
				match(ClosePar);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Theory_declContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode SYM_THEORY() { return getToken(SMTLIB26Parser.SYM_THEORY, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public List<Theory_attributeContext> theory_attribute() {
			return getRuleContexts(Theory_attributeContext.class);
		}
		public Theory_attributeContext theory_attribute(int i) {
			return getRuleContext(Theory_attributeContext.class,i);
		}
		public Theory_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_theory_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterTheory_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitTheory_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitTheory_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Theory_declContext theory_decl() throws RecognitionException {
		Theory_declContext _localctx = new Theory_declContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_theory_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(302);
			match(OpenPar);
			setState(303);
			match(SYM_THEORY);
			setState(305);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || _la==SIMPLE_SYM || _la==QUOTED_SYM) {
				{
				setState(304);
				symbol();
				}
			}

			setState(308); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(307);
				theory_attribute();
				}
				}
				setState(310); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN );
			setState(312);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Theory_attributeContext extends ParserRuleContext {
		public TerminalNode KEYWORD_SORTS() { return getToken(SMTLIB26Parser.KEYWORD_SORTS, 0); }
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<Sort_symbol_declContext> sort_symbol_decl() {
			return getRuleContexts(Sort_symbol_declContext.class);
		}
		public Sort_symbol_declContext sort_symbol_decl(int i) {
			return getRuleContext(Sort_symbol_declContext.class,i);
		}
		public TerminalNode KEYWORD_FUNS() { return getToken(SMTLIB26Parser.KEYWORD_FUNS, 0); }
		public List<Par_fun_symbol_declContext> par_fun_symbol_decl() {
			return getRuleContexts(Par_fun_symbol_declContext.class);
		}
		public Par_fun_symbol_declContext par_fun_symbol_decl(int i) {
			return getRuleContext(Par_fun_symbol_declContext.class,i);
		}
		public TerminalNode KEYWORD_SORTS_DESCRIPTION() { return getToken(SMTLIB26Parser.KEYWORD_SORTS_DESCRIPTION, 0); }
		public TerminalNode STRING() { return getToken(SMTLIB26Parser.STRING, 0); }
		public TerminalNode KEYWORD_FUNS_DESCRIPTION() { return getToken(SMTLIB26Parser.KEYWORD_FUNS_DESCRIPTION, 0); }
		public TerminalNode KEYWORD_DEFINITION() { return getToken(SMTLIB26Parser.KEYWORD_DEFINITION, 0); }
		public TerminalNode KEYWORD_VALUES() { return getToken(SMTLIB26Parser.KEYWORD_VALUES, 0); }
		public TerminalNode KEYWORD_NOTES() { return getToken(SMTLIB26Parser.KEYWORD_NOTES, 0); }
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public Theory_attributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_theory_attribute; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterTheory_attribute(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitTheory_attribute(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitTheory_attribute(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Theory_attributeContext theory_attribute() throws RecognitionException {
		Theory_attributeContext _localctx = new Theory_attributeContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_theory_attribute);
		int _la;
		try {
			setState(343);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,30,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(314);
				match(KEYWORD_SORTS);
				setState(315);
				match(OpenPar);
				setState(317); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(316);
					sort_symbol_decl();
					}
					}
					setState(319); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==OpenPar );
				setState(321);
				match(ClosePar);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(323);
				match(KEYWORD_FUNS);
				setState(324);
				match(OpenPar);
				setState(326); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(325);
					par_fun_symbol_decl();
					}
					}
					setState(328); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==OpenPar );
				setState(330);
				match(ClosePar);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(332);
				match(KEYWORD_SORTS_DESCRIPTION);
				setState(333);
				match(STRING);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(334);
				match(KEYWORD_FUNS_DESCRIPTION);
				setState(335);
				match(STRING);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(336);
				match(KEYWORD_DEFINITION);
				setState(337);
				match(STRING);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(338);
				match(KEYWORD_VALUES);
				setState(339);
				match(STRING);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(340);
				match(KEYWORD_NOTES);
				setState(341);
				match(STRING);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(342);
				attribute();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Logic_attributeContext extends ParserRuleContext {
		public TerminalNode KEYWORD_THEORIES() { return getToken(SMTLIB26Parser.KEYWORD_THEORIES, 0); }
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<SymbolContext> symbol() {
			return getRuleContexts(SymbolContext.class);
		}
		public SymbolContext symbol(int i) {
			return getRuleContext(SymbolContext.class,i);
		}
		public TerminalNode KEYWORD_LANGUAGE() { return getToken(SMTLIB26Parser.KEYWORD_LANGUAGE, 0); }
		public TerminalNode STRING() { return getToken(SMTLIB26Parser.STRING, 0); }
		public TerminalNode KEYWORD_EXTENSIONS() { return getToken(SMTLIB26Parser.KEYWORD_EXTENSIONS, 0); }
		public TerminalNode KEYWORD_VALUES() { return getToken(SMTLIB26Parser.KEYWORD_VALUES, 0); }
		public TerminalNode KEYWORD_NOTES() { return getToken(SMTLIB26Parser.KEYWORD_NOTES, 0); }
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public Logic_attributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_attribute; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterLogic_attribute(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitLogic_attribute(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitLogic_attribute(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Logic_attributeContext logic_attribute() throws RecognitionException {
		Logic_attributeContext _localctx = new Logic_attributeContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_logic_attribute);
		int _la;
		try {
			setState(363);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,32,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(345);
				match(KEYWORD_THEORIES);
				setState(346);
				match(OpenPar);
				setState(348); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(347);
					symbol();
					}
					}
					setState(350); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || _la==SIMPLE_SYM || _la==QUOTED_SYM );
				setState(352);
				match(ClosePar);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(354);
				match(KEYWORD_LANGUAGE);
				setState(355);
				match(STRING);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(356);
				match(KEYWORD_EXTENSIONS);
				setState(357);
				match(STRING);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(358);
				match(KEYWORD_VALUES);
				setState(359);
				match(STRING);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(360);
				match(KEYWORD_NOTES);
				setState(361);
				match(STRING);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(362);
				attribute();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LogicContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode SYM_LOGIC() { return getToken(SMTLIB26Parser.SYM_LOGIC, 0); }
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<Logic_attributeContext> logic_attribute() {
			return getRuleContexts(Logic_attributeContext.class);
		}
		public Logic_attributeContext logic_attribute(int i) {
			return getRuleContext(Logic_attributeContext.class,i);
		}
		public LogicContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterLogic(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitLogic(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitLogic(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LogicContext logic() throws RecognitionException {
		LogicContext _localctx = new LogicContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_logic);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(365);
			match(OpenPar);
			setState(366);
			match(SYM_LOGIC);
			setState(367);
			symbol();
			setState(369); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(368);
				logic_attribute();
				}
				}
				setState(371); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN );
			setState(373);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class B_valueContext extends ParserRuleContext {
		public TerminalNode SYM_TRUE() { return getToken(SMTLIB26Parser.SYM_TRUE, 0); }
		public TerminalNode SYM_FALSE() { return getToken(SMTLIB26Parser.SYM_FALSE, 0); }
		public B_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_b_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterB_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitB_value(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitB_value(this);
			else return visitor.visitChildren(this);
		}
	}

	public final B_valueContext b_value() throws RecognitionException {
		B_valueContext _localctx = new B_valueContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_b_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(375);
			_la = _input.LA(1);
			if ( !(_la==SYM_FALSE || _la==SYM_TRUE) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OptionContext extends ParserRuleContext {
		public TerminalNode KEYWORD_PRINT_SUCCESS() { return getToken(SMTLIB26Parser.KEYWORD_PRINT_SUCCESS, 0); }
		public B_valueContext b_value() {
			return getRuleContext(B_valueContext.class,0);
		}
		public TerminalNode KEYWORD_EXPAND_DEFINITIONS() { return getToken(SMTLIB26Parser.KEYWORD_EXPAND_DEFINITIONS, 0); }
		public TerminalNode KEYWORD_INTERACTIVE_MODE() { return getToken(SMTLIB26Parser.KEYWORD_INTERACTIVE_MODE, 0); }
		public TerminalNode KEYWORD_PRODUCE_PROOFS() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_PROOFS, 0); }
		public TerminalNode KEYWORD_PRODUCE_UNSAT_CORES() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_UNSAT_CORES, 0); }
		public TerminalNode KEYWORD_PRODUCE_MODELS() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_MODELS, 0); }
		public TerminalNode KEYWORD_PRODUCE_ASSIGNMENTS() { return getToken(SMTLIB26Parser.KEYWORD_PRODUCE_ASSIGNMENTS, 0); }
		public TerminalNode KEYWORD_REGULAR_OUTPUT_CHANNEL() { return getToken(SMTLIB26Parser.KEYWORD_REGULAR_OUTPUT_CHANNEL, 0); }
		public TerminalNode STRING() { return getToken(SMTLIB26Parser.STRING, 0); }
		public TerminalNode KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL() { return getToken(SMTLIB26Parser.KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL, 0); }
		public TerminalNode KEYWORD_RANDOM_SEED() { return getToken(SMTLIB26Parser.KEYWORD_RANDOM_SEED, 0); }
		public TerminalNode NUMERAL() { return getToken(SMTLIB26Parser.NUMERAL, 0); }
		public TerminalNode KEYWORD_VERBOSITY() { return getToken(SMTLIB26Parser.KEYWORD_VERBOSITY, 0); }
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public OptionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_option; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterOption(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitOption(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitOption(this);
			else return visitor.visitChildren(this);
		}
	}

	public final OptionContext option() throws RecognitionException {
		OptionContext _localctx = new OptionContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_option);
		try {
			setState(400);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,34,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(377);
				match(KEYWORD_PRINT_SUCCESS);
				setState(378);
				b_value();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(379);
				match(KEYWORD_EXPAND_DEFINITIONS);
				setState(380);
				b_value();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(381);
				match(KEYWORD_INTERACTIVE_MODE);
				setState(382);
				b_value();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(383);
				match(KEYWORD_PRODUCE_PROOFS);
				setState(384);
				b_value();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(385);
				match(KEYWORD_PRODUCE_UNSAT_CORES);
				setState(386);
				b_value();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(387);
				match(KEYWORD_PRODUCE_MODELS);
				setState(388);
				b_value();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(389);
				match(KEYWORD_PRODUCE_ASSIGNMENTS);
				setState(390);
				b_value();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(391);
				match(KEYWORD_REGULAR_OUTPUT_CHANNEL);
				setState(392);
				match(STRING);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(393);
				match(KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL);
				setState(394);
				match(STRING);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(395);
				match(KEYWORD_RANDOM_SEED);
				setState(396);
				match(NUMERAL);
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(397);
				match(KEYWORD_VERBOSITY);
				setState(398);
				match(NUMERAL);
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(399);
				attribute();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Info_flagContext extends ParserRuleContext {
		public TerminalNode KEYWORD_ERROR_BEHAVIOR() { return getToken(SMTLIB26Parser.KEYWORD_ERROR_BEHAVIOR, 0); }
		public TerminalNode KEYWORD_NAME() { return getToken(SMTLIB26Parser.KEYWORD_NAME, 0); }
		public TerminalNode KEYWORD_AUTHORS() { return getToken(SMTLIB26Parser.KEYWORD_AUTHORS, 0); }
		public TerminalNode KEYWORD_VERSION() { return getToken(SMTLIB26Parser.KEYWORD_VERSION, 0); }
		public TerminalNode KEYWORD_STATUS() { return getToken(SMTLIB26Parser.KEYWORD_STATUS, 0); }
		public TerminalNode KEYWORD_REASON_UNKNOWN() { return getToken(SMTLIB26Parser.KEYWORD_REASON_UNKNOWN, 0); }
		public KeywordContext keyword() {
			return getRuleContext(KeywordContext.class,0);
		}
		public TerminalNode KEYWORD_ALL_STATISTICS() { return getToken(SMTLIB26Parser.KEYWORD_ALL_STATISTICS, 0); }
		public Info_flagContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_info_flag; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterInfo_flag(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitInfo_flag(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitInfo_flag(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Info_flagContext info_flag() throws RecognitionException {
		Info_flagContext _localctx = new Info_flagContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_info_flag);
		try {
			setState(410);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,35,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(402);
				match(KEYWORD_ERROR_BEHAVIOR);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(403);
				match(KEYWORD_NAME);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(404);
				match(KEYWORD_AUTHORS);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(405);
				match(KEYWORD_VERSION);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(406);
				match(KEYWORD_STATUS);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(407);
				match(KEYWORD_REASON_UNKNOWN);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(408);
				keyword();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(409);
				match(KEYWORD_ALL_STATISTICS);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CommandContext extends ParserRuleContext {
		public List<TerminalNode> OpenPar() { return getTokens(SMTLIB26Parser.OpenPar); }
		public TerminalNode OpenPar(int i) {
			return getToken(SMTLIB26Parser.OpenPar, i);
		}
		public TerminalNode TOKEN_CMD_SET_LOGIC() { return getToken(SMTLIB26Parser.TOKEN_CMD_SET_LOGIC, 0); }
		public List<SymbolContext> symbol() {
			return getRuleContexts(SymbolContext.class);
		}
		public SymbolContext symbol(int i) {
			return getRuleContext(SymbolContext.class,i);
		}
		public List<TerminalNode> ClosePar() { return getTokens(SMTLIB26Parser.ClosePar); }
		public TerminalNode ClosePar(int i) {
			return getToken(SMTLIB26Parser.ClosePar, i);
		}
		public TerminalNode TOKEN_CMD_SET_OPTION() { return getToken(SMTLIB26Parser.TOKEN_CMD_SET_OPTION, 0); }
		public OptionContext option() {
			return getRuleContext(OptionContext.class,0);
		}
		public TerminalNode TOKEN_CMD_SET_INFO() { return getToken(SMTLIB26Parser.TOKEN_CMD_SET_INFO, 0); }
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public TerminalNode TOKEN_CMD_DECLARE_SORT() { return getToken(SMTLIB26Parser.TOKEN_CMD_DECLARE_SORT, 0); }
		public TerminalNode NUMERAL() { return getToken(SMTLIB26Parser.NUMERAL, 0); }
		public TerminalNode TOKEN_CMD_DEFINE_SORT() { return getToken(SMTLIB26Parser.TOKEN_CMD_DEFINE_SORT, 0); }
		public List<SortContext> sort() {
			return getRuleContexts(SortContext.class);
		}
		public SortContext sort(int i) {
			return getRuleContext(SortContext.class,i);
		}
		public TerminalNode TOKEN_CMD_DECLARE_FUN() { return getToken(SMTLIB26Parser.TOKEN_CMD_DECLARE_FUN, 0); }
		public TerminalNode TOKEN_CMD_DEFINE_FUN() { return getToken(SMTLIB26Parser.TOKEN_CMD_DEFINE_FUN, 0); }
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public List<Sorted_varContext> sorted_var() {
			return getRuleContexts(Sorted_varContext.class);
		}
		public Sorted_varContext sorted_var(int i) {
			return getRuleContext(Sorted_varContext.class,i);
		}
		public TerminalNode TOKEN_CMD_PUSH() { return getToken(SMTLIB26Parser.TOKEN_CMD_PUSH, 0); }
		public TerminalNode TOKEN_CMD_POP() { return getToken(SMTLIB26Parser.TOKEN_CMD_POP, 0); }
		public TerminalNode TOKEN_CMD_ASSERT() { return getToken(SMTLIB26Parser.TOKEN_CMD_ASSERT, 0); }
		public TerminalNode TOKEN_CMD_CHECK_SAT() { return getToken(SMTLIB26Parser.TOKEN_CMD_CHECK_SAT, 0); }
		public TerminalNode TOKEN_CMD_GET_ASSERTIONS() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_ASSERTIONS, 0); }
		public TerminalNode TOKEN_CMD_GET_PROOF() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_PROOF, 0); }
		public TerminalNode TOKEN_CMD_GET_UNSAT_CORE() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_UNSAT_CORE, 0); }
		public TerminalNode TOKEN_CMD_GET_VALUE() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_VALUE, 0); }
		public TerminalNode TOKEN_CMD_GET_ASSIGNMENT() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_ASSIGNMENT, 0); }
		public TerminalNode TOKEN_CMD_GET_OPTION() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_OPTION, 0); }
		public KeywordContext keyword() {
			return getRuleContext(KeywordContext.class,0);
		}
		public TerminalNode TOKEN_CMD_GET_INFO() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_INFO, 0); }
		public Info_flagContext info_flag() {
			return getRuleContext(Info_flagContext.class,0);
		}
		public TerminalNode TOKEN_CMD_EXIT() { return getToken(SMTLIB26Parser.TOKEN_CMD_EXIT, 0); }
		public TerminalNode TOKEN_CMD_GET_MODEL() { return getToken(SMTLIB26Parser.TOKEN_CMD_GET_MODEL, 0); }
		public CommandContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_command; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterCommand(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitCommand(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitCommand(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CommandContext command() throws RecognitionException {
		CommandContext _localctx = new CommandContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_command);
		int _la;
		try {
			setState(531);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,40,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(412);
				match(OpenPar);
				setState(413);
				match(TOKEN_CMD_SET_LOGIC);
				setState(414);
				symbol();
				setState(415);
				match(ClosePar);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(417);
				match(OpenPar);
				setState(418);
				match(TOKEN_CMD_SET_OPTION);
				setState(419);
				option();
				setState(420);
				match(ClosePar);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(422);
				match(OpenPar);
				setState(423);
				match(TOKEN_CMD_SET_INFO);
				setState(424);
				attribute();
				setState(425);
				match(ClosePar);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(427);
				match(OpenPar);
				setState(428);
				match(TOKEN_CMD_DECLARE_SORT);
				setState(429);
				symbol();
				setState(430);
				match(NUMERAL);
				setState(431);
				match(ClosePar);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(433);
				match(OpenPar);
				setState(434);
				match(TOKEN_CMD_DEFINE_SORT);
				setState(435);
				symbol();
				setState(436);
				match(OpenPar);
				setState(440);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || _la==SIMPLE_SYM || _la==QUOTED_SYM) {
					{
					{
					setState(437);
					symbol();
					}
					}
					setState(442);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(443);
				match(ClosePar);
				setState(444);
				sort();
				setState(445);
				match(ClosePar);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(447);
				match(OpenPar);
				setState(448);
				match(TOKEN_CMD_DECLARE_FUN);
				setState(449);
				symbol();
				setState(450);
				match(OpenPar);
				setState(454);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 88)) & ~0x3f) == 0 && ((1L << (_la - 88)) & ((1L << (SIMPLE_SYM - 88)) | (1L << (QUOTED_SYM - 88)) | (1L << (OpenPar - 88)))) != 0)) {
					{
					{
					setState(451);
					sort();
					}
					}
					setState(456);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(457);
				match(ClosePar);
				setState(458);
				sort();
				setState(459);
				match(ClosePar);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(461);
				match(OpenPar);
				setState(462);
				match(TOKEN_CMD_DEFINE_FUN);
				setState(463);
				symbol();
				setState(464);
				match(OpenPar);
				setState(468);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==OpenPar) {
					{
					{
					setState(465);
					sorted_var();
					}
					}
					setState(470);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(471);
				match(ClosePar);
				setState(472);
				sort();
				setState(473);
				term();
				setState(474);
				match(ClosePar);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(476);
				match(OpenPar);
				setState(477);
				match(TOKEN_CMD_PUSH);
				setState(478);
				match(NUMERAL);
				setState(479);
				match(ClosePar);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(480);
				match(OpenPar);
				setState(481);
				match(TOKEN_CMD_POP);
				setState(482);
				match(NUMERAL);
				setState(483);
				match(ClosePar);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(484);
				match(OpenPar);
				setState(485);
				match(TOKEN_CMD_ASSERT);
				setState(486);
				term();
				setState(487);
				match(ClosePar);
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(489);
				match(OpenPar);
				setState(490);
				match(TOKEN_CMD_CHECK_SAT);
				setState(491);
				match(ClosePar);
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(492);
				match(OpenPar);
				setState(493);
				match(TOKEN_CMD_GET_ASSERTIONS);
				setState(494);
				match(ClosePar);
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(495);
				match(OpenPar);
				setState(496);
				match(TOKEN_CMD_GET_PROOF);
				setState(497);
				match(ClosePar);
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(498);
				match(OpenPar);
				setState(499);
				match(TOKEN_CMD_GET_UNSAT_CORE);
				setState(500);
				match(ClosePar);
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(501);
				match(OpenPar);
				setState(502);
				match(TOKEN_CMD_GET_VALUE);
				setState(503);
				match(OpenPar);
				setState(505); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(504);
					term();
					}
					}
					setState(507); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (NUMERAL - 82)) | (1L << (DECIMAL - 82)) | (1L << (HEXADECIMAL - 82)) | (1L << (BINARY - 82)) | (1L << (STRING - 82)) | (1L << (SIMPLE_SYM - 82)) | (1L << (QUOTED_SYM - 82)) | (1L << (OpenPar - 82)))) != 0) );
				setState(509);
				match(ClosePar);
				setState(510);
				match(ClosePar);
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 16);
				{
				setState(512);
				match(OpenPar);
				setState(513);
				match(TOKEN_CMD_GET_ASSIGNMENT);
				setState(514);
				match(ClosePar);
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 17);
				{
				setState(515);
				match(OpenPar);
				setState(516);
				match(TOKEN_CMD_GET_OPTION);
				setState(517);
				keyword();
				setState(518);
				match(ClosePar);
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 18);
				{
				setState(520);
				match(OpenPar);
				setState(521);
				match(TOKEN_CMD_GET_INFO);
				setState(522);
				info_flag();
				setState(523);
				match(ClosePar);
				}
				break;
			case 19:
				enterOuterAlt(_localctx, 19);
				{
				setState(525);
				match(OpenPar);
				setState(526);
				match(TOKEN_CMD_EXIT);
				setState(527);
				match(ClosePar);
				}
				break;
			case 20:
				enterOuterAlt(_localctx, 20);
				{
				setState(528);
				match(OpenPar);
				setState(529);
				match(TOKEN_CMD_GET_MODEL);
				setState(530);
				match(ClosePar);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ScriptContext extends ParserRuleContext {
		public List<CommandContext> command() {
			return getRuleContexts(CommandContext.class);
		}
		public CommandContext command(int i) {
			return getRuleContext(CommandContext.class,i);
		}
		public ScriptContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_script; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterScript(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitScript(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitScript(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ScriptContext script() throws RecognitionException {
		ScriptContext _localctx = new ScriptContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_script);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(534); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(533);
				command();
				}
				}
				setState(536); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==OpenPar );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Gen_responseContext extends ParserRuleContext {
		public TerminalNode SYM_UNSUPPORTED() { return getToken(SMTLIB26Parser.SYM_UNSUPPORTED, 0); }
		public TerminalNode SYM_SUCCESS() { return getToken(SMTLIB26Parser.SYM_SUCCESS, 0); }
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode SYM_ERROR() { return getToken(SMTLIB26Parser.SYM_ERROR, 0); }
		public TerminalNode STRING() { return getToken(SMTLIB26Parser.STRING, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public Gen_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_gen_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGen_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGen_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGen_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Gen_responseContext gen_response() throws RecognitionException {
		Gen_responseContext _localctx = new Gen_responseContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_gen_response);
		try {
			setState(544);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYM_UNSUPPORTED:
				enterOuterAlt(_localctx, 1);
				{
				setState(538);
				match(SYM_UNSUPPORTED);
				}
				break;
			case SYM_SUCCESS:
				enterOuterAlt(_localctx, 2);
				{
				setState(539);
				match(SYM_SUCCESS);
				}
				break;
			case OpenPar:
				enterOuterAlt(_localctx, 3);
				{
				setState(540);
				match(OpenPar);
				setState(541);
				match(SYM_ERROR);
				setState(542);
				match(STRING);
				setState(543);
				match(ClosePar);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Error_behaviorContext extends ParserRuleContext {
		public TerminalNode SYM_IMMEDIATE_EXIT() { return getToken(SMTLIB26Parser.SYM_IMMEDIATE_EXIT, 0); }
		public TerminalNode SYM_CONTINUED_EXECUTION() { return getToken(SMTLIB26Parser.SYM_CONTINUED_EXECUTION, 0); }
		public Error_behaviorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_error_behavior; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterError_behavior(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitError_behavior(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitError_behavior(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Error_behaviorContext error_behavior() throws RecognitionException {
		Error_behaviorContext _localctx = new Error_behaviorContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_error_behavior);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(546);
			_la = _input.LA(1);
			if ( !(_la==SYM_CONTINUED_EXECUTION || _la==SYM_IMMEDIATE_EXIT) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Reason_unknownContext extends ParserRuleContext {
		public TerminalNode SYM_MEMOUT() { return getToken(SMTLIB26Parser.SYM_MEMOUT, 0); }
		public TerminalNode SYM_INCOMPLETE() { return getToken(SMTLIB26Parser.SYM_INCOMPLETE, 0); }
		public Reason_unknownContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_reason_unknown; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterReason_unknown(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitReason_unknown(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitReason_unknown(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Reason_unknownContext reason_unknown() throws RecognitionException {
		Reason_unknownContext _localctx = new Reason_unknownContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_reason_unknown);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(548);
			_la = _input.LA(1);
			if ( !(_la==SYM_INCOMPLETE || _la==SYM_MEMOUT) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatusContext extends ParserRuleContext {
		public TerminalNode SYM_SAT() { return getToken(SMTLIB26Parser.SYM_SAT, 0); }
		public TerminalNode SYM_UNSAT() { return getToken(SMTLIB26Parser.SYM_UNSAT, 0); }
		public TerminalNode SYM_UNKNOWN() { return getToken(SMTLIB26Parser.SYM_UNKNOWN, 0); }
		public StatusContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_status; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterStatus(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitStatus(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitStatus(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatusContext status() throws RecognitionException {
		StatusContext _localctx = new StatusContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_status);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(550);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_SAT) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Info_responseContext extends ParserRuleContext {
		public TerminalNode KEYWORD_ERROR_BEHAVIOR() { return getToken(SMTLIB26Parser.KEYWORD_ERROR_BEHAVIOR, 0); }
		public Error_behaviorContext error_behavior() {
			return getRuleContext(Error_behaviorContext.class,0);
		}
		public TerminalNode KEYWORD_NAME() { return getToken(SMTLIB26Parser.KEYWORD_NAME, 0); }
		public TerminalNode STRING() { return getToken(SMTLIB26Parser.STRING, 0); }
		public TerminalNode KEYWORD_AUTHORS() { return getToken(SMTLIB26Parser.KEYWORD_AUTHORS, 0); }
		public TerminalNode KEYWORD_VERSION() { return getToken(SMTLIB26Parser.KEYWORD_VERSION, 0); }
		public TerminalNode KEYWORD_REASON_UNKNOWN() { return getToken(SMTLIB26Parser.KEYWORD_REASON_UNKNOWN, 0); }
		public Reason_unknownContext reason_unknown() {
			return getRuleContext(Reason_unknownContext.class,0);
		}
		public AttributeContext attribute() {
			return getRuleContext(AttributeContext.class,0);
		}
		public Info_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_info_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterInfo_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitInfo_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitInfo_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Info_responseContext info_response() throws RecognitionException {
		Info_responseContext _localctx = new Info_responseContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_info_response);
		try {
			setState(563);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,43,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(552);
				match(KEYWORD_ERROR_BEHAVIOR);
				setState(553);
				error_behavior();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(554);
				match(KEYWORD_NAME);
				setState(555);
				match(STRING);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(556);
				match(KEYWORD_AUTHORS);
				setState(557);
				match(STRING);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(558);
				match(KEYWORD_VERSION);
				setState(559);
				match(STRING);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(560);
				match(KEYWORD_REASON_UNKNOWN);
				setState(561);
				reason_unknown();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(562);
				attribute();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_info_responseContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<Info_responseContext> info_response() {
			return getRuleContexts(Info_responseContext.class);
		}
		public Info_responseContext info_response(int i) {
			return getRuleContext(Info_responseContext.class,i);
		}
		public Get_info_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_info_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_info_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_info_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_info_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_info_responseContext get_info_response() throws RecognitionException {
		Get_info_responseContext _localctx = new Get_info_responseContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_get_info_response);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(565);
			match(OpenPar);
			setState(567); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(566);
				info_response();
				}
				}
				setState(569); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << KEYWORD_ALL_STATISTICS) | (1L << KEYWORD_AUTHORS) | (1L << KEYWORD_AXIOMS) | (1L << KEYWORD_CHAINABLE) | (1L << KEYWORD_DEFINITION) | (1L << KEYWORD_DIAGNOSTIC_OUTPUT_CHANNEL) | (1L << KEYWORD_ERROR_BEHAVIOR) | (1L << KEYWORD_EXPAND_DEFINITIONS) | (1L << KEYWORD_EXTENSIONS) | (1L << KEYWORD_FUNS) | (1L << KEYWORD_FUNS_DESCRIPTION) | (1L << KEYWORD_INTERACTIVE_MODE) | (1L << KEYWORD_LANGUAGE) | (1L << KEYWORD_LEFT_ASSOC) | (1L << KEYWORD_NAME) | (1L << KEYWORD_NAMED) | (1L << KEYWORD_NOTES) | (1L << KEYWORD_PRINT_SUCCESS) | (1L << KEYWORD_PRODUCE_ASSIGNMENTS) | (1L << KEYWORD_PRODUCE_MODELS) | (1L << KEYWORD_PRODUCE_PROOFS) | (1L << KEYWORD_PRODUCE_UNSAT_CORES) | (1L << KEYWORD_RANDOM_SEED) | (1L << KEYWORD_REASON_UNKNOWN) | (1L << KEYWORD_REGULAR_OUTPUT_CHANNEL) | (1L << KEYWORD_RIGHT_ASSOC) | (1L << KEYWORD_SORTS) | (1L << KEYWORD_SORTS_DESCRIPTION) | (1L << KEYWORD_STATUS) | (1L << KEYWORD_THEORIES) | (1L << KEYWORD_VALUES) | (1L << KEYWORD_VERBOSITY) | (1L << KEYWORD_VERSION))) != 0) || _la==KEYWORD_TOKEN );
			setState(571);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Check_sat_responseContext extends ParserRuleContext {
		public StatusContext status() {
			return getRuleContext(StatusContext.class,0);
		}
		public Check_sat_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_check_sat_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterCheck_sat_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitCheck_sat_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitCheck_sat_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Check_sat_responseContext check_sat_response() throws RecognitionException {
		Check_sat_responseContext _localctx = new Check_sat_responseContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_check_sat_response);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(573);
			status();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_assertions_responseContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public Get_assertions_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_assertions_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_assertions_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_assertions_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_assertions_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_assertions_responseContext get_assertions_response() throws RecognitionException {
		Get_assertions_responseContext _localctx = new Get_assertions_responseContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_get_assertions_response);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(575);
			match(OpenPar);
			setState(577); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(576);
				term();
				}
				}
				setState(579); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || ((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (NUMERAL - 82)) | (1L << (DECIMAL - 82)) | (1L << (HEXADECIMAL - 82)) | (1L << (BINARY - 82)) | (1L << (STRING - 82)) | (1L << (SIMPLE_SYM - 82)) | (1L << (QUOTED_SYM - 82)) | (1L << (OpenPar - 82)))) != 0) );
			setState(581);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ProofContext extends ParserRuleContext {
		public S_exprContext s_expr() {
			return getRuleContext(S_exprContext.class,0);
		}
		public ProofContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_proof; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterProof(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitProof(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitProof(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProofContext proof() throws RecognitionException {
		ProofContext _localctx = new ProofContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_proof);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(583);
			s_expr();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_proof_responseContext extends ParserRuleContext {
		public ProofContext proof() {
			return getRuleContext(ProofContext.class,0);
		}
		public Get_proof_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_proof_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_proof_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_proof_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_proof_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_proof_responseContext get_proof_response() throws RecognitionException {
		Get_proof_responseContext _localctx = new Get_proof_responseContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_get_proof_response);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(585);
			proof();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_unsat_core_responseContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<SymbolContext> symbol() {
			return getRuleContexts(SymbolContext.class);
		}
		public SymbolContext symbol(int i) {
			return getRuleContext(SymbolContext.class,i);
		}
		public Get_unsat_core_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_unsat_core_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_unsat_core_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_unsat_core_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_unsat_core_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_unsat_core_responseContext get_unsat_core_response() throws RecognitionException {
		Get_unsat_core_responseContext _localctx = new Get_unsat_core_responseContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_get_unsat_core_response);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(587);
			match(OpenPar);
			setState(589); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(588);
				symbol();
				}
				}
				setState(591); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << SYM_AND) | (1L << SYM_OR) | (1L << SYM_NOT) | (1L << SYM_BOOL) | (1L << SYM_CONTINUED_EXECUTION) | (1L << SYM_ERROR) | (1L << SYM_FALSE) | (1L << SYM_IMMEDIATE_EXIT) | (1L << SYM_INCOMPLETE) | (1L << SYM_LOGIC) | (1L << SYM_MEMOUT) | (1L << SYM_SAT) | (1L << SYM_SUCCESS) | (1L << SYM_THEORY) | (1L << SYM_TRUE) | (1L << SYM_UNKNOWN) | (1L << SYM_UNSAT) | (1L << SYM_UNSUPPORTED))) != 0) || _la==SIMPLE_SYM || _la==QUOTED_SYM );
			setState(593);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Valuation_pairContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public Valuation_pairContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_valuation_pair; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterValuation_pair(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitValuation_pair(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitValuation_pair(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Valuation_pairContext valuation_pair() throws RecognitionException {
		Valuation_pairContext _localctx = new Valuation_pairContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_valuation_pair);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(595);
			match(OpenPar);
			setState(596);
			term();
			setState(597);
			term();
			setState(598);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_value_responseContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<Valuation_pairContext> valuation_pair() {
			return getRuleContexts(Valuation_pairContext.class);
		}
		public Valuation_pairContext valuation_pair(int i) {
			return getRuleContext(Valuation_pairContext.class,i);
		}
		public Get_value_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_value_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_value_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_value_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_value_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_value_responseContext get_value_response() throws RecognitionException {
		Get_value_responseContext _localctx = new Get_value_responseContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_get_value_response);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(600);
			match(OpenPar);
			setState(602); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(601);
				valuation_pair();
				}
				}
				setState(604); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==OpenPar );
			setState(606);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class T_valuation_pairContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public SymbolContext symbol() {
			return getRuleContext(SymbolContext.class,0);
		}
		public B_valueContext b_value() {
			return getRuleContext(B_valueContext.class,0);
		}
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public T_valuation_pairContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_t_valuation_pair; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterT_valuation_pair(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitT_valuation_pair(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitT_valuation_pair(this);
			else return visitor.visitChildren(this);
		}
	}

	public final T_valuation_pairContext t_valuation_pair() throws RecognitionException {
		T_valuation_pairContext _localctx = new T_valuation_pairContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_t_valuation_pair);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(608);
			match(OpenPar);
			setState(609);
			symbol();
			setState(610);
			b_value();
			setState(611);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_assignment_responseContext extends ParserRuleContext {
		public TerminalNode OpenPar() { return getToken(SMTLIB26Parser.OpenPar, 0); }
		public TerminalNode ClosePar() { return getToken(SMTLIB26Parser.ClosePar, 0); }
		public List<T_valuation_pairContext> t_valuation_pair() {
			return getRuleContexts(T_valuation_pairContext.class);
		}
		public T_valuation_pairContext t_valuation_pair(int i) {
			return getRuleContext(T_valuation_pairContext.class,i);
		}
		public Get_assignment_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_assignment_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_assignment_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_assignment_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_assignment_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_assignment_responseContext get_assignment_response() throws RecognitionException {
		Get_assignment_responseContext _localctx = new Get_assignment_responseContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_get_assignment_response);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(613);
			match(OpenPar);
			setState(617);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==OpenPar) {
				{
				{
				setState(614);
				t_valuation_pair();
				}
				}
				setState(619);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(620);
			match(ClosePar);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Get_option_responseContext extends ParserRuleContext {
		public Attribute_valueContext attribute_value() {
			return getRuleContext(Attribute_valueContext.class,0);
		}
		public Get_option_responseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_get_option_response; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).enterGet_option_response(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof SMTLIB26ParserListener ) ((SMTLIB26ParserListener)listener).exitGet_option_response(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof SMTLIB26ParserVisitor ) return ((SMTLIB26ParserVisitor<? extends T>)visitor).visitGet_option_response(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Get_option_responseContext get_option_response() throws RecognitionException {
		Get_option_responseContext _localctx = new Get_option_responseContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_get_option_response);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(622);
			attribute_value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3_\u0273\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\3\2\3\2"+
		"\3\3\3\3\3\4\3\4\3\5\3\5\3\5\3\5\3\5\7\5`\n\5\f\5\16\5c\13\5\3\5\5\5f"+
		"\n\5\3\6\3\6\3\6\3\6\3\6\6\6m\n\6\r\6\16\6n\3\6\3\6\5\6s\n\6\3\7\3\7\3"+
		"\7\3\7\6\7y\n\7\r\7\16\7z\3\7\3\7\5\7\177\n\7\3\b\3\b\3\b\3\b\7\b\u0085"+
		"\n\b\f\b\16\b\u0088\13\b\3\b\5\b\u008b\n\b\3\t\3\t\3\t\3\t\5\t\u0091\n"+
		"\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5\n\u009a\n\n\3\13\3\13\3\13\3\13\3\13"+
		"\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\6\r\u00ab\n\r\r\r\16\r\u00ac"+
		"\3\r\3\r\3\r\3\r\3\r\3\r\6\r\u00b5\n\r\r\r\16\r\u00b6\3\r\3\r\3\r\3\r"+
		"\3\r\3\r\3\r\3\r\6\r\u00c1\n\r\r\r\16\r\u00c2\3\r\3\r\3\r\3\r\3\r\3\r"+
		"\3\r\3\r\6\r\u00cd\n\r\r\r\16\r\u00ce\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r"+
		"\6\r\u00d9\n\r\r\r\16\r\u00da\3\r\3\r\5\r\u00df\n\r\3\16\3\16\3\16\3\16"+
		"\7\16\u00e5\n\16\f\16\16\16\u00e8\13\16\3\16\3\16\3\17\3\17\3\20\3\20"+
		"\3\20\3\20\7\20\u00f2\n\20\f\20\16\20\u00f5\13\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\7\20\u00fd\n\20\f\20\16\20\u0100\13\20\3\20\3\20\3\20\3\20"+
		"\3\20\6\20\u0107\n\20\r\20\16\20\u0108\3\20\7\20\u010c\n\20\f\20\16\20"+
		"\u010f\13\20\3\20\3\20\5\20\u0113\n\20\3\21\3\21\3\21\3\21\3\21\6\21\u011a"+
		"\n\21\r\21\16\21\u011b\3\21\3\21\3\21\3\21\6\21\u0122\n\21\r\21\16\21"+
		"\u0123\3\21\7\21\u0127\n\21\f\21\16\21\u012a\13\21\3\21\3\21\3\21\5\21"+
		"\u012f\n\21\3\22\3\22\3\22\5\22\u0134\n\22\3\22\6\22\u0137\n\22\r\22\16"+
		"\22\u0138\3\22\3\22\3\23\3\23\3\23\6\23\u0140\n\23\r\23\16\23\u0141\3"+
		"\23\3\23\3\23\3\23\3\23\6\23\u0149\n\23\r\23\16\23\u014a\3\23\3\23\3\23"+
		"\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\5\23\u015a\n\23\3\24"+
		"\3\24\3\24\6\24\u015f\n\24\r\24\16\24\u0160\3\24\3\24\3\24\3\24\3\24\3"+
		"\24\3\24\3\24\3\24\3\24\3\24\5\24\u016e\n\24\3\25\3\25\3\25\3\25\6\25"+
		"\u0174\n\25\r\25\16\25\u0175\3\25\3\25\3\26\3\26\3\27\3\27\3\27\3\27\3"+
		"\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3"+
		"\27\3\27\3\27\3\27\3\27\5\27\u0193\n\27\3\30\3\30\3\30\3\30\3\30\3\30"+
		"\3\30\3\30\5\30\u019d\n\30\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\31\3\31\7\31\u01b9\n\31\f\31\16\31\u01bc\13\31\3\31\3\31\3\31"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\7\31\u01c7\n\31\f\31\16\31\u01ca\13\31"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\7\31\u01d5\n\31\f\31\16"+
		"\31\u01d8\13\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\6\31\u01fc\n\31\r\31\16"+
		"\31\u01fd\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\5\31\u0216\n\31\3\32"+
		"\6\32\u0219\n\32\r\32\16\32\u021a\3\33\3\33\3\33\3\33\3\33\3\33\5\33\u0223"+
		"\n\33\3\34\3\34\3\35\3\35\3\36\3\36\3\37\3\37\3\37\3\37\3\37\3\37\3\37"+
		"\3\37\3\37\3\37\3\37\5\37\u0236\n\37\3 \3 \6 \u023a\n \r \16 \u023b\3"+
		" \3 \3!\3!\3\"\3\"\6\"\u0244\n\"\r\"\16\"\u0245\3\"\3\"\3#\3#\3$\3$\3"+
		"%\3%\6%\u0250\n%\r%\16%\u0251\3%\3%\3&\3&\3&\3&\3&\3\'\3\'\6\'\u025d\n"+
		"\'\r\'\16\'\u025e\3\'\3\'\3(\3(\3(\3(\3(\3)\3)\7)\u026a\n)\f)\16)\u026d"+
		"\13)\3)\3)\3*\3*\3*\2\2+\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36 \"$&("+
		"*,.\60\62\64\668:<>@BDFHJLNPR\2\n\4\2\3\24Z[\4\2\25\65]]\3\2TX\5\299="+
		"=??\4\2\t\t\21\21\4\2\7\7\n\n\4\2\13\13\r\r\4\2\16\16\22\23\2\u02b4\2"+
		"T\3\2\2\2\4V\3\2\2\2\6X\3\2\2\2\be\3\2\2\2\nr\3\2\2\2\f~\3\2\2\2\16\u008a"+
		"\3\2\2\2\20\u0090\3\2\2\2\22\u0099\3\2\2\2\24\u009b\3\2\2\2\26\u00a0\3"+
		"\2\2\2\30\u00de\3\2\2\2\32\u00e0\3\2\2\2\34\u00eb\3\2\2\2\36\u0112\3\2"+
		"\2\2 \u012e\3\2\2\2\"\u0130\3\2\2\2$\u0159\3\2\2\2&\u016d\3\2\2\2(\u016f"+
		"\3\2\2\2*\u0179\3\2\2\2,\u0192\3\2\2\2.\u019c\3\2\2\2\60\u0215\3\2\2\2"+
		"\62\u0218\3\2\2\2\64\u0222\3\2\2\2\66\u0224\3\2\2\28\u0226\3\2\2\2:\u0228"+
		"\3\2\2\2<\u0235\3\2\2\2>\u0237\3\2\2\2@\u023f\3\2\2\2B\u0241\3\2\2\2D"+
		"\u0249\3\2\2\2F\u024b\3\2\2\2H\u024d\3\2\2\2J\u0255\3\2\2\2L\u025a\3\2"+
		"\2\2N\u0262\3\2\2\2P\u0267\3\2\2\2R\u0270\3\2\2\2TU\t\2\2\2U\3\3\2\2\2"+
		"VW\t\3\2\2W\5\3\2\2\2XY\t\4\2\2Y\7\3\2\2\2Zf\5\6\4\2[f\5\2\2\2\\f\5\4"+
		"\3\2]a\7^\2\2^`\5\b\5\2_^\3\2\2\2`c\3\2\2\2a_\3\2\2\2ab\3\2\2\2bd\3\2"+
		"\2\2ca\3\2\2\2df\7_\2\2eZ\3\2\2\2e[\3\2\2\2e\\\3\2\2\2e]\3\2\2\2f\t\3"+
		"\2\2\2gs\5\2\2\2hi\7^\2\2ij\7\67\2\2jl\5\2\2\2km\7T\2\2lk\3\2\2\2mn\3"+
		"\2\2\2nl\3\2\2\2no\3\2\2\2op\3\2\2\2pq\7_\2\2qs\3\2\2\2rg\3\2\2\2rh\3"+
		"\2\2\2s\13\3\2\2\2t\177\5\n\6\2uv\7^\2\2vx\5\n\6\2wy\5\f\7\2xw\3\2\2\2"+
		"yz\3\2\2\2zx\3\2\2\2z{\3\2\2\2{|\3\2\2\2|}\7_\2\2}\177\3\2\2\2~t\3\2\2"+
		"\2~u\3\2\2\2\177\r\3\2\2\2\u0080\u008b\5\2\2\2\u0081\u008b\5\6\4\2\u0082"+
		"\u0086\7^\2\2\u0083\u0085\5\b\5\2\u0084\u0083\3\2\2\2\u0085\u0088\3\2"+
		"\2\2\u0086\u0084\3\2\2\2\u0086\u0087\3\2\2\2\u0087\u0089\3\2\2\2\u0088"+
		"\u0086\3\2\2\2\u0089\u008b\7_\2\2\u008a\u0080\3\2\2\2\u008a\u0081\3\2"+
		"\2\2\u008a\u0082\3\2\2\2\u008b\17\3\2\2\2\u008c\u0091\5\4\3\2\u008d\u008e"+
		"\5\4\3\2\u008e\u008f\5\16\b\2\u008f\u0091\3\2\2\2\u0090\u008c\3\2\2\2"+
		"\u0090\u008d\3\2\2\2\u0091\21\3\2\2\2\u0092\u009a\5\n\6\2\u0093\u0094"+
		"\7^\2\2\u0094\u0095\78\2\2\u0095\u0096\5\n\6\2\u0096\u0097\5\f\7\2\u0097"+
		"\u0098\7_\2\2\u0098\u009a\3\2\2\2\u0099\u0092\3\2\2\2\u0099\u0093\3\2"+
		"\2\2\u009a\23\3\2\2\2\u009b\u009c\7^\2\2\u009c\u009d\5\2\2\2\u009d\u009e"+
		"\5\30\r\2\u009e\u009f\7_\2\2\u009f\25\3\2\2\2\u00a0\u00a1\7^\2\2\u00a1"+
		"\u00a2\5\2\2\2\u00a2\u00a3\5\f\7\2\u00a3\u00a4\7_\2\2\u00a4\27\3\2\2\2"+
		"\u00a5\u00df\5\6\4\2\u00a6\u00df\5\22\n\2\u00a7\u00a8\7^\2\2\u00a8\u00aa"+
		"\5\22\n\2\u00a9\u00ab\5\30\r\2\u00aa\u00a9\3\2\2\2\u00ab\u00ac\3\2\2\2"+
		"\u00ac\u00aa\3\2\2\2\u00ac\u00ad\3\2\2\2\u00ad\u00ae\3\2\2\2\u00ae\u00af"+
		"\7_\2\2\u00af\u00df\3\2\2\2\u00b0\u00b1\7^\2\2\u00b1\u00b2\7<\2\2\u00b2"+
		"\u00b4\7^\2\2\u00b3\u00b5\5\24\13\2\u00b4\u00b3\3\2\2\2\u00b5\u00b6\3"+
		"\2\2\2\u00b6\u00b4\3\2\2\2\u00b6\u00b7\3\2\2\2\u00b7\u00b8\3\2\2\2\u00b8"+
		"\u00b9\7_\2\2\u00b9\u00ba\5\30\r\2\u00ba\u00bb\7_\2\2\u00bb\u00df\3\2"+
		"\2\2\u00bc\u00bd\7^\2\2\u00bd\u00be\7;\2\2\u00be\u00c0\7^\2\2\u00bf\u00c1"+
		"\5\26\f\2\u00c0\u00bf\3\2\2\2\u00c1\u00c2\3\2\2\2\u00c2\u00c0\3\2\2\2"+
		"\u00c2\u00c3\3\2\2\2\u00c3\u00c4\3\2\2\2\u00c4\u00c5\7_\2\2\u00c5\u00c6"+
		"\5\30\r\2\u00c6\u00c7\7_\2\2\u00c7\u00df\3\2\2\2\u00c8\u00c9\7^\2\2\u00c9"+
		"\u00ca\7:\2\2\u00ca\u00cc\7^\2\2\u00cb\u00cd\5\26\f\2\u00cc\u00cb\3\2"+
		"\2\2\u00cd\u00ce\3\2\2\2\u00ce\u00cc\3\2\2\2\u00ce\u00cf\3\2\2\2\u00cf"+
		"\u00d0\3\2\2\2\u00d0\u00d1\7_\2\2\u00d1\u00d2\5\30\r\2\u00d2\u00d3\7_"+
		"\2\2\u00d3\u00df\3\2\2\2\u00d4\u00d5\7^\2\2\u00d5\u00d6\7\66\2\2\u00d6"+
		"\u00d8\5\30\r\2\u00d7\u00d9\5\20\t\2\u00d8\u00d7\3\2\2\2\u00d9\u00da\3"+
		"\2\2\2\u00da\u00d8\3\2\2\2\u00da\u00db\3\2\2\2\u00db\u00dc\3\2\2\2\u00dc"+
		"\u00dd\7_\2\2\u00dd\u00df\3\2\2\2\u00de\u00a5\3\2\2\2\u00de\u00a6\3\2"+
		"\2\2\u00de\u00a7\3\2\2\2\u00de\u00b0\3\2\2\2\u00de\u00bc\3\2\2\2\u00de"+
		"\u00c8\3\2\2\2\u00de\u00d4\3\2\2\2\u00df\31\3\2\2\2\u00e0\u00e1\7^\2\2"+
		"\u00e1\u00e2\5\n\6\2\u00e2\u00e6\7T\2\2\u00e3\u00e5\5\20\t\2\u00e4\u00e3"+
		"\3\2\2\2\u00e5\u00e8\3\2\2\2\u00e6\u00e4\3\2\2\2\u00e6\u00e7\3\2\2\2\u00e7"+
		"\u00e9\3\2\2\2\u00e8\u00e6\3\2\2\2\u00e9\u00ea\7_\2\2\u00ea\33\3\2\2\2"+
		"\u00eb\u00ec\t\5\2\2\u00ec\35\3\2\2\2\u00ed\u00ee\7^\2\2\u00ee\u00ef\5"+
		"\6\4\2\u00ef\u00f3\5\f\7\2\u00f0\u00f2\5\20\t\2\u00f1\u00f0\3\2\2\2\u00f2"+
		"\u00f5\3\2\2\2\u00f3\u00f1\3\2\2\2\u00f3\u00f4\3\2\2\2\u00f4\u00f6\3\2"+
		"\2\2\u00f5\u00f3\3\2\2\2\u00f6\u00f7\7_\2\2\u00f7\u0113\3\2\2\2\u00f8"+
		"\u00f9\7^\2\2\u00f9\u00fa\5\34\17\2\u00fa\u00fe\5\f\7\2\u00fb\u00fd\5"+
		"\20\t\2\u00fc\u00fb\3\2\2\2\u00fd\u0100\3\2\2\2\u00fe\u00fc\3\2\2\2\u00fe"+
		"\u00ff\3\2\2\2\u00ff\u0101\3\2\2\2\u0100\u00fe\3\2\2\2\u0101\u0102\7_"+
		"\2\2\u0102\u0113\3\2\2\2\u0103\u0104\7^\2\2\u0104\u0106\5\n\6\2\u0105"+
		"\u0107\5\f\7\2\u0106\u0105\3\2\2\2\u0107\u0108\3\2\2\2\u0108\u0106\3\2"+
		"\2\2\u0108\u0109\3\2\2\2\u0109\u010d\3\2\2\2\u010a\u010c\5\20\t\2\u010b"+
		"\u010a\3\2\2\2\u010c\u010f\3\2\2\2\u010d\u010b\3\2\2\2\u010d\u010e\3\2"+
		"\2\2\u010e\u0110\3\2\2\2\u010f\u010d\3\2\2\2\u0110\u0111\7_\2\2\u0111"+
		"\u0113\3\2\2\2\u0112\u00ed\3\2\2\2\u0112\u00f8\3\2\2\2\u0112\u0103\3\2"+
		"\2\2\u0113\37\3\2\2\2\u0114\u012f\5\36\20\2\u0115\u0116\7^\2\2\u0116\u0117"+
		"\7>\2\2\u0117\u0119\7^\2\2\u0118\u011a\5\2\2\2\u0119\u0118\3\2\2\2\u011a"+
		"\u011b\3\2\2\2\u011b\u0119\3\2\2\2\u011b\u011c\3\2\2\2\u011c\u011d\3\2"+
		"\2\2\u011d\u011e\7_\2\2\u011e\u011f\7^\2\2\u011f\u0121\5\n\6\2\u0120\u0122"+
		"\5\f\7\2\u0121\u0120\3\2\2\2\u0122\u0123\3\2\2\2\u0123\u0121\3\2\2\2\u0123"+
		"\u0124\3\2\2\2\u0124\u0128\3\2\2\2\u0125\u0127\5\20\t\2\u0126\u0125\3"+
		"\2\2\2\u0127\u012a\3\2\2\2\u0128\u0126\3\2\2\2\u0128\u0129\3\2\2\2\u0129"+
		"\u012b\3\2\2\2\u012a\u0128\3\2\2\2\u012b\u012c\7_\2\2\u012c\u012d\7_\2"+
		"\2\u012d\u012f\3\2\2\2\u012e\u0114\3\2\2\2\u012e\u0115\3\2\2\2\u012f!"+
		"\3\2\2\2\u0130\u0131\7^\2\2\u0131\u0133\7\20\2\2\u0132\u0134\5\2\2\2\u0133"+
		"\u0132\3\2\2\2\u0133\u0134\3\2\2\2\u0134\u0136\3\2\2\2\u0135\u0137\5$"+
		"\23\2\u0136\u0135\3\2\2\2\u0137\u0138\3\2\2\2\u0138\u0136\3\2\2\2\u0138"+
		"\u0139\3\2\2\2\u0139\u013a\3\2\2\2\u013a\u013b\7_\2\2\u013b#\3\2\2\2\u013c"+
		"\u013d\7/\2\2\u013d\u013f\7^\2\2\u013e\u0140\5\32\16\2\u013f\u013e\3\2"+
		"\2\2\u0140\u0141\3\2\2\2\u0141\u013f\3\2\2\2\u0141\u0142\3\2\2\2\u0142"+
		"\u0143\3\2\2\2\u0143\u0144\7_\2\2\u0144\u015a\3\2\2\2\u0145\u0146\7\36"+
		"\2\2\u0146\u0148\7^\2\2\u0147\u0149\5 \21\2\u0148\u0147\3\2\2\2\u0149"+
		"\u014a\3\2\2\2\u014a\u0148\3\2\2\2\u014a\u014b\3\2\2\2\u014b\u014c\3\2"+
		"\2\2\u014c\u014d\7_\2\2\u014d\u015a\3\2\2\2\u014e\u014f\7\60\2\2\u014f"+
		"\u015a\7X\2\2\u0150\u0151\7\37\2\2\u0151\u015a\7X\2\2\u0152\u0153\7\31"+
		"\2\2\u0153\u015a\7X\2\2\u0154\u0155\7\63\2\2\u0155\u015a\7X\2\2\u0156"+
		"\u0157\7%\2\2\u0157\u015a\7X\2\2\u0158\u015a\5\20\t\2\u0159\u013c\3\2"+
		"\2\2\u0159\u0145\3\2\2\2\u0159\u014e\3\2\2\2\u0159\u0150\3\2\2\2\u0159"+
		"\u0152\3\2\2\2\u0159\u0154\3\2\2\2\u0159\u0156\3\2\2\2\u0159\u0158\3\2"+
		"\2\2\u015a%\3\2\2\2\u015b\u015c\7\62\2\2\u015c\u015e\7^\2\2\u015d\u015f"+
		"\5\2\2\2\u015e\u015d\3\2\2\2\u015f\u0160\3\2\2\2\u0160\u015e\3\2\2\2\u0160"+
		"\u0161\3\2\2\2\u0161\u0162\3\2\2\2\u0162\u0163\7_\2\2\u0163\u016e\3\2"+
		"\2\2\u0164\u0165\7!\2\2\u0165\u016e\7X\2\2\u0166\u0167\7\35\2\2\u0167"+
		"\u016e\7X\2\2\u0168\u0169\7\63\2\2\u0169\u016e\7X\2\2\u016a\u016b\7%\2"+
		"\2\u016b\u016e\7X\2\2\u016c\u016e\5\20\t\2\u016d\u015b\3\2\2\2\u016d\u0164"+
		"\3\2\2\2\u016d\u0166\3\2\2\2\u016d\u0168\3\2\2\2\u016d\u016a\3\2\2\2\u016d"+
		"\u016c\3\2\2\2\u016e\'\3\2\2\2\u016f\u0170\7^\2\2\u0170\u0171\7\f\2\2"+
		"\u0171\u0173\5\2\2\2\u0172\u0174\5&\24\2\u0173\u0172\3\2\2\2\u0174\u0175"+
		"\3\2\2\2\u0175\u0173\3\2\2\2\u0175\u0176\3\2\2\2\u0176\u0177\3\2\2\2\u0177"+
		"\u0178\7_\2\2\u0178)\3\2\2\2\u0179\u017a\t\6\2\2\u017a+\3\2\2\2\u017b"+
		"\u017c\7&\2\2\u017c\u0193\5*\26\2\u017d\u017e\7\34\2\2\u017e\u0193\5*"+
		"\26\2\u017f\u0180\7 \2\2\u0180\u0193\5*\26\2\u0181\u0182\7)\2\2\u0182"+
		"\u0193\5*\26\2\u0183\u0184\7*\2\2\u0184\u0193\5*\26\2\u0185\u0186\7(\2"+
		"\2\u0186\u0193\5*\26\2\u0187\u0188\7\'\2\2\u0188\u0193\5*\26\2\u0189\u018a"+
		"\7-\2\2\u018a\u0193\7X\2\2\u018b\u018c\7\32\2\2\u018c\u0193\7X\2\2\u018d"+
		"\u018e\7+\2\2\u018e\u0193\7T\2\2\u018f\u0190\7\64\2\2\u0190\u0193\7T\2"+
		"\2\u0191\u0193\5\20\t\2\u0192\u017b\3\2\2\2\u0192\u017d\3\2\2\2\u0192"+
		"\u017f\3\2\2\2\u0192\u0181\3\2\2\2\u0192\u0183\3\2\2\2\u0192\u0185\3\2"+
		"\2\2\u0192\u0187\3\2\2\2\u0192\u0189\3\2\2\2\u0192\u018b\3\2\2\2\u0192"+
		"\u018d\3\2\2\2\u0192\u018f\3\2\2\2\u0192\u0191\3\2\2\2\u0193-\3\2\2\2"+
		"\u0194\u019d\7\33\2\2\u0195\u019d\7#\2\2\u0196\u019d\7\26\2\2\u0197\u019d"+
		"\7\65\2\2\u0198\u019d\7\61\2\2\u0199\u019d\7,\2\2\u019a\u019d\5\4\3\2"+
		"\u019b\u019d\7\25\2\2\u019c\u0194\3\2\2\2\u019c\u0195\3\2\2\2\u019c\u0196"+
		"\3\2\2\2\u019c\u0197\3\2\2\2\u019c\u0198\3\2\2\2\u019c\u0199\3\2\2\2\u019c"+
		"\u019a\3\2\2\2\u019c\u019b\3\2\2\2\u019d/\3\2\2\2\u019e\u019f\7^\2\2\u019f"+
		"\u01a0\7P\2\2\u01a0\u01a1\5\2\2\2\u01a1\u01a2\7_\2\2\u01a2\u0216\3\2\2"+
		"\2\u01a3\u01a4\7^\2\2\u01a4\u01a5\7R\2\2\u01a5\u01a6\5,\27\2\u01a6\u01a7"+
		"\7_\2\2\u01a7\u0216\3\2\2\2\u01a8\u01a9\7^\2\2\u01a9\u01aa\7Q\2\2\u01aa"+
		"\u01ab\5\20\t\2\u01ab\u01ac\7_\2\2\u01ac\u0216\3\2\2\2\u01ad\u01ae\7^"+
		"\2\2\u01ae\u01af\7B\2\2\u01af\u01b0\5\2\2\2\u01b0\u01b1\7T\2\2\u01b1\u01b2"+
		"\7_\2\2\u01b2\u0216\3\2\2\2\u01b3\u01b4\7^\2\2\u01b4\u01b5\7D\2\2\u01b5"+
		"\u01b6\5\2\2\2\u01b6\u01ba\7^\2\2\u01b7\u01b9\5\2\2\2\u01b8\u01b7\3\2"+
		"\2\2\u01b9\u01bc\3\2\2\2\u01ba\u01b8\3\2\2\2\u01ba\u01bb\3\2\2\2\u01bb"+
		"\u01bd\3\2\2\2\u01bc\u01ba\3\2\2\2\u01bd\u01be\7_\2\2\u01be\u01bf\5\f"+
		"\7\2\u01bf\u01c0\7_\2\2\u01c0\u0216\3\2\2\2\u01c1\u01c2\7^\2\2\u01c2\u01c3"+
		"\7C\2\2\u01c3\u01c4\5\2\2\2\u01c4\u01c8\7^\2\2\u01c5\u01c7\5\f\7\2\u01c6"+
		"\u01c5\3\2\2\2\u01c7\u01ca\3\2\2\2\u01c8\u01c6\3\2\2\2\u01c8\u01c9\3\2"+
		"\2\2\u01c9\u01cb\3\2\2\2\u01ca\u01c8\3\2\2\2\u01cb\u01cc\7_\2\2\u01cc"+
		"\u01cd\5\f\7\2\u01cd\u01ce\7_\2\2\u01ce\u0216\3\2\2\2\u01cf\u01d0\7^\2"+
		"\2\u01d0\u01d1\7E\2\2\u01d1\u01d2\5\2\2\2\u01d2\u01d6\7^\2\2\u01d3\u01d5"+
		"\5\26\f\2\u01d4\u01d3\3\2\2\2\u01d5\u01d8\3\2\2\2\u01d6\u01d4\3\2\2\2"+
		"\u01d6\u01d7\3\2\2\2\u01d7\u01d9\3\2\2\2\u01d8\u01d6\3\2\2\2\u01d9\u01da"+
		"\7_\2\2\u01da\u01db\5\f\7\2\u01db\u01dc\5\30\r\2\u01dc\u01dd\7_\2\2\u01dd"+
		"\u0216\3\2\2\2\u01de\u01df\7^\2\2\u01df\u01e0\7O\2\2\u01e0\u01e1\7T\2"+
		"\2\u01e1\u0216\7_\2\2\u01e2\u01e3\7^\2\2\u01e3\u01e4\7N\2\2\u01e4\u01e5"+
		"\7T\2\2\u01e5\u0216\7_\2\2\u01e6\u01e7\7^\2\2\u01e7\u01e8\7@\2\2\u01e8"+
		"\u01e9\5\30\r\2\u01e9\u01ea\7_\2\2\u01ea\u0216\3\2\2\2\u01eb\u01ec\7^"+
		"\2\2\u01ec\u01ed\7A\2\2\u01ed\u0216\7_\2\2\u01ee\u01ef\7^\2\2\u01ef\u01f0"+
		"\7G\2\2\u01f0\u0216\7_\2\2\u01f1\u01f2\7^\2\2\u01f2\u01f3\7K\2\2\u01f3"+
		"\u0216\7_\2\2\u01f4\u01f5\7^\2\2\u01f5\u01f6\7L\2\2\u01f6\u0216\7_\2\2"+
		"\u01f7\u01f8\7^\2\2\u01f8\u01f9\7M\2\2\u01f9\u01fb\7^\2\2\u01fa\u01fc"+
		"\5\30\r\2\u01fb\u01fa\3\2\2\2\u01fc\u01fd\3\2\2\2\u01fd\u01fb\3\2\2\2"+
		"\u01fd\u01fe\3\2\2\2\u01fe\u01ff\3\2\2\2\u01ff\u0200\7_\2\2\u0200\u0201"+
		"\7_\2\2\u0201\u0216\3\2\2\2\u0202\u0203\7^\2\2\u0203\u0204\7H\2\2\u0204"+
		"\u0216\7_\2\2\u0205\u0206\7^\2\2\u0206\u0207\7J\2\2\u0207\u0208\5\4\3"+
		"\2\u0208\u0209\7_\2\2\u0209\u0216\3\2\2\2\u020a\u020b\7^\2\2\u020b\u020c"+
		"\7I\2\2\u020c\u020d\5.\30\2\u020d\u020e\7_\2\2\u020e\u0216\3\2\2\2\u020f"+
		"\u0210\7^\2\2\u0210\u0211\7F\2\2\u0211\u0216\7_\2\2\u0212\u0213\7^\2\2"+
		"\u0213\u0214\7S\2\2\u0214\u0216\7_\2\2\u0215\u019e\3\2\2\2\u0215\u01a3"+
		"\3\2\2\2\u0215\u01a8\3\2\2\2\u0215\u01ad\3\2\2\2\u0215\u01b3\3\2\2\2\u0215"+
		"\u01c1\3\2\2\2\u0215\u01cf\3\2\2\2\u0215\u01de\3\2\2\2\u0215\u01e2\3\2"+
		"\2\2\u0215\u01e6\3\2\2\2\u0215\u01eb\3\2\2\2\u0215\u01ee\3\2\2\2\u0215"+
		"\u01f1\3\2\2\2\u0215\u01f4\3\2\2\2\u0215\u01f7\3\2\2\2\u0215\u0202\3\2"+
		"\2\2\u0215\u0205\3\2\2\2\u0215\u020a\3\2\2\2\u0215\u020f\3\2\2\2\u0215"+
		"\u0212\3\2\2\2\u0216\61\3\2\2\2\u0217\u0219\5\60\31\2\u0218\u0217\3\2"+
		"\2\2\u0219\u021a\3\2\2\2\u021a\u0218\3\2\2\2\u021a\u021b\3\2\2\2\u021b"+
		"\63\3\2\2\2\u021c\u0223\7\24\2\2\u021d\u0223\7\17\2\2\u021e\u021f\7^\2"+
		"\2\u021f\u0220\7\b\2\2\u0220\u0221\7X\2\2\u0221\u0223\7_\2\2\u0222\u021c"+
		"\3\2\2\2\u0222\u021d\3\2\2\2\u0222\u021e\3\2\2\2\u0223\65\3\2\2\2\u0224"+
		"\u0225\t\7\2\2\u0225\67\3\2\2\2\u0226\u0227\t\b\2\2\u02279\3\2\2\2\u0228"+
		"\u0229\t\t\2\2\u0229;\3\2\2\2\u022a\u022b\7\33\2\2\u022b\u0236\5\66\34"+
		"\2\u022c\u022d\7#\2\2\u022d\u0236\7X\2\2\u022e\u022f\7\26\2\2\u022f\u0236"+
		"\7X\2\2\u0230\u0231\7\65\2\2\u0231\u0236\7X\2\2\u0232\u0233\7,\2\2\u0233"+
		"\u0236\58\35\2\u0234\u0236\5\20\t\2\u0235\u022a\3\2\2\2\u0235\u022c\3"+
		"\2\2\2\u0235\u022e\3\2\2\2\u0235\u0230\3\2\2\2\u0235\u0232\3\2\2\2\u0235"+
		"\u0234\3\2\2\2\u0236=\3\2\2\2\u0237\u0239\7^\2\2\u0238\u023a\5<\37\2\u0239"+
		"\u0238\3\2\2\2\u023a\u023b\3\2\2\2\u023b\u0239\3\2\2\2\u023b\u023c\3\2"+
		"\2\2\u023c\u023d\3\2\2\2\u023d\u023e\7_\2\2\u023e?\3\2\2\2\u023f\u0240"+
		"\5:\36\2\u0240A\3\2\2\2\u0241\u0243\7^\2\2\u0242\u0244\5\30\r\2\u0243"+
		"\u0242\3\2\2\2\u0244\u0245\3\2\2\2\u0245\u0243\3\2\2\2\u0245\u0246\3\2"+
		"\2\2\u0246\u0247\3\2\2\2\u0247\u0248\7_\2\2\u0248C\3\2\2\2\u0249\u024a"+
		"\5\b\5\2\u024aE\3\2\2\2\u024b\u024c\5D#\2\u024cG\3\2\2\2\u024d\u024f\7"+
		"^\2\2\u024e\u0250\5\2\2\2\u024f\u024e\3\2\2\2\u0250\u0251\3\2\2\2\u0251"+
		"\u024f\3\2\2\2\u0251\u0252\3\2\2\2\u0252\u0253\3\2\2\2\u0253\u0254\7_"+
		"\2\2\u0254I\3\2\2\2\u0255\u0256\7^\2\2\u0256\u0257\5\30\r\2\u0257\u0258"+
		"\5\30\r\2\u0258\u0259\7_\2\2\u0259K\3\2\2\2\u025a\u025c\7^\2\2\u025b\u025d"+
		"\5J&\2\u025c\u025b\3\2\2\2\u025d\u025e\3\2\2\2\u025e\u025c\3\2\2\2\u025e"+
		"\u025f\3\2\2\2\u025f\u0260\3\2\2\2\u0260\u0261\7_\2\2\u0261M\3\2\2\2\u0262"+
		"\u0263\7^\2\2\u0263\u0264\5\2\2\2\u0264\u0265\5*\26\2\u0265\u0266\7_\2"+
		"\2\u0266O\3\2\2\2\u0267\u026b\7^\2\2\u0268\u026a\5N(\2\u0269\u0268\3\2"+
		"\2\2\u026a\u026d\3\2\2\2\u026b\u0269\3\2\2\2\u026b\u026c\3\2\2\2\u026c"+
		"\u026e\3\2\2\2\u026d\u026b\3\2\2\2\u026e\u026f\7_\2\2\u026fQ\3\2\2\2\u0270"+
		"\u0271\5\16\b\2\u0271S\3\2\2\2\63aenrz~\u0086\u008a\u0090\u0099\u00ac"+
		"\u00b6\u00c2\u00ce\u00da\u00de\u00e6\u00f3\u00fe\u0108\u010d\u0112\u011b"+
		"\u0123\u0128\u012e\u0133\u0138\u0141\u014a\u0159\u0160\u016d\u0175\u0192"+
		"\u019c\u01ba\u01c8\u01d6\u01fd\u0215\u021a\u0222\u0235\u023b\u0245\u0251"+
		"\u025e\u026b";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}