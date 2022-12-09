#ifndef COMPLEX3D_H
#define COMPLEX3D_H

#include <QPoint>

class Complex3D 
// class representing a complex number in a 3D plane
{
private:
// private variables
    qreal x = 0;
    qreal y = 0;
    qreal z = 0;

public:
    // default constructor
    Complex3D() = default;
    
    // constructor which initializes the points
    Complex3D(qreal newx, qreal newy, qreal newz);

    // Tetha and phi are used to get the polar form of the complex number
    [[nodiscard]] qreal theta() const;

    [[nodiscard]] qreal phi() const;

    [[nodiscard]] qreal abs() const;

    friend void operator^(Complex3D &z, int const &n);

    // getters
    qreal getX() const;
    qreal getY() const;
    qreal getZ() const;
};


#endif // COMPLEX3D_H
