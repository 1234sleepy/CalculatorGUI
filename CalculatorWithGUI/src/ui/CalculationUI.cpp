
#include "../../../CalculatorCore/include/calculators/BasicCalculator.h"
#include "../../../CalculatorCore/include/calculators/QuadraticCalculator.h"
#include "../../../CalculatorCore/include/calculators/TrigCalculator.h"

#include "../../include/filters/InputFilter.h"


#include "../../../CalculatorWithGUI/vendor/imguI/misc/cpp/imgui_stdlib.h" 

#include "../../include/ui/CalculatorUI.h"


const ImGuiWindowFlags CalculatorUI::imGuiWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;

const std::array<std::string, 9> CalculatorUI::buttonNames =
{
    "x",
    "a^2",
    "(",
    ")",
    "a^b",
    "*",
    "/",
    "e",
    "Pi"
};

const int CalculatorUI::programWidth = 600;
const int CalculatorUI::programHeight = 700;

const ImVec2 CalculatorUI::standardCalculatorBtnSize = ImVec2(370, 20);
const ImVec2 CalculatorUI::standardCalculatorUISize = ImVec2(180, 20);
const ImVec2 CalculatorUI::standardCalculatorUIWindowSize = ImVec2(400, 400);

const double CalculatorUI::standardCalculatorInputTextWithHintSize = 370.0;

void CalculatorUI::renderCalculatorUI(CalculatorUI::calculatorTypes& currentUI)
{
    ImGui::SetNextWindowSize(ImVec2(200, 400));
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


    CalculatorUI::renderFuncExprButtons();
}

void CalculatorUI::renderBasicCalculator()
{
    static char expression[256] = "";
    static char prevExpression[256] = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(CalculatorUI::standardCalculatorUIWindowSize);
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
            memcpy(prevExpression, expression, sizeof(expression));
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
    static char expression[256] = "";
    static char prevExpression[256] = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(CalculatorUI::standardCalculatorUIWindowSize);
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Quadratic Calculator", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {

        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Quadratic Calculator");
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::standardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "ax^2+bx+c",
            expression, sizeof(expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize))
        {
            result = QuadraticCalculator::evaluateExpression(expression);
            memcpy(prevExpression, expression, sizeof(expression));
            expression[0] = '\0';
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", prevExpression);
        ImGui::Text("Result: %.6f", result);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderTrigCalculator()
{
    static char expression[256] = "";
    static char prevExpression[256] = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(CalculatorUI::standardCalculatorUIWindowSize);
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Trig Calculator", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {

        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Trig Calculator");
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::standardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "sin(x)+cos(x)",
            expression, sizeof(expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize))
        {
            result = TrigCalculator::evaluateExpression(expression);
            memcpy(prevExpression, expression, sizeof(expression));
            expression[0] = '\0';
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", prevExpression);
        ImGui::Text("Result: %.6f", result);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderFuncExprButtons()
{
    ImGui::SetNextWindowSize(ImVec2(600, 300));
    ImGui::SetNextWindowPos(ImVec2(0, 400), ImGuiCond_Once);

    if (ImGui::Begin("Functions/Expressions", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Functions/Expressions");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();

        for(auto btn : CalculatorUI::buttonNames)
        {
            if (ImGui::Button(btn.c_str(), ImVec2(40,40)))
            {

            }
            ImGui::SameLine();
        }
    }
    ImGui::End();
}