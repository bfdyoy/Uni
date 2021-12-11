QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += D:\OpenCV\openvc_built\install\include

LIBS += D:\OpenCV\openvc_built\install\x64\vc16\lib\opencv_core411.lib
LIBS += D:\OpenCV\openvc_built\install\x64\vc16\lib\opencv_imgcodecs411.lib
LIBS += D:\OpenCV\openvc_built\install\x64\vc16\lib\opencv_imgproc411.lib
LIBS += D:\OpenCV\openvc_built\install\x64\vc16\lib\opencv_highgui411.lib
LIBS += D:\OpenCV\openvc_built\install\x64\vc16\lib\opencv_videoio411.lib
LIBS += D:\OpenCV\openvc_built\install\x64\vc16\lib\opencv_calib3d411.lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    crop.cpp \
    main.cpp \
    mainwindow.cpp \
    resize.cpp

HEADERS += \
    crop.h \
    dragndrop.h \
    mainwindow.h \
    resize.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
