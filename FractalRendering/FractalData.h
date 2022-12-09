#ifndef FRACTALDATA_H
#define FRACTALDATA_H


#include <QColor>
#include <QDataStream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QVector3D>
#include <random>

// naming the fractal types
// several fractals are treated
enum class FractalType {
    MANDELBROT,
    PSYCHOFRACTAL,
    ANOTHERFRACTAL,
    FLOWERFRACTAL,
    NEWFRACTAL,
    NEWNEWFRACTAL
};

// naming the color types
//only fractal's color and the background can be changed
enum class ColorType {
    FRACTAL,
    AMBIENCE
};

class FractalData {
public:
    // constants
    static const QVector3D baseCamera;
    static constexpr const qreal defaultZoom = -3.0; // default values for the zoom
    static constexpr const qreal defaultSpeed = 0.25; // default values for the speed

    // other useful variables
    qreal a{};
    qreal b{};
    qreal c{};
    quint8 n = 2;
    FractalType type{};
    QColor fractalColor = QColor(55, 255, 55);
    QColor ambienceColor = QColor(255, 55, 55);
    QVector3D camera = baseCamera;
    qreal zoomCoefficient = defaultZoom;
    qreal rotateSpeed = defaultSpeed;
    qreal absoluteSpeed = defaultSpeed;
    bool isRotating = false;

    // default constructor
    FractalData();

    [[maybe_unused]] FractalData(qreal a, qreal b, qreal c, quint8 n, FractalType type);

    FractalData(qreal a, qreal b, qreal c, quint8 n, FractalType type, const QColor &fractalColor, const QColor &ambienceColor, const QVector3D &camera, qreal zoomCoefficient, bool isRotating);

    void setZoomCoefficient(qreal zoomCoefficient = defaultZoom);

    void setAbsoluteSpeed(qreal absoluteSpeed);

    // generate a random number
    void genRandom();
};

#endif // FRACTALDATA_H
