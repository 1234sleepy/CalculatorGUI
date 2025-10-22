#pragma once

#include <string>
#include <vector>


class BasicCalculator
{
public:
    static double evaluateExpression(const char expression[256]);

	enum class operatorPrecedence
	{
		AdditionSubstractionPrecedence = 1,
		MultiplyDividePrecedence = 2,
		PowPrecedence = 3,
		OtherPrecedence = 0
	};

    static operatorPrecedence getOperatorPrecedence(char op);
	static bool isOperator(char c);

private:
    static std::vector<std::string> convertInfixToPostfix(const std::string& expr);
    static double evaluatePostfixExpression(const std::vector<std::string>& postfix);
};