#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions {
public:
    // constructor
    GeometryEngine();

    // virtual destructor
    virtual ~GeometryEngine();

    void drawGeometry(const QOpenGLShaderProgram *program); // draw the geometry

private:
    void initGeometry(); // initilise the geometry

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};


#endif // GEOMETRYENGINE_H
