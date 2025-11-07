#include "pch.h"
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include "../../../CalculatorWithGUI/vendor/imguI/imgui.h"

#include "../../include/calculators/QuadraticCalculator.h"

double QuadraticCalculator::evalSimpleExpr(std::string expression)
{
    std::vector<std::string> postfix = convertInfixToPostfix(expression);
    std::stack<double> values;

    static const std::unordered_map<std::string, std::function<double(double, double)>> ops = {
        {"+", [](double a, double b) { return a + b; }},
        {"-", [](double a, double b) { return a - b; }},
        {"*", [](double a, double b) { return a * b; }},
        {"/", [](double a, double b) { return a / b; }},
        {"^", [](double a, double b) { return std::pow(a, b); }},
        {"S", [](double a, double) { return std::sqrt(a); }}
    };

    for (const auto& token : postfix)
    {
        if (token == "P")
        {
            values.push(std::round(M_PI * 1000000.0) / 1000000.0);
        }
        else if (token == "e")
        {
            values.push(std::round(M_E * 1000000.0) / 1000000.0);
        }
        else if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-'))
        {
            values.push(std::stod(token));
        }
        else
        {
            auto it = ops.find(token);
            if (it != ops.end())
            {
                if (token == "S")
                {
                    double a = values.top();
                    values.pop();
                    values.push(it->second(a, 0.0));
                }
                else
                {
                    double b = values.top();
                    values.pop();
                    double a = values.top();
                    values.pop();
                    values.push(it->second(a, b));
                }
            }
        }
    }

    return values.empty() ? 0.0 : values.top();
}

std::vector<std::string> QuadraticCalculator::convertInfixToPostfix(std::string expression)
{
    std::vector<std::string> output;
    std::stack<char> ops;
    std::string num;

    auto pushNumber = [&]()
        {
            if (!num.empty())
            {
                output.push_back(num);
                num.clear();
            }
        };

    for (size_t i = 0; i < expression.size(); ++i)
    {
        char c = expression[i];
        if (isspace(c))
        {
            continue;
        }

        if (c == 'S')
        {
            ops.push('S');
        }
        else if (isdigit(c) || c == '.' || c == 'P' || c == 'e')
        {
            num += c;
        }
        else if (c == '(')
        {
            pushNumber();
            ops.push(c);
        }
        else if (c == ')')
        {
            pushNumber();
            while (!ops.empty() && ops.top() != '(')
            {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            if (!ops.empty())
            {
                ops.pop();
            }
            if (!ops.empty() && ops.top() == 'S')
            {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
        }
        else if (BasicCalculator::isOperator(c))
        {
            pushNumber();
            while (!ops.empty() && BasicCalculator::getOperatorPrecedence(ops.top()) >= BasicCalculator::getOperatorPrecedence(c))
            {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(c);
        }
        else if (c == '-' && (i == 0 || expression[i - 1] == '(' || BasicCalculator::isOperator(expression[i - 1])))
        {
            num += c;
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

QuadraticCalculator::CalcResult QuadraticCalculator::getRoots(QuadraticValues val)
{
    roots r{ "0", "0", false };

    if (val.a == 0)
    {
        r.firstRoot = r.secondRoot = std::to_string((val.b != 0) ? -val.c / val.b : 0);
        r.isImaginary = false;
        return { r, true, "" };
    }
    else
    {
        double discriminant = val.b * val.b - 4 * val.a * val.c;
        if (discriminant >= 0)
        {
            r.firstRoot = std::to_string((-val.b + std::sqrt(discriminant)) / (2 * val.a));
            r.secondRoot = std::to_string((-val.b - std::sqrt(discriminant)) / (2 * val.a));
            r.isImaginary = false;
        }
        else
        {
            double realPart = -val.b / (2 * val.a);
            double imaginaryPart = std::sqrt(-discriminant) / (2 * val.a);
            r.firstRoot = std::to_string(realPart) + " + " + std::to_string(imaginaryPart);
            r.secondRoot = std::to_string(realPart) + " - " + std::to_string(imaginaryPart);
            r.isImaginary = true;
        }
    }

    r.firstRoot = r.firstRoot.substr(0, 255);
    r.secondRoot = r.secondRoot.substr(0, 255);

    return { r, true, "" };
}

QuadraticValues QuadraticCalculator::evaluateQuadraticExpression(std::string expression)
{
    std::string s(expression);
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == 'x' && (i == 0 || (!isdigit(s[i - 1]) && s[i - 1] != '.')))
        {
            s.insert(i, "1");
            i++;
        }
    }

    double a = 0, b = 0, c = 0;
    std::string term;
    char sign = '+';

    for (size_t i = 0; i < s.size();)
    {
        if (s[i] == '+' || s[i] == '-')
        {
            sign = s[i];
            i++;
            continue;
        }
        else
        {
            size_t start = i;
            while (i < s.size() && s[i] != '+' && s[i] != '-')
            {
                ++i;
            }

            term = s.substr(start, i - start);

            if (term.empty())
            {
                continue;
            }
            else
            {
                size_t x2Pos = term.find("x^2");
                size_t xPos = term.find('x');

                bool isX2 = x2Pos != std::string::npos;
                bool isX = !isX2 && xPos != std::string::npos;

                std::string coefStr = (xPos != std::string::npos) ? term.substr(0, xPos) : term;
                double coef = evalSimpleExpr(coefStr.empty() ? "1" : coefStr);

                if (sign == '-')
                {
                    coef *= -1;
                }
                if (isX2)
                {
                    a += coef;
                }
                else if (isX)
                {
                    b += coef;
                }
                else
                {
                    c += coef;
                }

                sign = '+';
            }
        }
    }

    return { a, b, c };
}

bool QuadraticCalculator::isQuadraticExpression(std::string expression)
{
    if (expression.find('x') != std::string::npos && expression.find("x^2") != std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QuadraticCalculator::CalcResult QuadraticCalculator::evaluateExpression(std::string expression)
{
    if (!isQuadraticExpression(expression))
    {
        return QuadraticCalculator::CalcResult{ {"NAN","NAN",false}, false, "This is not quadratic expression" };
    }

    auto values = evaluateQuadraticExpression(expression);

    return getRoots(values);
    
}
