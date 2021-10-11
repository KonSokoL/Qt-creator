#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <math.h>

struct Point
{
    int x = 0;
    int y = 0;
};

class Triangle
{
private:
    double  perimeterCalculate();
    double  squareCalculate();
    double a = 0, b = 0, c = 0;
    double p = 0;
    double s = 0;
public:
    Point point1, point2, point3;
    double  getPerimeter();
    double  getSquare();
    bool    checkTriangleExists();
};

#endif // TRIANGLE_H
