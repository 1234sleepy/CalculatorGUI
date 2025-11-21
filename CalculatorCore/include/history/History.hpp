#pragma once

#include<iostream>
#include<stack>


class History {
public:
	struct historySave
	{
		std::string expr;
		std::string exprRes;
	};

	static int historyCount;

	static void clearHistory();
	static void addHistory(historySave expression);
	static std::stack<historySave> getHistory();
	static std::stack<historySave> getExportHistory();
private:
	static std::stack<historySave> _history;
};