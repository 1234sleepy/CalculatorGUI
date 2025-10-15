#include "../../include/calculators/BasicCalculator.h"

#include <iostream>
#include <string>

int NoLettersCallback(ImGuiInputTextCallbackData* data)
{
	ImWchar c = data->EventChar;

	bool isValidValue = (c >= '0' && c <= '9') || std::strchr("+-/*().^", c);

	return isValidValue? 0:1;
}

double EvaluateBasicCalculator(const char expression[256])
{
	size_t len = std::strlen(expression);

	double res = 0;
	
	char oper = 'n';
	std::string num = "";
	std::string num2 = "";

	double tmpValue = 0.0;

	for (size_t i = 0; i < len+1; i++)
	{
		std::cout << i << " num: " << num << " num2: " << num2 << " oper: " << oper << " res: " << res << " exp: " << expression[i] << "\n";
		if (oper == 'n')
		{
			if (!std::strchr("+-/*", expression[i]))
			{
				num += expression[i];
			}
			else
			{
				tmpValue = std::stod(num);
				num = "";
				res += tmpValue;
				tmpValue = 0;
				oper = expression[i];
			}
		}
		else if (oper != 'n')
		{
			if (!std::strchr("+-/*", expression[i]))
			{
				num2 += expression[i];
			}
			else
			{
				std::cout << "nice";
				tmpValue = std::stod(num2);
				switch (oper)
				{
					case '+':
						res += tmpValue;
						break;
					case '-':
						res -= tmpValue;
						break;
					case '*':
						res *= tmpValue;
						break;
					case '/':
						res /= tmpValue;
						break;
					default:
						res += tmpValue;
						break;
				}
				tmpValue = 0.0;
				num2 = "";
				oper = expression[i];
			}
		}
			std::cout << i << " num: " << num << " num2: " << num2 << " oper: " << oper << " res: " << res << "\n";
	}

	return res;
}