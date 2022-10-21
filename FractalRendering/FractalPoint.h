#ifndef FRACTALPOINT_H
#define FRACTALPOINT_H

#include <QColor>
#include <QPoint>

class FractalPoint {
private:
    qreal x, y;
    QColor color;

public:
    FractalPoint(qreal newX, qreal newY, QColor newColor);

    [[nodiscard]] QColor getColor() const;

    void setColor(QColor newColor);

    [[nodiscard]] qreal getX() const;

    [[nodiscard]] qreal getY() const;

    void setX(qreal newX) &;

    void setY(qreal newY) &;
};


#endif // FRACTALPOINT_H
