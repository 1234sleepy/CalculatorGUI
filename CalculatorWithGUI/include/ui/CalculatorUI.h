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

	static const std::array<std::string, 9> buttonNames;

	static const int programWidth;
	static const int programHeight;

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

};
