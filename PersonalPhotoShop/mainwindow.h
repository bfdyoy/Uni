#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include <QMimeData>
#include <QDropEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDragEnterEvent>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "blur.h"
#include "resize.h"
#include "rotate.h"
#include "crop.h"

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void newResize();
    void newRotate();
    void newCrop();
    void newBlur();

signals:
    void cleanBlur();
    void cleanResize();
    void cleanRotate();
    void cleanCrop();

private:
    Ui::MainWindow *ui;
    Mat image;
    Mat pastImg;
    Resize *size;
    Rotate *rotate;
    Crop *crop;
    Blur *blur;
private slots:
    void fileProcess();
    void switchPages();
    void accept();
    void reject();
protected:
    void dropEvent(QDropEvent*);
    void closeEvent(QCloseEvent*);
    void dragEnterEvent(QDragEnterEvent*);
};
#endif // MAINWINDOW_H
