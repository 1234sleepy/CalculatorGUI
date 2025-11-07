#pragma once
#pragma execution_character_set("utf-8")

#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>

#include "../../vendor/imguI/imgui.h"


#include "../../../CalculatorCore/include/calculators/BasicCalculator.h"
#include "../../../CalculatorCore/include/calculators/QuadraticCalculator.h"
#include "../../../CalculatorCore/include/calculators/TrigCalculator.h"
#include "../../../CalculatorCore/include/history/History.h"


#include "../../include/filters/InputFilter.h"


class CalculatorUI
{
public:
	enum class calculatorTypes
	{
		NoCalc = 0,
		BasicCalc = 1,
		QuadraticCalc = 2,
		TrigCalc = 3
	};

	struct functBtn
	{
		std::string name;
		std::string value;
		bool isSameLine;
		ImVec2 btnSize;
		calculatorTypes uprovedTypes[3];

		bool isUpproper(calculatorTypes renderType)
		{
			for(auto type : uprovedTypes)
			{
				if (renderType == type)
				{
					return true;
				}
			}

			return false;
		}
	};

	static const ImVec2 kFuncButtonSize;

	static const std::array<functBtn, 20> kButtonNames;

	static const int kProgramWidth;
	static const int kProgramHeight;

	static int countOfExportFiles;

	static bool isErrorHandlering;
	static std::string errorMsg;

	static std::string expression;
	static std::string prevExpression;

	static const ImGuiWindowFlags kImGuiWindowFlags;

	static bool isImportingFile;

	static const ImVec2 kStandardCalculatorBtnSize;
	static const ImVec2 kStandardCalculatorUISize;
	static const ImVec2 kStandardCalculatorUIWindowSize;

	static const double kStandardCalculatorInputTextWithHintSize;


	static void renderCalculatorUI(calculatorTypes& currentUI);
	static void renderBasicCalculator();
	static void renderQuadraticCalculator();
	static void renderTrigCalculator();

	static void saveHistory(History::historySave history);

	static void changePrevExpression();

	static void clearExpressionVariables();

	static void renderFuncExprButtons(CalculatorUI::calculatorTypes& currentUI);

	static void addToExpression(std::string addition);

	static void changeCalc(calculatorTypes& currentUI, calculatorTypes type);

	static void importExpressions(std::filesystem::path filePathName, CalculatorUI::calculatorTypes& currentUI);
	static void exportExpressions();

	static void basicCalcEvaluation(BasicCalculator::CalcResult& result);
	static void quadraticCalcEvaluation(QuadraticCalculator::CalcResult& result);
	static void trigCalcEvaluation(TrigCalculator::CalcResult& result);

	static void errorHandler(bool status, std::string msg);

	static std::string replaceLetters(std::string expression);
};
