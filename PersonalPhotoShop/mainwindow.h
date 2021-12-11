#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

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

private:
    Ui::MainWindow *ui;
    Mat image;
    Mat pastImg;
private slots:
    void fileProcess();
protected:
    void dropEvent(QDropEvent*);
    void closeEvent(QCloseEvent*);
    void dragEnterEvent(QDragEnterEvent*);
};
#endif // MAINWINDOW_H
