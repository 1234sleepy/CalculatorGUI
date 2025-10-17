#pragma once

#include "../../vendor/imguI/imgui.h"


#include <iostream>
#include <array>

class CalculatorUI
{
public:
	enum class calculatorTypes
	{
		BasicCalc,
		QuadraticCalc,
		TrigCalc
	};

	struct functBtn
	{
		std::string name;
		std::string value;
	};

	static const std::array<functBtn, 9> buttonNames;

	static const int programWidth;
	static const int programHeight;

	static char expression[256];
	static char prevExpression[256];

	static const ImGuiWindowFlags imGuiWindowFlags;

	static const ImVec2 standardCalculatorBtnSize;
	static const ImVec2 standardCalculatorUISize;
	static const ImVec2 standardCalculatorUIWindowSize;

	static const double standardCalculatorInputTextWithHintSize;


	static void renderCalculatorUI(calculatorTypes& currentUI);
	static void renderBasicCalculator();
	static void renderQuadraticCalculator();
	static void renderTrigCalculator();

	static void renderFuncExprButtons();

	static void addToExpression(std::string addition);

	static void changeCalc(calculatorTypes& currentUI, calculatorTypes type);

};
