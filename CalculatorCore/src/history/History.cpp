#include "pch.h"

#include "../../include/history/History.hpp"

std::stack<History::historySave> History::_history;

int History::historyCount{ 1 };

void History::clearHistory()
{
	History::_history = std::stack<historySave>();
}

void History::addHistory(History::historySave expression) 
{
	History::_history.push(expression);
}

std::stack<History::historySave> History::getHistory()
{
	return History::_history;
}

std::stack<History::historySave> History::getExportHistory()
{
	std::stack<historySave> exportHistory{};
	std::stack<historySave> tmp = History::_history;

	while (!tmp.empty())
	{
		exportHistory.push(tmp.top());
		tmp.pop();
	}

	return exportHistory;
}