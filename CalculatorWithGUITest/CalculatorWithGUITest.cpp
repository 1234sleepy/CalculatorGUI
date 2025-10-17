#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculatorCore/include/calculators/BasicCalculator.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorWithGUITest
{
	TEST_CLASS(CalculatorWithGUITest)
	{
	public:
		
		TEST_METHOD(BasicCalculatorEvaluationTest1)
		{
			double result = BasicCalculator::evaluateExpression("(12.5 + 123.2 * 12.1) / 12.0 * 32.0 - 43.7");
			Assert::AreEqual(3964.88, result, 0.01, L"Calculation failed!");
		}
		TEST_METHOD(BasicCalculatorEvaluationTest2)
		{
			double result = BasicCalculator::evaluateExpression("(12.5 + 123.2 * 12.1 - 45.6 / 7.8 + 89.3 * 3.4 - 56.7 / 2.1 + 34.2 * 1.5 + 78.9 / 3.3 - 12.1 * 4.5 + 67.8 - 45.6 / 1.2 + 23.4 * 5.6 - 78.9 / 2.3 + 12.3 * 4.5 - 9.8 / 1.1) * 2.3 - 45.6");
			Assert::AreEqual(4480.177, result, 0.01, L"Calculation failed!");
		}
	};
}
