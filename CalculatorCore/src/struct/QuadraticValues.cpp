#include "pch.h"
#include "../../include/struct/QuadraticValues.h"

QuadraticValues QuadraticValues::fromConstant(double val)
{
    return { 0, 0, val };
}

QuadraticValues QuadraticValues::fromVariable(const std::string& var)
{
    if (var == "x^2") return { 1, 0, 0 };
    if (var == "x")   return { 0, 1, 0 };
    return { 0, 0, 0 };
}

QuadraticValues QuadraticValues::operator+(const QuadraticValues& rhs) const
{
    return { a + rhs.a, b + rhs.b, c + rhs.c };
}

QuadraticValues QuadraticValues::operator-(const QuadraticValues& rhs) const
{
    return { a - rhs.a, b - rhs.b, c - rhs.c };
}

QuadraticValues QuadraticValues::operator*(const QuadraticValues& rhs) const
{
    if ((a != 0 || b != 0) && (rhs.a != 0 || rhs.b != 0))
        return { 0, 0, 0 };
    if (rhs.a == 0 && rhs.b == 0)
        return { a * rhs.c, b * rhs.c, c * rhs.c };

    if (a == 0 && b == 0)
        return { rhs.a * c, rhs.b * c, rhs.c * c };

    return { 0, 0, 0 }; 
}

QuadraticValues QuadraticValues::operator/(const QuadraticValues& rhs) const
{
    if (rhs.a != 0 || rhs.b != 0)
        return { 0, 0, 0 };

    return { a / rhs.c, b / rhs.c, c / rhs.c };
}