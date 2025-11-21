#pragma once

#include "../../include/ui/CalculatorUI.hpp"

#include <iostream>
#include <string>


class detectionOfType
{
public:
	static CalculatorUI::calculatorTypes detectType(std::string expression);
};
