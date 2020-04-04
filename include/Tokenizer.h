#pragma once
#include "Token.h"
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
		"in",
		"range",

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
		"EndLine",
		"BEG",
		"END",

		"EOFT" //√де-то есть define EOF (-1), поэтому EOFT
	};

	int is_number(std::string s)
	{
		int i = 0;
		if (s[0] == '-')
			i = 1;
		int count = 0;
		for (; i < s.size(); i++)
		{
			if (s[i] == '.')
				if (count)
					return -1;
				else
				{
					count = 1;
					continue;
				}

			if (s[i] < '0' || s[i] > '9')
				return -1;
		}
		return count;
	}

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
		int f = is_number(token);
		if (f != -1)
		{
			tokens_vec.push_back(Token(token, TokenType(f)));
			return;
		}
		//-------------------------

		for (int i = 0; i <= EOFT; i++)
		{
			if (token == TokenSymbol[i])
			{
				tokens_vec.push_back(Token(token, TokenType(i)));
				return;
			}
		}
		//---------

		for (int i = 0; i < variables_list.size(); i++)
		{
			if (token == variables_list[i])
			{
				tokens_vec.push_back(Token(token, TokenType(4)));
				return;
			}
		}

		//----

		if (token[0] == '_' || (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z'))
		{
			for (int i = 0; i < token.size(); i++)
			{
				if (!(token[i] == '_' || (token[i] >= 'a' && token[i] <= 'z') || (token[i] >= 'A' && token[i] <= 'Z') || (token[i] >= '0' && token[i] <= '9')))
				{
					throw 1;
					return;
				}
			}
			tokens_vec.push_back(Token(token, TokenType(4)));
			variables_list.push_back(token);
			return;
		}
		else
		{
			throw 1;
			return;
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

		int t_count = 0;
		int t_count_tmp = 0;

		for (const std::string current_string : string_arr)
		{
			int status = 3;
			char sym;
			t_count_tmp = 0;
			for (int i = 0; i < current_string.size(); i++)
			{
				sym = current_string[i];

				if (sym == '\t')
				{
					++t_count_tmp;
					continue;
				}
				else
				{
					if (t_count_tmp > t_count)
					{
						for (int i = 0; i < t_count_tmp - t_count; i++)
						{
							push_back("BEG");
						}
					}
					else
					{
						for (int i = 0; i < t_count - t_count_tmp; i++)
						{
							push_back("END");
						}
					}
					t_count = t_count_tmp;
				}

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
					continue;
				}

				else if (sym == '\'')
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
					continue;
				}


				if (sym == '$' || sym == '_' || (sym >= '0' && sym <= '9') || (sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || sym == '.')
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

				else if (sym == '(' || sym == ')' || sym == '[' || sym == ']' || sym == '{' || sym == '}')
				{
					push_back(tmp);
					tmp = "";
					status = 2;
					push_back(sym);
				}

				else if (sym == '=' || sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '!' || sym == '<' || sym == '>' || 
					     sym == '%' || sym == '&' || sym == '^' || sym == ':' || sym == '|' || sym == '.' || sym == ',' || sym == '?' || sym == '~')

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

			push_back(tmp);
			tmp = "";

			if (tokens_vec[tokens_vec.size() - 1].name != ",")
				push_back("EndLine");

		}
		push_back(tmp);

		return tokens_vec;

	}
};