#pragma once



enum TokenType {//��� ������������� ������, �������� ����� ���� ���-�� ����� ��� ����-�� �� �������
        NUMBER,
        HEX_NUMBER,
        WORD,
        TEXT,
		VAR,

        // keyword
        PRINT,
        IF,
        ELSE,
        WHILE,
        FOR,
        DO,
        BREAK,
        CONTINUE,
        DEF,
        RETURN,
        CLASS,
        NEW,
		IN,
		RANGE,

		DOUBLE_QUOTE, //"
		QUOTE, //'

        PLUS, // +
        MINUS, // -
        STAR, // *
        SLASH, // /
        PERCENT,// %
            

        EQ, // =
        EQEQ, // ==
        EXCL, // !
        EXCLEQ, // !=
        LTEQ, // <=
        LT, // <
        GT, // >
        GTEQ, // >=

        PLUSEQ, // +=
        MINUSEQ, // -=
        STAREQ, // *=
        SLASHEQ, // /=
        PERCENTEQ, // %=
           
        AMPEQ, // &=
        CARETEQ, // ^=
        BAREQ, // |=
        COLONCOLONEQ, // ::=
        LTLTEQ, // <<=
        GTGTEQ, // >>=
        GTGTGTEQ, // >>>=

        PLUSPLUS, // ++
        MINUSMINUS, // --

        LTLT, // <<
        GTGT, // >>
        GTGTGT, // >>>

        DOTDOT, // ..
        STARSTAR, // **
        QUESTIONCOLON, // ?:
        QUESTIONQUESTION, // ??

        TILDE, // ~
        CARET, // ^
        CARETCARET, // ^^
        BAR, // |
        BARBAR, // ||
        AMP, // &
        AMPAMP, // &&

        QUESTION, // ?
        COLON, // :
        COLONCOLON, // ::

        LPAREN, // (
        RPAREN, // )
        LBRACKET, // [
        RBRACKET, // ]
        LBRACE, // {
        RBRACE, // }
        COMMA, // ,
        DOT, // .

		EOL, // \n

		BEGIN, //""
		END, //""

        EOFT //���-�� ���� define EOF (-1), ������� EOFT
    };