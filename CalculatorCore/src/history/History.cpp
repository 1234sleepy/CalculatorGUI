#include "pch.h"

#include "../../include/history/History.hpp"

std::stack<History::historySave> History::_history;

int History::historyCount{ 1 };

void History::addHistory(History::historySave expression) 
{
	History::_history.push(expression);
}

std::stack<History::historySave> History::getHistory()
{
	return History::_history;
}