#pragma once


void RenderCalculatorUI();
void RenderBasicCalculator();
void RenderQuadraticCalculator();
void RenderTrigCalculator();

enum class CalculatorUI
{
	BasicCalc,
	QuadraticCalc,
	TrigCalc
};