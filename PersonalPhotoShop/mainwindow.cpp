#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dragndrop.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setAcceptDrops(true);

    connect(ui->open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(fileProcess()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileProcess()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->open && image.empty())
    {

        QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *.jpeg)"));
        if(!filePath.isEmpty())
        {
            image = imread(filePath.toStdString().c_str());
            imshow("Image", image);
            emit ui->Crop->triggered();
        }
    }
    else if(action == ui->save && !image.empty())
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "",tr("Image(*.png *.jpg)"));
        if(!filePath.isEmpty())
        {
            imwrite(filePath.toStdString().c_str(), image);
            image.release();
            destroyWindow("Image");
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
}
