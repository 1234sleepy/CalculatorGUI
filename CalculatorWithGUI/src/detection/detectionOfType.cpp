#include "../../include/detection/detectionOfType.hpp"

int detectionOfType::detectType(std::string expression)
{
	for (auto letter : expression)
	{
		if (letter == 'x')
		{
			return 2;
		}
	}

	return (expression.find("sin") != std::string::npos ||
		expression.find("cos") != std::string::npos ||
		expression.find("tan") != std::string::npos ||
		expression.find("csc") != std::string::npos ||
		expression.find("sec") != std::string::npos ||
		expression.find("cot") != std::string::npos ||
		expression.find("asin") != std::string::npos ||
		expression.find("acos") != std::string::npos ||
		expression.find("atan") != std::string::npos ||
		expression.find("acot") != std::string::npos)
		? 3
		: 1;
}