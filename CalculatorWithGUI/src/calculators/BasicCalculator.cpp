#include "../../include/calculators/BasicCalculator.h"

#include <iostream>
#include <stack>
#include <cctype>
#include <unordered_map>
#include <functional>
#include <cmath>

int BasicCalculator::getOperatorPrecedence(char op)
{
	if (op == '+' || op == '-')
	{
		return 1;
	}

	if (op == '*' || op == '/')
	{
		return 2;
	}

	if (op == '^')
	{
		return 3;
	}

	return 0;
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

        if (isdigit(c) || c == '.')
        {
            num += c;
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
				std::cerr << "Unknown operator: " << token << '\n';
				return NULL;
			}
		}
	}

	return values.top();
}

double BasicCalculator::evaluateExpression(const char expression[256])
{
	std::string expr = expression;

	std::vector<std::string> postfix = convertInfixToPostfix(expr);

	return evaluatePostfixExpression(postfix);
}