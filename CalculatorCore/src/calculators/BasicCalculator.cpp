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

std::vector<std::string> BasicCalculator::convertInfixToPostfix(std::string expression)
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

    for (size_t i = 0; i < expression.length(); ++i) 
    {
        if (isspace(expression[i]))
        {
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.' || expression[i] =='P' || expression[i] =='e')
        {
            if (expression[i] == 'P')
            {
                num += std::to_string(std::round(M_PI * 1000000.0) / 1000000.0);
            }
            else if (expression[i] == 'e')
            {
                num += std::to_string(std::round(M_E * 1000000.0) / 1000000.0);
            }
            else 
            {
                num += expression[i];
            }
        }
        else if (expression[i] == '-' && (i == 0 || expression[i - 1] == '(' || std::strchr("+-/*^", expression[i - 1])))
        {
            num += expression[i];
        }
        else
        {
            pushNumber();

            if (expression[i] == '(')
            {
                ops.push(expression[i]);
            }
            else if (expression[i] == ')')
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
            else if (std::strchr("+-*/^", expression[i]))
            {
                while (!ops.empty() && (
                    (getOperatorPrecedence(ops.top()) > getOperatorPrecedence(expression[i])) ||
                    (getOperatorPrecedence(ops.top()) == getOperatorPrecedence(expression[i]) && expression[i] != '^')
                    ))
                {
                    output.push_back(std::string(1, ops.top()));
                    ops.pop();
                }
                ops.push(expression[i]);
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

BasicCalculator::CalcResult BasicCalculator::evaluatePostfixExpression(const std::vector<std::string>& postfix)
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
                return {NAN, false, "Not correct exprassion"};
            }

            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            auto it = ops.find(token);

            if (it != ops.end())
            {
                double result = it->second(a, b);

                if (std::isnan(result))
                {
                    if (b == 0)
                    {
                        return { result, false, "Division on 0" };
                    }
                    return { result, false, "NAN" };
                }
                
                if (std::isinf(result))
                {
                    if (b == 0)
                    {
                        return { result, false, "Division on 0" };
                    }
                    return { result, false, "Infinity" };
                }

                values.push(result);
            }
            else
            {
                return { NAN, false, "Not correct exprassion" };
            }
        }
    }

    if (values.empty())
    {
        return { NAN, false, "Not correct exprassion" };;
    }

	return { values.top(), true, "" };
}

BasicCalculator::CalcResult BasicCalculator::evaluateExpression(std::string expression)
{
	std::vector<std::string> postfix = convertInfixToPostfix(expression);

	return evaluatePostfixExpression(postfix);
}