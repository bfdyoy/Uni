QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Complex3D.cpp \
    FractalData.cpp \
    FractalPoint.cpp \
    FractalWidget.cpp \
    GeometryEngine.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Complex3D.h \
    FractalData.h \
    FractalPoint.h \
    FractalWidget.h \
    GeometryEngine.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders/shaders.qrc

DISTFILES += \
    shaders/fshader.glsl \
    shaders/vshader.glsl
