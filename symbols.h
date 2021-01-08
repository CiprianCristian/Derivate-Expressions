#pragma once

#ifndef LIBRARIES_H
#include "libraries.h"
#endif

const string unaryOperators[] = { "sin" , "cos" , "tg" , "ctg" , "sqrt" , "log" };
const string binaryOperators = "+-/*^";
const char symbols[] = "()+-/*^";

bool isSymbol(char ch)
{
	for (unsigned int i = 0; i < 7; i++)
		if (ch == symbols[i])
			return 1;
	return 0;
}
int isLetter(char ch)
{
	if ('a' <= ch && ch <= 'z')
		return 1;
	if ('A' <= ch && ch <= 'Z')
		return 2;
	return 0;
}
bool isNumber(char ch)
{
	if ('0' <= ch && ch <= '9')
		return 1;
	return 0;
}

bool isUnaryOperator(string token)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (unaryOperators[i] == "log")
		{
			if (token.substr(0, unaryOperators[i].length()) == unaryOperators[i])
				return 1;
		}
		else if (token == unaryOperators[i])
			return 1;
	}
	return 0;
}
bool isBinaryOperator(string token)
{
	for (unsigned int i = 0; i < 5; i++)
		if (token[0] == binaryOperators[i])
			return 1;
	return 0;
}