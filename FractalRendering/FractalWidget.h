#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include "FractalData.h"
#include "GeometryEngine.h"

#include <QApplication>
#include <QElapsedTimer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QTimer>
#include <QVector2D>
#include <cmath>
#include <utility>

class FractalWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
// Is the part of the UI that shows the fractal
public:
    using QOpenGLWidget::QOpenGLWidget;

    // destructor
    ~FractalWidget();

    // set the data for a fractal
    void setFractalData(FractalData *data);

protected:
    // For zoom-in and zoom-out on wheel scrolled
    void wheelEvent(QWheelEvent *e) override; // wheel event handler

    void mousePressEvent(QMouseEvent *e) override; // mouse pressed event handler

    void mouseMoveEvent(QMouseEvent *e) override; // mouse move event handler

    void mouseReleaseEvent(QMouseEvent *) override; // mouse release event handler

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void initShaders(); // initialise the shaders

    void rotateFractal(QVector2D const &diff); // rotate the fractal

    void autoRotate(); // handle the auto rotation

private:
    bool mousePressed = false;
    QOpenGLShaderProgram program;
    FractalData *fractalData;
    GeometryEngine *geometries = nullptr;
    QElapsedTimer *elapsedTimer = nullptr;
    QTimer *timer = nullptr;

    QMatrix4x4 projection;
    QVector2D mousePressPosition;
    QVector3D pointAxisX = QVector3D(1.0, 0.0, 1.5);
    QVector3D pointAxisY = QVector3D(0.0, 1.0, 1.5);
    qreal autoRotationPos = 0.0;
};


#endif // FRACTALWIDGET_H
