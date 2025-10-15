#pragma once

enum class CalculatorUI
{
	BasicCalc,
	QuadraticCalc,
	TrigCalc
};

void RenderCalculatorUI(CalculatorUI& currentUI);
void RenderBasicCalculator();
void RenderQuadraticCalculator();
void RenderTrigCalculator();

