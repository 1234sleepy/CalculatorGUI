#pragma once

#include "../../../CalculatorWithGUI/vendor/imguI/imgui.h"

#include "../../include/struct/QuadraticValues.h"

#include "BasicCalculator.h"

#include <string>
#include <iostream>
#include <vector>

class QuadraticCalculator : public BasicCalculator
{
public:

	struct roots
	{
		std::string firstRoot = "0.000000";
		std::string secondRoot = "0.000000";
		bool isImaginary;
	};


	struct CalcResult
	{
		roots value;
		bool success;
		std::string errorMsg;
	};

    static CalcResult evaluateExpression(std::string expression);
private:

    static QuadraticValues evaluateQuadraticExpression(std::string expression);

    static double evalSimpleExpr(std::string expression);

    static std::vector<std::string> convertInfixToPostfix(std::string expression);

    static CalcResult getRoots(QuadraticValues val);

	static bool isQuadraticExpression(std::string expression);
};