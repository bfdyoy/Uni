#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "FractalData.h"
#include "FractalWidget.h"

#include <QColorDialog>
#include <QDoubleSpinBox>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressBar>
#include <QScrollBar>
#include <QSlider>
#include <QTemporaryDir>
#include <QTimer>

#include <ui_mainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

QT_FORWARD_DECLARE_CLASS(QOpenGLWidget)

class MainWindow : public QMainWindow {
    Q_OBJECT
    static const qint64 LIMIT = 180000;

public:
    // explicit constructor
    explicit MainWindow(QWidget *parent = nullptr);

    // destructor
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    FractalData data{};
    QElapsedTimer *elapsedTimer{};
    QTimer *timer{};
    qint64 time{}, frames{};
    QTemporaryDir *temporaryDir{};
    QSize prevSize{};
    bool isFullScreen = false;
    bool isSetting = true;

    void connectBoxBar();

    void makeMenu(); // create the menu

    void chooseColor(QColor const &color, ColorType type); // when choose a color is choosen

    void askColor(ColorType type);

    void updateButtons(); // update buttons states

    void readAndDraw(); // read new data and redraw

    void setValues(); // set new data for the values

    void generateRandom(); // generate random data

    void hideAndShow(); // hide and show window

    void hideBorders(); // hide the borders of the window

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
