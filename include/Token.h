#pragma once
#include <string>
#include "TokenType.h"
#include "Variables.h"

class Token {

public:
	std::string name;
	TokenType type;

public:
	Token(const std::string& _name, TokenType _type)
	{
		name = _name;
		type = _type;
	}

	Token(const Token& a)
	{
		name = a.name;
		type = a.type;
	}

	Token()
	{
		name = "";
		type = TokenType(0);
	}
};