#include "FractalWidget.h"

namespace {
    QVector3D transformColor(const QColor &color) {
        return QVector3D(float(color.red() / 255.0), float(color.green() / 255.0), float(color.blue() / 255.0));
    }
}// namespace

FractalWidget::~FractalWidget() {
    // Make sure the context is current when deleting the buffers.
    makeCurrent();
    delete geometries;
    doneCurrent();
}

void FractalWidget::wheelEvent(QWheelEvent *e) {
    // wheel event for zoom on scroll
    static const qreal degreesCoefficient = 1.0 / 360;
    static const qreal EPS = 0.001;
    QPoint numDegrees = e->angleDelta();

    // set min and max values
    static const qreal minZoom = -5.0;
    static const qreal maxZoom = 9.0;

    // get new values
    qreal delta = numDegrees.y() * degreesCoefficient;
    qreal newValue = fractalData->zoomCoefficient + delta;
    qreal newSpeed = fractalData->rotateSpeed;

    // reset speed based on the zoom
    if(newValue > FractalData::defaultZoom) 
    {
        newSpeed /= (1 + (newValue - FractalData::defaultZoom) * 0.1);
    }

    // check if new values can be applied
    if(EPS < abs(delta) && minZoom <= newValue && newValue <= maxZoom) {
        fractalData->zoomCoefficient = newValue;
        fractalData->rotateSpeed = newSpeed;
        update();
    }
}

void FractalWidget::mousePressEvent(QMouseEvent *e) {
    // Save mouse press position
    mousePressPosition = QVector2D(e->pos());
    // mouse pressed
    mousePressed = true;
}

void FractalWidget::mouseReleaseEvent(QMouseEvent *)
// reset state
{
    mousePressed = false;
}

namespace {
    // set up the rotation vector
    QVector3D rotate(QVector3D point, qreal alpha, QVector3D axis) {
        qreal t11 = cos(alpha) + (1 - cos(alpha)) * axis.x() * axis.x();
        qreal t12 = (1 - cos(alpha)) * axis.x() * axis.y() - sin(alpha) * axis.z();
        qreal t13 = (1 - cos(alpha)) * axis.x() * axis.z() + sin(alpha) * axis.y();
        qreal t21 = (1 - cos(alpha)) * axis.x() * axis.y() + sin(alpha) * axis.z();
        qreal t22 = cos(alpha) + (1 - cos(alpha)) * axis.y() * axis.y();
        qreal t23 = (1 - cos(alpha)) * axis.y() * axis.z() - sin(alpha) * axis.x();
        qreal t31 = (1 - cos(alpha)) * axis.x() * axis.z() - sin(alpha) * axis.y();
        qreal t32 = (1 - cos(alpha)) * axis.y() * axis.z() + sin(alpha) * axis.x();
        qreal t33 = cos(alpha) + (1 - cos(alpha)) * axis.z() * axis.z();
        return QVector3D(float(point.x() * t11) + float(point.y() * t21) + float(point.z() * t31),
                         float(point.x() * t12) + float(point.y() * t22) + float(point.z() * t32),
                         float(point.x() * t13) + float(point.y() * t23) + float(point.z() * t33));
    }
};// namespace

void FractalWidget::rotateFractal(QVector2D const &diff) {
    // rotate camera and fractal based on click movement
    if(diff.x() == 0 && diff.y() == 0)
        return;
    // initialise alpha
    QVector2D alpha = diff / 720.;

    QVector3D vecAxisY = (pointAxisY - fractalData->camera).normalized();

    // compute value on X axis
    pointAxisX = rotate(pointAxisX, alpha.x(), vecAxisY);
    pointAxisY = rotate(pointAxisY, alpha.x(), vecAxisY);
    fractalData->camera = rotate(fractalData->camera, alpha.x(), vecAxisY);

    QVector3D vecAxisX = (pointAxisX - fractalData->camera).normalized();

    // compute value on Y axis
    fractalData->camera = rotate(fractalData->camera, alpha.y(), vecAxisX);
    pointAxisX = rotate(pointAxisX, alpha.y(), vecAxisX);
    pointAxisY = rotate(pointAxisY, alpha.y(), vecAxisX);

    // update the position of the fractal
    update();
}

void FractalWidget::mouseMoveEvent(QMouseEvent *e) 
// mouse move event handler
{
    if(!mousePressed)
        return;
    // when the mouse is clicked and dragged
    // the position needs to be updated
    rotateFractal(QVector2D(e->pos()) - mousePressPosition);
    mousePressPosition = QVector2D(e->pos()); // update position
}

void FractalWidget::initializeGL() {
    this->setMouseTracking(true);

    // setup all the used functions
    initializeOpenGLFunctions();

    // set background color to black and opaque
    glClearColor(0, 0, 0, 1); 

    // initilise the shaders
    initShaders();

    // Enable depth buffer (compare values of buffers)
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling (render only visible polygons)
    glEnable(GL_CULL_FACE);

    geometries = new GeometryEngine;

    // Prepare for auto-rotation
    timer = new QTimer;
    elapsedTimer = new QElapsedTimer();
    connect(timer, &QTimer::timeout, [this]() { autoRotate(); }); // connect the signal to the slot
    elapsedTimer->start();
    timer->start();
}

void FractalWidget::initShaders() {
    // Compile vertex shader
    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if(!program.link())
        close();

    // Bind shader pipeline for use
    if(!program.bind())
        close();
}

void FractalWidget::resizeGL(int w, int h) {
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // default values
    const qreal zNear = 3.0;
    const qreal zFar = 7.0;
    const qreal fov = 45.0;

    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, float(aspect), zNear, zFar);
}

void FractalWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, float(fractalData->zoomCoefficient));
    matrix.lookAt(fractalData->camera, -fractalData->camera, pointAxisY - fractalData->camera);

    // set open gl values
    program.setUniformValue("mvp_matrix", projection * matrix);

    program.setUniformValue("POWER", (GLint) fractalData->n);
    program.setUniformValue("Resolution", dynamic_cast<QApplication *>(QCoreApplication::instance())->devicePixelRatio() * QVector2D(float(this->width()), float(this->height())));
    program.setUniformValue("CriticalPointX", (GLfloat) fractalData->a);
    program.setUniformValue("CriticalPointY", (GLfloat) fractalData->b);
    program.setUniformValue("CriticalPointZ", (GLfloat) fractalData->c);
    program.setUniformValue("TYPE", (GLint) fractalData->type);
    program.setUniformValue("Ambience", transformColor(fractalData->ambienceColor));
    program.setUniformValue("ColorFractal", transformColor(fractalData->fractalColor));
    program.setUniformValue("CameraPosition", fractalData->camera);
    program.setUniformValue("ZoomCoefficient", (GLfloat) fractalData->zoomCoefficient);

    // Draw geometry
    geometries->drawGeometry(&program);
}

void FractalWidget::setFractalData(FractalData *data) 
// set the value of FractalData
{
    fractalData = data;
}

void FractalWidget::autoRotate() 
// handle autorotation
{
    if(fractalData->isRotating) {
        auto nextPos = static_cast<qreal>(elapsedTimer->elapsed());
        qreal dx = (nextPos - autoRotationPos) * fractalData->absoluteSpeed;
        autoRotationPos = nextPos;
        rotateFractal({static_cast<float>(dx), 0.0});
    }
}
