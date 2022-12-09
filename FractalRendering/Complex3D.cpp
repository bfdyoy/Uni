#include "Complex3D.h"
#include "cmath"

Complex3D::Complex3D(qreal newx, qreal newy, qreal newz) : x(newx), y(newy), z(newz)
{
}

Complex3D operator+(const Complex3D& a, const Complex3D& b) {
    return Complex3D(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

qreal Complex3D::abs() const 
// calculate the absolute value
{
    return sqrt(x * x + y * y + z * z);
}

qreal Complex3D::theta() const 
// calculate theta
{
    return atan2(sqrt(x * x + y * y), z);
}

qreal Complex3D::phi() const 
// calculate phi
{
    return atan2(y, x);
}

qreal Complex3D::getX() const
// get the value of x
{
    return x;
}

qreal Complex3D::getY() const
// get the value of y
{
    return y;
}

qreal Complex3D::getZ() const
// get the value of z
{
    return z;
}

// calculate z to the power of n
void operator^(Complex3D &z, int const &n) {
    // auxiliary variable
    int help = 1;
    const int m = n - n % 2;
    
    // get the absolute value of the number z
    qreal r_n = z.abs();

    while(help < m) {
        r_n = r_n * r_n;
        help *= 2;
    }

    // check the parity
    if(n % 2 == 1) {
        r_n = z.abs() * r_n;
    }

    qreal theta_n = z.theta() * n;
    qreal phi_n = z.phi() * n;
    // update values
    z.x = r_n * sin(theta_n) * cos(phi_n);
    z.y = r_n * sin(theta_n) * sin(phi_n);
    z.z = r_n * cos(theta_n);
}
