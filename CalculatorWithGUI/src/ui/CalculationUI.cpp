
#include "../../include/detection/detectionOfType.h"

#include "../../external-library/ImGuiFileDialogLibrary/ImGuiFileDialog.h"

#include "../../../CalculatorWithGUI/vendor/imguI/misc/cpp/imgui_stdlib.h" 

#include "../../include/ui/CalculatorUI.h"




const ImGuiWindowFlags CalculatorUI::imGuiWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;

const std::array<CalculatorUI::functBtn, 17> CalculatorUI::buttonNames =
{
    CalculatorUI::functBtn("x^2", "^2", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("x^3", "^3", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("(", "(", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn(")", "^)", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("a^b", "^", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("*", "*", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("/", "/", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("e", "e", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("Pi", "P", {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("sin", "sin()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("cos", "cos()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("tan", "tan()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("cot", "cot()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("asin", "asin()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("acos", "acos()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("atan", "atan()", {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("acot", "acot()", {CalculatorUI::calculatorTypes::TrigCalc}),
};



const int CalculatorUI::programWidth = 700;
const int CalculatorUI::programHeight = 700;

const ImVec2 CalculatorUI::standardCalculatorBtnSize = ImVec2(470, 20);
const ImVec2 CalculatorUI::standardCalculatorUISize = ImVec2(180, 20);
const ImVec2 CalculatorUI::standardCalculatorUIWindowSize = ImVec2(700, 200);

const double CalculatorUI::standardCalculatorInputTextWithHintSize = 470.0;

char CalculatorUI::expression[256] = "";
char CalculatorUI::prevExpression[256] = "";


bool CalculatorUI::isImportingFile = false;


void CalculatorUI::changeCalc(CalculatorUI::calculatorTypes& currentUI, CalculatorUI::calculatorTypes type)
{
    currentUI = type;
    memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
    memset(CalculatorUI::CalculatorUI::prevExpression, 0, sizeof(CalculatorUI::CalculatorUI::prevExpression));
}

void CalculatorUI::basicCalcEvaluation(double& result)
{
    result = BasicCalculator::evaluateExpression(CalculatorUI::expression);

    memcpy(CalculatorUI::prevExpression, CalculatorUI::expression, sizeof(CalculatorUI::expression));

    History::addHistory({ std::string(CalculatorUI::expression), std::string(CalculatorUI::expression) + " = " + std::to_string(result) });

    memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
}

void CalculatorUI::quadraticCalcEvaluation(QuadraticCalculator::roots& result)
{
    result = QuadraticCalculator::evaluateExpression(CalculatorUI::expression);
    memcpy(CalculatorUI::prevExpression, CalculatorUI::expression, sizeof(CalculatorUI::expression));

    History::addHistory({ std::string(CalculatorUI::expression), std::string(CalculatorUI::expression) + " x1 = " + result.firstRoot + " x2= " + result.secondRoot });

    memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
}

void CalculatorUI::trigCalcEvaluation(double& result)
{
    result = TrigCalculator::evaluateExpression(CalculatorUI::expression);
    memcpy(CalculatorUI::prevExpression, CalculatorUI::expression, sizeof(CalculatorUI::expression));

    History::addHistory({ std::string(CalculatorUI::expression), std::string(CalculatorUI::expression) + " = " + std::to_string(result) });

    memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
}


void CalculatorUI::importExpressions(std::filesystem::path filePathName, CalculatorUI::calculatorTypes& currentUI)
{
    std::ifstream  importFile(filePathName, std::ios::out);
    std::string line;

    if (importFile.is_open())
    {
        CalculatorUI::isImportingFile = true;
        while (std::getline(importFile, line))
        {
            if (!line.empty())
            {
                strcpy_s(CalculatorUI::expression, sizeof(CalculatorUI::expression), line.c_str());
                CalculatorUI::calculatorTypes expressionType = static_cast<CalculatorUI::calculatorTypes>(detectionOfType::detectType(CalculatorUI::expression));
                
                switch (expressionType)
                {
                    case CalculatorUI::calculatorTypes::BasicCalc:
                        CalculatorUI::renderBasicCalculator();
                        break;
                    case CalculatorUI::calculatorTypes::QuadraticCalc:
                        CalculatorUI::renderQuadraticCalculator();
                        break;
                    case CalculatorUI::calculatorTypes::TrigCalc:
                        CalculatorUI::renderTrigCalculator();
                        break;
                }
            }
        }

        CalculatorUI::isImportingFile = false;
        importFile.close();
    }
    else 
    {

    }
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

        if (ImGui::Button("Input")) {
            IGFD::FileDialogConfig config;
            config.path = ".";
            ImGuiFileDialog::Instance()->OpenDialog("Input", "Choose File", ".txt", config);
        }

        if (ImGuiFileDialog::Instance()->Display("Input")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::filesystem::path filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

                importExpressions(filePathName, currentUI);

            }
            ImGuiFileDialog::Instance()->Close();
        }

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


    CalculatorUI::renderFuncExprButtons(currentUI);

    ImGui::SetNextWindowSize(ImVec2(500, 200));
    ImGui::SetNextWindowPos(ImVec2(200, 200));
    
    if (ImGui::Begin("Scrollable Window", nullptr,
        CalculatorUI::imGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("History");
        ImGui::SetWindowFontScale(1.0f);
        if (ImGui::BeginChild("ScrollableRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar    
            | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse))
        {
            auto hist = History::getHistory();
    
            while (!hist.empty())
            {
                const auto& element = hist.top();
    
                if (ImGui::Button(element.exprRes.c_str(), ImVec2(450,20)))
                {
                    memset(CalculatorUI::CalculatorUI::expression, 0, sizeof(CalculatorUI::CalculatorUI::expression));
                    memcpy(CalculatorUI::expression, element.expr.c_str(), sizeof(element));
                }
    
                hist.pop();
            }
    
        }
        ImGui::EndChild();
    
    }
    ImGui::End();
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
            CalculatorUI::expression, sizeof(CalculatorUI::expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize) || CalculatorUI::isImportingFile)
        {
            CalculatorUI::basicCalcEvaluation(result);
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

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize) || CalculatorUI::isImportingFile)
        {
            CalculatorUI::quadraticCalcEvaluation(result);
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
        ImGui::InputTextWithHint("##Expression", "sin(30)+cos(P)",
            CalculatorUI::expression, sizeof(CalculatorUI::expression),
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::standardCalculatorBtnSize) || CalculatorUI::isImportingFile)
        {
            CalculatorUI::trigCalcEvaluation(result);
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

void CalculatorUI::renderFuncExprButtons(CalculatorUI::calculatorTypes& currentUI)
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

        int i = 0;

        for(auto btn : CalculatorUI::buttonNames)
        {
            i++;

            if (btn.isUpproper(currentUI))
            {
                if (ImGui::Button(btn.name.c_str(), ImVec2(40, 40)))
                {
                    CalculatorUI::addToExpression(btn.value);
                }
            }
            else
            {
                ImVec4 buttonColor = ImVec4(0.255f, 0.18f, 0.075f, 1.00f);
                ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
                ImGui::BeginDisabled();
                if (ImGui::Button(btn.name.c_str(), ImVec2(40, 40)))
                {
                    
                    CalculatorUI::addToExpression(btn.value);
                    
                }
                ImGui::EndDisabled();
                ImGui::PopStyleColor(1);
            }


            if (i < 9)
            {
                ImGui::SameLine();
            }
            else 
            {
                i = 0;
            }
            
        }
    }
    ImGui::End();
}
