#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <regex>
#include <string>
#include <vector>

#include "../../../CalculatorWithGUI/vendor/imguI/imgui.h"

#include "BasicCalculator.hpp"

class TrigCalculator : public BasicCalculator
{
public:
	struct trigMatch
	{
		std::string fucnction;
		std::string argument;
	};


	static CalcResult evaluateExpression(std::string expression);

private:
	static std::string evaluateAllTrigFunctions(std::string expression);

};