#ifndef FRACTALPOINT_H
#define FRACTALPOINT_H

#include <QColor>
#include <QPoint>

class FractalPoint {
private:
    qreal x;
    qreal y;
    QColor color;

public:
    // constructor
    FractalPoint(qreal newX, qreal newY, const QColor& newColor);

    // getters
    [[nodiscard]] qreal getX() const;
    [[nodiscard]] qreal getY() const;

    [[nodiscard]] QColor getColor() const;

    // setters
    void setX(qreal newX) &;
    void setY(qreal newY) &;
  
    // set a new color
    void setColor(const QColor& newColor);
};


#endif // FRACTALPOINT_H
