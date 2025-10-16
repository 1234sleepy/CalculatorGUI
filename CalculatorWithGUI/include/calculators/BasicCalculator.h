#pragma once

#include "imgui.h"

#include <string>
#include <vector>

class BasicCalculator
{
public:
    static double evaluateExpression(const char expression[256]);

private:
    static std::vector<std::string> convertInfixToPostfix(const std::string& expr);
    static double evaluatePostfixExpression(const std::vector<std::string>& postfix);
    static int getOperatorPrecedence(char op);
};