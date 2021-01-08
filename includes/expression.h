#pragma once

#ifndef LIBRARIES_H
#include "libraries.h"
#endif

#include "symbols.h"

typedef vector<string> tokenVector;

void printTokens(tokenVector tokens)
{
	for (auto token : tokens)
		cout << token << " ";
	cout << endl;
}
void lowerCase(string& s)
{
	for (unsigned int i = 0; i < s.length(); i++)
		if (isLetter(s[i]) == 2)
			s[i] += 32;
}
void tokenize(tokenVector& infix, string s, unsigned int& success)
{
	infix.clear();
	lowerCase(s);
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (isSymbol(s[i]))
		{
			infix.push_back(s.substr(i, 1));
		}
		else if (isNumber(s[i]))
		{
			string token = "";
			unsigned int j = 0;
			for (j = i; j < s.length() && !isSymbol(s[j]) && !isLetter(s[j]) && s[j] != ' '; j++)
			{
				i = j;
				token += s[j];
			}
			infix.push_back(token);

			if (isLetter(s[j]))
				infix.push_back("*");
		}
		else if (isLetter(s[i]))
		{
			string token = "";
			unsigned int j = 0;
			for (j = i; j < s.length() && !isSymbol(s[j]) && (isLetter(s[j]) || isNumber(s[j])); j++)
			{
				i = j;
				token += s[j];
			}
			infix.push_back(token);
		}
	}

	success = 100;
	for (unsigned int i = 1; i < infix.size() && success; i++)
		if (isBinaryOperator(infix[i - 1]) && isBinaryOperator(infix[i]))
			success = 0;
}
void detokenize(tokenVector infix, string& s)
{
	s.clear();
	for (auto token : infix)
		s += token;
}
int getPriority(string token)
{
	if (isUnaryOperator(token)) return 4;
	if (token == "^") return 3;
	if (token == "/" || token == "*") return 2;
	if (token == "+" || token == "-") return 1;
	return 0;
}
void postfixize(tokenVector infix, tokenVector& postfix)
{
	stack<string> st;
	for (auto token : infix)
	{
		if (token == "(")
		{
			st.push(token);
			continue;
		}
		if (token == ")")
		{
			while (!st.empty() && st.top() != "(")
			{
				postfix.push_back(st.top());
				st.pop();
			}
			if (!st.empty())
			{
				st.pop();
			}
			continue;
		}

		if (getPriority(token) == 0)
		{
			postfix.push_back(token);
		}
		else
		{
			if (st.empty())
			{
				st.push(token);
			}
			else
			{
				while (!st.empty() && st.top() != "(" &&
					getPriority(token) <= getPriority(st.top()))
				{
					postfix.push_back(st.top());
					st.pop();
				}
				st.push(token);
			}
		}
	}

	while (!st.empty())
	{
		postfix.push_back(st.top());
		st.pop();
	}
}
