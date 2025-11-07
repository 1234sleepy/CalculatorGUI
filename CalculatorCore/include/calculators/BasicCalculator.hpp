#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <stack>
#include <cctype>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>



class BasicCalculator
{
public:

	enum class operatorPrecedence
	{
		AdditionSubstractionPrecedence = 1,
		MultiplyDivideSqrtPrecedence = 2,
		PowPrecedence = 3,
		OtherPrecedence = 0
	};

	struct CalcResult
	{
		double value;          
		bool success;          
		std::string errorMsg;
	};

    static CalcResult evaluateExpression(std::string expression);
    static operatorPrecedence getOperatorPrecedence(char op);
	static bool isOperator(char c);

    static std::vector<std::string> convertInfixToPostfix(std::string expression);
    static CalcResult evaluatePostfixExpression(const std::vector<std::string>& postfix);

};