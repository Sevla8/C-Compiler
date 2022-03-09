// Generated from /home/sevla/Desktop/COMP-project/compiler/ifcc.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, EQ=9, 
		B_PRIO_3=10, BU_PRIO_2_4=11, B_PRIO_5=12, B_PRIO_6=13, B_PRIO_7=14, B_PRIO_8=15, 
		B_PRIO_9=16, B_PRIO_10=17, B_PRIO_11=18, B_PRIO_12=19, B_PRIO_14=20, RETURN=21, 
		TYPE=22, IDENTIFIER=23, CONST=24, COMMENT=25, DIRECTIVE=26, WS=27;
	public static final int
		RULE_axiom = 0, RULE_prog = 1, RULE_instruction = 2, RULE_declaration = 3, 
		RULE_expression = 4;
	private static String[] makeRuleNames() {
		return new String[] {
			"axiom", "prog", "instruction", "declaration", "expression"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'main'", "'('", "')'", "'{'", "';'", "'}'", "'?'", "':'", "'='", 
			null, null, null, null, null, "'&'", "'^'", "'|'", "'&&'", "'||'", null, 
			"'return'", "'int'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, "EQ", "B_PRIO_3", 
			"BU_PRIO_2_4", "B_PRIO_5", "B_PRIO_6", "B_PRIO_7", "B_PRIO_8", "B_PRIO_9", 
			"B_PRIO_10", "B_PRIO_11", "B_PRIO_12", "B_PRIO_14", "RETURN", "TYPE", 
			"IDENTIFIER", "CONST", "COMMENT", "DIRECTIVE", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
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
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ifccParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class AxiomContext extends ParserRuleContext {
		public ProgContext prog() {
			return getRuleContext(ProgContext.class,0);
		}
		public AxiomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_axiom; }
	}

	public final AxiomContext axiom() throws RecognitionException {
		AxiomContext _localctx = new AxiomContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_axiom);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(10);
			prog();
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

	public static class ProgContext extends ParserRuleContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode RETURN() { return getToken(ifccParser.RETURN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public List<InstructionContext> instruction() {
			return getRuleContexts(InstructionContext.class);
		}
		public InstructionContext instruction(int i) {
			return getRuleContext(InstructionContext.class,i);
		}
		public ProgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prog; }
	}

	public final ProgContext prog() throws RecognitionException {
		ProgContext _localctx = new ProgContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_prog);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(12);
			match(TYPE);
			setState(13);
			match(T__0);
			setState(14);
			match(T__1);
			setState(15);
			match(T__2);
			setState(16);
			match(T__3);
			setState(20);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << BU_PRIO_2_4) | (1L << TYPE) | (1L << IDENTIFIER) | (1L << CONST))) != 0)) {
				{
				{
				setState(17);
				instruction();
				}
				}
				setState(22);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(23);
			match(RETURN);
			setState(24);
			expression(0);
			setState(25);
			match(T__4);
			setState(26);
			match(T__5);
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

	public static class InstructionContext extends ParserRuleContext {
		public DeclarationContext declaration() {
			return getRuleContext(DeclarationContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public InstructionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_instruction; }
	}

	public final InstructionContext instruction() throws RecognitionException {
		InstructionContext _localctx = new InstructionContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_instruction);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(30);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TYPE:
				{
				setState(28);
				declaration();
				}
				break;
			case T__1:
			case BU_PRIO_2_4:
			case IDENTIFIER:
			case CONST:
				{
				setState(29);
				expression(0);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(32);
			match(T__4);
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

	public static class DeclarationContext extends ParserRuleContext {
		public TerminalNode TYPE() { return getToken(ifccParser.TYPE, 0); }
		public TerminalNode IDENTIFIER() { return getToken(ifccParser.IDENTIFIER, 0); }
		public TerminalNode EQ() { return getToken(ifccParser.EQ, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(34);
			match(TYPE);
			setState(35);
			match(IDENTIFIER);
			setState(38);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==EQ) {
				{
				setState(36);
				match(EQ);
				setState(37);
				expression(0);
				}
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

	public static class ExpressionContext extends ParserRuleContext {
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	 
		public ExpressionContext() { }
		public void copyFrom(ExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Prio9Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_9() { return getToken(ifccParser.B_PRIO_9, 0); }
		public Prio9Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio8Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_8() { return getToken(ifccParser.B_PRIO_8, 0); }
		public Prio8Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio7Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_7() { return getToken(ifccParser.B_PRIO_7, 0); }
		public Prio7Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio6Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_6() { return getToken(ifccParser.B_PRIO_6, 0); }
		public Prio6Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio10Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_10() { return getToken(ifccParser.B_PRIO_10, 0); }
		public Prio10Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio5Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_5() { return getToken(ifccParser.B_PRIO_5, 0); }
		public Prio5Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio4Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode BU_PRIO_2_4() { return getToken(ifccParser.BU_PRIO_2_4, 0); }
		public Prio4Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio3Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_3() { return getToken(ifccParser.B_PRIO_3, 0); }
		public Prio3Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio2Context extends ExpressionContext {
		public TerminalNode BU_PRIO_2_4() { return getToken(ifccParser.BU_PRIO_2_4, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Prio2Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio1Context extends ExpressionContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Prio1Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class VarvalueContext extends ExpressionContext {
		public TerminalNode IDENTIFIER() { return getToken(ifccParser.IDENTIFIER, 0); }
		public VarvalueContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio13Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public Prio13Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio14Context extends ExpressionContext {
		public TerminalNode IDENTIFIER() { return getToken(ifccParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode EQ() { return getToken(ifccParser.EQ, 0); }
		public TerminalNode B_PRIO_14() { return getToken(ifccParser.B_PRIO_14, 0); }
		public Prio14Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class ValueContext extends ExpressionContext {
		public TerminalNode CONST() { return getToken(ifccParser.CONST, 0); }
		public ValueContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio11Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_11() { return getToken(ifccParser.B_PRIO_11, 0); }
		public Prio11Context(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Prio12Context extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode B_PRIO_12() { return getToken(ifccParser.B_PRIO_12, 0); }
		public Prio12Context(ExpressionContext ctx) { copyFrom(ctx); }
	}

	public final ExpressionContext expression() throws RecognitionException {
		return expression(0);
	}

	private ExpressionContext expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpressionContext _localctx = new ExpressionContext(_ctx, _parentState);
		ExpressionContext _prevctx = _localctx;
		int _startState = 8;
		enterRecursionRule(_localctx, 8, RULE_expression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(52);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				{
				_localctx = new Prio1Context(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(41);
				match(T__1);
				setState(42);
				expression(0);
				setState(43);
				match(T__2);
				}
				break;
			case 2:
				{
				_localctx = new Prio2Context(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(45);
				match(BU_PRIO_2_4);
				setState(46);
				expression(15);
				}
				break;
			case 3:
				{
				_localctx = new Prio14Context(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(47);
				match(IDENTIFIER);
				setState(48);
				_la = _input.LA(1);
				if ( !(_la==EQ || _la==B_PRIO_14) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(49);
				expression(3);
				}
				break;
			case 4:
				{
				_localctx = new ValueContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(50);
				match(CONST);
				}
				break;
			case 5:
				{
				_localctx = new VarvalueContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(51);
				match(IDENTIFIER);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(92);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,5,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(90);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
					case 1:
						{
						_localctx = new Prio3Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(54);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(55);
						match(B_PRIO_3);
						setState(56);
						expression(15);
						}
						break;
					case 2:
						{
						_localctx = new Prio4Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(57);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(58);
						match(BU_PRIO_2_4);
						setState(59);
						expression(14);
						}
						break;
					case 3:
						{
						_localctx = new Prio5Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(60);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(61);
						match(B_PRIO_5);
						setState(62);
						expression(13);
						}
						break;
					case 4:
						{
						_localctx = new Prio6Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(63);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(64);
						match(B_PRIO_6);
						setState(65);
						expression(12);
						}
						break;
					case 5:
						{
						_localctx = new Prio7Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(66);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(67);
						match(B_PRIO_7);
						setState(68);
						expression(11);
						}
						break;
					case 6:
						{
						_localctx = new Prio8Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(69);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(70);
						match(B_PRIO_8);
						setState(71);
						expression(10);
						}
						break;
					case 7:
						{
						_localctx = new Prio9Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(72);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(73);
						match(B_PRIO_9);
						setState(74);
						expression(9);
						}
						break;
					case 8:
						{
						_localctx = new Prio10Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(75);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(76);
						match(B_PRIO_10);
						setState(77);
						expression(8);
						}
						break;
					case 9:
						{
						_localctx = new Prio11Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(78);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(79);
						match(B_PRIO_11);
						setState(80);
						expression(7);
						}
						break;
					case 10:
						{
						_localctx = new Prio12Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(81);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(82);
						match(B_PRIO_12);
						setState(83);
						expression(6);
						}
						break;
					case 11:
						{
						_localctx = new Prio13Context(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(84);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(85);
						match(T__6);
						setState(86);
						expression(0);
						setState(87);
						match(T__7);
						setState(88);
						expression(5);
						}
						break;
					}
					} 
				}
				setState(94);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,5,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 4:
			return expression_sempred((ExpressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expression_sempred(ExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 14);
		case 1:
			return precpred(_ctx, 13);
		case 2:
			return precpred(_ctx, 12);
		case 3:
			return precpred(_ctx, 11);
		case 4:
			return precpred(_ctx, 10);
		case 5:
			return precpred(_ctx, 9);
		case 6:
			return precpred(_ctx, 8);
		case 7:
			return precpred(_ctx, 7);
		case 8:
			return precpred(_ctx, 6);
		case 9:
			return precpred(_ctx, 5);
		case 10:
			return precpred(_ctx, 4);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\35b\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\7\3\25\n\3"+
		"\f\3\16\3\30\13\3\3\3\3\3\3\3\3\3\3\3\3\4\3\4\5\4!\n\4\3\4\3\4\3\5\3\5"+
		"\3\5\3\5\5\5)\n\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\5\6"+
		"\67\n\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3"+
		"\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6"+
		"\3\6\3\6\3\6\7\6]\n\6\f\6\16\6`\13\6\3\6\2\3\n\7\2\4\6\b\n\2\3\4\2\13"+
		"\13\26\26\2n\2\f\3\2\2\2\4\16\3\2\2\2\6 \3\2\2\2\b$\3\2\2\2\n\66\3\2\2"+
		"\2\f\r\5\4\3\2\r\3\3\2\2\2\16\17\7\30\2\2\17\20\7\3\2\2\20\21\7\4\2\2"+
		"\21\22\7\5\2\2\22\26\7\6\2\2\23\25\5\6\4\2\24\23\3\2\2\2\25\30\3\2\2\2"+
		"\26\24\3\2\2\2\26\27\3\2\2\2\27\31\3\2\2\2\30\26\3\2\2\2\31\32\7\27\2"+
		"\2\32\33\5\n\6\2\33\34\7\7\2\2\34\35\7\b\2\2\35\5\3\2\2\2\36!\5\b\5\2"+
		"\37!\5\n\6\2 \36\3\2\2\2 \37\3\2\2\2!\"\3\2\2\2\"#\7\7\2\2#\7\3\2\2\2"+
		"$%\7\30\2\2%(\7\31\2\2&\'\7\13\2\2\')\5\n\6\2(&\3\2\2\2()\3\2\2\2)\t\3"+
		"\2\2\2*+\b\6\1\2+,\7\4\2\2,-\5\n\6\2-.\7\5\2\2.\67\3\2\2\2/\60\7\r\2\2"+
		"\60\67\5\n\6\21\61\62\7\31\2\2\62\63\t\2\2\2\63\67\5\n\6\5\64\67\7\32"+
		"\2\2\65\67\7\31\2\2\66*\3\2\2\2\66/\3\2\2\2\66\61\3\2\2\2\66\64\3\2\2"+
		"\2\66\65\3\2\2\2\67^\3\2\2\289\f\20\2\29:\7\f\2\2:]\5\n\6\21;<\f\17\2"+
		"\2<=\7\r\2\2=]\5\n\6\20>?\f\16\2\2?@\7\16\2\2@]\5\n\6\17AB\f\r\2\2BC\7"+
		"\17\2\2C]\5\n\6\16DE\f\f\2\2EF\7\20\2\2F]\5\n\6\rGH\f\13\2\2HI\7\21\2"+
		"\2I]\5\n\6\fJK\f\n\2\2KL\7\22\2\2L]\5\n\6\13MN\f\t\2\2NO\7\23\2\2O]\5"+
		"\n\6\nPQ\f\b\2\2QR\7\24\2\2R]\5\n\6\tST\f\7\2\2TU\7\25\2\2U]\5\n\6\bV"+
		"W\f\6\2\2WX\7\t\2\2XY\5\n\6\2YZ\7\n\2\2Z[\5\n\6\7[]\3\2\2\2\\8\3\2\2\2"+
		"\\;\3\2\2\2\\>\3\2\2\2\\A\3\2\2\2\\D\3\2\2\2\\G\3\2\2\2\\J\3\2\2\2\\M"+
		"\3\2\2\2\\P\3\2\2\2\\S\3\2\2\2\\V\3\2\2\2]`\3\2\2\2^\\\3\2\2\2^_\3\2\2"+
		"\2_\13\3\2\2\2`^\3\2\2\2\b\26 (\66\\^";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}