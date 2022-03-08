// Generated from \\wsl$\Ubuntu\home\tyefen\pld-comp\compiler\ifcc.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, B_PRIO_3=9, 
		BU_PRIO_2_4=10, B_PRIO_5=11, B_PRIO_6=12, B_PRIO_7=13, B_PRIO_8=14, B_PRIO_9=15, 
		B_PRIO_10=16, B_PRIO_11=17, B_PRIO_12=18, B_PRIO_14=19, RETURN=20, TYPE=21, 
		IDENTIFIER=22, CONST=23, COMMENT=24, DIRECTIVE=25, WS=26;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "B_PRIO_3", 
			"BU_PRIO_2_4", "B_PRIO_5", "B_PRIO_6", "B_PRIO_7", "B_PRIO_8", "B_PRIO_9", 
			"B_PRIO_10", "B_PRIO_11", "B_PRIO_12", "B_PRIO_14", "RETURN", "TYPE", 
			"IDENTIFIER", "CONST", "COMMENT", "DIRECTIVE", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'main'", "'('", "')'", "'{'", "';'", "'}'", "'?'", "':'", null, 
			null, null, null, null, "'&'", "'^'", "'|'", "'&&'", "'||'", "'='", "'return'", 
			"'int'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, "B_PRIO_3", "BU_PRIO_2_4", 
			"B_PRIO_5", "B_PRIO_6", "B_PRIO_7", "B_PRIO_8", "B_PRIO_9", "B_PRIO_10", 
			"B_PRIO_11", "B_PRIO_12", "B_PRIO_14", "RETURN", "TYPE", "IDENTIFIER", 
			"CONST", "COMMENT", "DIRECTIVE", "WS"
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


	public ifccLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\34\u00a3\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5"+
		"\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\f\3\f\3\f\3\f\5\f"+
		"S\n\f\3\r\3\r\3\r\3\r\3\r\5\rZ\n\r\3\16\3\16\3\16\3\16\5\16`\n\16\3\17"+
		"\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\22\3\23\3\23\3\23\3\24\3\24\3\25"+
		"\3\25\3\25\3\25\3\25\3\25\3\25\3\26\3\26\3\26\3\26\3\27\3\27\7\27}\n\27"+
		"\f\27\16\27\u0080\13\27\3\30\6\30\u0083\n\30\r\30\16\30\u0084\3\31\3\31"+
		"\3\31\3\31\7\31\u008b\n\31\f\31\16\31\u008e\13\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\32\3\32\7\32\u0097\n\32\f\32\16\32\u009a\13\32\3\32\3\32\3\32"+
		"\3\32\3\33\3\33\3\33\3\33\4\u008c\u0098\2\34\3\3\5\4\7\5\t\6\13\7\r\b"+
		"\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26"+
		"+\27-\30/\31\61\32\63\33\65\34\3\2\t\5\2\'\',,\61\61\4\2--//\4\2>>@@\5"+
		"\2C\\aac|\6\2\62;C\\aac|\3\2\62;\5\2\13\f\17\17\"\"\2\u00aa\2\3\3\2\2"+
		"\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3"+
		"\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2"+
		"\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2"+
		"\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2"+
		"\2\2\2\63\3\2\2\2\2\65\3\2\2\2\3\67\3\2\2\2\5<\3\2\2\2\7>\3\2\2\2\t@\3"+
		"\2\2\2\13B\3\2\2\2\rD\3\2\2\2\17F\3\2\2\2\21H\3\2\2\2\23J\3\2\2\2\25L"+
		"\3\2\2\2\27R\3\2\2\2\31Y\3\2\2\2\33_\3\2\2\2\35a\3\2\2\2\37c\3\2\2\2!"+
		"e\3\2\2\2#g\3\2\2\2%j\3\2\2\2\'m\3\2\2\2)o\3\2\2\2+v\3\2\2\2-z\3\2\2\2"+
		"/\u0082\3\2\2\2\61\u0086\3\2\2\2\63\u0094\3\2\2\2\65\u009f\3\2\2\2\67"+
		"8\7o\2\289\7c\2\29:\7k\2\2:;\7p\2\2;\4\3\2\2\2<=\7*\2\2=\6\3\2\2\2>?\7"+
		"+\2\2?\b\3\2\2\2@A\7}\2\2A\n\3\2\2\2BC\7=\2\2C\f\3\2\2\2DE\7\177\2\2E"+
		"\16\3\2\2\2FG\7A\2\2G\20\3\2\2\2HI\7<\2\2I\22\3\2\2\2JK\t\2\2\2K\24\3"+
		"\2\2\2LM\t\3\2\2M\26\3\2\2\2NO\7>\2\2OS\7>\2\2PQ\7@\2\2QS\7@\2\2RN\3\2"+
		"\2\2RP\3\2\2\2S\30\3\2\2\2TZ\t\4\2\2UV\7>\2\2VZ\7?\2\2WX\7@\2\2XZ\7?\2"+
		"\2YT\3\2\2\2YU\3\2\2\2YW\3\2\2\2Z\32\3\2\2\2[\\\7?\2\2\\`\7?\2\2]^\7#"+
		"\2\2^`\7?\2\2_[\3\2\2\2_]\3\2\2\2`\34\3\2\2\2ab\7(\2\2b\36\3\2\2\2cd\7"+
		"`\2\2d \3\2\2\2ef\7~\2\2f\"\3\2\2\2gh\7(\2\2hi\7(\2\2i$\3\2\2\2jk\7~\2"+
		"\2kl\7~\2\2l&\3\2\2\2mn\7?\2\2n(\3\2\2\2op\7t\2\2pq\7g\2\2qr\7v\2\2rs"+
		"\7w\2\2st\7t\2\2tu\7p\2\2u*\3\2\2\2vw\7k\2\2wx\7p\2\2xy\7v\2\2y,\3\2\2"+
		"\2z~\t\5\2\2{}\t\6\2\2|{\3\2\2\2}\u0080\3\2\2\2~|\3\2\2\2~\177\3\2\2\2"+
		"\177.\3\2\2\2\u0080~\3\2\2\2\u0081\u0083\t\7\2\2\u0082\u0081\3\2\2\2\u0083"+
		"\u0084\3\2\2\2\u0084\u0082\3\2\2\2\u0084\u0085\3\2\2\2\u0085\60\3\2\2"+
		"\2\u0086\u0087\7\61\2\2\u0087\u0088\7,\2\2\u0088\u008c\3\2\2\2\u0089\u008b"+
		"\13\2\2\2\u008a\u0089\3\2\2\2\u008b\u008e\3\2\2\2\u008c\u008d\3\2\2\2"+
		"\u008c\u008a\3\2\2\2\u008d\u008f\3\2\2\2\u008e\u008c\3\2\2\2\u008f\u0090"+
		"\7,\2\2\u0090\u0091\7\61\2\2\u0091\u0092\3\2\2\2\u0092\u0093\b\31\2\2"+
		"\u0093\62\3\2\2\2\u0094\u0098\7%\2\2\u0095\u0097\13\2\2\2\u0096\u0095"+
		"\3\2\2\2\u0097\u009a\3\2\2\2\u0098\u0099\3\2\2\2\u0098\u0096\3\2\2\2\u0099"+
		"\u009b\3\2\2\2\u009a\u0098\3\2\2\2\u009b\u009c\7\f\2\2\u009c\u009d\3\2"+
		"\2\2\u009d\u009e\b\32\2\2\u009e\64\3\2\2\2\u009f\u00a0\t\b\2\2\u00a0\u00a1"+
		"\3\2\2\2\u00a1\u00a2\b\33\3\2\u00a2\66\3\2\2\2\n\2RY_~\u0084\u008c\u0098"+
		"\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}