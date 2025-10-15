#pragma once

#include "imgui.h"

#include <iostream>

int NoLettersCallback(ImGuiInputTextCallbackData* data);
double EvaluateBasicCalculator(const char expression[256]);