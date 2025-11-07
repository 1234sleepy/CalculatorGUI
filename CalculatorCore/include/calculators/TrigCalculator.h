#pragma once

#include "../../../CalculatorWithGUI/vendor/imguI/imgui.h"

#include "BasicCalculator.h"

#include <string>
#include <vector>

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