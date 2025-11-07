#include "../../include/filters/InputFilter.hpp"

int NoLettersCallback(ImGuiInputTextCallbackData* data)
{
	ImWchar c{ data->EventChar };

	bool isValidValue{ (c >= '0' && c <= '9') || std::strchr("+-/*().^", c) };

	return isValidValue ? 0 : 1;
}

int NoLettersEcceptXCallback(ImGuiInputTextCallbackData* data)
{
	ImWchar c{ data->EventChar };

	bool isValidValue{ (c >= '0' && c <= '9') || std::strchr("+-/*().^", c) || c == 'x' };

	return isValidValue ? 0 : 1;
}