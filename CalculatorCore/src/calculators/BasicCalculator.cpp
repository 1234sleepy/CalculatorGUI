#include "pch.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

#include "../../include/calculators/BasicCalculator.h"

#include <stack>
#include <cctype>
#include <unordered_map>
#include <functional>



bool BasicCalculator::isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

BasicCalculator::operatorPrecedence BasicCalculator::getOperatorPrecedence(char op)
{
	if (op == '+' || op == '-')
	{
		return BasicCalculator::operatorPrecedence::AdditionSubstractionPrecedence;
	}

	if (op == '*' || op == '/')
	{
		return BasicCalculator::operatorPrecedence::MultiplyDividePrecedence;
	}

	if (op == '^')
	{
		return BasicCalculator::operatorPrecedence::PowPrecedence;
	}

	return BasicCalculator::operatorPrecedence::OtherPrecedence;
}

std::vector<std::string> BasicCalculator::convertInfixToPostfix(const std::string& expr)
{
    std::vector<std::string> output;
    std::stack<char> ops;
    std::string num = "";

    auto pushNumber = [&]()
    {
        if (!num.empty())
        {
            output.push_back(num);
            num.clear();
        }
    };

    for (size_t i = 0; i < expr.size(); ++i) 
    {
        char c = expr[i];

        if (isspace(c))
        {
            continue;
        }

        if (isdigit(c) || c == '.' || c=='P' || c=='e')
        {
            if (c == 'P')
            {
                num += std::to_string(std::round(M_PI * 1000000.0) / 1000000.0);
            }
            else if (c == 'e')
            {
                num += std::to_string(std::round(M_E * 1000000.0) / 1000000.0);
            }
            else 
            {
                num += c;
            }
        }
        else if (c == '-' && (i == 0 || expr[i - 1] == '(' || std::strchr("+-/*^", expr[i - 1])))
        {
            num += c;
        }
        else
        {
            pushNumber();

            if (c == '(')
            {
                ops.push(c);
            }
            else if (c == ')')
            {
                while (!ops.empty() && ops.top() != '(') {
                    output.push_back(std::string(1, ops.top()));
                    ops.pop();
                }
                if (!ops.empty())
                {
                    ops.pop();
                }
            }
            else if (std::strchr("+-*/^", c))
            {
                while (!ops.empty() && (
                    (getOperatorPrecedence(ops.top()) > getOperatorPrecedence(c)) ||
                    (getOperatorPrecedence(ops.top()) == getOperatorPrecedence(c) && c != '^')
                    ))
                {
                    output.push_back(std::string(1, ops.top()));
                    ops.pop();
                }
                ops.push(c);
            }
        }
    }

    pushNumber();

    while (!ops.empty())
    {
        output.push_back(std::string(1, ops.top()));
        ops.pop();
    }

    return output;
}

double BasicCalculator::evaluatePostfixExpression(const std::vector<std::string>& postfix)
{
    std::stack<double> values;

    static const std::unordered_map<std::string, std::function<double(double, double)>> ops = {
        {"+", [](double a, double b) { return a + b; }},
        {"-", [](double a, double b) { return a - b; }},
        {"*", [](double a, double b) { return a * b; }},
        {"/", [](double a, double b) { return a / b; }},
        {"^", [](double a, double b) { return std::pow(a, b); }}
    };

    for (const auto& token : postfix)
    {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-'))
        {
            values.push(std::stod(token));
        }
        else
        {
            if (values.size() < 2)
            {
                return NAN;
            }

            double b = values.top(); values.pop();
            double a = values.top(); values.pop();

            auto it = ops.find(token);
            if (it != ops.end())
            {
                double result = it->second(a, b);
                values.push(result);
            }
            else
            {
                return NAN;
            }
        }
    }

    if (values.empty())
    {
        return NAN;
    }

    return values.top();
}

double BasicCalculator::evaluateExpression(const char expression[256])
{
	std::string expr = expression;

	std::vector<std::string> postfix = convertInfixToPostfix(expr);

	return evaluatePostfixExpression(postfix);
}