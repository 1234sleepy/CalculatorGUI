#pragma once

#include "../../../CalculatorWithGUI/vendor/imguI/imgui.h"

#include "../../include/struct/QuadraticValues.h"

#include "BasicCalculator.h"

#include <string>
#include <vector>

class QuadraticCalculator : public BasicCalculator
{
public:
	struct roots
	{
		double firstRoot;
		double secondRoot;
	};

    static roots evaluateExpression(const char expression[256]);

private:

    static QuadraticValues evaluateQuadraticExpression(const char* expr);

    static double evalSimpleExpr(const std::string& expr);

    static std::vector<std::string> convertInfixToPostfix(const char* expr);

    static roots getRoots(QuadraticValues val);
};