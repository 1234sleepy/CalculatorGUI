#include "pch.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include "../../include/calculators/QuadraticCalculator.h"

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <sstream>
#include <algorithm>



double QuadraticCalculator::evalSimpleExpr(const std::string& expr)
{
    std::stack<double> values;
    std::stack<char> ops;

    auto applyOp = [&](double a, double b, char op)
        {
            switch (op)
            {
            case '+': 
                return a + b;
            case '-': 
                return a - b;
            case '*': 
                return a * b;
            case '/': 
                return (b != 0.0) ? a / b : 0.0;
            case '^': 
                return std::pow(a, b);
            default: 
                return 0.0;
            }
        };

    std::string num;

    for (size_t i = 0; i < expr.size(); ++i)
    {
        char c = expr[i];
        if (std::isspace(c))
        {
            continue;
        }

        if (std::isdigit(c) || c == '.')
        {
            num += c;
        }
        else
        {
            if (!num.empty())
            {
                values.push(std::stod(num));
                num.clear();
            }

            if (c == '(')
            {
                ops.push(c);
            }
            else if (c == ')')
            {
                while (!ops.empty() && ops.top() != '(')
                {
                    double b = values.top(); values.pop();
                    double a = values.top(); values.pop();

                    char op = ops.top(); ops.pop();

                    values.push(applyOp(a, b, op));
                }
                if (!ops.empty())
                {
                    ops.pop();
                }
            }
            else if (static_cast<bool>(BasicCalculator::getOperatorPrecedence(c)))
            {
                while (!ops.empty() && BasicCalculator::getOperatorPrecedence(ops.top()) >= BasicCalculator::getOperatorPrecedence(c))
                {
                    double b = values.top(); values.pop();
                    double a = values.top(); values.pop();

                    char op = ops.top(); ops.pop();

                    values.push(applyOp(a, b, op));
                }
                ops.push(c);
            }
        }
    }

    if (!num.empty())
    {
        values.push(std::stod(num));
    }

    while (!ops.empty())
    {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();

        char op = ops.top(); ops.pop();

        values.push(applyOp(a, b, op));
    }

    return values.empty() ? 0.0 : values.top();
}

std::vector<std::string> QuadraticCalculator::convertInfixToPostfix(const char* expr)
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

    for (size_t i = 0; expr[i] != '\0'; ++i)
    {
        char c = expr[i];
        if (std::isspace(c))
        {
            continue;
        }

        if (std::isdigit(c) || c == '.' || std::isalpha(c))
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
        }
        else if (QuadraticCalculator::isOperator(c))
        {
            pushNumber();
            while (!ops.empty() && getOperatorPrecedence(ops.top()) >= getOperatorPrecedence(c))
            {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(c);
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

QuadraticCalculator::roots QuadraticCalculator::getRoots(QuadraticValues val)
{
    roots r{ "0", "0", false};

    if (val.a == 0)
    {
        r.firstRoot = r.secondRoot = std::to_string((val.b != 0) ? -val.c / val.b : 0);

        r.isImaginary = false;

        return r;
    }

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

    r.firstRoot = r.firstRoot.substr(0, 255);
    r.secondRoot = r.secondRoot.substr(0, 255);

    return r;
}


QuadraticValues QuadraticCalculator::evaluateQuadraticExpression(const char* expr)
{
    std::string s(expr);

    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == 'x' && (i == 0 || (!std::isdigit(s[i - 1]) && s[i - 1] != '.')))
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

        size_t start = i;
        while (i < s.size() && s[i] != '+' && s[i] != '-') ++i;
        term = s.substr(start, i - start);
        if (term.empty())
        {
            continue;
        }

        bool isX2 = term.find("x^2") != std::string::npos;
        bool isX = !isX2 && term.find('x') != std::string::npos;

        size_t xPos = term.find('x');
        std::string coefStr = (xPos != std::string::npos) ? term.substr(0, xPos) : term;

        double coef = 0.0;

         coef = evalSimpleExpr(coefStr.empty() ? "1" : coefStr);

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
            c += evalSimpleExpr(coefStr) * (sign == '-' ? -1 : 1);
        }

        sign = '+';
    }

    return { a, b, c };
}

bool QuadraticCalculator::isQuadraticExpression(const char* expr)
{
    std::string expression = expr;

    bool isX = false;
    bool isPowX = false;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == 'x')
        {
            isX = true;
            if (expression[i] + 1 == '^')
            {
                isPowX = true;
            }
        }
    }

    return isX && isPowX ? true : false;
}


QuadraticCalculator::roots QuadraticCalculator::evaluateExpression(const char expression[256])
{
    if (!isQuadraticExpression(expression))
    {
        return QuadraticCalculator::roots{"NAN", "NAN", false};
    }

    auto postfix = convertInfixToPostfix(expression);

    auto values = evaluateQuadraticExpression(expression);

    return getRoots(values);
}
