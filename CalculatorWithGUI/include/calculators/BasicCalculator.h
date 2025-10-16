#pragma once

#include "imgui.h"

#include <iostream>
#include <vector>


int NoLettersCallback(ImGuiInputTextCallbackData* data);
double EvaluateBasicCalculator(const char expression[256]);