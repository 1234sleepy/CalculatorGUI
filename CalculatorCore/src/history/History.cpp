#include "pch.h"

#include "../../include/history/History.h"

std::stack<History::historySave> History::history;

void History::addHistory(History::historySave expression) 
{
	History::history.push(expression);
}

std::stack<History::historySave> History::getHistory()
{
	return History::history;
}