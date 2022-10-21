#ifndef COMPLEX3D_H
#define COMPLEX3D_H

#include <QPoint>

class Complex3D {
private:
    qreal x = 0;
    qreal y = 0;
    qreal z = 0;

public:
    Complex3D() = default;

    Complex3D(qreal newx, qreal newy, qreal newz);

    // Tetha and phi are used to get the polar form of the complex number
    [[nodiscard]] qreal theta() const;

    [[nodiscard]] qreal phi() const;

    [[nodiscard]] qreal abs() const;

    friend void operator^(Complex3D &z, int const &n);

    friend Complex3D operator+(Complex3D a, Complex3D b);
};


#endif // COMPLEX3D_H
