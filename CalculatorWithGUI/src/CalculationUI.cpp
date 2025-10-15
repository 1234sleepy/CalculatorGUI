#include "../include/ui/CalculatorUI.h"
#include "imgui.h"
#include "../imguI/misc/cpp/imgui_stdlib.h" 

#include <iostream>

void RenderCalculatorUI(CalculatorUI& currentUI)
{


    ImGui::SetNextWindowSize(ImVec2(200, 100));
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

    if (ImGui::Begin("UI", nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        if (ImGui::Button("Basic") || currentUI == CalculatorUI::BasicCalc)
        {
            RenderBasicCalculator();
            currentUI = CalculatorUI::BasicCalc;
        }
        if (ImGui::Button("Quadratic") || currentUI == CalculatorUI::QuadraticCalc)
        {
            RenderQuadraticCalculator();
            currentUI = CalculatorUI::QuadraticCalc;
        }
        if (ImGui::Button("Trig") || currentUI == CalculatorUI::TrigCalc)
        {
            RenderTrigCalculator();
            currentUI = CalculatorUI::TrigCalc;
        }
    }
    ImGui::End();
}

void RenderBasicCalculator()
{
    static std::string expression = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(ImVec2(400, 700));
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Basic Calculator", nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::InputTextWithHint("##Expression", "Type basic exprasion", &expression);

        if (ImGui::Button("Evaluate"))
        {
         
        }

        ImGui::Separator();
        ImGui::Text("Expression: %s", expression.c_str());
        ImGui::Text("Result: %.6f", result);
    }
    ImGui::End();
}

void RenderQuadraticCalculator()
{
    static std::string expression = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(ImVec2(400, 700));
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);


    if (ImGui::Begin("Quadratic Calculator", nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
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

void RenderTrigCalculator()
{
    static std::string expression = "";
    static double result = 0.0;

    ImGui::SetNextWindowSize(ImVec2(400, 700));
    ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Once);

    if (ImGui::Begin("Trig Calculator", nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::InputTextWithHint("##Expression", "Type trig exprasion", &expression);

        if (ImGui::Button("Evaluate"))
        {

        }

        ImGui::Separator();
        ImGui::Text("Expression: %s", expression.c_str());
        ImGui::Text("Result: %.6f", result);
    }
    ImGui::End();
}