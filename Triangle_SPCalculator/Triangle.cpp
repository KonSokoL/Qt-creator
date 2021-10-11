#include "Triangle.h"

double Triangle::getPerimeter()
{
    return perimeterCalculate();
}

double Triangle::getSquare()
{
    return squareCalculate();
}

double Triangle::perimeterCalculate()
{
    a = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
    b = sqrt(pow(point3.x - point2.x, 2) + pow(point3.y - point2.y, 2));
    c = sqrt(pow(point3.x - point1.x, 2) + pow(point3.y - point1.y, 2));

    p = a + b + c;
    return p;
}

double Triangle::squareCalculate()
{
    p = perimeterCalculate();

    double halfp = p / 2;

    s = sqrt(halfp * (halfp - a) * (halfp - b) * (halfp - c));
    return s;
}

bool Triangle::checkTriangleExists()
{
    a = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
    b = sqrt(pow(point3.x - point2.x, 2) + pow(point3.y - point2.y, 2));
    c = sqrt(pow(point3.x - point1.x, 2) + pow(point3.y - point1.y, 2));

    if ((a + b > c) && (a + c > b) && (b + c > a))
    {
        return true;
    }
    else
    {
        return false;
    }
}
