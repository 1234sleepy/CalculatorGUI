#pragma once

#include "imgui.h"

class CalculatorUI
{
public:
	enum class calculatorTypes
	{
		BasicCalc,
		QuadraticCalc,
		TrigCalc
	};

	static const ImGuiWindowFlags imGuiWindowFlags;

	static const ImVec2 standardCalculatorBtnSize;
	static const ImVec2 standardCalculatorUISize;


	static void renderCalculatorUI(calculatorTypes& currentUI);
	static void renderBasicCalculator();
	static void renderQuadraticCalculator();
	static void renderTrigCalculator();


};
