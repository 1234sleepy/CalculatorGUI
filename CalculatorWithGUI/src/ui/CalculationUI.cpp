
#include "../../../CalculatorCore/include/calculators/BasicCalculator.h"
#include "../../../CalculatorCore/include/calculators/QuadraticCalculator.h"
#include "../../../CalculatorCore/include/calculators/TrigCalculator.h"

#include "../../include/filters/InputFilter.h"


#include "../../../CalculatorWithGUI/vendor/imguI/misc/cpp/imgui_stdlib.h" 

#include "../../include/ui/CalculatorUI.h"


const ImGuiWindowFlags CalculatorUI::imGuiWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;

const std::array<CalculatorUI::functBtn, 9> CalculatorUI::buttonNames =
{
    CalculatorUI::functBtn("x^2", "^2"),
    CalculatorUI::functBtn("x^3", "^3"),
    CalculatorUI::functBtn("(", "("),
    CalculatorUI::functBtn(")", "^)"),
    CalculatorUI::functBtn("a^b", "^"),
    CalculatorUI::functBtn("*", "*"),
    CalculatorUI::functBtn("/", "/"),
    CalculatorUI::functBtn("e", "e"),
    CalculatorUI::functBtn("Pi", "P"),
};

const int CalculatorUI::programWidth = 700;
const int CalculatorUI::programHeight = 700;

const ImVec2 CalculatorUI::standardCalculatorBtnSize = ImVec2(470, 20);
const ImVec2 CalculatorUI::standardCalculatorUISize = ImVec2(180, 20);
const ImVec2 CalculatorUI::standardCalculatorUIWindowSize = ImVec2(700, 400);

const double CalculatorUI::standardCalculatorInputTextWithHintSize = 470.0;

char CalculatorUI::CalculatorUI::expression[256] = "";
char CalculatorUI::CalculatorUI::prevExpression[256] = "";

void CalculatorUI::changeCalc(CalculatorUI::calculatorTypes& currentUI, CalculatorUI::calculatorTypes type)
{
    currentUI = type;
    memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
    memset(CalculatorUI::CalculatorUI::prevExpression, 0, sizeof(CalculatorUI::CalculatorUI::prevExpression));
}

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
            if (currentUI != CalculatorUI::calculatorTypes::BasicCalc)
            {
                CalculatorUI::changeCalc(currentUI, CalculatorUI::calculatorTypes::BasicCalc);
            }

        }
        if (ImGui::Button("Quadratic", standardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::QuadraticCalc)
        {
            CalculatorUI::renderQuadraticCalculator();
            if (currentUI != CalculatorUI::calculatorTypes::QuadraticCalc)
            {
                CalculatorUI::changeCalc(currentUI, CalculatorUI::calculatorTypes::QuadraticCalc);
            }
        }
        if (ImGui::Button("Trig", standardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::TrigCalc)
        {
            CalculatorUI::renderTrigCalculator();
            if (currentUI != CalculatorUI::calculatorTypes::TrigCalc)
            {
                CalculatorUI::changeCalc(currentUI, CalculatorUI::calculatorTypes::TrigCalc);
            }
        }
    }
    ImGui::End();


    CalculatorUI::renderFuncExprButtons();
}

void CalculatorUI::renderBasicCalculator()
{
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
            CalculatorUI::CalculatorUI::expression, sizeof(CalculatorUI::expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize))
        {
            result = BasicCalculator::evaluateExpression(CalculatorUI::expression);
            memcpy(CalculatorUI::prevExpression, CalculatorUI::expression, sizeof(CalculatorUI::expression));
            memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", CalculatorUI::prevExpression);
        ImGui::Text("Result: %.6f", result);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderQuadraticCalculator()
{
    static QuadraticCalculator::roots result = {"0", "0", false};

    ImGui::SetNextWindowSize(CalculatorUI::standardCalculatorUIWindowSize);
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Quadratic Calculator", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {

        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Quadratic Calculator");
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Only simplified quadratic\nexpression such as\n7x^2-4x^2+23x+12x+1290-120/18");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::standardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "ax^2+bx+c",
            CalculatorUI::expression, sizeof(CalculatorUI::expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersEcceptXCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize))
        {
            result = QuadraticCalculator::evaluateExpression(CalculatorUI::expression);
            memcpy(CalculatorUI::prevExpression, CalculatorUI::expression, sizeof(CalculatorUI::expression));
            memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", CalculatorUI::prevExpression);
        ImGui::Text("Imaginary roots: %s", result.isImaginary ? "Yes" : "No");
        ImGui::Text("FirstRoot: %s", result.firstRoot.c_str());
        ImGui::Text("SecondRoot: %s", result.secondRoot.c_str());
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderTrigCalculator()
{
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
            CalculatorUI::expression, sizeof(CalculatorUI::expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize))
        {
            //result = TrigCalculator::evaluateExpression(CalculatorUI::expression);
            memcpy(CalculatorUI::prevExpression, CalculatorUI::expression, sizeof(CalculatorUI::expression));
            memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", CalculatorUI::prevExpression);
        ImGui::Text("Result: %.6f", result);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::addToExpression(std::string addition)
{
    strncat_s(CalculatorUI::expression, sizeof(CalculatorUI::expression), addition.c_str(), _TRUNCATE);
}

void CalculatorUI::renderFuncExprButtons()
{
    ImGui::SetNextWindowSize(ImVec2(700, 300));
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
            if (ImGui::Button(btn.name.c_str(), ImVec2(40,40)))
            {
                CalculatorUI::addToExpression(btn.value);
            }
            ImGui::SameLine();
        }
    }
    ImGui::End();
}
