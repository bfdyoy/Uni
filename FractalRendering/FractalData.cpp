#include "FractalData.h"
#include <QPair>
#include <QVector>
#include <functional>
#include <map>
#include <utility>
#include <vector>
#include <random>

const QVector3D FractalData::baseCamera = QVector3D(0, 0, 1.5);// is more centered, but worse in some way

namespace {
    qreal randomReal() {
        std::uniform_real_distribution<double> dist(-0.3, 0.3);
        return dist(*QRandomGenerator::global());
    }

    QColor randomColor() {
        return QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255));
    }

    static std::map<const std::string, const std::pair<std::function<qreal(std::vector<int> const &, std::vector<int> const &)>, const qreal>> metrics = {
            {"minkowski-normalized",
             {
                     [](std::vector<int> const &u, std::vector<int> const &v) -> qreal {
                         static const int p = 5;
                         qreal out = 0;
                         for(size_t i = 0; i < std::min(u.size(), v.size()); i++)
                             out += std::pow(std::abs(u[i] - v[i]) / 255., p);
                         return std::pow(out, 1. / p) / std::pow(3, 1. / p);
                     },
                     0.25// threshold
             }}};

    bool isSimilar(QColor const &u, QColor const &v, std::pair<std::function<qreal(std::vector<int>, std::vector<int>)>, qreal> const &metric) {
        static const auto toVector = [](QColor const &color) -> std::vector<int> {
            return {color.red(), color.green(), color.blue()};
        };
        return metric.first(toVector(u), toVector(v)) < metric.second;
    };

    bool isBlack(QColor const &color) {
        return color.value() < 150;
    }

}// namespace

void FractalData::genRandom() {
    // generate randomized data
    a = randomReal();
    b = randomReal();
    c = randomReal();
    n = 2 * (QRandomGenerator::global()->bounded(4) + 2);
    type = FractalType(QRandomGenerator::global()->bounded(5));
    auto genColors = [this]() {
        fractalColor = randomColor();
        ambienceColor = randomColor();
    };
    do {
        genColors();
        ;
    } while(isSimilar(fractalColor, ambienceColor, metrics["minkowski-normalized"]) || isBlack(fractalColor));
    // generate colors that are not similar
    zoomCoefficient = defaultZoom;
}

FractalData::FractalData() {
    genRandom();
}

FractalData::FractalData(qreal a, qreal b, qreal c, quint8 n, FractalType type, const QColor &fractalColor, const QColor &ambienceColor, const QVector3D &camera, qreal zoomCoefficient, bool isRotating) : a(a), b(b), c(c), n(n), type(type), fractalColor(fractalColor), ambienceColor(ambienceColor), camera(camera), zoomCoefficient(zoomCoefficient), isRotating(isRotating) {}

void FractalData::setZoomCoefficient(qreal zoomCoefficient) {
    FractalData::zoomCoefficient = zoomCoefficient;
}

void FractalData::setAbsoluteSpeed(qreal absoluteSpeed) {
    FractalData::absoluteSpeed = absoluteSpeed;
}
