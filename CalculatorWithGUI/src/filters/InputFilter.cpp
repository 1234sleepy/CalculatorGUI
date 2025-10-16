#include "../../include/filters/InputFilter.h"

int NoLettersCallback(ImGuiInputTextCallbackData* data)
{
	ImWchar c = data->EventChar;

	bool isValidValue = (c >= '0' && c <= '9') || std::strchr("+-/*().^", c);

	return isValidValue ? 0 : 1;
}