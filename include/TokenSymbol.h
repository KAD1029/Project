#pragma once
#include "Token.h"
#include "Variables.h"
#include <map>
#include <vector>
#include <string>





class Tokenizer {
	std::vector<Token> tokens_vec;

	std::vector<std::string> TokenSymbol{//Ёто приблительный список, возможно здесь есть что-то лишее или чего-то не хватает
		"",
		"",
		"",
		"",
		"",

		// keyword
		"print",
		"println",
		"if",
		"else",
		"while",
		"for",
		"do",
		"break",
		"continue",
		"def",
		"return",
		"class",
		"new",

		"\"",
		"'",

		"+", // +
		"-", // -
		"*", // *
		"/" , // /
		"%",// %


		"=", // =
		"==" , // ==
		"!", // !
		"!=" , // !=
		"<=" , // <=
		"<" , // <
		">", // >
		">=" , // >=

		"+=", // +=
		"-=", // -=
		"*=", // *=
		"/=", // /=
		"%=", // %=

		"&=", // &=
		"^=", // ^=
		"|=", // |=
		"::=", // ::=
		"<<=", // <<=
		">>=", // >>=
		">>>=", // >>>=

		"++", // ++
		"--", // --

		"<<" , // <<
		">>" , // >>
		">>>" , // >>>

		"..", // ..
		"**", // **
		"?:" , // ?:
		"??" , // ??

		"~", // ~
		"^", // ^
		"^^", // ^^
		"|" , // |
		"||" , // ||
		"&", // &
		"&&", // &&

		"?" , // ?
		":" , // :
		"::", // ::

		"(", // (
		")", // )
		"[", // [
		"]", // ]
		"{", // {
		"}", // }
		",", // ,
		".", // .

		"EOFT" //√де-то есть define EOF (-1), поэтому EOFT
	};

	void push_back(const std::string token, int type = -1)
	{
		if (token == "")
			return;

		if (type != -1)
		{
			tokens_vec.push_back(Token(token, TokenType(type)));
			return;
		}

		//ѕроверка на число--------
		bool f = true;
		for (int i = 0; i < token.size(); i++)
		{
			if (token[i] < '0' || token[i] > '9')
				f = false;
		}
		if (f)
		{
			tokens_vec.push_back(Token(token, TokenType(0)));
			return;
		}
		//-------------------------

		for (int i = 0; i < variables_list.size(); i++)
		{
			if (token == variables_list[i])
			{
				tokens_vec.push_back(Token(token, TokenType(4)));
				return;
			}
		}

		for (int i = 0; i <= EOFT; i++)
		{
			if (token == TokenSymbol[i])
			{
				tokens_vec.push_back(Token(token, TokenType(i)));
			}
		}
	}

	void push_back(const char token, int type = -1)
	{
		std::string tmp;
		tmp += token;

		push_back(tmp, type);
	}

public:
	std::vector<Token>& Tokenize(std::vector<std::string> string_arr)
	{
		std::string tmp;
		for (const std::string current_string : string_arr)
		{
			int status = 3;
			char sym;
			for (int i = 0; i < current_string.size(); i++)
			{
				sym = current_string[i];

				if (sym == '"')
				{
					push_back(tmp);
					tmp = "";
					push_back('"');
					i++;
					while (i < current_string.size() && current_string[i] != '"')
					{
						if (i == current_string.size())
							throw 1;
						tmp += current_string[i];
						i++;
					}
					if (i == current_string.size())
						throw 1;
					push_back(tmp, 3);
					push_back('"');
					tmp = "";
					i++;
					continue;
				}

				else if (sym == 39)//'
				{
					push_back(tmp);
					tmp = "";
					push_back(sym);
					i++;
					if (i >= current_string.size())
						throw 1;
					push_back(current_string[i], 2);
					i++;
					if (i >= current_string.size() || current_string[i] != 39)
						throw 1;
					push_back(current_string[i]);
					i++;
					continue;
				}

				if (sym == '$' || sym == '_' || (sym >= '0' && sym <= '9') || (sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || sym == ',')
				{
					if (status == 2)
					{
						push_back(tmp);
						tmp = "";
						status = 1;
					}
					else if (status == 3)
					{
						status = 1;
					}

					tmp += sym;
				}

				else if (sym == '=' || sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '(' || sym == ')' || sym == '!' || sym == '<' || sym == '>' ||
					sym == '%' || sym == '&' || sym == '^' || sym == ':' || sym == '|' || sym == '.' || sym == ',' || sym == '?' || sym == '~' || sym == '[' || sym == ']')
				{
					if (status == 1)
					{
						push_back(tmp);
						tmp = "";
						status = 2;
					}
					else if (status == 3)
						status = 2;

					tmp += sym;
				}

				else if (sym == ' ')
				{
					if (status == 3)
						continue;

					status = 3;

					push_back(tmp);
					tmp = "";
				}

				else
				{
					throw 1;
				}
			}
		}
	
		push_back(tmp);

		return tokens_vec;
	}
};