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
    explicit MainWindow(QWidget *parent = nullptr);

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

    void makeMenu();

    void chooseColor(QColor const &color, ColorType type);

    void askColor(ColorType type);

    void updateButtons();

    void readAndDraw();

    void setValues();

    void recordClickAction();

    void generateRandom();

    void hideAndShow();

    void hideBorders();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
