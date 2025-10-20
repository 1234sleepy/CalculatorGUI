#pragma once

#include <iostream>

struct QuadraticValues
{
    double a = 0;
    double b = 0;
    double c = 0;

    static QuadraticValues fromConstant(double val);
    static QuadraticValues fromVariable(const std::string& var);

    QuadraticValues operator+(const QuadraticValues& rhs) const;
    QuadraticValues operator-(const QuadraticValues& rhs) const;
    QuadraticValues operator*(const QuadraticValues& rhs) const;
    QuadraticValues operator/(const QuadraticValues& rhs) const;
};