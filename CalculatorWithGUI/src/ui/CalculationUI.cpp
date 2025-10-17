
#include "../../../CalculatorCore/include/calculators/BasicCalculator.h"
#include "../../../CalculatorCore/include/calculators/QuadraticCalculator.h"
#include "../../../CalculatorCore/include/calculators/TrigCalculator.h"

#include "../../include/filters/InputFilter.h"


#include "../../../CalculatorWithGUI/vendor/imguI/misc/cpp/imgui_stdlib.h" 

#include "../../include/ui/CalculatorUI.h"


#include <iostream>

const ImGuiWindowFlags CalculatorUI::imGuiWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;

const int CalculatorUI::programWidth = 600;
const int CalculatorUI::programHeight = 700;


const ImVec2 CalculatorUI::standardCalculatorBtnSize = ImVec2(370, 20);
const ImVec2 CalculatorUI::standardCalculatorUISize = ImVec2(180, 20);
const double CalculatorUI::standardCalculatorInputTextWithHintSize = 370.0;

void CalculatorUI::renderCalculatorUI(CalculatorUI::calculatorTypes& currentUI)
{
    ImGui::SetNextWindowSize(ImVec2(200, 700));
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

    if (ImGui::Begin("UI", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("UI");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();

        if (ImGui::Button("Basic", standardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::BasicCalc)
        {
            CalculatorUI::renderBasicCalculator();
            currentUI = CalculatorUI::calculatorTypes::BasicCalc;
        }
        if (ImGui::Button("Quadratic", standardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::QuadraticCalc)
        {
            CalculatorUI::renderQuadraticCalculator();
            currentUI = CalculatorUI::calculatorTypes::QuadraticCalc;
        }
        if (ImGui::Button("Trig", standardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::TrigCalc)
        {
            CalculatorUI::renderTrigCalculator();
            currentUI = CalculatorUI::calculatorTypes::TrigCalc;
        }
    }
    ImGui::End();
}

void CalculatorUI::renderBasicCalculator()
{
    static char expression[256] = "";
    static char prevExpression[256] = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(ImVec2(400, 700));
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Basic Calculator", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {

        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Basic Calculator");
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::standardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "(2+2)*2",
            expression, sizeof(expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize))
        {
            result = BasicCalculator::evaluateExpression(expression);
            //memcpy(prevExpression, expression, sizeof(expression));
            expression[0] = '\0';
        }


        
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", prevExpression);
        ImGui::Text("Result: %.6f", result);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderQuadraticCalculator()
{
    static std::string expression = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(ImVec2(400, 700));
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);


    if (ImGui::Begin("Quadratic Calculator", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {
        ImGui::InputTextWithHint("##Expression", "Type quadratic exprasion", &expression);

        if (ImGui::Button("Evaluate"))
        {

        }

        ImGui::Separator();
        ImGui::Text("Expression: %s", expression.c_str());
        ImGui::Text("Result: %.6f", result);
    }
    ImGui::End();
}

void CalculatorUI::renderTrigCalculator()
{
    static std::string expression = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(ImVec2(400, 700));
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Trig Calculator", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {
        ImGui::InputTextWithHint("##Expression", "Type trig exprasion", &expression);

        if (ImGui::Button("Evaluate"))
        {

        }

        ImGui::Separator();
        ImGui::Text("Expression: %s", expression);
        ImGui::Text("Result: %.6f", result);
    }
    ImGui::End();
}