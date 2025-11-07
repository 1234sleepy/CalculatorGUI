#include "../../include/ui/CalculatorUI.h"

const ImVec2 CalculatorUI::kFuncButtonSize = { 59,55 };


const ImGuiWindowFlags CalculatorUI::kImGuiWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
const std::array<CalculatorUI::functBtn, 20> CalculatorUI::kButtonNames =
{
    CalculatorUI::functBtn("x^2", "^2", true,CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("x^3", "^3", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("(", "(", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn(")", ")", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("a^b", "^", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("*", "*", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("/", "/", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("e", "e",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("π","π", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("√","√(", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::BasicCalc, CalculatorUI::calculatorTypes::QuadraticCalc, CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("sin", "sin(", false, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("cos", "cos(", true, CalculatorUI::kFuncButtonSize, {CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("tan", "tan(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("csc", "csc(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
	CalculatorUI::functBtn("sec", "sec(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("cot", "cot(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("asin", "asin(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("acos", "acos(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("atan", "atan(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
    CalculatorUI::functBtn("acot", "acot(",  true, CalculatorUI::kFuncButtonSize,{CalculatorUI::calculatorTypes::TrigCalc}),
};

bool CalculatorUI::isErrorHandlering = false;
std::string CalculatorUI::errorMsg = "";

const int CalculatorUI::kProgramWidth = 700;
const int CalculatorUI::kProgramHeight = 610;

int CalculatorUI::countOfExportFiles = 1;

const ImVec2 CalculatorUI::kStandardCalculatorBtnSize = ImVec2(470, 30);
const ImVec2 CalculatorUI::kStandardCalculatorUISize = ImVec2(180, 30);
const ImVec2 CalculatorUI::kStandardCalculatorUIWindowSize = ImVec2(700, 200);

const double CalculatorUI::kStandardCalculatorInputTextWithHintSize = 470.0;

std::string CalculatorUI::expression = "";
std::string CalculatorUI::prevExpression = "empty";

bool CalculatorUI::isImportingFile = false;

void CalculatorUI::saveHistory(History::historySave history)
{
    History::addHistory(history);
    History::historyCount++;

    CalculatorUI::changePrevExpression();
}

void CalculatorUI::changePrevExpression()
{
    CalculatorUI::prevExpression = CalculatorUI::expression;
    CalculatorUI::expression = "";
}

void CalculatorUI::clearExpressionVariables()
{
    CalculatorUI::expression = "";
    CalculatorUI::prevExpression = "empty";
}

void CalculatorUI::changeCalc(CalculatorUI::calculatorTypes& currentUI, CalculatorUI::calculatorTypes type)
{
    currentUI = type;
    CalculatorUI::clearExpressionVariables();
}

void CalculatorUI::basicCalcEvaluation(BasicCalculator::CalcResult& result)
{
    std::string s = CalculatorUI::replaceLetters(CalculatorUI::expression);
    result = BasicCalculator::evaluateExpression(CalculatorUI::replaceLetters(CalculatorUI::expression));

    CalculatorUI::errorHandler(result.success, result.errorMsg);

    CalculatorUI::saveHistory({ std::string(CalculatorUI::expression), std::to_string(History::historyCount) + ". " + std::string(CalculatorUI::expression) + " = " + std::to_string(result.value) });

}

void CalculatorUI::quadraticCalcEvaluation(QuadraticCalculator::CalcResult& result)
{
    result = QuadraticCalculator::evaluateExpression(CalculatorUI::replaceLetters(CalculatorUI::expression));

    CalculatorUI::errorHandler(result.success, result.errorMsg);

    CalculatorUI::saveHistory({ std::string(CalculatorUI::expression), std::to_string(History::historyCount) + ". " + std::string(CalculatorUI::expression) + " x1 = " + result.value.firstRoot + " x2= " + result.value.secondRoot });
}

void CalculatorUI::trigCalcEvaluation(TrigCalculator::CalcResult& result)
{
    result = TrigCalculator::evaluateExpression(CalculatorUI::replaceLetters(CalculatorUI::expression));

    CalculatorUI::errorHandler(result.success, result.errorMsg);

    CalculatorUI::saveHistory({ std::string(CalculatorUI::expression), std::to_string(History::historyCount) + ". " + std::string(CalculatorUI::expression) + " = " + std::to_string(result.value) });
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
                CalculatorUI::expression = line;
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
}

void CalculatorUI::exportExpressions()
{
    std::filesystem::path path = "export\\expressions" + std::to_string( CalculatorUI::countOfExportFiles) + ".txt";
    
    CalculatorUI::countOfExportFiles++;

    if (!std::filesystem::exists("export"))
    {
        std::filesystem::create_directory("export");
    }

    std::ofstream outputFile(path);
    if (outputFile.is_open())   
    {
        auto hist = History::getHistory();
        while (!hist.empty())
        {
            auto element = hist.top();
            outputFile << element.exprRes << "\n";
            hist.pop();
        }
    }
}

void CalculatorUI::renderCalculatorUI(CalculatorUI::calculatorTypes& currentUI)
{
    ImGui::SetNextWindowSize(ImVec2(200, 400));
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

    if (ImGui::Begin("UI", nullptr,
        CalculatorUI::kImGuiWindowFlags))
    {
        if (isErrorHandlering)
        {
            ImGui::OpenPopup("Error");

            if (ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("%s", CalculatorUI::errorMsg.c_str());

                if (ImGui::Button("OK"))
                {
                    ImGui::CloseCurrentPopup();
                    CalculatorUI::isErrorHandlering = false;
                    CalculatorUI::errorMsg = "";
                }

                ImGui::EndPopup();
            }
        }

        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("UI");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();

        if (ImGui::Button("Input"))
        {
            IGFD::FileDialogConfig config;
            config.path = ".";
            ImGuiFileDialog::Instance()->OpenDialog("Input", "Choose File", ".txt", config);
        }

        ImGui::SameLine(0.0f, 87.0f);
        
        if (ImGui::Button("Export"))
        {
            CalculatorUI::exportExpressions();
        }

        if (ImGuiFileDialog::Instance()->Display("Input")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::filesystem::path filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

                importExpressions(filePathName, currentUI);

            }
            ImGuiFileDialog::Instance()->Close();
        }

        if (ImGui::Button("Basic", kStandardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::BasicCalc)
        {
            CalculatorUI::renderBasicCalculator();
            if (currentUI != CalculatorUI::calculatorTypes::BasicCalc)
            {
                CalculatorUI::changeCalc(currentUI, CalculatorUI::calculatorTypes::BasicCalc);
            }

        }
        if (ImGui::Button("Quadratic", kStandardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::QuadraticCalc)
        {
            CalculatorUI::renderQuadraticCalculator();
            if (currentUI != CalculatorUI::calculatorTypes::QuadraticCalc)
            {
                CalculatorUI::changeCalc(currentUI, CalculatorUI::calculatorTypes::QuadraticCalc);
            }
        }
        if (ImGui::Button("Trig", kStandardCalculatorUISize) || currentUI == CalculatorUI::calculatorTypes::TrigCalc)
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
        CalculatorUI::kImGuiWindowFlags))
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
                auto element = hist.top();
    
                if (ImGui::Button(element.exprRes.c_str(), ImVec2(450,30)))
                {
                    CalculatorUI::expression = element.expr;
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
    static BasicCalculator::CalcResult result = {};

    ImGui::SetNextWindowSize(CalculatorUI::kStandardCalculatorUIWindowSize);
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Basic Calculator", nullptr,
        CalculatorUI::kImGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Basic Calculator");
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::kStandardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "(2+2)*2",
            &CalculatorUI::expression,
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::kStandardCalculatorBtnSize) || CalculatorUI::isImportingFile)
        {
            CalculatorUI::basicCalcEvaluation(result);
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", CalculatorUI::prevExpression.c_str());
        ImGui::Text("Result: %.6f", result.value);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderQuadraticCalculator()
{
    static QuadraticCalculator::CalcResult result = {};

    ImGui::SetNextWindowSize(CalculatorUI::kStandardCalculatorUIWindowSize);
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Quadratic Calculator", nullptr,
        CalculatorUI::kImGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Quadratic Calculator");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::kStandardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "ax^2+bx+c",
            &CalculatorUI::expression,
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersEcceptXCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::kStandardCalculatorBtnSize) || CalculatorUI::isImportingFile)
        {
            CalculatorUI::quadraticCalcEvaluation(result);
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", CalculatorUI::prevExpression.c_str());
        ImGui::Text("Imaginary roots: %s", result.value.isImaginary ? "Yes" : "No");
        ImGui::Text("FirstRoot: %s", result.value.firstRoot.c_str());
        ImGui::Text("SecondRoot: %s", result.value.secondRoot.c_str());
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::renderTrigCalculator()
{
    static TrigCalculator::CalcResult result = {};

    ImGui::SetNextWindowSize(CalculatorUI::kStandardCalculatorUIWindowSize);
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Trig Calculator", nullptr,
        CalculatorUI::kImGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Trig Calculator");
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Separator();

        ImGui::SetNextItemWidth(CalculatorUI::kStandardCalculatorInputTextWithHintSize);
        ImGui::InputTextWithHint("##Expression", "sin(30)+cos(P)",
            &CalculatorUI::expression,
            ImGuiInputTextFlags_CallbackCharFilter,
            NoLettersCallback);

        if (ImGui::Button("Evaluate", CalculatorUI::kStandardCalculatorBtnSize) || CalculatorUI::isImportingFile)
        {
            CalculatorUI::trigCalcEvaluation(result);
        }

        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Expression: %s", CalculatorUI::prevExpression.c_str());
        ImGui::Text("Result: %.6f", result.value);
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void CalculatorUI::addToExpression(std::string addition)
{
    CalculatorUI::expression += addition;
}

void CalculatorUI::renderFuncExprButtons(CalculatorUI::calculatorTypes& currentUI)
{
    ImGui::SetNextWindowSize(ImVec2(700, 300));
    ImGui::SetNextWindowPos(ImVec2(0, 400), ImGuiCond_Once);

    if (ImGui::Begin("Functions/Expressions", nullptr,
        CalculatorUI::kImGuiWindowFlags))
    {
        ImGui::SetCursorPosY(5);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Functions/Expressions");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();

        for(auto btn : CalculatorUI::kButtonNames)
        {
            if (btn.isSameLine)
            {
                ImGui::SameLine();
            }

            if (btn.isUpproper(currentUI))
            {
                if (ImGui::Button(btn.name.c_str(), btn.btnSize))
                {
                    CalculatorUI::addToExpression(btn.value);
                }
            }
            else
            {
                ImVec4 buttonColor = ImVec4(0.255f, 0.18f, 0.075f, 1.00f);
                ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
                ImGui::BeginDisabled();
                if (ImGui::Button(btn.name.c_str(), btn.btnSize))
                {
                    
                    CalculatorUI::addToExpression(btn.value);
                    
                }
                ImGui::EndDisabled();
                ImGui::PopStyleColor(1);
            }
        }
    }
    ImGui::End();
}

void CalculatorUI::errorHandler(bool status, std::string msg)
{
    if (!msg.empty() && status == false)
    {
        CalculatorUI::isErrorHandlering = true;
        CalculatorUI::errorMsg = msg;
    }
}


std::string CalculatorUI::replaceLetters(std::string expression)
{
    std::string res = "";

    for (int i = 0; i < expression.length(); i++)
    {
        if (static_cast<unsigned char>(expression[i]) == 207 && static_cast<unsigned char>(expression[i+1]) == 128)
        {
            res += 'P';
            i++;
        }
        else if (static_cast<unsigned char>(expression[i]) == 226 && static_cast<unsigned char>(expression[i + 1]) == 136 && static_cast<unsigned char>(expression[i + 2]) == 154)
        {
            res += 'S';
            i+=2;
        }
        else
        {
            res += expression[i];
        }
    }
    return res;
}