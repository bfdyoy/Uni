#include "FractalPoint.h"

// constructor
FractalPoint::FractalPoint(qreal newX, qreal newY, const QColor& newColor): x(newX), y(newY), color(newColor) 
{
}

QColor FractalPoint::getColor() const 
// get the color used
{
    return color;
}

void FractalPoint::setColor(const QColor& newColor) 
// set a new color
{
    color = newColor;
}

qreal FractalPoint::getX() const 
// get the value of x
{
    return x;
}

qreal FractalPoint::getY() const 
// get the value of y
{
    return y;
}

void FractalPoint::setX(qreal newX) & 
// set the value of x
{
    x = newX;
}

void FractalPoint::setY(qreal newY) & 
// set the value of y
{
    y = newY;
}
